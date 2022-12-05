#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<limits.h>
#include<errno.h>
#include<unistd.h>

int func(char *str, size_t len){
    if (str[0] == '+') {
        str++;
    }
    int mul = 1;
    if (str[len - 1] == 'k') {
        mul = 1000;
        str[--len] = '\0';
    }
    char *eptr = NULL;
    errno = 0;
    int res = strtoll(str, &eptr, 10);
    if (eptr == str || *eptr || __builtin_mul_overflow(res, mul, &res) || errno) {
        return 0;
    } else {
        return res;
    }
}


int 
main(int argc, char **argv)
{
    if(argc < 2){
        printf("0\n");
        return 0;
    }
    long long res = 0;
    for(int i = 1; i < argc; i++){
        size_t len = strlen(argv[i]);
        char sign = argv[i][len - 1];
        argv[i][len - 1] = '\0';
        len--;
        if(sign == '-'){
            res -= func(argv[i], len);
        } else if (sign == '+'){
            res += func(argv[i], len);
        }
    }
    printf("%lld\n", res);
}
