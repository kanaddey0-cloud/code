#include <iostream>
#include <cmath>
#include <cstdlib>

enum class GROWTH : char {
    GINS='l', GDEL='m', GSRC='o'
};

enum class SORT : char {
    BUBBLE='A', SELECTION='B', INSERTION='C', MERGE='D', QUICK='E',
    HEAP='F', SHELL='G', ODDEVEN='H', CYCLE='I', COUNTING='J',
    RADIX='K', BUCKET='L', INTRO='M', TIM='N',
    PDQ='O', DUAL_PIVOT='P', EXTERNAL_MERGE='Q',
    K_WAY_MERGE='R', BITONIC='S'
};

template<typename D>
class ARRAYreverse_iterator{ 
    D* ptr;
public:
    ARRAYreverse_iterator(D* p = nullptr);

    D& operator*();
    const D& operator*() const;

    ARRAYreverse_iterator<D>& operator++() noexcept;
    ARRAYreverse_iterator<D> operator++(int) noexcept;

    ARRAYreverse_iterator<D>& operator--() noexcept;
    ARRAYreverse_iterator<D> operator--(int) noexcept;

    bool operator!=(const ARRAYreverse_iterator<D>& other) const noexcept;
    bool operator==(const ARRAYreverse_iterator<D>& other) const noexcept;
    bool operator<(const ARRAYreverse_iterator& other) const noexcept;
    bool operator<=(const ARRAYreverse_iterator& other) const noexcept;
    bool operator>(const ARRAYreverse_iterator& other) const noexcept;
    bool operator>=(const ARRAYreverse_iterator& other) const noexcept;

    D* operator->();
    const D* operator->() const;
};

template<typename D>
ARRAYreverse_iterator<D>::ARRAYreverse_iterator(D* p) : ptr(p) {}

template<typename D>
D& ARRAYreverse_iterator<D>::operator*(){ return *ptr; }

template<typename D>
const D& ARRAYreverse_iterator<D>::operator*() const{ return *ptr; }

template<typename D>
ARRAYreverse_iterator<D>& ARRAYreverse_iterator<D>::operator++() noexcept{
    --ptr;
    return *this;
}

template<typename D>
ARRAYreverse_iterator<D> ARRAYreverse_iterator<D>::operator++(int) noexcept{
    ARRAYreverse_iterator<D> temp = *this;
    ++(*this);
    return temp;
}

template<typename D>
ARRAYreverse_iterator<D>& ARRAYreverse_iterator<D>::operator--() noexcept{
    ++ptr;
    return *this;
}

template<typename D>
ARRAYreverse_iterator<D> ARRAYreverse_iterator<D>::operator--(int) noexcept{
    ARRAYreverse_iterator<D> temp = *this;
    --(*this);
    return temp;
}

template<typename D>
bool ARRAYreverse_iterator<D>::operator!=(const ARRAYreverse_iterator<D>& other) const noexcept{ return ptr != other.ptr; }

template<typename D>
bool ARRAYreverse_iterator<D>::operator==(const ARRAYreverse_iterator<D>& other) const noexcept{ return ptr == other.ptr; }

template<typename D>
bool ARRAYreverse_iterator<D>::operator<(const ARRAYreverse_iterator<D>& other) const noexcept{ return ptr > other.ptr; }

template<typename D>
bool ARRAYreverse_iterator<D>::operator<=(const ARRAYreverse_iterator<D>& other) const noexcept{ return ptr >= other.ptr; }

template<typename D>
bool ARRAYreverse_iterator<D>::operator>(const ARRAYreverse_iterator<D>& other) const noexcept{ return ptr < other.ptr; }

template<typename D>
bool ARRAYreverse_iterator<D>::operator>=(const ARRAYreverse_iterator<D>& other) const noexcept{ return ptr <= other.ptr; }

template<typename D>
D* ARRAYreverse_iterator<D>::operator->(){ return ptr; }

template<typename D>
const D* ARRAYreverse_iterator<D>::operator->() const{ return ptr; }


template<typename D>
class ARRAYiterator{ 
    D* ptr;
public:
    ARRAYiterator(D* p = nullptr);

    D& operator*();
    const D& operator*() const;

    ARRAYiterator<D>& operator++() noexcept;
    ARRAYiterator<D> operator++(int) noexcept;

    ARRAYiterator<D>& operator--() noexcept;
    ARRAYiterator<D> operator--(int) noexcept;

    bool operator!=(const ARRAYiterator<D>& other) const noexcept;
    bool operator==(const ARRAYiterator<D>& other) const noexcept;
    bool operator<(const ARRAYiterator& other) const noexcept;
    bool operator<=(const ARRAYiterator& other) const noexcept;
    bool operator>(const ARRAYiterator& other) const noexcept;
    bool operator>=(const ARRAYiterator& other) const noexcept;

    D* operator->();
    const D* operator->() const;
}; 

template<typename D>
ARRAYiterator<D>::ARRAYiterator(D* p) :ptr(p) {}

template<typename D>
D& ARRAYiterator<D>::operator*(){
    if(!ptr) throw std::runtime_error("Null ARRAYiterator");
    return *ptr;
}

template<typename D>
const D& ARRAYiterator<D>::operator*() const{
    if(!ptr) throw std::runtime_error("Null ARRAYiterator");
    return *ptr;
}

template<typename D>
ARRAYiterator<D>& ARRAYiterator<D>::operator++() noexcept{
    ++ptr;
    return *this;
}

template<typename D>
ARRAYiterator<D> ARRAYiterator<D>::operator++(int) noexcept{
    ARRAYiterator<D> temp = *this;
    ++(*this);
    return temp;
}

template<typename D>
ARRAYiterator<D>& ARRAYiterator<D>::operator--() noexcept{
    --ptr;
    return *this;
}

template<typename D>
ARRAYiterator<D> ARRAYiterator<D>::operator--(int) noexcept{
    ARRAYiterator<D> temp = *this;
    --(*this);
    return temp;
}

template<typename D>
bool ARRAYiterator<D>::operator!=(const ARRAYiterator<D>& other) const noexcept{ return ptr != other.ptr; }

template<typename D>
bool ARRAYiterator<D>::operator==(const ARRAYiterator<D>& other) const noexcept{ return ptr == other.ptr; }

template<typename D>
bool ARRAYiterator<D>::operator<(const ARRAYiterator<D>& other) const noexcept{ return ptr < other.ptr; }

template<typename D>
bool ARRAYiterator<D>::operator<=(const ARRAYiterator<D>& other) const noexcept{ return ptr <= other.ptr; }

template<typename D>
bool ARRAYiterator<D>::operator>(const ARRAYiterator<D>& other) const noexcept{ return ptr > other.ptr; }

template<typename D>
bool ARRAYiterator<D>::operator>=(const ARRAYiterator<D>& other) const noexcept{ return ptr >= other.ptr; }

template<typename D>
D* ARRAYiterator<D>::operator->(){ return ptr; }

template<typename D>
const D* ARRAYiterator<D>::operator->() const{ return ptr; }


template<typename D>
class ARRAY {
protected:
    size_t Gsrc=0, Gins=0, Gdel=0;
    size_t C=2, S=0;
    bool sd=false;
    D *DATA=nullptr;

    void mergeSort(size_t left, size_t right, D* temp, bool ascend);
    void merge(size_t left, size_t mid, size_t right, D* temp, bool ascend);
    void quickSort(size_t low, size_t high, bool ascend);
    size_t partition(size_t low, size_t high, bool ascend);
    size_t medianOfThree(size_t low, size_t high, bool ascend);
    void heapify(size_t n, size_t root, bool ascend);
    void countingSort(size_t exp, bool ascend);
    void bucketInsertion(D* bucket, size_t n, bool ascend);
    void introSort(size_t low, size_t high, size_t depth, bool ascend);
    size_t introPartition(size_t low, size_t high, bool ascend);
    void timMerge(size_t left, size_t mid, size_t right, bool ascend);
    void timInsertion(size_t left, size_t right, bool ascend);
    void patternDefeatingQuickSort(size_t low, size_t high, size_t depth, bool ascend);
    size_t pdqPartition(size_t low, size_t high, bool ascend);
    bool isRangeSorted(size_t low, size_t high, bool ascend);
    void dualPivotQuickSort(size_t low, size_t high, bool ascend);
    void dualPivotPartition(size_t low, size_t high, size_t& leftPivot, size_t& rightPivot, bool ascend);
    void kWayMergeSort(size_t left, size_t right, size_t k, bool ascend);
    void kWayMerge(size_t left, size_t right, size_t k, bool ascend);
    void bitonicSort(size_t low, size_t count, bool ascend);
    void bitonicMerge(size_t low, size_t count, bool ascend);

    void growth(GROWTH G);
    
public:
    ARRAY(std::initializer_list<D> init);
    ARRAY(size_t len=2);
    ARRAY(const ARRAY& other);
    ARRAY(ARRAY&& other) noexcept;
    ~ARRAY();

    ARRAY& operator=(const ARRAY& other);
    ARRAY& operator=(ARRAY&& other) noexcept;
    D& operator[](std::ptrdiff_t index);
    const D& operator[](std::ptrdiff_t index) const;

    bool operator==(const ARRAY& other) const noexcept;
    bool operator!=(const ARRAY& other) const noexcept;
    bool operator<(const ARRAY& other) const noexcept;
    bool operator<=(const ARRAY& other) const noexcept;
    bool operator>(const ARRAY& other) const noexcept;
    bool operator>=(const ARRAY& other) const noexcept;

    bool insert(D val, long int index=-1);
    size_t drop(D val, bool dup=true);
    D remove(long int index=-1);
    size_t size() const noexcept;
    size_t capacity(size_t len=0) noexcept;
    bool length(long int len, bool f=true);
    size_t resize(bool f);
    void view(bool forward=true) const noexcept;
    void reverse() noexcept;

    bool search_linear(const D& value, size_t &index) noexcept;
    bool search_binary(const D& value, size_t &index) noexcept;

