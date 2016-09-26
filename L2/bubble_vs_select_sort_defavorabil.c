/**
*   
* @group 
*
* Bubble sort vs select sort caz defavorabil
*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define nl; printf("\n");

void genereaza_vector_defavorabil(int *a,int n,int min,int max){
    int i;
    a[0]=0;
    for (i=1;i<=n;i++)
        a[i]=-i;
    return;
}

void initializeaza_vector(int *a,int n){
    int i;
    for(i=0;i<n;i++)
        a[i] = 0;
}

int main()
{
    /** introducerea dimensiunii vectorului */

    int min = 1;
    int max = 1000;
    int n;

    /** vector comparatii */
    int vc[102];
    /** vector asignari */
    int va[102];

    /** vector comparatii select sort */
    int vcs[102];
    /** vector asignari select sort */
    int vas[102];

    initializeaza_vector(&vc,101);
    initializeaza_vector(&va,101);
    initializeaza_vector(&vcs,101);
    initializeaza_vector(&vas,101);

    int var;
    for (var = 0; var<5;var++){
        for (n = 100; n<=10000; n+=100){
            int a[n+2];


            genereaza_vector_defavorabil(&a,n+1,min,max);

            /** bubble sort */
            int comparatii = 0;
            int asignari = 0;
            int j,k,i;
            int o = 0;
            for (i = 1; i < n && o == 0; i++){
                /*o = 1;*/
                for (j = n; j >= i+1; j--){
                    if (a[j]<a[j-1]){
                        k = a[j];
                        a[j] = a[j-1];
                        a[j-1] = k;
                        asignari++;
                        o = 0;
                    }
                    comparatii++;
                }
            }

            va[n/100-1] += asignari*4;
            vc[n/100-1] += comparatii;





            /** generarea unui vector cu valori aleatorii */
            genereaza_vector_defavorabil(&a,n+1,min,max);
            i,j,k;
            comparatii = 0;
            asignari = 0;
            /**select sort*/
            for (j = 0; j < n-1; j++) {
                int iMin = j;
                asignari++;
                for ( i = j+1; i < n; i++) {
                    comparatii++;
                    if (a[i] < a[iMin]) {
                        iMin = i;
                        asignari++;
                    }
                }
                comparatii++;
                if(iMin != j) {
                    k = a[j];
                    a[j]=iMin;
                    iMin=k;
                    asignari+=3;
                }
            }

            vas[n/100-1] += asignari;
            vcs[n/100-1] += comparatii;
        }
    }


    var = 5;
    /** printarea rezultatelor pentru a genera graficul */
    FILE *f;
    f = fopen("grafic.csv","w");
    fprintf(f,"n,comparatii bubble,asignari bubble, comparatii sort, asignari sort\n");
    for (n = 1; n<=100; n++)
        fprintf(f,"%d00,%f,%f,%f,%f\n",n,(vc[n-1])/((double)var),va[n-1]/((double)var),(vcs[n-1])/((double)var),vas[n-1]/((double)var));
    fclose(f);
    return 0;
}
