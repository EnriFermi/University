#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define lnum 5
int main(){
    char c;
    int count = 0;
    while(count < lnum && read(0, &c, 1) != 0){
        if(c == '\n'){
            count ++;
        }
        write(1, &c, 1);
    }
}