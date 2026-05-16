#include <iostream>
#include <GDSLstack.hpp>
#include <GDSLqueue.hpp>

enum class NTYPE : char { LF='l', RT='r', IM='m' };

template<typename D>
struct BTnode{
    unsigned short K=0;
    BTnode<D>* P=nullptr; 
    D* KEY; 
    BTnode<D>** LINK;
    BTnode(unsigned short order, char* base);
};

template<typename D>
BTnode<D>::BTnode(unsigned short order, char* base){

    KEY  = (D*)(base + sizeof(BTnode<D>));
    LINK = (BTnode<D>**)((char*)KEY + sizeof(D)*order);  

    for(int i=0; i<order; i++)   KEY[i] = D();
    for(int i=0; i<=order; i++)  LINK[i] = nullptr;
}

template<typename D>
class BTREE{
protected:
    size_t N=0;
    unsigned short O;
    size_t node=0;
    BTnode<D>* ROOT=nullptr;
    BTnode<D>* create();
    void print_BTnode(BTnode<D>* ptr, bool f=false);
    void split(BTnode<D>* curr, D item, BTnode<D>* child);
    void borrowLeftSibling(NTYPE NT, BTnode<D>* left, BTnode<D>* parent, BTnode<D>* node, unsigned short l, unsigned short i=0);
    void borrowRightSibling(NTYPE NT, BTnode<D>* node, BTnode<D>* parent, BTnode<D>* right, unsigned short l, unsigned short i=0);
    void mergeLeftSibling(NTYPE NT, BTnode<D>* left, BTnode<D>* parent, BTnode<D>* node, unsigned short l, unsigned short i=0);
    void mergeRightSibling(NTYPE NT, BTnode<D>* node, BTnode<D>* parent, BTnode<D>* right, unsigned short l, unsigned short i=0);
    void inorderPredecessor(BTnode<D>* pred, BTnode<D>* node, unsigned short i, bool gape=false);
    void inorderSuccessor(BTnode<D>* node, BTnode<D>* succ, unsigned short i);
    void mergeLeftRight(BTnode<D>* left, BTnode<D>* node, BTnode<D>* right, unsigned short i);
    unsigned short link(BTnode<D>* node, BTnode<D>* parent);
    void fillMinimum(BTnode<D>* node, BTnode<D>* parent);
    void deletecase(NTYPE NT, BTnode<D>* node, unsigned short i, unsigned short l=65535);
public:
    BTREE(unsigned short order);
    ~BTREE();
    size_t size() const { return N; }
    void viewBFS(bool f=false);
    void viewDFS(bool f=false);
    bool search(D item);
    bool insert(D item);
    bool remove(D item);
};

template<typename D>
BTnode<D>* BTREE<D>::create(){
    size_t size = sizeof(BTnode<D>) +
                  sizeof(D) * O +
                  sizeof(BTnode<D>*) * (O + 1);

    char* block = new char[size];
    return new (block) BTnode<D>(O,block);
}

template<typename D>
BTREE<D>::BTREE(unsigned short order) : O(order) {}

template<typename D>
BTREE<D>::~BTREE(){
    // TODO: traverse tree and delete all nodes properly

    // if only root exists:
    if (ROOT) {
        delete[] (char*)ROOT;
        ROOT=nullptr;
    }
}

template<typename D>
void BTREE<D>::print_BTnode(BTnode<D>* ptr, bool f){ int i;

    if(f){

        if(ptr->P) std::cout<<"P["<<(std::uintptr_t)ptr->P<<"]\n"; 
        else std::cout<<"P[NULL]\n";

        std::cout<<"K[";
        for(i=0; i<ptr->K; i++){ 
            std::cout<<ptr->KEY[i]; if(i<(ptr->K -1)) std::cout<<"|";
        }
        std::cout<<"]\n";

        std::cout<<"L[";
        for(i=0; i<=ptr->K; i++){ 
            if(ptr->LINK[i]){ std::cout<<(std::uintptr_t)ptr->LINK[i]; if(i<ptr->K) std::cout<<"|"; }
            else{ std::cout<<"NULL"; if(i<ptr->K) std::cout<<"|"; } 
        }
        std::cout<<"]\n";

        std::cout<<(std::uintptr_t)ptr;

    }else{

        if(ptr->P) std::cout<<"P["<<ptr->P<<"]\n"; 
        else std::cout<<"P[NULL]\n";

        std::cout<<"K[";
        for(i=0; i<ptr->K; i++){ 
            std::cout<<ptr->KEY[i]; if(i<(ptr->K -1)) std::cout<<"|";
        }
        std::cout<<"]\n";

        std::cout<<"L[";
        for(i=0; i<=ptr->K; i++){ 
            if(ptr->LINK[i]){ std::cout<<ptr->LINK[i]; if(i<ptr->K) std::cout<<"|"; }
            else{ std::cout<<"NULL"; if(i<ptr->K) std::cout<<"|"; } 
        }
        std::cout<<"]\n";

        std::cout<<ptr;
    }
}

