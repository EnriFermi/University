#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define varSize 4
#define mnSize 6
char* f(){
    char c;
    int pointer=0;
    char* p = (char *) malloc(varSize);
    do {
        c = getchar();
        if((c == '\n')||(c == EOF)){
            break;
        }
        p[pointer]=c;
        pointer++;
        if(pointer%varSize == 0)
            p = (char *) realloc(p, pointer+varSize);
    } while (1==1);
    p[pointer] = '\0';
    return p;
}
int* f1(int m, int n){
    int* p = (int *) malloc(m*n*sizeof(int));
    int min = m < n? m : n, counter = 1;
    for(int square=0; square < (min+1)/2; square++) {
        for(int i=square; i<= n-square-1; i++) {
            p[square*n + i] = counter;
            counter++;
        }
        if(counter > m*n){
            break;
        }
        for(int j=square+1; j<= m-square-2; j++){
            p[j*n + (n-square-1)] = counter;
            counter++;
        }
        if(counter > m*n){
            break;
        }
        for(int i=n-square-1; i >= square; i--){
            p[(m-square-1)*n + i]= counter;
            counter++;
        }
        if(counter > m*n){
            break;
        }
        for(int j=m-square-2; j >= square+1; j--){
            p[j*n + square] = counter;
            counter++;
        }
        if(counter > m*n){
            break;
        }
    }
    return p;
}
int main() {
    int mn[mnSize] ={7, 7, 5, 5, 5, 6};
    int m, n;
    for(int k=0; k<mnSize; k+=2){
        m = mn[k];
        n = mn[k+1];
        int* a = f1(m, n);
        printf("%d X %d\n", m, n);
        for(int i=0; i<m; i++) {
            for(int j=0; j<n; j++){
                printf("%d ", a[i*n + j]);
            }
            printf("\n");
        }
    }
}



//-----------------

