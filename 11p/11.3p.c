#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <sys/fcntl.h>
#include <sys/wait.h>

int execute(char *arg) {
    int p = fork();
    if(p==0){
        int x = execlp(arg, arg, NULL);
        exit(x);
    }
    int status;
    waitpid(p, &status, 0);
    return status;
}
int valid(int status){
    int exit = WIFEXITED(status);
    int exit_status = WEXITSTATUS(status);
    return (exit == 1)&&(exit_status == 0);
}
int main(int argc, char **argv){
    if(argc != 4){
        exit(1);
    }
    int status1 = valid(execute(argv[1]));
    int status2;
    if(status1 != 1){
        status2 = valid(execute(argv[2]));
    } else {
        status2 = 0;
    }
    int status12 = !status1?status2:1;
    int status3;
    if(status12){
        status3 = valid(execute(argv[3]));
    } else {
        status3 = 0;
    }
    if((status12?status3:0) == 1){
        exit(0);
    } else {
        exit(1);
    }
}