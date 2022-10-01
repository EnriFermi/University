#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define varSize 4

int main(int argc, char * argv[]) {
    /*
    int sizeStr=0, j=0;
    char*p;
    char **end;
    double summ=0, add;
    for(int i=1; i<argc; i++) {
        p = argv[i];
        add = strtod(p, end);
        if(end[0][0] == '\0')
        {
            summ +=add;
            p[0] = '\0';
            continue;
        } else {
            sizeStr += strlen(p);
        }
    }
    char *res = malloc(2*sizeStr+1);
    for(int i=1; i<argc; i++) {
        p = argv[i];
        if(p != '\0') {
            for(int k=0; k<strlen(p); k++){
                res[j] = p[k];
                res[j+sizeStr] = p[k];
                j++;
            }
        }
    }
    res[2*sizeStr] = '\0';
    printf("Summ is: %f\n", summ);
    printf("String is: %s", res);
    free(res);
    return 0;*/
    typedef struct list{
        struct list *next;
        long number;
        long count;
    } LNode;
    if(argc < 2) {
        return 0;
    }
    long number;
    int N = strtol(argv[1], NULL, 10), flag, created=0;
    LNode* list = NULL, *p;
    while(scanf("%ld", &number) != -1) {
        p = list;
        flag = 0;
        while (p!=NULL) {
            if(p->number == number) {
                p->count++;
                flag = 1;
                break;
            }
            if(p->next != NULL) {
                p = p-> next;
            } else {
                break;
            }
        }
        if(flag == 0 && created == 1) {
            p->next = malloc(sizeof(LNode));
            
            p = p->next;
            p->next =NULL;
            p->count = 1;
            p->number = number;
        }
        if(flag == 0 && created == 0) {
            p = malloc(sizeof(LNode));
            p->next = NULL;
            p->count = 1;
            p->number = number;
            list = p;
            created = 1;
        }
    }

    p = list;
    printf("\n");
    while(p != NULL){
        if(p->count == N) {
            printf("%ld ", p->number);
        }
        p = p->next;
    }
}