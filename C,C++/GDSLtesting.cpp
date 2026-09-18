
#include <iostream>
#include <gdsl.hpp>
#include <gdsl_array>
#include <gdsl_list>
#include <gdsl_stack>
#include <gdsl_queue>
#include <gdsl_tree>
#include <gdsl_bst>
#include <gdsl_avl>
#include <gdsl_btree>

int main(){ std::cout<<"\nLibrary Compile Successfully\n\n"; }


// using namespace std;

// int main()
// {
//     AVLTREE<int> tree;

//     //              50
//     //            /    \
//     //          30      70
//     //         /  \    /  \
//     //       20   40  60   80
//     //
//     // Insert order creates this BST.
//     int data[] = {50, 30, 70, 20, 40, 60, 80};

//     for(int i=0; i<7; i++) tree.insert(data[i]);

//     cout << "========================================\n";
//     cout << "           VIEW FUNCTIONS\n";
//     cout << "========================================\n";

//     cout << "\nIN:\n";
//     tree.viewIN();

//     cout << "\nR_IN:\n";
//     tree.viewR_IN();

//     cout << "\nPRE:\n";
//     tree.viewPRE();

//     cout << "\nPOST:\n";
//     tree.viewPOST();

//     cout << "\nDFS LR:\n";
//     tree.viewDFS(false);

//     cout << "\nDFS RL:\n";
//     tree.viewDFS(true);

//     cout << "\nBFS LR:\n";
//     tree.viewBFS(false);

//     cout << "\nBFS RL:\n";
//     tree.viewBFS(true);


//     cout << "\n========================================\n";
//     cout << "        RANGE-BASED FOR LOOP\n";
//     cout << "========================================\n";

//     MODE modes[] =
//     {
//         MODE::DFS,
//         MODE::BFS,
//         MODE::DFS_RL,
//         MODE::BFS_RL,
//         MODE::IN,
//         MODE::R_IN,
//         MODE::PRE,
//         MODE::POST,
//     };

//     const char* names[] =
//     {
//         "DFS",
//         "BFS",
//         "DFS_RL",
//         "BFS_RL",
//         "IN",
//         "R_IN",
//         "PRE",
//         "POST",
//     };

//     for(int m = 0; m < 8; ++m)
//     {
//         tree.M = modes[m];

//         cout << "\n" << names[m] << " : ";

//         for(const auto& x : tree)
//             cout << x << ' ';

//         cout << '\n';
//     }


//     cout << "\n========================================\n";
//     cout << "          POSITIVE INDEXING\n";
//     cout << "========================================\n";

//     for(int m = 0; m < 8; ++m)
//     {
//         tree.M = modes[m];

//         cout << "\n" << names[m] << ":\n";

//         for(long int i = 0; i < tree.size(); ++i)
//             cout << "tree[" << i << "] = " << tree[i] << '\n';
//     }


//     cout << "\n========================================\n";
//     cout << "          NEGATIVE INDEXING\n";
//     cout << "========================================\n";

//     for(int m = 0; m < 8; ++m)
//     {
//         tree.M = modes[m];

//         cout << "\n" << names[m] << ":\n";

//         for(long int i = -1; i >= -tree.size(); --i)
//             cout << "tree[" << i << "] = " << tree[i] << '\n';
//     }


//     cout << "\n========================================\n";
//     cout << "          view(MODE)\n";
//     cout << "========================================\n";

//     for(int m = 0; m < 8; ++m)
//     {
//         cout << "\n" << names[m] << ":\n";
//         tree.view(modes[m]);
//     }

//     return 0;
// }


// int main()
// {
//     // ===================== JAGGED ARRAY =====================

//     ARRAY<ARRAY<int>> jaggedArray =
//     {
//         {1, 2},
//         {3, 4, 5, 6},
//         {7},
//         {8, 9, 10},
//         {},
//         {11, 12, 13, 14, 15}
//     };

//     std::cout << "========== JAGGED ARRAY ==========\n";

//     for(size_t i = 0; i < jaggedArray.size(); ++i)
//     {
//         std::cout << "Row " << i << " : ";

//         for(size_t j = 0; j < jaggedArray[i].size(); ++j)
//             std::cout << jaggedArray[i][j] << ' ';

//         std::cout << '\n';
//     }

//     std::cout << "\nRecursive Print:\n";
//     std::cout << jaggedArray << '\n';


//     // ===================== JAGGED LIST =====================

