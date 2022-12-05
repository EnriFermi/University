#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define varSize 4

typedef struct lineStruct
{
    int offset;
    int size;
} lineData;


lineData *set(FILE *file, int* size, int *maxSize){
    fseek(file, 0, SEEK_SET);
    lineData *p = malloc(sizeof(lineData)*2);
    p[0].offset = 0;
    maxSize[0] = 0;
    int lineS = 0, i = 1, lineSprev = 0;
    char c;
    while ((c = fgetc(file)) != EOF)
    {
        lineS++;
        if(c == '\n')
        {
            p = (lineData *) realloc(p, (i+1)*sizeof(lineData));
            p[i-1].size = lineS-lineSprev;
            maxSize[0] = (maxSize[0] < lineS-lineSprev) ? lineS-lineSprev : maxSize[0];
            p[i].offset = lineS;
            lineSprev = lineS;
            i++;
        }
    }
    size[0] = i-1;
    p[i-1].size = 0;
    return p;
}

char * skip_space(char *s){
    int i = 0;
    while(s[i]!='\0'&&s[i]==' '){
        i++;
    }
    return s + i;
}

void caps_lock(char *s){
    int i = 0;
    char c = s[i];
    while(c !='\0'){
        if('a' <= c && c <= 'z'){
            s[i] = c - 32;
        }
        i++;
        c = s[i];
    }
}
int strcmp_imp(char* s1, char* s2, int* flags){
    if(flags[1]){ //убираем пробелы
        s1 = skip_space(s1);
        s2 = skip_space(s2);
    }
    if(flags[2]){//капслочим
        caps_lock(s1);
        caps_lock(s2);
    }
    if(flags[0]){//есть ри реверс
        return (-1)*strcmp(s1, s2);
    } else {
        return strcmp(s1, s2);
    }

}
// 0 - реверс
// 1 - изначальные пробелы игнорируются
// 2 - малые буквы в большие
// 3 - не в стандарт а в файл
//закрывает файл на чтение
//не открывает  файл на запись
void sortf(int *flags, FILE* infile, FILE* outfile){
    if(infile == NULL){
        return;
    }
    int lcount, maxLineSize;
    lineData buffer;
    lineData *linemap = set(infile, &lcount, &maxLineSize);
    char* s = malloc(maxLineSize+1);
    char* s1= malloc(maxLineSize+1);
    for(int i = 0; i<lcount; i++){
        for(int j = i+1; j<lcount; j++){
            fseek(infile, linemap[j].offset, SEEK_SET);
            fgets(s1, linemap[j].size, infile);
            fseek(infile, linemap[i].offset, SEEK_SET);
            fgets(s, linemap[i].size, infile);
            if(strcmp_imp(s, s1, flags) > 0){
                buffer = linemap[j];
                linemap[j] = linemap[i];
                linemap[i] = buffer;
            }
        }
    }
    fseek(infile, 0, SEEK_SET);
    for(int i=0; i<lcount; i++){
        fseek(infile, linemap[i].offset, SEEK_SET);
        fgets(s, linemap[i].size, infile);
        if(flags[3]){
            fputs(s, outfile);
            fputc('\n', outfile);
        } else {
            printf("%s\n", s);
        }
    }
    free(s);
    free(s1);
    free(linemap);
    fclose(infile);
}
FILE **procArgv(int argc, char **argv, int flags[][4], FILE **outfile, char **ofilename, int *fcount){
    int i, changed = 0;
    for(i=1; i<argc; i++){
        if(argv[i][0] != '-' && strlen(argv[i]) == 2){
            break;
        }
        changed = 1;
        switch (argv[i][1])
        {
        case 'r':
            flags[0][0] = 1;
            break;
        case 'b':
            flags[0][1] = 1;
            break;
        case 'f':
            flags[0][2] = 1;
            break;
        case 'o':
            flags[0][3] = 1;
            if(argc>i+1){
                ofilename[0] = argv[i+1];
                outfile[0] = fopen("__temp__.txt", "w");
            }
            i++;
            break;
        default:
            changed = 0;
            break;
        }
        if(!changed){
            break;
        }
    }
    FILE **files = malloc(sizeof(FILE*)*(argc-i));
    for(int j=i; j<argc; j++){
        files[j-i]=fopen(argv[j], "r+");
    }
    fcount[0] = argc - i;
    return files;
}
int main(int argc, char **argv)
{
    if(argc < 2){
        return 0;
    }
    char *ofilename = NULL;
    int flags[4] = {0,0,0,0};
    int fcount = 0;
    FILE *outfile = NULL;
    FILE **files = procArgv(argc, argv, &flags, &outfile, &ofilename, &fcount);
    if(files == NULL || (ofilename == NULL && flags[3] == 1)){// ошибка
        return 0;
    }
    for(int i=0; i<fcount; i++){
        sortf(flags, files[i], outfile);
    }
    if(flags[3]){
        fclose(outfile);
        if(strcmp(ofilename, "___temp__.txt") != 0){
            if(remove(ofilename) == 0) { // вдруг файл для записи не удалось открыть
                rename("__temp__.txt", ofilename);
            } else {
                remove("__temp__.txt");
            }
        }
    }
}
