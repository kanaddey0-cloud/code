#include <iostream>
#include <stdexcept>

template<typename D>
struct node{ D K; node<D> *P; }; 

template<typename D>
class iterator { 
    node<D>* ptr; 
public:
    iterator(node<D>* p = nullptr);
    D& operator*();
    const D& operator*() const;
    iterator& operator++() noexcept;
    iterator operator++(int) noexcept;
    bool operator!=(const iterator& other) const noexcept;
    bool operator==(const iterator& other) const noexcept;
    D* operator->();
    const D* operator->() const;
};

template<typename D>
class LIST{
protected:
    long int elem; 
    node<D>* H, *T;
    node<D>* pointer(long int index) const;
    void rotate(node<D>*& head, node<D>*& tail);
    long int clear(node<D>*& p);
    long int clearupto(node<D>*& head, node<D>*& tail);
public:
    LIST();
    LIST(const LIST<D>& other);
    LIST(LIST<D>&& other) noexcept;
    D& operator[](long int index);
    const D& operator[](long int index) const;
    LIST<D>& operator=(const LIST<D>& other);
    LIST<D>& operator=(LIST<D>&& other) noexcept;
    long int size() const { return elem; }
    bool insert(D val, long int index=-1);
    long int drop(D val);
    D remove(long int index);
    long int update(D prev, D curr, bool in=false);
    D modify(D curr, long int index);
    bool add(const LIST<D>& next);
    const D& value(long int index) const;
    long int index(D value) const;
    void reverse();
    void view(bool v=false) const;
    iterator<D> begin() noexcept;
    iterator<D> begin() const noexcept;
    iterator<D> end() noexcept;
    iterator<D> end() const noexcept;
    ~LIST();
};

template<typename D>
bool LIST<D>::add(const LIST<D>& next){
    if(this == &next) return false;
    if(!next.H) return false;
    node<D>* tmp=next.H;
    while(tmp){
        insert(tmp->K); tmp=tmp->P;
    }
    return true;
}