//     LIST<LIST<int>> jaggedList =
//     {
//         {1, 2},
//         {3, 4, 5, 6},
//         {7},
//         {8, 9, 10},
//         {},
//         {11, 12, 13, 14, 15}
//     };

//     std::cout << "\n========== JAGGED LIST ==========\n";

//     size_t row = 0;
//     for(size_t i = 0; i < jaggedList.size(); ++i)
//     {
//         std::cout << "Row " << i << " : ";

//         for(size_t j = 0; j < jaggedList[i].size(); ++j)
//             std::cout << jaggedList[i][j] << ' ';

//         std::cout << '\n';
//     }

//     std::cout << "\nRecursive Print:\n";
//     std::cout << jaggedList << '\n';

//     return 0;
// }


// int main(){
//     LIST<int> L = {5,1,9,3,7,4,8,6,2};

//     std::cout << "Before : " << L << '\n';
//     L.sort();
//     std::cout << "After  : " << L << '\n';

//     LIST<int> A = {};
//     LIST<int> B = {5};
//     LIST<int> C = {2,1};
//     LIST<int> D = {1,2};
//     LIST<int> E = {5,5,5,5};
//     LIST<int> F = {9,8,7,6,5,4,3,2,1};

//     A.sort();
//     B.sort();
//     C.sort();
//     D.sort();
//     E.sort();
//     F.sort();

//     std::cout << A << '\n';
//     std::cout << B << '\n';
//     std::cout << C << '\n';
//     std::cout << D << '\n';
//     std::cout << E << '\n';
//     std::cout << F << '\n';
// }


// int main()
// {
//     ARRAY<ARRAY<int>> mat =
//     {
//         {1, 2, 3},
//         {4, 5, 6},
//         {7, 8, 9}
//     };

//     std::cout << "2D Matrix:\n";

//     for(size_t i = 0; i < mat.size(); ++i)
//     {
//         for(size_t j = 0; j < mat[i].size(); ++j)
//             std::cout << mat[i][j] << ' ';

//         std::cout << '\n';
//     }

//     std::cout << '\n' << mat << "\n\n";


//     // ===================== 3D ARRAY =====================

//     ARRAY<ARRAY<ARRAY<int>>> cube =
//     {
//         {
//             {1, 2},
//             {3, 4}
//         },
//         {
//             {5, 6},
//             {7, 8}
//         }
//     };

//     std::cout << "3D Matrix:\n";

//     for(size_t i = 0; i < cube.size(); ++i)
//     {
//         std::cout << "Layer " << i << ":\n";

//         for(size_t j = 0; j < cube[i].size(); ++j)
//         {
//             for(size_t k = 0; k < cube[i][j].size(); ++k)
//                 std::cout << cube[i][j][k] << ' ';

//             std::cout << '\n';
//         }

//         std::cout << '\n';
//     }

//     std::cout << cube << '\n';

//     return 0;
// }


// int main()
// {
//     std::cout << "========== INITIALIZER LIST ==========\n";

//     ARRAY<int> A = {1,2,3,4,5}; 
//     ARRAY<int> B{1,2,3,4,5};
//     ARRAY<int> C = {1,2,3,4,6};
//     ARRAY<int> D = {1,2,3};
//     ARRAY<int> E = {2,1,3,4,5};
//     ARRAY<int> F = {};

//     std::cout << "A = "; A.view();  std::cout << "\n";
//     std::cout << "B = "; B.view();  std::cout << "\n";
//     std::cout << "C = "; C.view();  std::cout << "\n";
//     std::cout << "D = "; D.view();  std::cout << "\n";
//     std::cout << "E = "; E.view();  std::cout << "\n";
//     std::cout << "F = "; F.view();

//     std::cout << "\n========== SIZE / CAPACITY ==========\n";
//     std::cout << "A : Size = " << A.size()
//               << "  Capacity = " << A.capacity() << '\n';

//     std::cout << "F : Size = " << F.size()
//               << "  Capacity = " << F.capacity() << '\n';

//     std::cout << "\n========== COMPARISON ==========\n";

//     std::cout << "A == B : " << (A == B) << '\n';
//     std::cout << "A != B : " << (A != B) << '\n';

//     std::cout << "A == C : " << (A == C) << '\n';
//     std::cout << "A != C : " << (A != C) << '\n';

//     std::cout << "A < C  : " << (A < C) << '\n';
//     std::cout << "C > A  : " << (C > A) << '\n';

