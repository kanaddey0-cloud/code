#include <iostream>
#include <stdexcept>

template<typename D>
struct LISTnode{ D K; LISTnode<D> *P; }; 


template<typename D>
class LISTiterator { 
    LISTnode<D>* ptr; 
public:
    LISTiterator(LISTnode<D>* p = nullptr);
	
    D& operator*();
    const D& operator*() const;
	
    LISTiterator& operator++() noexcept;
    LISTiterator operator++(int) noexcept;
	
    bool operator!=(const LISTiterator& other) const noexcept;
    bool operator==(const LISTiterator& other) const noexcept;
    bool operator<(const LISTiterator<D>& other) const noexcept;
    bool operator<=(const LISTiterator<D>& other) const noexcept;
    bool operator>(const LISTiterator<D>& other) const noexcept;
    bool operator>=(const LISTiterator<D>& other) const noexcept;
	
    D* operator->();
    const D* operator->() const;
};

template<typename D>
LISTiterator<D>::LISTiterator(LISTnode<D>* p) : ptr(p) {}

template<typename D>
D& LISTiterator<D>::operator*(){
    if(!ptr) throw std::runtime_error("Null LISTiterator");
    return ptr->K;
}

template<typename D>
const D& LISTiterator<D>::operator*() const{
    if(!ptr) throw std::runtime_error("Null LISTiterator");
    return ptr->K;
}

template<typename D>
LISTiterator<D>& LISTiterator<D>::operator++() noexcept{
    if(ptr) ptr = ptr->P;
    return *this;
}

template<typename D>
LISTiterator<D> LISTiterator<D>::operator++(int) noexcept{
    LISTiterator<D> temp = *this; 
    ++(*this);
    return temp;
}

template<typename D>
bool LISTiterator<D>::operator!=(const LISTiterator<D>& other) const noexcept{ return ptr != other.ptr; }

template<typename D>
bool LISTiterator<D>::operator==(const LISTiterator<D>& other) const noexcept{ return ptr == other.ptr; }

template<typename D>
bool LISTiterator<D>::operator<(const LISTiterator<D>& other) const noexcept{ return ptr < other.ptr; }

template<typename D>
bool LISTiterator<D>::operator>(const LISTiterator<D>& other) const noexcept{ return other < *this; }

template<typename D>
bool LISTiterator<D>::operator<=(const LISTiterator<D>& other) const noexcept{ return !(*this > other); }

template<typename D>
bool LISTiterator<D>::operator>=(const LISTiterator<D>& other) const noexcept{ return !(*this < other); }

template<typename D>
D* LISTiterator<D>::operator->(){ 
    if(!ptr) throw std::runtime_error("Null LISTiterator");
    return &(ptr->K); 
}

template<typename D>
const D* LISTiterator<D>::operator->() const{ 
    if(!ptr) throw std::runtime_error("Null LISTiterator");
    return &(ptr->K); 
}


template<typename D>
class LIST{
protected:
    size_t elem; 
    LISTnode<D>* H, *T;
	
    LISTnode<D>* pointer(std::ptrdiff_t index) const;
    void rotate(LISTnode<D>*& head, LISTnode<D>*& tail);
    size_t clear(LISTnode<D>*& p);
    size_t clearupto(LISTnode<D>*& head, LISTnode<D>*& tail);

    LISTnode<D>* mergeSort(LISTnode<D>* head);
    LISTnode<D>* merge(LISTnode<D>* left, LISTnode<D>* right);
    LISTnode<D>* middle(LISTnode<D>* head);

public:
    LIST(std::initializer_list<D> init);
    LIST();
    LIST(const LIST<D>& other);
    LIST(LIST<D>&& other) noexcept;
    ~LIST();

    size_t size() const { return elem; }
    bool insert(D val, std::ptrdiff_t index = -1);
    size_t drop(D val);
    D remove(std::ptrdiff_t index);
    size_t update(D prev, D curr, bool in = false);
    D modify(D curr, std::ptrdiff_t index);
    bool add(const LIST<D>& next);
    const D& value(std::ptrdiff_t index) const;
    size_t index(D value) const;
    void reverse();
    void view(bool v = false) const;
    void sort();

    D& operator[](const std::ptrdiff_t index);
    const D& operator[](const std::ptrdiff_t index) const;
    LIST<D>& operator=(const LIST<D>& other);
    LIST<D>& operator=(LIST<D>&& other) noexcept;

