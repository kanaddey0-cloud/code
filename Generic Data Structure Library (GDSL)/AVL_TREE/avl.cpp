#include <iostream>
#include <GDSLstack.hpp>
#include <GDSLqueue.hpp>
bool on=false;

#include <chrono>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace std::chrono;


template<typename D>
struct AVLnode{ int H: 8; D K; AVLnode<D>* L, *R; };

template<typename D>
class AVLTREE{
protected:
    unsigned long int elem;
    AVLnode<D>* ROOT, *AVL;
    bool f0=false;
    // STACK<AVLnode<D>*> S;
    AVLnode<D>* node[3];
    AVLnode<D>* link[4];
    AVLnode<D>* create(D item);
    void print_Key_L_C_R(const AVLnode<D>* tmp) const;
    bool deleting(AVLnode<D>*& del, AVLnode<D>* tmp);
    D deleting(AVLnode<D>* point, bool f1, bool f2=false);
public:
    AVLTREE();
    long int size() const { return elem; }
    void insert(D item);
    bool insert_(D item, AVLnode<D>* root);
    bool remove(D item);
    bool remove_(D item, AVLnode<D>* root);
    void viewBFS(bool order=false) const;
//-------------------BALANCE_TREE
    void insert_array(D arr[], size_t SIZE);
    void insert_index(D arr[], size_t LOW, size_t HIGH);
    char subH(AVLnode<D>* sub) const noexcept;
    char balanceH(AVLnode<D>* subL, AVLnode<D>* subR) const noexcept;
    void tree_balance(bool f=true) noexcept;
    AVLnode<D>* balance(AVLnode<D>* AVL); //, AVLnode<D>* parent
};

template<typename D>
AVLTREE<D>::AVLTREE() : ROOT(nullptr), AVL(nullptr), elem(0) {}

template<typename D>
void AVLTREE<D>::print_Key_L_C_R(const AVLnode<D>* tmp) const{
    if(tmp->L) std::cout<<tmp->L->K;
    else std::cout<<"NULL"; 
    std::cout<<"<-["<<tmp->K<<"]->";
    if(tmp->R) std::cout<<tmp->R->K;
    else std::cout<<"NULL"; 
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
            if(tmp->R) Q.enqueue(tmp->R);
            if(tmp->L) Q.enqueue(tmp->L);
        }else{
            if(tmp->L) Q.enqueue(tmp->L);
            if(tmp->R) Q.enqueue(tmp->R);
        }
        print_Key_L_C_R(tmp); std::cout<<"\n";
    }
}

// template<typename D>
// void AVLTREE<D>::tree_balance(bool f) noexcept{
//     AVLnode<D>* tmp;
//     char height;
//     while(!S.empty()){
//         tmp=S.pop();
//         height=balanceH(tmp->L,tmp->R);
//         if(-1 == height){ 
//             balance(tmp,!S.empty() ? S.tos() : nullptr); if(f) break; 
//         }
//         else tmp->H=height;
//     } 
//     if(f) S.clear();
// }

