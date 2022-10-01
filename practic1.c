#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define size 4

char* f(char * str){
    int i = 0, flag = 0, j=0, spaceflag = 0, existflag=0;
    char *buffer = malloc(size);
    char c = str[i];
    while (str[i] != '\0') {
        c = str[i];
        if(c == ' ') {
            if(spaceflag == 0 && existflag == 1) {
                if(flag == 1) {
                    buffer[j] = ' ';
                    j++;
                }
                flag = (flag + 1)%2;
                spaceflag = 1;
            }
        } else {
            if(existflag == 0)
                existflag = 1;
            spaceflag = 0;
        }
        if((flag == 1)&&(spaceflag ==0)) {
            buffer[j] = c;
            j++;
            if(j%4 == 0) {
                buffer = (char *) realloc(buffer, j+size);
            }
        }
        i++;
    };
    free(str);
    return buffer;
}

int main() {
    char c = 255;
    unsigned c1 = 255; 
    int x = c;
    int *y;
    int a[9];
    printf(": %d\n", c == c1);
    printf("char: %d\n", sizeof(char));
    printf("%d\n", sizeof(x));
    printf("%d\n", sizeof(y));
    printf("%d\n", sizeof(a));
    printf("x before: %d\n", x);
    printf("increment: %ld\n", sizeof(x++));
    printf("x after: %d\n", x);
    unsigned int z = 0xFFFFFFFF;
    int v = z;
    printf("M=N: %d\n", v);
    short h = z;
    printf("M>N : %d\n", h);
    unsigned short p = 0xFFFF;
    v = p;
    printf("M<N: %d\n", v);
    /*
    char *c = malloc(500);
    scanf("%[^\n]s", c);
    c = f(c);
    printf("%s", c);
    return 0;
    */
}