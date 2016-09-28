/**
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
    int asignari2 = 0;

    int i = *n;
    int p = (int)i/2;
    while (p > 0){
        (*comparatii)++;
        if (v[p]>v[i]){
            int tmp = v[p];
            v[p]=v[i];
            v[i]=tmp;
            (*asignari)+=3;
        }
        else break;
        i = p;
        p = (int)i/2;
    }
}


/** constructia heapului unui vector a in b */
void construieste_heap_top_down(int a[], int dimensiune_a, int b[], int asignari, int comparatii){
	int i;
	int dimb = 0;
	for (i=1;i<=dimensiune_a;i++){
		push(b,&dimb,a[i],asignari,comparatii);
	}
}


int main()
{
    int min = 1;
    int max = 1000;
    srand(time(NULL));
	double cinci_double = 5.0;
	int cinci_int = 5;


	int var,n;
	int va[100], vc[100]; // vector asignari si vector comparatii
	initializeaza_vector(&va,100);
	initializeaza_vector(&vc,100);
	for (var = 1; var <= cinci_int ; var++){
		for (n = 100; n <= 10000; n+= 100){
			int comparatii = 0, asignari = 0;
			int a[n+1];
			int b[n+1];
			initializeaza_vector(&b,n+1);
			genereaza_vector(&a,n,min,max);
			
			construieste_heap_top_down(&a,n,&b,&asignari,&comparatii);

			va[n/100-1] += asignari;
			vc[n/100-1] += comparatii;
		}
	}
	/** printarea rezultatelor pentru a genera graficul */
	
    FILE *f;
    f = fopen("grafic.csv","w");
    fprintf(f,"n,comparatii,asignari\n");
    for (n = 0; n<100; n++)
        fprintf(f,"%d00,%.1f,%.1f\n",n+1,vc[n]/cinci_double,va[n]/cinci_double);
    fclose(f); 
    return 0;
}