    void sort(SORT S, bool ascend=true);
    void sort_bubble(bool ascend=true);
    void sort_selection(bool ascend=true);
    void sort_insertion(bool ascend=true);
    void sort_merge(bool ascend=true);
    void sort_quick(bool ascend=true);
    void sort_heap(bool ascend=true);
    void sort_shell(bool ascend=true);
    void sort_oddeven(bool ascend=true);
    void sort_cycle(bool ascend=true);
    void sort_counting(bool ascend=true);
    void sort_radix(bool ascend=true);
    void sort_bucket(bool ascend=true);
    void sort_intro(bool ascend=true);
    void sort_tim(bool ascend=true);
    void sort_pattern_defeating_quicksort(bool ascend=true);
    void sort_dual_pivot_quicksort(bool ascend=true);
    void sort_external_merge_sort(bool ascend=true);
    void sort_k_way_merge_sort(bool ascend=true);
    void sort_bitonic_sort(bool ascend=true);
// void sort_block_sort(bool ascend=true);

    ARRAYiterator<D> begin() noexcept;
    ARRAYiterator<D> end() noexcept;
    ARRAYiterator<D> begin() const noexcept;
    ARRAYiterator<D> end() const noexcept;

    ARRAYreverse_iterator<D> rbegin() noexcept;
    ARRAYreverse_iterator<D> rend() noexcept;
    ARRAYreverse_iterator<D> rbegin() const noexcept;
    ARRAYreverse_iterator<D> rend() const noexcept;
};

template<typename D>
void ARRAY<D>::growth(GROWTH G){
    switch (G)
    {
    case GROWTH::GSRC: Gsrc++; break;
    case GROWTH::GINS: Gins++; break;
    case GROWTH::GDEL: Gdel++; break;
    default: return;
    }

    size_t Limit=SIZE_MAX; 
    if(Gsrc==Limit || Gins==Limit || Gdel==Limit)
    {
        Gins>>=2; Gdel>>=2; Gsrc>>=2;
    }
}

template<typename D>
size_t ARRAY<D>::resize(bool f){ size_t len=C;
    if(f)
    {
        if(C<10){ len*=2; sd=false; }
        else{
            sd=false;
            size_t T_Ops = Gins+Gdel+Gsrc;
            float Activity = T_Ops? static_cast<float>(Gins)/T_Ops : 0.0f;
            float Confidence = std::min(1.0f, static_cast<float>(T_Ops)/C);
            float GrowthRate = 10.0f + (90.0f * Activity * Confidence);
            len = C+static_cast<size_t>(C*GrowthRate / 100.0f);
        }}
    else
    {
        if(sd && S>(C/4)) sd=false;
        else{
            if((C>2) && (S<=C/4))
                len = std::max<size_t>(2, C/2);
            else return C;
        }
        return capacity(len);
    }
    Gins>>=1; Gdel>>=1; Gsrc>>=1; 
    return capacity(len);
}

template<typename D>
ARRAY<D>::ARRAY(std::initializer_list<D> init)
    : C(std::max<size_t>(2, init.size())), S(init.size())
{
    DATA = new D[C];
    size_t i=0;
    for(const D& val : init) DATA[i++]=val;
}

template<typename D>
ARRAY<D>::ARRAY(size_t len){ 
    if(len>2){
        C=len; sd=true;
    }
    DATA=new D[C]; 
}

template<typename D>
ARRAY<D>::ARRAY(const ARRAY<D>& other) :S(other.S), C(other.C){ // Growth-Rate will be same as before
    DATA=new D[C];
    for(size_t i=0; i < S; ++i) DATA[i]=other.DATA[i];
}

template<typename D>
ARRAY<D>::ARRAY(ARRAY&& other) noexcept 
    :DATA(other.DATA), S(other.S), C(other.C), Gsrc(other.Gsrc), Gins(other.Gins), Gdel(other.Gdel)
{
    other.DATA=nullptr; other.S=0; other.C=2; other.Gsrc=0; other.Gins=0; other.Gdel=0;
}

template<typename D>
ARRAY<D>::~ARRAY(){ delete[] DATA; }

template<typename D>
D& ARRAY<D>::operator[](std::ptrdiff_t index) {

    if (!S) throw std::runtime_error("Array is empty");
    if (index<0) index += static_cast<long int>(S);
    if (index<0 || static_cast<size_t>(index)>=S) throw std::out_of_range("Array index out of bounds");

    return DATA[index];
}

template<typename D>
const D& ARRAY<D>::operator[](std::ptrdiff_t index) const{

    if (!S) throw std::runtime_error("Array is empty");
    if (index<0) index += static_cast<long int>(S);
    if (index<0 || static_cast<size_t>(index)>=S) throw std::out_of_range("Array index out of bounds");

    return DATA[index];
}

template<typename D>
ARRAY<D>& ARRAY<D>::operator=(const ARRAY<D>& other){ // Growth-Rate will be same as before
    if (this==&other) return *this;

    delete[] DATA;  
    DATA=new D[other.C]; S=other.S; C=other.C;

    for (size_t i=0; i<S; ++i) DATA[i]=other.DATA[i];
    return *this;
}

template<typename D>
ARRAY<D>& ARRAY<D>::operator=(ARRAY&& other) noexcept{
    if (this==&other) return *this;

    delete[] DATA;
    DATA=other.DATA; C=other.C; S=other.S; Gsrc=other.Gsrc; Gins=other.Gins; Gdel=other.Gdel;

    other.DATA=nullptr; other.C=2; other.S=0; other.Gsrc=0; other.Gins=0; other.Gdel=0; 
    return *this;
}

template<typename D>
bool ARRAY<D>::operator==(const ARRAY& other) const noexcept{
    if(S != other.S)
        return false;

    for(size_t i = 0; i < S; ++i)
        if(DATA[i] != other.DATA[i])
            return false;

    return true;
}

template<typename D>
bool ARRAY<D>::operator!=(const ARRAY& other) const noexcept{
    return !(*this == other);
}

template<typename D>
bool ARRAY<D>::operator<(const ARRAY& other) const noexcept{
    size_t n = (S<other.S)? S:other.S;

    for(size_t i = 0; i < n; ++i){
        if(DATA[i] < other.DATA[i]) return true;
        if(DATA[i] > other.DATA[i]) return false;
    }
    return S<other.S;
}

template<typename D>
bool ARRAY<D>::operator<=(const ARRAY& other) const noexcept{
    return !(*this > other);
}

template<typename D>
bool ARRAY<D>::operator>(const ARRAY& other) const noexcept{
    return other < *this;
}

template<typename D>
bool ARRAY<D>::operator>=(const ARRAY& other) const noexcept{
    return !(*this < other);
}

template<typename D>
size_t ARRAY<D>::size() const noexcept{ return S; }

template<typename D>
size_t ARRAY<D>::capacity(size_t len) noexcept{
    if (len == C) return C;
    if(len){
        if(len>C) sd=true;
        
        D *ARR=new D[len];
        size_t i=0;
        while(i<len && i<S){ ARR[i]=DATA[i]; i++; }
        if(len<S) S=len;  C=len; 
        delete []DATA; DATA=ARR; 
        return C; 
    }
    return C;
}

template<typename D>
bool ARRAY<D>::insert(D val, long int index){
    if(S==0 && index!=0 && index!=-1) throw std::runtime_error("Array index out of bound");
    if(S==0){
        DATA[S]=val; S++; growth(GROWTH::GINS); 
        return true;
    }
    if(index==-1 || index==S){
        if(++S>C) resize(true);
        DATA[S-1]=val; growth(GROWTH::GINS); 
        return true;
    }
    if(index<0) index=S+index;
    if(index<0 || index>S) throw std::runtime_error("Array index out of bound");
    else {
        size_t i=S;
        if(++S>C) resize(true);
        while(i>index){ 
            DATA[i]=DATA[i-1]; i--; 
        }
        DATA[i]=val; 
        growth(GROWTH::GINS); return true;
    }
    return false;
}

template<typename D>
size_t ARRAY<D>::drop(D val, bool dup){
    size_t cnt=1;
    if(S==0) throw std::runtime_error("Array is empty");
    size_t i=0;
    while(i<S && DATA[i]!=val) i++;
    if(dup){ 
        if(i==S) throw std::runtime_error("Elements not found!");
        size_t w=i, r=i;
        while(r<S){
            if(DATA[r] != val) DATA[w++] = DATA[r];
            r++;
        }
        size_t rmv=S-w; cnt=rmv;
        while(rmv--) DATA[--S]=D();
    } else {
        if(i==S) throw std::runtime_error("Element not found!");
        while(i<(S-1)){ 
            DATA[i]=DATA[i+1]; i++;
        }   DATA[i]=D();
        S--; 
    }
    growth(GROWTH::GDEL);
    resize(false);
    return cnt;
}

template<typename D>
D ARRAY<D>::remove(long int index){
    D tmp;
    if(S==0) throw std::runtime_error("Arrat is empty");
    if(index==-1){
        S--; tmp=DATA[S]; DATA[S]=D(); growth(GROWTH::GDEL);
        resize(false); return tmp;
    }
    if(index<0) index=S+index;
    if(index<0 || index>=S) throw std::runtime_error("Array index out of bound");

    size_t i=index; tmp=DATA[i];
    while(i<(S-1)){ DATA[i]=DATA[i+1]; i++; }
    DATA[i]=D(); 
    S--; growth(GROWTH::GDEL);

    resize(false);
    return tmp;
}

template<typename D>
void ARRAY<D>::view(bool forward) const noexcept{
    if(!S) std::cout<<"[]";
    else if(forward){
        std::cout<<"[";
        size_t i=0;
        for(; i<(S-1); i++) std::cout<<DATA[i]<<", ";
        std::cout<<DATA[i]<<"]";
    } else {
        std::cout<<"[";
        size_t i=S-1;
        for(; i>0; i--) std::cout<<DATA[i]<<", ";
        std::cout<<DATA[i]<<"]";
    }
}

