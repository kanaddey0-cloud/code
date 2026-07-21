// 1. Class
// 2. Object
// 3. Constructor
// 4. this & super
// 6. static
// 7. final & const
// 8. Inheritance (extends)
// 9. @override
// 11. Abstract Class
// 12. implements (Interface)
// 13. with (Mixin)
// 14. Enum
// 15. Extension
// 16. Generics
// 17. Factory Constructor
// 18. Callable Class
// 19. Operator Overloading


//-----------------------------------------------------------------------

// // Dimond Problem
// class Child extends Parent
//     with Mixin1, Mixin2
//     implements Interface1, Interface2 {
// }
//   ✅ 1 extends
//   ✅ 0 or more with
//   ✅ 0 or more implements

// // Mixin with variable & multiple methods
// mixin CanMove {
//   int speed = 10;

//   void walk() => print("Walking");
//   void run() => print("Running from CanMove");
//   void jump() => print("Jumping");
//   void showSpeed() => print("Speed: $speed");
// }
// class Human with CanMove {} // Uses one mixin


// // Inheritance + multiple mixins
// class Animal { void eat() => print("Eating"); }
// mixin CanRun { void run() => print("Running from CanRun"); }
// mixin CanSwim { void swim() => print("Swimming"); }

// class Dog extends Animal with CanRun, CanSwim {}


// // Method conflict (Last overrides Previous)
// mixin A { void hello1() => print("Hello 1 from mixin A");
//           void hello2() => print("Hello 2 from mixin A"); }
// mixin B { void hello2() => print("Hello 2 from mixin B");
//           void hello3() => print("Hello 3 from mixin B"); }

// class C { void hello1() => print("Ovverride class C");
//           void hello2() => print("Ovverride class C"); }
// class D { void hello2() => print("Ovverride class D");
//           void hello3() => print("Ovverride class D"); }

// class E { void hello1() => print("Hello 1 from class E");
//           void hello3() => print("Hello 3 from class E"); 
//           void hello4() => print("Hello 4 from class E"); }

// mixin F { void hello1() => print("Ovverride class E");
//           void hello3() => print("Ovverride class E"); }

// // 1st. Class itself and implemetations (if written)
// // 2nd. Last mixin
// // 3rd. Previous mixin(s)
// // 4th. Parent class (extends)

// class Test1 extends E
//           with A, B           // last is Win
//           implements C, D {   // you must implement those method in class C, D

//   // void hello1() => print("Hello 1 from class  Test 1");
//   // void hello2() => print("Hello 2 from class  Test 1");
//   // void hello3() => print("Hello 3 from class  Test 1");
//   // void hello4() => print("Hello 4 from class  Test 1");
// }

// mixin Test_2 implements A, B, C, D, E, F {   
//   // Must Override else Test2 not use it ERROR
//   void hello1() => print("Hello 1 from class  Test 2");
//   void hello2() => print("Hello 2 from class  Test 2");
//   void hello3() => print("Hello 3 from class  Test 2");
//   void hello4() => print("Hello 4 from class  Test 2");
// }

// class Test2 with Test_2 {}

// void main() {

//   print("----- Human -----");
//   Human h = Human();
//   h.walk();  h.run();  h.jump();  h.showSpeed();

//   print("\n----- Dog -----");
//   Dog d = Dog();
//   d.eat();  d.run();  d.swim();

//   print("\n----- Method Conflict -----");
//   Test1 t1 = Test1();
//   t1.hello1(); 
//   t1.hello2(); // B wins
//   t1.hello3(); 
//   t1.hello4(); 

//   print("\n----- Method Conflict -----");
//   Test2 t2 = Test2();
//   t2.hello1(); 
//   t2.hello2(); // B wins
//   t2.hello3(); 
//   t2.hello4(); 
// }


//-----------------------------------------------------------------------

// // Constructor Chaining with initialization list
// class Animal {
//   String name = "Animal";

//   Animal() { print("Animal Constructor"); } // Constructors cannot use arrow (=>)
//   void sound() => print("-> Animal Sound");
// }

// class Dog extends Animal { // (Constructor Chaining)
//   String name = "Dog";

//   Dog() : super() {     // initialization list
//     print(this.name);  print(super.name);  
//     this.sound();      super.sound();      
//   }
//   void sound() => print("-> Dog Bark"); 
// }

// class Person {
//   Person(String role) { print("Person Role: $role"); }
// }

// class Student extends Person {
//   final String name;
//   int age = 16;

//   // 1. (Initializer List) 
//   Student(String n, this.age)
//       : name = n.toUpperCase(), //- Initialize final fields
//         super("Student");       //- Call parent constructor

//   // 2. (Named Constructor)- Calls another constructor in the same class
//   Student.guest() : this("Guest", 18); // The reason is readability and convenience, not necessity.
//   Student.shreya() : this("SHREYA", 23); // Diffreace value with-in single construtor
// }

// void main() {
//   Dog();  print("");

//   Student s = Student.guest();   // Because Student.guest() tells you the intention (just a meaning) immediately.
//   Student s1 = Student.shreya(); // Because Student.shreya() tells you the intention immediately.
//   Student s2 = Student("KANAD", 24);

//   print("\n${s.name} ${s.age}");
//   print("${s1.name} ${s1.age}");
//   print("${s2.name} ${s2.age}");
// }
// // we must call super construtor
//   // class P1 { P1(); }
//   // class C1 extends P1 { C1(); } // ✅ Dart automatically calls super()

//   // class P2 { P2(String name); }
//   // class C2 extends P2 { C2() : super("Kanad"); } // ✅ Required


//-----------------------------------------------------------------------

// // Access Modifier
// class Student {
//   String name = "Kanad";  // Public Variable
//   int _age = 24;          // Private Variable

//   void showInfo() {  // Public Method
//     print("Name: $name");  print("Age: $_age");
//     _secret(); 
//   }
//   void _secret() => print("This is a private method.");  // Private Method

// // @protected
// // Tells the Dart Analyzer (compiler/IDE) that this method
// // is intended to be used only by this class and its subclasses.
// // It is ONLY a warning, NOT an enforced access modifier.
// }

// void main() {
//   Student s = Student();

//   print(s.name);  s.showInfo();
//   print(s._age);  s._secret();
// }


//-----------------------------------------------------------------------

// // Factory Constructor
// class Student {
//   String name;
//   static final Student _guest = Student._("Guest");  // Store one object

//   Student._(this.name);                       // Private constructor
//   factory Student.guest() { return _guest; }  // Factory constructor
// }

// void main() {
//   Student s1 = Student.guest();
//   Student s2 = Student.guest();

//   print("${s1.name} ${s2.name}");  print(identical(s1, s2));
// }


//-----------------------------------------------------------------------

// // calleble class: Callable Class: Used when an object needs to remember its own state (values).
// class Adder {   // And use them whenever it is called like a function.
//   int base;
//   Adder(this.base);

//   int call(int x) => base + x;  // calleble function
// }

// void main() {
//   Adder add10 = Adder(10);  // add10 remembers base = 10.
//   Adder add20 = Adder(20);  // for codder to remember it, oparate on which values.

//   print(add10(5));       // Object called like a function.
//   print(add10.call(5));  // same thing.
//   print(add20(5));
// }
// // Any class can become callable simply by defining a method named call().


//-----------------------------------------------------------------------

