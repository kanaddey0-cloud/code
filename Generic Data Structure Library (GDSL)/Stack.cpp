#include<GDSLlist.hpp>
#include <string>

template<typename D>
class STACK{
protected:
    LIST<D> S;
    bool BDT;
public:
    STACK();
    long int size();
    bool empty();
    bool push(D val);
    void view(bool v);
    D pop();
};

template<typename D>
STACK<D>::STACK(){}

template<typename D>
long int STACK<D>::size(){ return S.size(); }

template<typename D>
bool STACK<D>::empty(){ return size()==0; }

template<typename D>
bool STACK<D>::push(D val){ return S.insert(val); }

template<typename D>
D STACK<D>::pop(){
    long int index=size();
    if(!index) throw std::runtime_error("Stack is empty");
    return S.remove(--index);
}

template<typename D>
void STACK<D>::view(bool v){
    long int index = size();
    if(!index) return;
    if(v) std::cout << "SP->";
    std::cout << "[";
    for(int i=0; i<index; i++){
        std::cout << S.value(i); if(i<(index-1)) std::cout<<", ";
    }
    std::cout << "]";
}

template<typename D>
std::ostream& operator<<(std::ostream& out, const node<D>& n){
    return out << n.K;
}

#include <iostream>
using namespace std;

int main() {

    cout << "===== Test 1: STACK<int> =====" << endl;
    STACK<int> s1;

    s1.push(10);
    s1.push(20);
    s1.push(30);

    s1.view(true);   // expected: SP->[10, 20, 30]
    cout << endl;

    cout << "Pop: " << s1.pop() << endl;  // 30
    s1.view(true);
    cout << endl << endl;


    cout << "===== Test 2: STACK<string> =====" << endl;
    STACK<string> s2;

    s2.push("A");
    s2.push("B");
    s2.push("C");

    s2.view(true);   // SP->[A, B, C]
    cout << endl;

    cout << "Pop: " << s2.pop() << endl;  // C
    s2.view(true);
    cout << endl << endl;


    cout << "===== Test 3: STACK<node<int>> =====" << endl;
    STACK<node<int>> s3;

    s3.push({100, nullptr});
    s3.push({200, nullptr});
    s3.push({300, nullptr});

    s3.view(true);   // SP->[100, 200, 300]
    cout << endl;

    cout << "Pop: " << s3.pop().K << endl;  // 300
    s3.view(true);
    cout << endl << endl;


    cout << "===== Test 4: Empty Stack =====" << endl;
    STACK<int> s4;

    try {
        s4.pop();   // should throw
    } catch(const exception& e) {
        cout << "Exception: " << e.what() << endl;
    }

    return 0;
}

// int main() {
//     STACK<node<int>> a;

//     a.push({10, nullptr});
//     a.push({20, nullptr});
//     a.push({30, nullptr});
//     a.push({40, nullptr});
//     a.push({50, nullptr});
//     a.push({60, nullptr});
//     a.push({70, nullptr});

//     a.view();

//     a.pop();
//     a.pop();
//     a.pop();

//     cout << endl;
//     a.view();

//     return 0;
// }
