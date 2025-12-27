#include<stdio.h>
#define N 100
int lcm[N]={0};
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
int range(){
    int index=0,count=0;
    while(lcm[index] != 0 && count != 23){
        count ++; index++;
    }
    return count;
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
int notIn(int bit0, int bit1){
    int b0=0,b1=0;
    while(bit0 && bit1){
        b0=bit0%10; b1=bit1%10;
        if(b0 && b1) return 0;
        bit0=bit0/10; bit1=bit1/10;
    } 
    return 1;
}
int power(int number, int pow){
    int temp=number; 
    while(--pow){
        number=number*temp;
    } return number;
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
int max(int a, int b){ return a>=b? a:b; }
int min(int a, int b){ return a<=b? a:b; }
int oddEven(int num){ return num%2? 0:1; }
int minus_plus(int num){ return num<0? 1:0; }
char p_m__char(int p_m){ return p_m? '-':'+'; }
int unSign(int number){ return number<0? number*-1 : number; }
struct middle{ int f_num,s_num; char f_op,s_op; } result;
void write(int f, int s,int operation, int target, int p_m){
    if(p_m && operation){
        result.f_num=max(f,s);
        result.f_op=p_m__char(p_m);
        result.s_num=min(f,s);
        result.s_op='+';
    }else if (p_m && !operation){
        result.f_num=f;
        result.f_op=p_m__char(p_m);
        result.s_num=s;
        result.s_op=p_m__char(p_m);
    }else if (!p_m && operation){
        result.f_num=max(f,s);
        result.f_op=p_m__char(p_m);
        result.s_num=min(f,s);
        result.s_op='-';
    }else if (!p_m && !operation){
        result.f_num=f;
        result.f_op=p_m__char(p_m);
        result.s_num=s;
        result.s_op=p_m__char(p_m);
    }else{ printf("\n ERROR! \n"); }
}
int _divide(int n, int upto){
    if(n==upto) return upto;
    while(++upto != n && n%upto){}
    return upto;
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
int cx2, cx, c;
int valid_tearm(int f, int s){
    int us_cx2=unSign(cx2), us_c=unSign(c);
    if( !(max(us_cx2,f)%min(us_cx2,f)) && !(max(us_c,s)%min(us_c,s)) ){
        if((max(us_cx2,f)/min(us_cx2,f)) == (max(us_c,s)/min(us_c,s))) { return 1; }
    }
    if( !(max(us_cx2,s)%min(us_cx2,s)) && !(max(us_c,f)%min(us_c,f)) ){
        if((max(us_cx2,s)/min(us_cx2,s)) == (max(us_c,f)/min(us_c,f))) { return 1; }
    }
    int c_d_left=comm_divisor(us_cx2,f), c_d_right=comm_divisor(us_c,s);
    if(c_d_left && c_d_right) return 1;
    c_d_left=comm_divisor(us_cx2,s); c_d_right=comm_divisor(us_c,f);
    if(c_d_left && c_d_right) return 1;
    return 0;
}
int find(int f, int s, int target){
    if(minus_plus(target)){
        if(f+s == unSign(target)){ 
            if(valid_tearm(f,s)){
                write(f,s,0,target,1); return 1;
            } 
        }
        if(max(f,s)-min(f,s) == unSign(target)){ 
            if(valid_tearm(f,s)){    
                write(f,s,1,target,1); return 1;
            } 
        }
    }else{
        if(f+s == unSign(target)){ 
            if(valid_tearm(f,s)){
                write(f,s,0,target,0); return 1;
            } 
        }
        if(max(f,s)-min(f,s) == unSign(target)){ 
            if(valid_tearm(f,s)){
                write(f,s,1,target,0); return 1;
            } 
        }
    }
    return 0;
}
int flag=1;
struct middle middle_tearm(){
    int bi=0,bj=0,first,second;
    lcm_clac(unSign(cx2)*unSign(c));
    int times=power(2,range());
    for(int i=1; i<times; i++){
        bi=decimalToBinary(i); 
        for (int j=1; j<times; j++){
            bj=decimalToBinary(j);
            if(notIn(bi,bj)){
                first=clacM(bi); second=clacM(bj);
                if(find(first,second,cx)) 
                    return result; 
            }
        }
    }
    flag=0; printf("\n Middle Tearm Not Posible! \n\n");
}
void ppp(void);
int main(){

    printf("The expression is ax%c+bx+c\n",-3);
    printf("input a=");
    scanf("%d",&cx2);
    printf("input b=");
    scanf("%d",&cx);
    printf("input c=");
    scanf("%d",&c);
    printf("\n %dx%c%c%dx%c%d\n",cx2,-3,p_m__char(minus_plus(cx)),unSign(cx),p_m__char(minus_plus(c)),unSign(c));

    // ppp();
    result=middle_tearm();
    if(flag)
        printf("= %dx%c%c%dx%c%dx%c%d\n\n",cx2,-3,result.f_op,result.f_num,result.s_op,result.s_num,p_m__char(minus_plus(cx2)),unSign(c));

return 0;
}
void ppp(){
    printf("\n");
    int i=0,j=range();
    while(j--){
        printf("%d\n",lcm[i++]);
    }
}