template<typename D>
bool ARRAY<D>::length(long int len, bool f){
    if(!S) return false;

    if(len<0 && static_cast<size_t>(-len)>=S){ //if reduce elements > store elements
        size_t i=0;
        while(i<S) DATA[i++]=D(); S=0;
        growth(GROWTH::GDEL);
        resize(false);

    } else if(len>0 && f){ //increse back
        sd=true;
        size_t Si=S+static_cast<size_t>(len);
        if(Si>C) capacity(Si);
        while(S<Si) DATA[S++]=D(); 

    } else if(len<0 && f){ //reduce back
        size_t Si=S; S-=static_cast<size_t>(-len); size_t i=S;
        while(i<Si) DATA[i++]=D();
        growth(GROWTH::GDEL);
        resize(false);

    } else if(len>0 && !f){ //increse front
        sd=true;
        size_t Si=S-1; S+=static_cast<size_t>(len); size_t i=S-1;
        if(S>C) capacity(S);
        while(Si>0) 
            DATA[i--]=DATA[Si--]; DATA[i]=DATA[Si];
        while(i>0) 
            DATA[--i]=D(); 

    } else if(len<0 && !f){ //reduce front
        size_t leni=static_cast<size_t>(-len);
        size_t i=0; while(leni<S) DATA[i++]=DATA[leni++]; 
        S+=len; 
        while(i<S) DATA[i++]=D();
        growth(GROWTH::GDEL);
        resize(false);

    } else {
        capacity(S); //round of 
    }
    return true;
}

template<typename D>
void ARRAY<D>::reverse() noexcept{
    if(S<2) return;

    size_t l=0, r=S-1;
    while(l<r){
        std::swap(DATA[l], DATA[r]);
        ++l; --r;
    }
}

template<typename D>
ARRAYiterator<D> ARRAY<D>::begin() noexcept{ return ARRAYiterator<D>(DATA); }

template<typename D>
ARRAYiterator<D> ARRAY<D>::begin() const noexcept{ return ARRAYiterator<D>(DATA); }

template<typename D>
ARRAYiterator<D> ARRAY<D>::end() noexcept{ return ARRAYiterator<D>(DATA+S); }

template<typename D>
ARRAYiterator<D> ARRAY<D>::end() const noexcept{ return ARRAYiterator<D>(DATA+S); }

template<typename D>
ARRAYreverse_iterator<D> ARRAY<D>::rbegin() noexcept{ return ARRAYreverse_iterator<D>(S? DATA+ S-1 : DATA-1); }

template<typename D>
ARRAYreverse_iterator<D> ARRAY<D>::rbegin() const noexcept{ return ARRAYreverse_iterator<D>(S? DATA+ S-1 : DATA-1); }

template<typename D>
ARRAYreverse_iterator<D> ARRAY<D>::rend() noexcept{ return ARRAYreverse_iterator<D>(DATA-1); }

template<typename D>
ARRAYreverse_iterator<D> ARRAY<D>::rend() const noexcept{ return ARRAYreverse_iterator<D>(DATA-1); }

template<typename D>
bool ARRAY<D>::search_linear(const D& val, size_t &index) noexcept
{
    if(S==0) 
        { index=SIZE_MAX; return false; }
    growth(GROWTH::GSRC);

    size_t i=S;
    while(i--)
        if(DATA[i]==val){ index=i; return true; }

    index=SIZE_MAX; return false;
}

template<typename D>
bool ARRAY<D>::search_binary(const D& val, size_t &index) noexcept
{
    if(S==0) 
        { index=SIZE_MAX; return false; }
    growth(GROWTH::GSRC);

    size_t l=0, h=S-1;
    while(l<=h)
    {
        size_t m=l+(h-l) / 2;
        if(DATA[m]==val){ index=m; return true; }
        if(DATA[m]<val) l=m+1;
        else 
           { if(m==0) break; h=m-1; }  
    }
    index=SIZE_MAX; return false;
}

template<typename D>
void ARRAY<D>::sort(SORT S, bool ascend)
{
    switch(S)
    {
        case SORT::BUBBLE:           sort_bubble(ascend);                      break;
        case SORT::SELECTION:        sort_selection(ascend);                   break;
        case SORT::INSERTION:        sort_insertion(ascend);                   break;
        case SORT::MERGE:            sort_merge(ascend);                       break;
        case SORT::QUICK:            sort_quick(ascend);                       break;
        case SORT::HEAP:             sort_heap(ascend);                        break;
        case SORT::SHELL:            sort_shell(ascend);                       break;
        case SORT::ODDEVEN:          sort_oddeven(ascend);                     break;
        case SORT::CYCLE:            sort_cycle(ascend);                       break;
        case SORT::COUNTING:         sort_counting(ascend);                    break;
        case SORT::RADIX:            sort_radix(ascend);                       break;
        case SORT::BUCKET:           sort_bucket(ascend);                      break;
        case SORT::INTRO:            sort_intro(ascend);                       break;
        case SORT::TIM:              sort_tim(ascend);                         break;
        case SORT::PDQ:              sort_pattern_defeating_quicksort(ascend); break;
        case SORT::DUAL_PIVOT:       sort_dual_pivot_quicksort(ascend);        break;
        case SORT::EXTERNAL_MERGE:   sort_external_merge_sort(ascend);         break;
        case SORT::K_WAY_MERGE:      sort_k_way_merge_sort(ascend);            break;
        case SORT::BITONIC:          sort_bitonic_sort(ascend);                break;

        default:
            throw std::invalid_argument("Invalid sorting algorithm.");
    }
}

template<typename D>
void ARRAY<D>::sort_bubble(bool ascend){
    if(S < 2) return;

    for(size_t end = S - 1; end > 0; --end){
        bool swapped = false;

        for(size_t i = 0; i < end; ++i){
            if((ascend && DATA[i] > DATA[i + 1]) ||
               (!ascend && DATA[i] < DATA[i + 1])){
                std::swap(DATA[i], DATA[i + 1]);
                swapped = true;
            }
        }

        if(!swapped) break;
    }
}

template<typename D>
void ARRAY<D>::sort_selection(bool ascend){
    if(S < 2) return;

    for(size_t i = 0; i < S - 1; ++i){
        size_t best = i;

        for(size_t j = i + 1; j < S; ++j){
            if((ascend && DATA[j] < DATA[best]) ||
               (!ascend && DATA[j] > DATA[best])){
                best = j;
            }
        }

        if(best != i)
            std::swap(DATA[i], DATA[best]);
    }
}

template<typename D>
void ARRAY<D>::sort_insertion(bool ascend){
    if(S < 2) return;

    for(size_t i = 1; i < S; ++i){
        D key = DATA[i];
        size_t j = i;

        while(j > 0 &&
             ((ascend && DATA[j - 1] > key) ||
              (!ascend && DATA[j - 1] < key))){
            DATA[j] = DATA[j - 1];
            --j;
        }

        DATA[j] = key;
    }
}

template<typename D>
void ARRAY<D>::sort_merge(bool ascend){
    if (S <= 1)
        return;

    D* temp = new D[S];

    mergeSort(0, S - 1, temp, ascend);

    delete[] temp;
}

template<typename D>
void ARRAY<D>::mergeSort(size_t left, size_t right, D* temp, bool ascend){
    if (left >= right)
        return;

    size_t mid = left + (right - left) / 2;


    mergeSort(left, mid, temp, ascend);
    mergeSort(mid + 1, right, temp, ascend);


    merge(left, mid, right, temp, ascend);
}

template<typename D>
void ARRAY<D>::merge(size_t left, size_t mid, size_t right, D* temp, bool ascend){
    size_t i = left;
    size_t j = mid + 1;
    size_t k = left;

    while (i <= mid && j <= right){
        bool condition;

        if (ascend)
            condition = DATA[i] <= DATA[j];
        else
            condition = DATA[i] >= DATA[j];


        if (condition)
            temp[k++] = DATA[i++];
        else
            temp[k++] = DATA[j++];
    }

    while (i <= mid){
        temp[k++] = DATA[i++];
    }

    while (j <= right){
        temp[k++] = DATA[j++];
    }


    for (size_t x = left; x <= right; x++){
        DATA[x] = temp[x];
    }
}

template<typename D>
void ARRAY<D>::sort_quick(bool ascend){
    if (S <= 1)
        return;

    quickSort(0, S - 1, ascend);
}

template<typename D>
void ARRAY<D>::quickSort(size_t low, size_t high, bool ascend){
    if (low < high)
    {
        size_t pivot = partition(low, high, ascend);

        if (pivot > 0)
            quickSort(low, pivot - 1, ascend);

        quickSort(pivot + 1, high, ascend);
    }
}

template<typename D>
size_t ARRAY<D>::partition(size_t low, size_t high, bool ascend){
    size_t pivotIndex = medianOfThree(low, high, ascend);

    D pivot = DATA[pivotIndex];

    D temp = DATA[pivotIndex];
    DATA[pivotIndex] = DATA[high];
    DATA[high] = temp;

    size_t i = low;

    for (size_t j = low; j < high; j++)
    {
        bool condition;

        if (ascend)
            condition = DATA[j] < pivot;
        else
            condition = DATA[j] > pivot;


        if (condition)
        {
            temp = DATA[i];
            DATA[i] = DATA[j];
            DATA[j] = temp;

            i++;
        }
    }

    temp = DATA[i];
    DATA[i] = DATA[high];
    DATA[high] = temp;

    return i;
}

template<typename D>
size_t ARRAY<D>::medianOfThree(size_t low, size_t high, bool ascend){
    size_t mid = low + (high - low) / 2;

    D &a = DATA[low];
    D &b = DATA[mid];
    D &c = DATA[high];

    if (ascend)
    {
        if (a < b)
        {
            if (b < c) return mid;
            else if (a < c) return high;
            else return low;
        }
        else
        {
            if (a < c) return low;
            else if (b < c) return high;
            else return mid;
        }
    }
    else
    {
        if (a > b)
        {
            if (b > c) return mid;
            else if (a > c) return high;
            else return low;
        }
        else
        {
            if (a > c) return low;
            else if (b > c) return high;
            else return mid;
        }
    }
}

template<typename D>
void ARRAY<D>::sort_heap(bool ascend){
    if(S < 2) return;

    for(size_t i = S / 2; i > 0; --i)
        heapify(S, i - 1, ascend);

    for(size_t i = S - 1; i > 0; --i)
    {
        D temp = DATA[0];
        DATA[0] = DATA[i];
        DATA[i] = temp;

        heapify(i, 0, ascend);
    }
}

template<typename D>
void ARRAY<D>::heapify(size_t n, size_t root, bool ascend){
    size_t largest = root;
    size_t left = (2 * root) + 1;
    size_t right = (2 * root) + 2;

    if(ascend)
    {
        if(left < n && DATA[left] > DATA[largest])
            largest = left;

        if(right < n && DATA[right] > DATA[largest])
            largest = right;
    }
    else
    {
        if(left < n && DATA[left] < DATA[largest])
            largest = left;

        if(right < n && DATA[right] < DATA[largest])
            largest = right;
    }

    if(largest != root)
    {
        D temp = DATA[root];
        DATA[root] = DATA[largest];
        DATA[largest] = temp;

        heapify(n, largest, ascend);
    }
}