    bool operator==(const LIST<D>& other) const noexcept;
    bool operator!=(const LIST<D>& other) const noexcept;
    bool operator<(const LIST<D>& other) const noexcept;
    bool operator<=(const LIST<D>& other) const noexcept;
    bool operator>(const LIST<D>& other) const noexcept;
    bool operator>=(const LIST<D>& other) const noexcept;

    LISTiterator<D> begin() noexcept;
    LISTiterator<D> end() noexcept;
    LISTiterator<D> begin() const noexcept;
    LISTiterator<D> end() const noexcept;
};

template<typename D>
LIST<D>::LIST(std::initializer_list<D> init) : LIST<D>()
{
    for(const D& v : init) insert(v);
}

template<typename D>
LIST<D>::LIST(){ H=T=nullptr; elem=0; }

template<typename D>
LIST<D>::LIST(LIST<D>&& other) noexcept :H(other.H), T(other.T), elem(other.elem) {
    other.H = other.T = nullptr;
    other.elem = 0;
}

template<typename D>
LIST<D>::LIST(const LIST<D>& other):LIST<D>(){
    LISTnode<D>* iter = other.H;
    while(iter){
        insert(iter->K); iter = iter->P;
    }
}

template<typename D>
LIST<D>::~LIST(){
    clear(H);
    T = nullptr; elem = 0;
}

template<typename D>
LIST<D>& LIST<D>::operator=(LIST<D>&& other) noexcept{
    if(this != &other){
        clear(H);
        H = other.H; T = other.T;
        elem = other.elem;

        other.H = other.T = nullptr;
        other.elem = 0;
    }
    return *this;
}

template<typename D>
LIST<D>& LIST<D>::operator=(const LIST<D>& other){
    if(this != &other){
        clear(H);
        H=T=nullptr; elem=0;
        
        LISTnode<D>* iter=other.H;
        while(iter){
            insert(iter->K); iter=iter->P;
        }
    }
    return *this;
}

template<typename D>
bool LIST<D>::operator==(const LIST<D>& other) const noexcept
{
    if(elem != other.elem) return false;
    LISTnode<D>* a = H, *b = other.H;

    while(a){
        if(a->K != b->K) return false;
        a=a->P; b=b->P;
    }
    return true;
}

template<typename D>
bool LIST<D>::operator!=(const LIST<D>& other) const noexcept{ return !(*this == other); }

template<typename D>
bool LIST<D>::operator<(const LIST<D>& other) const noexcept
{
    LISTnode<D>* a = H, *b = other.H;
    while(a && b)
    {
        if(a->K < b->K) return true;
        if(a->K > b->K) return false;

        a=a->P; b=b->P;
    }
    return elem < other.elem;
}

template<typename D>
bool LIST<D>::operator>(const LIST<D>& other) const noexcept{ return other < *this; }

template<typename D>
bool LIST<D>::operator<=(const LIST<D>& other) const noexcept{ return !(*this > other); }

template<typename D>
bool LIST<D>::operator>=(const LIST<D>& other) const noexcept{ return !(*this < other); }

template<typename D>
bool LIST<D>::add(const LIST<D>& next){
    if(this == &next) return false;
    if(!next.H) return false;
    LISTnode<D>* tmp=next.H;
    while(tmp){
        insert(tmp->K); tmp=tmp->P;
    }
    return true;
}

template<typename D>
size_t LIST<D>::clear(LISTnode<D>*& p){
    LISTnode<D>* tmp; size_t count=0;
    while(p){ 
        tmp=p; p=p->P; 
        delete tmp; count++;
    }
    return count;
}

template<typename D>
size_t LIST<D>::clearupto(LISTnode<D>*& head, LISTnode<D>*& tail){
    if(!head) return 0;
    LISTnode<D>* p=head->P, *tmp; size_t count=0;
    while(p && p!=tail){ 
        tmp=p; p=p->P; 
        delete tmp; count++;
    }
    if(!p){ head->P=nullptr; return count; }
    if(tail && p==tail){
        tail=tail->P; 
        delete p; count++;
    }
    if(tail){ head->P=tail;  
    }else{ 
        tail=head; tail->P=head->P=nullptr; 
    }
    return count;
}

template<typename D>
D& LIST<D>::operator[](const std::ptrdiff_t index){
    if(!H || elem==0) throw std::runtime_error("List is empty");

    LISTnode<D>* ptr=pointer(index);  
    if(!ptr) throw std::out_of_range("Index out of bounds");
    return ptr->K;                    
}