template<typename D>
void BTREE<D>::viewBFS(bool f){
    if(!ROOT){ std::cout<<"Tree is empty"; return; }
    QUEUE<BTnode<D>*> Q; 
    BTnode<D>* tmp;
    Q.enqueue(ROOT); std::cout<<"\n";
    while(!Q.empty()){
        tmp=Q.dequeue();
        for(int i=0; i<=tmp->K; i++) if(tmp->LINK[i]) Q.enqueue(tmp->LINK[i]);
        print_BTnode(tmp,f);  
        if(!Q.empty()) std::cout<<"\n\n";
    }
}

template<typename D>
void BTREE<D>::viewDFS(bool f){
    if(!ROOT){ std::cout<<"Tree is empty"; return; }
    STACK<BTnode<D>*> S; 
    BTnode<D>* tmp;
    S.push(ROOT); std::cout<<"\n";
    while(!S.empty()){
        tmp=S.pop();
        for(int i=0; i<=tmp->K; i++) if(tmp->LINK[i]) S.push(tmp->LINK[i]);
        print_BTnode(tmp,f); 
        if(!S.empty()) std::cout<<"\n\n";
    }
}

template<typename D>
bool BTREE<D>::search(D item){
    BTnode<D>* ptr=ROOT; 
    while(ptr){
        unsigned short i=0;
        while(i<ptr->K && item>ptr->KEY[i]) i++;
        if(i<ptr->K && item==ptr->KEY[i]) return true;
        ptr=ptr->LINK[i];
    }
    return false;
}

template<typename D>
bool BTREE<D>::insert(D item){
    if(!ROOT){
        ROOT=create(); N++; 
        ROOT->KEY[0]=item; ROOT->K++;
        return true;
    }
    BTnode<D>* ptr=ROOT; unsigned short i;
    while(ptr){
        i=0;
        while(i<ptr->K && item>ptr->KEY[i]) i++;
        if(i<ptr->K && item==ptr->KEY[i]) return false;
        if(!ptr->LINK[i]) break;
        ptr=ptr->LINK[i];
    }
    if(ptr->K==O){ split(ptr,item,nullptr);
    }else{
        unsigned short n=ptr->K;
        while(n-- && n>=i){
            ptr->KEY[n+1]=ptr->KEY[n];
        }
        ptr->KEY[i]=item; ptr->K++;
    }
    return true;
}

template<typename D>
void BTREE<D>::split(BTnode<D>* curr, D item, BTnode<D>* child){
    BTnode<D>* node=create(); N++;

    unsigned short i=0;
    while(i<curr->K && item>curr->KEY[i]) i++;

    unsigned short n=O/2;
    D tmpK=item; BTnode<D>* tmpL=child;

    if(i<n) for(int j=i; j<n; j++){ std::swap(tmpK,curr->KEY[j]);
                                    std::swap(tmpL,curr->LINK[j+1]); }
    else if(i>n) for(int j=i-1; j>=n; j--){ std::swap(tmpK,curr->KEY[j]);
                                            std::swap(tmpL,curr->LINK[j+1]); } 
    int k=0;
    node->LINK[k]=tmpL;  if(tmpL) tmpL->P = node;
    while(n<O){
        node->KEY[k]=curr->KEY[n]; curr->KEY[n]=D();
        node->LINK[k+1]=curr->LINK[n+1]; curr->LINK[n+1]=nullptr;
        
        if(node->LINK[k+1]) node->LINK[k+1]->P=node;
        node->K++;   curr->K--;
        k++; n++;
    }

    if(curr==ROOT){
        BTnode<D>* node2=create(); N++;
        node2->KEY[0]=tmpK; node2->K++;
        node2->LINK[0]=curr; node2->LINK[1]=node;
        curr->P=node->P=node2;
        node2->P=nullptr; ROOT=node2;
    }
    else if(curr->P->K==O) split(curr->P,tmpK,node);
    else{
        BTnode<D>* currP=curr->P;
        int n=currP->K -1;
        while(n>=0 && tmpK<currP->KEY[n]){
            currP->KEY[n+1]=currP->KEY[n];
            currP->LINK[n+2]=currP->LINK[n+1]; 
            n--;
        }
        currP->KEY[n+1]=tmpK; currP->LINK[n+2]=node; currP->K++;
        node->P=currP;
    }
}

