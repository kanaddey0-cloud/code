#include <GDSLstack.hpp>
#include <GDSLqueue.hpp>

enum class MODE : char {
    DFS='w', BFS='x', DFS_LR='y', BFS_RL='z',
    IN='a', PRE='b', POST='c',
    DEF='d'
};
enum { L, R, P };

template<typename D>
struct BSTnode{ D K; BSTnode<D>** LINK; };

template<typename D>
class BSTiterator { 
    BSTnode<D>* ptr, *ROOT, *last;
    STACK<BSTnode<D>*> S;
    QUEUE<BSTnode<D>*> Q;
public:
    MODE M;
    BSTiterator(MODE mode, BSTnode<D>* p = nullptr);
    BSTnode<D>* increment();
    BSTnode<D>* incrementBFS();
    BSTnode<D>* incrementDFS();
    BSTnode<D>* incrementIN();
    BSTnode<D>* incrementPRE();
    BSTnode<D>* incrementPOST();
    D& operator*();
    const D& operator*() const;
    BSTiterator& operator++() noexcept;
    BSTiterator operator++(int) noexcept;
    bool operator!=(const BSTiterator& other) const noexcept;
    bool operator==(const BSTiterator& other) const noexcept;
    D* operator->();
    const D* operator->() const;
};

template<typename D>
BSTiterator<D>::BSTiterator(MODE mode, BSTnode<D>* p) : ptr(nullptr), last(nullptr), ROOT(p), M(mode) {
    if(!ROOT) return;

    switch(M){
        case MODE::BFS:
        case MODE::BFS_RL:
            Q.enqueue(ROOT); break;

        case MODE::DFS:
        case MODE::DFS_LR:

        case MODE::PRE:
            S.push(ROOT); break;

        case MODE::IN:
        case MODE::POST:
        {
            BSTnode<D>* temp = ROOT;
            while(temp){
                S.push(temp);
                temp = temp->LINK[L];
            } break;
        }

        default: break;
    }
}
    
template <typename D>
BSTnode<D>* BSTiterator<D>::incrementBFS(){
    if(Q.empty()) return nullptr;
    BSTnode<D>* temp = Q.dequeue();

    if(M == MODE::BFS){
        if(temp->LINK[L]) Q.enqueue(temp->LINK[L]);
        if(temp->LINK[R]) Q.enqueue(temp->LINK[R]);
    }else{
        if(temp->LINK[R]) Q.enqueue(temp->LINK[R]);
        if(temp->LINK[L]) Q.enqueue(temp->LINK[L]);
    }
    return temp;
}

template<typename D>
BSTnode<D>* BSTiterator<D>::incrementDFS(){
    if(S.empty()) return nullptr;
    BSTnode<D>* temp = S.pop();

    if(M == MODE::DFS){
        if(temp->LINK[L]) S.push(temp->LINK[L]);
        if(temp->LINK[R]) S.push(temp->LINK[R]);
    }else{
        if(temp->LINK[R]) S.push(temp->LINK[R]);
        if(temp->LINK[L]) S.push(temp->LINK[L]);
    }
    return temp;
}

template<typename D>
BSTnode<D>* BSTiterator<D>::incrementIN(){
    if(S.empty()) return nullptr;
    BSTnode<D>* node = S.pop();

    BSTnode<D>* tmp = node->LINK[R];
    while(tmp){
        S.push(tmp);
        tmp = tmp->LINK[L];
    }
    return node;
}

template<typename D>
BSTnode<D>* BSTiterator<D>::incrementPRE(){
    if(S.empty()) return nullptr;
    BSTnode<D>* node = S.pop();

    if(node->LINK[R]) S.push(node->LINK[R]);
    if(node->LINK[L]) S.push(node->LINK[L]);
    return node;
}

template<typename D>
BSTnode<D>* BSTiterator<D>::incrementPOST(){
    while(!S.empty()){
        BSTnode<D>* peek = S.tos();
        BSTnode<D>* right = peek->LINK[R];

        if(right && last != right){
            BSTnode<D>* tmp = right;
            while(tmp){
                S.push(tmp);
                tmp = tmp->LINK[L];
            }
        }else{
            S.pop();
            last = peek;
            return peek;
        }
    }
    return nullptr;
}

template<typename D>
BSTnode<D>* BSTiterator<D>::increment(){
    switch(M){
        case MODE::BFS: 
        case MODE::BFS_RL: 
            return incrementBFS();

        case MODE::DFS: 
        case MODE::DFS_LR: 
            return incrementDFS();

        case MODE::IN:   return incrementIN();
        case MODE::PRE:  return incrementPRE();
        case MODE::POST: return incrementPOST();

        default: return nullptr;
    }
}

template<typename D>
D& BSTiterator<D>::operator*(){
    if(!ptr) throw std::runtime_error("Null iterator");
    return ptr->K;
}

template<typename D>
const D& BSTiterator<D>::operator*() const{
    if(!ptr) throw std::runtime_error("Null iterator");
    return ptr->K;
}

template<typename D>
BSTiterator<D>& BSTiterator<D>::operator++() noexcept{
    ptr = increment();
    return *this;
}

template<typename D>
BSTiterator<D> BSTiterator<D>::operator++(int) noexcept{
    BSTiterator<D> temp = *this; 
    ptr = increment();
    return temp;
}

template<typename D>
bool BSTiterator<D>::operator!=(const BSTiterator<D>& other) const noexcept{ return ptr != other.ptr; }

