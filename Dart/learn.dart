// class Student {
//   final String name = getName();   // ❌ Error

//   String getName() {
//     print("Creating...");
//     return "Kanad";
//   }
// }

// class Student {
//   final String name = Student.getName();

//   static String getName() {
//     print("Creating...");
//     return "Kanad";
//   }
// }

// class Student {
//   final String name;

//   Student() : name = getName();

//   static String getName() {
//     print("Creating...");
//     return "Kanad";
//   }
// }

class Student {
  late final String name = getName();

  String getName() {
    print("Creating...");
    return "Kanad";
  }
}

void main() {
  Student s = Student();

  print("Object Created");

  print(s.name);
}