template<typename D>
const D& LIST<D>::operator[](const std::ptrdiff_t index) const{
    if(!H || elem==0) throw std::runtime_error("List is empty");

    const LISTnode<D>* ptr = pointer(index);   
    if(!ptr) throw std::out_of_range("Index out of bounds");
    return ptr->K;                    
}

template<typename D>
size_t LIST<D>::update(D prev, D curr, bool in){
    LISTnode<D> *iter=H; size_t index=0;
    while(iter){
        if(iter->K==prev){
            iter->K=curr;
            return index;
        }
        iter=iter->P; index++;
    }
    if(in){ 
        insert(curr); return elem-1; 
    } return -1;
}

template<typename D>
D LIST<D>::modify(D curr, std::ptrdiff_t index){
    LISTnode<D>* point=pointer(index);
    if(point){
        D tmp=point->K; point->K=curr;
        return tmp;
    } 
    throw std::out_of_range("Index out of bounds");
}

template<typename D>
LISTnode<D>* LIST<D>::pointer(std::ptrdiff_t index) const{
    if(index<0) index=static_cast<std::ptrdiff_t>(elem)+index;
    if(index>=static_cast<std::ptrdiff_t>(elem) || index<0) return nullptr;
    LISTnode<D> *iter=H;
    for(std::ptrdiff_t i=0; i<index; i++) iter=iter->P;
    return iter;
}

template<typename D>
size_t LIST<D>::index(D value) const{
    LISTnode<D> *iter=H; size_t index=0;
    while(iter){
        if(iter->K==value) return index;
        iter=iter->P; index++;
    } return -1;
}

template<typename D>
const D& LIST<D>::value(std::ptrdiff_t index) const{
    if(index<0) index=static_cast<std::ptrdiff_t>(elem)+index;
    if(index>=static_cast<std::ptrdiff_t>(elem) || index<0) 
        throw std::out_of_range("Index out of bounds");
    LISTnode<D> *iter=H;
    for(std::ptrdiff_t i=0; i<index; i++) iter=iter->P;
    return iter->K;
}

template<typename D>
D LIST<D>::remove(std::ptrdiff_t index){
    if(!elem) throw std::runtime_error("List is empty"); 
    if(index<0) index=static_cast<std::ptrdiff_t>(elem)+index;
    if(index>=static_cast<std::ptrdiff_t>(elem) || index<0) 
        throw std::out_of_range("Index out of bounds");

    LISTnode<D> *iter=H; D K;
    if(index==0){ K=iter->K;
        H=H->P; delete iter; elem--; 
        if(!H) T=nullptr; return K; 
    }
    for(std::ptrdiff_t i=1; i<index; i++){ iter=iter->P; }
    LISTnode<D> *tmp=iter->P; 
    iter->P=tmp->P;
    if(T==tmp) T=iter;
    K=tmp->K; delete tmp; elem--; return K;
}

template<typename D>
size_t LIST<D>::drop(D val){
    if(H==nullptr) return -1; 
    LISTnode<D> *iter=H;
    if(H->K==val){ 
        H=H->P; delete iter; elem--; 
        if(!H) T=nullptr; return 0; 
    }
    size_t index=1;
    while(iter->P){
        if(iter->P->K==val){
            LISTnode<D> *tmp=iter->P; iter->P=tmp->P;
            if(tmp==T) T=iter;
            delete tmp; elem--; return index;
        }
        iter=iter->P; index++;
    }
    return -1; 
}

template<typename D>
bool LIST<D>::insert(D val, std::ptrdiff_t index){
    if(H==nullptr && index!=-1 && index!=0) return false;
    if(H==nullptr){
        H=T=new LISTnode<D>{val, nullptr}; elem++;
        return true;
    }
    if(index==-1 || index==static_cast<std::ptrdiff_t>(elem)){
        T->P=new LISTnode<D>{val, nullptr}; T=T->P; elem++;    
        return true;    
    }
    if(index<0) index=static_cast<std::ptrdiff_t>(elem)+index;
    if(index<0 || index>static_cast<std::ptrdiff_t>(elem)) return false;
    if(index==0){
        LISTnode<D> *tmp=new LISTnode<D>{val, H};
        H=tmp; elem++;
        return true;
    }
    LISTnode<D> *iter=H; std::ptrdiff_t i;
    for(i=1; i<index; i++) iter=iter->P;
    LISTnode<D> *tmp=new LISTnode<D>{val, iter->P};
    iter->P=tmp; elem++;
    return true;
}

