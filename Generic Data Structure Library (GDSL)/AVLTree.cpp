// #include <type_traits>
// #include <cstdint>
// template<typename T>
// auto Abs(T x) {
//     static_assert(std::is_integral<T>::value, "Only integer types allowed");
//     using Bigger = std::conditional_t<
//         (sizeof(T) < sizeof(long long)),
//         long long,
//         __int128_t   // for very large types
//     >;
//     return (x < 0) ? -(Bigger)x : (Bigger)x;
// }

#include <GDSLstack.hpp>
#include <GDSLqueue.hpp>

enum class MODE :char {
    DFS='w', BFS='x', DFS_LR='y', BFS_RL='z',
    IN='a', PRE='b', POST='c',
    DEF='d'
};
enum { L, R };

template<typename D>
struct AVLnode{ unsigned int H: 7; D K; AVLnode<D>* LINK[2]; };

template<typename D>
class AVLiterator { 
    AVLnode<D>* ptr, *ROOT, *last;
    STACK<AVLnode<D>*> S;
    QUEUE<AVLnode<D>*> Q;
public:
    MODE M;
    AVLiterator(MODE mode, AVLnode<D>* p = nullptr);
    AVLnode<D>* increment();
    AVLnode<D>* incrementBFS();
    AVLnode<D>* incrementDFS();
    AVLnode<D>* incrementIN();
    AVLnode<D>* incrementPRE();
    AVLnode<D>* incrementPOST();
    D& operator*();
    const D& operator*() const;
    AVLiterator& operator++() noexcept;
    AVLiterator operator++(int) noexcept;
    bool operator!=(const AVLiterator& other) const noexcept;
    bool operator==(const AVLiterator& other) const noexcept;
    D* operator->();
    const D* operator->() const;
};

template<typename D>
AVLiterator<D>::AVLiterator(MODE mode, AVLnode<D>* p) : ptr(nullptr), last(nullptr), ROOT(p), M(mode) {
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
            AVLnode<D>* temp = ROOT;
            while(temp){
                S.push(temp);
                temp = temp->LINK[L];
            } break;
        }

        default: break;
    }
}
    