template<typename D>
bool BSTiterator<D>::operator==(const BSTiterator<D>& other) const noexcept{ return ptr == other.ptr; }

template<typename D>
D* BSTiterator<D>::operator->(){ 
    if(!ptr) throw std::runtime_error("Null iterator");
    return &(ptr->K); 
}

template<typename D>
const D* BSTiterator<D>::operator->() const{ 
    if(!ptr) throw std::runtime_error("Null iterator");
    return &(ptr->K); 
}

template<typename D>
class BSTREE{
protected:
    unsigned long int elem;
    unsigned int LC: 2;
    BSTnode<D>* ROOT;
    BSTnode<D>* create(D item, BSTnode<D>* parent=nullptr);
    void print_Key_L_C_R(const BSTnode<D>* tmp) const;
    bool deleting(BSTnode<D>*& del, BSTnode<D>* tmp);
    bool freelink(BSTnode<D>*& root);
    unsigned long int addlink(BSTnode<D>*& root, const BSTnode<D>*& other);
    BSTnode<D>* pointer(long int index, MODE mode=MODE::DEF) const;
    BSTnode<D>* pointerBFS(const unsigned long int index, bool order=false) const;
    BSTnode<D>* pointerDFS(const unsigned long int index, bool order=false) const;
    BSTnode<D>* pointerIN(BSTnode<D>* root, const unsigned long int index, unsigned long int& count) const;
    BSTnode<D>* pointerPRE(BSTnode<D>* root, const unsigned long int index, unsigned long int& count) const;
    BSTnode<D>* pointerPOST(BSTnode<D>* root, const unsigned long int index, unsigned long int& count) const;
public:
    MODE M;
    BSTREE(bool l=false);
    BSTREE(const BSTREE<D>& other);
    BSTREE(BSTREE<D>&& other) noexcept;
    BSTREE& operator=(const BSTREE& other);
    BSTREE& operator=(BSTREE&& other) noexcept;
    D& operator[](const long int index);
    const D& operator[](const long int index) const;
    long int size() const { return elem; }
    bool insert(D item);
    bool search(D item);
    bool remove(D item);
    bool add(const BSTREE<D>& root);
    void view(MODE mode=MODE::DEF) const;
    void viewDFS(bool order=false) const;
    void viewBFS(bool order=false) const;
    void viewIN(const BSTnode<D>* root) const;
    void viewPRE(const BSTnode<D>* root) const;
    void viewPOST(const BSTnode<D>* root) const;
    BSTiterator<D> begin() noexcept;
    BSTiterator<D> begin() const noexcept;
    BSTiterator<D> end() noexcept;
    BSTiterator<D> end() const noexcept;
    ~BSTREE();
};

template<typename D>
BSTREE<D>::BSTREE(bool l){ ROOT=nullptr; LC=l?3:2; M=MODE::IN; elem=0; }

template<typename D>
BSTREE<D>::BSTREE(const BSTREE<D>& other) :BSTREE<D>(other.LC==3?true:false){
    M=other.M;
    if(!other.ROOT) return; 
    QUEUE<BSTnode<D>*> Q; 
    BSTnode<D>* tmp;
    Q.enqueue(other.ROOT);
    while(!Q.empty()){
        tmp=Q.dequeue();
            if(tmp->LINK[L]) Q.enqueue(tmp->LINK[L]);
            if(tmp->LINK[R]) Q.enqueue(tmp->LINK[R]);
        insert(tmp->K);
    }
}

template<typename D>
BSTREE<D>::BSTREE(BSTREE<D>&& other) noexcept :ROOT(other.ROOT), elem(other.elem), LC(other.LC), M(other.M){
    other.ROOT=nullptr;
    other.elem=0;
}

template<typename D>
BSTREE<D>& BSTREE<D>::operator=(const BSTREE<D>& other){
    if(this == &other) return *this;

    freelink(ROOT); if(ROOT){ delete[] ROOT->LINK; delete ROOT; ROOT=nullptr; } 
    elem=0; LC=other.LC;
    if(!other.ROOT) return *this;
    
    QUEUE<BSTnode<D>*> Q; 
    BSTnode<D>* tmp;
    Q.enqueue(other.ROOT);
    while(!Q.empty()){
        tmp=Q.dequeue();
            if(tmp->LINK[L]) Q.enqueue(tmp->LINK[L]);
            if(tmp->LINK[R]) Q.enqueue(tmp->LINK[R]);
        insert(tmp->K);
    }
    return *this;
}

template<typename D>
BSTREE<D>& BSTREE<D>::operator=(BSTREE<D>&& other) noexcept{
    if(this == &other) return *this;

    freelink(ROOT); if(ROOT){ delete[] ROOT->LINK; delete ROOT; ROOT=nullptr; } 
    elem=0; LC=other.LC;
    if(!other.ROOT) return *this;

    ROOT=other.ROOT; elem=other.elem;
    other.ROOT=nullptr; other.elem=0;
    return *this;
}

template<typename D>
BSTREE<D>::~BSTREE(){ 
    if(ROOT){ freelink(ROOT); delete[] ROOT->LINK; delete ROOT; ROOT=nullptr; } 
}