template<typename D>
void LIST<D>::view(bool v) const{
    if(!H)
        if(v) std::cout<<"Head->NULL<-Tail";
        else std::cout<<"NULL";
    else{
        LISTnode<D> *iter=H;
        if(v) std::cout<<"Head->";
        bool f=false;
        while(iter){
            if(f) std::cout<<"->["<<iter->K<<"]";  else{ std::cout<<"["<<iter->K<<"]"; f=true; }
            iter=iter->P;
        }
        if(v) std::cout<<"<-Tail";
    }
}

template<typename D>
void LIST<D>::rotate(LISTnode<D>*& head, LISTnode<D>*& tail){
    if(!head || !head->P) return;
    LISTnode<D>* pA = nullptr, *pB = head, *pC = nullptr;
    while(pB){
        pC=pB->P;
        pB->P=pA;
        pA=pB; pB=pC;
    }
    tail=head; head=pA;
    return;
}

template<typename D>
void LIST<D>::reverse(){ rotate(H,T); }

template<typename D>
void LIST<D>::sort()  // Marge Sort
{
    if(elem < 2) return;

    H = mergeSort(H);
    T = H;
    while(T->P) T = T->P;
}

template<typename D>
LISTnode<D>* LIST<D>::middle(LISTnode<D>* head)
{
    if(!head) return nullptr;

    LISTnode<D>* slow = head, *fast = head->P;
    while(fast && fast->P)
    {
        slow = slow->P; fast = fast->P->P;
    }
    return slow;
}

template<typename D>
LISTnode<D>* LIST<D>::mergeSort(LISTnode<D>* head)
{
    if(!head || !head->P) return head;

    LISTnode<D>* mid = middle(head), *right = mid->P;
    mid->P = nullptr;

    LISTnode<D>* left = mergeSort(head);
    right = mergeSort(right);

    return merge(left, right);
}

template<typename D>
LISTnode<D>* LIST<D>::merge(LISTnode<D>* left, LISTnode<D>* right)
{
    if(!left) return right;
    if(!right) return left;

    if(left->K <= right->K)
    {
        left->P = merge(left->P, right);
        return left;
    }

    right->P = merge(left, right->P);
    return right;
}

template<typename D>
LISTiterator<D> LIST<D>::begin() noexcept{ return LISTiterator<D>(H); }

template<typename D>
LISTiterator<D> LIST<D>::end() noexcept{ return LISTiterator<D>(nullptr); }

template<typename D>
LISTiterator<D> LIST<D>::begin() const noexcept{ return LISTiterator<D>(H); }

template<typename D>
LISTiterator<D> LIST<D>::end() const noexcept{ return LISTiterator<D>(nullptr); }

template<typename D>
std::ostream& operator<<(std::ostream& out, const LIST<D>& l){ l.view(false); return out; }


int main(){
    LIST<int> L = {5,1,9,3,7,4,8,6,2};

    std::cout << "Before : " << L << '\n';
    L.sort();
    std::cout << "After  : " << L << '\n';

    LIST<int> A = {};
    LIST<int> B = {5};
    LIST<int> C = {2,1};
    LIST<int> D = {1,2};
    LIST<int> E = {5,5,5,5};
    LIST<int> F = {9,8,7,6,5,4,3,2,1};

    A.sort();
    B.sort();
    C.sort();
    D.sort();
    E.sort();
    F.sort();

    std::cout << A << '\n';
    std::cout << B << '\n';
    std::cout << C << '\n';
    std::cout << D << '\n';
    std::cout << E << '\n';
    std::cout << F << '\n';
}


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

//     std::cout << "A = "; A.view();
//     std::cout << "B = "; B.view();
//     std::cout << "C = "; C.view();
//     std::cout << "D = "; D.view();
//     std::cout << "E = "; E.view();

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


// int main() {
//     LIST<int> list;

//     std::cout << "=== INSERT TEST ===\n";
//     list.insert(10);
//     list.insert(20);
//     list.insert(30);
//     list.insert(40);
//     list.insert(50);
//     list.insert(60);
// int arr[10];
//     // cout<<list;
//     // std::cout << list <<"\n";
//     list.view(true);
//     std::cout << list[-1] <<"\n";

