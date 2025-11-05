// #include <stdio.h>
// int main() { 
// int i = 0; 
// for (; ;) 
//     printf("In for loop\n"); 
// printf("After loop\n"); 
// } 

// #include <stdio.h> 

// void foo();  // Function declaration (implicitly assumes 'void foo(void)')

// int main() 
// { 
//     void foo(int);  // Local redeclaration with different signature
//     foo(1);  // Calling foo with an integer argument
//     return 0; 
// } 

// void foo(int i) // Function definition with parameter
// { 
//     printf("2 "); 
// }  

#include <stdio.h> 
void convert(int n) { 
  if (n <= 1) 
    printf("%d", n); 
  else { 
    convert(n/2); 
    printf("%d", n%2); 
  } 
} 

void foo();  // (Line 2) Global declaration - Assumes foo(void) (no arguments)

int main() 
{ 
  // convert(3);
    // void foo(int);  // (Line 5) Local redeclaration with an int parameter
    // foo();  // (Line 6) Calls foo() with no arguments
    // return 0; 
// printf("%d",main);

} 

void foo()  // (Line 9) Function definition with no parameters
{ 
    printf("2 "); 
}  