template<typename D>
void BTREE<D>::borrowLeftSibling(NTYPE NT, BTnode<D>* left, BTnode<D>* parent, BTnode<D>* node, unsigned short l, unsigned short i){
    BTnode<D>* tmp; 
    switch (NT){
        case NTYPE::LF :
            if(i){ 
                D t=node->KEY[0];
                for(int j=1; j<node->K; j++){
                    if(i<j) break;
                    std::swap(t,node->KEY[j]);
            }}
            node->KEY[0]=parent->KEY[l-1];
            parent->KEY[l-1]=left->KEY[left->K -1];
            left->KEY[--left->K]=D();
            return; 

        case NTYPE::IM :
            for(int j=node->K; j>0; j--){ node->KEY[j]=node->KEY[j-1];
                                          node->LINK[j+1]=node->LINK[j]; }
            node->LINK[1]=node->LINK[0];
            node->KEY[0]=parent->KEY[l-1];            node->LINK[0]=left->LINK[left->K];   node->K++;
            parent->KEY[l-1]=left->KEY[left->K -1];   if(left->LINK[left->K]) left->LINK[left->K]->P=node;
            
            left->LINK[left->K]=nullptr;   left->KEY[--left->K]=D();
            return;
    }
}

template<typename D>
void BTREE<D>::borrowRightSibling(NTYPE NT, BTnode<D>* node, BTnode<D>* parent, BTnode<D>* right, unsigned short l, unsigned short i){
    BTnode<D>* tmp; 
    switch (NT){
        case NTYPE::LF :
            for(int j=i+1; j<node->K; j++) node->KEY[j-1]=node->KEY[j];
            node->KEY[node->K -1]=parent->KEY[l];
            parent->KEY[l]=right->KEY[0];

            for(int j=1; j<right->K; j++) right->KEY[j-1]=right->KEY[j];
            right->KEY[--right->K]=D();
            return;

        case NTYPE::IM :
            node->KEY[node->K++]=parent->KEY[l]; node->LINK[node->K]=right->LINK[0];
            parent->KEY[l]=right->KEY[0];        if(right->LINK[0]) right->LINK[0]->P=node;

            int j; for(j=0; j<right->K-1; j++){ right->KEY[j]=right->KEY[j+1];
                                                right->LINK[j]=right->LINK[j+1]; }
            right->LINK[j]=right->LINK[j+1];
            right->LINK[right->K]=nullptr;      --right->K;
            return;
    }
}

template<typename D>
void BTREE<D>::mergeLeftSibling(NTYPE NT, BTnode<D>* left, BTnode<D>* parent, BTnode<D>* node, unsigned short l, unsigned short i){
    switch(NT){
        case NTYPE::LF :
            left->KEY[left->K++]=parent->KEY[l-1];
            for(int j=l-1; (j+1)<parent->K; j++){ parent->KEY[j]=parent->KEY[j+1];
                                                  parent->LINK[j+1]=parent->LINK[j+2]; }
            parent->LINK[parent->K]=nullptr;
            parent->KEY[--parent->K]=D(); 

            for(int j=0; j<node->K; j++) if(i!=j) left->KEY[left->K++]=node->KEY[j];
            delete[] (char*)node; N--;
            
            if(parent->K < (O/2)) fillMinimum(parent,parent->P);
            return;

        case NTYPE::IM :
            left->KEY[left->K++]=parent->KEY[l-1];
            left->LINK[left->K]=node->LINK[0];
            left->LINK[left->K]->P=left;
            for(int j=l-1; (j+1)<parent->K; j++){ parent->KEY[j]=parent->KEY[j+1];
                                                  parent->LINK[j+1]=parent->LINK[j+2]; }
            parent->LINK[parent->K]=nullptr;
            parent->KEY[--parent->K]=D(); 

            for(int j=0; j<node->K; j++){ left->KEY[left->K++]=node->KEY[j];
                                          left->LINK[left->K]=node->LINK[j+1];
                                          left->LINK[left->K]->P=left; }
            delete[] (char*)node; N--;
            if(parent->K < (O/2)) fillMinimum(parent,parent->P);
            return;
        
        case NTYPE::RT :
            left->KEY[left->K++]=parent->KEY[l-1];
            left->LINK[left->K]=node->LINK[0];
            left->LINK[left->K]->P=left;
            delete[] (char*)parent; N--;

            for(int j=0; j<node->K; j++){ left->KEY[left->K++]=node->KEY[j];
                                          left->LINK[left->K]=node->LINK[j+1];
                                          left->LINK[left->K]->P=left; }
            delete[] (char*)node; N--;
            left->P=nullptr;  ROOT=left;
            return;
    }
}

