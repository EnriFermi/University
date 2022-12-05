#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define varSize 4
//Получает из стандартоного ввода строку
char* getString(){
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
//Находит последнее вхождение строки в строку
char* last(char * str, char * strj){
    int i = 0, flag=0, j = 0, size = strlen(str);
    char c, cj;
    char * p = NULL;
    while (str[i] != '\0') {
        c = str[i];
        cj = strj[j];
        if(cj == '\0'){
            p = str+i-j;
            j = 0;
            cj = strj[j];
        }
        //printf("%c %c %d %d\n", c, cj, i, j);
        if(c == cj){
            j++;
        } else {
            j = 0;
        }
        i++;
    };
    if(strj[j] == '\0'){
        p = str+i-j;
    }
    if(strj[0] == '\0')
    {
        return str+i+1;
    }
    return p;
}
//Находит первое вхождение строки
char* first(char * str, char * strj){
    int i = 0, flag=0, j = 0;
    char c, cj;
    char * p = NULL;
    if(strj[0] == '\0')
    {
        return str;
    }
    while (str[i] != '\0') {
        c = str[i];
        cj = strj[j];
        if(cj == '\0'){
            p = str+i-j;
            break;
        }
        //printf("%c %c %d %d\n", c, cj, i, j);
        if(c == cj){
            j++;
        } else {
            j = 0;
        }
        i++;
    };
    if(strj[j] == '\0'){
        p = str+i-j;
    }
    return p;
}
//Удаляет все вхождения в строку данной строки(реализовал отдельную функцию first, так как это оптимальнее, чем last в моей реализации)
char* delete(char * str, char *strd){
    int i = 0, strSize = strlen(strd), j=0;
    char * pointer = first(str, strd);
    char * buffer = malloc(varSize);
    if(strd[0] == '\0') {
        free(buffer);
        return str;
    }
    while (pointer != NULL) {
        while (str + i != pointer){
            buffer[j] = str[i];
            j++;
            if(j%varSize == 0) {
                buffer = (char *) realloc(buffer, j+varSize);
            }
            i++;
        }
        i+=strSize;
        pointer = first(str+i, strd);
    }
    while(str[i]!='\0'){
        buffer[j] = str[i];
        j++;
        if(j%varSize == 0) {
            buffer = (char *) realloc(buffer, j+varSize);
        }
        i++;
    }
    buffer[j]='\0';
    free(str);
    return buffer;
}

int main() {
    char *res, *c, *cj;
    c = getString();
    cj = getString();
    // res = last(c, cj); 1 задача
    res = delete(c, cj); // 2 задача
    printf("\n%s", res);
    return 0;
}