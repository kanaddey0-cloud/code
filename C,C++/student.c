#include <stdio.h>

// int main()
// {
//     char name1[20] = "Kanad";
//     int roll1 = 101;
//     char grade1 = 'A';

//     char name2[20] = "Rahul";
//     int roll2 = 102;
//     char grade2 = 'B';

//     char name3[20] = "Amit";
//     int roll3 = 103;
//     char grade3 = 'A';

//     char name4[20] = "Riya";
//     int roll4 = 104;
//     char grade4 = 'B';

//     printf("Student 1: %s %d %c\n", name1, roll1, grade1);
//     printf("Student 2: %s %d %c\n", name2, roll2, grade2);
//     printf("Student 3: %s %d %c\n", name3, roll3, grade3);
//     printf("Student 4: %s %d %c\n", name4, roll4, grade4);

//     return 0;
// }



// struct Student
// {
//     char name[20];
//     int roll;
//     char grade;
// };

// int main()
// {
//     int a=10;
//     struct Student s1 = {"Kanad", 101, 'A'};
//     struct Student s2 = {"Rahul", 102, 'B'};
//     struct Student s3 = {"Amit", 103, 'A'};
//     struct Student s4 = {"Riya", 104, 'B'};

//     printf("Student 1: %s %d %c\n", s1.name, s1.roll, s1.grade);
//     printf("Student 2: %s %d %c\n", s2.name, s2.roll, s2.grade);
//     printf("Student 3: %s %d %c\n", s3.name, s3.roll, s3.grade);
//     printf("Student 4: %s %d %c\n", s4.name, s4.roll, s4.grade);

//     return 0;
// }



// struct Student
// {
//     char name[20];
//     int roll;
//     char grade;
// };

// int main()
// {
//     struct Student students[4] = { {"Kanad", 101, 'A'},
//                                    {"Rahul", 102, 'B'},
//                                    {"Amit", 103, 'A'},
//                                    {"Riya", 104, 'B'} };

//     printf("Student 1: %s %d %c\n", students[0].name, students[0].roll, students[0].grade);
//     printf("Student 2: %s %d %c\n", students[1].name, students[1].roll, students[1].grade);
//     printf("Student 3: %s %d %c\n", students[2].name, students[2].roll, students[2].grade);
//     printf("Student 4: %s %d %c\n", students[3].name, students[3].roll, students[3].grade);

//     return 0;
// }



typedef struct Student
{
    char name[20];
    int roll;
    char grade;
} Student;

int main()
{

    int a=10;
    int *ptr=&a;

    Student s1 = {"Kanad", 101, 'A'};
    Student s2 = {"Rahul", 102, 'B'};
    Student s3 = {"Amit", 103, 'A'};
    Student s4 = {"Riya", 104, 'B'};

    Student *p;

    p = &s1;  printf("Student 1: %s %d %c\n", (*p).name, (*p).roll, (*p).grade);

    p = &s2;  printf("Student 2: %s %d %c\n", p->name, p->roll, p->grade);
    p = &s3;  printf("Student 3: %s %d %c\n", p->name, p->roll, p->grade);
    p = &s4;  printf("Student 4: %s %d %c\n", p->name, p->roll, p->grade);

    return 0;
}