template<typename D>
void BTREE<D>::mergeRightSibling(NTYPE NT, BTnode<D>* node, BTnode<D>* parent, BTnode<D>* right, unsigned short l, unsigned short i){
    switch(NT){
        case NTYPE::LF :
            for(int j=i; (j+1)<node->K; j++) node->KEY[j]=node->KEY[j+1];
            node->KEY[--node->K]=D();

            node->KEY[node->K++]=parent->KEY[l];
            for(int j=l; (j+1)<parent->K; j++){ parent->KEY[j]=parent->KEY[j+1];
                                                parent->LINK[j+1]=parent->LINK[j+2]; }
            parent->LINK[parent->K]=nullptr;
            parent->KEY[--parent->K]=D(); 

            for(int j=0; j<right->K; j++) node->KEY[node->K++]=right->KEY[j];
            delete[] (char*)right; N--;
            
            if(parent->K < (O/2)) fillMinimum(parent,parent->P);
            return;

        case NTYPE::IM :
            node->KEY[node->K++]=parent->KEY[l];
            node->LINK[node->K]=right->LINK[0];
            node->LINK[node->K]->P=node;
            for(int j=l; (j+1)<parent->K; j++){ parent->KEY[j]=parent->KEY[j+1];
                                                parent->LINK[j+1]=parent->LINK[j+2]; }
            parent->LINK[parent->K]=nullptr;
            parent->KEY[--parent->K]=D(); 

            for(int j=0; j<right->K; j++){ node->KEY[node->K++]=right->KEY[j];
                                           node->LINK[node->K]=right->LINK[j+1]; 
                                           node->LINK[node->K]->P=node; }
            delete[] (char*)right; N--;
            if(parent->K < (O/2)) fillMinimum(parent,parent->P);
            return;

        case NTYPE::RT :
            node->KEY[node->K++]=parent->KEY[l];
            node->LINK[node->K]=right->LINK[0];
            node->LINK[node->K]->P=node;
            delete[] (char*)parent; N--;

            for(int j=0; j<right->K; j++){ node->KEY[node->K++]=right->KEY[j];
                                           node->LINK[node->K]=right->LINK[j+1]; 
                                           node->LINK[node->K]->P=node; }
            delete[] (char*)right; N--;
            node->P=nullptr;  ROOT=node;
            return;
    }
}

template<typename D>
void BTREE<D>::inorderPredecessor(BTnode<D>* pred, BTnode<D>* node, unsigned short i, bool gape){
    node->KEY[i]=pred->KEY[--pred->K];
    pred->KEY[pred->K]=D();

    if(gape) fillMinimum(pred,pred->P);
}

template<typename D>
void BTREE<D>::inorderSuccessor(BTnode<D>* node, BTnode<D>* succ, unsigned short i){
    node->KEY[i]=succ->KEY[0];
    for(int j=0; (j+1)<succ->K; j++) succ->KEY[j]=succ->KEY[j+1];
    succ->KEY[--succ->K]=D();
}

template<typename D>
void BTREE<D>::mergeLeftRight(BTnode<D>* left, BTnode<D>* node, BTnode<D>* right, unsigned short i){
    for(int j=0; j<right->K; j++)
        left->KEY[left->K++]=right->KEY[j];
    for(int j=i; (j+1)<node->K; j++){ node->KEY[j]=node->KEY[j+1];
                                        node->LINK[j+1]=node->LINK[j+2]; }
    node->LINK[node->K]=nullptr;
    node->KEY[--node->K]=D(); 
    delete [](char*)right;

    if(node->K < (O/2)) fillMinimum(node,node->P);
}