template<typename D>
unsigned long int BSTREE<D>::addlink(BSTnode<D>*& root, const BSTnode<D>*& other){
    if(!root || !other) return 0;
    QUEUE<const BSTnode<D>*> Q; 
    BSTnode<D>* ptr, *tmp, *key; D item; unsigned long int count=0;
    Q.enqueue(other);
    while(!Q.empty()){
        key=Q.dequeue();
            if(key->LINK[L]) Q.enqueue(key->LINK[L]);
            if(key->LINK[R]) Q.enqueue(key->LINK[R]); 
        ptr=root; item=key->K;
        while(ptr){
            tmp=ptr;
            if(item<ptr->K) ptr=ptr->LINK[L];
            else if(item>ptr->K) ptr=ptr->LINK[R];
            else{ tmp=nullptr; break; }
        }
        if(!tmp) continue;
        if(item<tmp->K) tmp->LINK[L]=create(item,tmp); 
        else tmp->LINK[R]=create(item,tmp); 
        elem++; count++;
    }
    return count;
}

template<typename D>
bool BSTREE<D>::add(const BSTREE<D>& root){
    if(this == &root) return false;
    if(!root.ROOT) return false;
    QUEUE<BSTnode<D>*> Q; 
    BSTnode<D>* tmp;
    Q.enqueue(root.ROOT);
    while(!Q.empty()){
        tmp=Q.dequeue();
            if(tmp->LINK[L]) Q.enqueue(tmp->LINK[L]);
            if(tmp->LINK[R]) Q.enqueue(tmp->LINK[R]);
        insert(tmp->K);
    }
    return true;
}

template<typename D>
void BSTREE<D>::print_Key_L_C_R(const BSTnode<D>* tmp) const{
    if(tmp->LINK[L]) std::cout<<tmp->LINK[L]->K<<"<-";
    else std::cout<<"NULL<-"; 
    std::cout<<"["<<tmp->K<<"]";
    if(tmp->LINK[R]) std::cout<<"->"<<tmp->LINK[R]->K;
    else std::cout<<"->NULL"; 
}

template<typename D>
void BSTREE<D>::viewBFS(bool order) const{
    if(!ROOT){ std::cout<<"Tree is empty"; return; }
    QUEUE<BSTnode<D>*> Q; 
    BSTnode<D>* tmp;
    Q.enqueue(ROOT);
    while(!Q.empty()){
        tmp=Q.dequeue();
        if(order){
            if(tmp->LINK[R]) Q.enqueue(tmp->LINK[R]);
            if(tmp->LINK[L]) Q.enqueue(tmp->LINK[L]);
        }else{
            if(tmp->LINK[L]) Q.enqueue(tmp->LINK[L]);
            if(tmp->LINK[R]) Q.enqueue(tmp->LINK[R]);
        }
        print_Key_L_C_R(tmp); std::cout<<"\n";
    }
}

template<typename D>
void BSTREE<D>::viewDFS(bool order) const{
    if(!ROOT){ std::cout<<"Tree is empty"; return; }
    STACK<BSTnode<D>*> S; 
    BSTnode<D>* tmp;
    S.push(ROOT);
    while(!S.empty()){
        tmp=S.pop();
        if(order){
            if(tmp->LINK[R]) S.push(tmp->LINK[R]);
            if(tmp->LINK[L]) S.push(tmp->LINK[L]);
        }else{
            if(tmp->LINK[L]) S.push(tmp->LINK[L]);
            if(tmp->LINK[R]) S.push(tmp->LINK[R]);
        }
        print_Key_L_C_R(tmp); std::cout<<"\n";
    }
}

template<typename D>
void BSTREE<D>::viewIN(const BSTnode<D>* root) const{
    if(!root) return;

    viewIN(root->LINK[L]);  print_Key_L_C_R(root); std::cout<<"\n";  viewIN(root->LINK[R]);
}

template<typename D>
void BSTREE<D>::viewPRE(const BSTnode<D>* root) const{
    if(!root) return;

    print_Key_L_C_R(root); std::cout<<"\n";  viewPRE(root->LINK[L]);  viewPRE(root->LINK[R]);
}

template<typename D>
void BSTREE<D>::viewPOST(const BSTnode<D>* root) const{
    if(!root) return;

    viewPOST(root->LINK[L]);  viewPOST(root->LINK[R]);  print_Key_L_C_R(root); std::cout<<"\n";
}

template<typename D>
void BSTREE<D>::view(MODE mode) const{
    if(!ROOT){ std::cout << "NULL"; return; }
    if(mode == MODE::DEF) mode=M;
    switch(mode){
        case MODE::DFS: viewDFS(); break;
        case MODE::BFS: viewBFS(); break;

        case MODE::IN:
            if(ROOT) viewIN(ROOT);
            break;
        case MODE::PRE:
            if(ROOT) viewPRE(ROOT);
            break;
        case MODE::POST:
            if(ROOT) viewPOST(ROOT);
            break;

        case MODE::DFS_LR: viewDFS(true); break;
        case MODE::BFS_RL: viewBFS(true); break;

        default:
            throw std::runtime_error("Invalid traversal mode");
    }
}

template<typename D>
BSTnode<D>* BSTREE<D>::pointerIN(BSTnode<D>* root, const unsigned long int index, 
                                                         unsigned long int& count) const{
    if(!root) return nullptr;

    BSTnode<D>* left=pointerIN(root->LINK[L], index, count);  if(left) return left;
    if(count == index) return root;  count++;
    return pointerIN(root->LINK[R], index, count);
}

template<typename D>
BSTnode<D>* BSTREE<D>::pointerPRE(BSTnode<D>* root, const unsigned long int index, 
                                                          unsigned long int& count) const{
    if(!root) return nullptr;

    if(count == index) return root;  count++;
    BSTnode<D>* left = pointerPRE(root->LINK[L], index, count);  if(left) return left;
    return pointerPRE(root->LINK[R], index, count);
}

