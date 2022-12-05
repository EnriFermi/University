#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <limits.h>
#include <fcntl.h>
#include <signal.h>
#define varSize 4
char* f(char *isEnd){
    char c;
    int pointer=0;
    char* p = (char *) malloc(varSize);
    do {
        c = getchar();
        //read(0, &c, 1);
        if((c == '\n')||(c == EOF)){
            isEnd[0] = (char) (c != EOF);
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
char* reverse(char *str, int size){
    char buffer;
    for(int i=0; i<size/2; i++){
        buffer = str[i];
        str[i] = str[size-1-i];
        str[size-1-i] = buffer;
    }
}
int main(int argc, char **argv)
{
    if(argc < 2){
        return 0;
    }
    //?  
    int in_file = open(argv[1], O_RDONLY, 0666);
    int out_file = open("___temp___", O_WRONLY|O_CREAT|O_TRUNC, 0666);
    dup2(in_file, 0);
    dup2(out_file, 1);
    //?
    int p_to_s[2], s_to_p[2];
    pipe(p_to_s);
    pipe(s_to_p);

    int p1 = fork();
    if(p1 == -1) return -1;
    if(p1 == 0){
        close(out_file);
        close(in_file);
        close(p_to_s[1]);
        close(s_to_p[0]);
        char is_cont, *str, res;
        int str_len;
        do {
            read(p_to_s[0], &is_cont, 1);
            read(p_to_s[0], &str_len, sizeof(int));
            str = malloc(str_len+1);
            read(p_to_s[0], str, str_len);
            str[str_len] = '\0'; 
            reverse(str, str_len);
            write(s_to_p[1], str, str_len);
            free(str);
        } while(is_cont);
        close(p_to_s[0]);
        close(s_to_p[1]);
        return 0;
    }
    close(p_to_s[0]);
    close(s_to_p[1]);
    int son_answer, str_len;
    char *str, is_cont;
    do{
        str = f(&is_cont);
        str_len = strlen(str);
        write(p_to_s[1], &is_cont, 1);
        write(p_to_s[1], &str_len, sizeof(int));
        write(p_to_s[1], str, str_len);
        read(s_to_p[0], str, str_len);
        //reverse(str, str_len);
        printf("%s", str);
        if(is_cont != 0 || str_len != 0){
            printf("\n");
        }
        fflush(stdout);
        free(str);
    } while(is_cont);
    close(p_to_s[1]);
    close(s_to_p[0]);
    close(in_file);
    close(out_file);
    wait(0);
    remove(argv[1]);
    rename("___temp___", argv[1]);
}