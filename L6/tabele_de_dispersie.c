#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int N = 10007;
int N95 = (int)(95.0/100* 10007);

/** returneaza un intreg cuprins intre min si max */
int intreg_aleator(int min, int max){
    //srand(time(NULL));
    return rand() % (max-min+1) + min;
}

typedef struct tip_nod{
    int v; // valoarea
    //int l; // lista din care face parte
    struct tip_nod *d,*s; // nodul drept si nodul stang
} nod;


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
    return p;
}

int getHash(int x){
    return (x%N);
}

/** initializeaza tabela de dispersie */
void initializeaza(struct tip_nod* a[], int dimensiune){
    int i;
    for (i=0;i<N;i++)
        a[i] = 0;
}


/** insereaza valoarea x in tabela a */
void insereaza(struct tip_nod* a[], int x){
    nod* p;
    p = creeaza_nod();
    p->v = x;

    int h = getHash(x);
    if (a[h] == 0)
        a[getHash(x)] = p;
    else{
        nod* u;
        u = a[h];
        while (u->d != 0)
            u = u->d;
        u->d = p;
        p->s = u;
    }
}


/** afisaza tabela de dispersie */
void afisaza(struct tip_nod* a[], int dimensiune){
    printf("\nTabela este:\n");
    int i;
    nod* u;
    for (i=0;i<dimensiune;i++)
        if (a[i] == 0)
            continue;
        else
        {
            u = a[i];
            printf("a[%d]: ", i);
            do{
                printf("%d ",u->v);
                u = u->d;
            }
            while (u != 0);
            printf("\n");
        }
    printf("--------------\n");
}


/** cauta un element in lista si returneaza indexul
    in care a fost gasit sau -1 daca nu a fost gasit */
nod* cauta(int x, struct tip_nod* a[], int dimensiune){
    int h = getHash(x);

    if (a[h] == 0)
        return -1;

    nod* u;
    u = a[h];
    do{
        if (u->v == x)
            return h;
        u = u->d;
    } while (u != 0);

    return -1;
}

int main()
{
    srand(time(NULL));
    struct tip_nod* a[N]; //tabela de dispersie
    initializeaza(a,N);


    int i, u;

    for (i=0;i<N95;i++)
        insereaza(a,intreg_aleator(0,100000));

    afisaza(a,N);

    printf("\nCauta un element. Introduceti i. i =");
    scanf(" %d",&i);

    if ((u = cauta(i,a,N)) < 0)
        printf("Elementul nu a fost gasit.");
    else
        printf("Elementul a fost gasit la indexul %d.", u);


    return 0;
}
