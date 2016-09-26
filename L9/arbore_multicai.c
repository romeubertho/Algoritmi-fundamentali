/**   
implementarea schemei din fig1.png
*/

#include <stdio.h>
#include <stdlib.h>


typedef struct tip_nod{
    /** valoare nodului */
    int v;
    /** indexul din nod */
    int i;
    int on;  ///nivelul la care se afla nodul
    /** nodul parinte, nodul drept, nodul stang */
    struct tip_nod *p,*d,*s; /// nodul parinte va fi folosit mai la urma ca nodul din mijloc
} nod;



/** afisare (parcurgere inordine) */
void afisaza_arbore(nod* p){
    int i;
    if (p != 0){
        for (i = 0; i< p->on; i++)
            printf("\t");
        printf("%2d\n",p->i);
        afisaza_arbore(p->s);
        afisaza_arbore(p->p);
    }
}


/** crearea unui nod */
nod *creeaza_nod(nod* pp,nod* s, nod* d,int v, int i,int on){
    nod *p;
    p =(nod*) malloc (sizeof(nod));

    if (p == 0){
        printf("\nEroare: nu s-a alocat memorie in heap!");
        return 0;
    }

    p->p = 0;
    p->s = 0;
    p->d = 0;
    p->v = -1;
    p->i = i;
    p->on = on;

    if (pp >= 0)
        p->p = pp;
    if (s >= 0)
        p->s = s;
    if (d >= 0)
        p->d = d;
    if (v >= -1)
        p->v = v;
    return p;
}


/** legare noduri -- R1: parent representation */
nod** r1(nod**p,int dim,int *a){
    int i;
    for (i = 1; i<dim; i++)
        p[i]->p = a[i]>0?p[a[i]]:0;
    printf("R1: parent representation:\n");
    afisare(p,dim);
    printf("\n");
}


/** multi-way representation -- R2
    acum pointer-ul ->p reprezinta nodul central
*/
nod** r2(nod**p,int dimensiune){
    nod*u[dimensiune];
    int i = 0;
    for (i = 1; i<dimensiune; i++)
        u[i] = creeaza_nod(0,0,0,p[i]->v,i,p[i]->on);

    for (i = 1; i<dimensiune; i++)
        if (p[i]->p != 0){
            nod *x;
            x = u[p[i]->p->i];
            if (x->s == 0){
                x->s = u[i];
            }
            else
                if (x->p == 0)
                    x->p = u[i];
                else
                    x->d = u[i];
            p[i]->p = 0;
        }

    printf("R2: parent representation:\n");
    afisare(u,dimensiune);
    return u;
}


/** binary representation -- r3 */
///s - nivel inferior; p - acelasi nivel
nod** r3(nod**p,int dimensiune){
    nod*u[dimensiune];
    int i;
    for (i = 1; i<dimensiune; i++)
        u[i] = creeaza_nod(0,0,0,p[i]->v,i,p[i]->on);

    for (i = 1; i<dimensiune; i++){
        if (p[i]->p!=0 && p[i]->d!=0){
            u[p[i]->p->i]->p = u[p[i]->d->i];
        }
        if (p[i]->s!=0 && p[i]->p!=0){
            u[p[i]->s->i]->p = u[p[i]->p->i];
        }

        u[i]->d = 0;
    }

    for (i = 1; i<dimensiune; i++){
        if (p[i]->s!=0)
            u[i]->s = u[p[i]->s->i];
    }
    afisare(u,dimensiune);

    int max = 0;
    int maxi = 0;
    for (i=0;i<dimensiune;i++){
        if ((max < u[i]->v && max > 0) || u[i]->v < 0){
            max = u[i]->v;
            maxi = i;
        }
    }



    afisaza_arbore(u[7]);
    return u;
}

void afisare(nod**p,int dim){
    int i;
    for (i = 1;i<dim; i++){
        printf("p[%d]=%d\t",i,p[i]->v);
        if (p[i]->s>0)
            printf("s=%d\t",p[i]->s->i);
        else
            printf("s=0\t");
        if (p[i]->p>0)
            printf("p=%d\t",p[i]->p->i);
        else
            printf("p=0\t");
        if (p[i]->d>0)
            printf("d=%d",p[i]->d->i);
        else
            printf("d=0");
        printf("\n");
    }
    printf("\n");
}


int main()
{
    int a[] = {0,2,7,5,2,7,7,-1,5,2};
    int dim = 10;
    nod* p[dim];
    int i;

    ///initializare noduri
    for (i = 1; i<dim; i++)
        p[i] = creeaza_nod(0,0,0,a[i],i,0);


/// R1
    r1(p,dim,a);

    for (i = 1;i<dim;i++){
        nod* no = p[i];
        while (no->p != 0){
            p[i]->on += 1;
            no=no->p;
        }
    }


/// R2
    int dimensiune = dim;
    nod*u[dimensiune];
    i = 0;
    for (i = 1; i<dimensiune; i++)
        u[i] = creeaza_nod(0,0,0,p[i]->v,i,p[i]->on);

    for (i = 1; i<dimensiune; i++)
        if (p[i]->p != 0){
            nod *x;
            x = u[p[i]->p->i];
            if (x->s == 0){
                x->s = u[i];
            }
            else
                if (x->p == 0)
                    x->p = u[i];
                else
                    x->d = u[i];
            p[i]->p = 0;
        }

    printf("R2: parent representation:\n");
    afisare(u,dimensiune);


/// R3
    printf("R3: binary representation:\n");
    r3(u,dim);

    return 0;
}
