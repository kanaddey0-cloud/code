#include<iostream>
#include<string>
using namespace std;
class b{int n;
public:
void use (int aa){n=aa;cout<<n;}
void p(float f){cout<<endl<<"Kanad";}
};
class x:public b{
    int a;
    public:
    x(int a){this->a=a;}
    void p(x);
    using b::p;
};
void x::p(x tmp){cout<<endl<<"Kanad--"<<endl;}

int main(){
//     int a;
x ob1(10),ob2(20);
ob2.p(ob1);
ob1.p(ob2);
ob1.use(100);
ob1.p(2.5);
    return 0;
}