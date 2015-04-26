/*Written by Bejamin R. Olson
* Copyright 2012, All Rights Reserved
*/

package simplereading2;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.util.*;
import java.util.HashMap;
import java.util.ArrayList;

/**
 *
 * @author Benjamin R. Olson
 * CategoryObj{} is used in main class SimpleReading2{}
 */
public class CategoryObj {

    
    /**updates ArrayList<String> folderList and
     *user's JComboBox<String> menu
     *called by main method
     */
    public void loadCategories(){
        String[] list = getDirPathsList();
        System.out.println("From loadCategories: " + list.length);
        for(int i = 0; i < list.length; i++){
            System.out.println("In loadCategories, checking this folder: " + list[i]);
            if(folderExists(list[i]) && folderContainsPictures(list[i])){
                    folderList.add(list[i]);
                    menu.addItem(list[i]);
            }/*else{
                if(!folderList.isEmpty()){
                    System.out.println("folderList not empty");
                    if(!folderList.contains(list[i])){
                        folderList.remove(list[i]);
                        menu.removeItem(list[i]);
                    }
                }
                System.out.println("Folder: " + list[i] + "deleted from menu.");
                JOptionPane.showMessageDialog(
                    null, "Folder: " + list[i] + " deleted from menu, \n" +
                        "because it has been deleted or moved."
                );
            }*/
        }
    }//end method loadCategories()
    
    /**calls showLesson based on the category folder (absolute path)
     *passed as the parameter and
     *this method is called by main method
     */
    public void chooseCategoryAndShowLesson(String folderName){
        if(folderContainsPictures(folderName)){
            if(!folderIsInList(folderName)){
                folderList.add(folderName);
                menu.addItem(folderName);
            }
            showLesson(folderName);
        }else{
            System.out.println("User tried to load a folder without pictures.");
            JOptionPane.showMessageDialog(
                    null, "This folder contains no usable pictures."
            );
        }
    }//end method chooseCategoryAndShowLesson()
    
    /**returns word and filepath pairs as a HashMap*/
    private HashMap<String, String> makeLesson(String category){
        java.util.HashMap<String, String> pairs = new
            java.util.HashMap<String, String>();
        if(folderExists(category)){
            if(folderContainsPictures(category)){
                File f = new File(category);
                File[] list = f.listFiles();
                for(int i = 0; i < list.length; i++){
                    if(isPictureFile(list[i])){
                        char[] wordArray = list[i].getName().toCharArray();
                        String word = "";
                        for(int j = 0; j < wordArray.length; j++){
                            if(wordArray[j] == '.'){break;}
                            word += wordArray[j];
                        }
                        System.out.println("In makeLesson loop " + i + ", word " + word);
                        pairs.put(word, list[i].getAbsolutePath());
                    }
                }
            }
        }
        return pairs;
    }//end method makeLesson()
    
    /*fields used in showLesson() below*/
    HashMap<String, String> pairs;//initialized in showLesson()
    Iterator<String> i;//initialized in showLesson()
    JFrame frame;//initialized in showLesson()
    JPanel panel;//initialized in showLesson()
    JLabel label;//initialized in showLesson()
    String[] words;//initialized in showLesson()
    boolean isImage = true;//may alternate between true and false during program runtime
    int randomNumber = 0;//changes during program runtime
    
    /**calls showFrame*/
    private void showLesson(String category){
        pairs = makeLesson(category);
        words = new String[pairs.size()];
        i = pairs.keySet().iterator();
        int number = 0;
                    while(i.hasNext()){
                        words[number] = i.next();
                        number++;
                    }
        frame = new JFrame(category);
        panel = new JPanel();
        label = new JLabel();
        Action action = new AbstractAction(){
            public void actionPerformed(ActionEvent e){
                    if(isImage){
                        showText(words[randomNumber], label);
                        isImage = false;
                    }else{
                        showImage(pairs.get(words[randomNumber]), label);
                        isImage = true;
                        randomNumber = (int)(Math.random()*words.length);
                    }
                }//end method actionPerformed()
        };
        showFrame(frame, panel, label, action);
    }//end method showLesson()
    
