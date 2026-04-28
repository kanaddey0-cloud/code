#include <chrono>
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <new>
#include <utility>

using namespace std;
using namespace std::chrono;

/*
    AVLTREE<T> - pointer based, performance oriented AVL tree
    ---------------------------------------------------------

    This version uses real node pointers:

        node->left
        node->right
        node->parent

    It is still optimized for the provided benchmark:

    1. Preallocated node pool
       A normal pointer AVL tree often does "new Node" for every insert. That is
       very slow for 10 million nodes. This implementation allocates one large
       contiguous pool and constructs nodes inside it.

    2. Pointer links
       Children and parents are Node* pointers, similar to:

           struct AVLnode { int H:8; D K; AVLnode<D>* L, *R; };

       I use an unsigned char height instead of an int bit-field because it is
       simple, compact, and usually faster for this workload.

    3. Parent pointer
       The parent pointer lets insertion rebalance upward without recursion and
       without keeping a separate stack.

    4. Increasing-input fast path
       Your test inserts 1, 2, 3, ... . When the new value is greater than the
       current maximum, the node is attached directly after the current max node
       instead of searching from the root.

    5. Early AVL stop
       After an insertion, AVL rebalancing only continues while subtree height
       changes. Once height is unchanged, all ancestors above it are unchanged.

    Complexity:
       insert(value): O(log n), with a faster path for increasing values
       contains(value): O(log n)
       size(): O(1)
*/
template <typename T>
class AVLTREE {
private:
    struct Node {
        T value;
        Node* left;
        Node* right;
        Node* parent;
        unsigned char height;

        explicit Node(const T& v)
            : value(v), left(nullptr), right(nullptr), parent(nullptr), height(1) {}
    };

    Node* pool;
    size_t node_count;
    size_t node_capacity;
    Node* root;
    Node* max_node;

    static int height(const Node* node) {
        return node == nullptr ? 0 : node->height;
    }

    static int balance_factor(const Node* node) {
        return height(node->left) - height(node->right);
    }

    static void refresh_height(Node* node) {
        const int lh = height(node->left);
        const int rh = height(node->right);
        node->height = static_cast<unsigned char>((lh > rh ? lh : rh) + 1);
    }

    void destroy_storage() {
        for (size_t i = 0; i < node_count; ++i) {
            pool[i].~Node();
        }

        ::operator delete(pool);
    }

    Node* make_node(const T& value) {
        if (node_count == node_capacity) {
            reserve(node_capacity == 0 ? 2 : node_capacity * 2);
        }

        Node* node = &pool[node_count++];
        new (node) Node(value);
        return node;
    }

    Node* rotate_right(Node* y) {
        Node* x = y->left;
        Node* moved_subtree = x->right;
        Node* parent = y->parent;

        x->right = y;
        x->parent = parent;
        y->left = moved_subtree;
        y->parent = x;

        if (moved_subtree != nullptr) {
            moved_subtree->parent = y;
        }

        if (parent == nullptr) {
            root = x;
        } else if (parent->left == y) {
            parent->left = x;
        } else {
            parent->right = x;
        }

        refresh_height(y);
        refresh_height(x);

        return x;
    }

    Node* rotate_left(Node* x) {
        Node* y = x->right;
        Node* moved_subtree = y->left;
        Node* parent = x->parent;

        y->left = x;
        y->parent = parent;
        x->right = moved_subtree;
        x->parent = y;

        if (moved_subtree != nullptr) {
            moved_subtree->parent = x;
        }

        if (parent == nullptr) {
            root = y;
        } else if (parent->left == x) {
            parent->left = y;
        } else {
            parent->right = y;
        }

        refresh_height(x);
        refresh_height(y);

        return y;
    }

    Node* rebalance(Node* node) {
        refresh_height(node);

        const int bf = balance_factor(node);

        if (bf > 1) {
            if (balance_factor(node->left) < 0) {
                rotate_left(node->left);
            }
            return rotate_right(node);
        }

        if (bf < -1) {
            if (balance_factor(node->right) > 0) {
                rotate_right(node->right);
            }
            return rotate_left(node);
        }

        return node;
    }

public:
    explicit AVLTREE(size_t reserve_count = 10000000)
        : pool(nullptr), node_count(0), node_capacity(0),
          root(nullptr), max_node(nullptr) {
        reserve(reserve_count);
    }

    ~AVLTREE() {
        destroy_storage();
    }

    AVLTREE(const AVLTREE&) = delete;
    AVLTREE& operator=(const AVLTREE&) = delete;

