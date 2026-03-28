#include <iostream>

template<typename D>
struct node{ D K; node<D> *P; }; 

template<typename D>
class LIST{
    long int elem; 
    node<D> *H, *T;
public:
    LIST(){ H=T=nullptr; elem=0; }
    long int size() const { return elem; }
    int insert(D val, long int index=-1);
    int drop(D val);
    D remove(long int index);
    long int update(D prev, D curr, bool in=0);
    node<D>* pointer(long int index);
    D modify(D curr, long int index);
    D value(long int index);
    long int index(D value);
    void view();
};

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
node<D>* LIST<D>::pointer(long int index){
    if(index>=elem || index<0) return nullptr;
    node<D> *iter=H;
    for(long int i=0; i<index; i++) iter=iter->P;
    return iter;
}

// template<typename I, typename R>
// R find(I veriable, bool position){
//     node<D> *iter=H; 
//     if(position){
//         if(veriable=elem) throw out_of_range("Index out of bounds");
//         for(int i=0; i<veriable; i++) iter=iter->P;
//         return iter->K;
//     }
//     long int index=0;
//     while(iter){
//         if(iter->K==val) return index;
//         iter=iter->P; index++;
//     } return -1;
// }
// template<typename D>
// node<D>* LIST<D>::search(D val){
//     node<D> *iter=H; 
//     while(iter){
//         if(iter->K==val) return iter;
//         iter=iter->P; 
//     } return nullptr;
// }

template<typename D>
long int LIST<D>::index(D value){
    node<D> *iter=H; long int index=0;
    while(iter){
        if(iter->K==value) return index;
        iter=iter->P; index++;
    } return -1;
}

template<typename D>
D LIST<D>::value(long int index){
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
int LIST<D>::drop(D val){
    if(H==nullptr) throw std::runtime_error("List is empty"); 
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
    throw std::out_of_range("Value not found in list"); 
}

template<typename D>
int LIST<D>::insert(D val, long int index){
    if(H==nullptr){
        H=T=new node<D>{val, nullptr}; elem++;
        return 1;
    }
    if(index<-1) throw std::out_of_range("Index cannot be less than -1");
    if(index==-1 || index>=elem){
        T->P=new node<D>; T=T->P;
        *T = node<D>{val, nullptr}; elem++;    
        return 1;    
    }
    if(index==0){
        node<D> *tmp=new node<D>{val, H};
        H=tmp; elem++;
        return 1;
    }
    node<D> *iter=H;
    for(long int i=1; i<=index; i++){
        if(i==index){
            node<D> *tmp=new node<D>{val, iter->P};
            iter->P=tmp; elem++;
            return 1;
        }
        iter=iter->P;
    }
    return 0;
}

template<typename D>
void LIST<D>::view(){
    node<D> *iter=H;
    std::cout<<"[";
    while(iter){
        std::cout<<iter->K; if(iter->P!=nullptr) std::cout<<", ";
        iter=iter->P;
    } std::cout<<"]";
}

#include <string>
using namespace std;
// ---------- TEST FUNCTION ----------
template<typename T>
void testList(string name) {
    cout << "\n============================\n";
    cout << "Testing LIST<" << name << ">\n";
    cout << "============================\n";

    LIST<T> l;

    try {
        cout << "\n--- INSERT ---\n";
        l.insert((T)10);
        l.insert((T)20);
        l.insert((T)30);
        l.insert((T)40);
        l.view(); cout << endl;

        cout << "\n--- INSERT AT POSITION ---\n";
        l.insert((T)99, 0);
        l.insert((T)77, 2);
        l.insert((T)88, -1);
        l.view(); cout << endl;

        cout << "\n--- SIZE ---\n";
        cout << l.size() << endl;

        cout << "\n--- VALUE ---\n";
        cout << "Index 0: " << l.value(0) << endl;
        cout << "Index 2: " << l.value(2) << endl;

        cout << "\n--- INDEX ---\n";
        cout << "Index of 40: " << l.index((T)40) << endl;

        cout << "\n--- MODIFY ---\n";
        cout << "Old value: " << l.modify((T)555, 1) << endl;
        l.view(); cout << endl;

        cout << "\n--- UPDATE (FOUND) ---\n";
        cout << "Updated index: " << l.update((T)30, (T)300) << endl;
        l.view(); cout << endl;

        cout << "\n--- UPDATE (NOT FOUND, INSERT) ---\n";
        cout << "Index: " << l.update((T)999, (T)111, true) << endl;
        l.view(); cout << endl;

        cout << "\n--- POINTER ---\n";
        node<T>* p = l.pointer(2);
        if(p) cout << "Pointer value: " << p->K << endl;

        cout << "\n--- REMOVE ---\n";
        cout << "Removed: " << l.remove(0) << endl;
        l.view(); cout << endl;

        cout << "\n--- DROP ---\n";
        cout << "Dropped index: " << l.drop((T)40) << endl;
        l.view(); cout << endl;

        cout << "\n--- FINAL LIST ---\n";
        l.view(); cout << endl;

    } catch(exception &e) {
        cout << "Exception: " << e.what() << endl;
    }
}

int main() {

    // INT
    testList<int>("int");

    // FLOAT
    testList<float>("float");

    // CHAR
    testList<char>("char");

    // STRING (special handling)
    cout << "\n============================\n";
    cout << "Testing LIST<string>\n";
    cout << "============================\n";

    LIST<string> ls;

    try {
        ls.insert("A");
        ls.insert("B");
        ls.insert("C");
        ls.insert("D");
        ls.view(); cout << endl;

        ls.insert("Start", 0);
        ls.insert("Mid", 2);
        ls.insert("End", -1);
        ls.view(); cout << endl;

        cout << "Index of C: " << ls.index("C") << endl;

        cout << "Modify index 1: " << ls.modify("XXX", 1) << endl;
        ls.view(); cout << endl;

        cout << "Update B->BBB: " << ls.update("B", "BBB") << endl;
        ls.view(); cout << endl;

        cout << "Remove index 0: " << ls.remove(0) << endl;
        ls.view(); cout << endl;

        cout << "Drop C: " << ls.drop("C") << endl;
        ls.view(); cout << endl;

    } catch(exception &e) {
        cout << "Exception: " << e.what() << endl;
    }

    return 0;
}
//using VarType = variant<int, double, string>;