    /**get the list of files and folders within the main/working directory*/
    private String[] getDirPathsList(){
        File path = new File("");
        File mainFolder = new File(path.getAbsolutePath());
        System.out.println("From getList: " + mainFolder.getAbsolutePath());
        return mainFolder.list();
    }//end method getList()
    
    private boolean folderExists(String folderPath){
        System.out.println("In folderExists:");
        File f = new File(folderPath);
        if(f.isDirectory()){
            return f.exists();
        }else{
            return false;
        }
    }//end method folderExists()
    
    /**must be given a folder and not a file*/
    private boolean folderContainsPictures(String folder){
        System.out.println("Folder given to folderContainsPictures: " + folder);
        File f = new File(folder);
        File[] filesInFolder = f.listFiles();
        for(int i = 0; i < filesInFolder.length; i++){
            System.out.println("FolderContainsPictures for loop: " + i);
            if(isPictureFile(filesInFolder[i])){return true;}
        }
        return false;
    }
    
    private boolean isPictureFile(File file){
        if(file.getName().endsWith(".jpeg")||
           file.getName().endsWith(".jpg")||
           file.getName().endsWith(".JPEG")||
           file.getName().endsWith(".gif")
         ){
            return true;
         }else return false;
    }
    
    private boolean folderIsInList(String folder){
        System.out.println("In folderIsInList method: String[] list initialized");
        for(int i = 0; i < folderList.size(); i++){
            if(folderList.get(i).equals(folder)){return true;}
        }
        return false;
    }
    
    /**initializes GUI with spacebar-fired Action events*/
    private void showFrame(JFrame f, JPanel p, JLabel l, Action action){
        p.setFocusable(true);
        p.getInputMap().put(KeyStroke.getKeyStroke("SPACE"), "space");
        p.getActionMap().put("space", action);
        l.setFont(new Font(l.getFont().getName(), java.awt.Font.PLAIN, 200));
        p.add(l);
        f.add(p);
        f.setVisible(true);
        f.setMinimumSize(new Dimension(1000, 700));
        f.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);   
    }//end method showFrame()
    
    /**used in showLesson()*/
    private void showImage(String hashMapFilePath, JLabel l){
        ImageIcon imageIcon = new ImageIcon(hashMapFilePath);
        Image img = scaleImage(imageIcon);
        imageIcon = new ImageIcon(img);

        l.setText(null);
        l.setIcon(imageIcon);
    }//end method showLesson()
    
    /**used in showLesson()*/
    private void showText(String word, JLabel l){
        l.setIcon(null);
        l.setText(word);
    }//end method showText()
    
    /**returns true if width is longest*/
    private boolean isWidthLongest(ImageIcon imgIcon){
        boolean widthIsLongest = false;

        int height = imgIcon.getIconHeight();
        int width = imgIcon.getIconWidth();

        if(height > width){widthIsLongest = false;}
        if(width > height){widthIsLongest = true;}
        return widthIsLongest;
    }//end method isWidthLongest()
    
    /**returns a properly scaled Image*/
    private Image scaleImage(ImageIcon imgIcon){
        int width = imgIcon.getIconWidth();
        int height = imgIcon.getIconHeight();
        int scaledWidth;
        int scaledHeight;
        int scaledWidthMax = 1000;
        int scaledHeightMax = 700;

        if(isWidthLongest(imgIcon) == true){
            scaledWidth = scaledWidthMax;
            scaledHeight = height * scaledWidth / width;
        }else{
            scaledHeight = scaledHeightMax;
            scaledWidth = width * scaledHeight / height;
        }
        Image i = imgIcon.getImage().getScaledInstance(
                scaledWidth, scaledHeight, Image.SCALE_SMOOTH);
        return i;
    }//end method scaleImage()
    
    //class CategoryObj{} variables declaration
    public ArrayList<String> folderList = new ArrayList<String>();//used in loadCategories
    public JComboBox<String> menu = new JComboBox<String>();//used in loadCategories 
    //end CategoryObj{} variables declaration
    
}//end class CategoryObj{}
