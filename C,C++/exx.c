// #include <stdio.h>
// int main() {
//     int n = 4,r=0;
//     while (r++ != 2*n-1) {
//         int temp = r>n? 2*n-r:r;
//         while (temp--) printf(" * ");
//         printf("\n");
//     } return 0;
// }



// #include<stdio.h>
// int main(){
// int n,count,stop=1,k=1,light=1;
// scanf("%d",&n);
// int br=(n*2)-1;
// int loop=(n*n)+br;
// count=stop;
// while(loop--){
//    if(count--){ printf(" * ");}
//     else if (stop==n){
//         stop=n-1;
//         light=0;
//         count=stop;
//         printf("\n");
//     }
//     else if(light){
//         printf("\n");
//         stop++;
//         count=stop;
//     }else{
//         printf("\n");
//         stop--;
//         count=stop;
//     }
// }
// return 0;
// }



// #include<stdio.h>
// int n=4;
// void loop2(int temp){
//     if(!temp)return;
//     printf(" * ");
//     loop2(--temp);
// }
// void loop(int r, int temp){
//     if(!temp)return;
//     while(temp--) {printf(" * ");}
//     loop2(temp);
//     printf("\n");
//     temp= ++r>n? 2*n-r:r;
//     loop(r, temp);
// }
// int main(){
//     loop(1,1);  
// return 0;
// }



// #include<stdio.h>
// int n;
// void loop(int count,int r, int temp){
//     if(!count) return;
//     if(!temp){
//         printf("\n");
//         r++;
//         int temp=r>n? 2*n-r:r ;
//         loop(count,r,temp);
//     }else{
//         printf(" * ");  count--; 
//         loop(count,r,--temp);
//     }
// }
// int main(){
//     scanf("%d",&n);
//     int count=n*n;
// loop(count,1,1);

// return 0;
// }