//     std::cout << "D < A  : " << (D < A) << '\n';
//     std::cout << "A > D  : " << (A > D) << '\n';

//     std::cout << "E > A  : " << (E > A) << '\n';
//     std::cout << "A < E  : " << (A < E) << '\n';

//     std::cout << "A <= B : " << (A <= B) << '\n';
//     std::cout << "A >= B : " << (A >= B) << '\n';

//     std::cout << "A <= C : " << (A <= C) << '\n';
//     std::cout << "A >= C : " << (A >= C) << '\n';

//     std::cout << "\n========== INDEX OPERATOR ==========\n";

//     std::cout << "A[0]  = " << A[0] << '\n';
//     std::cout << "A[2]  = " << A[2] << '\n';
//     std::cout << "A[-1] = " << A[-1] << '\n';
//     std::cout << "A[-2] = " << A[-2] << '\n';

//     std::cout << "\n========== FORWARD ITERATOR ==========\n";

//     for(auto it=A.begin(); it!=A.end(); ++it)
//         std::cout << *it << ' ';
//     std::cout << '\n';

//     std::cout << "\n========== RANGE-BASED FOR ==========\n";

//     for(const auto &x : A)
//         std::cout << x << ' ';
//     std::cout << '\n';

//     std::cout << "\n========== REVERSE ITERATOR ==========\n";

//     for(auto it=A.rbegin(); it!=A.rend(); ++it)
//         std::cout << *it << ' ';
    
//     std::cout << "\n==========  ==========\n";

//     ARRAY<int> G = {1,2,3,4};
//     ARRAY<int> H = {1,2,3,4,5};

//     std::cout << "G < H : " << (G < H) << '\n';
//     std::cout << "H > G : " << (H > G) << '\n';

//     ARRAY<int> I = {5};
//     ARRAY<int> J = {5};

//     std::cout << "I == J : " << (I == J) << '\n';

//     ARRAY<int> K = {5};
//     ARRAY<int> L = {4};

//     std::cout << "K > L : " << (K > L) << '\n';
//     std::cout << "K < L : " << (K < L) << '\n';

//     ARRAY<int> M = {};

//     std::cout << "M == F : " << (M == F) << '\n';
//     std::cout << "M <= F : " << (M <= F) << '\n';
//     std::cout << "M >= F : " << (M >= F) << '\n';

//     return 0;
// }



// int main()
// {
//     // ===================== 2D LIST =====================

//     LIST<LIST<int>> mat =
//     {
//         {1, 2, 3},
//         {4, 5, 6},
//         {7, 8, 9}
//     };

//     std::cout << "2D List:\n";

//     for(auto row = mat.begin(); row != mat.end(); ++row)
//     {
//         for(auto col = row->begin(); col != row->end(); ++col)
//             std::cout << *col << ' ';

//         std::cout << '\n';
//     }

//     std::cout << '\n' << mat << "\n\n";


//     // ===================== 3D LIST =====================

//     LIST<LIST<LIST<int>>> cube =
//     {
//         {
//             {1, 2},
//             {3, 4}
//         },
//         {
//             {5, 6},
//             {7, 8}
//         }
//     };

//     std::cout << "3D List:\n";

//     size_t layer = 0;

//     for(auto plane = cube.begin(); plane != cube.end(); ++plane)
//     {
//         std::cout << "Layer " << layer++ << ":\n";

//         for(auto row = plane->begin(); row != plane->end(); ++row)
//         {
//             for(auto col = row->begin(); col != row->end(); ++col)
//                 std::cout << *col << ' ';

//             std::cout << '\n';
//         }

//         std::cout << '\n';
//     }

//     std::cout << cube << '\n';

//     return 0;
// }


// int main()
// {
//     // ===== Initializer List =====
//     LIST<int> A = {1, 2, 3};
//     LIST<int> B = {1, 2, 3};
//     LIST<int> C = {1, 2, 4};
//     LIST<int> D = {1, 2};
//     LIST<int> E = {2, 1, 3};

//     std::cout << "A = "; A.view();  std::cout << "\n";
//     std::cout << "B = "; B.view();  std::cout << "\n";
//     std::cout << "C = "; C.view();  std::cout << "\n";
//     std::cout << "D = "; D.view();  std::cout << "\n";
//     std::cout << "E = "; E.view();  std::cout << "\n";

