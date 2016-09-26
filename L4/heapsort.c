#include <stdio.h>

/** returneaza indice fiu stang */
int stanga(int i){
	return 2*i;
}

/** returneaza indice fiu drept */
int dreapta(int i){
	return 2*i+1;
}

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

/** max_heapify - cormen 3ed pag 154 */
void max_heapify(int *A, int i, int *h, int *asignari, int *comparatii){
	int ivm, s, d; //indicele valorii maxime, fiu stang, fiu drept
	
	s = stanga(i);
	d = dreapta(i);
	
	(*comparatii)++;
	if(s <= *h && A[s] > A[i])
		ivm =  s;
	else
		ivm = i;
	
	(*comparatii)++;
	if ((d <= *h)&&(A[d] > A[ivm]))
		ivm = d;
	
	(*comparatii)++;
	if(ivm != i){
		int tmp;
		tmp = A[ivm];
		A[ivm] = A[i];
		A[i] = tmp;
		max_heapify(A, ivm, h,asignari,comparatii);
		(*asignari) += 3;
	}
}

/** constructie heap - cormen 3ed pagina 157*/
void build_max_heap(int *A, int n, int *h,int * asignari, int *comparatii){
	*h=n-1;
	int i;
	for (i=n/2;i>0;i--)
		max_heapify(A,i,h,asignari,comparatii);	
}

/** heap sort - cormed 3ed pag 160 */
void heap_sort(int *A, int n, int *h, int *asignari, int *comparatii){
	build_max_heap(A,n,h,asignari,comparatii);
	int i;
	for(i = n - 1; i > 0; i--){
		int tmp = A[0];
		A[0] = A[i];
		A[i] = tmp;
		*h = *h - 1;
		(*asignari) += 3;
		max_heapify(A,0,h,asignari,comparatii);
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
			int a[n+2];
			genereaza_vector(&a,n+1,min,max);
			//afisaza_vector_in_consola(" =========== a:",a,n+1);

			int dim = 0; // dimensiune heap
			heap_sort(a, n+2, &dim, &asignari, &comparatii);

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