//     std::cout << "=== INDEX TEST (+ve) ===\n";
//     std::cout << "list[0] = " << list[0] << "\n";
//     std::cout << "list[2] = " << list[2] << "\n";
//     std::cout << "list[4] = " << list[4] << "\n\n";

//     std::cout << "=== INDEX TEST (-ve) ===\n";
//     std::cout << "list[-1] = " << list[-1] << "\n";
//     std::cout << "list[-2] = " << list[-2] << "\n";
//     std::cout << "list[-5] = " << list[-5] << "\n\n";

//     std::cout << "=== MODIFY TEST ===\n";
//     list.modify(999, 2);
//     std::cout << "After modify index 2 → ";
//     list.view();
//     std::cout << "\n\n";

//     std::cout << "=== UPDATE TEST ===\n";
//     int pos = list.update(40, 777);
//     std::cout << "Updated position: " << pos << "\n";
//     list.view();
//     std::cout << "\n\n";

//     std::cout << "=== DROP TEST ===\n";
//     int d = list.drop(20);
//     std::cout << "Dropped index: " << d << "\n";
//     list.view();
//     std::cout << "\n\n";

//     std::cout << "=== REMOVE TEST ===\n";
//     int removed = list.remove(0);
//     std::cout << "Removed value: " << removed << "\n";
//     list.view();
//     std::cout << "\n\n";

//     std::cout << "=== REVERSE TEST ===\n";
//     list.reverse();
//     list.view(true);
//     std::cout << "\n\n";

//     std::cout << "=== ITERATOR TEST ===\n";
//     for(auto it = list.begin(); it != list.end(); ++it) {
//         std::cout << *it << " ";
//     }
//     std::cout << "\n\n";

//     std::cout << "=== CONST RANGE FOR STYLE ===\n";
//     for(const auto x : list) {
//         std::cout << x << " ";
//     }
//     std::cout << "\n\n";

//     std::cout << "=== OUT OF BOUND TEST ===\n";
//     try {
//         std::cout << list[100];
//     } catch(const std::exception &e) {
//         std::cout << "Exception: " << e.what() << "\n";
//     }

//     return 0;
// }

// int main() {
    
//     LIST<int> list2;

//     // Fill list2
//     list2.insert(10);
//     list2.insert(20);
//     list2.insert(30);

//     // cout << "Initial list2: ";
//     list2.view(true); cout<<"\n";
//     LIST<int> list1(list2);
//     list2.view(true);
//     cout<<list1[0];
//     list1[1]=22;
//     cout<<list1[1];

//     // // -----------------------------
//     // // ✅ TEST 1: add() (COPY)
//     // // -----------------------------
//     // cout << "\n--- Testing add() (copy) ---\n";

//     // list1.add(list2);

//     // cout << "list1 after add: ";
//     // list1.view();   // [10, 20, 30]

//     // cout << "list2 after add: ";
//     // list2.view();   // should remain SAME

//     // // Modify list1 to prove it's independent
//     // list1.insert(40);

//     // cout << "list1 after insert 40: ";
//     // list1.view();   // [10,20,30,40]

//     // cout << "list2 still unchanged: ";
//     // list2.view();   // [10,20,30]

//     return 0;
// }

// #include <string>
// using namespace std;

// int main(){
//     LIST<int> l;

//     l.insert(10);
//     l.insert(20);
//     l.insert(30);

//     // 🔥 Range-based loop
//     for (auto x : l) {
//         cout << x << " ";
//     }
//     return 0;
// }

// // ---------- TEST FUNCTION ----------
// template<typename T>
// void testList(string name) {
//     cout << "\n============================\n";
//     cout << "Testing LIST<" << name << ">\n";
//     cout << "============================\n";

//     LIST<T> l;

//     try {
//         cout << "\n--- INSERT ---\n";
//         l.insert((T)10);
//         l.insert((T)20);
//         l.insert((T)30);
//         l.insert((T)40);
//         l.view(); cout << endl;

//         cout << "\n--- INSERT AT POSITION ---\n";
//         l.insert((T)99, 0);
//         l.insert((T)77, 2);
//         l.insert((T)88, -1);
//         l.view(); cout << endl;

//         cout << "\n--- SIZE ---\n";
//         cout << l.size() << endl;

