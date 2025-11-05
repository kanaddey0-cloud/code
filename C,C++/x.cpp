#include <iostream>
using namespace std;
class node{int a;};
class abc{
    node n;
    int a;float b;
    public:
    static int count;
    abc(){cout<<"Defual Constructor";}
    abc(int x, float y){
        a=x; b=y;
        cout<<a<<" "<<b<<" Constructor"<<endl;
    }
    void get(int x, float y){
        a=x; b=y;
        sh();
    }
    void sh(){
        cout<<endl<<endl<<a<<" "<<b;
    }
    ~abc(){cout<<count<<" Destractor\n";count++;}
};int abc::count;

int main() {
    abc::count=0;
    abc obj(2,2.5),obj2(5,5.6),ob3;
    ob3.get(10,2.56);
   obj.sh();
   obj2.sh();
   ob3.sh();
   cout<<"\n\n";
    return 0;
}
