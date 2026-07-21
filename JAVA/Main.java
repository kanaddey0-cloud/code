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


// interface A {
//     void methodA();
// }

// interface B {
//     void methodB();
// }

// // Interface C extends both A and B
// interface C extends A, B {
//     void methodC();
// }

// class demo implements C, A, B {

//     public void methodA() {
//         System.out.println("Method A");
//     }

//     public void methodB() {
//         System.out.println("Method B");
//     }

//     public void methodC() {
//         System.out.println("Method C");
//     }

//     public static void main(String[] args) {
//         Test obj = new Test();

//         obj.methodA();
//         obj.methodB();
//         obj.methodC();
//     }
// }


// interface A { void show(); }
// interface B { void show(); }
// interface Dmo extends A, B {
//     default void show() {
//         System.out.println("Show Method");
//     }
// }

// class Demo1 implements A, B {
//     public void show() { }
// }
// class Demo2 implements Dmo { }   // ✅ OK
// class Demo3 implements Dmo, A, B { } // ✅ OK (redundant but legal)
// class Demo4 extends Demo1 implements Dmo { } // ❌ conflict between the inherited class method and the interface default method.

// interface C { int show(); }
// interface D { void show(); }

// class demo5 implements C, D {
//     // Different return type only → ❌ ERROR! 
//     // Different parameters → ✅ Method Overloading
// }


// Constructor Chaining using this()

// class A {
//     A() {
//         this(10); // calls A(int) constructor
//         System.out.println("A constructor");
//     }
//     A(int x) { System.out.println("A : " + x); }
// }

// class B extends A {
//     B() {
//         this(20); // calls B(int) constructor
//         System.out.println("B constructor");
//     }
//     B(int y) {
//         super(); // calls A() constructor
//         System.out.println("B : " + y);
//     }
// }

// class C extends B {
//     C() {
//         this(30); // calls C(int) constructor
//         System.out.println("C constructor");
//     }
//     C(int z) {
//         super(); // calls B() constructor
//         System.out.println("C : " + z);
//     }
// }

// public class Main {
//     public static void main(String[] args) {
//         new C();
//     }
// }

// class Demo5 extends Demo1 implements Dmo, Dmo1 {
//     public void show() {
//         Dmo.super.show(); Dmo1.super.show();   // choose one, then valid
//         Demo1.super.show();
//     } }   


// class Main { 
//     void add(int a, int b) { 
//         System.out.println(a + b); 
//     } 
 
//     void add(int a, int b, int c) { 
//         add(a+b, c); 
//     } 
 
//     void add(double a, double b) { 
//         System.out.println(a + b); 
//     } 
 
//     public static void main(String args[]) { 
//         Main t = new Main(); 
 
//         t.add(10, 20); 
//         t.add(10, 20, 30); 
//         t.add(10.5, 20.5); 
//     } 
// } 