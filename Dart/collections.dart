// | Feature          | List            | Set           | Map                |
// | ---------------- | --------------- | ------------- | ------------------ |
// | Stores           | Values          | Unique Values | Key → Value        |
// | Duplicate Values | ✅ Yes         | ❌ No         | Keys ❌, Values ✅   |
// | Access           | By **Index**    | No Index      | By **Key**         |
// | Example          | `["A","B","A"]` | `{"A","B"}`   | `{"name":"Kanad"}` |


void main() {

  //=========================
  // List
  // Ordered collection
  // Duplicate values allowed
  // Access by index
  //=========================

  List<String> list = [
    "Apple",
    "Banana",
    "Apple",   // Duplicate allowed
  ];
  print("List    : $list");
  print("Index 0 : ${list[0]}");
  print("Index 1 : ${list[1]}");

  List<dynamic> data = [
    10,
    3.14,
    "Kanad",
    true,
    [1, 2, 3],
    {"name": "Kanad"},
  ];
  print(data);

  List<List<int>> jagged = [
    [1, 2],
    [3, 4, 5],
    [6],
    [7, 8, 9, 10],
  ];
  print(jagged);

  print("--------------------------");

  //=========================
  // Set
  // Unique values only
  // No index access
  //=========================

  Set<String> set = {
    "Apple",
    "Banana",
    "Apple",   // Duplicate ignored
  };
  print("Set   : $set");

  Set<Set<int>> not_jagged_set = {
    {1, 2},
    {3, 4, 5},
    {6},
  };
  print("Set   : $not_jagged_set");
  // However, this is not called a jagged array because:
  //   A Set has no indexes.
  //   A Set is about uniqueness, not rows and columns.
  //   The term jagged array specifically refers to arrays/lists with rows of different lengths.

  print("--------------------------");

  //=========================
  // Map
  // Key -> Value pairs
  // Access by key
  // Keys must be unique
  //=========================

  Map<String, dynamic> map = {
    "name": "Kanad",
    "age": 24,
    "city": "Kolkata",
  };

  print("Map   : $map");
  print("Name  : ${map["name"]}");
  print("Age   : ${map["age"]}");
}




// void main() {
//   List<int> numbers = [30, 10, 20];

//   //=========================
//   // Basic Properties
//   //=========================

//   print(numbers);                 // [30,10,20]
//   print(numbers.length);          // 3
//   print(numbers.isEmpty);         // false
//   print(numbers.isNotEmpty);      // true
//   print(numbers.first);           // 30
//   print(numbers.last);            // 20
//   print(numbers[1]);              // 10

//   print("----------------");

//   //=========================
//   // Add Elements
//   //=========================

//   numbers.add(40);
//   numbers.addAll([50, 60]);
//   print(numbers);

//   print("----------------");

//   //=========================
//   // Insert Elements At Position
//   //=========================

//   numbers.insert(1, 15);
//   numbers.insertAll(2, [16, 17]);
//   print(numbers);

//   print("----------------");

//   //=========================
//   // Remove Elements
//   //=========================

//   numbers.remove(30);         // remove value
//   numbers.removeAt(0);        // remove index
//   numbers.removeLast();
//   print(numbers);

//   print("----------------");

//   //=========================
//   // Search
//   //=========================

//   print(numbers.contains(40));
//   print(numbers.indexOf(40));
//   print(numbers.indexOf(999));

//   print("----------------");

//   //=========================
//   // Sort & Reverse
//   //=========================

//   numbers.sort();
//   print(numbers);
//   print(numbers.reversed);
//   print(numbers.reversed.toList());

//   print("----------------");

//   //=========================
//   // Sub List
//   //=========================

//   print(numbers.sublist(1));    // Starts from index 1 and goes to the end
//   print(numbers.sublist(1, 3)); // Starts from index 1 and stops before index 3

//   print("----------------");

//   //=========================
//   // Loop
//   //=========================

//   for (var n in numbers) {
//     print(n);
//   }

//   print("----------------");

//   //=========================
//   // map()
//   //=========================

//   List<int> square =
//       numbers.map((e) => e * e).toList();
//   print(square);

//   print("----------------");

//   //=========================
//   // where()
//   //=========================

//   List<int> even =
//       numbers.where((e) => e % 2 == 0).toList();
//   print(even);

//   print("----------------");

//   //=========================
//   // forEach()
//   //=========================

//   numbers.forEach((e) {
//     print(e);
//   });

//   print("----------------");

