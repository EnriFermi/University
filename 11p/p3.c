#include <signal.h>
#include <sys/wait.h>
#include <sys/file.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
	int a, son1, son2, son3;
	int p[2];
	pipe(p);
	
	if( (son1 = fork()) == 0 ) {
		close(p[0]);
		dup2(p[1],1);
		close(p[1]);
		a = open( argv[4], O_RDONLY );
		if (a == -1)
			exit(1);
		dup2(a,0);
		close(a);
		execlp(argv[1],argv[1],NULL);
		exit(1);
	}
	
	if ( (son3 = fork()) == 0 ) {
		close(p[1]);
		dup2(p[0],0);
		close(p[0]);
		a = open( argv[5], O_WRONLY | O_CREAT | O_APPEND, 0777 );
		dup2(a,1);
		close(a);
		execlp(argv[3],argv[3],NULL);
		exit(1);
	}
	
	close(p[0]);
	
	waitpid(son1,&a,0);
	if(WIFEXITED(a))
		a = WEXITSTATUS(a);
	
	if (a != 0) {
		/* первый неуспешен, возвращаем третий */
		close(p[1]);
		waitpid(son3,&a,0);
		if ( WIFEXITED(a) )
			a = WEXITSTATUS(a);
		else
			a = 1;
		exit(0);
	}
	
	if( (son2 = fork()) == 0 ) {
		dup2(p[1],1);
		close(p[1]);
		execlp(argv[2],argv[2],NULL);
		exit(1);
	}
	
	close(p[1]);
	
	waitpid(son2,&son2,0);
	waitpid(son3,&a,0);
	if ( WIFEXITED(a) )
		a = WEXITSTATUS(a);
	else
		a = 1;
	exit(0);
}