#include <iostream>
#include <GDSLstack.hpp>
#include <GDSLqueue.hpp>

enum class MODE : char {
    DFS='w', BFS='x', DFS_LR='y', BFS_RL='z',
    IN='a', PRE='b', POST='c'
};
enum { L, R, P };

template<typename D>
struct BSTnode{ D K; BSTnode<D>** LINK; };

template<typename D>
std::ostream& operator<<(std::ostream& out, const BSTnode<D>& n){ return out<<n.K; }

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
    BSTnode<D>* pointer(long int index) const;
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
    void view();
    void viewDFS(bool order=false);
    void viewBFS(bool order=false);
    void viewIN(const BSTnode<D>* root) const;
    void viewPRE(const BSTnode<D>* root) const;
    void viewPOST(const BSTnode<D>* root) const;
    ~BSTREE();
};

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
        delete tmp;
    }
    root->LINK[L]=nullptr; root->LINK[R]=nullptr; 
    return true;
}

template<typename D>
BSTREE<D>::BSTREE(bool l){ ROOT=nullptr; LC=l?3:2; M=MODE::IN; elem=0; }

template<typename D>
BSTREE<D>::BSTREE(const BSTREE<D>& other):BSTREE<D>(other.LC==3?true:false){
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

    freelink(ROOT); delete ROOT; ROOT=nullptr; elem=0; LC=other.LC;

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
    freelink(ROOT); delete ROOT; ROOT=nullptr; elem=0; LC=other.LC;
    if(!other.ROOT) return *this;

    ROOT=other.ROOT; elem=other.elem; LC=other.LC;
    other.ROOT=nullptr; other.elem=0;
    return *this;
}

template<typename D>
BSTREE<D>::~BSTREE(){ freelink(ROOT); delete ROOT; ROOT=nullptr; }

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
void BSTREE<D>::viewBFS(bool order){
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
void BSTREE<D>::viewDFS(bool order){
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
void BSTREE<D>::view(){
    if(!ROOT){ std::cout << "NULL"; return; }
    switch(M){
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
BSTnode<D>* BSTREE<D>::pointer(long int index) const{
    index = index<0 ? elem+index : index;
    if(index>=elem || index<0) return nullptr;

    unsigned long int count = 0;
    switch(M){
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
    if(tmp->LINK[L] == ptr){ delete ptr; tmp->LINK[L]=nullptr; elem--; }
    else{ delete ptr; tmp->LINK[R]=nullptr; elem--; }
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
        ROOT=nullptr; delete ptr; delete tmp; elem--; return true; 
    }
    if(ptr->LINK[L]==nullptr && ptr->LINK[R]==nullptr){
        if(tmp->LINK[L] == ptr){ tmp->LINK[L]=nullptr; delete ptr; elem--; }
        else{ tmp->LINK[R]=nullptr; delete ptr; elem--; }
        return true;
    }
    return deleting(ptr,tmp);
}

template<typename D>
bool BSTREE<D>::search(D item){
    BSTnode<D>* ptr=ROOT;
    while(ptr){ 
        if(item<ptr->K) ptr=ptr->LINK[L];
        else if(item>ptr->K) ptr=ptr->LINK[R];
        else return false;
    } 
    return false;
}

template<typename D>
BSTnode<D>* BSTREE<D>::create(D item, BSTnode<D>* parent){
    BSTnode<D>* ptr=new BSTnode<D>;
    if(LC==3) ptr->LINK=new BSTnode<D>*[3]{nullptr,nullptr,parent}; 
    else ptr->LINK=new BSTnode<D>*[2]{nullptr,nullptr}; 
    ptr->K=item;
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


#include <iostream>
#include <stdexcept>

// Assume your BSTREE and MODE are already defined

#include <iostream>
#include <stdexcept>

// Assume BSTREE and MODE already defined

int main(){
    BSTREE<int> tree;

    // 🔹 Insert sample data
    int arr[] = {10, 5, 20, 3, 7, 15, 30};
    for(int x : arr){
        tree.insert(x);
    }

    // ============================
    // 🔥 VIEW TESTS
    // ============================

    std::cout << "\n===== VIEW TESTS =====\n";

    tree.M = MODE::BFS;
    std::cout << "\n--- BFS ---\n";
    tree.view();

    tree.M = MODE::DFS;
    std::cout << "\n--- DFS ---\n";
    tree.view();

    tree.M = MODE::IN;
    std::cout << "\n--- INORDER ---\n";
    tree.view();

    tree.M = MODE::PRE;
    std::cout << "\n--- PREORDER ---\n";
    tree.view();

    tree.M = MODE::POST;
    std::cout << "\n--- POSTORDER ---\n";
    tree.view();

    tree.M = MODE::DFS_LR;
    std::cout << "\n--- DFS (Right->Left) ---\n";
    tree.view();

    tree.M = MODE::BFS_RL;
    std::cout << "\n--- BFS (Right->Left) ---\n";
    tree.view();


    // ============================
    // 🔥 POINTER / INDEX TESTS
    // ============================

    std::cout << "\n\n===== POINTER / INDEX TESTS =====\n";

    tree.M = MODE::IN;
    std::cout << "\nINORDER indexing:\n";
    for(int i = 0; i < tree.size(); i++){
        std::cout << "tree[" << i << "] = " << tree[i] << "\n";
    }

    tree.M = MODE::BFS;
    std::cout << "\nBFS indexing:\n";
    for(int i = 0; i < tree.size(); i++){
        std::cout << "tree[" << i << "] = " << tree[i] << "\n";
    }

    tree.M = MODE::DFS;
    std::cout << "\nDFS indexing:\n";
    for(int i = 0; i < tree.size(); i++){
        std::cout << "tree[" << i << "] = " << tree[i] << "\n";
    }


    // ============================
    // 🔥 NEGATIVE INDEX TEST
    // ============================

    std::cout << "\n\n===== NEGATIVE INDEX TEST =====\n";

    tree.M = MODE::IN;
    std::cout << "Last element (tree[-1]) = " << tree[-1] << "\n";
    std::cout << "Second last (tree[-2]) = " << tree[-2] << "\n";


    // ============================
    // 🔥 OUT OF BOUNDS TEST
    // ============================

    std::cout << "\n\n===== OUT OF BOUNDS TEST =====\n";

    try{
        std::cout << tree[100] << "\n";   // invalid
    }
    catch(const std::exception& e){
        std::cout << "Caught: " << e.what() << "\n";
    }


    // ============================
    // 🔥 INVALID MODE TEST
    // ============================

    std::cout << "\n\n===== INVALID MODE TEST =====\n";

    try{
        tree.M = (MODE)'k';   // force invalid
        tree.view();          // should throw
    }
    catch(const std::exception& e){
        std::cout << "Caught: " << e.what() << "\n";
    }

    return 0;
}

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