/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package tedi;

import UI.EditorForm;
import UI.EditorForm.Info;
import java.awt.List;
import java.io.BufferedReader;
import java.io.File;
import java.util.Vector;
import java.io.FileReader;
import java.util.ArrayList;
/**
 *
 * @author Ferran
 */
public class Parser {
    private static String filename;
    private static Parser par;
 
    public Parser (){
        filename = "";
    }
    
    public Parser (String fn){
        filename = fn;
        //fer el Parsing
        ArrayList<String> records = new ArrayList<String>();
        try
        {
          BufferedReader reader = new BufferedReader(new FileReader(filename));
          String line;
          while ((line = reader.readLine()) != null)
          {
            records.add(line);
          }
          reader.close();
        }
        catch (Exception e)
        {
          File f = new File(filename);
         try{
            f.createNewFile();
         }
         catch(Exception e1){
            System.err.format("Exception occurred trying to read '%s'.", filename);
            e.printStackTrace();
         }
        }
        
        System.out.println(records.get(0));
        
    }
    
    public void setFilename(String fn){
        filename = fn;
    }
    
    public static Parser getInstance(String luaP){
        if (par == null) {
            par = new Parser(luaP);
        }
        return par;
    }
    
     public void getParsedInfo(Vector<Info> info ,int C, int R) {
        Info ninfo = info.get(0);
        for(int i = 0; i < C; i++){
            for(int j = 0; j < R; j++){
                
            }
        }
    }
}
