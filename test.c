#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#define bytes 4

char *input_string(){
    char *ptr = (char*) malloc (bytes);
    char c;
    int i = 0;
    c = getchar();
    while ((c != '\n') && (c != EOF)){
        ptr[i] = c;
        c = getchar();
        i++;
        if (i % bytes == 0)
            ptr = (char*) realloc(ptr, (i +bytes));
    }
    return ptr;
}

int main(){
    char *ptr = input_string();
    printf("\n%s", ptr);
return 0;
}