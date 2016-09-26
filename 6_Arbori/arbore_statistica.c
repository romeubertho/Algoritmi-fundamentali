/**
Statistici dinamice de ordine
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>


typedef struct tip_nod{
    /** valoare nodului */
    int v;
    /** dimensiune aka size -- dimensiunea subarborelui cu radacina in nod; valoare minima 1 */
    int dim;
    /** nodul parinte, nodul drept, nodul stang */
    struct tip_nod *p,*d,*s;
} nod;


/** returneaza un intreg cuprins intre min si max */
int intreg_aleator(int min, int max){
    return rand() % (max-min+1) + min;
}


/** crearea unui nod */
nod *creeaza_nod(){
    nod *p;
    p =(nod*) malloc (sizeof(nod));

    if (p == 0){
        printf("\nEroare: nu s-a alocat memorie in heap!");
        return 0;
    }

    p->d = 0;
    p->s = 0;
    p->v = 0;
    p->dim = 0;
    return p;
}


/** afisaza vector */
void afisaza_vector(int a[], int dimensiune){
    int i;
    printf("Vectorul sortat este: ");
    for (i = 0;i < dimensiune; i++)
        printf("%d ", a[i]);
    printf("\n");
}


/** afisare (parcurgere inordine) */
void afisaza_arbore(nod* p, int nivel){
    int i;
    if (p != 0){
        afisaza_arbore(p->s,nivel+1);
        for (i = 0; i< nivel; i++)
            printf("\t");
        printf("%2d-%2d\n",p->v,p->dim);
        afisaza_arbore(p->d,nivel+1);
    }
}


/** construieste arborele; a - vectorul de intrare; lungimea - lungimea lui a */
nod* construieste(int a[],int lungime){
    nod* nd;
    nd = creeaza_nod();
    nd->dim = lungime;
    int jum = lungime/2; /// jumatate
    nd->v = a[jum];

    if (lungime-(jum+1) > 0){
        nd->d = construieste(a+jum+1,lungime-(jum+1));
    }

    if (jum > 0)
        nd->s = construieste(a,jum);


    return nd;
}


int main(){
    srand(time(NULL));

/// se genereaza un vector sortat
    int i, a[12];
    a[0] = 0;
    for (i = 1;i<=11;i++)
        a[i] = i-1;

/// se afisaza vectorul sortat
    afisaza_vector(a+1,11);

/// construieste vectorul
    nod *rad = construieste(a+1,11);

/// afisaza arborele
    printf("Arborele este:\n");
    afisaza_arbore(rad,0);

    return 0;
}