template<typename D>
AVLnode<D>* AVLTREE<D>::balance(AVLnode<D>* AVL){ //, AVLnode<D>* parent
    if(subH(AVL->L) > subH(AVL->R)){  // if(AVL->H > 0)
        node[2]=AVL; link[3]=AVL->R; 
        AVLnode<D>* left=AVL->L;
        if(subH(left->L) < subH(left->R)){  // if(left->H > 0)
            node[0]=left; link[0]=left->L;
            node[1]=left->R;
            link[1]=node[1]->L; link[2]=node[1]->R;  //1
        }
        else if(subH(left->L) >= subH(left->R)){  // else if(left->H < 0)
            node[1]=left; link[2]=left->R;
            node[0]=left->L;
            link[0]=node[0]->L; link[1]=node[0]->R;  //2
        }
    }
    else if(subH(AVL->L) < subH(AVL->R)){  // else if(AVL->H < 0)
        node[0]=AVL; link[0]=AVL->L;  
        AVLnode<D>* right=AVL->R;
        if(subH(right->L) < subH(right->R)){  // if(right->H > 0)
            node[1]=right; link[1]=right->L;  
            node[2]=right->R;
            link[2]=node[2]->L; link[3]=node[2]->R;  //3
        }
        else if(subH(right->L) >= subH(right->R)){  // else if(right->H < 0)
            node[2]=right; link[3]=right->R;
            node[1]=right->L;
            link[1]=node[1]->L; link[2]=node[1]->R;  //4
        } 
    }
    node[1]->L=node[0];   node[1]->R=node[2];

    node[0]->L=link[0];   node[2]->L=link[2];
    node[0]->R=link[1];   node[2]->R=link[3];

    node[0]->H=balanceH(node[0]->L,node[0]->R);
    node[2]->H=balanceH(node[2]->L,node[2]->R);
    node[1]->H=balanceH(node[1]->L,node[1]->R);

    return node[1];

    // if(parent){
    //     if(parent->K > node[1]->K) parent->L=node[1];
    //     else if(parent->K < node[1]->K) parent->R=node[1];
    // } 
    // else ROOT=node[1];
}

// template<typename D>  
// bool AVLTREE<D>::deleting(AVLnode<D>*& del, AVLnode<D>* tmp){
//     AVLnode<D>* ptr=del;  
//     if(ptr->L){
//         tmp=ptr; ptr=ptr->L; S.push(tmp);
//         while(ptr->R){ 
//             tmp=ptr; ptr=ptr->R; S.push(tmp);
//         }
//         del->K=ptr->K;
//         return deleting(ptr,tmp);
//     }
//     if(ptr->R){
//         tmp=ptr; ptr=ptr->R; S.push(tmp);
//         while(ptr->L){ 
//             tmp=ptr; ptr=ptr->L; S.push(tmp);
//         }
//         del->K=ptr->K; 
//         return deleting(ptr,tmp);
//     }
//     if(tmp->L == ptr){ 
//         delete ptr; tmp->L=nullptr; elem--; 
//     }else{ 
//         delete ptr; tmp->R=nullptr; elem--; 
//     }
//     return true;
// }

// template<typename D>
// bool AVLTREE<D>::remove(D item){
//     AVLnode<D>* ptr, *tmp;
//     tmp=ptr=ROOT;
//     while(ptr){
//         if(ptr->K!=item){ 
//             tmp=ptr;  S.push(tmp); 
//         }
//         if(item<ptr->K) ptr=ptr->L;
//         else if(item>ptr->K) ptr=ptr->R;
//         else break;
//     } 
//     if(!ptr){ S.clear(); return false; }
//     if(elem == 1){
//         delete ROOT; ROOT=nullptr; elem--; return true; 
//     }
//     if(ptr->L==nullptr && ptr->R==nullptr){
//         if(tmp->L == ptr){ 
//             tmp->L=nullptr; delete ptr; elem--; 
//         }else{ 
//             tmp->L=nullptr; delete ptr; elem--; 
//         }
//         tree_balance();
//         return true;
//     }
//     bool del=deleting(ptr,tmp); 
//     tree_balance(false);
//     return del;
// }