    AVLTREE(AVLTREE&& other) noexcept
        : pool(other.pool), node_count(other.node_count),
          node_capacity(other.node_capacity), root(other.root),
          max_node(other.max_node) {
        other.pool = nullptr;
        other.node_count = 0;
        other.node_capacity = 0;
        other.root = nullptr;
        other.max_node = nullptr;
    }

    AVLTREE& operator=(AVLTREE&& other) noexcept {
        if (this != &other) {
            destroy_storage();

            pool = other.pool;
            node_count = other.node_count;
            node_capacity = other.node_capacity;
            root = other.root;
            max_node = other.max_node;

            other.pool = nullptr;
            other.node_count = 0;
            other.node_capacity = 0;
            other.root = nullptr;
            other.max_node = nullptr;
        }

        return *this;
    }

    void reserve(size_t count) {
        if (count <= node_capacity) {
            return;
        }

        Node* new_pool = static_cast<Node*>(::operator new(sizeof(Node) * count));

        /*
            Reallocation invalidates pointers, so pointer rebasing is required.
            The benchmark uses the default 10,000,000 reserve, so this slow path
            is not hit during the measured loop.
        */
        const intptr_t byte_offset = static_cast<intptr_t>(
            reinterpret_cast<uintptr_t>(new_pool) - reinterpret_cast<uintptr_t>(pool));

        for (size_t i = 0; i < node_count; ++i) {
            new (&new_pool[i]) Node(std::move(pool[i]));

            if (new_pool[i].left != nullptr) {
                new_pool[i].left = reinterpret_cast<Node*>(
                    reinterpret_cast<uintptr_t>(new_pool[i].left) + byte_offset);
            }
            if (new_pool[i].right != nullptr) {
                new_pool[i].right = reinterpret_cast<Node*>(
                    reinterpret_cast<uintptr_t>(new_pool[i].right) + byte_offset);
            }
            if (new_pool[i].parent != nullptr) {
                new_pool[i].parent = reinterpret_cast<Node*>(
                    reinterpret_cast<uintptr_t>(new_pool[i].parent) + byte_offset);
            }

            pool[i].~Node();
        }

        if (root != nullptr) {
            root = reinterpret_cast<Node*>(reinterpret_cast<uintptr_t>(root) + byte_offset);
        }
        if (max_node != nullptr) {
            max_node = reinterpret_cast<Node*>(
                reinterpret_cast<uintptr_t>(max_node) + byte_offset);
        }

        ::operator delete(pool);
        pool = new_pool;
        node_capacity = count;
    }

    size_t size() const {
        return node_count;
    }

    bool empty() const {
        return root == nullptr;
    }

    bool contains(const T& value) const {
        Node* cur = root;

        while (cur != nullptr) {
            if (value < cur->value) {
                cur = cur->left;
            } else if (cur->value < value) {
                cur = cur->right;
            } else {
                return true;
            }
        }

        return false;
    }

    bool insert(const T& value) {
        if (root == nullptr) {
            root = make_node(value);
            max_node = root;
            return true;
        }

        Node* parent = nullptr;

        if (max_node->value < value) {
            // Fast path for strictly increasing input.
            parent = max_node;
            Node* inserted = make_node(value);
            inserted->parent = parent;
            parent->right = inserted;
            max_node = inserted;
        } else {
            Node* cur = root;

            while (true) {
                parent = cur;

                if (value < cur->value) {
                    if (cur->left == nullptr) {
                        Node* inserted = make_node(value);
                        inserted->parent = parent;
                        cur->left = inserted;
                        break;
                    }

                    cur = cur->left;
                } else if (cur->value < value) {
                    if (cur->right == nullptr) {
                        Node* inserted = make_node(value);
                        inserted->parent = parent;
                        cur->right = inserted;

                        if (max_node->value < value) {
                            max_node = inserted;
                        }

                        break;
                    }

                    cur = cur->right;
                } else {
                    return false;
                }
            }
        }

        while (parent != nullptr) {
            const int old_height = parent->height;
            Node* new_subroot = rebalance(parent);

            if (new_subroot->height == old_height) {
                break;
            }

            parent = new_subroot->parent;
        }

        return true;
    }
};

int main() {
    cout << "Program started\n";

    srand(static_cast<unsigned>(time(0)));

    auto start = high_resolution_clock::now();

    AVLTREE<int> tree;
    int n = 10000000;

    cout << "S\n";
    for (int i = 1; i < n; i++) {
        tree.insert(i);
    }
    cout << "I\n";

    auto end = high_resolution_clock::now();

    cout << "size: " << tree.size() << "\n";
    cout << "contains last: " << tree.contains(n - 1) << "\n";
    cout << duration_cast<milliseconds>(end - start).count() << " ms\n";

    cout << "Program finished\n";
    return 0;
}
