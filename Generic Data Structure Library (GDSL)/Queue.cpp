#include <iostream>
#include <stdexcept>
#include <new>
#include <gdsl_list>

template<typename D>
class QUEUE;

template<typename D>
union FIFO
{
    struct Continuous { friend class QUEUE<D>;
    protected:
        D *Q;
        size_t C, S, f, r;
    public:
        Continuous(size_t size=2)
            : C(size ? size : 2), S(0), f(0), r(0)
        { Q=new D[C]; }
        ~Continuous() { delete[] Q; }

        size_t size();
        bool empty();
        bool enqueue(D val);
        D dequeue();
        D front();
        D rear();
        void view(bool v) const;
        void clear();

        Continuous(const Continuous&);
        Continuous& operator=(const Continuous&);

        Continuous(Continuous&&) noexcept;
        Continuous& operator=(Continuous&&) noexcept;
    } 
    array;

    struct Linked { friend class QUEUE<D>;
    protected:
        ::LIST<D> Q;
    public:
        Linked()=default;

        size_t size();
        bool empty();
        bool enqueue(D val);
        D dequeue();
        D front();
        D rear();
        void view(bool v) const;
        void clear();

        Linked(const Linked&) = default;
        Linked& operator=(const Linked&) = default;

        Linked(Linked&&) noexcept = default;
        Linked& operator=(Linked&&) noexcept = default;
    } 
    list;

    FIFO() {}
    ~FIFO() {}

    FIFO(const FIFO&)=delete;
    FIFO& operator=(const FIFO&)=delete;

    FIFO(FIFO&&)=delete;
    FIFO& operator=(FIFO&&)=delete;
};

template<typename D>
FIFO<D>::Continuous::Continuous(const Continuous& other)
    : C(other.C), S(other.S), f(other.f), r(other.r)
{
    Q=new D[C];
    for(size_t i=0; i < C; ++i) Q[i]=other.Q[i];
}

template<typename D>
typename FIFO<D>::Continuous& 
FIFO<D>::Continuous::operator=(const Continuous& other)
{
    if(this != &other){
        D* temp=new D[other.C];
        for(size_t i=0; i < other.C; ++i) temp[i]=other.Q[i];

        delete[] Q;
        Q=temp; C=other.C; S=other.S; f=other.f; r=other.r;
    }
    return *this;
}

template<typename D>
FIFO<D>::Continuous::Continuous(Continuous&& other) noexcept
    : Q(other.Q), C(other.C), S(other.S), f(other.f), r(other.r)
{
    other.Q=nullptr; other.C=0; other.S=0; other.f=0; other.r=0;
}

template<typename D>
typename FIFO<D>::Continuous& 
FIFO<D>::Continuous::operator=(Continuous&& other) noexcept
{
    if(this != &other){ delete[] Q;
        Q=other.Q;       C=other.C; S=other.S; f=other.f; r=other.r;
        other.Q=nullptr; other.C=0; other.S=0; other.f=0; other.r=0;
    }
    return *this;
}

template<typename D>
size_t FIFO<D>::Continuous::size(){ return S; }

template<typename D>
size_t FIFO<D>::Linked::size(){ return Q.size(); }

template<typename D>
bool FIFO<D>::Continuous::empty(){ return S==0; }

template<typename D>
bool FIFO<D>::Linked::empty(){ return Q.size()==0; }

template<typename D>
bool FIFO<D>::Continuous::enqueue(D val){
    if (S==C)
        throw std::runtime_error("Queue overflow");

    Q[r]=val; r=(r+1)%C; S++;
    return true;
}

template<typename D>
bool FIFO<D>::Linked::enqueue(D val){ return Q.insert(val); }

template<typename D>
D FIFO<D>::Continuous::dequeue(){
    if (empty())
        throw std::runtime_error("Queue is empty");

    D val=Q[f]; f=(f+1)%C; S--;
    return val;
}

template<typename D>
D FIFO<D>::Linked::dequeue(){
    if(empty()) 
        throw std::runtime_error("Queue is empty");

    return Q.remove(0);
}

template<typename D>
D FIFO<D>::Continuous::front(){
    if (empty())
        throw std::runtime_error("Queue is empty");

    return Q[f];
}

