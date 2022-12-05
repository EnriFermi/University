#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <sys/fcntl.h>
#include <sys/wait.h>

int main(int argc, char **argv){
    if(argc != 6){
        exit(1);
    }
    /** brackets*/
    int fd[2];
    pipe(fd);
    int p1 = fork();
    if(p1 == 0) {
        close(fd[0]);
        dup2(fd[1], 1);
        close(fd[1]);
        int fin = 0;
        fin = open(argv[4], O_RDONLY, S_IRWXU);
        if(fin == -1){
            exit(1);
        }
        dup2(fin, 0);
        close(fin);
        int x = execlp(argv[1], argv[1], NULL);
        exit(x);
    }
    int p3 = fork();
    if(p3 == 0) {
        close(fd[1]);
        dup2(fd[0], 0);
        close(fd[0]);
        int fin = 0;
        fin = open(argv[5], O_CREAT|O_WRONLY|O_APPEND, S_IRWXU);
        dup2(fin, 1);
        close(fin);
        int x = execlp(argv[3], argv[3], NULL);
        exit(x);
    }
    close(fd[0]);
    int status, status3 = 1;
    waitpid(p1, &status, 0);

    if(WIFEXITED(status)){
        status = WEXITSTATUS(status);
    }
    if(status){
        close(fd[1]);
        waitpid(p3, &status3,0);
		if (WIFEXITED(status3)) {
			status3 = WEXITSTATUS(status3);
		}
		exit(status3);
    }
    int p2 =fork();
    if(p2 == 0) {
		dup2(fd[1],1);
		close(fd[1]);
		execlp(argv[2],argv[2],NULL);
		exit(1);
	}
    close(fd[1]);
	waitpid(p2,&p2,0);
	waitpid(p3,&status3,0);
	if ( WIFEXITED(status3) )
		status3 = WEXITSTATUS(status3);
	exit(status);
}