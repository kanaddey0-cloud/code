// // Generics: Write one class or function that works with different data types safely.
// class Pair<K, V> {
//   K key;  V value;

//   Pair(this.key, this.value);
//   void show() => print("$key : $value");
// }

// void display<K, V>(K key, V value) => print("$key -> $value");

// void main() {
//   Pair<String, int> student = Pair("Kanad", 24);
//   student.show();

//   display<String, bool>("Flutter", true);
// }


//-----------------------------------------------------------------------

// Exception
// try
//  ├── on ... { }
//  ├── on ... catch(e) { }
//  ├── on ... catch(e, s) { }
//  ├── catch(e) { }          // Optional, only one general catch
//  └── finally { }           // Optional, only one


// void main() {
//   try {
//     // print(10 ~/ 0);                  // Implicitly throws IntegerDivisionByZeroException
//     // throw Exception("Manual Error"); // Explicitly throws an Exception object
//     throw "ERROR";                      // Explicitly throws a String (or any object/value)
//   }
//   on IntegerDivisionByZeroException { print("Divide By Zero"); } // Handle a specific exception
//   on Exception catch (e) { print("General Exception: $e"); }     // If you need Exception object too
//   catch (e, s) { print("Unknown Error: $e \n$s"); }              // Handle anything not caught above
//   finally { print("Program Finished."); }  // Always executes
// }


// void c() { throw Exception("Error"); }
// void b() { c(); }
// void a() { b(); }

// void main() {
//   try {
//     a();
//   } catch (e, s) {
//     print(e);
//     print(s); // Stack Trace
//   }
// }


//-----------------------------------------------------------------------

// // Extension: Add new methods/properties to an existing class without modifying or inheriting it.
// extension English on String { String greet() => "Hello $this"; }
// extension French on String { String greet() => "Bonjour $this"; }

// void main() {
//   // print("Kanad".greet()); // when single extention
//   print(English("Kanad").greet());
//   print(French("Kanad").greet());
// }


//-----------------------------------------------------------------------

// Arithmetic :   +    -    *   /    %   ~/
// Unary      :   -    ~
// Comparison :   ==   <    >   <=   >=
// Bitwise    :   &    |    ^   <<   >>   >>>
// Index      :   []   []=

// class Point {
//   int x, y;

//   Point(this.x, this.y);

//   Point operator +(Point other) {
//     return Point(x + other.x, y + other.y);
//   }
// }

// void main() {
//   Point p1 = Point(2, 3);
//   Point p2 = Point(4, 5);

//   Point p3 = p1 + p2;

//   print("${p3.x}, ${p3.y}");
// }

/*
// Arithmetic
ReturnType operator +(Type other)  { ... }
ReturnType operator -(Type other)  { ... }
ReturnType operator *(Type other)  { ... }
ReturnType operator /(Type other)  { ... }
ReturnType operator %(Type other)  { ... }
ReturnType operator ~/(Type other) { ... }

// Unary
ReturnType operator -() { ... }
ReturnType operator ~() { ... }

// Comparison
bool operator ==(Object other) { ... }
bool operator <(Type other)  { ... }
bool operator >(Type other)  { ... }
bool operator <=(Type other) { ... }
bool operator >=(Type other) { ... }

// Bitwise
ReturnType operator &(Type other)   { ... }
ReturnType operator |(Type other)   { ... }
ReturnType operator ^(Type other)   { ... }
ReturnType operator <<(int shift)   { ... }
ReturnType operator >>(int shift)   { ... }
ReturnType operator >>>(int shift)  { ... }

// Index
ReturnType operator [](int index) { ... }
void operator []=(int index, ValueType value) { ... }
*/


//-----------------------------------------------------------------------