template<typename D>
D FIFO<D>::Linked::front(){
	if(empty())
        throw std::runtime_error("Queue is empty");
		
    return Q.value(0);
}

template<typename D>
D FIFO<D>::Continuous::rear(){
    if (empty())
        throw std::runtime_error("Queue is empty");

    return Q[(r+C-1)%C];
}

template<typename D>
D FIFO<D>::Linked::rear(){
	if(empty())
        throw std::runtime_error("Queue is empty");
		
    return Q.value(-1);
}

template<typename D>
void FIFO<D>::Continuous::clear(){ S=f=r=0; }

template<typename D>
void FIFO<D>::Linked::clear(){
    while(Q.size()) Q.remove(0);
}

template<typename D>
void FIFO<D>::Continuous::view(bool v) const {
    if(v) std::cout << "Front->";
    std::cout << "[";
    for (size_t i=0; i<S; i++){
        if(i) std::cout << ", "; std::cout << Q[(f+i)%C];
    }
    std::cout << "]";
    if(v) std::cout << "<-Rear";
}

template<typename D>
void FIFO<D>::Linked::view(bool v) const{
    if(v) std::cout << "Front->";
    bool f=false;
    std::cout << "[";
    for(auto x : Q){
        if(f) std::cout<<", "<<x;  else{ std::cout<<x; f=true; }
    }
    std::cout << "]";
    if(v) std::cout << "<-Rear";
}

template<typename D>
class QUEUE{
protected:
    bool C;
    FIFO<D> Queue;
public:
    QUEUE(size_t size=0);
    ~QUEUE();

    bool resize(size_t size, bool force=false);
    size_t size();
    bool empty();
    bool enqueue(D val);
    D dequeue();
    D front();
    D rear();
    void view(bool v=false) const;
    void clear();

    QUEUE(const QUEUE&);
    QUEUE& operator=(const QUEUE&);

    QUEUE(QUEUE&&) noexcept;
    QUEUE& operator=(QUEUE&&) noexcept;
};

template<typename D>
QUEUE<D>::QUEUE(size_t size)
{
    if(size){
        new (&Queue.array) typename FIFO<D>::Continuous(size);
        C = true;
    }else{
        new (&Queue.list) typename FIFO<D>::Linked();
        C = false;
    }
}

template<typename D>
QUEUE<D>::~QUEUE()
{
    if(C)
        Queue.array.~Continuous();
    else
        Queue.list.~Linked();
}

template<typename D>
QUEUE<D>::QUEUE(const QUEUE& other)
{
    C=other.C;
    if(C)
        new (&Queue.array) typename FIFO<D>::Continuous(other.Queue.array);
    else
        new (&Queue.list) typename FIFO<D>::Linked(other.Queue.list);
}

template<typename D>
QUEUE<D>& QUEUE<D>::operator=(const QUEUE& other)
{
    if(this == &other) return *this;

    if(C)
        Queue.array.~Continuous();
    else
        Queue.list.~Linked();

    C=other.C;
    if(C)
        new (&Queue.array) typename FIFO<D>::Continuous(other.Queue.array);
    else
        new (&Queue.list) typename FIFO<D>::Linked(other.Queue.list);

    return *this;
}

template<typename D>
QUEUE<D>::QUEUE(QUEUE&& other) noexcept
{
    C=other.C;
    if(C)
        new (&Queue.array) typename FIFO<D>::Continuous(std::move(other.Queue.array));
    else
        new (&Queue.list) typename FIFO<D>::Linked(std::move(other.Queue.list));
}

template<typename D>
QUEUE<D>& QUEUE<D>::operator=(QUEUE&& other) noexcept
{
    if(this == &other) return *this;

    if(C)
        Queue.array.~Continuous();
    else
        Queue.list.~Linked();

    C=other.C;
    if(C)
        new (&Queue.array) typename FIFO<D>::Continuous(std::move(other.Queue.array));
    else
        new (&Queue.list) typename FIFO<D>::Linked(std::move(other.Queue.list));

    return *this;
}

template<typename D>
size_t QUEUE<D>::size()
{
    return C? Queue.array.size()
            : Queue.list.size();
}

template<typename D>
bool QUEUE<D>::empty()
{
    return C? Queue.array.empty()
            : Queue.list.empty();
}

template<typename D>
bool QUEUE<D>::enqueue(D val)
{
    return C? Queue.array.enqueue(val)
            : Queue.list.enqueue(val);
}

