#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define varSize 4

typedef struct lineStruct
{
    int offset;
    int size;
} lineData;


lineData *set(FILE *file, int size, int *maxSize){
    fseek(file, 0, SEEK_SET);
    lineData *p = malloc((size+1)*sizeof(lineData));
    p[0].offset = 0;
    maxSize[0] = 0;
    int lineS = 0, i = 1, lineSprev = 0;
    char c;
    while ((c = fgetc(file)) != EOF)
    {
        printf("%c", c);
        lineS++;
        if(c == '\n')
        {
            p[i-1].size = lineS-lineSprev;
            maxSize[0] = (maxSize[0] < lineS-lineSprev) ? lineS-lineSprev : maxSize[0];
            p[i].offset = lineS;
            lineSprev = lineS;
            i++;
        }
    }
    p[i-1].size = 0;
    return p;
}

int main(int argc, char **argv)
{
    
    if(argc < 2){
        return 0;
    }
    FILE *f = fopen(argv[1], "r+");
    char c;
    int size = 0, isenter = 0;
    while ((c = fgetc(f)) != EOF)
    {
        isenter = 0;
        if(c == '\n')
        {
            size ++;
            isenter = 1;
        }
    }
    if(!isenter){
        fputc('\n', f);
    }
    fflush(f);
    int maxLineSize = 0;
    lineData *sizes = set(f, size, &maxLineSize);
    int contin, lineNum;
    
    FILE *f1 = fopen("output.txt", "w+");
    lineData buffer;
    char* s = malloc(maxLineSize+1);
    // Сортировка по размеру(шаблон тот же, другой признак сравнения)
    /*
    for(int i = 0; i<size; i++){
        for(int j = i+1; j<size; j++){
            if(sizes[i].size > sizes[j].size){
                buffer = sizes[j];
                sizes[j] = sizes[i];
                sizes[i] = buffer;
            }
        }
    }
    */
    // Сортировка лексикографически
    /*
    char* s1= malloc(maxLineSize+1);
    for(int i = 0; i<size; i++){
        for(int j = i+1; j<size; j++){
            fseek(f, sizes[j].offset, SEEK_SET);

            fgets(s1, sizes[j].size, f);
            fseek(f, sizes[i].offset, SEEK_SET);
            
            fgets(s, sizes[i].size, f);
            if(strcmp(s, s1) > 0){
                buffer = sizes[j];
                sizes[j] = sizes[i];
                sizes[i] = buffer;
            }
        }
    }*/
    fseek(f, 0, SEEK_SET);
    for(int i=0; i<size; i++){
        fseek(f, sizes[i].offset, SEEK_SET);
        fgets(s, sizes[i].size, f);
        fputs(s, f1);
        fputc('\n', f1);
    }
    free(sizes);
    fclose(f);
    return 0;
}
