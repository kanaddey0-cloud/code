// Class
// #include <iostream>
// #include<string>
// using namespace std;
// class node{int a;};
// class abc{
//     node n;
//     int a;float b;
//     public:
//     static int count;
//     abc(){cout<<"Default Constructor";}
//     abc(int x, float y){
//         a=x; b=y;
//         cout<<a<<" "<<b<<" Constructor"<<endl;
//     }
//     abc(abc &tmp){
//         a=tmp.a; b=tmp.b;
//     }
//     void get(int x, float y){
//         a=x; b=y;
//         sh("ob3");
//     }
//     void sh(string s){
//         cout<<endl<<endl<<s<<" "<<a<<" "<<b;
//     }
//     ~abc(){cout<<count<<" Destractor\n";count++;}
// };int abc::count;
// class student{
//     int roll;
//     string name;
//     char grade;
//     public: student(){}
//     student(int a, string b, char c){
//         roll = a ; name = b ; grade = c;
//     }
//     void insert(int a, string b, char c){
//         roll = a ; name = b ; grade = c;
//     }
//     void print(){
//         cout<<roll<<" "<<name<<" "<<grade<<endl;
//     }
// };
// int main() {
//    abc::count=0;
//     abc obj(2,2.5),ob2(5,5.6),ob3;
//     ob3.get(10,2.56);
//     abc ob4(obj);
//    obj.sh("obj");
//    ob2.sh("ob2");
//    ob3.sh("ob3");
//    ob4.sh("ob4");
//    cout<<"\n\n";
//    student stu[2];
//     stu[0].insert(1,"Shubhajit Das",'C');
//     stu[1]=student(3,"Aritra Das",'A');
//     stu[0].print();
//     stu[1].print();
//     cout<<endl;
//     student std[4]={student(3,"Aritra Das",'A'),student(3,"Aritra Das",'A'),
//         student(3,"Aritra Das",'A'),student(3,"Aritra Das",'A')};
//     for(student i: std){ i.print(); } cout<<endl;
//     return 0;
// }


// Function Overloading
// #include <iostream>
// using namespace std;
// class B{
// public:
//     void funb(){cout<<"Base Class";}
//     void funOLoad(float);
//     void funOLoad2(float);
// };
// void B::funOLoad(float f){cout<<"\nbase funOLoad call"<<f;}
// void B::funOLoad2(float){cout<<"\nbase funOLoad2 call";}
// class D : public B{
// public:
//     void fund(){cout<<"\nDerived Class ";  funb();}
//     void funOLoad(int);
//     void funOLoad2(int);
//     using B::funOLoad2;
// };
// void D::funOLoad(int n){cout<<"\nderived funOLoad call = "<<n;}
// void D::funOLoad2(int){cout<<"\nderived funOLoad2 call";}
// int main(){
//     D d;
//     d.fund();  cout<<endl; 
//     d.funb();  cout<<endl;
//     d.funOLoad(4);
//     d.funOLoad(1.2f);  cout<<endl;
//     d.funOLoad2(10);
//     d.funOLoad2(1.4f);
// return 0;
// }


// Friend Function
// #include<iostream>
// using namespace std;
// class B;
// class proto{ public: void have(B); };
// class type{ public: void have(B); void haveNOT(){/*Do Not Access Class B Data Item val*/} };
// class A{
//     int val;
// public:
//     proto p;
//     type t;
//     A(int n){ val=n; }
//     void access(B);
//     friend class B;
//     friend void friendFUNCTION(A,B);
// };
// class B{
//     int val;
// public:
//     B(int n){ val=n; }
//     void access(A a){ cout<<endl<<a.val; }
//     friend void A::access(B);
//     friend class proto;
//     friend void type::have(B);
//     friend void friendFUNCTION(A,B);
// };
// void proto::have(B b){ cout<<endl<<b.val; }
// void type::have(B b){ cout<<endl<<b.val; }
// void A::access(B b){ cout<<endl<<b.val; }
// void friendFUNCTION(A a,B b){ cout<<endl<<a.val<<" "<<b.val; }
// int main(){
//     B b(99); A a(100);
//     friendFUNCTION(a,b);
//     b.access(a);
//     a.access(b);
//     a.p.have(b);
//     a.t.have(b);
//     return 0;
// }


// Static Keyword
// #include<iostream>
// using namespace std;
// class exam{
//     int val;
// public:
//     static int a,b;
//     exam(int val){ this->val=val; a++; b--;}
//     void have(){ cout<<endl<<val<<"  ";  }
//     static void access(){ cout<<endl<<a<<" "<<b; }
// }; int exam::a=0, exam::b; //ZERO by defualt assign or not
// int main(){
//     exam x(0);
//     exam::access();
//     x.have();
// cout<<"\n";
//     exam x1(10);
//     exam::access();
//     x1.have();
// cout<<"\n";
//     exam x2(20);
//     exam::access();
//     x2.have();
// cout<<"\n";
//     exam x3(30);
//     exam::access();
//     x3.have();
// cout<<"\n";
//     exam x4(40);
//     exam::access();
//     x4.have();
// cout<<endl<<exam::a<<" "<<exam::b;
//     return 0;
// }


