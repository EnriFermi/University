#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define varSize 4

int contains(char *str, char c){
    int contains = 0;
    for(int i=0; i< strlen(str); i++) {
        if(str[i]==c){
            contains = 1;
            break;
        }
    }
    return contains;
}

int main(int argc, char **argv)
{
    if(argc < 3){
        return 0;
    }
    FILE *f = fopen(argv[1], "r"), *f1 = fopen("_____file______.txt", "w");;
    char c;
    int size = 0, contain = 0;
    while ((c = fgetc(f)) != EOF)
    {
        if(c == '\n')
        {
            if(!contain){
                fseek(f, (-1)*size-1, SEEK_CUR);
                for(int i=0; i<size+1; i++){
                    fputc(fgetc(f), f1);
                }
            }
            contain = 0;
            size = -1;
        }
        if(c == argv[2][0]) {
            contain = 1;
        }
        size++;
    }
    if (!contain)
    {
        fseek(f, (-1) * size-1, SEEK_CUR);
        for (int i = 0; i < size+1; i++)
        {
            fputc(fgetc(f), f1);
        }
    }
    fclose(f);
    fclose(f1);
    remove(argv[1]);
    rename("_____file______.txt", argv[1]);
    return 0;
}
