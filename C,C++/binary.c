#include<stdio.h>

int power(int number, int pow){
    int temp=number; 
    while(--pow){
        number=number*temp;
    } return number;
}
int max(int a, int b){ return a>=b? a:b; }
int min(int a, int b){ return a<=b? a:b; }
int oddEven(int num){ return num%2? 0:1; }
int minus_plus(int num){ return num<0? 1:0; }
char p_m__char(int p_m){ return p_m? '-':'+'; }
int unSign(int number){ return number<0? (number*-2)/2 : number; }
int lcm[23]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int divide(int n, int upto){
    int tmp=1; 
    while(upto && ++tmp != n){  
        if(!(n%tmp)){ upto--; printf("%d\n",tmp);}
    }
    return tmp;
}

int revers(int binary){
    int rev=0;
    while(binary){
        rev=rev*10+(binary%10); 
        binary=binary/10; 
    }
    return rev;
}
int addZero(int binary, int zero){
    while(zero--){binary=binary*10;}
    return binary;
}
int decimalToBinary(int decimal){
    int binary=0,flag=1,zero=0;
    while(decimal != 1){
        if(flag){
            if(decimal%2){ flag=0; }
            else{ zero++; }
        }
        binary=binary*10+(decimal%2);
        decimal=decimal/2;
    }    
    binary=binary*10+decimal;
    binary=revers(binary);
    return addZero(binary,zero);
}

int main(){
    
    printf("\n%d\n\n",decimalToBinary(13));
}
// void ABequalC(){
//     int us_cx2=unSign(cx2), us_cx=unSign(cx), us_c=unSign(c);
//     int ni,nj;
//     if(oddEven(cx)){ ni=nj=us_cx/2; ++nj; }
//     else{ ni=nj=us_cx/2; }
//     for(int i=ni; i>0; i--){
//         for(int j=nj; j<=us_cx; j++){
//             if(find(i,j,cx))
//                 return result;
//         }
//     }
// }

    // if(unSign(cx2)*unSign(c) == cx){ ABequalC();  return result; }
