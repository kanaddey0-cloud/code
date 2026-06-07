// Only ONE public class per file
// File name = public class name


// class GrandParent { 
//     int value = 100;  final int VALUE = 10; 
//     final void display() { System.out.println("Display from GrandParent"); } 
//     void show() { 
//         System.out.println("GrandParent show(): value = " + value); 
//     } 
// } 
 
// class Parent extends GrandParent {   // VALUE = 20;  Error:    
//     int value = 200; // hides GrandParent's value 
//     void show() {
//         System.out.println("final value of GrandParent = " + VALUE);  
//         System.out.println("Parent show(): value = " + value); 
//         System.out.println("Accessing GrandParent value using super: " + super.value); 
//     } 
// } 
 
// class Child extends Parent {   // void display() { }  Error: Cannot override final method 
//     int value = 300; // hides Parent's value 
//     void show() { 
//         System.out.println("final value of GrandParent = " + VALUE); 
//         System.out.println("Child show(): value = " + value); 
//         System.out.println("Parent value using super: " + super.value); // refers to Parent’s variable 
//         System.out.println();
//         super.show(); // calls Parent's show() 
//     } 
// } 
 
// public class demo { 
//     public static void main(String[] args) { 
//         Child c = new Child(); 
//         System.out.println();
//         c.show();           System.out.println(); 
//         c.display();
//         System.out.println();
//     } 
// } 

// class Animal { 
//     void eat() { System.out.println("eating..."); } 
// } 
 
// class Dog extends Animal { 
//     void bark() { System.out.println("barking..."); } 
// } 
 
// class Puppy extends Dog { 
//     void weep() { System.out.println("weeping..."); } 
// } 
 
// public class demo { 
//     public static void main(String[] args) { 
//         Puppy p = new Puppy(); 
//         p.eat();    p.bark();    p.weep(); 
//     } 
// } 

// interface Pet { 
//     void play(); 
//     default void sleep() {  System.out.println("Pet is sleeping...");  } 
//     static void info() { 
//         System.out.println("All pets are friendly animals.");  } 
// } 
 
// interface Animal { 
//     default void sleep() {  System.out.println("Animal is sleeping");  } 
// } 
 
// class Cat implements Animal {    } 
 
// class Dog implements Pet, Animal { 
//     public void play() {  System.out.println("Dog is playing fetch!");  } 
//     @Override    //  Must override sleep() to resolve ambiguity explicitly 
//     public void sleep() { 
//         Pet.super.sleep();          // explicitly calls Pet's version 
//         Animal.super.sleep();  // explicitly calls Animal's version 
//         System.out.println("Dog chooses where to sleep!"); 
//     } 
// } 
 
// public class demo { 
//     public static void main(String[] args) { 
//         Dog d = new Dog();  d.play(); 
//         d.sleep();   // resolves ambiguity by overriding 
//         Cat c = new Cat();    c.sleep();    // explicitly called 
//         Pet.info();  // static method call 
//     } 
// } 

// interface Pet { 
//     String SPECIES = "Dog";  int AGE = 3;   // public static final by default 
//     void play();   void sleep(); 
// } 
 
// class Trainable { 
//     static int MAX_HOURS = 5; 
//     void train(){  System.out.println("Is Training");   } 
// } 
 
// class Dog extends Trainable implements Pet { 
//     public void play() {  System.out.println(SPECIES + " is playing");  } 
//     public void sleep() {  System.out.println(SPECIES + " is sleeping");  } 
//     public void train() {   
//         System.out.println(SPECIES + " is training for " + MAX_HOURS + " hours");  } 
// } 

// public class demo { 
//     public static void main(String[] args) { 
//         Dog d = new Dog(); 
//         d.play();  d.sleep();  d.train(); 
// // Access interface variables directly 
//         System.out.println("Species: " + Pet.SPECIES);   
//         System.out.println("Age: " + Pet.AGE); 
//         System.out.println("Max Hours: " + Trainable.MAX_HOURS); 
//     } 
// } 



// // import college.*;
// import college.Student;
// import college.Teacher;

// // class Helper {
// //     void help() {
// //         System.out.println("Helping student");
// //     }
// // }

// public class demo {
//     public static void main(String[] args) {

//         Student s = new Student();
//         s.show();

//         Helper h = new Helper();
//         h.help();

//         Teacher t = new Teacher();
//         t.teach();
//     }
// }


// class Student {
//     static String college = "ABC College";
//     String name;

//     Student(String name) {
//         this.name = name;
//     }
// }

// public class demo {
//     public static void main(String[] args) {
//         Student s1 = new Student("A");
//         Student s2 = new Student("B");

//         System.out.println(s1.college);
//         System.out.println(s2.college);
//         System.out.println(Student.college);
        
//         System.out.println(s1.name);
//         System.out.println(s2.name);
//     }
// }


// class MathUtil {

//     static int add(int a, int b) {
//         return a + b;
//     }

//     static void show() {
//         System.out.println("Static function called");
//     }
// }

// public class Main {
//     public static void main(String[] args) {

//         int result = MathUtil.add(10, 20);
//         System.out.println(result);

//         MathUtil.show();
//     }
// }



// import java.lang.Math;

// public class Main {
//     public static void main(String[] args) {

//         int a = 10;
//         int b = 20;

//         System.out.println(Math.max(a, b));
//         System.out.println(Math.min(a, b));
//         System.out.println(Math.sqrt(25));
//         System.out.println(Math.pow(2, 3));
//     }
// }



// interface Cat { void sound(); }

// interface Animal {
//     void sound();
//     void eat();
// }

// public class Main {
//     public static void main(String[] args) {

//         Cat c = ()-> System.out.println("meow meow");
//         c.sound(); 

//         Animal a = new Animal() {
//             public void sound() {
//                 System.out.println("bhow bhow");
//             }

//             public void eat() {
//                 System.out.println("Eating...");
//             }
//         };

//         a.sound();
//         a.eat();
//     }
// }



// interface Animal {
//     void sound();   // abstract method (no body)
// }

// class Dog implements Animal {
//     public void sound() {
//         System.out.println("Dog barks");
//     }
// }

// class Cat implements Animal {
//     public void sound() {
//         System.out.println("Cat meows");
//     }
// }

// public class Main {
//     public static void main(String[] args) {

//         Animal a;

//         a = new Dog();
//         a.sound();

//         a = new Cat();
//         a.sound();
//     }
// }


