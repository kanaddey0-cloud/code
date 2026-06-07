abstract class Animal {
    abstract void sound();   // abstract method

    void eat() {             // normal method
        System.out.println("Animal is eating");
    }
}

class Dog extends Animal {
    void sound() {
        System.out.println("Dog barks");
    }
}

public class abstruct {
    public static void main(String[] args) {
        Dog d = new Dog();

        d.sound();
        d.eat();
    }
}


// abstract class Calculator {
//     abstract int add(int a, int b); // parameter + return type
// }

// class MyCalculator extends Calculator {
//     int add(int a, int b) {
//         return a + b;
//     }
// }

// class MyCalculator2 extends Calculator {
//     int add(int a, int b) {
//         System.out.println("->"+(a+b));
//         return 10;
//     }
// }

// public class mew {
//     public static void main(String[] args) {
//         MyCalculator c = new MyCalculator();
//         MyCalculator2 c2 = new MyCalculator2();

//         int result = c2.add(10, 20);

//         result = c.add(10, 20);
//         System.out.println(result);
//     }
// }