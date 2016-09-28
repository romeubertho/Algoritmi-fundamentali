/**
 *   
 *  
 * @ 8
 * @Saptamana 11
 */
package multimiDisjuncte;

import java.util.TreeMap;

public class Multime<X> {
    public final TreeMap<Integer,X> t = new TreeMap<>();
    private int id;
    
    public Multime(){
        id = 1;
    }
    
    public void put(X x){
        for (Integer q : t.keySet())
            if (t.get(q).equals(x))
                return;
        t.put(id++,x);
    }
    
    public Multime(X x){
        id=1;
        t.put(id++, x);
    }
    
    public int rank(){
       return  t.size();
    }
    
    public void afisare(){
        System.out.print("{");
        t.keySet().stream().forEach((q) -> {
            System.out.format(" %d ", (Integer)t.get(q));
        });
        System.out.println("}");
    }
    
    /**
     * Verifica daca multimea contine un anumit element
     * @param x
     * @return true daca il contine, false daca nu il contine
     */
    public boolean contine(X x){
        for (Integer q : t.keySet()){
            if (t.get(q).equals(x))
                return true;
        }
        return false;
    }
   
}
