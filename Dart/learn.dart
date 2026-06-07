// // Named parameters
// void user1({required String name, int age = 18}) {
//   print("$name $age");
// }
// // Positional parameters
// void user2(String name, [int age = 18]) {
//   print("$name $age");
// }

// void user3(String name, int age) {
//   print("$name $age");
// }

// void main() {
//   user1(name: "Kanad", age: 22);
//   user1(age: 24, name: "Kanad");  // order does not mattter
//   user1(name: "Kanad");
//                           print("-------------");
//   user2("Kanad", 22);
//   user2("Kanad");
//                           print("-------------");
//   user3("Kanad", 22);
// }

void main() {
  int? x;
  print(x);

  var y;
  y = 10;         print(y);
  y = "Kanad";    print(y);
  y = true;       print(y);

  var w = 10;     print(w);
                              print("-------------");
  dynamic z = 10; print(z);
  z = "Kanad";    print(z);
  z = true;       print(z);
}