// Namespace
// #include <iostream>
// namespace MyNamespace {
//     int num = 10;
//     void display() {
//         std::cout << "Num:1 " << num << std::endl;
//     }
//     namespace sagar{
//         void display() {
//             std::cout << "Num:2 " << num << std::endl;
//         }
//     }
// }
// namespace{ //An anonymous namespace (namespace {}) in C++ makes its members accessible only within the current translation unit (source file).
//     int number = 30;
//     void output() {
//         std::cout <<std::endl<< "main " << number;
//     }
// }
// int main() {
//     output();
//     std::cout<<std::endl<<number;
//     // Accessing namespace members using the scope resolution operator (::)
//     using namespace MyNamespace::sagar;
//     std::cout << std::endl<<MyNamespace::num << std::endl;
//     display();
//     display();
//     using namespace MyNamespace;
//     MyNamespace::display();
//     return 0;
// }


// Problem
// #include<stdio.h>
// // int fun(int n=0){
// //     static int a=16;
// //     printf(" \n%d-%d",a,n);
// //     return a--;
// // }
// int fun(int n){
//     int x=1, k;
//     if(n==1) return x;
//     for(k=1; k<n; ++k){
//         x= x+ fun(k)*fun(n-k);
//     }
//     return x;
// }
// int main(){
// printf("%d",fun(5));
//     // for(fun(11);fun(22);fun(99)) {printf(" %d\n",fun(33));}
//     // int a;
//     // a=12;
//     // printf("%d",sizeof(a++));
//     // printf("%d",a);
//     // int _=10;
//     // printf("%d",_);
//     // unsigned int var=20;
//     // printf("%d",~var);

//     return 0;
// }


// Pointer & Array
// #include<iostream>
// using namespace std;
// int sum();
// int main(){
//     int arr[2][3][4]={0,1,2,3,  4,5,6,7,  8,9,10,11, 
//                  12,13,14,15,  16,17,18,19,  20,21,22,23};              
//     int arr2[12]={0,1,2,3,4,5,6,7,8,9,10,11};    
//     int (*p0)[2][3][4]=&arr;
//     int (*p)[3][4]=arr;
//     int *p2[2][2][3];
//     int *p3 = arr2;
//     cout<<endl<<*((*((*p)+1))+3);
//     // for(auto i: arr)cout<<endl<<i;
//     return 0;
// }


// Function Pointer
// #include<iostream>
// #include<functional>
// using namespace std;
// int fun(float f, char c){
//     return (int)c;
// }
// void f(int (*fp)(float,char)){
//     cout<<endl<<fp(2.5f,'b');
// } 
// void f2(function<int(float,char)> fp2){  //<functional>
//     cout<<endl<<fp2(2.5f,'d');
// }
// int main(){
// function<int(float,char)> fp2=fun;  //<functional>
// int (*fp)(float,char) = fun;
// cout<<fp(2.5f,'a');
// f(fun);
// cout<<endl<<fp2(2.5f,'c');
// f2(fun);
//     return 0;
// }


// Template
// #include<iostream>
// using namespace std;
// template<class S,class K>
// void sum(S a, S b, K c){
//     S d=97;
//     cout<<"\na="<<a<<" b="<<b<<" c="<<c<<" d="<<d;
// }
// template<class S,class K=int>
// class TMP{
//     K kk; S ss; 
// public:
//     TMP(S ss, K kk){ this->ss=ss; this->kk=kk; }
//     void p(){ cout<<endl<<"ss="<<ss<<" kk="<<kk; }
// };
// template<class S, class K>
// K fun(S x, K y){ return x; }
// int main(){
//     sum(10,20,2.5);
//     sum(2.4,2.5,5.1);
//     sum('a','b',20);
// cout<<"\n";
//     TMP<int,float> obj(10,2.5),obj2(20,4.9);
//     obj.p(); obj2.p();
//     TMP<float, char> obj3(23,'b');
//     obj3.p();
//     cout<<"\n"<<fun('a',2);
//     TMP<float> obj4(2.5,24);
//     obj4.p();
//     return 0;
// }