template<typename D>
void LIST<D>::rotate(node<D>*& head, node<D>*& tail){
    if(!head || !head->P) return;
    node<D>* pA = nullptr, *pB = head, *pC = nullptr;
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
LIST<D>::LIST(){
    H = T = nullptr; elem = 0;
}

template<typename D>
LIST<D>::LIST(LIST<D>&& other) noexcept{
    H = other.H; T = other.T;
    elem = other.elem;

    other.H = other.T = nullptr;
    other.elem = 0;
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
LIST<D>::LIST(const LIST<D>& other){
    H = T = nullptr; elem = 0;
    node<D>* iter = other.H;
    while(iter){
        insert(iter->K); iter = iter->P;
    }
}

template<typename D>
LIST<D>& LIST<D>::operator=(const LIST<D>& other){
    if(this != &other){
        clear(H);
        H=T=nullptr; elem=0;
        
        node<D>* iter=other.H;
        while(iter){
            insert(iter->K); iter=iter->P;
        }
    }
    return *this;
}

template<typename D>
long int LIST<D>::clear(node<D>*& p){
    node<D>* tmp; long int count=0;
    while(p){ 
        tmp=p; p=p->P; 
        delete tmp; count++;
    }
    return count;
}

template<typename D>
long int LIST<D>::clearupto(node<D>*& head, node<D>*& tail){
    if(!head) return 0;
    node<D>* p=head->P, *tmp; long int count=0;
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
LIST<D>::~LIST(){
    clear(H);
    T = nullptr; elem = 0;
}

template<typename D>   // Read & Write 
D& LIST<D>::operator[](long int index){
    node<D>* ptr=pointer(index);   // get the node pointer
    if(!ptr) throw std::out_of_range("Index out of bounds");
    return ptr->K;                 // return reference to the value
}

template<typename D>  // Read Only
const D& LIST<D>::operator[](long int index) const{
    node<D>* ptr=pointer(index);   // get the node pointer
    if(!ptr) throw std::out_of_range("Index out of bounds");
    return ptr->K;                 // return const reference
}

template<typename D>
long int LIST<D>::update(D prev, D curr, bool in){
    node<D> *iter=H; long int index=0;
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
D LIST<D>::modify(D curr, long int index){
    node<D>* point=pointer(index);
    if(point){
        D tmp=point->K; point->K=curr;
        return tmp;
    } 
    throw std::out_of_range("Index out of bounds");
}

template<typename D>
node<D>* LIST<D>::pointer(long int index) const{
    if(index>=elem || index<0) return nullptr;
    node<D> *iter=H;
    for(long int i=0; i<index; i++) iter=iter->P;
    return iter;
}

template<typename D>
long int LIST<D>::index(D value) const{
    node<D> *iter=H; long int index=0;
    while(iter){
        if(iter->K==value) return index;
        iter=iter->P; index++;
    } return -1;
}

template<typename D>
const D& LIST<D>::value(long int index) const{
    if(index>=elem || index<0) throw std::out_of_range("Index out of bounds");
    node<D> *iter=H;
    for(long int i=0; i<index; i++) iter=iter->P;
    return iter->K;
}

template<typename D>
D LIST<D>::remove(long int index){
    if(!elem) throw std::runtime_error("List is empty"); 
    if(index>=elem || index<0) throw std::out_of_range("Index out of bounds");

    node<D> *iter=H; D K;
    if(index==0){ K=iter->K;
        H=H->P; delete iter; elem--; 
        if(!H) T=nullptr; return K; 
    }
    for(long int i=1; i<index; i++){ iter=iter->P; }
    node<D> *tmp=iter->P; 
    iter->P=iter->P->P;
    if(T==tmp) T=iter;
    K=tmp->K; delete tmp; elem--; return K;
}

template<typename D>
long int LIST<D>::drop(D val){
    if(H==nullptr) return -1; 
    node<D> *iter=H;
    if(H->K==val){ 
        H=H->P; delete iter; elem--; 
        if(!H) T=nullptr; return 0; 
    }
    long int index=1;
    while(iter->P){
        if(iter->P->K==val){
            node<D> *tmp=iter->P; iter->P=tmp->P;
            if(tmp==T) T=iter;
            delete tmp; elem--; return index;
        }
        iter=iter->P; index++;
    }
    return -1; 
}

template<typename D>
bool LIST<D>::insert(D val, long int index){
    if(H==nullptr){
        H=T=new node<D>{val, nullptr}; elem++;
        return true;
    }
    if(index<-1 || index>elem) return false;
    if(index==-1 || index==elem){
        T->P=new node<D>; T=T->P;
        *T=node<D>{val, nullptr}; elem++;    
        return true;    
    }
    if(index==0){
        node<D> *tmp=new node<D>{val, H};
        H=tmp; elem++;
        return true;
    }
    node<D> *iter=H; long int i;
    for(i=1; i<index; i++) iter=iter->P;
    node<D> *tmp=new node<D>{val, iter->P};
    iter->P=tmp; elem++;
    return true;
}

template<typename D>
void LIST<D>::view(bool v) const{
    node<D> *iter=H;
    if(v) std::cout<<"head->";
    std::cout<<"[";
    while(iter){
        std::cout<<iter->K; if(iter->P!=nullptr) std::cout<<", ";
        iter=iter->P;
    } std::cout<<"]";
    if(v) std::cout<<"<-tail";
}

template<typename D>
iterator<D> LIST<D>::begin() noexcept{ return iterator<D>(H); }

template<typename D>
iterator<D> LIST<D>::end() noexcept{ return iterator<D>(nullptr); }

template<typename D>
iterator<D> LIST<D>::begin() const noexcept{ return iterator<D>(H); }

template<typename D>
iterator<D> LIST<D>::end() const noexcept{ return iterator<D>(nullptr); }

//-------------- iterator
template<typename D>
iterator<D>::iterator(node<D>* p) : ptr(p) {}

template<typename D>
D& iterator<D>::operator*(){
    if(!ptr) throw std::runtime_error("Null iterator");
    return ptr->K;
}

template<typename D>
const D& iterator<D>::operator*() const{
    if(!ptr) throw std::runtime_error("Null iterator");
    return ptr->K;
}

template<typename D>
iterator<D>& iterator<D>::operator++() noexcept{
    if(ptr) ptr = ptr->P;
    return *this;
}

template<typename D>
iterator<D> iterator<D>::operator++(int) noexcept{
    iterator<D> temp = *this; 
    ++(*this);
    return temp;
}

template<typename D>
bool iterator<D>::operator!=(const iterator<D>& other) const noexcept{ return ptr != other.ptr; }

template<typename D>
bool iterator<D>::operator==(const iterator<D>& other) const noexcept{ return ptr == other.ptr; }

template<typename D>
D* iterator<D>::operator->(){ 
    if(!ptr) throw std::runtime_error("Null iterator");
    return &(ptr->K); 
}

template<typename D>
const D* iterator<D>::operator->() const{ 
    if(!ptr) throw std::runtime_error("Null iterator");
    return &(ptr->K); 
}


using namespace std;

int main() {
    LIST<int> list1;
    LIST<int> list2;

    // Fill list2
    list2.insert(10);
    list2.insert(20);
    list2.insert(30);

    // cout << "Initial list2: ";
    list2.view(true);

    // // -----------------------------
    // // ✅ TEST 1: add() (COPY)
    // // -----------------------------
    // cout << "\n--- Testing add() (copy) ---\n";

    // list1.add(list2);

    // cout << "list1 after add: ";
    // list1.view();   // [10, 20, 30]

    // cout << "list2 after add: ";
    // list2.view();   // should remain SAME

    // // Modify list1 to prove it's independent
    // list1.insert(40);

    // cout << "list1 after insert 40: ";
    // list1.view();   // [10,20,30,40]

    // cout << "list2 still unchanged: ";
    // list2.view();   // [10,20,30]

    return 0;
}

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
