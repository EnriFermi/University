#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define varSize 4


unsigned long readXXX() {
    char c;
    unsigned long s = 0;
    while (scanf("%c", &c) != EOF){
        if (c <= 'f' && c >= 'a'){
            s += 10 + c - 'a';
        } else if (c <= 'F' && c >= 'A'){
            s += 10 + c - 'A';
        } else if (c <= '9' && c >= '0'){
            s += c - '0';
        }
    }
    return s;
}

int main()
{
    printf("%lu\n",readXXX());
}

