// // #include<stdio.h>
// // enum colors{RED, BROWN, ORANGE}; 
// // int main(){
// //     // int a=1, b=2, c=3;
// //     // int x= c==(a+b);
// //     // printf("%d",x);
// //     // int n=(a=c, b+=a, c=100);
// //     // printf("\n %d %d %d %d",n ,a, b, c);
// //     // float f=2.0123456789;
// //     // printf("\n %f",f);

// //     // int a=10;
// //     // float b =++a;
// //     printf ("%d..%f..%d \n", RED, BROWN, ORANGE); 
// //     // int i = -9; 
// //     // printf("%d %d %d", i++, ++i, ++i); 

// //     // int i = -1; 
// //     // printf("sizeof(i) = %d", sizeof(i)); 
// // }

// // #include<iostream> 
// //  using namespace std; 
 
// //  void print() 
// //  { 
// //   cout<< "Hi"; 
// //  } 
// //  int main() 
// //  { 
// //   int var = 0; 
// //   var = print(); 
// //   cout<< var; 
// //   return 0; 
// //  } 
 
// //  #include <stdio.h>
// // void foo();
// // int main()
// // {
// //     void foo();
// //     foo();
// //     return 0;
// // }
// // void foo()
// // {
// //     printf("2 ");
// // }

// // #include <stdio.h>
// // void foo();
// // int main()
// // {
// //     void foo(int);
// //     foo(1);
// //     return 0;
// // }
// // void foo(int i)
// // {
// //     printf("2 ");
// // }

// // #include <stdio.h>
// // void foo(int);
// // int main()
// // {
// //     void foo(); 
// //     foo(1);
// //     return 0;
// // }
// // void foo(int i)
// // {
// //     printf("2 ");
// // }
// // What is the output of the following program ? 
// //  #include <stdio.h> 
// //  enum colors{RED, BROWN, ORANGE}; 
// //  int main( ) 
// //  { 
// //     int a=0;
// //   printf ("%ld..%d..%d", a, a+1, a+2); 
// //   return 0;
// //  } 
// //  (A) Compiler Error (B) 0..0.000000..1 
// //  (C) 0..1.000000..2 (D) Runtime Error 
// // void fun(int a, int b, int c){
// //   printf("\na=%d  b=%d  c=%d",a,b,c);
// // }


// // int fun(){ 1<0? return 1: return 0; }
// // #define a 10
// #define x(a, b) ((a)>(b))?(a):(b);
// #define c(x) (x*x*x)
// #include<stdio.h>
// int main(){
// // int a=10;
// int b=3;
// // int s=b++ * b++ * b++;
// // int s=++b * ++b * ++b; 
// // b=3;
// int k=c(b++);
// printf("k=%d, b=%d \n",k,b);
// // printf("s=%d",++b + ++b + ++b);
// // printf("\n%d  %d  %d",++b , b++ , b++);

// // int m=10;
// // int n=5;
// // int d=x(++m, n++);
// // printf("\nd=%d, m=%d, n=%d",d,m,n);

// // int a=10;
// // int f = ++a+ ++a+a++ + ++a;
// // printf("%d %d",f,a);
// // printf("\n%d  %d  %d  %d",--a,++a,--a,a++);
// // fun((a,0,a),a,a);

// // double d=14728749.22;
// // int n=d;
// // printf("\n %d",n); printf("   %1f",d);

// // int i=10; float f=2.5f;
// // scanf("%f",&i);
// // printf("%d",i);
// // scanf("%d",&f);
// // printf("%f",f);

// // printf("%d",fun());
// printf("%d",(2)+1>0?1:0);
// printf("%d",2+(1>0?1:0));
// printf("%d",1>0?1:0);
//   return 0;
// }
// // if()//error
// //  if("")//true
// //   if(" ")//true
// //    if('')//flase
// //     if(' ')//true