template<typename D>
D QUEUE<D>::dequeue()
{
    return C? Queue.array.dequeue()
            : Queue.list.dequeue();
}

template<typename D>
D QUEUE<D>::front()
{
    return C? Queue.array.front()
            : Queue.list.front();
}

template<typename D>
D QUEUE<D>::rear()
{
    return C? Queue.array.rear()
            : Queue.list.rear();
}

template<typename D>
void QUEUE<D>::view(bool v) const
{
     C? Queue.array.view(v)
      : Queue.list.view(v);
}

template<typename D>
void QUEUE<D>::clear()
{
     C? Queue.array.clear()
      : Queue.list.clear();
}

template<typename D>
bool QUEUE<D>::resize(size_t size, bool force)
{
    if(!C) return false;
    if(size<Queue.array.S) return false;
    if(size<=Queue.array.C) return true;
    if(!force) return false;

    D *ARR=new D[size];
    for(size_t i=0; i<Queue.array.S; i++)
        ARR[i]=Queue.array.Q[(Queue.array.f+i)%Queue.array.C];

    delete[] Queue.array.Q;
    Queue.array.Q=ARR;  Queue.array.C=size; 
    Queue.array.f=0;    Queue.array.r=Queue.array.S;

    return true;
}

template<typename D>
std::ostream& operator<<(std::ostream& out, const QUEUE<D>& Q){ Q.view(false); return out; }


int main()
{
    std::cout << "==============================\n";
    std::cout << " ARRAY BASED QUEUE TEST\n";
    std::cout << "==============================\n";

    QUEUE<int> A(5);      // Array Queue (capacity = 5)

    std::cout << "Empty : " << std::boolalpha << A.empty() << "\n";

    A.enqueue(10);
    A.enqueue(20);
    A.enqueue(30);
    A.enqueue(40);
    A.enqueue(50);

    std::cout << "Queue : ";
    A.view(true);
    std::cout << '\n';

    std::cout << "Size  : " << A.size() << '\n';
    std::cout << "Front : " << A.front() << '\n';
    std::cout << "Rear  : " << A.rear() << '\n';

    std::cout << "Dequeue : " << A.dequeue() << '\n';

    std::cout << "After Dequeue : ";
    A.view(true);
    std::cout << '\n';

    std::cout << "Resize(10,false) : "
              << A.resize(10,false) << '\n';

    std::cout << "Resize(10,true)  : "
              << A.resize(10,true) << '\n';

    A.enqueue(60);
    A.enqueue(70);
    A.enqueue(80);
    A.enqueue(90);

    std::cout << "After Resize + Enqueue : ";
    A.view(true);
    std::cout << '\n';

    A.clear();

    std::cout << "After Clear : ";
    A.view(true);
    std::cout << '\n';

    std::cout << "Empty : " << A.empty() << "\n\n";


    std::cout << "==============================\n";
    std::cout << " LINKED LIST BASED QUEUE TEST\n";
    std::cout << "==============================\n";

    QUEUE<int> L;     // Linked Queue

    std::cout << "Empty : " << L.empty() << '\n';

    L.enqueue(100);
    L.enqueue(200);
    L.enqueue(300);
    L.enqueue(400);
    L.enqueue(500);

    std::cout << "Queue : ";
    L.view(true);
    std::cout << '\n';

    std::cout << "Size  : " << L.size() << '\n';
    std::cout << "Front : " << L.front() << '\n';
    std::cout << "Rear  : " << L.rear() << '\n';

    std::cout << "Dequeue : " << L.dequeue() << '\n';

    std::cout << "After Dequeue : ";
    L.view(true);
    std::cout << '\n';

    std::cout << "Resize(20,true) : "
              << L.resize(20,true)
              << " (expected false)\n";

    L.clear();

    std::cout << "After Clear : ";
    L.view();
    std::cout << '\n';

    std::cout << "Empty : " << L.empty() << '\n';

    return 0;
}


// template<typename D>
// class QUEUE{
// protected:
//     LIST<D> Q;
// public:
//     long int size();
//     bool empty();
//     bool enqueue(D val);
//     D dequeue();
// 	D front();
//     D rear();
//     void view(bool v=true) const;
// 	void clear();
// };