template<typename D>
BSTnode<D>* BSTREE<D>::pointerPOST(BSTnode<D>* root, const unsigned long int index, 
                                                           unsigned long int& count) const{
    if(!root) return nullptr;

    BSTnode<D>* left = pointerPOST(root->LINK[L], index, count);  if(left) return left;
    BSTnode<D>* right = pointerPOST(root->LINK[R], index, count);  if(right) return right;
    if(count == index) return root;  count++;  return nullptr;
}

template<typename D>
BSTnode<D>* BSTREE<D>::pointerBFS(const unsigned long int index, bool order) const{
    if(!ROOT) return nullptr;
    unsigned long int count=0;
    QUEUE<BSTnode<D>*> Q; Q.enqueue(ROOT);
    BSTnode<D>* tmp;
    while(!Q.empty()){
        tmp=Q.dequeue();
        if(index == count) return tmp;   count++;
        if(order){
            if(tmp->LINK[R]) Q.enqueue(tmp->LINK[R]);
            if(tmp->LINK[L]) Q.enqueue(tmp->LINK[L]);
        }else{
            if(tmp->LINK[L]) Q.enqueue(tmp->LINK[L]);
            if(tmp->LINK[R]) Q.enqueue(tmp->LINK[R]);
        }
    }
    return nullptr;
}

template<typename D>
BSTnode<D>* BSTREE<D>::pointerDFS(const unsigned long int index, bool order) const{
    if(!ROOT) return nullptr; 
    unsigned long int count=0;
    STACK<BSTnode<D>*> S; S.push(ROOT);
    BSTnode<D>* tmp;
    while(!S.empty()){
        tmp=S.pop();
        if(index == count) return tmp;   count++;
        if(order){
            if(tmp->LINK[R]) S.push(tmp->LINK[R]);
            if(tmp->LINK[L]) S.push(tmp->LINK[L]);
        }else{
            if(tmp->LINK[L]) S.push(tmp->LINK[L]);
            if(tmp->LINK[R]) S.push(tmp->LINK[R]);
        }
    }
    return nullptr;
}

template<typename D>
BSTnode<D>* BSTREE<D>::pointer(long int index, MODE mode) const{
    index = index<0 ? elem+index : index;
    if(index>=elem || index<0) return nullptr;

    unsigned long int count = 0;  if(mode == MODE::DEF) mode=M;
    switch(mode){
        case MODE::DFS: return pointerDFS(index);
        case MODE::BFS: return pointerBFS(index);

        case MODE::IN:   return pointerIN(ROOT,index,count);
        case MODE::PRE:  return pointerPRE(ROOT,index,count);
        case MODE::POST: return pointerPOST(ROOT,index,count);

        case MODE::DFS_LR: return pointerDFS(index,true);
        case MODE::BFS_RL: return pointerBFS(index,true);

        default:
            throw std::runtime_error("Invalid traversal mode");
    }
}

template<typename D>  
D& BSTREE<D>::operator[](const long int index){
    if(!ROOT) throw std::runtime_error("Tree is empty"); 

    BSTnode<D>* ptr=pointer(index);
    if(!ptr) throw std::out_of_range("Index out of bounds"); 
    return ptr->K;
}

template<typename D>  
const D& BSTREE<D>::operator[](const long int index) const{
    if(!ROOT) throw std::runtime_error("Tree is empty"); 

    const BSTnode<D>* ptr=pointer(index);
    if(!ptr) throw std::out_of_range("Index out of bounds"); 
    return ptr->K;
}

template<typename D>  
bool BSTREE<D>::deleting(BSTnode<D>*& del, BSTnode<D>* tmp){
    BSTnode<D>* ptr=del;  
    if(ptr->LINK[L]){
        tmp=ptr; ptr=ptr->LINK[L];
        while(ptr->LINK[R]){ tmp=ptr; ptr=ptr->LINK[R]; }
        del->K=ptr->K;
        return deleting(ptr,tmp);
    }
    if(ptr->LINK[R]){
        tmp=ptr; ptr=ptr->LINK[R];  
        while(ptr->LINK[L]){ tmp=ptr; ptr=ptr->LINK[L]; }
        del->K=ptr->K; 
        return deleting(ptr,tmp);
    }
    if(tmp->LINK[L] == ptr){ 
        delete[] ptr->LINK; delete ptr; tmp->LINK[L]=nullptr; elem--; 
    }else{ 
        delete[] ptr->LINK; delete ptr; tmp->LINK[R]=nullptr; elem--; 
    }
    return true;
}

template<typename D>
bool BSTREE<D>::remove(D item){
    BSTnode<D>* ptr, *tmp;
    tmp=ptr=ROOT;
    while(ptr){
        if(ptr->K!=item) tmp=ptr;
        if(item<ptr->K) ptr=ptr->LINK[L];
        else if(item>ptr->K) ptr=ptr->LINK[R];
        else break;
    } 
    if(!ptr) return false;
    if(elem == 1){
        delete[] ROOT->LINK; delete ROOT; ROOT=nullptr; elem--; return true; 
    }
    if(ptr->LINK[L]==nullptr && ptr->LINK[R]==nullptr){
        if(tmp->LINK[L] == ptr){ 
            tmp->LINK[L]=nullptr; delete[] ptr->LINK; delete ptr; elem--; 
        }else{ 
            tmp->LINK[R]=nullptr; delete[] ptr->LINK; delete ptr; elem--; 
        }
        return true;
    }
    return deleting(ptr,tmp);
}