//     std::cout << "\n===== Equality =====\n";
//     std::cout << "A == B : " << (A == B) << '\n';
//     std::cout << "A != B : " << (A != B) << '\n';
//     std::cout << "A == C : " << (A == C) << '\n';
//     std::cout << "A != C : " << (A != C) << '\n';

//     std::cout << "\n===== Less / Greater =====\n";
//     std::cout << "A < C  : " << (A < C) << '\n';
//     std::cout << "C > A  : " << (C > A) << '\n';

//     std::cout << "D < A  : " << (D < A) << '\n';
//     std::cout << "A > D  : " << (A > D) << '\n';

//     std::cout << "E > A  : " << (E > A) << '\n';
//     std::cout << "A < E  : " << (A < E) << '\n';

//     std::cout << "\n===== Less/Greater Equal =====\n";
//     std::cout << "A <= B : " << (A <= B) << '\n';
//     std::cout << "A >= B : " << (A >= B) << '\n';

//     std::cout << "A <= C : " << (A <= C) << '\n';
//     std::cout << "A >= C : " << (A >= C) << '\n';

//     std::cout << "\n===== Iterator =====\n";
//     std::cout << "A : ";

//     for(auto it = A.begin(); it != A.end(); ++it)
//         std::cout << *it << ' ';

//     std::cout << std::endl << std::endl;

//     LIST<int> F = {1,2,3,4};
//     LIST<int> G = {1,2,3};

//     std::cout << "F < G : " << (F < G) << '\n';
//     std::cout << "F > G : " << (F > G) << '\n';
//     std::cout << "G < F : " << (G < F) << '\n';
//     std::cout << "G > F : " << (G > F) << '\n';

//     return 0;
// }




// template<typename D>
// std::ostream& operator<<(std::ostream& out, const LISTnode<D>& n){
//     return out << n.K;
// }

// #include <iostream>
// #include <stdexcept>

// // assume AVLTREE + MODE already included
// int main() {

//     std::cout << "==============================\n";
//     std::cout << "   BST LIBRARY FINAL TEST\n";
//     std::cout << "==============================\n\n";

//     AVLTREE<int> tree;

//     int arr[] = {10, 5, 20, 3, 7, 15, 30};
//     for(int x : arr)
//         tree.insert(x);
//     std::cout<<tree<<"\n\n";
//     // =========================================================
//     // 1. ITERATOR MULTI OBJECT TEST
//     // =========================================================
//     std::cout << "=== ITERATOR MULTI OBJECT TEST ===\n";

//     auto it1 = tree.begin();
//     auto it2 = tree.begin();

//     std::cout << "it1: ";
//     for(; it1 != tree.end(); ++it1)
//         std::cout << *it1 << " ";

//     std::cout << "\nit2: ";
//     for(; it2 != tree.end(); ++it2)
//         std::cout << *it2 << " ";

//     std::cout << "\n\n";

//     // =========================================================
//     // 2. TRAVERSAL TESTS (ALL MODES)
//     // =========================================================
//     std::cout << "=== TRAVERSAL TESTS ===\n\n";

//     struct TestMode {
//         MODE m;
//         const char* name;
//     } tests[] = {
//         {MODE::IN, "INORDER"},
//         {MODE::PRE, "PREORDER"},
//         {MODE::POST, "POSTORDER"},
//         {MODE::BFS, "BFS"},
//         {MODE::DFS, "DFS"},
//         {MODE::DFS_LR, "DFS_LR"},
//         {MODE::BFS_RL, "BFS_RL"}
//     };

//     for(auto &t : tests) {
//         tree.M = t.m;

//         std::cout << t.name << ":\n";
//         for(auto x : tree)
//             std::cout << x << " ";

//         std::cout << "\n\n";
//     }

//     // =========================================================
//     // 3. SIZE TEST
//     // =========================================================
//     std::cout << "=== SIZE TEST ===\n";
//     std::cout << "Size: " << tree.size() << "\n\n";

//     // =========================================================
//     // 4. INDEX OPERATOR TEST
//     // =========================================================
//     std::cout << "=== INDEX TEST (INORDER) ===\n";
//     tree.M = MODE::IN;

//     for(int i = 0; i < tree.size(); i++)
//         std::cout << "tree[" << i << "] = " << tree[i] << "\n";

//     std::cout << "\n";

//     // negative index
//     std::cout << "Last element tree[-1] = " << tree[-1] << "\n\n";

