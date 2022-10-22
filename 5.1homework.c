#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define varSize 4

#define BINPRINT(x)                                \
    do                                             \
    {                                              \
        int __i = 0;                               \
        signed long long __p = x;                  \
        char *__c = malloc(varSize);               \
        if (__p < 0)                               \
        {                                          \
            __p = -1 * __p;                        \
            printf("-");                           \
        }                                          \
        while (__p > 0)                            \
        {                                          \
            __c[__i] = '0' + __p % 2;              \
            __p = __p / 2;                         \
            __i++;                                 \
            if (__i % varSize == 0)                \
                __c = realloc(__c, __i + varSize); \
        }                                          \
        for (int __j = __i - 1; __j >= 0; __j--)   \
            printf("%c", __c[__j]);                \
        free(__c);                                 \
    } while (0)

int main()
{
    char c = -3;
    if(c) BINPRINT(c); else printf("Zero!\n");
    printf("\n");
    BINPRINT((short)7);
    printf("\n");
    long x = 15;
    if(x)BINPRINT(x); else printf("Zero!\n");
    printf("\n");
    BINPRINT((long long)x);
    printf("\n");
    return 0;
}

