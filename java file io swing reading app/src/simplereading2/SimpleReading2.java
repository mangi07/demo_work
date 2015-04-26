/*Written by Bejamin R. Olson
* Copyright 2012, All Rights Reserved
*/

/*This program searches folders in its directory
* to find any folders containing pictures
* and then presents these folders as categories
* that the user can select from a drop-down menu.
* When a category is selected, a frame pops up
* that will show word-picture pairs, in random order,
* as long as the user continues to press the space bar
* or until the user exits that frame.
*/

/*Strategy:
 * Load category folders into the ComboBox,
 * check to see whether they still refer to actual folders,
 * and check to see whether those folders still contain
 * at least one picture each.  If they do, do nothing; if they don't,
 * remove them and notify the user, and then...
 * 
 * The user chooses a file folder from which word-picture sets
 * are shown in random order:
 * 1. The user chooses one folder containing pictures:
 *      a. Let user open any folder on hard disk.
 *          Use ComboBox to choose a loaded folder path.
 *      b. Determine whether chosen folder has pictures:
 *          1. If not, go back to a.
 *          2. If so, continue with 2. after this:
 *              If the chosen folder path has not been added to the Combo Box,
 *                  add it to the ComboBox.
 * 2. Make word-picture objects (type PictureObj):
 *      a. Find all pictures in the folder.
 *      b. Make a word-picture object, for each file...
 *          1. Make the word from the file name,
 *          2. Make picture file path to get that file, and
 *          3. Add the word-picture object to the category
 * 3. Do the presentation for this chosen category...
 *      a. Show the presentation frame.
 *      b. Let the user show word followed by its picture, in random order, from the list.
 *          1. If the user reaches the end of the list, go back to "a".
 *          2. The user can stop the presentation at any time.
 */

package simplereading2;

/**
 *
 * @author Benjamin R. Olson
 */
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class SimpleReading2 implements ActionListener{
    
    public void init(){
        obj = new CategoryObj();
        JFrame f = new JFrame("Simple Reading BRO");
        f.setMinimumSize(new Dimension(500, 500));
        f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        JPanel p = new JPanel();
        f.add(p);
        obj.loadCategories();
        JComboBox combo = obj.menu;
        p.add(combo);
        combo.addActionListener(this);
        f.setVisible(true);
    }
    
    public void actionPerformed(ActionEvent e){
            String category = (String)obj.menu.getSelectedItem();
            obj.chooseCategoryAndShowLesson(category);
        }
    
    public static void main(String[] args) {
        SimpleReading2 reading = new SimpleReading2();
        reading.init();
    }
    
    //variables declaration
    CategoryObj obj;
    
}//end class SimpleReading2
