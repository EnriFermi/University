#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define varSize 4

int contains(char *str, char c){
    int contains = 0;
    for(int i=0; i< strlen(str); i++) {
        if(str[i]==c){
            contains = 1;
            break;
        }
    }
    return contains;
}

int main(int argc, char **argv)
{
    FILE *f = fopen(argv[1], "r");
    fseek(f, 0, SEEK_END);
    long long size = ftell(f);
    char *storyData = malloc(size);
    char *ptr = storyData;
    *ptr = 0;
    fseek(f, 0, SEEK_SET);
    while (fgets(ptr, size, f))
    {
        if (!contains(ptr, argv[2][0]))
        {
            ptr = ptr + strlen(ptr);
        }
    }
    fclose(f);
    f = fopen("file.txt", "w");
    fputs(storyData, f);
    fclose(f);

    free(storyData);

    return 0;
}
