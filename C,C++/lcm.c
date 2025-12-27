#include<stdio.h>
#define N 100
int lcm[N]={0};
int range(){
    int index=0,count=0;
    while(lcm[index] != 0 && count != 23){
        count ++; index++;
    }
    return count;
}
int divide(int n){
    int tmp=1;
    while(++tmp != n && n%tmp){}
    return tmp;
}
void lcm_clac(int n){
    int rem=1,index=0;
    while(n != 1){
        rem = divide(n);
        lcm[index]=rem;
        n = n/rem;
        index++;
    }   lcm[index]=1;
}
int _divide(int n, int upto){
    if(n==upto) return upto;
    while(++upto != n && n%upto){}
    return upto;
}
void factors(int n){
    int rem=1, quo, index=0;
    do{
        rem = _divide(n,rem); quo = n/rem;
        lcm[index]=rem; index++;
        lcm[index]=quo; index++;
    } while (rem<quo);
}
int comm_divisor(int n1, int n2){
    int n1_rem=_divide(n1,1), n2_rem=_divide(n2,1);
    do{
        if(n1_rem == n2_rem) break;
        if(n1_rem < n2_rem) n1_rem=_divide(n1,n1_rem);
        if(n1_rem > n2_rem) n2_rem=_divide(n2,n2_rem);
    } while (n1_rem<n1 || n2_rem<n2); 
    return n1_rem==n2_rem? n1_rem : 0;
}
int main(){
    lcm_clac(36); int i=0;
    while (lcm[i]){
        printf("%d ",lcm[i]); i++;
    } printf("\n%d" ,range());
    printf("\n%d" ,comm_divisor(4,6));
}