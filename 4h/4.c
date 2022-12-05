#include<stdio.h>
#include<limits.h>
#include<math.h>
#include<fcntl.h>
#include<errno.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<unistd.h>



void func(int tmp, int fd) {
    struct stat stb;
    fstat(fd, &stb);
    unsigned char buf;
    read(fd, &buf, sizeof(buf));
    if (tmp > 0 && (tmp - 1) / 8 <= stb.st_size){
        tmp--;
        lseek(fd, tmp/8, SEEK_SET);
        read(fd, &buf, sizeof(buf));
        buf |= 1u << (tmp % 8);
    } else if (tmp < 0 && (tmp + 1) / 8 >= -stb.st_size) {
        tmp = - tmp - 1;
        lseek(fd, tmp/8, SEEK_SET);
        read(fd, &buf, sizeof(buf));
        buf &= ~(1u << (tmp % 8));
    
    }
    lseek(fd, tmp / 8, SEEK_SET);
    write(fd, &buf, sizeof(buf));
} 

int
main(int argc, char *argv[])
{
    if(argc < 2) {
        return 0;
    }
    int fd = open(argv[1], O_RDWR, 0666);
    int tmp = 0; 
    while(scanf("%d", &tmp) != EOF){
        func(tmp, fd);
    }
    close(fd);
    return 0;
}

