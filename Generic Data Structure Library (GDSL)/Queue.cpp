#include <GDSLlist.hpp>

template<typename D>
class QUEUE{
protected:
    LIST<D> Q;
public:
    long int size();
    bool empty();
    bool enqueue(D val);
    D dequeue();
    void view(bool v=true) const;
    D front();
    D rear();
    void clear();
};

template<typename D>
long int QUEUE<D>::size(){ return Q.size(); }

template<typename D>
bool QUEUE<D>::empty(){ return Q.size()==0; }

template<typename D>
bool QUEUE<D>::enqueue(D val){ return Q.insert(val); }

template<typename D>
D QUEUE<D>::dequeue(){
    if(empty()) 
		throw std::runtime_error("Queue is empty");

	return Q.remove(0);
}

template<typename D>
void QUEUE<D>::view(bool v) const{
    long int index = Q.size();
    if(!index) return;
    if(v) std::cout << "Front->";
    std::cout << "[";
    for(long int i=0; i<index; i++){
        std::cout << Q.value(i); if(i<(index-1)) std::cout<<", ";
    }
    std::cout << "]";
    if(v) std::cout << "<-Rear";
}

template<typename D>
void QUEUE<D>::clear(){
    while(Q.size()) Q.remove(Q.size()-1);
}

template<typename D>
D QUEUE<D>::front(){
	if(!Q.size())
		throw std::runtime_error("Queue is empty");
		
    return Q.value(0);
}

template<typename D>
D QUEUE<D>::rear(){
	if(!Q.size())
        throw std::runtime_error("Queue is empty");
		
    return Q.value(-1);
}

template<typename D>
std::ostream& operator<<(std::ostream& out, const QUEUE<D>& Q){  Q.view(false); return out;  }

template<typename D>
std::ostream& operator<<(std::ostream& out, const node<D>& n){
    return out << n.K;
}

#include <iostream>
using namespace std;

// assuming QUEUE + node + LIST already defined

int main() {

    cout << "===== Test 1: QUEUE<int> =====" << endl;
    QUEUE<int> q1;

    q1.enqueue(10);
    q1.enqueue(20);
    q1.enqueue(30);

    q1.view(true);   // SP->[10, 20, 30]
    cout << endl;

    cout << "Dequeue: " << q1.dequeue() << endl;  // 10
    q1.view(true);
    cout << endl << endl;


    cout << "===== Test 2: QUEUE<string> =====" << endl;
    QUEUE<string> q2;

    q2.enqueue("A");
    q2.enqueue("B");
    q2.enqueue("C");

    q2.view(true);   // SP->[A, B, C]
    cout << endl;

    cout << "Dequeue: " << q2.dequeue() << endl;  // A
    q2.view(true);
    cout << endl << endl;


    cout << "===== Test 3: QUEUE<node<int>> =====" << endl;
    QUEUE<node<int>> q3;

    q3.enqueue({100, nullptr});
    q3.enqueue({200, nullptr});
    q3.enqueue({300, nullptr});

    q3.view(true);   // SP->[100, 200, 300]
    cout << endl;

    cout << "Dequeue: " << q3.dequeue().K << endl;  // 100
    q3.view(true);
    cout << endl << endl;


    cout << "===== Test 4: Empty Queue =====" << endl;
    QUEUE<int> q4;

    try {
        q4.dequeue();   // should throw
    } catch(const exception& e) {
        cout << "Exception: " << e.what() << endl;
    }

    return 0;
}

// using namespace std;
// int main(){
//     QUEUE<int> a;
//     a.enqueue(10);
//     a.enqueue(20);
//     a.enqueue(30);
//     a.enqueue(40);
//     a.enqueue(50);
//     a.enqueue(60);
//     a.enqueue(70);
//     a.view();
//     a.dequeue();
//     a.dequeue();
//     a.dequeue();
//     cout<<endl;
//     a.view();
//     return 0;
// }
