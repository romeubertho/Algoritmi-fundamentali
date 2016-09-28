/**
 *   
 *  
 * @ 9 - BFS
 * @Saptamana 12
 */
package bfs;

import java.util.Set;

public class Nod<T> {
    private int id;
    /** datele memorate in nod */
    private T date;
    /** lista de adiacenta */
    protected Set<Integer> la;
    
    public Nod(int id, T date, Set<Integer> la){
        this.id = id;
        this.date = date;
        this.la = la;
    }
    
    public Nod(int id, Set<Integer> la){
        this.id = id;
        this.la = la;
    }
    
    /** 
     * Transmite lista de adiacenta printr-un String 
     */
    public String toStringLa(){
        if (la.isEmpty())
            return "";
        String rez = "";
        for (Integer x : la)
            rez += String.format("%d ", x);
        
        return rez;
    }
    
    ///Getters
    public int getId(){
        return this.id;
    }
}
