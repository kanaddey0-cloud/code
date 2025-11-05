#include<stdio.h>
int mx_n=0;
// int array_n=7;
int array_row=7;
int array_coloum=7;
// int array_elements=array_row*array_coloum;
int arr[7][7] = {
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,1},
    {0,1,0,1,0,1,1},
    {0,0,1,0,1,0,0},
    {0,1,0,1,0,0,0},
    {0,0,1,0,0,0,0}
};
int pointed(int p_i, int p_j){
    return arr[p_i][p_j];
}
int up(int p_i, int p_j){
    int count=0;
    while(--p_i > 0){
        if(pointed(p_i, p_j)) {count++;}
    }
    return count;
}
int down(int p_i, int p_j){
    int count=0;
    while(++p_i < array_row){
        if(pointed(p_i, p_j)) {count++;}
    }
    return count;
}
int left(int p_i, int p_j){
    int count=0;
    while(--p_j > 0){
        if(pointed(p_i, p_j)) {count++;}
    }
    return count;
}
int right(int p_i, int p_j){
    int count=0;
    while(++p_j < array_coloum){
        if(pointed(p_i, p_j)) {count++;}
    }
    return count;
}
int left_up(int p_i, int p_j){
    int count=0;
    while(--p_i>0 && --p_j>0){
        if(pointed(p_i, p_j)) {count++;}
    }
    return count;
}
int right_down(int p_i, int p_j){
    int count=0;
    while(++p_i<array_row && ++p_j<array_coloum){
        if(pointed(p_i, p_j)) {count++;}
    }
    return count;
}
int right_up(int p_i, int p_j){
    int count=0;
    while(--p_i>0 && ++p_j<array_coloum){
        if(pointed(p_i, p_j)) {count++;}
    }
    return count;
}
int left_down(int p_i, int p_j){
    int count=0;
    while(++p_i<array_row && --p_j>0){
        if(pointed(p_i, p_j)) {count++;}
    }
    return count;
}
int up_down(int p_i, int p_j){
    return 1 + up(p_i,p_j) + down(p_i,p_j);
}
int left_right(int p_i, int p_j){
    return 1 + left(p_i,p_j) + right(p_i,p_j);
}
int lup_rdwn(int p_i, int p_j){
    return 1 + left_up(p_i,p_j) + right_down(p_i,p_j);
}
int rup_ldwn(int p_i, int p_j){
    return 1 + right_up(p_i,p_j) + left_down(p_i,p_j);
}
int max(int a, int b){
    if(a>b){ return a; }else{ return b; }
}
int maximum(int p_i, int p_j){
    int a,b,c,d;
    a=up_down(p_i,p_j);
    b=left_right(p_i,p_j);
    c=lup_rdwn(p_i,p_j);
    d=rup_ldwn(p_i,p_j);
    return max(max(a,b),max(c,d));
}
void line(){
    for(int i=0; i<array_row; i++){
        for(int j=0; j<array_coloum; j++){
            if(arr[i][j]){
                mx_n=max(mx_n,maximum(i,j));
            }
        }
    }
}
int main (){
    line();
    printf("%d",mx_n);
return 0;
}