//   //=========================
//   // join()
//   //=========================

//   print(numbers.join(", "));

//   print("----------------");

//   //=========================
//   // clear()
//   //=========================

//   numbers.clear();
//   print(numbers);
//   print(numbers.isEmpty);
// }




// void main() {
//   Set<int> numbers = {30, 10, 20};

//   //=========================
//   // Basic Properties
//   //=========================

//   print(numbers);               // {30,10,20}
//   print(numbers.length);        // 3
//   print(numbers.isEmpty);       // false
//   print(numbers.isNotEmpty);    // true

//   print("----------------");

//   //=========================
//   // Add Elements
//   //=========================

//   numbers.add(40);
//   numbers.addAll({50, 60});

//   print(numbers);

//   print("----------------");

//   //=========================
//   // Duplicate Values
//   //=========================

//   numbers.add(40);              // Ignored
//   numbers.add(10);              // Ignored

//   print(numbers);

//   print("----------------");

//   //=========================
//   // Remove Elements
//   //=========================

//   numbers.remove(30);

//   print(numbers);

//   print("----------------");

//   //=========================
//   // Search
//   //=========================

//   print(numbers.contains(40));
//   print(numbers.contains(100));

//   print("----------------");

//   //=========================
//   // Convert to List
//   //=========================

//   List<int> list = numbers.toList();

//   print(list);
//   print(list[0]);               // Now indexing is possible

//   print("----------------");

//   //=========================
//   // Union
//   //=========================

//   Set<int> other = {40, 50, 70};

//   print(numbers.union(other));

//   print("----------------");

//   //=========================
//   // Intersection
//   //=========================

//   print(numbers.intersection(other));

//   print("----------------");

//   //=========================
//   // Difference
//   //=========================

//   print(numbers.difference(other));

//   print("----------------");

//   //=========================
//   // lookup()
//   //=========================

//   print(numbers.lookup(40));    // 40
//   print(numbers.lookup(999));   // null

//   print("----------------");

//   //=========================
//   // Loop
//   //=========================

//   for (var value in numbers) {
//     print(value);
//   }

//   print("----------------");

//   //=========================
//   // forEach()
//   //=========================

//   numbers.forEach((value) {
//     print(value);
//   });

//   print("----------------");

//   //=========================
//   // clear()
//   //=========================

//   numbers.clear();

//   print(numbers);
//   print(numbers.isEmpty);
// }




// void main() {
//   Map<String, dynamic> student = {
//     "name": "Kanad",
//     "age": 24,
//     "city": "Kolkata",
//   };

//   //=========================
//   // Basic Properties
//   //=========================

//   print(student);
//   print(student.length);
//   print(student.isEmpty);
//   print(student.isNotEmpty);
//   print(student["name"]);

//   print("----------------");

//   //=========================
//   // Add & Update
//   //=========================

//   student["cgpa"] = 8.56;      // Add
//   student["age"] = 25;         // Update
//   print(student);

//   print("----------------");

//   //=========================
//   // putIfAbsent()
//   //=========================

//   student.putIfAbsent("country", () => "India");
//   student.putIfAbsent("name", () => "Unknown"); // Won't change
//   print(student);

//   print("----------------");

//   //=========================
//   // update()
//   //=========================

//   student.update("age", (value) => value + 1);
//   print(student);

//   print("----------------");

//   //=========================
//   // Search
//   //=========================

//   print(student.containsKey("city"));
//   print(student.containsKey("phone"));
//   print(student.containsValue("India"));
//   print(student.containsValue("Delhi"));

//   print("----------------");

//   //=========================
//   // Keys, Values, Entries
//   //=========================

//   print(student.keys);
//   print(student.values);
//   print(student.entries);

//   print("----------------");

//   //=========================
//   // forEach()
//   //=========================

//   student.forEach((key, value) {
//     print("$key : $value");
//   });

//   print("----------------");

//   //=========================
//   // Loop using entries
//   //=========================

//   for (var entry in student.entries) {
//     print("${entry.key} -> ${entry.value}");
//   }

//   print("----------------");

//   //=========================
//   // Remove
//   //=========================

//   student.remove("city");
//   print(student);

//   print("----------------");

//   //=========================
//   // addAll()
//   //=========================

//   student.addAll({
//     "email": "kanad@gmail.com",
//     "phone": "9876543210",
//   });

//   print(student);

//   print("----------------");

//   //=========================
//   // clear()
//   //=========================

//   student.clear();
//   print(student);
//   print(student.isEmpty);
// }
