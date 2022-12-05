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

int main(int argc, char **argv)
{
    char c;
    c = getchar();
    printf("%c\n",c);
    return 0;
}