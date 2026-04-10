
#include <iostream>
#include <GDSLlist.hpp>
// #include <GDSLstack.hpp>
// #include <GDSLqueue>

template<typename D>
std::ostream& operator<<(std::ostream& out, const node<D>& n){
    return out << n.K;
}

using namespace std;
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

// SinglyList Testing ... .
int main() {
    LIST<int> l;

    std::cout << "===== BASIC INSERT =====\n";
    l.insert(10);
    l.insert(20);
    l.insert(30);
    l.view(); std::cout << "\n";

    std::cout << "\n===== INSERT AT POSITION =====\n";
    l.insert(5, 0);     // head
    l.insert(25, 3);    // middle
    l.insert(40, -1);   // end
    l.view(true); std::cout << "\n";

    std::cout << "\n===== SIZE =====\n";
    std::cout << "Size: " << l.size() << "\n";

    std::cout << "\n===== ACCESS =====\n";
    std::cout << "l[0] = " << l[0] << "\n";
    std::cout << "l[2] = " << l[2] << "\n";

    std::cout << "\n===== MODIFY =====\n";
    std::cout << "Old value at index 1: " << l.modify(100, 1) << "\n";
    l.view(); std::cout << "\n";

    std::cout << "\n===== UPDATE =====\n";
    std::cout << "Update 20 -> 200 at index: " << l.update(20, 200) << "\n";
    l.view(true); std::cout << "\n";

    std::cout << "\n===== INDEX & VALUE =====\n";
    std::cout << "Index of 30: " << l.index(30) << "\n";
    std::cout << "Value at index 2: " << l.value(2) << "\n";

    std::cout << "\n===== REMOVE =====\n";
    std::cout << "Removed element: " << l.remove(0) << "\n";
    l.view(); std::cout << "\n";

    std::cout << "\n===== DROP =====\n";
    std::cout << "Dropped index of 200: " << l.drop(200) << "\n";
    l.view(true); std::cout << "\n";

    std::cout << "\n===== REVERSE =====\n";
    l.reverse();
    l.view(); std::cout << "\n";

    std::cout << "\n===== ITERATOR (manual) =====\n";
    for (auto it = l.begin(); it != l.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    std::cout << "\n===== RANGE LOOP =====\n";
    for (auto x : l) {
        std::cout << x << " ";
    }
    std::cout << "\n";

    std::cout << "\n===== COPY TEST =====\n";
    LIST<int> copy = l;
    copy.insert(999);
    std::cout << "Original: ";
    l.view(); std::cout << "\n";
    std::cout << "Copy: ";
    copy.view(true); std::cout << "\n";

    std::cout << "\n===== MOVE TEST =====\n";
    LIST<int> moved = std::move(copy);
    std::cout << "Moved: ";
    moved.view(); std::cout << "\n";

    std::cout << "\n===== ADD (MERGE COPY) =====\n";
    LIST<int> l2;
    l2.insert(1);
    l2.insert(2);
    l.add(l2);

    std::cout << "After adding l2 into l: ";
    l.view(true); std::cout << "\n";

    std::cout << "\n===== DONE =====\n";

    return 0;
}

