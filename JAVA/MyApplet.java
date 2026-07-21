// Browser Loads Applet → init() → start() → paint() → stop() → destroy()
    
import java.applet.Applet.*;
import java.awt.*;
import java.awt.event.*; 




// Demonstrates Applet Life Cycle
// init() → start() → paint() → stop() → destroy()
// Also shows TextField creation and basic GUI initialization.

public class MyApplet extends Applet {

    TextField txt;

    public void init() {
        // Initialize components
        txt = new TextField(20);
        add(txt);
        txt.setText("Applet Loaded");
    }

    public void start() {
        // Runs whenever applet becomes active
        txt.setText("Applet Started");
    }

    public void paint(Graphics g) {
        // Display output
        g.drawString("Welcome to Java Applet", 50, 80);
    }

    public void stop() {
        // Runs when applet becomes inactive
        txt.setText("Applet Stopped");
    }

    public void destroy() {
        // Cleanup resources
        txt = null;
        System.out.println("Applet Destroyed");
    }
}


//--------------------------------------------------------------------

// Demonstrates simple arithmetic operation in Applet
// Calculates sum of two numbers and displays result using drawString().

// public class Math extends Applet {
// 	public void paint(Graphics g) {
// 		int x,y,z;
// 		String s;
// 		x=20;
// 		y=30;
// 		z=x+y;
// 		s="Sum = " + String.valueOf(z);
// 		g.drawString(s,100,100);
// 	}
// }


//--------------------------------------------------------------------

// Demonstrates Graphics class drawing methods
// drawLine(), drawRect(), drawOval(), fillOval(), setColor().

// public class LineRect extends Applet {
// 	public void paint(Graphics g) {
// 		g.drawLine(10,10,50,50);
// 		g.drawRect(10,60,40,30);
// 		g.drawOval(120,120,200,120);
// 		g.setColor(Color.green);
// 		g.fillOval(170,130,100,100);
// 	}
// }


//--------------------------------------------------------------------

// Demonstrates computer graphics using Applet
// Draws a human face using ovals, arcs, and filled shapes.

// public class MyFace extends Applet {
// 	public void paint(Graphics g) {
// 		g.drawOval(40,40,120,150); //Head
// 		g.drawOval(57,75,30,20);   //Left Eye
// 		g.drawOval(110,75,30,20);  //Right Eye
// 		g.fillOval(68,81,10,10);   //Pupil(Left)
// 		g.fillOval(121,81,10,10);  //Pupil(Right)
// 		g.drawOval(85,100,30,30);  //Nose 
// 		g.fillArc(60,125,80,40,180,180); //Mouth
// 		g.drawOval(25,92,15,30);   //Left Ear
// 		g.drawOval(160,92,15,30);  //Right Ear
// 	}
// }


//--------------------------------------------------------------------

// Demonstrates Event Handling in Applet
// Uses Button, TextField, ActionListener, and actionPerformed().
// Clicking the button changes the TextField content.

// public class EventApplet extends Applet implements ActionListener {  
//     Button b;  
//     TextField tf;  
      
//     public void init() {  
//         tf=new TextField();  
//         tf.setBounds(30,40,150,20);  
        
//         b=new Button("Click Me");  
//         b.setBounds(80,150,60,50);  
        
//         add(b);
//         add(tf);  
//         b.addActionListener(this);  
        
//         setLayout(null);  
//     }  
      
//      public void actionPerformed(ActionEvent e) {  
//         tf.setText("Welcome");  
//     }   
// }  


//--------------------------------------------------------------------

// Demonstrates User Input Handling in Applet
// Reads values from TextFields, converts String to int,
// performs addition, and displays the result.

// public class UserIn extends Applet {
// 	TextField t1,t2;
	
// 	public void init() {
// 		t1 = new TextField(8);
// 		t2 = new TextField(8);
// 		add(t1);
// 		add(t2);
// 		t1.setText("0");
// 		t2.setText("0");
// 	}
	
// 	public void paint(Graphics g) {
// 		int x,y,z;
// 		String s1,s2,s;
// 		x=y=z=0;
// 		g.drawString("Enter value of each Text Box AND PRESS ENTER.",10,50);
		
//         try {
// 			s1 = t1.getText();
// 			x=Integer.parseInt(s1);
// 			s2 = t2.getText();
// 			y = Integer.parseInt(s2);
// 		} catch(Exception e) {}
		
// 		z=x+y;
// 		s = String.valueOf(z);
// 		g.drawString("THE SUM IS",10,75);
// 		g.drawString(s,100,75);
// 	}
	
// 	public boolean action(Event ev,Object o) {
// 		repaint();
// 		return true;
// 	}
// }