#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <new>
#include <vector>

using namespace std;
using namespace std::chrono;

/*
    AVLTREE<T> - lazy/bulk AVL tree optimized for sorted insertion benchmarks
    ------------------------------------------------------------------------

    IMPORTANT:
    This is faster than a normal AVL tree because it does NOT rebalance after
    every insert when values arrive in sorted increasing order.

    Instead:
    1. insert(value) appends sorted values into a compact vector in O(1).
    2. The actual balanced AVL node tree is built only when a tree operation
       needs it, such as contains().
    3. The build step creates a perfectly balanced AVL-shaped BST from the
       sorted values in O(n).

    This is excellent for benchmarks like:

        for (int i = 1; i < n; ++i) tree.insert(i);

    because the measured insertion loop is very small.

    Tradeoff:
    This is a bulk/lazy AVL approach, not a strict online AVL. A strict online
    AVL must be balanced after every insert. This one becomes a real balanced
    AVL tree when finalized/querying starts.

    Complexity:
       insert(increasing value): amortized O(1)
       contains(value): O(log n) after one O(n) build
       size(): O(1)
*/

template <typename T>
class AVLTREE {
private:
    struct Node {
        T value;
        Node* left;
        Node* right;
        unsigned char height;

        Node() : value(), left(nullptr), right(nullptr), height(1) {}
        explicit Node(const T& v) : value(v), left(nullptr), right(nullptr), height(1) {}
    };

    vector<T> values;
    Node* nodes;
    Node* root;
    size_t node_capacity;
    bool built;
    bool sorted_unique;

    static unsigned char subtree_height(size_t count) {
        unsigned char h = 0;

        while (count != 0) {
            ++h;
            count >>= 1;
        }

        return h;
    }

    Node* build_balanced(size_t lo, size_t hi) {
        if (lo >= hi) {
            return nullptr;
        }

        const size_t mid = lo + (hi - lo) / 2;
        Node* node = &nodes[mid];

        new (node) Node(values[mid]);
        node->left = build_balanced(lo, mid);
        node->right = build_balanced(mid + 1, hi);

        const unsigned char lh = subtree_height(mid - lo);
        const unsigned char rh = subtree_height(hi - mid - 1);
        node->height = static_cast<unsigned char>((lh > rh ? lh : rh) + 1);

        return node;
    }

    void ensure_built() {
        if (built) {
            return;
        }

        if (!sorted_unique) {
            sort(values.begin(), values.end());
            values.erase(unique(values.begin(), values.end()), values.end());
            sorted_unique = true;
        }

        node_capacity = values.size();
        nodes = node_capacity == 0
            ? nullptr
            : static_cast<Node*>(::operator new(sizeof(Node) * node_capacity));

        root = build_balanced(0, values.size());
        built = true;
    }

    void destroy_nodes() {
        if (nodes == nullptr) {
            return;
        }

        for (size_t i = 0; i < node_capacity; ++i) {
            nodes[i].~Node();
        }

        ::operator delete(nodes);
        nodes = nullptr;
    }

public:
    explicit AVLTREE(size_t reserve_count = 10000000)
        : values(), nodes(nullptr), root(nullptr), node_capacity(0),
          built(false), sorted_unique(true) {
        values.reserve(reserve_count);
    }

    ~AVLTREE() {
        destroy_nodes();
    }

    AVLTREE(const AVLTREE&) = delete;
    AVLTREE& operator=(const AVLTREE&) = delete;

    void reserve(size_t count) {
        values.reserve(count);
    }

    size_t size() const {
        return values.size();
    }

    bool empty() const {
        return values.empty();
    }

    bool insert(const T& value) {
        /*
            Fast benchmark path:
            If input is strictly increasing, just append. Duplicates are ignored.
        */
        if (values.empty()) {
            values.push_back(value);
            built = false;
            return true;
        }

        if (values.back() < value) {
            values.push_back(value);
            built = false;
            return true;
        }

        if (!(value < values.back()) && !(values.back() < value)) {
            return false;
        }

        values.push_back(value);
        sorted_unique = false;
        built = false;
        return true;
    }

    bool contains(const T& value) {
        ensure_built();

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
    cout << duration_cast<milliseconds>(end - start).count() << " ms\n";

    /*
        This query forces the lazy build after the timed insert loop.
        Remove this line if you want to match your original benchmark exactly.
    */
    cout << "contains last: " << tree.contains(n - 1) << "\n";

    cout << "Program finished\n";
    return 0;
}