template<typename D> 
D AVLTREE<D>::deleting(AVLnode<D>* point, bool f1, bool f2){  D tmp;
    // if(!point) return 
    if(f1){
        if(f2){
            if(point->R){
                tmp=deleting(point->R,true,true);
                if(f0){
                    delete point->R; point->R=nullptr; f0=false;
                }else{
                    if(AVL) point->R=AVL; AVL=nullptr; 
                }
            }else  return deleting(point,false);
        }else{
            if(point->L){
                tmp=deleting(point->L,true);
                if(f0){
                    delete point->L; point->L=nullptr; f0=false;
                }else{
                    if(AVL) point->L=AVL; AVL=nullptr;
                }
            }else  return deleting(point,false);
        }
        point->H=balanceH(point->L,point->R);
        if(-1 == point->H) AVL=balance(point); 
        return tmp;
    }else{
        if(!point->L && !point->R){ f0=true; return point->K; }
        else if(point->L && !point->R){
            point->K=point->L->K;
            delete point->L; point->L=nullptr;
            //point
        }else if(!point->L && point->R){
            point->K=point->R->K;
            delete point->R; point->R=nullptr;
            //point
        }else{
            if(subH(point->L) >= subH(point->R)){
                if(point->L->R){
                    point->K=deleting(point->L->R,true,true);  // Called if(point->R)
                    if(f0){  delete point->L->R; point->L->R=nullptr; f0=false;  }
                    point->L->H=balanceH(point->L->L,point->L->R);
                    //point
                    if(-1 == point->L->H) point->L=balance(point->L);
                }else{
                    point->K=deleting(point->L,false);
                    if(f0){  delete point->L; point->L=nullptr; f0=false;  }
                    //point
                }
            }else{
                if(point->R->L){
                    point->K=deleting(point->R->L,true);  // Called if(point->L)
                    if(f0){  delete point->R->L; point->R->L=nullptr; f0=false;  }
                    point->R->H=balanceH(point->R->L,point->R->R);
                    //point
                    if(-1 == point->R->H) point->R=balance(point->R);
                }else{
                    point->K=deleting(point->R,false);
                    if(f0){  delete point->R; point->R=nullptr; f0=false;  }
                    //point
                }
            }
        }
        point->H=balanceH(point->L,point->R);
        if(-1 == point->H) AVL=balance(point);
        return point->K;
    }
}

template<typename D>
bool AVLTREE<D>::remove_(D item, AVLnode<D>* root){
    if(!root) std::cout<<root->K<<"\n";
    if(root->K > item){  
        if(root->L){
            if(remove_(item,root->L)){ delete root->L; root->L=nullptr; }
            else if(AVL){
                root->L=AVL; AVL=nullptr;
            }
        }else return false;

    }else if(root->K < item){ 
        if(root->R){
            if(remove_(item,root->R)){ delete root->R; root->R=nullptr; }
            else if(AVL){
                root->R=AVL; AVL=nullptr;
            }
        }else return false;

    }else{  
        deleting(root,false); 
        if(f0) return true;   f0=true;  
    }
    
    if(f0){
        root->H=balanceH(root->L,root->R); 
        // if(on){ std::cout<<root->K<<"("<<root->H<<")\n"; viewBFS(); std::cout<<"\n"; }
        if(-1 == root->H)
            AVL=balance(root); 
    }return false;  
}

template<typename D>
bool AVLTREE<D>::remove(D item){
    if(!ROOT) return false;
    if(ROOT->K == item){
        deleting(ROOT,false);
        if(f0){  delete ROOT; ROOT=nullptr; f0=false;  }
        else if(AVL){  ROOT=AVL; AVL=nullptr;  }
    }else{
        remove_(item,ROOT); f0=false;
        if(AVL){  ROOT=AVL; AVL=nullptr;  }
    }   
    return false; 
}

