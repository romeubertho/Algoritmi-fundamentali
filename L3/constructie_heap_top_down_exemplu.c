/**
*   
* @group 
*
* Heap sort - constructie heap top-down
* programul genereaza heap-ul corespunzator unui vector generat cu valori aleatorii cu n=10 elemente
* dupa care afisaza cum arata heap-ul corespunzator pentru ca utilizatorul sa poata verifica corectitudinea
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


/** returneaza un intreg cuprins intre min si max */
int intreg_aleator(int min, int max){
    //srand(time(NULL));
    return rand() % (max-min+1) + min;
}

/** genereaza un vector a cu n elemente (incepand de la a[1]) cu valori cuprinse intre min si max */
void genereaza_vector(int *a,int n,int min,int max){
    int i;
    a[0]=0;
    for (i=1;i<=n;i++)
        a[i]=intreg_aleator(min,max);
    return;
}

/** seteaza valorile unui vector la 0 */
void initializeaza_vector(int *a,int n){
    int i;
    for(i=0;i<n;i++)
        a[i] = 0;
}

/** afisaza un vector in consola */
void afisaza_vector(int a[], int n){
    int i;
    for (i = 1; i<= n; i++)
        printf("%d  ",a[i]);
    printf("\n");
    return;
}

/** adauga un element in heap si reconstruieste heapul */
void push(int v[],int *n, int element, int *asignari, int *comparatii){
    v[++(*n)] = element;
    int asignari2;

    int i = *n;
    int p = (int)i/2;
    while (p > 0){
        (*comparatii)++;
        if (v[p]>v[i]){
            int tmp = v[p];
            v[p]=v[i];
            v[i]=tmp;
            asignari2++;
        }
        else break;
        i = p;
        p = (int)i/2;
    }
    (*asignari) += asignari2*3;
}


/** constructia heapului unui vector a in b */
void construieste_heap_top_down(int a[], int dimensiune_a, int b[], int asignari, int comparatii){
	int i;
	int dimb = 0;
	for (i=1;i<=dimensiune_a;i++){
		push(b,&dimb,a[i],&asignari,&comparatii);
		printf("Dimensiunea vectorului b este: %d\n", dimb);
		printf("Vectorul b este: \t\t\t"); afisaza_vector(b,dimb);
	}
}

int main()
{
    int min = 1;
    int max = 1000;
    int n;
    srand(time(NULL));

	
	n=10;
	int a[n+1];
	int b[n+1];
	initializeaza_vector(&b,n+1);
	genereaza_vector(&a,n,min,max);
	int comparatii = 0, asignari = 0;

	/** constructie heap */
	int dima = n;
	printf("Vectorul a este: "); afisaza_vector(a,n); printf("\n");
	
	printf("Constructia bottom up a heapului:\n");
	printf("---------------------------------\n");
	construieste_heap_top_down(a,dima,b,&asignari,&comparatii);


    return 0;
}