template<typename D>
void ARRAY<D>::sort_shell(bool ascend){
    if(S < 2) return;

    static const size_t gaps[] = {701,301,132,57,23,10,4,1};

    for(size_t gap : gaps){
        if(gap >= S) continue;

        for(size_t i = gap; i < S; ++i){
            D temp = DATA[i];
            size_t j = i;

            while(j >= gap &&
                  ((ascend && DATA[j-gap] > temp) ||
                   (!ascend && DATA[j-gap] < temp))){
                DATA[j] = DATA[j-gap];
                j -= gap;
            }

            DATA[j] = temp;
        }
    }
}

template<typename D>
void ARRAY<D>::sort_oddeven(bool ascend){
    if(S < 2) return;

    bool sorted = false;

    while(!sorted){
        sorted = true;

        for(size_t i = 1; i < S-1; i += 2){
            if((ascend && DATA[i] > DATA[i+1]) ||
               (!ascend && DATA[i] < DATA[i+1])){
                std::swap(DATA[i], DATA[i+1]);
                sorted = false;
            }
        }

        for(size_t i = 0; i < S-1; i += 2){
            if((ascend && DATA[i] > DATA[i+1]) ||
               (!ascend && DATA[i] < DATA[i+1])){
                std::swap(DATA[i], DATA[i+1]);
                sorted = false;
            }
        }
    }
}

template<typename D>
void ARRAY<D>::sort_cycle(bool ascend){
    if(S < 2) return;

    for(size_t cycleStart = 0; cycleStart < S-1; ++cycleStart){
        D item = DATA[cycleStart];
        size_t pos = cycleStart;

        for(size_t i = cycleStart+1; i < S; ++i){
            if((ascend && DATA[i] < item) ||
               (!ascend && DATA[i] > item))
                ++pos;
        }

        if(pos == cycleStart)
            continue;

        while(item == DATA[pos])
            ++pos;

        std::swap(item, DATA[pos]);

        while(pos != cycleStart){
            pos = cycleStart;

            for(size_t i = cycleStart+1; i < S; ++i){
                if((ascend && DATA[i] < item) ||
                   (!ascend && DATA[i] > item))
                    ++pos;
            }

            while(item == DATA[pos])
                ++pos;

            std::swap(item, DATA[pos]);
        }
    }
}

template<typename D>
void ARRAY<D>::sort_counting(bool ascend){
    if(S < 2) return;

    D mn = DATA[0];
    D mx = DATA[0];

    for(size_t i = 1; i < S; ++i){
        if(DATA[i] < mn) mn = DATA[i];
        if(DATA[i] > mx) mx = DATA[i];
    }

    size_t range = static_cast<size_t>(mx - mn + 1);

    size_t* count = new size_t[range]();

    for(size_t i = 0; i < S; ++i)
        ++count[DATA[i] - mn];

    size_t k = 0;

    if(ascend){
        for(size_t i = 0; i < range; ++i)
            while(count[i]--)
                DATA[k++] = static_cast<D>(i + mn);
    }
    else{
        for(size_t i = range; i-- > 0; )
            while(count[i]--)
                DATA[k++] = static_cast<D>(i + mn);
    }

    delete[] count;
}

template<typename D>
void ARRAY<D>::sort_radix(bool ascend){
    if(S < 2) return;

    D max = DATA[0];

    for(size_t i = 1; i < S; i++)
    {
        if(DATA[i] > max)
            max = DATA[i];
    }

    for(size_t exp = 1; max / exp > 0; exp *= 10)
        countingSort(exp, ascend);
}

template<typename D>
void ARRAY<D>::countingSort(size_t exp, bool ascend){
    D* output = new D[S];
    size_t count[10] = {0};

    for(size_t i = 0; i < S; i++)
    {
        size_t digit = (DATA[i] / exp) % 10;
        count[digit]++;
    }

    if(ascend)
    {
        for(size_t i = 1; i < 10; i++)
            count[i] += count[i - 1];
    }
    else
    {
        for(size_t i = 8; i != (size_t)-1; i--)
            count[i] += count[i + 1];
    }

    for(size_t i = S; i > 0; i--)
    {
        size_t index = i - 1;
        size_t digit = (DATA[index] / exp) % 10;

        output[count[digit] - 1] = DATA[index];
        count[digit]--;
    }

    for(size_t i = 0; i < S; i++)
        DATA[i] = output[i];

    delete[] output;
}

template<typename D>
void ARRAY<D>::sort_bucket(bool ascend){
    if(S < 2) return;

    D min = DATA[0];
    D max = DATA[0];

    for(size_t i = 1; i < S; i++)
    {
        if(DATA[i] < min)
            min = DATA[i];

        if(DATA[i] > max)
            max = DATA[i];
    }

    size_t bucketCount = S;

    D** buckets = new D*[bucketCount];
    size_t* sizes = new size_t[bucketCount]{};

    for(size_t i = 0; i < bucketCount; i++)
        buckets[i] = new D[S];

    for(size_t i = 0; i < S; i++)
    {
        size_t index = ((DATA[i] - min) * (bucketCount - 1)) / (max - min + 1);
        buckets[index][sizes[index]++] = DATA[i];
    }

    for(size_t i = 0; i < bucketCount; i++)
    {
        bucketInsertion(buckets[i], sizes[i], ascend);
    }

    size_t pos = 0;

    if(ascend)
    {
        for(size_t i = 0; i < bucketCount; i++)
        {
            for(size_t j = 0; j < sizes[i]; j++)
                DATA[pos++] = buckets[i][j];
        }
    }
    else
    {
        for(size_t i = bucketCount; i > 0; i--)
        {
            size_t index = i - 1;

            for(size_t j = 0; j < sizes[index]; j++)
                DATA[pos++] = buckets[index][j];
        }
    }

    for(size_t i = 0; i < bucketCount; i++)
        delete[] buckets[i];

    delete[] buckets;
    delete[] sizes;
}

template<typename D>
void ARRAY<D>::bucketInsertion(D* bucket, size_t n, bool ascend){
    for(size_t i = 1; i < n; i++)
    {
        D temp = bucket[i];
        size_t j = i;

        while(j > 0 &&
             ((ascend && bucket[j-1] > temp) ||
              (!ascend && bucket[j-1] < temp)))
        {
            bucket[j] = bucket[j-1];
            j--;
        }

        bucket[j] = temp;
    }
}

template<typename D>
void ARRAY<D>::sort_intro(bool ascend){
    if(S < 2) return;

    size_t depth = 2 * static_cast<size_t>(log2(S));

    introSort(0, S - 1, depth, ascend);
}

template<typename D>
void ARRAY<D>::introSort(size_t low, size_t high, size_t depth, bool ascend){
    if(low >= high)
        return;

    if(depth == 0)
    {
        size_t n = high - low + 1;

        for(size_t i = n / 2; i > 0; i--)
            heapify(n, i - 1, ascend);

        for(size_t i = n - 1; i > 0; i--)
        {
            D temp = DATA[low];
            DATA[low] = DATA[low + i];
            DATA[low + i] = temp;

            heapify(i, 0, ascend);
        }

        return;
    }

    size_t pivot = introPartition(low, high, ascend);

    if(pivot > 0)
        introSort(low, pivot - 1, depth - 1, ascend);

    introSort(pivot + 1, high, depth - 1, ascend);
}

template<typename D>
size_t ARRAY<D>::introPartition(size_t low, size_t high, bool ascend){
    D pivot = DATA[high];

    size_t i = low;

    for(size_t j = low; j < high; j++)
    {
        if((ascend && DATA[j] < pivot) ||
           (!ascend && DATA[j] > pivot))
        {
            D temp = DATA[i];
            DATA[i] = DATA[j];
            DATA[j] = temp;

            i++;
        }
    }

    D temp = DATA[i];
    DATA[i] = DATA[high];
    DATA[high] = temp;

    return i;
}

template<typename D>
void ARRAY<D>::sort_tim(bool ascend){
    if(S < 2) return;

    const size_t RUN = 32;

    for(size_t i = 0; i < S; i += RUN)
    {
        size_t right = (i + RUN - 1 < S - 1) ? i + RUN - 1 : S - 1;
        timInsertion(i, right, ascend);
    }

    for(size_t size = RUN; size < S; size *= 2)
    {
        for(size_t left = 0; left < S; left += 2 * size)
        {
            size_t mid = left + size - 1;

            if(mid >= S - 1)
                continue;

            size_t right = left + 2 * size - 1;

            if(right >= S)
                right = S - 1;

            timMerge(left, mid, right, ascend);
        }
    }
}

template<typename D>
void ARRAY<D>::timMerge(size_t left, size_t mid, size_t right, bool ascend){
    size_t n1 = mid - left + 1;
    size_t n2 = right - mid;

    D* L = new D[n1];
    D* R = new D[n2];

    for(size_t i = 0; i < n1; i++)
        L[i] = DATA[left + i];

    for(size_t i = 0; i < n2; i++)
        R[i] = DATA[mid + 1 + i];

    size_t i = 0;
    size_t j = 0;
    size_t k = left;

    while(i < n1 && j < n2)
    {
        if((ascend && L[i] <= R[j]) ||
           (!ascend && L[i] >= R[j]))
            DATA[k++] = L[i++];
        else
            DATA[k++] = R[j++];
    }

    while(i < n1)
        DATA[k++] = L[i++];

    while(j < n2)
        DATA[k++] = R[j++];

    delete[] L;
    delete[] R;
}

template<typename D>
void ARRAY<D>::timInsertion(size_t left, size_t right, bool ascend){
    for(size_t i = left + 1; i <= right; i++)
    {
        D temp = DATA[i];
        size_t j = i;

        while(j > left &&
             ((ascend && DATA[j - 1] > temp) ||
              (!ascend && DATA[j - 1] < temp)))
        {
            DATA[j] = DATA[j - 1];
            j--;
        }

        DATA[j] = temp;
    }
}

