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
int p0;
int p1;
int volatile end;
void handler(int){

}
void handler_e(int){
    end++;
}
int main(int argc, char **argv)
{
    signal(SIGALRM, handler_e);
    signal(SIGUSR1, handler);
    p0=getpid();
    alarm(2);
    end = 0;
    p1 = fork();
    if(p1 == -1) return -1;
    if(p1){
        pause();
    } else {
        kill(0, SIGUSR1);
    }
    while(1){
        if (p1){
            printf("Father\n");
            kill(p1, SIGUSR1);
            pause();
            if(end){
                kill(p1, SIGTERM);
                break;
            }
            
        } else {
            pause();
            printf("Son\n");
            kill(0, SIGUSR1);
        }
    }
    end = 0;
    alarm(1);
    while(1){
        printf("Father\n");
        if(end){
            break;
        }
    }
}