template<typename D>
bool BSTREE<D>::freelink(BSTnode<D>*& root){
    if(!root) return false;
    QUEUE<BSTnode<D>*> Q; 
    BSTnode<D>* tmp;
        if(root->LINK[L]) Q.enqueue(root->LINK[L]);
        if(root->LINK[R]) Q.enqueue(root->LINK[R]);
    while(!Q.empty()){
        tmp=Q.dequeue();
            if(tmp->LINK[L]) Q.enqueue(tmp->LINK[L]);
            if(tmp->LINK[R]) Q.enqueue(tmp->LINK[R]);
        delete[] tmp->LINK;
        delete tmp;
    }
    root->LINK[L]=nullptr; root->LINK[R]=nullptr; 
    return true;
}

template<typename D>
bool BSTREE<D>::search(D item){
    BSTnode<D>* ptr=ROOT;
    while(ptr){ 
        if(item<ptr->K) ptr=ptr->LINK[L];
        else if(item>ptr->K) ptr=ptr->LINK[R];
        else return true;
    } 
    return false;
}

template<typename D>
BSTnode<D>* BSTREE<D>::create(D item, BSTnode<D>* parent){
    BSTnode<D>* ptr=new BSTnode<D>;
    ptr->K=item;
    if(LC==3) ptr->LINK=new BSTnode<D>*[3]{nullptr,nullptr,parent}; 
    else ptr->LINK=new BSTnode<D>*[2]{nullptr,nullptr}; 
    return ptr;
}

template<typename D>
bool BSTREE<D>::insert(D item){
    if(!ROOT){
        ROOT=create(item); elem++; return true;
    }
    BSTnode<D>* ptr, *tmp; 
    ptr=ROOT;
    while(ptr){
        tmp=ptr;
        if(item<ptr->K) ptr=ptr->LINK[L];
        else if(item>ptr->K) ptr=ptr->LINK[R];
        else return false;
    }
    if(item<tmp->K) tmp->LINK[L]=create(item,tmp); 
    else tmp->LINK[R]=create(item,tmp); elem++; 
    return true;
}

template<typename D>
BSTiterator<D> BSTREE<D>::begin() noexcept{
    BSTiterator<D> it(M,ROOT);  return ++it;
}

template<typename D>
BSTiterator<D> BSTREE<D>::end() noexcept{ return BSTiterator<D>(M,nullptr); }

template<typename D>
BSTiterator<D> BSTREE<D>::begin() const noexcept{
        BSTiterator<D> it(M,ROOT); return ++it;
}

template<typename D>
BSTiterator<D> BSTREE<D>::end() const noexcept{ return BSTiterator<D>(M,nullptr); }

template<typename D>
std::ostream& operator<<(std::ostream& out, const BSTREE<D>& BST){  BST.view(); return out;  }

#include <iostream>
using namespace std;

// int main() {

//     // BSTREE<int> tree;

//     // int arr[] = {10, 5, 20, 3, 7, 15, 30};
//     // for(int x : arr)
//     //     tree.insert(x);

//     // // two iterators from same tree
//     // auto it1 = tree.begin();
//     // auto it2 = tree.begin();

//     // std::cout << "it1: ";
//     // for(; it1 != tree.end(); ++it1)
//     //     std::cout << *it1 << " ";

//     // std::cout << "\nit2: ";
//     // for(; it2 != tree.end(); ++it2)
//     //     std::cout << *it2 << " ";

//     BSTREE<int> tree;

//     int arr[] = {10, 5, 20, 3, 7, 15, 30};
//     for(int x : arr)
//         tree.insert(x);

//     // =========================
//     // 1. INORDER
//     // =========================
//     tree.M = MODE::IN;

//     std::cout << "INORDER:\n";
//     for(auto it : tree)
//         std::cout << it << " ";
//     std::cout << "\n\n";

//     // =========================
//     // 2. PREORDER
//     // =========================
//     tree.M = MODE::PRE;

//     std::cout << "PREORDER:\n";
//     for(auto it : tree)
//         std::cout << it << " ";
//     std::cout << "\n\n";

//     // =========================
//     // 3. POSTORDER
//     // =========================
//     tree.M = MODE::POST;

//     std::cout << "POSTORDER:\n";
//     for(auto it : tree)
//         std::cout << it << " ";
//     std::cout << "\n\n";

//     // =========================
//     // 4. BFS (LEVEL ORDER)
//     // =========================
//     tree.M = MODE::BFS;

//     std::cout << "BFS:\n";
//     for(auto it : tree)
//         std::cout << it << " ";
//     std::cout << "\n\n";

//     // =========================
//     // 5. DFS (same as PREORDER usually)
//     // =========================
//     tree.M = MODE::DFS;

//     std::cout << "DFS:\n";
//     for(auto it : tree)
//         std::cout << it << " ";
//     std::cout << "\n\n";

//     // =========================
//     // 6. DFS_LR (if you support variant)
//     // =========================
//     tree.M = MODE::DFS_LR;

//     std::cout << "DFS_LR:\n";
//     for(auto it : tree)
//         std::cout << it << " ";
//     std::cout << "\n\n";

//     // =========================
//     // 7. BFS_RL (reverse level order or right-first BFS)
//     // =========================
//     tree.M = MODE::BFS_RL;