template<typename D>
unsigned short BTREE<D>::link(BTnode<D>* node, BTnode<D>* parent){
    if(!parent) 
        throw std::runtime_error("Parent link null");

    for(int l=0; l<=parent->K; l++)
        if(parent->LINK[l] == node) return l;
    throw std::runtime_error("Link(l) not found");
}

template<typename D>
void BTREE<D>::fillMinimum(BTnode<D>* node, BTnode<D>* parent){
    if(!node || (node==ROOT && node->K>0)) return;
    else if(node==ROOT && node->K==0 && node->LINK[0]){
        ROOT=node->LINK[0];
        ROOT->P=nullptr; delete[] (char*)node;
    }else{
        unsigned short l=link(node,parent);
        if(parent->K==1){
            if(l)
                if((parent->LINK[l-1])->K > (O/2)) 
                    borrowLeftSibling(NTYPE::IM,parent->LINK[l-1],parent,node,l);
                else 
                    mergeLeftSibling(NTYPE::RT,parent->LINK[l-1],parent,node,l);
            else
                if((parent->LINK[l+1])->K > (O/2)) 
                    borrowRightSibling(NTYPE::IM,node,parent,parent->LINK[l+1],l);
                else 
                    mergeRightSibling(NTYPE::RT,node,parent,parent->LINK[l+1],l);       
        }else{
            if(!l)
                if((parent->LINK[l+1])->K > (O/2)) 
                    borrowRightSibling(NTYPE::IM,node,parent,parent->LINK[l+1],l);
                else 
                    mergeRightSibling(NTYPE::IM,node,parent,parent->LINK[l+1],l);
            else if(l==parent->K)
                if((parent->LINK[l-1])->K > (O/2)) 
                    borrowLeftSibling(NTYPE::IM,parent->LINK[l-1],parent,node,l);
                else 
                    mergeLeftSibling(NTYPE::IM,parent->LINK[l-1],parent,node,l);
            else 
                if((parent->LINK[l-1])->K > (parent->LINK[l+1])->K) 
                    borrowLeftSibling(NTYPE::IM,parent->LINK[l-1],parent,node,l);
                else if((parent->LINK[l-1])->K < (parent->LINK[l+1])->K) 
                    borrowRightSibling(NTYPE::IM,node,parent,parent->LINK[l+1],l);
                else
                    if((parent->LINK[l-1])->K > (O/2)) 
                        borrowLeftSibling(NTYPE::IM,parent->LINK[l-1],parent,node,l);
                    else 
                        mergeLeftSibling(NTYPE::IM,parent->LINK[l-1],parent,node,l);
        }
    }
}

template<typename D>
void BTREE<D>::deletecase(NTYPE NT, BTnode<D>* node, unsigned short i , unsigned short l){
    switch(NT){
        case NTYPE::LF :
            if(!l)
                if((node->P->LINK[l+1])->K > (O/2)) 
                    borrowRightSibling(NT,node,node->P,node->P->LINK[l+1],l,i);
                else
                    mergeRightSibling(NT,node,node->P,node->P->LINK[l+1],l,i);

            else if(l==node->P->K)
                if((node->P->LINK[l-1])->K > (O/2)) 
                    borrowLeftSibling(NT,node->P->LINK[l-1],node->P,node,l,i);
                else 
                    mergeLeftSibling(NT,node->P->LINK[l-1],node->P,node,l,i);
            else 
                if((node->P->LINK[l-1])->K > (node->P->LINK[l+1])->K) 
                    borrowLeftSibling(NT,node->P->LINK[l-1],node->P,node,l,i);

                else if((node->P->LINK[l-1])->K < (node->P->LINK[l+1])->K)
                    borrowRightSibling(NT,node,node->P,node->P->LINK[l+1],l,i);
                else
                    if((node->P->LINK[l-1])->K > (O/2)) 
                        borrowLeftSibling(NT,node->P->LINK[l-1],node->P,node,l,i);
                    else 
                        mergeLeftSibling(NT,node->P->LINK[l-1],node->P,node,l,i);
            break;

        case NTYPE::IM :
        case NTYPE::RT :

            BTnode<D>* pred=node->LINK[i];
            while(pred->LINK[0]) pred=pred->LINK[pred->K]; 
            if(pred->K > (O/2)){ 
                inorderPredecessor(pred,node,i);
            break;}

            BTnode<D>* succ=node->LINK[i+1];
            while(succ->LINK[0]) succ=succ->LINK[0]; 
            if(succ->K > (O/2)){ 
                inorderSuccessor(node,succ,i);
            break;}

            if(pred == node->LINK[i]) mergeLeftRight(pred,node,succ,i); // Leaf
            else
                inorderPredecessor(pred,node,i,true);
            break;
    }
}

