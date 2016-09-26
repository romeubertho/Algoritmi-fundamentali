/*
 *  , 
 * 
 * 
 * Laboratorul 4 - Quicksort
 */

#include <stdio.h>

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
    for(i=0;i<=n;i++)
        a[i] = 0;
}

int partitioneaza(int a[], int p, int r, int *asignari, int *comparatii){
	int i,j;
	i = p-1;
	int x = a[r];
	
	for(j=p;j<r;j++){
		(*comparatii)++;
		if(a[j] <= x){
			i++;
			int tmp = a[i];
			a[i] = a[j];
			a[j] = tmp;
			(*asignari) += 3;
		}
	}

	a[r] = a[i+1];
	a[i+1] = x;
	(*asignari)+=2;
	
	return i + 1;
}

void quick_sort(int a[], int p, int r,int *asignari, int *comparatii){
	(*comparatii)++;
	if(p < r){
		int q = partitioneaza(a,p,r,asignari,comparatii);
		quick_sort(a,p,q-1,asignari,comparatii);
		quick_sort(a,q+1,r,asignari,comparatii);
	}	
}

/** afisaza un vector in consola */
void afisaza_vector_in_consola(char *c,int v[], int n){
	int i;
	printf("%s\n",c);
	for (i=1;i<n;i++){
		printf("v[%d]=%d\n",i,v[i]);
	}
	printf("\n");
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
			genereaza_vector(&a,n+1,min,max);
			//afisaza_vector_in_consola(" =========== a:",a,n+1);

			quick_sort(a,1,n,&asignari,&comparatii);

			//afisaza_vector_in_consola("a: ---------------------",a,n+1);


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
