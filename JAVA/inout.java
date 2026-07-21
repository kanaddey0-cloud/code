
import java.util.Scanner;

public class inout {
    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);

        System.out.print("Enter inputs:\n");
        int a = sc.nextInt();
        long d = sc.nextLong();
        float b = sc.nextFloat();
        double c = sc.nextDouble();
        boolean e = sc.nextBoolean();
// 10
// 100000
// 5.5
// 99.99
// true
// Hello
// I am learning Java
// s

        System.out.print("Enter word (String): ");
        String s1 = sc.next();

        sc.nextLine(); // clear buffer (important)

        System.out.print("Enter full line (String): ");
        String s2 = sc.nextLine();

        System.out.print("Enter char: ");
        char ch = sc.next().charAt(0);

        System.out.println("\nOUTPUT:");
        System.out.println(a);
        System.out.println(d);
        System.out.println(b);
        System.out.println(c);
        System.out.println(e);
        System.out.println(s1);
        System.out.println(s2);
        System.out.println(ch);
    }
}




// public class inout {
//     public static void main(String[] args) {

//         int[] arr = {10,20,30};

//         int[][] arr2 = new int[2][];
//         arr2[0] = new int[]{10,20};
//         arr2[1] = new int[]{10,20,30,40};
        
//         int[] arr1 = new int[5];
        
//         int[][] arr3 = new int[2][];
//         arr3[0] = new int[2];
//         arr3[1] = new int[4];
//         // arr3
//         // +-- arr3[0] -> [0][0]
//         // +-- arr3[1] -> [0][0][0][0]

//         int[] arr4 = {++a, ++a, ++a}; 
//         System.out.println(arr4[0]);

//         int[] arr5 = new int[10]; 
//         arr5[0] = ++a;
//         System.out.println(arr5[0]); 
//     }   
// }
