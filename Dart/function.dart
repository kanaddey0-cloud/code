// Named parameters 
void user0({String? name, int? age}) {
  print("$name $age");
}

// Named parameters (required)
void user1({required String name, int age = 18}) {
  print("$name $age");
}
void user12({required String name, required int age}) {
  print("$name $age");
}

// Positional parameters
void user2(String name, [int age = 18]) {
  print("$name $age");
}

void user3(String name, int age) { print("$name $age"); }

void main() {
  user0();                // Allowed
  user0(name: "Kanad");   // Allowed

                          print("-------------");
  user1(name: "Kanad", age: 22);
  user1(age: 24, name: "Kanad");  // order does not mattter
  user1(name: "Kanad");
                          print("");
  user12(name: "Kanad", age: 22);
  user12(age: 24, name: "Kanad");  // order does not mattter

                          print("-------------");
  user2("Kanad", 22);
  user2("Kanad");

                          print("-------------");
  user3("Kanad", 22);
}




// void main() { 
//   int mark = 90;
//   // Dart ternary  ==  C++ ternary
//   // (condition ? trueValue : falseValue)
//   String grade = (mark >= 90)
//       ? "A"
//       : (mark >= 75)
//           ? "B"
//           : "C";
//   print(grade);

//   var add = (a, b) { // Lambda
//     print(a);
//     print(b);
//     return a + b;
//   };
//   Also Lambda with Arrow
//   int Function(int, int) add1 = (int a, int b) => a + b;
//   var add2 = (a, b) => a + b;
//   var add3 = (int a, int b) => a + b;
//   print("  ${add(0,1)}  ${add1(1,1)}  ${add2('1','2')}  ${add3(2,3)}");
// }




// void main() {
//   print(square(5));
//   print(add(10, 20));
//   greet("Kanad");
// }
// // Arrow/inline not a Lambda
// int square(int n) => n * n;
// int add(int a, int b) => a + b;
// void greet(String name) => print("Hello $name");

// // without =>
// // numbers.map((e) { return e * e; }).toList();

// // with =>
// // numbers.map((e) => e * e).toList();



      
// void main() {
//   List<int> numbers = [1, 2, 3, 4, 5, 6];

//   // map() -> Transform each element, return updated list
//   var square = numbers.map((e) => e * e).toList();
//   print("map()        : $square");

//   // where() -> Filter elements, return (if ture take else not) list elements
//   var even = numbers.where((e) => e.isEven).toList();
//   print("where()      : $even");
  
//   // reduce() -> include finding the sum, product, maximum, minimum, or combining a list into a single value.
//   int sum = numbers.reduce((previous, current) {
//     // print("$previous + $current");
//     return previous + current;
//   });
//   print("Sum          : $sum");

//   // any() -> At least one element satisfies the condition, return true/false
//   bool hasGreaterThan5 = numbers.any((e) => e > 5);
//   print("any()        : $hasGreaterThan5");

//   // every() -> All elements satisfy the condition, return true/false
//   bool allPositive = numbers.every((e) => e > 0);
//   print("every()      : $allPositive");

//   // firstWhere() -> First matching element index
//   int firstEven = numbers.firstWhere((e) => e.isEven);
//   print("firstWhere() : $firstEven");

//   // forEach() -> Perform an action on every element
//   print("\nforEach()");
//   numbers.forEach((e) => print(e));
// }
