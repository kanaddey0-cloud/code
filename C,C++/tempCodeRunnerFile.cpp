#include<iostream>
using namespace std;
class TWO;
class ONE{
public:
    int a; float b;
    ONE(){ a=12; b=2.4f; }
    operator int(){ return a; }
    operator float(){ return b; }
    ONE operator =(TWO); // Operator should be Member of a CLASS not a Friend Function
    operator TWO(); 
};
class TWO{
public:
    int a; float b;
    TWO(){ a=17; b=9.4f; }
};
ONE ONE::operator=(TWO tmp2){
    ONE tmp1;
    tmp1.a=tmp2.a; tmp1.b=tmp2.b;
    return tmp1;
}
ONE::operator TWO(){
    TWO tmp; 
    tmp.a=a; tmp.b=b;
    return tmp;
}
int main(){
    int i; float f; ONE _1; TWO _2;
    i=_1; f=_1;  cout<<endl<<i<<" "<<f;
    _1=_2;  cout<<endl<<_1.a<<" "<<_1.b;
    _2=_1;  cout<<endl<<_2.a<<" "<<_2.b;
return 0;
}