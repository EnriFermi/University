#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define varSize 4

void standartPrint(int x, int n){
    
}

void multiTable(long long a, long long b, int n) {
    //Заголовок
    for(long long i = 0; i<n; i++){
        printf(" ");
    }
    for(long long i=a; i<b; i++){
        printf(" %*lld", n, i);
    }
    printf("\n");
    //Основные строки
    for(long long i=a; i<b; i++){
        
        printf("%*lld", n, i);
        for(long long j=a; j<b; j++){
            long long mult = j*i;
            printf(" %*lld", n, mult);
        }
        printf("\n");
    }
}

int main()
{
    long long a, b;
    int n;
    scanf("%lld %lld %d", &a, &b, &n);
    multiTable(a, b, n);
}

