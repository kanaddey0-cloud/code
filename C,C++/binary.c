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
// int lcm[23]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
// int divide(int n, int upto){
//     int tmp=1; 
//     while(upto && ++tmp != n){  
//         if(!(n%tmp)){ upto--; printf("%d\n",tmp);}
//     }
//     return tmp;
// }
int notIn(int bit0, int bit1){
    int b0=0,b1=0;
    while(bit0 && bit1){
        b0=bit0%10; b1=bit1%10;
        if(b0 && b1) return 0;
        bit0=bit0/10; bit1=bit1/10;
    } 
    return 1;
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
int clacM(int binary){
    int rng=range(), rem=0, mul=1, i=0;
    while(binary){
        rem=binary%10;
        if(rem){
            mul=mul*lcm[i++];
        }else{ i++; }
        binary=binary/10;
    }
    return mul;
}
int divide(int n){
    int tmp=1;
    while(++tmp != n && n%tmp){}
    return tmp;
}
void lcm_clac(int n){
    int rem=1, index=0;
    while(n != 1){
        rem = divide(n);
        lcm[index]=rem;
        n = n/rem;
        index++;
    }   lcm[index]=1;
}

int main(){
    lcm_clac(36); int i=0;
    while (lcm[i]){
        printf("%d ",lcm[i]); i++;
    } int rng=range(); printf("\nRange = %d" ,rng);
    int binary=decimalToBinary(31);
    int pow=power(2,rng);
    printf("\nPower = %d",pow);
    printf("\nBinary = %d",binary);
    printf("\nMultiply = %d",clacM(binary));

    int bi,bj;
    for(int i=1; i<pow; i++){
        bi=decimalToBinary(i); 
        for (int j=1; j<pow; j++){
            bj=decimalToBinary(j); 
            if(notIn(bi,bj))
                printf("\n%d ~ %d \t<> %d ~ %d",bi,bj,clacM(bi),clacM(bj));
        }
    }
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
