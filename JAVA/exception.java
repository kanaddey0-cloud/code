// Object
//  └── Throwable
//       ├── Error
//       └── Exception
//            ├── IOException
//            ├── SQLException
//            └── RuntimeException
//                 ├── ArithmeticException
//                 ├── NullPointerException
//                 └── ArrayIndexOutOfBoundsException


// public class Main {
//     public static void main(String[] args) {
//         try {
//             int result = 10 / 0; // ArithmeticException
//             System.out.println(result);
//         } catch (ArithmeticException e) {
//             System.out.println("Cannot divide by zero!");
//         } finally {
//             System.out.println("Always executed");
//         }
//     }
// }


// // 1. throw (used inside method)
// //     👉 Used to actually throw an exception object
// public class Main {
//     static void checkAge(int age) {
//         if (age < 18) {
//             throw new ArithmeticException("Not eligible to vote");
//         }
//         System.out.println("Welcome");
//     }

//     public static void main(String[] args) {
//         checkAge(15);
//     }
// }


// // throws (used in method signature)
// //     👉 Used to declare an exception that a method might throw
// public class Main {

//     static void showElement() throws ArrayIndexOutOfBoundsException {
//         int arr[] = {10, 20, 30};
//         System.out.println(arr[5]);  // ERROR Wrong index (valid: 0 to 2)
//     }

//     public static void main(String[] args) {
//         try {
//             showElement();
//         } catch (ArrayIndexOutOfBoundsException e) {
//             System.out.println("Array index is out of bound!");
//         }
//     }
// }


// // custom exception
// class MyException extends Exception {
//     MyException(String message) {
//         super(message);
//         System.out.println("own sms error");
//     }
// }

// public class Main {

//     static void checkAge(int age) throws MyException {
//         if (age < 18) {
//             throw new MyException("Age must be 18 or above");
//         } else {
//             System.out.println("Valid Age");
//         }
//     }

//     public static void main(String[] args) {
//         try {
//             checkAge(15);
//         } catch (MyException e) {
//             System.out.println("Caught: " + e.getMessage());
//         }
//     }
// }


// class Main {
//     static void test() throws Exception {
//         try {
//             int x = 10 / 0;
//         } catch (Exception e) {
//             System.out.println("Caught inside test() "+e.getMessage());
//             throw e;    // Rethrow
//         }
//     }

//     public static void main(String[] args) {
//         try {
//             test();
//         } catch (Exception e) {
//             System.out.println("Caught in main() "+e.getMessage());
//         }
//     }
// }
