#include <iostream>
#include <chrono>
#include <cstdlib>
#include <ctime>

using namespace std::chrono;
using namespace std;

template <typename T>
class AVLTREE {
private:
    struct Node {
        T value;
        Node* left;
        Node* right;
        int height;

        Node(T v) : value(v), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root = nullptr;

    int height(Node* n) {
        return n ? n->height : 0;
    }

    int subH(Node* n) {
        return n ? height(n->left) - height(n->right) : 0;
    }

    int balanceH(Node* l, Node* r) {
        return max(height(l), height(r)) + 1;
    }

    // 🔥 YOUR BALANCE LOGIC (adapted)
    Node* balance(Node* AVL) {
    if (!AVL) return AVL;

    Node *node0, *node1, *node2;
    Node *link0, *link1, *link2, *link3;

    if (subH(AVL) > 1) {   // LEFT HEAVY
        Node* left = AVL->left;
        if (!left) return AVL;

        node2 = AVL;
        link3 = AVL->right;

        if (subH(left) < 0) {   // LR case
            if (!left->right) return AVL;   // ✅ SAFE GUARD

            node0 = left;
            link0 = left->left;

            node1 = left->right;
            link1 = node1->left;
            link2 = node1->right;
        } else {                // LL case
            if (!left->left) return AVL;   // ✅ SAFE GUARD

            node1 = left;
            link2 = left->right;

            node0 = left->left;
            link0 = node0->left;
            link1 = node0->right;
        }
    }
    else if (subH(AVL) < -1) {  // RIGHT HEAVY
        Node* right = AVL->right;
        if (!right) return AVL;

        node0 = AVL;
        link0 = AVL->left;

        if (subH(right) < 0) {   // RR case
            if (!right->right) return AVL;   // ✅ SAFE GUARD

            node1 = right;
            link1 = right->left;

            node2 = right->right;
            link2 = node2->left;
            link3 = node2->right;
        } else {                // RL case
            if (!right->left) return AVL;   // ✅ SAFE GUARD

            node2 = right;
            link3 = right->right;

            node1 = right->left;
            link1 = node1->left;
            link2 = node1->right;
        }
    }
    else {
        return AVL;
    }

    // reconnect
    node1->left = node0;
    node1->right = node2;

    node0->left = link0;
    node0->right = link1;

    node2->left = link2;
    node2->right = link3;

    node0->height = balanceH(node0->left, node0->right);
    node2->height = balanceH(node2->left, node2->right);
    node1->height = balanceH(node1->left, node1->right);

    return node1;
}

    Node* insert(Node* node, T val) {
        if (!node) return new Node(val);

        if (val < node->value)
            node->left = insert(node->left, val);
        else if (val > node->value)
            node->right = insert(node->right, val);
        else
            return node;

        node->height = balanceH(node->left, node->right);

        return balance(node);
    }

    void inorder(Node* node) {
        if (!node) return;
        inorder(node->left);
        cout << node->value << " ";
        inorder(node->right);
    }

public:
    void insert(T val) {
        root = insert(root, val);
    }

    void print() {
        inorder(root);
        cout << endl;
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

    cout << duration_cast<milliseconds>(end - start).count() << " ms\n";

    cout << "Program finished\n";
    return 0;
}