//     std::cout << "BFS_RL:\n";
//     for(auto it : tree)
//         std::cout << it << " ";
//     std::cout << "\n\n";

//     return 0;
// }


int main() {
    BSTREE<int> tree;

    std::cout << "=== INSERT TEST ===\n\n";
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);
    cout<<tree;
    std::cout << "\nTree (INORDER view):\n";
    tree.view(MODE::IN);
    std::cout << "\n\n";

    std::cout << "=== SIZE ===\n";
    std::cout << "Size: " << tree.size() << "\n\n";

    std::cout << "=== +VE INDEX TEST (INORDER) ===\n";
    std::cout << "tree[0] = " << tree[0] << "\n";
    std::cout << "tree[1] = " << tree[1] << "\n";
    std::cout << "tree[3] = " << tree[3] << "\n";
    std::cout << "tree[6] = " << tree[6] << "\n\n";

    std::cout << "=== -VE INDEX TEST (INORDER) ===\n";
    std::cout << "tree[-1] = " << tree[-1] << "\n";
    std::cout << "tree[-2] = " << tree[-2] << "\n";
    std::cout << "tree[-7] = " << tree[-7] << "\n\n";

    std::cout << "=== FRONT / BACK SIMULATION ===\n";
    std::cout << "First (tree[0]) = " << tree[0] << "\n";
    std::cout << "Last (tree[-1]) = " << tree[-1] << "\n\n";

    std::cout << "=== ITERATOR TEST (INORDER) ===\n";
    for(auto it = tree.begin(); it != tree.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n\n";

    std::cout << "=== SEARCH TEST ===\n";
    std::cout << "search(40): " << tree.search(40) << "\n";
    std::cout << "search(100): " << tree.search(100) << "\n\n";

    std::cout << "=== REMOVE TEST ===\n";
    tree.remove(30);
    tree.view(MODE::IN);
    std::cout << "\n\n";

    std::cout << "=== DFS VIEW ===\n";
    tree.view(MODE::DFS);
    std::cout << "\n\n";

    std::cout << "=== BFS VIEW ===\n";
    tree.view(MODE::BFS);
    std::cout << "\n\n";

    std::cout << "=== CONST INDEX TEST ===\n";
    const BSTREE<int>& cref = tree;
    std::cout << "cref[0] = " << cref[0] << "\n";
    std::cout << "cref[-1] = " << cref[-1] << "\n\n";

    std::cout << "=== OUT OF BOUNDS TEST ===\n";
    try {
        std::cout << tree[100] << "\n";
    } catch(const std::exception& e) {
        std::cout << "Exception: " << e.what() << "\n";
    }

    std::cout << "\n=== ALL TEST COMPLETE ===\n";

    return 0;
}

// ---- assume your full class definitions are included above ----

// -------- MAIN TEST --------
// int main() {
//     BSTREE<int> tree;

//     // Insert elements
//     tree.insert(10);
//     tree.insert(5);
//     tree.insert(15);
//     tree.insert(2);
//     tree.insert(7);

//     cout << "Tree size: " << tree.size() << endl;

//     // ---------------- INORDER ----------------
//     cout << "\nINORDER Traversal:\n";
//     tree.M = MODE::IN;

//     for(auto it = tree.begin(); it != tree.end(); ++it) {
//         cout << *it << " ";
//         cout << "IN LOOP\n";
//     }
//     cout << endl;

//     // ---------------- PREORDER ----------------
//     cout << "\nPREORDER Traversal:\n";
//     tree.M = MODE::PRE;

//     for(auto it = tree.begin(); it != tree.end(); ++it) {
//         cout << *it << " ";cout << "IN LOOP\n";
//     }
//     cout << endl;

//     // ---------------- POSTORDER ----------------
//     cout << "\nPOSTORDER Traversal:\n";
//     tree.M = MODE::POST;

//     for(auto it = tree.begin(); it != tree.end(); ++it) {
//         cout << *it << " ";cout << "IN LOOP\n";
//     }
//     cout << endl;

//     // ---------------- BFS ----------------
//     cout << "\nBFS Traversal:\n";
//     tree.M = MODE::BFS;

//     for(auto it = tree.begin(); it != tree.end(); ++it) {
//         cout << *it << " ";
//     }
//     cout << endl;

//     // ---------------- BFS_RL ----------------
//     cout << "\nBFS Right-to-Left Traversal:\n";
//     tree.M = MODE::BFS_RL;

//     for(auto it = tree.begin(); it != tree.end(); ++it) {
//         cout << *it << " ";
//     }
//     cout << endl;

//     // ---------------- DFS ----------------
//     cout << "\nDFS Traversal:\n";
//     tree.M = MODE::DFS;

//     for(auto it = tree.begin(); it != tree.end(); ++it) {
//         cout << *it << " ";
//     }
//     cout << endl;

//     // ---------------- DFS_RL ----------------
//     cout << "\nDFS Left-to-Right Traversal:\n";
//     tree.M = MODE::DFS_LR;

//     for(auto it = tree.begin(); it != tree.end(); ++it) {
//         cout << *it << " ";
//     }
//     cout << endl;cout << endl;

//     return 0;
// }

// #include <iostream>
// #include <stdexcept>

// // Assume your BSTREE and MODE are already defined

// #include <iostream>
// #include <stdexcept>

// Assume BSTREE and MODE already defined

// int main(){
//     BSTREE<int> tree;

