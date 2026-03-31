# ifndef LINKED_LIST
# define LINKED_LIST

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
    void clearupto(node<D>*& p);
public:
    LIST();
    LIST(const LIST<D>& other);
    LIST(LIST<D>&& other) noexcept;
    D& operator[](long int index);
    const D& operator[](long int index) const;
    LIST<D>& operator=(const LIST<D>& other);
    LIST<D>& operator=(LIST<D>&& other) noexcept;
    long int size() const { return elem; }
    int insert(D val, long int index=-1);
    int drop(D val);
    D remove(long int index);
    long int update(D prev, D curr, bool in=0);
    D modify(D curr, long int index);
    D value(long int index) const;
    long int index(D value) const;
    void reverse();
    void view() const;
    iterator<D> begin();
    iterator<D> begin() const;
    iterator<D> end();
    iterator<D> end() const;
    ~LIST();
};

# include "LinkedList.tpp"