template<typename D>
void ARRAY<D>::sort_pattern_defeating_quicksort(bool ascend){
    if(S < 2) return;

    size_t depth = 2 * (size_t)std::log2(S);
    patternDefeatingQuickSort(0, S - 1, depth, ascend);
}

template<typename D>
void ARRAY<D>::patternDefeatingQuickSort(size_t low, size_t high, size_t depth, bool ascend)
{
    while(low < high)
    {
        if(isRangeSorted(low, high, ascend))
            return;

        if(depth == 0)
        {
            // Fallback to Heap Sort later if you implement one.
            // sort_heap(low, high);
            return;
        }

        depth--;

        size_t pivot = pdqPartition(low, high, ascend);

        if(pivot - low < high - pivot)
        {
            if(pivot > low)
                patternDefeatingQuickSort(low, pivot - 1, depth, ascend);

            low = pivot + 1;
        }
        else
        {
            if(pivot < high)
                patternDefeatingQuickSort(pivot + 1, high, depth, ascend);

            if(pivot==0) break;
            high = pivot - 1;
        }
    }
}

template<typename D>
size_t ARRAY<D>::pdqPartition(size_t low, size_t high, bool ascend)
{
    size_t mid = low + (high - low) / 2;

    if(ascend)
    {
        if(DATA[mid] < DATA[low]) std::swap(DATA[mid], DATA[low]);
        if(DATA[high] < DATA[low]) std::swap(DATA[high], DATA[low]);
        if(DATA[high] < DATA[mid]) std::swap(DATA[high], DATA[mid]);
    }
    else
    {
        if(DATA[mid] > DATA[low]) std::swap(DATA[mid], DATA[low]);
        if(DATA[high] > DATA[low]) std::swap(DATA[high], DATA[low]);
        if(DATA[high] > DATA[mid]) std::swap(DATA[high], DATA[mid]);
    }

    std::swap(DATA[mid], DATA[high]);

    D pivot = DATA[high];

    size_t i = low;

    for(size_t j = low; j < high; j++)
    {
        bool cond = ascend ? (DATA[j] < pivot)
                           : (DATA[j] > pivot);

        if(cond)
        {
            std::swap(DATA[i], DATA[j]);
            i++;
        }
    }

    std::swap(DATA[i], DATA[high]);

    return i;
}

template<typename D>
bool ARRAY<D>::isRangeSorted(size_t low, size_t high, bool ascend)
{
    if(high <= low)
        return true;

    if(ascend)
    {
        for(size_t i = low + 1; i <= high; i++)
            if(DATA[i] < DATA[i - 1])
                return false;
    }
    else
    {
        for(size_t i = low + 1; i <= high; i++)
            if(DATA[i] > DATA[i - 1])
                return false;
    }

    return true;
}

template<typename D>
void ARRAY<D>::sort_dual_pivot_quicksort(bool ascend)
{
    if(S < 2)
        return;

    dualPivotQuickSort(0, S - 1, ascend);
}

template<typename D>
void ARRAY<D>::dualPivotQuickSort(size_t low, size_t high, bool ascend)
{
    if(low >= high)
        return;

    size_t lp, rp;

    dualPivotPartition(low, high, lp, rp, ascend);

    if(lp > low)
        dualPivotQuickSort(low, lp - 1, ascend);

    if(lp + 1 < rp)
        dualPivotQuickSort(lp + 1, rp - 1, ascend);

    if(rp < high)
        dualPivotQuickSort(rp + 1, high, ascend);
}

template<typename D>
void ARRAY<D>::dualPivotPartition(size_t low, size_t high, size_t& leftPivot, size_t& rightPivot, bool ascend)
{
    if(ascend)
    {
        if(DATA[low] > DATA[high])
            std::swap(DATA[low], DATA[high]);
    }
    else
    {
        if(DATA[low] < DATA[high])
            std::swap(DATA[low], DATA[high]);
    }

    D p = DATA[low];
    D q = DATA[high];

    size_t lt = low + 1;
    size_t gt = high - 1;
    size_t i = lt;

    while(i <= gt)
    {
        if(ascend)
        {
            if(DATA[i] < p)
            {
                std::swap(DATA[i], DATA[lt]);
                lt++;
            }
            else if(DATA[i] > q)
            {
                while(i < gt && DATA[gt] > q)
                    gt--;

                std::swap(DATA[i], DATA[gt]);
                gt--;

                if(DATA[i] < p)
                {
                    std::swap(DATA[i], DATA[lt]);
                    lt++;
                }
            }
        }
        else
        {
            if(DATA[i] > p)
            {
                std::swap(DATA[i], DATA[lt]);
                lt++;
            }
            else if(DATA[i] < q)
            {
                while(i < gt && DATA[gt] < q)
                    gt--;

                std::swap(DATA[i], DATA[gt]);
                gt--;

                if(DATA[i] > p)
                {
                    std::swap(DATA[i], DATA[lt]);
                    lt++;
                }
            }
        }

        i++;
    }

    lt--;
    gt++;

    std::swap(DATA[low], DATA[lt]);
    std::swap(DATA[high], DATA[gt]);

    leftPivot = lt;
    rightPivot = gt;
}

template<typename D>
void ARRAY<D>::sort_external_merge_sort(bool ascend)
{
    if(S < 2)
        return;

    D* temp = new D[S];

    mergeSort(0, S - 1, temp, ascend);

    delete[] temp;
}

template<typename D>
void ARRAY<D>::sort_k_way_merge_sort(bool ascend)
{
    if(S < 2)
        return;

    kWayMergeSort(0, S - 1, 4, ascend);
}

template<typename D>
void ARRAY<D>::kWayMergeSort(size_t left, size_t right, size_t k, bool ascend)
{
    if(left >= right)
        return;

    if(k < 2)
        k = 2;

    size_t n = right - left + 1;

    if(n <= k)
    {
        for(size_t i = left + 1; i <= right; i++)
        {
            D key = DATA[i];
            size_t j = i;

            while(j > left &&
                 (ascend ? DATA[j-1] > key
                         : DATA[j-1] < key))
            {
                DATA[j] = DATA[j-1];
                j--;
            }

            DATA[j] = key;
        }

        return;
    }

    size_t part = n / k;
    size_t rem  = n % k;

    size_t start = left;

    for(size_t i=0;i<k;i++)
    {
        size_t len = part + (i < rem);

        if(len==0)
            break;

        size_t end = start + len - 1;

        kWayMergeSort(start,end,k,ascend);

        start = end + 1;
    }

    kWayMerge(left,right,k,ascend);
}

template<typename D>
void ARRAY<D>::kWayMerge(size_t left, size_t right, size_t k, bool ascend)
{
    size_t n = right - left + 1;

    D* temp = new D[n];

    size_t part = n / k;
    size_t rem  = n % k;

    size_t starts[32];
    size_t ends[32];

    size_t cur = left;

    for(size_t i=0;i<k;i++)
    {
        size_t len = part + (i < rem);

        if(len==0)
        {
            starts[i]=ends[i]=0;
            continue;
        }

        starts[i]=cur;
        ends[i]=cur+len-1;

        cur=ends[i]+1;
    }

    size_t idx=0;

    while(true)
    {
        int best=-1;

        for(size_t i=0;i<k;i++)
        {
            if(starts[i]>ends[i])
                continue;

            if(best==-1)
            {
                best=i;
                continue;
            }

            if(ascend)
            {
                if(DATA[starts[i]]<DATA[starts[best]])
                    best=i;
            }
            else
            {
                if(DATA[starts[i]]>DATA[starts[best]])
                    best=i;
            }
        }

        if(best==-1)
            break;

        temp[idx++] = DATA[starts[best]++];
    }

    for(size_t i=0;i<n;i++)
        DATA[left+i]=temp[i];

    delete[] temp;
}

template<typename D>
void ARRAY<D>::sort_bitonic_sort(bool ascend)
{
    if(S < 2)
        return;

    if((S & (S - 1)) != 0)
        throw std::invalid_argument("Bitonic sort requires array size to be a power of two.");

    bitonicSort(0, S, ascend);
}

template<typename D>
void ARRAY<D>::bitonicSort(size_t low, size_t count, bool ascend)
{
    if(count<=1)
        return;

    size_t mid = count/2;

    bitonicSort(low,mid,true);

    bitonicSort(low+mid,
                count-mid,
                false);

    bitonicMerge(low,count,ascend);
}

template<typename D>
void ARRAY<D>::bitonicMerge(size_t low, size_t count, bool ascend)
{
    if(count<=1)
        return;

    size_t mid = count/2;

    for(size_t i=low;i<low+mid;i++)
    {
        bool swapNeeded =
            ascend ?
            (DATA[i] > DATA[i+mid]) :
            (DATA[i] < DATA[i+mid]);

        if(swapNeeded)
            std::swap(DATA[i],DATA[i+mid]);
    }

    bitonicMerge(low,mid,ascend);

    bitonicMerge(low+mid, count-mid, ascend);
}

template<typename D>
std::ostream& operator<<(std::ostream& out, const ARRAY<D>& a){ a.view(); return out; }



// int main()
// {
//     ARRAY<ARRAY<int>> mat =
//     {
//         {1, 2, 3},
//         {4, 5, 6},
//         {7, 8, 9}
//     };

//     std::cout << "2D Matrix:\n";

//     for(size_t i = 0; i < mat.size(); ++i)
//     {
//         for(size_t j = 0; j < mat[i].size(); ++j)
//             std::cout << mat[i][j] << ' ';

//         std::cout << '\n';
//     }

//     std::cout << '\n' << mat << "\n\n";


//     // ===================== 3D ARRAY =====================

//     ARRAY<ARRAY<ARRAY<int>>> cube =
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

//     std::cout << "3D Matrix:\n";

//     for(size_t i = 0; i < cube.size(); ++i)
//     {
//         std::cout << "Layer " << i << ":\n";

//         for(size_t j = 0; j < cube[i].size(); ++j)
//         {
//             for(size_t k = 0; k < cube[i][j].size(); ++k)
//                 std::cout << cube[i][j][k] << ' ';

//             std::cout << '\n';
//         }

//         std::cout << '\n';
//     }

//     std::cout << cube << '\n';

//     return 0;
// }


// int main()
// {
//     std::cout << "========== INITIALIZER LIST ==========\n";