//     // 🔹 Insert sample data
//     int arr[] = {10, 5, 20, 3, 7, 15, 30};
//     for(int x : arr){
//         tree.insert(x);
//     }

//     // ============================
//     // 🔥 VIEW TESTS
//     // ============================

//     std::cout << "\n===== VIEW TESTS =====\n";

//     tree.M = MODE::BFS;
//     std::cout << "\n--- BFS ---\n";
//     tree.view();

//     tree.M = MODE::DFS;
//     std::cout << "\n--- DFS ---\n";
//     tree.view();

//     tree.M = MODE::IN;
//     std::cout << "\n--- INORDER ---\n";
//     tree.view();

//     tree.M = MODE::PRE;
//     std::cout << "\n--- PREORDER ---\n";
//     tree.view();

//     tree.M = MODE::POST;
//     std::cout << "\n--- POSTORDER ---\n";
//     tree.view();

//     tree.M = MODE::DFS_LR;
//     std::cout << "\n--- DFS (Right->Left) ---\n";
//     tree.view();

//     tree.M = MODE::BFS_RL;
//     std::cout << "\n--- BFS (Right->Left) ---\n";
//     tree.view();


//     // ============================
//     // 🔥 POINTER / INDEX TESTS
//     // ============================

//     std::cout << "\n\n===== POINTER / INDEX TESTS =====\n";

//     tree.M = MODE::IN;
//     std::cout << "\nINORDER indexing:\n";
//     for(int i = 0; i < tree.size(); i++){
//         std::cout << "tree[" << i << "] = " << tree[i] << "\n";
//     }

//     tree.M = MODE::PRE;
//     std::cout << "\nPREORDER indexing:\n";
//     for(int i = 0; i < tree.size(); i++){
//         std::cout << "tree[" << i << "] = " << tree[i] << "\n";
//     }

//     tree.M = MODE::POST;
//     std::cout << "\nPOSTORDER indexing:\n";
//     for(int i = 0; i < tree.size(); i++){
//         std::cout << "tree[" << i << "] = " << tree[i] << "\n";
//     }

//     tree.M = MODE::BFS;
//     std::cout << "\nBFS indexing:\n";
//     for(int i = 0; i < tree.size(); i++){
//         std::cout << "tree[" << i << "] = " << tree[i] << "\n";
//     }

//     tree.M = MODE::DFS;
//     std::cout << "\nDFS indexing:\n";
//     for(int i = 0; i < tree.size(); i++){
//         std::cout << "tree[" << i << "] = " << tree[i] << "\n";
//     }


//     // ============================
//     // 🔥 NEGATIVE INDEX TEST
//     // ============================

//     std::cout << "\n\n===== NEGATIVE INDEX TEST =====\n";

//     tree.M = MODE::IN;
//     std::cout << "Last element (tree[-1]) = " << tree[-1] << "\n";
//     std::cout << "Second last (tree[-2]) = " << tree[-2] << "\n";


//     // ============================
//     // 🔥 OUT OF BOUNDS TEST
//     // ============================

//     std::cout << "\n\n===== OUT OF BOUNDS TEST =====\n";

//     try{
//         std::cout << tree[100] << "\n";   // invalid
//     }
//     catch(const std::exception& e){
//         std::cout << "Caught: " << e.what() << "\n";
//     }


//     // ============================
//     // 🔥 INVALID MODE TEST
//     // ============================

//     std::cout << "\n\n===== INVALID MODE TEST =====\n";

//     try{
//         tree.M = (MODE)'k';   // force invalid
//         tree.view();          // should throw
//     }
//     catch(const std::exception& e){
//         std::cout << "Caught: " << e.what() << "\n";
//     }

//     return 0;
// }

// #include <stdexcept>
// using namespace std;
// Assume BSTREE and BSTnode already defined

// int main(){
//     BSTREE<int> tree;

//     // Insert elements
//     int arr[] = {10, 5, 20, 3, 7, 15, 30};
//     for(int x : arr){
//         tree.insert(x);
//     }

//     std::cout << "\n--- DFS ---\n";
//     tree.view(DFS);

//     std::cout << "\n\n--- BFS ---\n";
//     tree.view(BFS);

//     std::cout << "\n\n--- INORDER ---\n";
//     tree.view(IN);

//     std::cout << "\n\n--- PREORDER ---\n";
//     tree.view(PRE);

//     std::cout << "\n\n--- POSTORDER ---\n";
//     tree.view(POST);

//     std::cout << "\n\n--- DFS Left->Right ---\n";
//     tree.view(DFS_LR);

//     std::cout << "\n\n--- BFS Right->Left ---\n";
//     tree.view(BFS_RL);

//     std::cout << "\n";

//     return 0;
// }
// #include <iostream>
// #include <utility> // for std::move

// int main(){
//     std::cout << "===== ORIGINAL TREE =====\n";
//     BSTREE<int> t1(true); // or false depending on your LC
//     t1.insert(10);
//     t1.insert(5);
//     t1.insert(20);
//     t1.insert(3);
//     t1.insert(7);

//     t1.viewBFS(false);

//     // ============================
//     // COPY CONSTRUCTOR
//     // ============================
//     std::cout << "\n===== COPY CONSTRUCTOR =====\n";
//     BSTREE<int> t2(t1);

//     std::cout << "Original (t1):\n";
//     t1.viewBFS(false);

//     std::cout << "Copied (t2):\n";
//     t2.viewBFS(false);

