#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

#define offset 4
#define varSize 4
char* in_str(){
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
void fencrypt(){
    getchar();
    printf("Input file name: \n");
    char *file_name = in_str();
    FILE *file = fopen(file_name, "r+");
    if(file == NULL){
        free(file_name);
        printf("Incorrect file name\n");
        fclose(file);
    }
    FILE *buf_file = fopen("___temp___", "w");
    if(buf_file == NULL){
        free(file_name);
        printf("Creating buffer problems\n");
        fclose(file);
        fclose(buf_file);
    }
    char c, res_c;
    while((c = fgetc(file)) != EOF){
        if('a' <= c && c <= 'z'){
            res_c = 'a' + (c-'a'+offset) % 26;
        } else if('A' <= c && c <= 'Z'){
            res_c = 'A' + (c-'A'+offset) % 26;
        } else if(c == ' ' || c == '\n'){
            res_c = c;
        } else {
            free(file_name);
            printf("Incorrect input\n");
            fclose(file);
            fclose(buf_file);
            remove("___temp___");
            return;
        }
        putc(res_c, buf_file);
    }
    fclose(buf_file);
    fclose(file);
    remove(file_name);
    rename("___temp___", file_name);
    free(file_name);
}
void fdecrypt(){
    getchar();
    printf("Input file name: \n");
    char *file_name = in_str();
    FILE *file = fopen(file_name, "r+");
    if(file == NULL){
        free(file_name);
        printf("Incorrect file name\n");
        fclose(file);
    }
    FILE *buf_file = fopen("___temp___", "w");
    if(buf_file == NULL){
        free(file_name);
        printf("Creating buffer problems\n");
        fclose(file);
        fclose(buf_file);
    }
    char c, res_c;
    while((c = fgetc(file)) != EOF){
        if('a' <= c && c <= 'z'){
            res_c = 'a' + (c-'a'-offset) % 26;
        } else if('A' <= c && c <= 'Z'){
            res_c = 'A' + (c-'A'-offset) % 26;
        } else if(c == ' ' || c == '\n'){
            res_c = c;
        } else {
            free(file_name);
            printf("Incorrect input\n");
            fclose(file);
            fclose(buf_file);
            remove("___temp___");
            return;
        }
        putc(res_c, buf_file);
    }
    fclose(buf_file);
    fclose(file);
    remove(file_name);
    rename("___temp___", file_name);
    free(file_name);
}
void fout(){
    getchar();
    printf("Input file name: \n");
    char *file_name = in_str();
    FILE *file = fopen(file_name, "r+");
    if(file == NULL){
        free(file_name);
        printf("Incorrect file name\n");
        fclose(file);
    }
    char c;
    while((c = fgetc(file)) != EOF){
        printf("%c", c);
    }
    free(file_name);
    fclose(file);
}
void (**func_list)();
char ** line_list;
void c_exit(){
    free(line_list);
    free(func_list);
    exit(0);
}

// TODO сделать обработку исключений DONE
// TODO сделать освобождение памяти DONE
void menu(int m_size, ...) {
    if(m_size%2 != 0) {
        free(line_list);
        free(func_list);
        exit(1);
    }
    va_list arg_list;
    va_start(arg_list, m_size);
    func_list= malloc(m_size*sizeof(void (*)()));
    line_list = malloc(m_size*sizeof(char*));
    for(int i=0; i<m_size; i++){
        line_list[i] = va_arg(arg_list, char *);
        printf("%d) %s\n", i+1, line_list[i]);
        func_list[i] = va_arg(arg_list, void (*)());
    } 
    va_end(arg_list);
    int message;
    while(1){
        scanf("%d", &message);
        func_list[message-1]();
    }
}
int main(int argc, char **argv)
{
    menu(4, "Output file", fout, "Encrypt file", fencrypt, "Decrypt file", fdecrypt, "Exit menu", c_exit);
}