//     // =========================================================
//     // 5. SEARCH TEST
//     // =========================================================
//     std::cout << "=== SEARCH TEST ===\n";
//     std::cout << "search(15): " << tree.search(15) << "\n";
//     std::cout << "search(100): " << tree.search(100) << "\n\n";

//     // =========================================================
//     // 6. REMOVE TEST
//     // =========================================================
//     std::cout << "=== REMOVE TEST ===\n";
//     tree.remove(20);

//     tree.M = MODE::IN;
//     for(auto x : tree)
//         std::cout << x << " ";

//     std::cout << "\n\n";

//     // =========================================================
//     // 7. VIEW FUNCTION TEST
//     // =========================================================
//     std::cout << "=== VIEW TEST (BFS) ===\n";
//     tree.view(MODE::BFS);

//     std::cout << "\n";

//     std::cout << "=== VIEW TEST (DFS) ===\n";
//     tree.view(MODE::DFS);

//     std::cout << "\n";

//     // =========================================================
//     // 8. CONST TEST
//     // =========================================================
//     std::cout << "=== CONST TEST ===\n";
//     const AVLTREE<int>& cref = tree;

//     std::cout << "cref[0] = " << cref[0] << "\n";
//     std::cout << "cref[-1] = " << cref[-1] << "\n\n";

//     // =========================================================
//     // 9. EXCEPTION TEST
//     // =========================================================
//     std::cout << "=== EXCEPTION TEST ===\n";

//     try {
//         std::cout << tree[100] << "\n";
//     }
//     catch(const std::exception& e) {
//         std::cout << "Caught: " << e.what() << "\n";
//     }

//     std::cout << "\n=== ALL TESTS COMPLETE ===\n";

//     return 0;
// }

// using namespace std;
// int main() {

//     cout << "===== Test 1: QUEUE<int> =====" << endl;
//     QUEUE<int> q1;

//     q1.enqueue(10);
//     q1.enqueue(20);
//     q1.enqueue(30);

//     q1.view(true);   // SP->[10, 20, 30]
//     cout << endl;

//     cout << "Dequeue: " << q1.dequeue() << endl;  // 10
//     q1.view(true);
//     cout << endl << endl;


//     cout << "===== Test 2: QUEUE<string> =====" << endl;
//     QUEUE<string> q2;

//     q2.enqueue("A");
//     q2.enqueue("B");
//     q2.enqueue("C");

//     q2.view(true);   // SP->[A, B, C]
//     cout << endl;

//     cout << "Dequeue: " << q2.dequeue() << endl;  // A
//     q2.view(true);
//     cout << endl << endl;


//     cout << "===== Test 3: QUEUE<node<int>> =====" << endl;
//     QUEUE<node<int>> q3;

//     q3.enqueue({100, nullptr});
//     q3.enqueue({200, nullptr});
//     q3.enqueue({300, nullptr});

//     q3.view(true);   // SP->[100, 200, 300]
//     cout << endl;

//     cout << "Dequeue: " << q3.dequeue().K << endl;  // 100
//     q3.view(true);
//     cout << endl << endl;


//     cout << "===== Test 4: Empty Queue =====" << endl;
//     QUEUE<int> q4;

//     try {
//         q4.dequeue();   // should throw
//     } catch(const exception& e) {
//         cout << "Exception: " << e.what() << endl;
//     }

//     return 0;
// }

// using namespace std;
// int main() {

//     cout << "===== Test 1: STACK<int> =====" << endl;
//     STACK<int> s1;

//     s1.push(10);
//     s1.push(20);
//     s1.push(30);

//     s1.view(true);   // expected: SP->[10, 20, 30]
//     cout << endl;

//     cout << "Pop: " << s1.pop() << endl;  // 30
//     s1.view(true);
//     cout << endl << endl;


//     cout << "===== Test 2: STACK<string> =====" << endl;
//     STACK<string> s2;

//     s2.push("A");
//     s2.push("B");
//     s2.push("C");

//     s2.view(true);   // SP->[A, B, C]
//     cout << endl;

//     cout << "Pop: " << s2.pop() << endl;  // C
//     s2.view(true);
//     cout << endl << endl;


//     cout << "===== Test 3: STACK<node<int>> =====" << endl;
//     STACK<node<int>> s3;

//     s3.push({100, nullptr});
//     s3.push({200, nullptr});
//     s3.push({300, nullptr});

//     s3.view(true);   // SP->[100, 200, 300]
//     cout << endl;

