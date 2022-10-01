#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <crtdbg.h>

int f(int n, int a[]){
    int c=0;
    for(int i=1; i<n-1; i++) 
        c += (a[i-1]==a[i+1]);
    return c;
}
int f1(int *p, int d){
    int s=0;
    for(int i=0; i<d-1; i++) {
        p+=i+1;
        for(int j=i+1; j<d; j++) {
            s+=*p;
            p++;
        }
    }
    return s;
}
int main() {
    int a[3][3] ={{1, 2, 3},
                  {4, 5, 6},
                  {7, 8, 9}};
    int c = 0;
    int *p;
    p = (int*) malloc(4);
    p = &c;
    c = f1((int*) a, 3);
    printf("%d", c);
    __CrtDumpMemoryLeaks();
    return 0;
}