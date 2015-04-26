/*
 * By Benjamin Richard Olson, Copyright 2012, All Rights Reserved
 * This program displays moving bubbles on the screen.
 * Each time the user does a mouse click within the program's frame,
 * a new moving bubble is added.
 * If the user clicks outside the box, the bubbles will move
 * towards the box and will then be contained inside of it.
 * Each bubble changes shape and color as it moves.
 * To limit CPU consuption, the number of bubbles is limited to 5.
 */

//package tests;

/**
 *
 * @author Benjamin R. Olson
 */
import java.awt.Color;
import java.awt.Point;
import java.awt.Dimension;
import java.awt.Graphics;
import javax.swing.*;
import java.awt.event.*;
import java.util.ArrayList;
import java.util.List;

public class Bubbles extends JPanel implements MouseListener {

    public Bubbles() { addMouseListener(this); }
    
    public void mouseClicked(MouseEvent e) {
		if (ovalList.size() < 5){
			addNewOval( e.getX(), e.getY() );
			System.out.println("mouse clicked");
		}
    }
    public void mousePressed (MouseEvent e){}
    public void mouseReleased(MouseEvent e){}
    public void mouseEntered (MouseEvent e){}
    public void mouseExited  (MouseEvent e){}
    
    public void addNewOval (int x, int y) {
        Oval ov = new Oval(x, y);
        threadList.add(new Thread(ov) );
        threadList.get(threadList.size()-1).start();
        ovalList.add(ov);
        System.out.println("threadList Thread #: " + 
                (threadList.size()-1));
    }
    
    public void paint(Graphics g) {
        g.clearRect(0, 0, 500, 500);
        g.setColor(Color.BLACK);
        g.fillRect(0, 0, 500, 500);
        for (int i = 0; i < ovalList.size(); i++) {
            Oval o = ovalList.get(i);
            g.setColor(Color.getHSBColor(
                             o.color / 256.0f, 1.0f, 1.0f));
            g.fillOval(o.getX(), o.getY(), o.getWidth(), o.getHeight());
        }
    }//end paint()
    
    /*public void update(Graphics g) {
        paint(g);
    }*/
    
    public static void main(String[] args) {
        JFrame f = new JFrame();
        Tests t = new Tests();
        f.add(t);
        f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        f.setMinimumSize(new Dimension(500, 500));
        f.setVisible(true);
        //f.setLocation(new Point(200, 50));
        
        while(true) { t.repaint(); }//repaint() calls paint()
 
    }//end main()

    //variables declaration
    List<Thread> threadList = new ArrayList<Thread>();
    List<Oval> ovalList = new ArrayList<Oval>(); 
    
}//end Tests{}

class Oval implements Runnable {
    /* Oval bounces within a 500x500pixel frame */
    /* Oval object will be initialized as 50 px wide and 100 px tall */
    public Oval (int x, int y) { xOval = x; yOval = y; }
    
    /* Contains logic determining how the shape changes with time */
    public void run() {
        while(true) {
            try {
                Thread.sleep(15);
            }catch (InterruptedException e) { e.printStackTrace(); }
            
            /* how the oval moves within the frame */
            if (xOval == 0) { goRight = true; }
            if (xOval + width >= 500){ goRight = false; }
            if (goRight == true) { xOval++; } else { xOval--; }
            
            if (yOval == 0) { goDown = true; }
            if (yOval + height >= 500){ goDown = false; }
            if (goDown == true) { yOval++; }  else { yOval--; }
            
            /* how the oval changes shape as it moves */
            if(width == 50) {wider = true; }
            if(width == 100){wider = false;}
            if(height == 100){shorter = true; }
            if(height == 50) {shorter = false;}
            if(wider == true)  {width++; } else { width--; }
            if(shorter == true){height--;} else { height++;}
            
            if(color < 257) {color++;} else {color = 0.0f;}
        }
    }//end run()
    
    //variables declaration
    public float color = 0.0f;
    boolean goRight = true, goDown = true, wider = true, shorter = true;
    private int xOval = 0, yOval = 0;
    private int width = 50, height = 100;
	
	//getter and setter methods
    public int getX () { return xOval; }
    public int getY () { return yOval; }
    public int getWidth() { return width; }
    public int getHeight(){ return height; }
    public void setOval (int x, int y) { xOval = x; yOval = y; }
    
}//end Oval{}