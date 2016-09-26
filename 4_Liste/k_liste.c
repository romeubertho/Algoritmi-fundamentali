#include <stdio.h>
#include <stdlib.h>


typedef struct tip_nod{
    int v; // valoarea
    int l; // lista din care face parte
    struct tip_nod *d; // nodul drept
} nod;


/** crearea unui nod */
nod *creare_nod(int lista, int max){
    nod *p;
    p =(nod*) malloc (sizeof(nod));

    if (p == 0){
        printf("\nEroare: nu s-a alocat memorie in heap!");
        return 0;
    }

    p->d = 0;

    p->v = intreg_aleator(max-10,max-1);
    p->l = lista;
    return p;
}


/** seteaza valorile unui vector la 0 */
void initializeaza_vector(int *a,int n){
    int i;
    for(i=0;i<n;i++)
        a[i] = 0;
}


/** returneaza un intreg cuprins intre min si max */
int intreg_aleator(int min, int max){
    return rand() % (max-min+1) + min;
}


/** adauga un element in heap si reconstruieste heapul */
void push(int v[],int *n, int element){
    v[++(*n)] = element;

    int i = *n;
    int p = (int)i/2;
    while (p > 0){
        if (v[p]>v[i]){
            int tmp = v[p];
            v[p]=v[i];
            v[i]=tmp;
        }
        else break;
        i = p;
        p = (int)i/2;
    }
}

/** returneaza indice fiu stang */
int stanga(int i){
	return 2*i;
}

/** returneaza indice fiu drept */
int dreapta(int i){
	return 2*i+1;
}

/** max_heapify - cormen 3ed pag 154 */
void max_heapify(int *A, int *B, int i, int *h){
	int ivm, s, d; //indicele valorii maxime, fiu stang, fiu drept

	s = stanga(i);
	d = dreapta(i);

	if(s <= *h && A[s] > A[i])
		ivm =  s;
	else
		ivm = i;

	if ((d <= *h)&&(A[d] > A[ivm]))
		ivm = d;

	if(ivm != i){
		int tmp;
		tmp = A[ivm];
		A[ivm] = A[i];
		A[i] = tmp;

        tmp = B[ivm];
		B[ivm] = B[i];
		B[i] = tmp;

		max_heapify(A,B, ivm, h);
	}
}

/** constructie heap - cormen 3ed pagina 157*/
void build_max_heap(int *A, int *B, int n, int *h){
	*h=n-1;
	int i;
	for (i=n/2;i>0;i--)
		max_heapify(A,B,i,h);
}

/** afisaza un vector in consola */
void avc(char *c,int v[], int n){
	int i;
	printf("%s\n",c);
	for (i=1;i<n;i++){
		printf("v[%d]=%d\n",i,v[i]);
	}
	printf("\n");
}

/** main */
int main()
{
    srand(time(NULL));

    int k;
    int n;

/** citeste k si n */
    do{
        printf("k = ");
        scanf("%d", &k);
        printf("n = ");
        scanf("%d", &n);
    } while (k>=n);


    nod* a[k]; // radacina listei
    nod* u[k]; // ultimul element din lista

    int i;
/** construieste listele */
    int ll[k]; //lungimea fiecarei liste

    for (i=0;i<k;i++){
        ll[i] = 0;
    }

    nod *p;
    for (i=0;i<k;i++){
        p = creare_nod(i,1000);
        a[i] = p;
        u[i] = a[i];
        ll[i]++;
    }

    i = 0;

    int lc;
    while (i<n-k){
        lc = intreg_aleator(0,k-1); //index lista curenta
        ll[lc]++;
        p = creare_nod(lc,u[lc]->v);    //se creaza un nod de valoare mai mare decat valoarea ultimului element din lista de indice lc
        u[lc]->d = p;                   //se adauga nodul p in coada listei
        u[lc]=p;
        i++;
    }


    int v[n]; //vectorul sortat
    initializeaza_vector(&v, n);

    int h[k+1]; //heapul folosit
    int hi[k+1]; //indicele corespunzator listei din care se ia valoarea pusa in h

/** construieste heap */
    i = 0;
    for (i=0;i<k;i++){
        h[i+1] = a[i]->v;
        hi[i+1] = i;
    }

    int ii;
    int j;

    ii = 0;
    int sp;

    for (i=0;i<n;i++){
        if (n-i < k)
            sp = k-n+i;
        else
            sp = 0;

        build_max_heap(h,hi,k+1-sp,&ii);
        v[i] = h[1];
        if  (i == n-1)
            break;

        ll[hi[1]]--;
        a[hi[1]] = a[hi[1]]->d;

        for (j=0;j<k;j++){
            if (ll[(hi[1]+j)%k] > 0){
                hi[1] = (hi[1]+j)%k;
                h[1] = a[hi[1]]->v;
                break;
            }
        }
    }
    avc("\nv: ",v,n);
    return 0;
}