template <typename D>
AVLnode<D>* AVLiterator<D>::incrementBFS(){
    if(Q.empty()) return nullptr;
    AVLnode<D>* temp = Q.dequeue();

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
AVLnode<D>* AVLiterator<D>::incrementDFS(){
    if(S.empty()) return nullptr;
    AVLnode<D>* temp = S.pop();

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
AVLnode<D>* AVLiterator<D>::incrementIN(){
    if(S.empty()) return nullptr;
    AVLnode<D>* node = S.pop();

    AVLnode<D>* tmp = node->LINK[R];
    while(tmp){
        S.push(tmp);
        tmp = tmp->LINK[L];
    }
    return node;
}

template<typename D>
AVLnode<D>* AVLiterator<D>::incrementPRE(){
    if(S.empty()) return nullptr;
    AVLnode<D>* node = S.pop();

    if(node->LINK[R]) S.push(node->LINK[R]);
    if(node->LINK[L]) S.push(node->LINK[L]);
    return node;
}

template<typename D>
AVLnode<D>* AVLiterator<D>::incrementPOST(){
    while(!S.empty()){
        AVLnode<D>* peek = S.tos();
        AVLnode<D>* right = peek->LINK[R];

        if(right && last != right){
            AVLnode<D>* tmp = right;
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
AVLnode<D>* AVLiterator<D>::increment(){
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
D& AVLiterator<D>::operator*(){
    if(!ptr) throw std::runtime_error("Null iterator");
    return ptr->K;
}

template<typename D>
const D& AVLiterator<D>::operator*() const{
    if(!ptr) throw std::runtime_error("Null iterator");
    return ptr->K;
}

template<typename D>
AVLiterator<D>& AVLiterator<D>::operator++() noexcept{
    ptr = increment();
    return *this;
}

template<typename D>
AVLiterator<D> AVLiterator<D>::operator++(int) noexcept{
    AVLiterator<D> temp = *this; 
    ptr = increment();
    return temp;
}

template<typename D>
bool AVLiterator<D>::operator!=(const AVLiterator<D>& other) const noexcept{ return ptr != other.ptr; }

template<typename D>
bool AVLiterator<D>::operator==(const AVLiterator<D>& other) const noexcept{ return ptr == other.ptr; }

template<typename D>
D* AVLiterator<D>::operator->(){ 
    if(!ptr) throw std::runtime_error("Null iterator");
    return &(ptr->K); 
}

template<typename D>
const D* AVLiterator<D>::operator->() const{ 
    if(!ptr) throw std::runtime_error("Null iterator");
    return &(ptr->K); 
}

template<typename D>
class AVLTREE{
protected:
    unsigned long int elem;
    AVLnode<D>* ROOT;
    // AVLnode<D>* AVL, parent;
    STACK<AVLnode<D>*> S;
    AVLnode<D>* node[3];
    AVLnode<D>* link[4];
    AVLnode<D>* create(D item);
    void print_Key_L_C_R(const AVLnode<D>* tmp) const;
    bool deleting(AVLnode<D>*& del, AVLnode<D>* tmp);
    bool freelink(AVLnode<D>*& root);
    unsigned long int addlink(AVLnode<D>*& root, const AVLnode<D>*& other);
    AVLnode<D>* pointer(long int index, MODE mode=MODE::DEF) const;
    AVLnode<D>* pointerBFS(const unsigned long int index, bool order=false) const;
    AVLnode<D>* pointerDFS(const unsigned long int index, bool order=false) const;
    AVLnode<D>* pointerIN(AVLnode<D>* root, const unsigned long int index, unsigned long int& count) const;
    AVLnode<D>* pointerPRE(AVLnode<D>* root, const unsigned long int index, unsigned long int& count) const;
    AVLnode<D>* pointerPOST(AVLnode<D>* root, const unsigned long int index, unsigned long int& count) const;
public:
    MODE M;
    AVLTREE();
    AVLTREE(const AVLTREE<D>& other);
    AVLTREE(AVLTREE<D>&& other) noexcept;
    AVLTREE& operator=(const AVLTREE& other);
    AVLTREE& operator=(AVLTREE&& other) noexcept;
    D& operator[](const long int index);
    const D& operator[](const long int index) const;
    long int size() const { return elem; }
    bool insert(D item);
    bool search(D item);
    bool remove(D item);
    bool add(const AVLTREE<D>& root);
    void view(MODE mode=MODE::DEF);
    void viewDFS(bool order=false);
    void viewBFS(bool order=false);
    void viewIN(const AVLnode<D>* root) const;
    void viewPRE(const AVLnode<D>* root) const;
    void viewPOST(const AVLnode<D>* root) const;
    AVLiterator<D> begin() noexcept;
    AVLiterator<D> begin() const noexcept;
    AVLiterator<D> end() noexcept;
    AVLiterator<D> end() const noexcept;
    ~AVLTREE();
//-------------------BALANCE_TREE
    char subH(AVLnode<D>* sub) const noexcept;
    char balanceH(AVLnode<D>* subL, AVLnode<D>* subR) const noexcept;
    void tree_balance() noexcept;
    void balance(AVLnode<D>*& AVL, AVLnode<D>* parent);
};

template<typename D>
AVLTREE<D>::AVLTREE() : ROOT(nullptr),M(MODE::IN), elem(0) {}

template<typename D>
AVLTREE<D>::AVLTREE(const AVLTREE<D>& other) :AVLTREE<D>(){
    M=other.M;
    if(!other.ROOT) return; 
    QUEUE<AVLnode<D>*> Q; 
    AVLnode<D>* tmp;
    Q.enqueue(other.ROOT);
    while(!Q.empty()){
        tmp=Q.dequeue();
            if(tmp->LINK[L]) Q.enqueue(tmp->LINK[L]);
            if(tmp->LINK[R]) Q.enqueue(tmp->LINK[R]);
        insert(tmp->K);
    }
}

template<typename D>
AVLTREE<D>::AVLTREE(AVLTREE<D>&& other) noexcept :ROOT(other.ROOT), elem(other.elem), M(other.M){
    other.ROOT=nullptr;
    other.elem=0;
}

template<typename D>
AVLTREE<D>& AVLTREE<D>::operator=(const AVLTREE<D>& other){
    if(this == &other) return *this;

    freelink(ROOT); if(ROOT){ delete ROOT; ROOT=nullptr; } 
    elem=0; 
    if(!other.ROOT) return *this;
    
    QUEUE<AVLnode<D>*> Q; 
    AVLnode<D>* tmp;
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
AVLTREE<D>& AVLTREE<D>::operator=(AVLTREE<D>&& other) noexcept{
    if(this == &other) return *this;

    freelink(ROOT); if(ROOT){ delete ROOT; ROOT=nullptr; } 
    elem=0; 
    if(!other.ROOT) return *this;

    ROOT=other.ROOT; elem=other.elem;
    other.ROOT=nullptr; other.elem=0;
    return *this;
}

template<typename D>
AVLTREE<D>::~AVLTREE(){ 
    if(ROOT){ freelink(ROOT); delete ROOT; ROOT=nullptr; } 
}

template<typename D>
unsigned long int AVLTREE<D>::addlink(AVLnode<D>*& root, const AVLnode<D>*& other){
    if(!root || !other) return 0;
    QUEUE<const AVLnode<D>*> Q; 
    AVLnode<D>* ptr, *tmp, *key; D item; unsigned long int count=0;
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
        if(item<tmp->K) tmp->LINK[L]=create(item); 
        else tmp->LINK[R]=create(item); 
        elem++; count++;
    }
    return count;
}

template<typename D>
bool AVLTREE<D>::add(const AVLTREE<D>& root){
    if(this == &root) return false;
    if(!root.ROOT) return false;
    QUEUE<AVLnode<D>*> Q; 
    AVLnode<D>* tmp;
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
void AVLTREE<D>::print_Key_L_C_R(const AVLnode<D>* tmp) const{
    if(tmp->LINK[L]) std::cout<<tmp->LINK[L]->K<<"<-";
    else std::cout<<"NULL<-"; 
    std::cout<<"["<<tmp->K<<"]";
    if(tmp->LINK[R]) std::cout<<"->"<<tmp->LINK[R]->K;
    else std::cout<<"->NULL"; 
}

template<typename D>
void AVLTREE<D>::viewBFS(bool order){
    if(!ROOT){ std::cout<<"Tree is empty"; return; }
    QUEUE<AVLnode<D>*> Q; 
    AVLnode<D>* tmp;
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
void AVLTREE<D>::viewDFS(bool order){
    if(!ROOT){ std::cout<<"Tree is empty"; return; }
    STACK<AVLnode<D>*> S; 
    AVLnode<D>* tmp;
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
void AVLTREE<D>::viewIN(const AVLnode<D>* root) const{
    if(!root) return;

    viewIN(root->LINK[L]);  print_Key_L_C_R(root); std::cout<<"\n";  viewIN(root->LINK[R]);
}

template<typename D>
void AVLTREE<D>::viewPRE(const AVLnode<D>* root) const{
    if(!root) return;

    print_Key_L_C_R(root); std::cout<<"\n";  viewPRE(root->LINK[L]);  viewPRE(root->LINK[R]);
}

template<typename D>
void AVLTREE<D>::viewPOST(const AVLnode<D>* root) const{
    if(!root) return;

    viewPOST(root->LINK[L]);  viewPOST(root->LINK[R]);  print_Key_L_C_R(root); std::cout<<"\n";
}

template<typename D>
void AVLTREE<D>::view(MODE mode){
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
AVLnode<D>* AVLTREE<D>::pointerIN(AVLnode<D>* root, const unsigned long int index, 
                                                          unsigned long int& count) const{
    if(!root) return nullptr;

    AVLnode<D>* left=pointerIN(root->LINK[L], index, count);  if(left) return left;
    if(count == index) return root;  count++;
    return pointerIN(root->LINK[R], index, count);
}

template<typename D>
AVLnode<D>* AVLTREE<D>::pointerPRE(AVLnode<D>* root, const unsigned long int index, 
                                                           unsigned long int& count) const{
    if(!root) return nullptr;

    if(count == index) return root;  count++;
    AVLnode<D>* left = pointerPRE(root->LINK[L], index, count);  if(left) return left;
    return pointerPRE(root->LINK[R], index, count);
}

template<typename D>
AVLnode<D>* AVLTREE<D>::pointerPOST(AVLnode<D>* root, const unsigned long int index, 
                                                            unsigned long int& count) const{
    if(!root) return nullptr;

    AVLnode<D>* left = pointerPOST(root->LINK[L], index, count);  if(left) return left;
    AVLnode<D>* right = pointerPOST(root->LINK[R], index, count);  if(right) return right;
    if(count == index) return root;  count++;  return nullptr;
}

template<typename D>
AVLnode<D>* AVLTREE<D>::pointerBFS(const unsigned long int index, bool order) const{
    if(!ROOT) return nullptr;
    unsigned long int count=0;
    QUEUE<AVLnode<D>*> Q; Q.enqueue(ROOT);
    AVLnode<D>* tmp;
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
AVLnode<D>* AVLTREE<D>::pointerDFS(const unsigned long int index, bool order) const{
    if(!ROOT) return nullptr; 
    unsigned long int count=0;
    STACK<AVLnode<D>*> S; S.push(ROOT);
    AVLnode<D>* tmp;
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
AVLnode<D>* AVLTREE<D>::pointer(long int index, MODE mode) const{
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
D& AVLTREE<D>::operator[](const long int index){
    if(!ROOT) throw std::runtime_error("Tree is empty"); 

    AVLnode<D>* ptr=pointer(index);
    if(!ptr) throw std::out_of_range("Index out of bounds"); 
    return ptr->K;
}

template<typename D>  
const D& AVLTREE<D>::operator[](const long int index) const{
    if(!ROOT) throw std::runtime_error("Tree is empty"); 

    const AVLnode<D>* ptr=pointer(index);
    if(!ptr) throw std::out_of_range("Index out of bounds"); 
    return ptr->K;
}

template<typename D>  
bool AVLTREE<D>::deleting(AVLnode<D>*& del, AVLnode<D>* tmp){
    AVLnode<D>* ptr=del;  
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
        delete ptr; tmp->LINK[L]=nullptr; elem--; 
    }else{ 
        delete ptr; tmp->LINK[R]=nullptr; elem--; 
    }
    return true;
}

template<typename D>
bool AVLTREE<D>::remove(D item){
    AVLnode<D>* ptr, *tmp;
    tmp=ptr=ROOT;
    while(ptr){
        if(ptr->K!=item) tmp=ptr;
        if(item<ptr->K) ptr=ptr->LINK[L];
        else if(item>ptr->K) ptr=ptr->LINK[R];
        else break;
    } 
    if(!ptr) return false;
    if(elem == 1){
        delete ROOT; ROOT=nullptr; elem--; return true; 
    }
    if(ptr->LINK[L]==nullptr && ptr->LINK[R]==nullptr){
        if(tmp->LINK[L] == ptr){ 
            tmp->LINK[L]=nullptr; delete ptr; elem--; 
        }else{ 
            tmp->LINK[R]=nullptr; delete ptr; elem--; 
        }
        return true;
    }
    return deleting(ptr,tmp);
}

template<typename D>
bool AVLTREE<D>::freelink(AVLnode<D>*& root){
    if(!root) return false;
    QUEUE<AVLnode<D>*> Q; 
    AVLnode<D>* tmp;
        if(root->LINK[L]) Q.enqueue(root->LINK[L]);
        if(root->LINK[R]) Q.enqueue(root->LINK[R]);
    while(!Q.empty()){
        tmp=Q.dequeue();
            if(tmp->LINK[L]) Q.enqueue(tmp->LINK[L]);
            if(tmp->LINK[R]) Q.enqueue(tmp->LINK[R]);
        delete tmp;
    }
    root->LINK[L]=nullptr; root->LINK[R]=nullptr; 
    return true;
}

template<typename D>
bool AVLTREE<D>::search(D item){
    AVLnode<D>* ptr=ROOT;
    while(ptr){ 
        if(item<ptr->K) ptr=ptr->LINK[L];
        else if(item>ptr->K) ptr=ptr->LINK[R];
        else return true;
    } 
    return false;
}

template<typename D>
AVLnode<D>* AVLTREE<D>::create(D item){
    AVLnode<D>* ptr=new AVLnode<D>;
    ptr->H=0;
    ptr->K=item;
    ptr->LINK[L]=nullptr; ptr->LINK[R]=nullptr; 
    return ptr;
}

// template<typename D>
// bool AVLTREE<D>::insert(D item){
//     if(!ROOT){
//         ROOT=create(item); elem++; return true;
//     }
//     AVLnode<D>* ptr, *tmp; 
//     ptr=ROOT;
//     while(ptr){
//         tmp=ptr;
//         if(item<ptr->K) ptr=ptr->LINK[L];
//         else if(item>ptr->K) ptr=ptr->LINK[R];
//         else return false;
//     }
//     if(item<tmp->K) tmp->LINK[L]=create(item); 
//     else tmp->LINK[R]=create(item); elem++; 
//     return true;
// }

template<typename D>
AVLiterator<D> AVLTREE<D>::begin() noexcept{
    AVLiterator<D> it(M,ROOT);  return ++it;
}

template<typename D>
AVLiterator<D> AVLTREE<D>::end() noexcept{ return AVLiterator<D>(M,nullptr); }

template<typename D>
AVLiterator<D> AVLTREE<D>::begin() const noexcept{
        AVLiterator<D> it(M,ROOT);  return ++it;
}

template<typename D>
AVLiterator<D> AVLTREE<D>::end() const noexcept{ return AVLiterator<D>(M,nullptr); }

template<typename D>
char AVLTREE<D>::subH(AVLnode<D>* sub) const noexcept{ if(!sub) return 0;   return sub->H + 1; }

template<typename D>
char AVLTREE<D>::balanceH(AVLnode<D>* subL, AVLnode<D>* subR) const noexcept{
    char leftH = subH(subL), rightH = subH(subR);
    char balance = leftH-rightH;
    if(balance<2 && balance>-2) return (leftH > rightH ? leftH : rightH);
    return -1;
}

template<typename D>
void AVLTREE<D>::tree_balance() noexcept{
    AVLnode<D>* tmp, *AVL=nullptr;
    char height;
    while(!S.empty()){
        tmp=S.pop();
        height=balanceH(tmp->LINK[L],tmp->LINK[R]);
        if(-1 == height){ AVL=tmp;
                          balance(AVL,!S.empty() ? S.tos() : nullptr); break; }
        else tmp->H=height;
    } S.clear();
}

template<typename D>
void AVLTREE<D>::balance(AVLnode<D>*& AVL, AVLnode<D>* parent){ 
    if(subH(AVL->LINK[L]) > subH(AVL->LINK[R])){  // if(AVL->H > 0)
        node[2]=AVL; link[3]=AVL->LINK[R]; 
        AVLnode<D>* left=AVL->LINK[L];
        if(subH(left->LINK[L]) < subH(left->LINK[R])){  // if(left->H > 0)
            node[0]=left; link[0]=left->LINK[L];
            node[1]=left->LINK[R];
            link[1]=node[1]->LINK[L]; link[2]=node[1]->LINK[R];  //1
        }
        else if(subH(left->LINK[L]) > subH(left->LINK[R])){  // else if(left->H < 0)
            node[1]=left; link[2]=left->LINK[R];
            node[0]=left->LINK[L];
            link[0]=node[0]->LINK[L]; link[1]=node[0]->LINK[R];  //2
        }
    }
    else if(subH(AVL->LINK[L]) < subH(AVL->LINK[R])){  // else if(AVL->H < 0)
        node[0]=AVL; link[0]=AVL->LINK[L];  
        AVLnode<D>* right=AVL->LINK[R];
        if(subH(right->LINK[L]) < subH(right->LINK[R])){  // if(right->H > 0)
            node[1]=right; link[1]=right->LINK[L];  
            node[2]=right->LINK[R];
            link[2]=node[2]->LINK[L]; link[3]=node[2]->LINK[R];  //3
        }
        else if(subH(right->LINK[L]) > subH(right->LINK[R])){  // else if(right->H < 0)
            node[2]=right; link[3]=right->LINK[R];
            node[1]=right->LINK[L];
            link[1]=node[1]->LINK[L]; link[2]=node[1]->LINK[R];  //4
        } 
    }
    node[1]->LINK[L]=node[0];   node[1]->LINK[R]=node[2];

    node[0]->LINK[L]=link[0];   node[2]->LINK[L]=link[2];
    node[0]->LINK[R]=link[1];   node[2]->LINK[R]=link[3];

    node[0]->H=balanceH(node[0]->LINK[L],node[0]->LINK[R]);
    node[2]->H=balanceH(node[2]->LINK[L],node[2]->LINK[R]);
    node[1]->H=balanceH(node[1]->LINK[L],node[1]->LINK[R]);

    if(parent){
        if(parent->K > node[1]->K) parent->LINK[L]=node[1];
        else if(parent->K < node[1]->K) parent->LINK[R]=node[1];
    } 
    else ROOT=node[1];
}

template<typename D>
bool AVLTREE<D>::insert(D item){
    if(!ROOT){
        ROOT=create(item); elem++; return true;
    }
    AVLnode<D>* ptr, *tmp;
    ptr=ROOT; S.push(ROOT);
    while(ptr){
        tmp=ptr;
        if(item<ptr->K){ ptr=ptr->LINK[L];
                         if(ptr) S.push(ptr); }
        else if(item>ptr->K){ ptr=ptr->LINK[R];
                              if(ptr) S.push(ptr); }
        else{ S.clear(); return false; }
    }
    if(item<tmp->K) tmp->LINK[L]=create(item); 
    else tmp->LINK[R]=create(item); elem++; 
    tree_balance();
    return true;
}

#include <iostream>
using namespace std;
int main() {

    AVLTREE<int> tree;
    int arr[] = {
        50,20,70,10,30,60,80,
        25,27,26,5,1,2,3,4,
        90,100,95,85,75
    };  
    int arr[] = {14, 17, 11, 7, 53, 4, 13, 12, 8, 60, 19, 16, 20};
    for(int x : arr){
        cout<<x<<"-------------------\n";
        tree.insert(x); tree.view(MODE::BFS);
    }

// cout<<"-------------------\n";
//     AVLTREE<int> tree1;// Tree 1
//     int arr1[] = {4, 2, 8, 1, 3, 6, 10, 5, 7, 11, 12};
//     for(int x : arr1) tree1.insert(x); 
//     tree1.view(MODE::BFS);
// cout<<"-------------------\n";
//     AVLTREE<int> tree2;// Tree 2
//     int arr2[] = {9, 5, 11, 3, 7, 10, 12, 2, 4, 6, 8, 1};
//     for(int x : arr2) tree2.insert(x); 
//     tree2.view(MODE::BFS);
// cout<<"-------------------\n";
//     AVLTREE<int> tree3;// Tree 3
//     int arr3[] = {23, 20, 30, 10, 22, 25, 40, 24, 35};
//     for(int x : arr3) tree3.insert(x); 
//     tree3.view(MODE::BFS);
// cout<<"-------------------\n";



    // AVLTREE<int> tree;

    // int arr[] = {10, 5, 20, 3, 7, 15, 30};
    // for(int x : arr)
    //     tree.insert(x);

    // // two iterators from same tree
    // auto it1 = tree.begin();
    // auto it2 = tree.begin();

    // std::cout << "it1: ";
    // for(; it1 != tree.end(); ++it1)
    //     std::cout << *it1 << " ";

    // std::cout << "\nit2: ";
    // for(; it2 != tree.end(); ++it2)
    //     std::cout << *it2 << " ";


    // =========================
    // 1. INORDER
    // =========================
    // tree.M = MODE::IN;

    // std::cout << "INORDER:\n";
    // for(auto it : tree)
    //     std::cout << it << " ";
    // std::cout << "\n\n";

    // // =========================
    // // 2. PREORDER
    // // =========================
    // tree.M = MODE::PRE;

    // std::cout << "PREORDER:\n";
    // for(auto it : tree)
    //     std::cout << it << " ";
    // std::cout << "\n\n";

    // // =========================
    // // 3. POSTORDER
    // // =========================
    // tree.M = MODE::POST;

    // std::cout << "POSTORDER:\n";
    // for(auto it : tree)
    //     std::cout << it << " ";
    // std::cout << "\n\n";

    // // =========================
    // // 4. BFS (LEVEL ORDER)
    // // =========================
    // tree.M = MODE::BFS;

    // std::cout << "BFS:\n";
    // for(auto it : tree)
    //     std::cout << it << " ";
    // std::cout << "\n\n";

    // // =========================
    // // 5. DFS (same as PREORDER usually)
    // // =========================
    // tree.M = MODE::DFS;

    // std::cout << "DFS:\n";
    // for(auto it : tree)
    //     std::cout << it << " ";
    // std::cout << "\n\n";

    // // =========================
    // // 6. DFS_LR (if you support variant)
    // // =========================
    // tree.M = MODE::DFS_LR;

    // std::cout << "DFS_LR:\n";
    // for(auto it : tree)
    //     std::cout << it << " ";
    // std::cout << "\n\n";

    // // =========================
    // // 7. BFS_RL (reverse level order or right-first BFS)
    // // =========================
    // tree.M = MODE::BFS_RL;

    // std::cout << "BFS_RL:\n";
    // for(auto it : tree)
    //     std::cout << it << " ";
    // std::cout << "\n\n";

    return 0;
}


//--------------------------------------------------------
//--------------------------------------------------------
// #include "GDSL/include/Non Linear/Tree/BinarySearchTree.hpp"
// #include <GDSLstack.hpp>
// #include <GDSLqueue.hpp>

// template<typename D>
// class AVLTREE: public BSTREE<D>{
//     int H: 3;
//     STACK<AVLnode<D>*> S;
// public:
//     AVLTREE();
//     bool insert(D item);
//     AVLnode<D>* create(D item);  // , AVLnode<D>* parent=nullptr
//     AVLnode<D>* balance_factor();
//     void balance_tree(AVLnode<D>* AVL);
// };

// template<typename D>
// AVLTREE<D>::AVLTREE() :AVLTREE<D>() {}

// template<typename D>
// AVLTREE<D>::create(D item){ // , AVLnode<D>* parent
//     AVLnode<D>* ptr=new AVLnode<D>;
//     ptr->K=item;
//     // if(LC==3) ptr->LINK=new AVLnode<D>*[3]{nullptr,nullptr,parent}; 
//     // else 
//     ptr->LINK=new AVLnode<D>*[2]{nullptr,nullptr}; 
//     return ptr;
// }

// template<typename D>
// bool AVLTREE<D>::insert(D item){
//     if(!ROOT){
//         ROOT=create(item); elem++; return true;
//     }
//     AVLnode<D>* ptr, *tmp;
//     ptr=ROOT; S.push(ROOT);
//     while(ptr){
//         tmp=ptr;
//         if(item<ptr->K){ ptr=ptr->LINK[L];
//                          if(ptr) S.push(ptr) }
//         else if(item>ptr->K){ ptr=ptr->LINK[R];
//                               if(ptr) S.push(ptr) }
//         else{ S.clear(); return false; }
//     }
//     if(item<tmp->K) tmp->LINK[L]=create(item,tmp); 
//     else tmp->LINK[R]=create(item,tmp); elem++; 
//     balance_factor();
//     balance();
//     return true;
// }

// // #include <type_traits>
// // #include <cstdint>
// // template<typename T>
// // auto Abs(T x) {
// //     static_assert(std::is_integral<T>::value, "Only integer types allowed");
// //     using Bigger = std::conditional_t<
// //         (sizeof(T) < sizeof(long long)),
// //         long long,
// //         __int128_t   // for very large types
// //     >;
// //     return (x < 0) ? -(Bigger)x : (Bigger)x;
// // }

// template<typename D>
// AVLnode<D>* AVLTREE<D>::balance_factor(){
//     AVLnode<D>* tmp, AVL=nullptr; bool f=true;
//     while(!S.empty()){
//         tmp=S.pop();
//         char left = tmp->LINK[L]? Abs(tmp->LINK[L]->H) + 1 : 0;
//         char right = tmp->LINK[R]? Abs(tmp->LINK[R]->H) + 1 : 0;
//         tmp->H = left-right;
//         if(f && (tmp->H > 1 && tmp->H < -1)){ AVL=tmp; f=false; }
//     }
//     return AVL;
// }

// AVLnode<D>* node[3];
// AVLnode<D>* link[4];
// template<typename D>
// void AVLTREE<D>::balance_tree(AVLnode<D>* AVL){
//     if(AVL->H > 0){ 
//         node[2]=AVL; link[3]=AVL->LINK[R]; 
//         AVLnode<D>* left=AVL->LINK[L];
//         if(left->H > 0){
//             node[1]=left; link[2]=left->LINK[R]; //2
//             node[0]=left->LINK[L];
//             link[0]=node[0]->LINK[L]; link[1]=node[0]->LINK[r];
//         }
//         else if(left->H < 0){ 
//             node[0]=left; link[0]=left->LINK[L]; //1
//             node[1]=left->LINK[R];
//             link[1]=node[1]->LINK[L]; link[2]=node[1]->LINK[r];
//         }
//     }
//     else if(AVL->H < 0){
//         node[0]=AVL; link[0]=AVL->LINK[L];
//         AVLnode<D>* right=AVL->LINK[R];
//         if(right->H > 0){ 
//             node[2]=right; link[3]=right->LINK[R]; //4
//             node[1]=right->LINK[L];
//             link[1]=node[1]->LINK[L]; link[2]=node[1]->LINK[r];
//         }
//         else if(right->H < 0){ 
//             node[1]=right; link[1]=right->LINK[L]; //3
//             node[2]=right->LINK[R];
//             link[2]=node[2]->LINK[L]; link[3]=node[2]->LINK[r];
//         }
//     }
// }

// using namespace std;
// int main(){
    
//     return 0;
// }