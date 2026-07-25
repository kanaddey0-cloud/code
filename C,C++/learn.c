// #include <stdio.h>

// int main() {
//     int a = 5, b = 3, sum;

//     asm (
//         "addl %%ebx, %%eax;"
//         : "=a"(sum)          // output
//         : "a"(a), "b"(b)    // input
//     );

//     printf("Sum = %d\n", sum);

//     return 0;
// }

#include <stdio.h>

struct Student {
    char name[20];
    int roll;
    int marks;
};

int main(){
    char name1[] = "Alice";
    int roll1 = 1;
    int marks1 = 85;

    char name2[] = "Bob";
    int roll2 = 2;
    int marks2 = 90;

    char name3[] = "Charlie";
    int roll3 = 3;
    int marks3 = 78;


    struct Student s1;
    struct Student s2;
    struct Student s3;

    strcpy(s1.name, "Alice");
    s1.roll = 1;
    s1.marks = 85;

    strcpy(s2.name, "Bob");
    s2.roll = 2;
    s2.marks = 90;

    strcpy(s3.name, "Charlie");
    s3.roll = 3;
    s3.marks = 78;

    // struct Student s1 = {"Alice",1,85};
    // struct Student s2 = {"Bob",2,90};
    // struct Student s3 = {"Charlie",3,78};


    struct Student stu[3];

    strcpy(stu[0].name, "Alice");
    stu[0].roll = 1;
    stu[0].marks = 85;

    strcpy(stu[1].name, "Bob");
    stu[1].roll = 2;
    stu[1].marks = 90;

    strcpy(stu[2].name, "Charlie");
    stu[2].roll = 3;
    stu[2].marks = 78;
}
