// import 'dart:io';
// void main() {
//   // String (variable length)
//   stdout.write("Enter Name: ");
//   String? name = stdin.readLineSync();

//   // int (64-bit = 8 bytes on Dart VM)
//   stdout.write("Enter Age: ");
//   int age = int.parse(stdin.readLineSync()!);

//   // double (64-bit IEEE 754 = 8 bytes)
//   stdout.write("Enter Salary: ");
//   double salary = double.parse(stdin.readLineSync()!);

//   // num (parent type of int & double)
//   // Stores either a 64-bit int or a 64-bit double
//   stdout.write("Enter Number: ");
//   num number = num.parse(stdin.readLineSync()!);

//   // bool (implementation-dependent, not guaranteed 1 bit)
//   stdout.write("Enter true/false: ");
//   bool isStudent = stdin.readLineSync()!.toLowerCase() == "true";

//   print("\n----- Output -----");
//   print("Name      : $name");
//   print("Age       : $age");
//   print("Salary    : $salary");
//   print("Number    : $number");
//   print("IsStudent : $isStudent");
// }




class Student {
  late final String name = getName(); // Initialize later, on first use
  // final String name = getName();      // Initialize now
}
String getName() {
  print("Creating..."); return "Kanad";
}

void main() {
  int? x=10, h;
  print("$x $h");

  var y;  // same as dynamic
  y = 10;         print(y);
  y = "Kanad";    print(y);
  y = true;       print(y);
                              print("-------------");
  var w = 10;  // same as int  
  print(w);
  // w = "shreya";   print(w);  // ERROR
  // w = true;       print(w);  // ERROR
                              print("-------------");
  dynamic z = 10; print(z);
  z = "Kanad";    print(z);
  z = true;       print(z);
                              print("-------------");
  dynamic k;
  k = 10;         print(k);
  k = "Kanad";    print(k);
  k = true;       print(k);
                              print("-------------");
  var a = 10; print(a);
  int b = 20; print(b);
  dynamic c = 30;print(c);
  Object d = 40; print(d); // like a void pointer
                              print("-------------");
  final e; 
  e = 10;         print(e);
  // const g;  ERROR
  const f = 60;   print(f);
                              print("-------------");
  String s; // print(s);
  String? s1;  print(s1);
                              print("-------------");
  // late
  Student stu = Student();
  print("Object Created");
  print(stu.name); // when access then late veriable initalzation
  // That's why it's called lazy initialization
}




// class Student {
//   String name;
//   int age;

//   Student(this.name, this.age);
// }

// void main() {
//   Object obj;  // Object can reference(Void Pointer) any Dart object

//   obj = 10;  print(obj);
//   obj = "Kanad";  print(obj);

//   // print(obj.length);           // ❌ Compile-time Error
//   print((obj as String).length);  // ✅ 5

//   obj = [1, 2, 3];                      print(obj); // List
//   obj = {"name": "Shreya", "age": 23};  print(obj); // Map
//   obj = {1, 2, 3};                      print(obj); // Set
//   obj = ("Kanad", 24);                  print(obj); // Record
//   obj = Student("Kanad", 24);           print(obj); // Class Object

//   // print(obj.name);             // ❌ Compile-time Error
//   print((obj as Student).name);   // ✅ Kanad

//   print("----------------");

//   // dynamic can also reference any Dart object
//   dynamic dyn = Student("Shreya", 23); print(dyn.name);   // ✅ No cast needed
//   dyn = "Hello";                       print(dyn.length); // ✅ String.length
//   dyn = 10; // int
//   // print(dyn.length);  // ❌ NoSuchMethodError
// }


// void main() {
//   // Numeric Conversions ------------------------

//   int i = 10;
//   double d = i.toDouble();      // int -> double

//   double pi = 3.14;
//   int x = pi.toInt();           // double -> int

//   String s = i.toString();      // int -> String

//   int a = int.parse("100");        // String -> int
//   double b = double.parse("12.5"); // String -> double
//   num c = num.parse("99");         // String -> num

//   print("$d  $x  $s  $a  $b  $c");

//   print("----------------");


//   // Object Casting -----------------------------

//   Object obj = "Kanad";

//   if (obj is String) {
//     print(obj.length);          // Type promoted automatically
//   }

//   String name = obj as String;  // Explicit cast
//   print(name);

//   print("----------------");


//   // Runtime Error Example ----------------------

//   dynamic value = 10;

//   // Compiles, but crashes at runtime
//   // print(value.length);

//   value = "Shreya";
//   print(value.length);          // 6
// }