//     ARRAY<int> A = {1,2,3,4,5};
//     ARRAY<int> B{1,2,3,4,5};
//     ARRAY<int> C = {1,2,3,4,6};
//     ARRAY<int> D = {1,2,3};
//     ARRAY<int> E = {2,1,3,4,5};
//     ARRAY<int> F = {};

//     std::cout << "A = "; A.view();
//     std::cout << "B = "; B.view();
//     std::cout << "C = "; C.view();
//     std::cout << "D = "; D.view();
//     std::cout << "E = "; E.view();
//     std::cout << "F = "; F.view();

//     std::cout << "\n========== SIZE / CAPACITY ==========\n";
//     std::cout << "A : Size = " << A.size()
//               << "  Capacity = " << A.capacity() << '\n';

//     std::cout << "F : Size = " << F.size()
//               << "  Capacity = " << F.capacity() << '\n';

//     std::cout << "\n========== COMPARISON ==========\n";

//     std::cout << "A == B : " << (A == B) << '\n';
//     std::cout << "A != B : " << (A != B) << '\n';

//     std::cout << "A == C : " << (A == C) << '\n';
//     std::cout << "A != C : " << (A != C) << '\n';

//     std::cout << "A < C  : " << (A < C) << '\n';
//     std::cout << "C > A  : " << (C > A) << '\n';

//     std::cout << "D < A  : " << (D < A) << '\n';
//     std::cout << "A > D  : " << (A > D) << '\n';

//     std::cout << "E > A  : " << (E > A) << '\n';
//     std::cout << "A < E  : " << (A < E) << '\n';

//     std::cout << "A <= B : " << (A <= B) << '\n';
//     std::cout << "A >= B : " << (A >= B) << '\n';

//     std::cout << "A <= C : " << (A <= C) << '\n';
//     std::cout << "A >= C : " << (A >= C) << '\n';

//     std::cout << "\n========== INDEX OPERATOR ==========\n";

//     std::cout << "A[0]  = " << A[0] << '\n';
//     std::cout << "A[2]  = " << A[2] << '\n';
//     std::cout << "A[-1] = " << A[-1] << '\n';
//     std::cout << "A[-2] = " << A[-2] << '\n';

//     std::cout << "\n========== FORWARD ITERATOR ==========\n";

//     for(auto it=A.begin(); it!=A.end(); ++it)
//         std::cout << *it << ' ';
//     std::cout << '\n';

//     std::cout << "\n========== RANGE-BASED FOR ==========\n";

//     for(const auto &x : A)
//         std::cout << x << ' ';
//     std::cout << '\n';

//     std::cout << "\n========== REVERSE ITERATOR ==========\n";

//     for(auto it=A.rbegin(); it!=A.rend(); ++it)
//         std::cout << *it << ' ';
    
//     std::cout << "\n==========  ==========\n";

//     ARRAY<int> G = {1,2,3,4};
//     ARRAY<int> H = {1,2,3,4,5};

//     std::cout << "G < H : " << (G < H) << '\n';
//     std::cout << "H > G : " << (H > G) << '\n';

//     ARRAY<int> I = {5};
//     ARRAY<int> J = {5};

//     std::cout << "I == J : " << (I == J) << '\n';

//     ARRAY<int> K = {5};
//     ARRAY<int> L = {4};

//     std::cout << "K > L : " << (K > L) << '\n';
//     std::cout << "K < L : " << (K < L) << '\n';

//     ARRAY<int> M = {};

//     std::cout << "M == F : " << (M == F) << '\n';
//     std::cout << "M <= F : " << (M <= F) << '\n';
//     std::cout << "M >= F : " << (M >= F) << '\n';


//     return 0;
// }


// int main()
// {
//     std::cout << "========== USER FIXED CAPACITY ==========\n";

//     ARRAY<int> arr(200);   // User requests a large initial capacity

//     std::cout << "Initial\n";
//     std::cout << "Size = " << arr.size()
//               << "  Capacity = " << arr.capacity() << "\n\n";

//     // Fill 5x the initial capacity
//     for (int i = 1; i <= 20; i++)
//         arr.insert(i);

//     std::cout << "After inserting 20 elements\n";
//     std::cout << "Size = " << arr.size()
//               << "  Capacity = " << arr.capacity() << "\n\n";

//     // Remove one element
//     arr.remove();

//     std::cout << "After removing ONE element\n";
//     std::cout << "Size = " << arr.size()
//               << "  Capacity = " << arr.capacity() << "\n";

//     std::cout << "\nCapacity should NOT shrink here.\n\n";

//     for (int i = 1; i <= 70; i++)
//         arr.insert(i);

//     for (int i = 1; i <= 70; i++)
//         arr.remove();

//     std::cout << "After one more deletion (shrink expected)\n";
//     std::cout << "Size = " << arr.size()
//               << "  Capacity = " << arr.capacity() << "\n";

//     return 0;
// }

// template<typename D>
// void printState(ARRAY<D>& arr, const char* name)
// {
//     std::cout << "\n" << name << '\n';
//     arr.view();
//     std::cout << "\nSize = " << arr.size()
//               << "  Capacity = " << arr.capacity() << '\n';
// }

// int main()
// {
//     ARRAY<int> arr1;
//     ARRAY<int> arr2;

//     for(int i=1;i<=16;i++)
//     {
//         arr1.insert(i);
//         arr2.insert(i);
//     }

//     std::cout << "\n========== INITIAL ==========\n";

//     printState(arr1,"Array 1");
//     printState(arr2,"Array 2");

//     std::cout << "\n========== ARRAY 1 : SEARCH ==========\n";

//     size_t index;

//     for(int i=0;i<1000000;i++)
//     {
//         arr1.search_linear(1,index);
//         arr1.search_linear(8,index);
//         arr1.search_linear(16,index);

//         arr1.search_binary(1,index);
//         arr1.search_binary(8,index);
//         arr1.search_binary(16,index);
//     }

//     std::cout << "\n========== ARRAY 2 : INSERT / REMOVE ==========\n";

//     for(int i=0;i<1000;i++)
//     {
//         arr2.remove();
//         arr2.insert(100);
//     }

//     std::cout << "\nAfter Operations\n";

//     printState(arr1,"Array 1");
//     printState(arr2,"Array 2");

//     std::cout << "\n========== INSERT ONE MORE ==========\n";

//     arr1.insert(17);
//     arr2.insert(17);

//     printState(arr1,"Array 1");
//     printState(arr2,"Array 2");

//     return 0;
// }


// #include <iostream>
// #include <iostream>

// template<typename D>
// void printState(ARRAY<D>& arr, const char* msg)
// {
//     std::cout << "\n" << msg << "\n";
//     std::cout << "Size     = " << arr.size() << '\n';
//     std::cout << "Capacity = " << arr.capacity() << '\n';
//     std::cout << "Data      ";
//     arr.view();
// }

// int main()
// {
//     ARRAY<int> arr;

//     printState(arr, "Initial");

//     std::cout << "\n========== INSERT ==========\n";

//     for(int i = 1; i <= 20; i++)
//     {
//         arr.insert(i);

//         std::cout << "Insert " << i
//                   << " -> Size = " << arr.size()
//                   << ", Capacity = " << arr.capacity()
//                   << '\n';
//     }

//     printState(arr, "After Insert");

//     std::cout << "\n========== REMOVE ==========\n";

//     while(arr.size())
//     {
//         arr.remove();

//         std::cout << "Remove -> Size = " << arr.size()
//                   << ", Capacity = " << arr.capacity()
//                   << '\n';
//     }

//     printState(arr, "After Remove");

//     return 0;
// }


// #include <iostream>
// template<typename D>
// void build(ARRAY<D>& arr)
// {
//     arr.insert(3);
//     arr.insert(7);
//     arr.insert(1);
//     arr.insert(8);
//     arr.insert(2);
//     arr.insert(6);
//     arr.insert(4);
//     arr.insert(5);
// }

// template<typename D>
// void testSort(const char* name, void (ARRAY<D>::*sort)(bool))
// {
//     std::cout << "\n\n========== " << name << " ==========\n";

//     ARRAY<D> asc;
//     build(asc);

//     std::cout << "Original:\n";
//     asc.view();

//     (asc.*sort)(true);

//     std::cout << "\nAscending:\n";
//     asc.view();

//     ARRAY<D> desc;
//     build(desc);

//     (desc.*sort)(false);

//     std::cout << "\nDescending:\n";
//     desc.view();
// }

// int main()
// {
//     // Basic Sorts
//     testSort<int>("Bubble Sort", &ARRAY<int>::sort_bubble);
//     testSort<int>("Selection Sort", &ARRAY<int>::sort_selection);
//     testSort<int>("Insertion Sort", &ARRAY<int>::sort_insertion);

//     // Efficient Comparison Sorts
//     testSort<int>("Merge Sort", &ARRAY<int>::sort_merge);
//     testSort<int>("Quick Sort", &ARRAY<int>::sort_quick);
//     testSort<int>("Heap Sort", &ARRAY<int>::sort_heap);
//     testSort<int>("Shell Sort", &ARRAY<int>::sort_shell);

//     // Specialized Sorts
//     testSort<int>("Odd-Even Sort", &ARRAY<int>::sort_oddeven);
//     testSort<int>("Cycle Sort", &ARRAY<int>::sort_cycle);
//     testSort<int>("Counting Sort", &ARRAY<int>::sort_counting);
//     testSort<int>("Radix Sort", &ARRAY<int>::sort_radix);
//     testSort<int>("Bucket Sort", &ARRAY<int>::sort_bucket);

//     // Hybrid / Modern Sorts
//     testSort<int>("Intro Sort", &ARRAY<int>::sort_intro);
//     testSort<int>("Tim Sort", &ARRAY<int>::sort_tim);
//     testSort<int>("Pattern-Defeating QuickSort", &ARRAY<int>::sort_pattern_defeating_quicksort);
//     testSort<int>("Dual-Pivot QuickSort", &ARRAY<int>::sort_dual_pivot_quicksort);
//     testSort<int>("External Merge Sort", &ARRAY<int>::sort_external_merge_sort);
//     testSort<int>("K-Way Merge Sort", &ARRAY<int>::sort_k_way_merge_sort);
//     testSort<int>("Bitonic Sort", &ARRAY<int>::sort_bitonic_sort);

//     std::cout << "\n\n";
//     return 0;
// }


