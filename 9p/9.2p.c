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
char* f(char *p){
    char c;
    int pointer=0;
    do {
        c = getchar();
        if((c == '\n')||(c == EOF)){
            break;
        }
        p[pointer]=c;
        pointer++;
    } while (1==1);
    p[pointer] = '\0';
    return p;
}
int main(int argc, char **argv)
{
    if(argc < 2){
        return 0;
    }
    //?  
    int file = open(argv[1], O_WRONLY|O_CREAT|O_TRUNC, 0666);
    dup2(file, 1);
    //?
    int p_to_s[2], s_to_p[2];
    pipe(p_to_s);
    pipe(s_to_p);

    int p1 = fork();
    if(p1 == -1) return -1;
    if(p1 == 0){
        close(p_to_s[1]);
        close(s_to_p[0]);
        char c, *str = malloc(80), res;
        int str_len;
        int flag;
        
        do {
            read(p_to_s[0], &c, 1);
            read(p_to_s[0], &str_len, sizeof(int));
            read(p_to_s[0], str, str_len);
            str[str_len] = '\0'; 
            if(strcmp(str, "exit")){
                flag = 0;
                res = 1;
                for (int i = 0; i < str_len; i++){
                    flag += str[i] == c;
                }
                printf("%d\n", flag);
                fflush(stdout);
                
            } else {
                res = 0;
            }
            write(s_to_p[1], &res , 1);
        } while(res);
        close(p_to_s[0]);
        close(s_to_p[1]);
        close(file);
        return 0;
    }
    close(p_to_s[0]);
    close(s_to_p[1]);
    int son_answer, str_len;
    char c, *str = malloc(80), res;
    do{
        scanf("%c", &c);
        getchar();
        f(str);
        str_len = strlen(str);
        if(strcmp(str, "exit")){
            printf("%s\n", str);
            fflush(stdout);
        }
        write(p_to_s[1], &c, 1);
        write(p_to_s[1], &str_len, sizeof(int));
        write(p_to_s[1], str, str_len);
        read(s_to_p[0], &res, 1);
    } while(res);
    close(p_to_s[1]);
    close(s_to_p[0]);
    close(file);
    wait(0);
}