// Operator Overloading
#include<iostream>
using namespace std;
class complex{
    // int n;
public:
    int n;
    complex()=default;
    complex(int num){ n=num; }
    complex operator +(complex x){ // binary
            cout<<endl<<"+ Operator Overload";
        complex tmp;
        tmp.n = n+x.n;
        return tmp;
    }
    complex* operator - (complex y){ // binary
        n -= y.n;
        return this;
    }
    void operator *(){ cout<<endl<<"Value = "<<n; } // unary
    complex operator *(complex x){ // binary
        complex tmp;
        tmp.n = n*x.n;
        return tmp;
    }
    complex operator ++(){ //unary
        complex tmp;
        tmp.n=++n;  // Pre-Increment
        return tmp; 
    } 
    complex operator ++(int){ //unary
        complex tmp;
        tmp.n=n++;  // Post-Increment
        return tmp; 
    }
// operator>> and operator<< usually involve two operands: a stream object (istream or ostream) and an instance of the class (complex in this case). The stream object comes first (e.g., cin >> obj; or cout << obj;), which means the operators can't naturally be member functions of the complex class—because a member function always assumes the class object is the left-hand operand.
// If the member variable n in your complex class is declared as public, then friend functions like operator>> and operator<< would no longer need the friend keyword to access it. Public members are accessible to any function, whether it's a member function, a friend function, or just a regular function.
    friend istream& operator >>(istream &sin, complex &x){
        sin>>x.n; // We cannot use const complex &x because we need to modify x (store input values inside it).
        return sin; // complex &x input perameter (&) to avoid necessary copy 
    } // Return ostream & Allows multiple outputs in one statement
    friend ostream& operator <<(ostream &sout, const complex &x) {
        sout << x.n; // work on const value also, without const also fine
        return sout; // const complex &x input perameter (&) to avoid necessary copy 
    } // Return ostream & Allows multiple outputs in one statement
};
int main(){
    complex c0(1), c1(2), c2(4);
   
    // c0 = c1+c2; *c0;
    // c0=c1*c2; *c0;
    c0=*(c2-c1); *c0; *c1; *c2;

    // c2=++c0; *c2; *c0;
    // c1=c0++; *c1; *c0;

    // cout<<endl;
    // cin>>c0;
    // cout<<c0;

    return 0;
}

// #include <iostream>
// using namespace std;
// class MyClass {
//     int value;
// public:
//     MyClass(int v = 0) : value(v) {}
//     MyClass operator+(int x) const {   // Member function: Object + int
//         return MyClass(value + x);
//     }
//     friend MyClass operator+(int x, const MyClass& obj) {    // Friend function: int + Object
//         return MyClass(x + obj.value);
//     }
//     void display() const {
//         cout << "Value: " << value << endl;
//     }
// };
// int main() {
//     MyClass Object(5);
//     Object = 10 + Object;      // ✅ friend function handles this
//     Object.display();      // Output: Value: 15
//     Object = Object + 10;      // ✅ member function handles this
//     Object.display();      // Output: Value: 25
//     return 0;
// }



// Data Conversion Function
// #include<iostream>
// using namespace std;
// class TWO;
// class ONE{
// public:
//     int a; float b;
//     ONE(){ a=12; b=2.4f; }
//     operator int(){ return a; }
//     operator float(){ return b; }
//     ONE operator =(TWO); // Operator should be Member of a CLASS not a Friend Function
//     operator TWO(); 
// };
// class TWO{
// public:
//     int a; float b;
//     TWO(){ a=17; b=9.4f; }
// };
// ONE ONE::operator=(TWO tmp2){
//     ONE tmp1;
//     tmp1.a=tmp2.a; tmp1.b=tmp2.b;
//     return tmp1;
// }
// ONE::operator TWO(){
//     TWO tmp; 
//     tmp.a=a; tmp.b=b;
//     return tmp;
// }
// int main(){
//     int i; float f; ONE _1; TWO _2;
//     i=_1; f=_1;  cout<<endl<<i<<" "<<f;
//     _1=_2;  cout<<endl<<_1.a<<" "<<_1.b;
//     _2=_1;  cout<<endl<<_2.a<<" "<<_2.b;
// return 0;
// }


// Problem 2
// #include <iostream> 
// using namespace std;  
// int main() { 
// try { 
//     try { 
//         throw 20; 
//     } 
//     catch (int n) { 
//         cout << "Inner Catch\n"; 
//         throw; 
//     } 
// } 
// catch (int x) { 
//     cout << "Outer Catch "<<x<<endl; 
// } 
//     return 0; 
// } 


// Move Symentrix
// 1. Move Constructor 
// 2. Move Assignment 
// #include <iostream>
// #include <utility>  // for std::move
// class MyClass {
// private:
//     int* data;
// public:
//     // Constructor
//     MyClass(int value) : data(new int(value)) {
//         std::cout << "Constructor called!\n";
//     }
//     // Move Constructor
//     MyClass(MyClass&& other) noexcept : data(nullptr) {
//         std::cout << "Move Constructor called!\n";
//         data = other.data;
//         other.data = nullptr;
//     }
//     // Move Assignment Operator Or Assignment Constructor
//     MyClass& operator=(MyClass&& other) noexcept {
//         std::cout << "Move Assignment Operator called!\n";
//         if (this != &other) {
//             delete data;
//             data = other.data;
//             other.data = nullptr;
//         } // Returning MyClass& (a reference to the current instance) in the assignment operator allows for assignment chaining.
//         return *this;
//     } // MyClass a, b, c;  a = b = c; Equivalent to (a = (b = c));
//     ~MyClass() { delete data; }
// };
// int main() {
//     MyClass obj1(42);        // Constructor called
//     MyClass obj2 = std::move(obj1);  // Move Constructor called
//     MyClass obj3(100);       // Constructor called
//     obj3 = std::move(obj2);  // Move Assignment Operator called
// return 0;
// }