template<typename D>
bool BTREE<D>::remove(D item){
    if(!ROOT) return false;

    BTnode<D>* ptr=ROOT; unsigned short i,l=0;
    while(ptr){
        i=0;
        while(i<ptr->K && item>ptr->KEY[i]) i++;
        if(i<ptr->K && item==ptr->KEY[i]) break;
        if(!ptr->LINK[i]) return false;
        l=i; ptr=ptr->LINK[i]; 
    }

    if(ptr==ROOT){
        if(ptr->LINK[0]){
            deletecase(NTYPE::RT,ptr,i);
        }else{
            while((i+1)<ptr->K){
                ptr->KEY[i]=ptr->KEY[i+1]; i++;
            }
            ptr->KEY[i]=D(); ptr->K--;

            if(ROOT->K==0){ delete[] (char*)ROOT; ROOT=nullptr; }
        }
        return true;
    }

    if(ptr->LINK[0]){ deletecase(NTYPE::IM,ptr,i,l);
    }else{
        if(ptr->K==(O/2)){
            deletecase(NTYPE::LF,ptr,i,l);
        }else{
            while((i+1)<ptr->K){
                ptr->KEY[i]=ptr->KEY[i+1]; i++;
            }
            ptr->KEY[i]=D(); ptr->K--;
        }
    }
    return true;
}

#include <iostream>
using namespace std;

int main() {

    BTREE<int> T(4);

    // =========================
    // PHASE 1: COMPLEX INSERT
    // =========================
    cout << "\n===== COMPLEX INSERT PHASE =====\n";

    int insertPhase[] = {
        50, 20, 70, 10, 30, 60, 80,
        5, 15, 25, 35, 55, 65, 75, 85,
        2, 7, 12, 18, 22, 28, 32, 38,
        52, 58, 62, 68, 72, 78, 82, 88,
        90, 95, 98, 100
    };

    for(int x : insertPhase) {
        cout << "insert " << x << endl;
        T.insert(x);
    }
    T.viewBFS();


    // =========================
    // PHASE 2: COMPLEX DELETE
    // =========================
    cout << "\n\n===== COMPLEX DELETE PHASE =====\n";

    int deletePhase[] = {
        5, 7, 12, 15, 18, 22, 25, 28,
        30, 32, 35, 38,
        50, 52, 55, 58,
        60, 62, 65, 68,
        70, 72, 75, 78,
        80, 82, 85, 88,
        90, 95, 98, 100
    };

    for(int x : deletePhase) {
        cout << "delete " << x << endl;
        T.remove(x);
    }
    T.viewBFS();


    // =========================
    // PHASE 3: REBUILD TREE
    // =========================
    cout << "\n\n===== REBUILD AFTER COLLAPSE =====\n";

    int rebuild[] = {
        40, 45, 42, 44, 41,
        46, 47, 43, 49,
        39, 37, 36, 34, 33
    };

    for(int x : rebuild) {
        cout << "insert " << x << endl;
        T.insert(x);
    }
    T.viewBFS();


    // =========================
    // PHASE 4: FINAL WIPE
    // =========================
    cout << "\n\n===== FINAL CASCADE WIPE =====\n";

    int finalWipe[] = {
        41, 42, 43, 44, 45,
        46, 47, 49, 40,
        39, 37, 36, 34, 33
    };

    for(int x : finalWipe) {
        cout << "delete " << x << endl;
        T.remove(x);
    }
    T.viewBFS();

    cout << "\n\n===== TEST COMPLETE =====\n";

    return 0;
}

// int main(){

//     cout << "\n===== HIDDEN BUG ZONE TEST =====\n";

// BTREE<int> T(4);

