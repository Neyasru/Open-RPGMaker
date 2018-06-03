/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package tedi;
import UI.*;
import static javax.swing.JFrame.EXIT_ON_CLOSE;

/**
 *
 * @author Ferran
 */
public class Tedi {
    
    
     /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        java.awt.EventQueue.invokeLater(new Runnable() {
            LoadForm loadform = LoadForm.getInstance();           
            @Override
            public void run() {
                loadform.initPresentation();
            } 
        });
    }
    
}