//     // Modify t2 to ensure deep copy
//     t2.insert(99);
//     std::cout << "\nAfter modifying t2:\n";
//     std::cout << "t1:\n"; t1.viewBFS(false);
//     std::cout << "t2:\n"; t2.viewBFS(false);

//     // ============================
//     // COPY ASSIGNMENT
//     // ============================
//     std::cout << "\n===== COPY ASSIGNMENT =====\n";
//     BSTREE<int> t3;
//     t3 = t1;

//     std::cout << "t1:\n"; t1.viewBFS(false);
//     std::cout << "t3:\n"; t3.viewBFS(false);

//     // Modify t3
//     t3.insert(77);
//     std::cout << "\nAfter modifying t3:\n";
//     std::cout << "t1:\n"; t1.viewBFS(false);
//     std::cout << "t3:\n"; t3.viewBFS(false);

//     // ============================
//     // MOVE CONSTRUCTOR
//     // ============================
//     std::cout << "\n===== MOVE CONSTRUCTOR =====\n";
//     BSTREE<int> t4(std::move(t1));

//     std::cout << "Moved-to (t4):\n";
//     t4.viewBFS(false);

//     std::cout << "Moved-from (t1):\n";
//     t1.viewBFS(false); // should be empty

//     // ============================
//     // MOVE ASSIGNMENT
//     // ============================
//     std::cout << "\n===== MOVE ASSIGNMENT =====\n";
//     BSTREE<int> t5;
//     t5 = std::move(t2);

//     std::cout << "Moved-to (t5):\n";
//     t5.viewBFS(false);

//     std::cout << "Moved-from (t2):\n";
//     t2.viewBFS(false); // should be empty

//     return 0;
// }

// int main(){
//     BSTREE<int> t;

//     int arr[] = {
//         50, 30, 70, 20, 40, 60, 80,
//         10, 25, 35, 45, 55, 65, 75, 85,
//         5, 15, 27, 33, 37, 43, 47
//     };

//     for(int x : arr) t.insert(x);

//     std::cout << "Initial Tree:\n";
//     t.view(0,0);

//     // 🔴 Now manually delete ROOT each time

//     std::cout << "\nDelete 50 (root)\n";
//     t.remove(50);
//     t.view(0,0);

//     std::cout << "\nDelete 47 (new root maybe)\n";
//     t.remove(47);
//     t.view(0,0);

//     std::cout << "\nDelete 45\n";
//     t.remove(45);
//     t.view(0,0);

//     std::cout << "\nDelete 43\n";
//     t.remove(43);
//     t.view(0,0);

//     std::cout << "\nDelete 40\n";
//     t.remove(40);
//     t.view(0,0);

//     std::cout << "\nDelete 37\n";
//     t.remove(37);
//     t.view(0,0);

//     std::cout << "\nDelete 35\n";
//     t.remove(35);
//     t.view(0,0);

//     std::cout << "\nDelete 33\n";
//     t.remove(33);
//     t.view(0,0);

//     std::cout << "\nDelete 30\n";
//     t.remove(30);
//     t.view(0,0);

//     return 0;
// }

// int main(){
//     BSTREE<int> tree;

//     // 🔹 Insert test data
//     int arr[] = {50, 30};
//     int n = sizeof(arr)/sizeof(arr[0]);

//     std::cout << "=== INSERT ===\n";
//     for(int i = 0; i < n; i++){
//         tree.insert(arr[i]);
//         std::cout << "Inserted: " << arr[i] << "\n";
//     }

//     // // 🔹 Traversal tests
//     // std::cout << "\n=== DFS (LEFT TO RIGHT) ===\n";
//     // tree.view(DFS, LR);
//     // std::cout << "======\n";
//     // std::cout << "\n=== DFS (RIGHT TO LEFT) ===\n";
//     // tree.view(DFS, RL);
//     // std::cout << "======\n";
//     // std::cout << "\n=== DFS (RL) ===\n";
//     std::cout << "\n======\n";
//     tree.view(BFS);
//     std::cout << "======\n\n";
// tree.remove(50);
//     std::cout << "\n======\n";
//     tree.view(BFS);
//     std::cout << "======\n\n";
    

//     return 0;
// }
// int main(){
//     BSTREE<int> tree(true); // with parent pointer

//     // Insert elements
//     int arr[] = {50, 30, 70, 20, 40, 60, 80, 65, 75};
//     int n = sizeof(arr)/sizeof(arr[0]);

//     for(int i = 0; i < n; i++){
//         tree.insert(arr[i]);
//     }
//     // ---------------------------
//     // BFS Tests
//     // ---------------------------
//     cout << "\n=== BFS (LEFT TO RIGHT) ===\n";
//     tree.view(BFS, LR);

//     cout << "\n\n=== BFS (RIGHT TO LEFT) ===\n";
//     tree.view(BFS, RL);

//     // ---------------------------
//     // DFS Tests
//     // ---------------------------
//     cout << "\n\n=== DFS (LEFT TO RIGHT) ===\n";
//     tree.view(DFS, LR);

//     cout << "\n\n=== DFS (RIGHT TO LEFT) ===\n";
//     tree.view(DFS, RL);

//     // ---------------------------
//     // Search Tests
//     // ---------------------------
//     cout << "\n\n=== SEARCH TEST ===\n";

//     int keys[] = {40, 65, 100};
//     for(int k : keys){
//         cout << "Search " << k << ": "
//              << (tree.search(k) ? "Found" : "Not Found") << endl;
//     }

//     return 0;
// }