// // -----------------------------
// // STEP 1: Build controlled tree
// // (balanced but fragile layout)
// // -----------------------------
// int base[] = {
//     50,

//     20, 80,

//     10, 30, 60, 90,

//     5, 15, 25, 35,
//     55, 65, 75, 85,
//     95, 100
// };

// for(int x : base)
//     T.insert(x);

// cout << "\n===== INITIAL TREE =====\n";
// T.viewBFS();


// // =============================
// // 🔥 STAGE 1: FORCE BORROW EDGE CASE
// // =============================
// cout << "\n===== BORROW EDGE CASE =====\n";

// // removes from nodes with uneven siblings
// T.remove(5);     // left extreme
// T.remove(15);    // forces borrow from right sibling
// T.remove(25);    // middle-left imbalance

// // T.viewBFS();


// // =============================
// // 🔥 STAGE 2: FORCE WRONG SIBLING CHOICE
// // =============================
// cout << "\n===== SIBLING CHOICE TEST =====\n";

// T.remove(55);   // left of right subtree
// T.remove(65);   // adjacent internal shift
// T.remove(75);   // forces decision: left or right borrow?

// // T.viewBFS();


// // // =============================
// // // 🔥 STAGE 3: FORCE MERGE CHAIN ACROSS LEVELS
// // // =============================
// cout << "\n===== CROSS-LEVEL MERGE =====\n";

// T.remove(10); T.viewBFS();
// T.remove(20); T.viewBFS();
// T.remove(30); T.viewBFS();
// T.remove(35);

// // T.viewBFS();


// // =============================
// // 🔥 STAGE 4: ROOT SHRINK STRESS
// // =============================
// cout << "\n===== ROOT SHRINK STRESS =====\n";

// T.remove(50); //T.viewBFS();
// T.remove(60); T.viewBFS();
// T.remove(80); T.viewBFS();
// T.remove(90);

// T.viewBFS();


// // =============================
// // 🔥 STAGE 5: FINAL CASCADING COLLAPSE
// // =============================
// cout << "\n===== FINAL CASCADE WIPE =====\n";

// int wipe[] = {
//     2, 5, 7, 12, 15, 18, 22, 25, 28,
//     32, 35, 38, 55, 58, 60, 62, 65,
//     68, 70, 72, 75, 78, 80, 82, 85,
//     88, 90, 92, 95, 98, 100
// };

// for(int x : wipe){
//     T.remove(x); cout<<"\n-----------"<<x<<"\n";
//     if(x==85 || x==95 || x==100) T.viewBFS();
// }
// // T.viewBFS();
// cout << "\n===== TEST COMPLETE =====\n";

//     return 0;
// }

// int main() {

//     BTREE<int> T(4);

//     // ------------------------------
//     // STEP 1: Build tree
//     // ------------------------------
//     int arr[] = {
//         50,

//         20, 80,

//         10, 30, 60, 90,

//         5, 15, 25, 35,
//         55, 65, 75, 85,
//         95, 100,

//         2, 7, 12, 18,
//         22, 28, 32, 38,
//         52, 58, 62, 68,
//         72, 78, 82, 88,
//         92, 98
//     };

//     for(int x : arr)
//         T.insert(x);

//     cout << "\n===== INITIAL TREE =====\n";
//     T.viewBFS();

//     // ------------------------------
//     // STEP 2: Leaf deletions
//     // ------------------------------
//     cout << "\n===== LEAF DELETION TEST =====\n";
//     T.remove(7);
//     T.remove(18);
//     T.viewBFS();

//     // ------------------------------
//     // STEP 3: Internal deletions
//     // ------------------------------
//     cout << "\n===== INTERNAL NODE DELETION =====\n";
//     T.remove(50);
//     T.remove(20);
//     T.remove(80);
//     T.viewBFS();

//     // ------------------------------
//     // STEP 4: Borrow / merge stress
//     // ------------------------------
//     cout << "\n===== BORROW + MERGE TEST =====\n";
//     T.remove(2);
//     T.remove(100);
//     T.remove(5);
//     T.remove(10);
//     T.viewBFS();

//     // ------------------------------
//     // STEP 5: Cascading underflow
//     // ------------------------------
//     cout << "\n===== CASCADING UNDERFLOW TEST =====\n";
//     T.remove(15);
//     T.remove(25);
//     T.remove(30);
//     T.remove(35);
//     T.viewBFS();


