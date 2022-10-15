#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define varSize 4

typedef struct clist{
        struct clist *next;
        char chr;
    } charNode;

typedef charNode* charList;

typedef struct slist{
        struct slist *next;
        struct slist *prev;
        char* string;
    } stringNode;

typedef stringNode* stringList;
charList newC(){
    charList p = malloc(sizeof(charList));
    p->next = NULL;
    p->chr = '\0';
    return p;
}
charList addC(charList p, char chr) {
    p->next = malloc(sizeof(charList));
    p->chr = chr;
    p = p->next;
    p->next =NULL;
    p->chr = '\0';
    return p;
}
char* listToString(charList l, int lSize) {
    int point = 0;
    char *s = malloc(lSize);
    while(l!=NULL) {
        s[point++] = l->chr;
        l = l->next;
    }
    return s;
}
void clearC(charList p) {
    while(p!=NULL) {
        charList q = p->next;
        free(p);
        p = q;
    }
}
stringList newS(){
    stringList p = malloc(sizeof(stringList));
    p->next = NULL;
    p->prev = NULL;
    p->string = NULL;
    return p;
}
stringList addS(stringList p, char* string) {
    stringList q = p->next;
    p->next = malloc(sizeof(charList));
    p->next->prev = p;
    p = p->next;
    p->next = q;
    p->string = string;
    return p;
}
void addSortedS(stringList p, char* string) {
    stringList r = p, rb = NULL;
    r = r -> next;
    if(r==NULL){
        addS(p, string);
        return;
    }
    while(strcmp(r->string, string) < 0) {
        rb = r;
        r = r -> next;
        if(r == NULL) {
            break;
        }
    }
    if(rb == NULL) {
        addS(p, string);
        return;
    }
    addS(rb, string);
    return;
}
void clearS(stringList p) {
    while(p!=NULL) {
        stringList q = p->next;
        free(p->string);
        free(p);
        p = q;
    }
}

stringList read(stringList* sListSorted) {
    int wSize=0, spaceflag = 0;
    char c;
    charList word = newC();
    charList wordRunner = word;
    stringList text = newS();
    stringList textRunner = text;
    c = getchar();
    while (c != '\n' && c != EOF) {
        if(c == ' ') {
            if(spaceflag == 1) {
                textRunner = addS(textRunner, listToString(word, wSize));
                addSortedS(sListSorted[0], listToString(word, wSize));
                clearC(word);
                wSize = 0;
                word = newC();
                wordRunner = word;
            }
            spaceflag = 0;
        } else {
            spaceflag = 1;
        }
        if(spaceflag == 1){
            wordRunner = addC(wordRunner, c);
            wSize++;
        }

        c = getchar();
    };
    if(spaceflag == 1) {
        textRunner = addS(textRunner, listToString(word, wSize));
        addSortedS(sListSorted[0], listToString(word, wSize));
        
    }
    clearC(word);
    return text;
}
void writeFB(stringList sList, stringList sortedSList){
    stringList saveList = sList;
    stringList psList = sList;
    sList = sList->next;
    while(sList != NULL ){
        printf("%s ", sList->string);
        psList = sList;
        sList = sList->next;
    }
    printf("\n");
    while(psList != saveList) {
        printf("%s ", psList->string);
        psList = psList->prev;
    }
    printf("\n");
    stringList saveSortedList = sortedSList;
    sortedSList = sortedSList -> next;
    while(sortedSList != NULL){
        printf("%s ", sortedSList->string);
        sortedSList = sortedSList -> next;
    }
    clearS(saveList);
    clearS(saveSortedList);
}

int main() {
    stringList sortedSList = newS();
    stringList sList = read(&sortedSList);
    writeFB(sList, sortedSList);
    return 0;
}
