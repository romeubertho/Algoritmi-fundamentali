/**
 *   
 *  
 * @ 10 - DFS
 * @Saptamana 13
 */
package dfs;

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.PrintWriter;
import java.io.UnsupportedEncodingException;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Random;
import java.util.Scanner;
import java.util.Set;


/** Clasa in care se ruleaza DFS */
public class DFS {    
    /** Rezultatul testarii */
    private static String rez;
    /** Lista Nodurilor Grafului */
    private static final List<Nod<Integer>> lng = new ArrayList<>();
    /** Lista nodurilor grafului generat la punctul 1 */
    private static List<Nod<Integer>> lng1;
    /** Lista nodurilor grafului generat la punctul 2 */
    private static List<Nod<Integer>> lng2;
    
    
    /** 
     * Verifica daca nodul a fost deja adaugat in lista
     * @param id id-ul elementului care se intentioneaza a fi adaugat
     * @param lista lista de verificat
     * @return true daca elementul e duplicat, false in celelalte cazuri
     */
    static private <T> boolean eDuplicat(int id, List<Nod<T>> lista){
        if (lista.stream().anyMatch((x) -> (x.getId() == id))) {
            return true;
        }
        return false;
    }
    
    
    /**
     * Citeste listele de adiacenta din fisier
     * In fisierul nodurilor, pe primul rand trebuie scris 0 x unde x este nodul cu care se incepe
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
     * DFS incepand de la primul element citit
     * @param lng lista nodurilor
     * @return returneaza un string ce contine id-urile nodurilor in ordinea parcurgerii lor
     */
    public static int[] dfs(List<Nod<Integer>> lng){// throws Exception{
        /** id-ul nodurilor din coada de asteptare */
        final List<Integer> nodurileVizitate  = new LinkedList<>();
        final List<Integer> stiva = new ArrayList<>();
        
        final int[] p = new int[2];
        p[0] = 0;   /// pointerul ce indica ultimul element nevizitat din stiva
        p[1] = 0;   ///numarul de cautari a unui nod care poate fi pus in stiva
        
        nodurileVizitate.add(lng.get(0).getId());    /// se adauga elementul de start in coada pe pozitia 0
        stiva.add(p[0]++, 0);  // se pune primul element (elementul auxiliar 0) in stiva

        final boolean[] k = new boolean[1]; 
        
        do {
            k[0] = true;    /// k ne spune daca la iteratia curenta s-a adaugat un nod in stiva
            lng.stream().forEach(j->{ /// se cauta in multimea tuturor nodurilor
                    if (p[0] == 0)
                        return;
                    int a = stiva.get(p[0]-1);
                    if (j.getId() == a){ /// nodul de id egal cu nodul din varful stivei
                        k[0] = true;
                        lng.get(a).la.stream().forEach(x->{ /// se adauga primul element adiacent nodului curent care nu a fost inca descoperit
                            p[1]++;
                            if ((!nodurileVizitate.contains(x)) && k[0]){ /// daca nodul a fost deja descoperit el nu se mai adauga
                                nodurileVizitate.add(x);   
                                stiva.add(p[0]++,x);                              
                                k[0] = false;
                            }
                        });
                        if (k[0])
                            p[0]--;
                    }// else
                        //throw new Exception("Nodurile au fost introduse gresit in fisier!");
            });
        } while (p[0] != 0);  ///cat timp nu mai sunt noduri in sitva
        
        rez = nodurileVizitate.stream().map((i) -> String.format("%d ", i)).reduce("", String::concat).substring(2);
        return p;
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
    
    
    /**
     * Generarea unui grafic aleator pentru subpunctul 1 (cu 100 de varfuri si cu numar variabil de muchii)
     * @param numarDeMuchii arata numarul muchiilor
     */
    @SuppressWarnings("empty-statement")
    public static void genereaza1(int numarDeMuchii){
        lng1  = new ArrayList<>();
        int NUMARUL_VARFURILOR = 100;
        
        for (int i = 0; i <= NUMARUL_VARFURILOR; i++) ///aloca varfurile
            lng1.add(i, new Nod(i));
        
        lng1.get(0).adaugaNod(1);   ///algoritmul incepe de la nodrul 1        
        
        Random rand = new Random();
        for (int i = 0; i < numarDeMuchii; i++){
            int x = rand.nextInt(NUMARUL_VARFURILOR)+1;
            int y;
            while ((y = rand.nextInt(NUMARUL_VARFURILOR)+1) == x);
            lng1.get(x).adaugaNod(y);
        }
    }
    
    
    /**
     * Rezolvarea ceritnei de la subpunctul 1
     * @throws FileNotFoundException
     * @throws UnsupportedEncodingException 
     */
    public static void calculeaza1() throws FileNotFoundException, UnsupportedEncodingException{
        try (PrintWriter writer = new PrintWriter("out1.csv", "UTF-8")) {
            for (int i = 1000; i <= 5000; i+=100){
                genereaza1(i);
                int [] parametri = dfs(lng1);
                writer.println(i+","+parametri[1]);
            }
            writer.close();
        }
    }     
    
    
    /**
     * Generarea unui grafic aleator pentru subpunctul 2 (cu 9000 de muchii si cu numar variabil de varfuri)
     * @param numarulVarfurilor 
     */
    @SuppressWarnings("empty-statement")
    public static void genereaza2(int numarulVarfurilor){
        int NUMARUL_MUCHIILOR = 9000;
        lng2  = new ArrayList<>();
        
        for (int i = 0; i <= numarulVarfurilor; i++) ///aloca varfurile
            lng2.add(i, new Nod(i));
        
        lng2.get(0).adaugaNod(1);   ///algoritmul incepe de la nodrul 1        
        
        Random rand = new Random();
        for (int i = 0; i < NUMARUL_MUCHIILOR; i++){
            int x = rand.nextInt(numarulVarfurilor)+1;
            int y;
            while ((y = rand.nextInt(numarulVarfurilor)+1) == x);
            lng2.get(x).adaugaNod(y);
        }
        
    }
    
    
    /**
     * Rezolvarea ceritnei de la subpunctul 1
     * @throws FileNotFoundException
     * @throws UnsupportedEncodingException 
     */
    public static void calculeaza2() throws FileNotFoundException, UnsupportedEncodingException{
        try (PrintWriter writer = new PrintWriter("out2.csv", "UTF-8")) {
            for (int i = 100; i <= 200; i+=10){
                genereaza2(i);
                int [] parametri = dfs(lng2);
                writer.println(i+","+parametri[1]);
            }
        }
    }   
    
    
    public static void main(String[] args) throws FileNotFoundException, Exception {
        creeazaListe();      
        printLng(lng);
        dfs(lng);
        System.out.println(rez);
        calculeaza1();
        calculeaza2();
    }
}