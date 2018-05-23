/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package tedi;

/**
 *
 * @author Ferran
 */
public class Parser {
    private static String filename;
    
    public Parser (){
        filename = "";
    }
    
    public Parser (String fn){
        filename = fn;
    }
    
    public void setFilename(String fn){
        filename = fn;
    }
    
    
}
