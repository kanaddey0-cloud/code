#include <GDSLstack.hpp>
#include <GDSLqueue.hpp>

enum class MODE :char {
    DFS='w', BFS='x', DFS_LR='y', BFS_RL='z',
    IN='a', PRE='b', POST='c',
    DEF='d'
}; 
enum { L, R };

template<typename D>
struct AVLnode{ int H: 8; D K; AVLnode<D>* LINK[2]; };

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
    AVLnode<D>* ROOT, *AVL;
    bool f0=false;
    AVLnode<D>* node[3];
    AVLnode<D>* link[4];
    AVLnode<D>* create(D item);
    void print_Key_L_C_R(const AVLnode<D>* tmp) const;
    D deleting(AVLnode<D>* point, bool f1, bool f2=false);
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
    bool search(D item);
    void insert(D item);
    bool insert_(D item, AVLnode<D>* root);
    bool remove(D item);
    bool remove_(D item, AVLnode<D>* root);
    bool add(const AVLTREE<D>& root);
    void view(MODE mode=MODE::DEF) const;
    void viewDFS(bool order=false) const;
    void viewBFS(bool order=false) const;
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
    AVLnode<D>* balance(AVLnode<D>* AVL);
};

template<typename D>
AVLTREE<D>::AVLTREE() : ROOT(nullptr), AVL(nullptr), M(MODE::IN), elem(0) {}

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
void AVLTREE<D>::viewBFS(bool order) const{
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
void AVLTREE<D>::viewDFS(bool order) const{
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
void AVLTREE<D>::view(MODE mode) const{
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
char AVLTREE<D>::subH(AVLnode<D>* sub) const noexcept{ if(!sub) return 0;   return 1+ sub->H; }

template<typename D>
char AVLTREE<D>::balanceH(AVLnode<D>* subL, AVLnode<D>* subR) const noexcept{
    char leftH = subH(subL), rightH = subH(subR);
    char balance = leftH-rightH;
    if(balance<2 && balance>-2) return (leftH > rightH ? leftH : rightH);
    return -1;
}

template<typename D>
AVLnode<D>* AVLTREE<D>::balance(AVLnode<D>* AVL){ 
    if(subH(AVL->LINK[L]) > subH(AVL->LINK[R])){  // if(AVL->H > 0)
        node[2]=AVL; link[3]=AVL->LINK[R]; 
        AVLnode<D>* left=AVL->LINK[L];
        if(subH(left->LINK[L]) < subH(left->LINK[R])){  // if(left->H > 0)
            node[0]=left; link[0]=left->LINK[L];
            node[1]=left->LINK[R];
            link[1]=node[1]->LINK[L]; link[2]=node[1]->LINK[R];  //1
        }
        else if(subH(left->LINK[L]) >= subH(left->LINK[R])){  // else if(left->H < 0)
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
        else if(subH(right->LINK[L]) >= subH(right->LINK[R])){  // else if(right->H < 0)
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

    return node[1];
}

template<typename D> 
D AVLTREE<D>::deleting(AVLnode<D>* point, bool f1, bool f2){  D tmp;
    if(f1){
        if(f2){
            if(point->LINK[R]){
                tmp=deleting(point->LINK[R],true,true);
                if(f0){
                    delete point->LINK[R]; point->LINK[R]=nullptr; f0=false; elem--;
                }else{
                    if(AVL) point->LINK[R]=AVL; AVL=nullptr; 
                }
            }else return deleting(point,false);
        }else{
            if(point->LINK[L]){
                tmp=deleting(point->LINK[L],true);
                if(f0){
                    delete point->LINK[L]; point->LINK[L]=nullptr; f0=false; elem--;
                }else{
                    if(AVL) point->LINK[L]=AVL; AVL=nullptr;
                }
            }else return deleting(point,false);
        }
        point->H=balanceH(point->LINK[L],point->LINK[R]);
        if(-1 == point->H) AVL=balance(point); 
        return tmp;

    }else{
        if(!point->LINK[L] && !point->LINK[R]){ f0=true; return point->K; }
        else if(point->LINK[L] && !point->LINK[R]){
            point->K=point->LINK[L]->K;
            delete point->LINK[L]; point->LINK[L]=nullptr; elem--;
        }
        else if(!point->LINK[L] && point->LINK[R]){
            point->K=point->LINK[R]->K;
            delete point->LINK[R]; point->LINK[R]=nullptr; elem--;
        }
        else{
            if(subH(point->LINK[L]) >= subH(point->LINK[R])){
                if(point->LINK[L]->LINK[R]){
                    point->K=deleting(point->LINK[L]->LINK[R],true,true);
                    if(f0){  
                        delete point->LINK[L]->LINK[R]; point->LINK[L]->LINK[R]=nullptr; f0=false; elem--;
                    }
                    point->LINK[L]->H=balanceH(point->LINK[L]->LINK[L],point->LINK[L]->LINK[R]);
                    if(-1 == point->LINK[L]->H) 
                        point->LINK[L]=balance(point->LINK[L]);
                }else{
                    point->K=deleting(point->LINK[L],false);
                    if(f0){  
                        delete point->LINK[L]; point->LINK[L]=nullptr; f0=false; elem--;
                    }
                }
            }else{
                if(point->LINK[R]->LINK[L]){
                    point->K=deleting(point->LINK[R]->LINK[L],true);
                    if(f0){  
                        delete point->LINK[R]->LINK[L]; point->LINK[R]->LINK[L]=nullptr; f0=false;  elem--;
                    }
                    point->LINK[R]->H=balanceH(point->LINK[R]->LINK[L],point->LINK[R]->LINK[R]);
                    if(-1 == point->LINK[R]->H) 
                        point->LINK[R]=balance(point->LINK[R]);
                }else{
                    point->K=deleting(point->LINK[R],false);
                    if(f0){  
                        delete point->LINK[R]; point->LINK[R]=nullptr; f0=false; elem--;
                    }
                }
            }
        }
        point->H=balanceH(point->LINK[L],point->LINK[R]);
        if(-1 == point->H) AVL=balance(point);
        return point->K;
    }
}

template<typename D>
bool AVLTREE<D>::remove_(D item, AVLnode<D>* root){
    if(!root) std::cout<<root->K<<"\n";
    if(root->K > item){  
        if(root->LINK[L]){
            if(remove_(item,root->LINK[L])){ delete root->LINK[L]; root->LINK[L]=nullptr; elem--;}
            else if(AVL){
                root->LINK[L]=AVL; AVL=nullptr;
            }
        }else return false;

    }else if(root->K < item){ 
        if(root->LINK[R]){
            if(remove_(item,root->LINK[R])){ delete root->LINK[R]; root->LINK[R]=nullptr; elem--; }
            else if(AVL){
                root->LINK[R]=AVL; AVL=nullptr;
            }
        }else return false;

    }else{  
        deleting(root,false); 
        if(f0) return true;   f0=true;  
    }
    
    if(f0){
        root->H=balanceH(root->LINK[L],root->LINK[R]); 
        if(-1 == root->H)
            AVL=balance(root); 
    }return false;  
}

template<typename D>
bool AVLTREE<D>::remove(D item){
    if(!ROOT) return false;
    if(ROOT->K == item){
        deleting(ROOT,false);
        if(f0){ delete ROOT; ROOT=nullptr; f0=false; elem--; }
        else if(AVL){ ROOT=AVL; AVL=nullptr; }
    }else{
        remove_(item,ROOT); f0=false;
        if(AVL){ ROOT=AVL; AVL=nullptr; }
    }   
    return false; 
}

template<typename D>
AVLnode<D>* AVLTREE<D>::create(D item){  elem++;
    AVLnode<D>* ptr=new AVLnode<D>;

    ptr->H=0; ptr->K=item;
    ptr->LINK[L]=nullptr; ptr->LINK[R]=nullptr; 

    return ptr;
}

template<typename D>
bool AVLTREE<D>::insert_(D item, AVLnode<D>* root){
    if(root->K > item){
        if(!root->LINK[L]){
            root->LINK[L]=create(item); 
            root->H=balanceH(root->LINK[L],root->LINK[R]); 
            return true;
        }else{
            if(insert_(item,root->LINK[L])) root->H=balanceH(root->LINK[L],root->LINK[R]);
            else if(AVL){
                if(root->K > AVL->K) root->LINK[L]=AVL;
                else root->LINK[R]=AVL;
                AVL=nullptr; return false;
            }else return false;
        }
    }else if(root->K < item){
        if(!root->LINK[R]){
            root->LINK[R]=create(item);
            root->H=balanceH(root->LINK[L],root->LINK[R]);  
            return true;
        }else{
            if(insert_(item,root->LINK[R])) root->H=balanceH(root->LINK[L],root->LINK[R]);
            else if(AVL){
                if(root->K > AVL->K) root->LINK[L]=AVL;
                else root->LINK[R]=AVL;
                AVL=nullptr; return false;
            }else return false;
        }
    }else return false;

    if(-1 != root->H) return true; 
    AVL=balance(root);  return false;
}

template<typename D>
void AVLTREE<D>::insert(D item){ 
    if(!ROOT){ ROOT=create(item); }
    else{
        insert_(item,ROOT);
        if(AVL){
            ROOT=AVL; AVL=nullptr;
        }
    } 
}

template<typename D>
std::ostream& operator<<(std::ostream& out, const AVLTREE<D>& AVL){  AVL.view(); return out;  }

#include <iostream>
#include <chrono>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace std::chrono;

// #include "AVLTree.h"   // IMPORTANT: add your AVL definition here

// int main() {

//     cout << "Program started\n";

//     srand(time(0));

//     auto start = high_resolution_clock::now();

//     AVLTREE<int> tree;

//     int n = 1000000;

// cout << "S\n";

//     for(int i = 0; i < n; i++){
//         tree.insert(i);
//         // if(i % 1000 == 0) cout << "Inserted " << i << endl;
//     }

// cout << "I\n";

// //     for(int i = 0; i < n/2; i++){
// //         tree.remove(i);
// //         // cout<<"|";
// //     }

// // cout << "D\n";

//     auto end = high_resolution_clock::now();

//     cout << duration_cast<milliseconds>(end - start).count() << " ms\n";

//     cout << "Program finished\n";

//     return 0;
// }

// int main() {

//INSERT
//---------------------------------------------

//     AVLTREE<int> tree;
// int arr[] = {14, 17, 11, 7, 53, 4, 13, 12, 8, 60, 19, 16, 20};
// for(int x : arr){
//     cout << x << "-----------------\n";
//     tree.insert(x);
//     tree.view(MODE::BFS);
// }
// cout << "\n===== DELETION START =====\n";
// // test deletions (mix of leaf, one-child, two-child)
// int delArr[] = {8, 7, 11, 14, 53};
// for(int x : delArr){
//     cout << x << " (DELETE) -----------------\n";
//     tree.remove(x);
//     tree.view(MODE::BFS);
// }

// cout<<"-------------------\n";
// AVLTREE<int> tree1;
// int arr1[] = {4, 2, 8, 1, 3, 6, 10, 5, 7, 11, 12};
// for(int x : arr1) tree1.insert(x);
// tree1.view(MODE::BFS);
// cout << "\nDELETE TREE1\n";
// int del1[] = {1, 6, 4};
// for(int x : del1){
//     cout << x << " (DELETE) --------\n";
//     tree1.remove(x);
//     tree1.view(MODE::BFS);
// }

// cout<<"-------------------\n";
// AVLTREE<int> tree2;
// int arr2[] = {9, 5, 11, 3, 7, 10, 12, 2, 4, 6, 8, 1};
// for(int x : arr2) tree2.insert(x);
// tree2.view(MODE::BFS);
// cout << "\nDELETE TREE2\n";
// int del2[] = {1, 7, 9};
// for(int x : del2){
//     cout << x << " (DELETE) --------\n";
//     tree2.remove(x);
//     tree2.view(MODE::BFS);
// }

// cout<<"-------------------\n";
// AVLTREE<int> tree3;
// int arr3[] = {23, 20, 30, 10, 22, 25, 40, 24, 35};
// for(int x : arr3) tree3.insert(x);
// tree3.view(MODE::BFS);
// cout << "\nDELETE TREE3\n";
// int del3[] = {24, 30, 23};
// for(int x : del3){
//     cout << x << " (DELETE) --------\n";
//     tree3.remove(x);
//     tree3.view(MODE::BFS);
// }

//"give hardest case"

int main(){

auto start = high_resolution_clock::now();
AVLTREE<int> tree;

int arr[] = {
    50,20,70,10,30,60,80,
    25,27,26,5,1,2,3,4,
    90,100,95,85,75
};

tree.M=MODE::BFS;

for(int x : arr){
    // cout << x << "-------------------\n";
    tree.insert(x); //cout<<tree;
}     
cout<<tree;

cout << "\n===== DELETION START =====\n";
int delArr[] = {
    4,   // leaf
    5,   // single child
    25,  // internal (rotation heavy)
    50,  // ROOT deletion
    70,  // internal (right heavy)
    90,  // deeper subtree
    20   // near root rebalance
};

for(int x : delArr){
    // cout << "------------------- DELETE " << x << "\n" ;
    tree.remove(x);
}
cout<<tree;

auto end = high_resolution_clock::now();

auto duration = duration_cast<microseconds>(end - start);

cout << "\nTime taken: " << duration.count() << " microseconds\n";
return 0;
}



//DELETE
//---------------------------------------------

    // AVLTREE<int> tree;
    // int arr[] = {
    //     50,20,70,10,30,60,80,
    //     25,27,26,5,1,2,3,4,
    //     90,100,95,85,75
    // };  
    // int arr[] = {14, 17, 11, 7, 53, 4, 13, 12, 8, 60, 19, 16, 20};

    // for(int x : arr){
    //     cout<<x<<"-----------------\n";
    //     tree.insert(x); tree.view(MODE::BFS);
    // }

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

//----------------------------------------------

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

//     return 0;
// }


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