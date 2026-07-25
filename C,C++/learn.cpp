// C++26 Reflection example

// #include <meta>
// #include <iostream>
// #include <string>

// enum class Color { Red, Green, Blue };

// template <typename E>
// constexpr std::string enum_to_string(E value) {
//     template for (constexpr auto e : std::meta::enumerators_of(^^E)) {
//         if (value == [:e:])
//             return std::string(std::meta::identifier_of(e));
//     }
//     return "<unknown>";
// }

// int main() {
//     Color c = Color::Green;

//     std::cout << enum_to_string(c) << '\n';
// }


// Reflection Example Count enum values automatically:

// #include <meta>

// enum class Day { Mon, Tue, Wed, Thu, Fri };

// constexpr int count_days() {
//     int count = 0;
//     template for (constexpr auto e : std::meta::enumerators_of(^^Day)) {
//         ++count;
//     }
//     return count;
// }
// static_assert(count_days() == 5);

// #include <iostream>
// using namespace std;
// int main() {
//     size_t n=2;
//     long int y=6;
//     // n=static_cast<size_t>(-y);
//     n=n-y;
//     cout<<n;
//     // int arr[2]={10,20};
//     // int arr2[2]={1,2};
//     // arr2[n++]=arr[n];
//     // std::cout << arr2[0] <<"\t"<< arr2[1] << std::endl;
//     // std::cout << arr[0] <<"\t"<< arr[1];
// }




template<typename D>
class LIST;

template<typename D>
class LISTreverse_iterator {
    // friend class LIST<D>;

    D* Stack;      // Beginning of the array
    D* ptr;        // Current element
    D* end;
public:
    LISTreverse_iterator(D* stack, D* position);
    LISTreverse_iterator(LISTnode<D>* p = nullptr, size_t size = 0);
    LISTreverse_iterator(const LISTreverse_iterator&) = delete;
    LISTreverse_iterator& operator=(const LISTreverse_iterator&) = delete;

    LISTreverse_iterator(LISTreverse_iterator&& other) noexcept;
    LISTreverse_iterator& operator=(LISTreverse_iterator&& other) noexcept;

    ~LISTreverse_iterator();

    D& operator*();
    const D& operator*() const;

    LISTreverse_iterator& operator--() noexcept;
    LISTreverse_iterator operator--(int) noexcept;

    bool operator!=(const LISTreverse_iterator& other) const noexcept;
    bool operator==(const LISTreverse_iterator& other) const noexcept;

    D* operator->();
    const D* operator->() const;
};

template<typename D>
LISTreverse_iterator<D>::LISTreverse_iterator(D* stack, D* position)
        :Stack(stack), ptr(position), end(stack - 1) {}

template<typename D>
LISTreverse_iterator<D>::LISTreverse_iterator(LISTnode<D>* p, size_t size)
    :Stack(nullptr), ptr(nullptr), end(nullptr)
{
    if (!p || size == 0)
        return;        // rend()

    Stack = new D[size];

    for(size_t i = size; i > 0; --i){
        Stack[i - 1] = p->K;
        p = p->P;
    }

    ptr = Stack + (size - 1);   // last element
    end = Stack - 1;            // before first element
}

template<typename D>
LISTreverse_iterator<D>::~LISTreverse_iterator() { delete[] Stack; }

template<typename D>
LISTreverse_iterator<D>::LISTreverse_iterator(LISTreverse_iterator&& other) noexcept
    : Stack(other.Stack), ptr(other.ptr), end(other.end)
{
    other.Stack = other.ptr = other.end = nullptr;
}

template<typename D>
LISTreverse_iterator<D>& LISTreverse_iterator<D>::operator=(LISTreverse_iterator&& other) noexcept
{
    if (this != &other) {
        delete[] Stack;

        Stack = other.Stack;  ptr = other.ptr;  end = other.end;

        other.Stack = other.ptr = nullptr;  other.end = nullptr;
    }
    return *this;
}

template<typename D>
D& LISTreverse_iterator<D>::operator*(){
    if (!ptr)
        throw std::runtime_error("Null LISTreverse_iterator");
    return *ptr;
}

template<typename D>
const D& LISTreverse_iterator<D>::operator*() const{
    if (!ptr)
        throw std::runtime_error("Null LISTreverse_iterator");
    return *ptr;
}

template<typename D>
LISTreverse_iterator<D>& LISTreverse_iterator<D>::operator--() noexcept{
    if(ptr != end) --ptr;

    return *this;
}

template<typename D>
LISTreverse_iterator<D> LISTreverse_iterator<D>::operator--(int) noexcept{
    LISTreverse_iterator temp(std::move(*this));
    --ptr;
    return temp;
}

template<typename D>
bool LISTreverse_iterator<D>::operator!=(const LISTreverse_iterator<D>& other) const noexcept{ return ptr != other.ptr; }

template<typename D>
bool LISTreverse_iterator<D>::operator==(const LISTreverse_iterator<D>& other) const noexcept{ return ptr == other.ptr; }

template<typename D>
D* LISTreverse_iterator<D>::operator->(){
    if (!ptr)
        throw std::runtime_error("Null LISTreverse_iterator");
    return ptr;
}

template<typename D>
const D* LISTreverse_iterator<D>::operator->() const{
    if (!ptr)
        throw std::runtime_error("Null LISTreverse_iterator");
    return ptr;
}



LISTreverse_iterator<D> rbegin() noexcept;
LISTreverse_iterator<D> rend() noexcept;
LISTreverse_iterator<D> rbegin() const noexcept;
LISTreverse_iterator<D> rend() const noexcept;

template<typename D>
LISTreverse_iterator<D> LIST<D>::rbegin() noexcept{ return LISTreverse_iterator<D>(H, elem); }

template<typename D>
LISTreverse_iterator<D> LIST<D>::rbegin() const noexcept{ return LISTreverse_iterator<D>(H, elem); }

template<typename D>
LISTreverse_iterator<D> LIST<D>::rend() noexcept
{
    return LISTreverse_iterator<D>(nullptr, 0);
}

template<typename D>
LISTreverse_iterator<D> LIST<D>::rend() const noexcept
{
    return LISTreverse_iterator<D>(nullptr, 0);
}

// template<typename D>
// LISTreverse_iterator<D> LIST<D>::rend() noexcept{
//     auto temp = rbegin();

//     LISTreverse_iterator<D> result(temp.Stack, temp.end);

//     temp.Stack = nullptr;
//     temp.ptr = nullptr;

//     return result;
// }

// template<typename D>
// LISTreverse_iterator<D> LIST<D>::rend() const noexcept{
//     auto temp = rbegin();

//     LISTreverse_iterator<D> result(temp.Stack, temp.end);

//     temp.Stack = nullptr;
//     temp.ptr = nullptr;

//     return result;
// }