// int main()
// {
//     ARRAY<int> A;
//     ARRAY<int> B;
//     ARRAY<int> C;

//     A.insert(1);
//     A.insert(2);
//     A.insert(3);

//     B.insert(1);
//     B.insert(2);
//     B.insert(3);

//     C.insert(1);
//     C.insert(2);
//     C.insert(4);

//     std::cout << "A : ";
//     A.view();

//     std::cout << "B : ";
//     B.view();

//     std::cout << "C : ";
//     C.view();



//     std::cout << "\n========== Comparison Operator Test ==========\n";

//     /*==================== ARRAY ====================*/

//     std::cout << "\n----- ARRAY -----\n";

//     std::cout << "\nA vs B\n";
//     std::cout << "== : " << (A == B) << '\n';
//     std::cout << "!= : " << (A != B) << '\n';
//     std::cout << "<  : " << (A <  B) << '\n';
//     std::cout << "<= : " << (A <= B) << '\n';
//     std::cout << ">  : " << (A >  B) << '\n';
//     std::cout << ">= : " << (A >= B) << '\n';

//     std::cout << "\nA vs C\n";
//     std::cout << "== : " << (A == C) << '\n';
//     std::cout << "!= : " << (A != C) << '\n';
//     std::cout << "<  : " << (A <  C) << '\n';
//     std::cout << "<= : " << (A <= C) << '\n';
//     std::cout << ">  : " << (A >  C) << '\n';
//     std::cout << ">= : " << (A >= C) << '\n';

//     std::cout << "\nC vs A\n";
//     std::cout << "== : " << (C == A) << '\n';
//     std::cout << "!= : " << (C != A) << '\n';
//     std::cout << "<  : " << (C <  A) << '\n';
//     std::cout << "<= : " << (C <= A) << '\n';
//     std::cout << ">  : " << (C >  A) << '\n';
//     std::cout << ">= : " << (C >= A) << '\n';



//     /*================ FORWARD ITERATOR ================*/

//     std::cout << "\n----- FORWARD ITERATOR -----\n";

//     auto i1 = A.begin();
//     auto i2 = A.begin();
//     auto i3 = A.begin();
//     ++i3;

//     std::cout << "\ni1 vs i2\n";
//     std::cout << "== : " << (i1 == i2) << '\n';
//     std::cout << "!= : " << (i1 != i2) << '\n';
//     std::cout << "<  : " << (i1 <  i2) << '\n';
//     std::cout << "<= : " << (i1 <= i2) << '\n';
//     std::cout << ">  : " << (i1 >  i2) << '\n';
//     std::cout << ">= : " << (i1 >= i2) << '\n';

//     std::cout << "\ni1 vs i3\n";
//     std::cout << "== : " << (i1 == i3) << '\n';
//     std::cout << "!= : " << (i1 != i3) << '\n';
//     std::cout << "<  : " << (i1 <  i3) << '\n';
//     std::cout << "<= : " << (i1 <= i3) << '\n';
//     std::cout << ">  : " << (i1 >  i3) << '\n';
//     std::cout << ">= : " << (i1 >= i3) << '\n';

//     std::cout << "\ni3 vs i1\n";
//     std::cout << "== : " << (i3 == i1) << '\n';
//     std::cout << "!= : " << (i3 != i1) << '\n';
//     std::cout << "<  : " << (i3 <  i1) << '\n';
//     std::cout << "<= : " << (i3 <= i1) << '\n';
//     std::cout << ">  : " << (i3 >  i1) << '\n';
//     std::cout << ">= : " << (i3 >= i1) << '\n';



//     /*================ REVERSE ITERATOR ================*/

//     std::cout << "\n----- REVERSE ITERATOR -----\n";

//     auto r1 = A.rbegin();
//     auto r2 = A.rbegin();
//     auto r3 = A.rbegin();
//     ++r3;

//     std::cout << "\nr1 vs r2\n";
//     std::cout << "== : " << (r1 == r2) << '\n';
//     std::cout << "!= : " << (r1 != r2) << '\n';
//     std::cout << "<  : " << (r1 <  r2) << '\n';
//     std::cout << "<= : " << (r1 <= r2) << '\n';
//     std::cout << ">  : " << (r1 >  r2) << '\n';
//     std::cout << ">= : " << (r1 >= r2) << '\n';

//     std::cout << "\nr1 vs r3\n";
//     std::cout << "== : " << (r1 == r3) << '\n';
//     std::cout << "!= : " << (r1 != r3) << '\n';
//     std::cout << "<  : " << (r1 <  r3) << '\n';
//     std::cout << "<= : " << (r1 <= r3) << '\n';
//     std::cout << ">  : " << (r1 >  r3) << '\n';
//     std::cout << ">= : " << (r1 >= r3) << '\n';

//     std::cout << "\nr3 vs r1\n";
//     std::cout << "== : " << (r3 == r1) << '\n';
//     std::cout << "!= : " << (r3 != r1) << '\n';
//     std::cout << "<  : " << (r3 <  r1) << '\n';
//     std::cout << "<= : " << (r3 <= r1) << '\n';
//     std::cout << ">  : " << (r3 >  r1) << '\n';
//     std::cout << ">= : " << (r3 >= r1) << '\n';

//     return 0;
// }


// #include <iostream>

// struct Point{
//     int x;
//     int y;

//     void print() const{
//         std::cout << "(" << x << "," << y << ")";
//     }
// };

// int main()
// {
//     std::cout << "========== ARRAY Comparison ==========\n\n";

//     ARRAY<int> A;
//     ARRAY<int> B;
//     ARRAY<int> C;

//     A.insert(1);
//     A.insert(2);
//     A.insert(3);

//     B.insert(1);
//     B.insert(2);
//     B.insert(3);

//     C.insert(1);
//     C.insert(2);
//     C.insert(4);

//     std::cout << "A : "; A.view();
//     std::cout << "B : "; B.view();
//     std::cout << "C : "; C.view();

//     std::cout << "\nA == B : " << (A == B) << '\n';
//     std::cout << "A != B : " << (A != B) << '\n';

//     std::cout << "A <  C : " << (A < C) << '\n';
//     std::cout << "A <= C : " << (A <= C) << '\n';
//     std::cout << "C >  A : " << (C > A) << '\n';
//     std::cout << "C >= A : " << (C >= A) << '\n';



//     std::cout << "\n\n========== Forward Iterator ==========\n\n";

//     for(auto it = A.begin(); it != A.end(); ++it)
//         std::cout << *it << ' ';

//     std::cout << "\n";



//     std::cout << "\nPrefix ++\n";

//     auto it = A.begin();

//     std::cout << *it << '\n';

//     ++it;
//     std::cout << *it << '\n';

//     ++it;
//     std::cout << *it << '\n';



//     std::cout << "\nPostfix ++\n";

//     it = A.begin();

//     std::cout << *(it++) << '\n';
//     std::cout << *it << '\n';



//     std::cout << "\nPrefix --\n";

//     it = A.end();
//     --it;

//     std::cout << *it << '\n';

//     --it;
//     std::cout << *it << '\n';



//     std::cout << "\nPostfix --\n";

//     it = A.end();
//     --it;

//     std::cout << *(it--) << '\n';
//     std::cout << *it << '\n';



//     std::cout << "\nIterator Comparisons\n";

//     auto a = A.begin();
//     auto b = A.begin();

//     ++b;

//     std::cout << "a==b : " << (a==b) << '\n';
//     std::cout << "a!=b : " << (a!=b) << '\n';
//     std::cout << "a<b  : " << (a<b) << '\n';
//     std::cout << "a<=b : " << (a<=b) << '\n';
//     std::cout << "a>b  : " << (a>b) << '\n';
//     std::cout << "a>=b : " << (a>=b) << '\n';



//     std::cout << "\n\n========== Reverse Iterator ==========\n\n";

//     for(auto rit = A.rbegin(); rit != A.rend(); ++rit)
//         std::cout << *rit << ' ';

//     std::cout << "\n";



//     std::cout << "\nReverse Prefix ++\n";

//     auto rit = A.rbegin();

//     std::cout << *rit << '\n';

//     ++rit;
//     std::cout << *rit << '\n';

//     ++rit;
//     std::cout << *rit << '\n';



//     std::cout << "\nReverse Postfix ++\n";

//     rit = A.rbegin();

//     std::cout << *(rit++) << '\n';
//     std::cout << *rit << '\n';



//     std::cout << "\nReverse Prefix --\n";

//     rit = A.rend();
//     --rit;

//     std::cout << *rit << '\n';

//     --rit;
//     std::cout << *rit << '\n';



//     std::cout << "\nReverse Postfix --\n";

//     rit = A.rend();
//     --rit;

//     std::cout << *(rit--) << '\n';
//     std::cout << *rit << '\n';



//     std::cout << "\nReverse Iterator Comparisons\n";

//     auto r1 = A.rbegin();
//     auto r2 = A.rbegin();

//     ++r2;

//     std::cout << "r1==r2 : " << (r1==r2) << '\n';
//     std::cout << "r1!=r2 : " << (r1!=r2) << '\n';
//     std::cout << "r1<r2  : " << (r1<r2) << '\n';
//     std::cout << "r1<=r2 : " << (r1<=r2) << '\n';
//     std::cout << "r1>r2  : " << (r1>r2) << '\n';
//     std::cout << "r1>=r2 : " << (r1>=r2) << '\n';



//     std::cout << "\n\n========== operator-> Test ==========\n\n";

//     ARRAY<Point> P;

//     P.insert({10,20});
//     P.insert({30,40});
//     P.insert({50,60});

//     std::cout << "Forward\n";

//     for(auto i = P.begin(); i != P.end(); ++i)
//     {
//         i->print();
//         std::cout << ' ';
//     }

//     std::cout << "\nReverse\n";

//     for(auto i = P.rbegin(); i != P.rend(); ++i)
//     {
//         i->print();
//         std::cout << ' ';
//     }

//     std::cout << '\n';

//     return 0;
// }


// using std::cout;
// using std::endl;
// int main() {

//     cout << "\n========== BUILD ==========\n";
//     ARRAY<int> a;

//     for (int i = 1; i <= 5; ++i)
//         a.insert(i);

//     a.view();

//     cout << "\n========== [] TEST ==========\n";
//     cout << "a[0]  = " << a[0]  << endl;
//     cout << "a[2]  = " << a[2]  << endl;
//     cout << "a[-1] = " << a[-1] << endl;
//     cout << "a[-2] = " << a[-2] << endl;

