
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
        clearupto(H);
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
void LIST<D>::clearupto(node<D>*& p){
    node<D>* tmp;
    while(p){ 
        tmp = p; p = p->P; 
        delete tmp; 
    }
}

template<typename D>
LIST<D>::~LIST(){
    clearupto(H);
    T = nullptr; elem = 0;
}

template<typename D>
D& LIST<D>::operator[](long int index){
    node<D>* ptr = pointer(index);   // get the node pointer
    if(!ptr) throw std::out_of_range("Index out of bounds");
    return ptr->K;                    // return reference to the value
}

template<typename D>
const D& LIST<D>::operator[](long int index) const{
    node<D>* ptr = pointer(index);   // get the node pointer
    if(!ptr) throw std::out_of_range("Index out of bounds");
    return ptr->K;                    // return const reference
}

template<typename D>
LIST<D>& LIST<D>::operator=(const LIST<D>& other){
    if(this != &other){
        clearupto(H);
        H = T = nullptr; elem = 0;
        
        node<D>* iter = other.H;  // Copy new nodes
        while(iter){
            insert(iter->K); iter = iter->P;
        }
    }
    return *this;
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
long int LIST<D>::index(D value) const{
    node<D> *iter=H; long int index=0;
    while(iter){
        if(iter->K==value) return index;
        iter=iter->P; index++;
    } return -1;
}

template<typename D>
D LIST<D>::value(long int index) const{
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
int LIST<D>::insert(D val, long int index){
    if(H==nullptr){
        H=T=new node<D>{val, nullptr}; elem++;
        return 1;
    }
    if(index<-1 || index>elem) return -1;
    if(index==-1 || index==elem){
        T->P=new node<D>; T=T->P;
        *T=node<D>{val, nullptr}; elem++;    
        return 1;    
    }
    if(index==0){
        node<D> *tmp=new node<D>{val, H};
        H=tmp; elem++;
        return 1;
    }
    node<D> *iter=H; long int i;
    for(i=1; i<index; i++) iter=iter->P;
    node<D> *tmp=new node<D>{val, iter->P};
    iter->P=tmp; elem++;
    return 1;
}

template<typename D>
void LIST<D>::view() const{
    node<D> *iter=H;
    std::cout<<"[";
    while(iter){
        std::cout<<iter->K; if(iter->P!=nullptr) std::cout<<", ";
        iter=iter->P;
    } std::cout<<"]";
}

template<typename D>
iterator<D> LIST<D>::begin(){ return iterator<D>(H); }

template<typename D>
iterator<D> LIST<D>::end(){ return iterator<D>(nullptr); }

template<typename D>
iterator<D> LIST<D>::begin() const{ return iterator<D>(H); }

template<typename D>
iterator<D> LIST<D>::end() const{ return iterator<D>(nullptr); }

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