//         cout << "\n--- VALUE ---\n";
//         cout << "Index 0: " << l.value(0) << endl;
//         cout << "Index 2: " << l.value(2) << endl;

//         cout << "\n--- INDEX ---\n";
//         cout << "Index of 40: " << l.index((T)40) << endl;

//         cout << "\n--- MODIFY ---\n";
//         cout << "Old value: " << l.modify((T)555, 1) << endl;
//         l.view(); cout << endl;

//         cout << "\n--- UPDATE (FOUND) ---\n";
//         cout << "Updated index: " << l.update((T)30, (T)300) << endl;
//         l.view(); cout << endl;

//         cout << "\n--- UPDATE (NOT FOUND, INSERT) ---\n";
//         cout << "Index: " << l.update((T)999, (T)111, true) << endl;
//         l.view(); cout << endl;

//         cout << "\n--- POINTER ---\n";
//         node<T>* p = l.pointer(2);
//         if(p) cout << "Pointer value: " << p->K << endl;

//         cout << "\n--- REMOVE ---\n";
//         cout << "Removed: " << l.remove(0) << endl;
//         l.view(); cout << endl;

//         cout << "\n--- DROP ---\n";
//         cout << "Dropped index: " << l.drop((T)40) << endl;
//         l.view(); cout << endl;

//         cout << "\n--- FINAL LIST ---\n";
//         l.view(); cout << endl;

//     } catch(exception &e) {
//         cout << "Exception: " << e.what() << endl;
//     }
// }

// int main() {

//     // INT
//     testList<int>("int");

//     // FLOAT
//     testList<float>("float");

//     // CHAR
//     testList<char>("char");

//     // STRING (special handling)
//     cout << "\n============================\n";
//     cout << "Testing LIST<string>\n";
//     cout << "============================\n";

//     LIST<string> ls;

//     try {
//         ls.insert("A");
//         ls.insert("B");
//         ls.insert("C");
//         ls.insert("D");
//         ls.view(); cout << endl;

//         ls.insert("Start", 0);
//         ls.insert("Mid", 2);
//         ls.insert("End", -1);
//         ls.view(); cout << endl;

//         cout << "Index of C: " << ls.index("C") << endl;

//         cout << "Modify index 1: " << ls.modify("XXX", 1) << endl;
//         ls.view(); cout << endl;

//         cout << "Update B->BBB: " << ls.update("B", "BBB") << endl;
//         ls.view(); cout << endl;

//         cout << "Remove index 0: " << ls.remove(0) << endl;
//         ls.view(); cout << endl;

//         cout << "Drop C: " << ls.drop("C") << endl;
//         ls.view(); cout << endl;

//     } catch(exception &e) {
//         cout << "Exception: " << e.what() << endl;
//     }

//     return 0;
// }

// int main() {

//     cout << "===== LINKED LIST TEST =====\n";

//     LIST<int> l;

//     // ---------------- INSERT ----------------
//     cout << "\n[INSERT]\n";
//     l.insert(10);
//     l.insert(20);
//     l.insert(30);
//     l.insert(40);
//     l.view(); cout << endl;

//     // Insert at specific positions
//     cout << "\n[INSERT AT POSITION]\n";
//     l.insert(99, 0);   // head
//     l.insert(77, 2);   // middle
//     l.insert(88, -1);  // end
//     l.view(); cout << endl;

//     // ---------------- SIZE ----------------
//     cout << "\n[SIZE]\n";
//     cout << "Size: " << l.size() << endl;

//     // ---------------- ACCESS ----------------
//     cout << "\n[ACCESS]\n";
//     cout << "l[0] = " << l[0] << endl;
//     cout << "l[2] = " << l[2] << endl;

//     // Modify using []
//     l[1] = 555;
//     cout << "After modify l[1]=555: ";
//     l.view(); cout << endl;

//     // ---------------- VALUE / INDEX ----------------
//     cout << "\n[VALUE / INDEX]\n";
//     cout << "Value at index 3: " << l.value(3) << endl;
//     cout << "Index of 40: " << l.index(40) << endl;

//     // ---------------- MODIFY ----------------
//     cout << "\n[MODIFY]\n";
//     cout << "Old value: " << l.modify(111, 2) << endl;
//     l.view(); cout << endl;

//     // ---------------- UPDATE ----------------
//     cout << "\n[UPDATE]\n";
//     cout << "Update 30 -> 300 at index: " << l.update(30, 300) << endl;
//     l.view(); cout << endl;