//     a[0] = 100;
//     a[-1] = 500;

//     a.view();

//     cout << "\n========== COPY CONSTRUCTOR ==========\n";
//     ARRAY<int> b(a);

//     b.view();

//     b[0] = 999;

//     cout << "Original :" << endl;
//     a.view();

//     cout << "Copy :" << endl;
//     b.view();

//     cout << "\n========== COPY ASSIGNMENT ==========\n";
//     ARRAY<int> c;

//     c = a;

//     c.view();

//     c[-1] = 888;

//     cout << "Original :" << endl;
//     a.view();

//     cout << "Assigned :" << endl;
//     c.view();

//     cout << "\n========== MOVE CONSTRUCTOR ==========\n";
//     ARRAY<int> d(std::move(c));

//     cout << "Moved-To :" << endl;
//     d.view();

//     cout << "Moved-From :" << endl;
//     c.view();

//     cout << "\n========== MOVE ASSIGNMENT ==========\n";
//     ARRAY<int> e;

//     e = std::move(d);

//     cout << "Moved-To :" << endl;
//     e.view();

//     cout << "Moved-From :" << endl;
//     d.view();

//     cout << "\n========== CHAIN ASSIGNMENT ==========\n";
//     ARRAY<int> x, y, z;

//     x.insert(1);
//     y.insert(2);
//     z.insert(3);
//     z.insert(4);
//     z.insert(5);

//     x = y = z;

//     cout << "x : ";
//     x.view();

//     cout << "y : ";
//     y.view();

//     cout << "z : ";
//     z.view();

//     cout << "\n========== OUT OF BOUNDS ==========\n";

//     try {
//         cout << a[100] << endl;
//     }
//     catch (const std::exception& e) {
//         cout << e.what() << endl;
//     }

//     try {
//         cout << a[-100] << endl;
//     }
//     catch (const std::exception& e) {
//         cout << e.what() << endl;
//     }

//     return 0;
// }


// int main() {
//     ARRAY<int> arr;

//     //====================================================
//     std::cout << "========== INITIAL ==========\n";
//     arr.view();
//     std::cout << "\nSize: " << arr.size()
//               << "\nCapacity: " << arr.capacity() << "\n\n";

//     //====================================================
//     std::cout << "========== BUILD ==========\n";
//     for(int i=1;i<=8;i++)
//         arr.insert(i);

//     arr.view();
//     std::cout << "\nSize: " << arr.size()
//               << "\nCapacity: " << arr.capacity() << "\n\n";

//     //====================================================
//     std::cout << "========== GROW BACK +3 ==========\n";
//     arr.length(3);
//     arr.view();
//     std::cout << "\nSize: " << arr.size()
//               << "\nCapacity: " << arr.capacity() << "\n\n";

//     //====================================================
//     std::cout << "========== SHRINK BACK -2 ==========\n";
//     arr.length(-2);
//     arr.view();
//     std::cout << "\nSize: " << arr.size()
//               << "\nCapacity: " << arr.capacity() << "\n\n";

//     //====================================================
//     std::cout << "========== GROW FRONT +4 ==========\n";
//     arr.length(4,false);
//     arr.view();
//     std::cout << "\nSize: " << arr.size()
//               << "\nCapacity: " << arr.capacity() << "\n\n";

//     //====================================================
//     std::cout << "========== SHRINK FRONT -3 ==========\n";
//     arr.length(-3,false);
//     arr.view();
//     std::cout << "\nSize: " << arr.size()
//               << "\nCapacity: " << arr.capacity() << "\n\n";

//     //====================================================
//     std::cout << "========== ROUND CAPACITY ==========\n";
//     arr.length(0);
//     arr.view();
//     std::cout << "\nSize: " << arr.size()
//               << "\nCapacity: " << arr.capacity() << "\n\n";

//     //====================================================
//     std::cout << "========== INSERT AFTER REBUILD ==========\n";

//     arr.insert(100);
//     arr.insert(200,0);
//     arr.insert(300,4);
//     arr.insert(400,-1);
//     arr.insert(500,-2);

//     arr.view();

//     std::cout << "\nSize: " << arr.size()
//               << "\nCapacity: " << arr.capacity() << "\n\n";

//     //====================================================
//     std::cout << "========== REMOVE TEST ==========\n";

//     std::cout << "remove(last) = " << arr.remove() << '\n';
//     std::cout << "remove(front)= " << arr.remove(0) << '\n';
//     std::cout << "remove(mid)  = " << arr.remove(3) << '\n';

//     arr.view();

//     std::cout << "\nSize: " << arr.size()
//               << "\nCapacity: " << arr.capacity() << "\n\n";

//     //====================================================
//     std::cout << "========== DROP TEST ==========\n";

//     arr.insert(5);
//     arr.insert(5);
//     arr.insert(5);

//     arr.view();
//     std::cout << "\nDrop duplicate 5\n";

//     arr.drop(5,true);

//     arr.view();

//     std::cout << "\nSize: " << arr.size()
//               << "\nCapacity: " << arr.capacity() << "\n\n";

//     //====================================================
//     std::cout << "========== HEAVY INSERT ==========\n";

//     for(int i=0;i<100;i++)
//         arr.insert(i+1000);

//     std::cout << "Size: " << arr.size()
//               << "\nCapacity: " << arr.capacity() << "\n\n";

//     //====================================================
//     std::cout << "========== HEAVY SHRINK ==========\n";

//     arr.length(-90);

//     arr.view();

//     std::cout << "\nSize: " << arr.size()
//               << "\nCapacity: " << arr.capacity() << "\n\n";

//     //====================================================
//     std::cout << "========== INSERT AFTER SHRINK ==========\n";

//     arr.insert(9999);
//     arr.insert(8888,0);
//     arr.insert(7777,-2);

//     arr.view();

//     std::cout << "\nSize: " << arr.size()
//               << "\nCapacity: " << arr.capacity() << "\n\n";

//     //====================================================
//     std::cout << "========== CLEAR ==========\n";

//     arr.length(-100000);

//     arr.view();

//     std::cout << "\nSize: " << arr.size()
//               << "\nCapacity: " << arr.capacity() << "\n\n";

//     //====================================================
//     std::cout << "========== REBUILD AFTER CLEAR ==========\n";

//     for(int i=10;i<=100;i+=10)
//         arr.insert(i);

//     arr.view();

//     std::cout << "\nSize: " << arr.size()
//               << "\nCapacity: " << arr.capacity() << "\n\n";

//     //====================================================
//     std::cout << "========== FINAL REVERSE VIEW ==========\n";

//     arr.view(false);

//     std::cout << "\n\nFinal Size     : " << arr.size()
//               << "\nFinal Capacity : " << arr.capacity()
//               << "\n\n========== TEST COMPLETE ==========\n";
// }


// int main() {
//     ARRAY<int> arr;

//     std::cout << "===== BUILD ARRAY =====\n";
//     for (int i = 1; i <= 8; i++)
//         arr.insert(i);

//     arr.view();
//     std::cout << "\nSize: " << arr.size()
//               << "\nCapacity: " << arr.capacity() << "\n\n";

//     // ---------------------------------------
//     std::cout << "===== GROW BACK (+3) =====\n";
//     arr.length(3);
//     arr.view();
//     std::cout << "\nSize: " << arr.size()
//               << "\nCapacity: " << arr.capacity() << "\n\n";

//     // ---------------------------------------
//     std::cout << "===== SHRINK BACK (-2) =====\n";
//     arr.length(-2);
//     arr.view();
//     std::cout << "\nSize: " << arr.size()
//               << "\nCapacity: " << arr.capacity() << "\n\n";

//     // ---------------------------------------
//     std::cout << "===== GROW FRONT (+4) =====\n";
//     arr.length(4, false);
//     arr.view();
//     std::cout << "\nSize: " << arr.size()
//               << "\nCapacity: " << arr.capacity() << "\n\n";

//     // ---------------------------------------
//     std::cout << "===== SHRINK FRONT (-3) =====\n";
//     arr.length(-3, false);
//     arr.view();
//     std::cout << "\nSize: " << arr.size()
//               << "\nCapacity: " << arr.capacity() << "\n\n";

//     // ---------------------------------------
//     std::cout << "===== ROUND CAPACITY =====\n";
//     arr.length(0);
//     arr.view();
//     std::cout << "\nSize: " << arr.size()
//               << "\nCapacity: " << arr.capacity() << "\n\n";

//     // ---------------------------------------
//     std::cout << "===== CLEAR ARRAY =====\n";
//     arr.length(-100);
//     arr.view();
//     std::cout << "\nSize: " << arr.size()
//               << "\nCapacity: " << arr.capacity() << "\n\n";

//     std::cout << "===== TEST COMPLETE =====\n";
// }


// int main()
// {
//     ARRAY<int> arr;

//     std::cout << "Initial\n";
//     arr.view();
//     std::cout << "\nSize: " << arr.size()
//               << "\nCapacity: " << arr.capacity() << "\n\n";

//     // Append
//     arr.insert(2);
//     arr.insert(4);
//     arr.insert(6);
//     arr.insert(8);
//     arr.insert(10);
//     arr.insert(12);

//     std::cout << "After append:\n";
//     arr.view(); 
//     std::cout << "\nSize: " << arr.size()
//               << "\nCapacity: " << arr.capacity() << "\n\n";

//     // Front
//     arr.insert(1, 0);

//     std::cout << "Insert at front:\n";
//     arr.view();
//     std::cout << "\n\n";

//     // Middle
//     arr.insert(5, 3);

//     std::cout << "Insert in middle:\n";
//     arr.view();
//     std::cout << "\n\n";

//     // End
//     arr.insert(99, arr.size());

//     std::cout << "Insert at end:\n";
//     arr.view();
//     std::cout << "\n\n";

//     // Negative index
//     arr.insert(88, -2);

//     std::cout << "Insert at -2:\n";
//     arr.view();
//     std::cout << "\n\n";

//     // Reverse
//     std::cout << "Reverse:\n";
//     arr.view(false);
//     std::cout << "\n";

//     std::cout << "\nFinal Size: " << arr.size();
//     std::cout << "\nFinal Capacity: " << arr.capacity() << '\n';
// }
