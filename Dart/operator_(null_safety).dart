// NULL SAFETY
// void main() {
//   String? name;

//   // ??  -> (Null-coalescing) Return right value if left is null
//   print(name ?? "Guest");      // Guest

//   name = "Kanad";
//   print(name ?? "Guest");      // Kanad

//   print("----------------");

//   String? city;

//   // ??= -> (Null-aware Assignment) Assign a Value only if variable is null
//   city ??= "Kolkata";
//   print(city);                 // Kolkata

//   city ??= "Delhi";            // Won't change
//   print(city);                 // Kolkata

//   print("----------------");

//   // ?. -> (Null-aware access) When accessing a member that may be null.
//   String? language;

//   print(language?.length);       // null

//   language = "Dart";
//   print(language?.length);       // 4

//   print("----------------");

//   // ! -> (Null assertion) When you are sure a nullable variable is not null.
//   String? country = "India";

//   print(country!.length);        // 5

//   // country = null;
//   // print(country!.length);     // Runtime Error
// }


class Student {
  String name = "";
  int age = 0;

  void printInfo() {
    print("Name: $name, Age: $age");
  }
}

void main() {

  // ~/ -> Integer(floor) Division
  print("7 / 2  = ${7 / 2}");
  print("7 ~/ 2 = ${7 ~/ 2}");

  print("----------------");

  // is, is!, as
  Object obj = "Kanad";

  print(obj is String);     // true
  print(obj is! int);       // true

  String text = obj as String;
  print(text);

  print("----------------");

  // ... -> Spread Operator
  List<int> list1 = [1, 2, 3];
  List<int> list2 = [...list1, 4, 5];

  print(list2);

  print("----------------");

  // ...? -> Null-aware Spread
  List<int>? numbers = null;

  List<int> result = [10, ...?numbers, 20];
  print(result);

  numbers = [30, 40];

  result = [10, ...?numbers, 20];
  print(result);

  print("----------------");

  // .. -> Cascade operator always refers to the same object that was created or referenced immediately before it.
  Student student = Student()
    ..name = "Kanad"
    ..age = 24
    ..printInfo();
}