//     cout << "Update (not found, insert): index = "
//          << l.update(999, 123, true) << endl;
//     l.view(); cout << endl;

//     // ---------------- POINTER ----------------
//     cout << "\n[POINTER]\n";
//     node<int>* p = l.pointer(2);
//     if(p) cout << "Pointer value: " << p->K << endl;

//     // ---------------- REMOVE ----------------
//     cout << "\n[REMOVE]\n";
//     cout << "Removed element: " << l.remove(0) << endl;
//     l.view(); cout << endl;

//     // ---------------- DROP ----------------
//     cout << "\n[DROP]\n";
//     cout << "Dropped index: " << l.drop(40) << endl;
//     l.view(); cout << endl;

//     // ---------------- COPY CONSTRUCTOR ----------------
//     cout << "\n[COPY CONSTRUCTOR]\n";
//     LIST<int> l2 = l;
//     cout << "Copied list: ";
//     l2.view(); cout << endl;

//     // ---------------- ASSIGNMENT ----------------
//     cout << "\n[ASSIGNMENT OPERATOR]\n";
//     LIST<int> l3;
//     l3 = l;
//     cout << "Assigned list: ";
//     l3.view(); cout << endl;

//     // ---------------- CONST TEST ----------------
//     cout << "\n[CONST TEST]\n";
//     const LIST<int> cl = l;
//     cout << "cl[0] = " << cl[0] << endl;

//     // ---------------- STRING TEST ----------------
//     cout << "\n[STRING TEST]\n";
//     LIST<string> ls;
//     ls.insert("A");
//     ls.insert("B");
//     ls.insert("C");
//     ls.insert("D");

//     ls.view(); cout << endl;

//     ls.insert("Start", 0);
//     ls.insert("End", -1);
//     ls.view(); cout << endl;

//     cout << "Index of C: " << ls.index("C") << endl;

//     cout << "Modify index 1: " << ls.modify("XXX", 1) << endl;
//     ls.view(); cout << endl;

//     cout << "Drop C: " << ls.drop("C") << endl;
//     ls.view(); cout << endl;

//     cout << "\n===== TEST COMPLETE =====\n";

//     return 0;
// }

//using VarType = variant<int, double, string>;

// template<typename D>
// class LIST {
//     node<D>* H;
//     node<D>* T;
//     long int elem;

// public:

// // “Iterator class is needed to wrap raw pointers and provide controlled access with operator overloading so the container behaves like STL instead of exposing internal structure.”

// // “We use iterator instead of returning raw pointer because pointer exposes internal node structure and cannot be controlled, while iterator provides abstraction and operator-based access.”

//     class iterator {
//     node<D>* ptr;

//     public:
//         iterator(node<D>* p = nullptr) : ptr(p) {}

//         D& operator*(){
//             if(!ptr) throw std::runtime_error("Null iterator");
//             return ptr->K;
//         }
//         const D& operator*() const{
//             if(!ptr) throw std::runtime_error("Null iterator");
//             return ptr->K;
//         }

//         iterator& operator++(){
//             if(ptr) ptr = ptr->P;
//             return *this;
//         }
//         iterator operator++(int){
//             iterator temp = *this; 
//             ++(*this);
//             return temp;
//         }

//         bool operator!=(const iterator& other) const{ return ptr != other.ptr; }
//         bool operator==(const iterator& other) const{ return ptr == other.ptr; }

//         D* operator->(){ return &(ptr->K); }
//         const D* operator->() const{ return &(ptr->K); }
//         // string s = "hello"; string* p = &s;
//         // cout << p->size();  we cannot overload (.) in C++ thats why ->

//     };

//     iterator begin(){ return iterator(H); }
//     iterator end(){ return iterator(nullptr); }

//     iterator begin() const{ return iterator(H); }
//     iterator end() const{ return iterator(nullptr); }

// };


// int main(){
//     LIST<int> l;

//     l.insert(10);
//     l.insert(20);
//     l.insert(30);

//     for(auto it = l.begin(); it != l.end(); ++it){
//         cout << *it << " ";
//     }

//     for(auto x : l){
//         cout << x << " ";
//     }
//     // for(auto x : l) 👉 Compiler converts it into
//     // auto && __range = l;
//     // for(auto __it = __range.begin(); __it != __range.end(); ++__it){
//     //     auto x = *__it;
//     // }
// }
