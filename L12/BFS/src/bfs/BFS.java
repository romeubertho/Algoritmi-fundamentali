/**
 *   
 *  
 * @ 9 - BFS
 * @Saptamana 12
 */
package bfs;

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Scanner;
import java.util.Set;


/** Clasa in care se ruleaza BFS */
public class BFS {    
    /** Lista Nodurilor Grafului */
    private static final List<Nod<Integer>> lng = new ArrayList<>();
    
    
    /** 
     * Verifica daca nodul a fost deja adaugat in lista
     * @param id id-ul elementului care se intentioneaza a fi adaugat
     * @param lista lista de verificat
     * @return true daca elementul e duplicat, false in celelalte cazuri
     */
    static private <T> boolean eDuplicat(int id, List<Nod<T>> lista){
        for (Nod<T> x : lista)
            if (x.getId() == id)
                return true;
        return false;
    }
    
    
    /**
     * Citeste listele de adiacenta din fisier
     * @throws FileNotFoundException 
     */
    private static void creeazaListe() throws FileNotFoundException{
        ///citirea nodurilor din fisier
        Scanner in = new Scanner(new FileReader("in.txt"));
        Scanner buf;    ///linia curenta de fisier txt
        while (in.hasNextLine()){
            buf = new Scanner(in.nextLine());
            int idNod = buf.nextInt(); ///id-ul nodului adaugat
            if (eDuplicat(idNod, lng)){
                buf.close();
                continue;
            }
            
            Set<Integer> lad = new HashSet<>(); ///lista de adiacenta a nodului curent reprezentata ca o multime     
            while (buf.hasNextInt()){
                int tmp = buf.nextInt();
                if (tmp == idNod)
                    continue;
                lad.add(tmp);
            }
                       
            lng.add(idNod,new Nod(idNod,lad));
            
            buf.close();
        }
        in.close();   
    }
    
    
    /**
     * BFS incepand de la primul element citit
     * @return returneaza un string ce contine id-urile nodurilor in ordinea parcurgerii lor
     */
    public static <T> String bfs1(){// throws Exception{
        String rez = "";
        /** id-ul nodurilor din coada de asteptare */
        List<Integer> coada  = new LinkedList<>();
        /** pointerul ce indica ultimul element nevizitat din coada */
        int p = 0;
        
        coada.add(lng.get(p).getId());    /// se adauga elementul de start in coada
        //rez += String.format("%d ", coada.get(p));
        
        do {
            for (Nod j : lng){  /// se cauta in coada nodul de id egal cu nodul care trebuie vizitat
                if (j.getId() == coada.get(p)){ 
                    for (Integer x : lng.get(coada.get(p)).la) { /// se adauga toate elementele adiacente nodului curent care nu au fost inca descoperite
                        if (!coada.contains(x)){ /// daca nodul a fost deja descoperit el nu se mai adauga
                            coada.add(x);
                            rez += String.format("%d ", x);                            
                        }
                        //break;
                    };
                }// else
                    //throw new Exception("Nodurile au fost introduse gresit in fisier!");
            }
            p++;
        } while (p < coada.size());
        
        return rez;
    }
    
    
    /**
     * Afisaza lista nodurilor grafului impreuna cu nodurile de care sunt legate
     * @param l lista de afisat
     */
    public static <T> void printLng(List<Nod<T>> l){
        l.stream().forEach((x) -> {
            System.out.print(x.getId() + ": ");
            System.out.print(x.toStringLa());
            System.out.println();                    
        });
    }
        
    
    public static void main(String[] args) throws FileNotFoundException, Exception {
        creeazaListe();      
        printLng(lng);
        System.out.println(bfs1());
    }
}