template<typename D>
AVLnode<D>* AVLTREE<D>::create(D item){
    AVLnode<D>* ptr=new AVLnode<D>;
    ptr->H=0;
    ptr->K=item;
    ptr->L=nullptr; ptr->R=nullptr; 
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
//         S.push(tmp);
//         if(item<ptr->K) ptr=ptr->L;
//         else if(item>ptr->K) ptr=ptr->R;
//         else{ S.clear(); return false; }
//     }
//     if(item<tmp->K) tmp->L=create(item); 
//     else tmp->R=create(item); elem++; 
//     tree_balance();
//     return true;
// }

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
bool AVLTREE<D>::insert_(D item, AVLnode<D>* root){
    if(root->K > item){
        if(!root->L){
            root->L=create(item); 
            root->H=balanceH(root->L,root->R); 
            return true;
        }else{
            if(insert_(item,root->L)) root->H=balanceH(root->L,root->R);
            else if(AVL){
                if(root->K > AVL->K) root->L=AVL;
                else root->R=AVL;
                AVL=nullptr; return false;
            }else return false;
        }
    }else if(root->K < item){
        if(!root->R){
            root->R=create(item);
            root->H=balanceH(root->L,root->R);
            return true;
        }else{
            if(insert_(item,root->R)) root->H=balanceH(root->L,root->R);
            else if(AVL){
                if(root->K > AVL->K) root->L=AVL;
                else root->R=AVL;
                AVL=nullptr; return false;
            }else return false;
        }
    }else return false;

    if(-1 != root->H) return true; 
    AVL=balance(root);  return false;
}

template<typename D>
void AVLTREE<D>::insert(D item){ 
    if(!ROOT) ROOT=create(item); 
    else{
        insert_(item,ROOT);
        if(AVL){
            ROOT=AVL; AVL=nullptr;
        }
    } 
}

template<typename D>
void AVLTREE<D>::insert_index(D arr[], size_t LOW, size_t HIGH){
    if(LOW == HIGH){ insert(arr[LOW]); return; }
    else if((1+LOW) == HIGH){ 
        insert(arr[LOW]); insert(arr[HIGH]); return;
    }else{
        size_t MID=(LOW+HIGH)/2;
        insert(arr[MID]);
        insert_index(arr,LOW,(MID-1));
        insert_index(arr,(1+MID),HIGH);
    }
}

template<typename D>
void AVLTREE<D>::insert_array(D arr[], size_t SIZE){
    // if(ROOT) insert_index(arr,0,SIZE-1);
    // else
    //     for(size_t i=0; i<SIZE; i++) insert(arr[i]);
        int step = SIZE;

    while (step > 0) {
        int start = step / 2;

        for (int i = start; i < SIZE; i += step) {
            insert(arr[i]);
        }

        step /= 2;
    }
}


#include <iostream>
using namespace std;

// assume your AVLTREE is already included above this

// int main() {

//     AVLTREE<int> tree;

//     cout << "========== INSERT PHASE ==========\n";

//     int insertArr[] = {
//         // balanced core
//         50, 20, 70, 10, 30, 60, 80,

//         // force LR + RL patterns
//         25, 27, 26,

//         // left heavy chain
//         5, 1, 2, 3, 4,

//         // right heavy chain
//         90, 100, 95, 85, 75
//     };

//     for(int x : insertArr){
//         // cout << "\nINSERT: " << x << "\n";
//         tree.insert(x);
//     }
// tree.viewBFS(); cout << "\n";
//     cout << "\n========== DELETION PHASE ==========\n";

//     int deleteArr[] = {
//         // 🔴 leaf deletion (no rotation)
//         4,

//         // 🔴 single child case → may trigger rebalance
//         5,

//         // 🔴 LR case trigger
//         25,

//         // 🔴 root deletion → heavy restructuring
//         50,

//         // 🔴 RR case trigger
//         70,

//         // 🔴 deeper subtree collapse
//         90,

//         // 🔴 near-root cascade (multiple rotations upward)
//         20,

//         // 🔴 final cleanup stress
//         30, 60, 80, 10, 1, 2, 3, 26, 27, 75, 85, 95, 100
//     };

//     for(int x : deleteArr){
//         cout << "\nDELETE: " << x << "\n";
//         tree.remove(x);
//         tree.viewBFS(); cout << "\n";
//     }

//     cout << "\n========== FINAL TREE ==========\n";
//     tree.viewBFS(); cout << "\n";

//     return 0;
// }

// int main(){

//     cout << "Program started\n";
//     auto start = high_resolution_clock::now();
//     AVLTREE<int> tree;

//     int arr[] = {
//         50,20,70,10,30,60,80,
//         25,27,26,5,1,2,3,4,
//         90,100,95,85,75,

//         // zig-zag patterns (LR, RL)
//         55,65,63,64,62,61,
//         35,45,43,44,42,41,

//         // increasing blocks (RR rotations)
//         101,102,103,104,105,106,107,108,109,110,

//         // decreasing blocks (LL rotations)
//         200,199,198,197,196,195,194,193,192,191,

//         // mixed middle insertions
//         150,120,130,125,135,123,127,
//         170,160,165,162,168,166,164,

//         // more zig-zag
//         15,18,17,16,19,
//         75,72,74,73,71,

//         // dense cluster (frequent rebalance)
//         300,250,275,260,270,265,268,267,266,
//         350,320,340,330,335,332,338,

//         // tail mix
//         400,380,390,385,395,
//         450,420,430,425,435,
//         500,480,490,485,495
//     };
//     cout << "I\n";
//     for(int x : arr){
//         // cout << x << "-------------------\n";
//         tree.insert(x); //cout << x << "\n"; 
//     }   
//     // tree.insert(5); tree.insert(10); tree.insert(15);

//     tree.viewBFS();
//     cout << "End\n";
//     cout << "\n===== DELETION START =====\n";
//     int delArr[] = {
//         4,   // leaf
//         5,   // single child
//         25,  // internal (rotation heavy)
//         50,  // ROOT deletion
//         70,  // internal (right heavy)
//         90,  // deeper subtree
//         20   // near root rebalance
//     };

//     for(int x : delArr){
//         cout << "------------------- DELETE " << x << "\n" ;
//         tree.remove(x);
//     }
//     tree.viewBFS();

//     auto end = high_resolution_clock::now();

//     auto duration = duration_cast<microseconds>(end - start);

//     cout << "Time taken: " << duration.count() << " microseconds\n";
//     return 0;
// }

#include <vector>
int main() {

    cout << "Program started\n";

    srand(time(0));

    auto start = high_resolution_clock::now();

    AVLTREE<int> tree;
    int n = 10000000;
cout << "S\n";
    for(int i = 1; i < n; i++){
        tree.insert(i);
        // if(i % 1000 == 0) cout << "Inserted " << i << endl;
    }
cout << "I\n";
    auto end = high_resolution_clock::now();

    cout << duration_cast<milliseconds>(end - start).count() << " ms\n";
// tree.viewBFS(); cout << "----------------\n----------\n\n";
    for(int i = 0; i < n/2; i++){
        // if(i == 4) on=true;
        // else on=false; 
        //cout<<i;
        
        tree.remove(i);
        //if(i==4) //{ cout<<"\n"<<i<<" -------------\n";  }
        //tree.viewBFS(); 
    }
cout << "D\n";
// tree.viewBFS();
    // vector<int> arr(1000001);
    // for(int i = 0; i <= 1000000; i++){ 
    //     arr[i]=i; 
    //     // if(i % 100000 == 0) cout << "Prepared: " << i << endl;
    // }
    // AVLTREE<int> t;
    // // Insert using your function
    // t.insert_array(arr.data(), 1000000);

    end = high_resolution_clock::now();

    cout << duration_cast<milliseconds>(end - start).count() << " ms\n";

    cout << "Program finished\n";
    return 0;
}

// #include <iostream>
// using namespace std;

// int main() {

//     // Arrays
//     int arr1[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
//     int arr2[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
//     int arr3[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
//     int arr4[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17};

//     // 4 AVL Trees
//     AVLTREE<int> t1, t2, t3, t4;

//     // Insert using your function
//     t1.insert_index(arr1, 0, 14);
//     t2.insert_index(arr2, 0, 15);
//     t3.insert_index(arr3, 0, 16);
//     t4.insert_index(arr4, 0, 17);

//     // (Optional) Print trees
//     cout << "Tree 1:\n"; t1.viewBFS();
//     cout << "\nTree 2:\n"; t2.viewBFS();
//     cout << "\nTree 3:\n"; t3.viewBFS();
//     cout << "\nTree 4:\n"; t4.viewBFS();

//     return 0;
// }

