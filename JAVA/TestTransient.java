// File Handling / I/O
//         |
//         ├── File class
//         ├── FileReader / FileWriter
//         ├── BufferedReader / BufferedWriter (BufferedWriter is just efficient then FileWriter)
//         ├── InputStream / OutputStream    // byte by byte read & write
//         |
//         └── Object Serialization
//               |
//               ├── Serialization
//               └── Deserialization

// Student s1 = new Student(); 
 
// // Serialization 
// FileOutputStream fos = new FileOutputStream("student.txt"); 
// ObjectOutputStream oos = new ObjectOutputStream(fos); 
// oos.writeObject(s1); 
// oos.close(); 

// // Deserialization 
// FileInputStream fis = new FileInputStream("student.txt"); 
// ObjectInputStream ois = new ObjectInputStream(fis); 

// Student s2 = (Student) ois.readObject(); 
//---------------------------------------------------------------------------------------

// import java.io.*;
// import java.io.File;
// import java.io.FileWriter;
// import java.io.FileReader;
// import java.io.BufferedReader;
// import java.io.IOException;
// import java.nio.file.Files;
// import java.nio.file.Path;
// import java.nio.file.StandardCopyOption;

// class file {
//     public static void main(String[] args) throws Exception {

//         // Create file
//         File file = new File("data.txt");

//         if(file.createNewFile())
//             System.out.println("File created");
//         else
//             System.out.println("Already exists");


//         // Write to file
//         FileWriter fw = new FileWriter(file);
//         fw.write("Hello Java\n");
//         fw.write("File Handling");
//         fw.close();


//         // Append data
//         FileWriter append = new FileWriter(file, true);

//         append.write("\nNew Line Added");
//         append.close();


//         // Read file
//         FileReader fr = new FileReader(file);
//         int ch;

//         while((ch = fr.read()) != -1) {
//             System.out.print((char)ch);
//         }

//         fr.close();


//         // Read file line by line
//         BufferedReader br = new BufferedReader(new FileReader(file));

//         String line;

//         while((line = br.readLine()) != null) {
//             System.out.println(line);
//         }

//         br.close();


//         // Copy file
//         Files.copy(
//             Path.of("data.txt"),
//             Path.of("copy.txt"),
//             StandardCopyOption.REPLACE_EXISTING 
//         );      // if not then do not replace the exiting file and ERROR


// System.out.println("----------------------");
//         // File information
//         System.out.println(file.getName());         // file name
//         System.out.println(file.getAbsolutePath()); // full path
//         System.out.println(file.getPath());         // path given while creating
//         System.out.println(file.length());          // size in bytes
//         System.out.println(file.exists());          // checks file exists or not
//         System.out.println(file.isFile());          // true if it is a file
//         System.out.println(file.isDirectory());     // true if it is a folder
//         System.out.println(file.canRead());         // read permission
//         System.out.println(file.canWrite());        // write permission
//         System.out.println(file.canExecute());      // execute permission
//         System.out.println(file.lastModified());    // last modified time (milliseconds)
// System.out.println("----------------------");        


//         // Delete file
//         if(file.delete()) {
//             System.out.println("File Deleted");
//         }

//         // new File("copy.txt").delete();
//     }
// }




import java.io.*;

class Student implements Serializable {
    String name;
    transient int age; // will not be saved

    Student(String name, int age) {
        this.name = name;
        this.age = age;
    }
}

public class TestTransient {
    public static void main(String[] args) throws Exception {
        Student s1 = new Student("Kanad", 22);

        // Serialize
        ObjectOutputStream out = new ObjectOutputStream(new FileOutputStream("student.txt"));
        out.writeObject(s1);
        out.close();

        // Deserialize
        ObjectInputStream in = new ObjectInputStream(new FileInputStream("student.txt"));
        Student s2 = (Student) in.readObject();
        in.close();

        System.out.println(s2.name); // Output: Kanad
        System.out.println(s2.age);  // Output: 0 (default, because transient)
    }
}
