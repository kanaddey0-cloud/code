import java.lang.Thread;

// public class ThreadDemo {
//     public static void main(String[] argv) throws InterruptedException {
//         Thread T1 =new Thread(()->{
//             for(int i=1; i<=4; i++)  System.out.println("T1 = " + i); 
//         });
//         Thread T2 = new Thread(()->{
//             for(int i=1; i<=4; i++)  System.out.println("T2 = " + i); 
//         });
//         T1.start(); T2.start();
//         Runnable r = () -> { for(int i=1; i<=4; i++) System.out.println("R = " + i); };  r.run();
//         Runnable r1 = () -> {
//             for(int i=1; i<=4; i++)  System.out.println("R1 = " + i); 
//         };
//         Runnable r2 = () -> {
//             for(int i=1; i<=4; i++)  System.out.println("R2 = " + i); 
//         };
//         Thread t3 = new Thread(r1);   t3.start();
//         t3 = new Thread(r2);   t3.start();
//     }
// }


// In Java, an abstract method cannot be declared with the synchronized modifier.
// The reason: synchronized applies to the implementation of a method (to control thread access).
// but abstract methods have no body. Since there is no implementation, synchronization cannot be applied.

// // Synchronized Method: 
// class Counter {
//     static int count = 0;
//     public synchronized void increment() {
//         count++;
//     }
// }

// // Synchronized Block: 
// class Counter {
//     static int count = 0;
//     public void increment() {
//         synchronized(this) {
//             count++;
//         }
//     }
// }




class MyThread extends Thread {
    public MyThread(String name) { setName(name); }

    @Override
    public void run() {

        System.out.println("Current Thread : " + Thread.currentThread().getName() + "\n");

        for (int i = 1; i <= 3; i++) {
            System.out.println(getName() + " Priority = " + getPriority() + " Count = " + i);

            Thread.yield();  // Hints the scheduler that this thread is willing to give up the CPU.
                             // Another ready thread may run, but it is not guaranteed.
            try {
                Thread.sleep(1000);  System.out.println("\n" + getName() + " slepping... 10sec");
            } catch (InterruptedException e) {
                System.out.println("\n" + getName() + " Interrupted!");
                return;
            }
        }
    }
}

public class ThreadFunction {

    public static void main(String[] args) throws InterruptedException {
        System.out.println("Main Thread : " + Thread.currentThread().getName() + "\n");

        MyThread T1 = new MyThread("T1");
        MyThread T2 = new MyThread("T2");

        T1.setPriority(Thread.MAX_PRIORITY);  // 10
                    // Thread.NORM_PRIORITY      5
        T2.setPriority(Thread.MIN_PRIORITY);  // 1   

        T2.setDaemon(true);  // Marks the thread as a background service thread.
        // JVM exits when only daemon threads remain. all user threads complete their execution.

        System.out.println("Name      : " + T1.getName());
        System.out.println("Priority  : " + T1.getPriority() + "\n");

        System.out.println("Name      : " + T2.getName());
        System.out.println("Priority  : " + T2.getPriority());
        System.out.println("Daemon    : " + T2.isDaemon() + "\n");

        T1.start();
        T2.start();

        System.out.println("T1 Alive? " + T1.isAlive() + "\n");  // Returns true if the thread is still running.

        System.out.println("\nMain slepping...\n");
        Thread.sleep(1000);  // Pauses the current thread for a given time (mili_sec).
        T2.interrupt();      // Interrupts a sleeping or waiting thread.
        
        Thread.sleep(2000); T1.interrupt();

        T1.join();  // Current thread waits until T1 finishes.

        System.out.println("\nT1 State : " + T1.getState());  // returns the current state of a Java thread { NEW RUNNABLE BLOCKED WAITING TIMED_WAITING TERMINATED }
        System.out.println("T2 State : " + T2.getState());
        System.out.println("\nProgram Finished");
    }
}




// class MyTask implements Runnable {
//     @Override
//     public void run() {
//         System.out.println(
//             Thread.currentThread().getName()
//             + " is running");
//     }
// }

// public class ThreadConstructors {

//     public static void main(String[] args)
//             throws InterruptedException {

//         Runnable task = new MyTask();

//         ThreadGroup group = new ThreadGroup("MyGroup");

//         // Thread()
//         Thread t1 = new Thread();  // defualt name t1

//         // Thread(String name)
//         Thread t2 = new Thread("T2");

//         // Thread(Runnable target)
//         Thread t3 = new Thread(task);  // defualt name t3

//         // Thread(Runnable target, String name)
//         Thread t4 = new Thread(task, "T4");

//         // Thread(ThreadGroup group, Runnable target)
//         Thread t5 = new Thread(group, task);  // defualt name t5

//         // Thread(ThreadGroup group, String name)
//         Thread t6 = new Thread(group, "T6");

//         // Thread(ThreadGroup group, Runnable target, String name)
//         Thread t7 = new Thread(group, task, "T7");

//         // Thread(ThreadGroup group, Runnable target, String name, long stackSize)
//         Thread t8 = new Thread(group, task, "T8", 1000);

//         t1.start();
//         t2.start();
//         t3.start();
//         t4.start();
//         t5.start();
//         t6.start();
//         t7.start();
//         t8.start();

//         // activeCount()
//         System.out.println("\nActive Threads : " + Thread.activeCount());

//         // getThreadGroup()
//         ThreadGroup tg = t7.getThreadGroup();
//         if (tg != null) {
//             System.out.println("T7 Group : " + tg.getName());
//         } else {
//             System.out.println("T7 Group is NULL");
//         }

//         // t7.checkAccess();  removed (deprecated)
//         System.out.println("Access check skipped (deprecated API)");

//         t3.join();
//         t4.join();
//         t5.join();
//         t7.join();
//         t8.join();

//         System.out.println("\nProgram Finished");
//     }
// }