//     cout << "Pop: " << s3.pop().K << endl;  // 300
//     s3.view(true);
//     cout << endl << endl;


//     cout << "===== Test 4: Empty Stack =====" << endl;
//     STACK<int> s4;

//     try {
//         s4.pop();   // should throw
//     } catch(const exception& e) {
//         cout << "Exception: " << e.what() << endl;
//     }

//     return 0;
// }

// template<typename D>
// D fun(D n){
//     return false;
// }

// #include <type_traits>
// #include <string>

// template<typename T>
// constexpr bool is_basic_type() {
//     return 
//         std::is_arithmetic<T>::value ||     // int, float, double, char, bool, signed, unsigned, long...
//         std::is_same<T, std::string>::value; // string
// }

// using namespace std;
// int main() {
//     std::cout << is_basic_type<int>() << std::endl;          // 1
//     std::cout << is_basic_type<long>() << std::endl;         // 1
//     std::cout << is_basic_type<unsigned int>() << std::endl; // 1
//     std::cout << is_basic_type<double>() << std::endl;       // 1
//     std::cout << is_basic_type<char>() << std::endl;         // 1
//     std::cout << is_basic_type<std::string>() << std::endl;  // 1

//     std::cout << is_basic_type<node<int>>() << std::endl;    // 0 ❌
// }

// // SinglyList Testing ... .
// int main() {
//     LIST<int> l;

//     std::cout << "===== BASIC INSERT =====\n";
//     l.insert(10);
//     l.insert(20);
//     l.insert(30);
//     l.view(); std::cout << "\n";

//     std::cout << "\n===== INSERT AT POSITION =====\n";
//     l.insert(5, 0);     // head
//     l.insert(25, 3);    // middle
//     l.insert(40, -1);   // end
//     l.view(false); std::cout << "\n";

//     std::cout << "\n===== SIZE =====\n";
//     std::cout << "Size: " << l.size() << "\n";

//     std::cout << "\n===== ACCESS =====\n";
//     std::cout << "l[0] = " << l[0] << "\n";
//     std::cout << "l[2] = " << l[2] << "\n";

//     std::cout << "\n===== MODIFY =====\n";
//     std::cout << "Old value at index 1: " << l.modify(100, 1) << "\n";
//     l.view(); std::cout << "\n";

//     std::cout << "\n===== UPDATE =====\n";
//     std::cout << "Update 20 -> 200 at index: " << l.update(20, 200) << "\n";
//     l.view(); std::cout << "\n";

//     std::cout << "\n===== INDEX & VALUE =====\n";
//     std::cout << "Index of 30: " << l.index(30) << "\n";
//     std::cout << "Value at index 2: " << l.value(2) << "\n";

//     std::cout << "\n===== REMOVE =====\n";
//     std::cout << "Removed element: " << l.remove(0) << "\n";
//     l.view(); std::cout << "\n";

//     std::cout << "\n===== DROP =====\n";
//     std::cout << "Dropped index of 200: " << l.drop(200) << "\n";
//     l.view(false); std::cout << "\n";

//     std::cout << "\n===== REVERSE =====\n";
//     l.reverse();
//     l.view(); std::cout << "\n";

//     std::cout << "\n===== ITERATOR (manual) =====\n";
//     for (auto it = l.begin(); it != l.end(); ++it) {
//         std::cout << *it << " ";
//     }
//     std::cout << "\n";

//     std::cout << "\n===== RANGE LOOP =====\n";
//     for (auto x : l) {
//         std::cout << x << " ";
//     }
//     std::cout << "\n";

//     std::cout << "\n===== COPY TEST =====\n";
//     LIST<int> copy = l;
//     copy.insert(999);
//     std::cout << "Original: ";
//     l.view(); std::cout << "\n";
//     std::cout << "Copy: ";
//     copy.view(); std::cout << "\n";

//     std::cout << "\n===== MOVE TEST =====\n";
//     LIST<int> moved = std::move(copy);
//     std::cout << "Moved: ";
//     moved.view(); std::cout << "\n";

//     std::cout << "\n===== ADD (MERGE COPY) =====\n";
//     LIST<int> l2;
//     l2.insert(1);
//     l2.insert(2);
//     l.add(l2);

//     std::cout << "After adding l2 into l: ";
//     l.view(false); std::cout << "\n";

//     std::cout << "\n===== DONE =====\n";

//     return 0;
// }

