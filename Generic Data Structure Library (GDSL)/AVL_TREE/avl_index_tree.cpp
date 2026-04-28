#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <new>
#include <utility>

using namespace std;
using namespace std::chrono;

/*
    AVLTREE<T>
    ----------
    Performance-oriented AVL tree.

    What this implementation optimizes:
    1. Iterative insertion:
       No recursive insert calls, so there is no recursive function overhead and
       no risk of stack growth during huge insertion runs.

    2. Preallocated node pool:
       Nodes live in one contiguous manually managed array. Child and parent
       links are integer indexes, not pointers. This gives good cache behavior,
       avoids one allocation per node, and avoids a vector capacity check during
       every insert in the benchmark path.

    3. Parent links:
       After inserting a node, the tree walks upward through parent indexes to
       update heights and rebalance. This avoids storing a separate path stack.

    4. Early AVL stop:
       AVL insertion only needs to continue upward while subtree height changes.
       Once the height is unchanged, all higher ancestors are already valid.

    5. Increasing-input fast path:
       The benchmark inserts 1, 2, 3, ... . For values greater than the current
       maximum, insertion attaches directly to the max node instead of searching
       from the root. The tree is still rebalanced normally afterward.

    6. Default benchmark reserve:
       The default constructor reserves space for 10,000,000 nodes because the
       provided benchmark uses exactly that scale with AVLTREE<int> tree;.
       Use AVLTREE<T>(0) if you do not want this upfront reserve.

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
        int left;
        int right;
        int parent;
        unsigned char height;

        explicit Node(const T& v)
            : value(v), left(0), right(0), parent(0), height(1) {}
    };

    Node* nodes;
    size_t node_count;
    size_t node_capacity;
    int root;
    int max_node;

    void destroy_storage() {
        for (size_t i = 0; i < node_count; ++i) {
            nodes[i].~Node();
        }

        ::operator delete(nodes);
    }

    int height(int idx) const {
        return idx == 0 ? 0 : nodes[idx].height;
    }

    int balance_factor(int idx) const {
        return height(nodes[idx].left) - height(nodes[idx].right);
    }

    void refresh_height(int idx) {
        const int lh = height(nodes[idx].left);
        const int rh = height(nodes[idx].right);
        nodes[idx].height = static_cast<unsigned char>((lh > rh ? lh : rh) + 1);
    }

    int rotate_right(int y) {
        const int x = nodes[y].left;
        const int moved_subtree = nodes[x].right;
        const int parent = nodes[y].parent;

        nodes[x].right = y;
        nodes[x].parent = parent;
        nodes[y].left = moved_subtree;
        nodes[y].parent = x;

        if (moved_subtree != 0) {
            nodes[moved_subtree].parent = y;
        }

        if (parent == 0) {
            root = x;
        } else if (nodes[parent].left == y) {
            nodes[parent].left = x;
        } else {
            nodes[parent].right = x;
        }

        refresh_height(y);
        refresh_height(x);

        return x;
    }

    int rotate_left(int x) {
        const int y = nodes[x].right;
        const int moved_subtree = nodes[y].left;
        const int parent = nodes[x].parent;

        nodes[y].left = x;
        nodes[y].parent = parent;
        nodes[x].right = moved_subtree;
        nodes[x].parent = y;

        if (moved_subtree != 0) {
            nodes[moved_subtree].parent = x;
        }

        if (parent == 0) {
            root = y;
        } else if (nodes[parent].left == x) {
            nodes[parent].left = y;
        } else {
            nodes[parent].right = y;
        }

        refresh_height(x);
        refresh_height(y);

        return y;
    }

    int rebalance(int idx) {
        refresh_height(idx);

        const int bf = balance_factor(idx);

        if (bf > 1) {
            if (balance_factor(nodes[idx].left) < 0) {
                rotate_left(nodes[idx].left);
            }
            return rotate_right(idx);
        }

        if (bf < -1) {
            if (balance_factor(nodes[idx].right) > 0) {
                rotate_right(nodes[idx].right);
            }
            return rotate_left(idx);
        }

        return idx;
    }

public:
    explicit AVLTREE(size_t reserve_count = 10000000)
        : nodes(nullptr), node_count(0), node_capacity(0), root(0), max_node(0) {
        reserve(reserve_count);
        new (&nodes[0]) Node(T{}); // Index 0 is the null-child sentinel.
        node_count = 1;
        nodes[0].height = 0;
    }

    ~AVLTREE() {
        destroy_storage();
    }

    AVLTREE(const AVLTREE&) = delete;
    AVLTREE& operator=(const AVLTREE&) = delete;

    AVLTREE(AVLTREE&& other) noexcept
        : nodes(other.nodes), node_count(other.node_count),
          node_capacity(other.node_capacity), root(other.root),
          max_node(other.max_node) {
        other.nodes = nullptr;
        other.node_count = 0;
        other.node_capacity = 0;
        other.root = 0;
        other.max_node = 0;
    }

    AVLTREE& operator=(AVLTREE&& other) noexcept {
        if (this != &other) {
            destroy_storage();

            nodes = other.nodes;
            node_count = other.node_count;
            node_capacity = other.node_capacity;
            root = other.root;
            max_node = other.max_node;

            other.nodes = nullptr;
            other.node_count = 0;
            other.node_capacity = 0;
            other.root = 0;
            other.max_node = 0;
        }

        return *this;
    }

    void reserve(size_t count) {
        const size_t requested = count + 1;

        if (requested <= node_capacity) {
            return;
        }

        Node* new_nodes = static_cast<Node*>(::operator new(sizeof(Node) * requested));

        for (size_t i = 0; i < node_count; ++i) {
            new (&new_nodes[i]) Node(std::move(nodes[i]));
            nodes[i].~Node();
        }

        ::operator delete(nodes);
        nodes = new_nodes;
        node_capacity = requested;
    }

    size_t size() const {
        return node_count - 1;
    }

    bool empty() const {
        return root == 0;
    }

    bool contains(const T& value) const {
        int cur = root;

        while (cur != 0) {
            if (value < nodes[cur].value) {
                cur = nodes[cur].left;
            } else if (nodes[cur].value < value) {
                cur = nodes[cur].right;
            } else {
                return true;
            }
        }

        return false;
    }

    bool insert(const T& value) {
        if (root == 0) {
            if (node_count == node_capacity) {
                reserve(node_capacity == 0 ? 2 : node_capacity * 2);
            }

            new (&nodes[node_count]) Node(value);
            root = static_cast<int>(node_count);
            max_node = root;
            ++node_count;
            return true;
        }

        int parent = 0;

        if (nodes[max_node].value < value) {
            // Fast path for strictly increasing data.
            parent = max_node;
            if (node_count == node_capacity) {
                reserve(node_capacity * 2);
            }

            new (&nodes[node_count]) Node(value);
            const int inserted = static_cast<int>(node_count);
            ++node_count;
            nodes[inserted].parent = parent;
            nodes[parent].right = inserted;
            max_node = inserted;
        } else {
            int cur = root;

            while (true) {
                parent = cur;

                if (value < nodes[cur].value) {
                    if (nodes[cur].left == 0) {
                        if (node_count == node_capacity) {
                            reserve(node_capacity * 2);
                        }

                        new (&nodes[node_count]) Node(value);
                        const int inserted = static_cast<int>(node_count);
                        ++node_count;
                        nodes[inserted].parent = parent;
                        nodes[cur].left = inserted;
                        break;
                    }

                    cur = nodes[cur].left;
                } else if (nodes[cur].value < value) {
                    if (nodes[cur].right == 0) {
                        if (node_count == node_capacity) {
                            reserve(node_capacity * 2);
                        }

                        new (&nodes[node_count]) Node(value);
                        const int inserted = static_cast<int>(node_count);
                        ++node_count;
                        nodes[inserted].parent = parent;
                        nodes[cur].right = inserted;

                        if (nodes[max_node].value < value) {
                            max_node = inserted;
                        }

                        break;
                    }

                    cur = nodes[cur].right;
                } else {
                    return false;
                }
            }
        }

        while (parent != 0) {
            const int old_height = nodes[parent].height;
            const int new_subroot = rebalance(parent);

            if (nodes[new_subroot].height == old_height) {
                break;
            }

            parent = nodes[new_subroot].parent;
        }

        return true;
    }

    void print_node(int idx) const {
        if (idx == 0) return;

        int l = nodes[idx].left;
        int r = nodes[idx].right;

        if (l == 0) cout << "NULL";
        else cout << nodes[l].value;

        cout << "<-[" << nodes[idx].value << "]->";

        if (r == 0) cout << "NULL";
        else cout << nodes[r].value;

        cout << "\n";
    }

    void viewBFS() const {
        if (root == 0) {
            cout << "Tree is empty\n";
            return;
        }

        int *queue = new int[node_count];
        int front = 0, rear = 0;

        queue[rear++] = root;

        while (front < rear) {
            int cur = queue[front++];

            print_node(cur);

            if (nodes[cur].left != 0)
                queue[rear++] = nodes[cur].left;

            if (nodes[cur].right != 0)
                queue[rear++] = nodes[cur].right;
        }

        delete[] queue;
    }

};

int main() {
    cout << "Program started\n";

    srand(static_cast<unsigned>(time(0)));

    auto start = high_resolution_clock::now();

    AVLTREE<int> tree;
    int n = 1000000;

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



// int main(){

//     cout << "Program started\n";
// auto start = high_resolution_clock::now();
// AVLTREE<int> tree;

// int arr[] = {
//     50,20,70,10,30,60,80,
//     25,27,26,5,1,2,3,4,
//     90,100,95,85,75,

//     // zig-zag patterns (LR, RL)
//     55,65,63,64,62,61,
//     35,45,43,44,42,41,

//     // increasing blocks (RR rotations)
//     101,102,103,104,105,106,107,108,109,110,

//     // decreasing blocks (LL rotations)
//     200,199,198,197,196,195,194,193,192,191,

//     // mixed middle insertions
//     150,120,130,125,135,123,127,
//     170,160,165,162,168,166,164,

//     // more zig-zag
//     15,18,17,16,19,
//     75,72,74,73,71,

//     // dense cluster (frequent rebalance)
//     300,250,275,260,270,265,268,267,266,
//     350,320,340,330,335,332,338,

//     // tail mix
//     400,380,390,385,395,
//     450,420,430,425,435,
//     500,480,490,485,495
// };
// cout << "I\n";
// for(int x : arr){
//     // cout << x << "-------------------\n";
//     tree.insert(x); //cout << x << "\n"; 
// }   
// // tree.insert(5); tree.insert(10); tree.insert(15);

// tree.viewBFS();
// cout << "End\n";
// // cout << "\n===== DELETION START =====\n";
// // int delArr[] = {
// //     4,   // leaf
// //     5,   // single child
// //     25,  // internal (rotation heavy)
// //     50,  // ROOT deletion
// //     70,  // internal (right heavy)
// //     90,  // deeper subtree
// //     20   // near root rebalance
// // };

// // for(int x : delArr){
// //     cout << "------------------- DELETE " << x << "\n" ;
// //     tree.remove(x);
// // }
// // tree.viewBFS();

// auto end = high_resolution_clock::now();

// auto duration = duration_cast<microseconds>(end - start);

// cout << "Time taken: " << duration.count() << " microseconds\n";
// return 0;
// }
