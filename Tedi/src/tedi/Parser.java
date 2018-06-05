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
import java.util.HashMap;
import java.util.Map;
/**
 *
 * @author Ferran
 */
public class Parser {
    private static String filename;
    private static Parser par;
    private Map<String, Integer> idexMap;
    private Map<Integer, String> strgMap;
 
    public Parser (){
        filename = "";
    }
    
    public Parser (String fn,Vector<Info> info ,int C, int R){
        filename = fn;
        idexMap = new HashMap<>();
        strgMap = new HashMap<>();
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
        //printDebug(records);
        int i = 0;
        String s;
        String a[];
        if (records.get(0).equals("tiles = {")){
            i = 1;
            while (!records.get(i).equals("}")){
                s = records.get(i);
                a = s.split(" ");
                //System.out.println(a[0]);
                idexMap.put(a[4], Integer.parseInt(a[6].substring(0, a[6].length()-1)));
                strgMap.put(Integer.parseInt(a[6].substring(0, a[6].length()-1)), a[4]);
                //System.out.println(a[2].substring(0, a[2].length()-1));
                i++;
            }
        }
        i++;
        while (i < records.size()){
            s = records.get(i);
            a = s.split(" ");
            int id = idexMap.get(a[0]);
            System.out.println(id);
            //entrem a tractar el cas
            Info pars = new Info();
            pars = info.get(id);
            pars.name = strgMap.get(id);
            System.out.println(pars.name);
            
            ++i;
            while (!records.get(i).equals("}")){
                s = records.get(i);
                a = s.split(" ");
                switch(a[4]){
                    case "GraphicsComponent":
                        i++;
                        s = records.get(i);
                        a = s.split(" ");
                        String ID = a[10].substring(0, a[10].length()-1);
                        pars.gC.imageID = ID;
                        
                        i++;
                        s = records.get(i);
                        a = s.split(" ");
                        int row = Integer.parseInt(a[10].substring(0, a[10].length()-1));
                        pars.gC.row = row;
                        
                        i++;
                        s = records.get(i);
                        a = s.split(" ");
                        int column = Integer.parseInt(a[10].substring(0, a[10].length()-1));
                        pars.gC.column = column;
                        
                        i++;
                        s = records.get(i);
                        a = s.split(" ");
                        int anim = Integer.parseInt(a[10].substring(0, a[10].length()-1));
                        pars.gC.numAnim = anim;
                        break;
                    case "TransformComponent":
                        i++;
                        s = records.get(i);
                        a = s.split(" ");
                        int nw = Integer.parseInt(a[10].substring(0, a[10].length()-1));
                        pars.tC.w = nw;
                        
                        i++;
                        s = records.get(i);
                        a = s.split(" ");
                        int nh = Integer.parseInt(a[10].substring(0, a[10].length()-1));
                        pars.tC.h = nh;
                        
                        i++;
                        s = records.get(i);
                        a = s.split(" ");
                        int nx = Integer.parseInt(a[10].substring(0, a[10].length()-1));
                        pars.tC.x = nx;
                        
                        i++;
                        s = records.get(i);
                        a = s.split(" ");
                        int ny = Integer.parseInt(a[10].substring(0, a[10].length()-1));
                        pars.tC.y = ny;
                        
                        i++;
                        s = records.get(i);
                        a = s.split(" ");
                        int nscale = Integer.parseInt(a[10].substring(0, a[10].length()-1));
                        pars.tC.scale = nscale;
                        
                        break;
                    case "ColliderComponent":
                        i++;
                        s = records.get(i);
                        a = s.split(" ");
                        String ntype = a[10].substring(0, a[10].length()-1);
                        pars.cC.type = ntype;
                        break;
                    default:
                        System.out.println(a[0]);
                        break;
                }
                info.setElementAt(pars, id);
                ++i;
            }
            
            ++i;
        }       
    }
    
    void printDebug( ArrayList<String> records){
      for (int i = 0; i < records.size(); i++){
            System.out.println(records.get(i));
        }
    }
    
    public void setFilename(String fn){
        filename = fn;
    }
    
    public static Parser getInstance(String luaP,Vector<Info> info ,int C, int R){
        if (par == null) {
            par = new Parser(luaP,info ,C,R);
        }
        return par;
    }
    
    public void save(Vector<Info> info) {
        System.out.println(info.get(0).name);
    }
}
