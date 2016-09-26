/**
 *   
 *  
 * @ 8
 * @Saptamana 11
 */
package multimiDisjuncte;

import java.util.TreeMap;

public class Main {
    private static final TreeMap<Integer,Multime<Integer>> mdm = new TreeMap<>();
    
    public static Multime makeSet(int e){
        return new Multime<>((Integer)e);
    }
      
    public static Multime union(Multime<Integer> a, Multime<Integer> b){
        Multime<Integer> c = new Multime<>();
        a.t.keySet().stream().forEach((q) -> {
            c.put(a.t.get(q));
        });
        b.t.keySet().stream().forEach((q) -> {
            c.put(b.t.get(q));
        });
        return c;
    }
    
    public static void findSet(Integer x){
        System.out.println("Gaseste: "+x);
        for(Integer q: mdm.keySet()){
            if (mdm.get(q).contine(x))
                mdm.get(q).afisare();
        }
    }
    
    public static void afisare(){
        System.out.println("afisare: ");
        System.out.print("{");
        mdm.keySet().stream().forEach((q) -> {
            mdm.get(q).afisare();
        });
        System.out.println("}");
    }
    
    public static void main (String [] args){     
        
        Multime<Integer> x = makeSet(4);
        x.put(7);
        x.put(9);
        x.put(9);
        x.afisare();
        Multime<Integer> y = makeSet(1);
        Multime<Integer> z = makeSet(2);
        z.put(4);
        x = union(x,y);
        x = union(x,z);
        x.afisare();
        
        mdm.put(1, x);
        mdm.put(2, y);
        mdm.put(3, z);
        findSet(2);
        
        afisare();
    }
}