// #include <stdio.h>
// // void _f(); void _f(int); //Error for Overloading in Global
// void _1(); void _2(int);
// void foo(int);
// void fun(){
//   void foo(); //No ERROR because OVERloading not support
//     foo(0);
// }
// int main()
// {
//     void foo(int); //No ERROR 
//     void foo(); //No ERROR 
//     // void foo(float); //Error Because of foo(int) function is Global
//     void _f(); void _f(int); //No Error for Overloading in Local
//     void _1(); void _2(int);     
//     foo(0);
//     fun();
//     return 0;
// }
// void foo(int a)
// {  printf("2 ");  }

// #include<stdio.h>
// void foo(int n, int sum)
// {
//   int k = 0, j = 0;
//   if (n == 0) return;
//     k = n % 10; 
//   j = n / 10;
//   sum = sum + k;
//   foo (j, sum);
//   printf ("%d,", k);
// }

// int a, b, c = 0;
// void prtFun (void);
// int main ()
// {
//     static int a = 1; /* line 1 */
//     prtFun();
//     a += 1;
//     prtFun();
//     printf ( "\n %d %d " , a, b) ;
// //     // int x=5>8?10:1!=2<5?20:30;
// //     // printf ( "\n %d  " ,x) ;
// // char c=257;
// // int i=0xa;
// // printf("%d",i);
//     return 0;
// }
// void prtFun (void)
// {
//     static int a = 2; /* line 2 */
//     int b = 1;
//     a += ++b;
//     printf (" \n %d %d " , a, b);
// }

// #include <stdio.h>
// int main() {
//     // int choice = 4;
//     // switch (choice) {
//     //     case 1:
//     //         printf("Option 1 selected.\n");
//     //         break;
//     //     case 2:
//     //         printf("Option 2 selected.\n");
//     //         break;
//     //     case 3:
//     //         printf("Option 3 selected.\n");
//     //         break;
//     //     default:
//     //         printf("Invalid option.\n");
//     // }
// char s1[10]="Kanad Dey";
// char s2[4]={'S','o','n','u'};
// printf("%s",s2);
// char s[9]=" Shreya ";
// printf("\nI Love \          
//               YOU");  // print BLANK SPACE before "you" how many space in there
// printf("\nI Love"          
//             " YOU");  // Do not print BLANK SPACE
//     return 0;
// }

// #include<stdio.h>
// #include<string.h>
// // void foo(char *a){
// //     if(*a && *a != ' '){ foo(a+1); putchar(*a); }
// // }
// // // void f1(char *s1, char *s2){ char *tmp=s1; s1=s2; s2=tmp; }
// // // void f2(char **s1, char **s2){ char *tmp=*s1; *s1=*s2; *s2=tmp; }
// int main(){
//     // foo("ABCD EFGH");
// //     // char *s1="Hii", *s2="Bye";
// //     // f1(s1,s2); printf("\n%s %s",s1,s2);
// //     // f2(&s1,&s2); printf("\n%s %s",s1,s2);
// char *c1="GATECSIT2025";
// char c2[]="JECA2025";
// char *p1=c1;
// char *p2=c2;
// printf("\n%d",(int)strlen(c1+2[p1]-6[p1]-1));
// printf("\n%s",p2+p2[3]-p2[1]); // NO output p - 4(65-69)
//     return 0;
// }

// #include<stdio.h>
// #include<string.h>
// int main(){
// char p[20];
// char *s="string";
// int len=strlen(s);
// for(int i=0; i<len; i++){
//     p[i]=s[len-i];
// } printf("%s",p); //Nothing
//     return 0;
// }

// #include <stdio.h>
// int a = 0;
// void get(int n) { a++;
//     if (n < 1)  return;
//     get(n - 1);
//     get(n - 3);
// }
// int main() {
//     get(6);
//     printf("%d\n", a);
//     return 0;
// }

// #include <stdio.h>  
// int x = 2;  
// int f()  
// {  
//     if (x == 0)    return x + 1;  
//     else    return x - 1;  
// }  
// int g(){      return x++;  }  
// int main()  
// {  
//     int i = (f() + g()) | g(); //bitwise or  
//     printf("%d\n",x);
//     int j = g() | (f() + g()); //bitwise or  
//     printf("%d %d",i,j);
    
//     return 0;
// }