//     // ------------------------------
//     // STEP 6: Root shrink stress
//     // (safe controlled deletion)
//     // ------------------------------
//     cout << "\n===== ROOT SHRINK TEST =====\n";

//     int shrink[] = {
//         60, 65, 70, 75,
//         85, 90, 95, 98,
//         55, 58, 62, 68,
//         72, 78, 82, 88, 92,
//         22, 28, 32, 38
//     };

//     for(int x : shrink)
//         T.remove(x);

//     T.viewBFS();

//     return 0;
// }

// using namespace std;

// int main(){

//     BTREE<int> T(4);   // order = 4 (max keys = 4)

// // ---------------------------
// // Build a dense balanced tree
// // ---------------------------
// int arr[] = {
//     50,

//     20, 80,

//     10, 30, 60, 90,

//     5, 15, 25, 35,
//     55, 65, 75, 85,
//     95, 100
// };

// for(int x : arr){
//     T.insert(x);
// }

// cout << "\n===== INITIAL TREE =====\n";
// T.viewBFS();


// // ======================================================
// // INTERNAL NODE DELETION TEST CASES
// // ======================================================

// cout << "\n\n===== DELETE INTERNAL KEYS =====\n";

// // Case 1: internal node with both children (force successor swap)
// cout << "\n--- Delete 50 (root internal) ---\n";
// T.remove(50);
// T.viewBFS();


// // Case 2: internal node causing successor path borrow/merge
// cout << "\n--- Delete 20 (internal, left-heavy subtree) ---\n";
// T.remove(20);
// T.viewBFS();


// // Case 3: internal deletion triggering predecessor replacement
// cout << "\n--- Delete 80 (internal, right subtree) ---\n";
// T.remove(80);
// T.viewBFS();


// // Case 4: cascading underflow after internal deletion
// cout << "\n--- Delete 30 (forces merge chain) ---\n";
// T.remove(30);
// T.viewBFS();


// // Case 5: deep internal node stress
// cout << "\n--- Delete 60 (deep internal case) ---\n";
// T.remove(60);
// T.viewBFS();


// // Case 6: cleanup stress
// cout << "\n--- Delete 90 ---\n";
// T.remove(90);
// T.viewBFS();

    // BTREE<int> T(4);

    // // Build a balanced tree
    // int arr[] = {
    //     10,20,30,40,50,60,70,80,90,100,
    //     5,15,25,35,45,55,65,75,85,95
    // };

    // for(int x : arr){
    //     T.insert(x); // T.viewBFS(); cout<<"--------------";
    // }

    // cout << "\nInitial Tree:\n";
    // T.viewBFS();

    // // ROOT deletions (important sequence)
    // int del[] = {50, 60, 55, 65, 70, 75, 80};

    // for(int x : del){
    //     cout << "\n\nDelete: " << x << "\n";
    //     T.remove(x);
    // }
    //     T.viewBFS();
//     return 0;
// }

// using namespace std;
// int main(){

//     BTREE<int> T(4);   // order = 4 (min = 1)

//     // Insert elements
//     for(int i = 1; i <= 20; i++){
//         T.insert(i);
//     }

//     cout << "\nInitial Tree (BFS):\n";
//     T.viewBFS(true);


//     // 🔴 Delete ONLY leaf-heavy values (rightmost side)
//     int delArr[] = {20, 19, 18, 17, 16};

//     for(int x : delArr){
//         cout << "\n\nDelete: " << x << "\n";
//         T.remove(x);
//         T.viewBFS(true);
//     }

//     return 0;
// }

// using namespace std;
// int main(){
//     // BTREE<int> T(6);   

//     // int arr[] = {10, 20, 30, 40, 50, 60, 5, 80};

//     // for(int x : arr){
//     //     std::cout << "\nInsert: " << x << "\n";
//     //     T.insert(x); 
//     //     T.viewBFS();
//     // }



//     BTREE<int> T(4);   // order = 6

//     // Sequential insert
//     for(int i = 1; i <= 20; i++){
//         // std::cout << "\nInsert: " << i << "\n";
//         T.insert(i);
//     }    
//     T.viewBFS();

//     // for(int i = 1; i <= 20; i++){
//     //     std::cout <<T.search(i)<< "\n";
//     // }

//     return 0;
// }
