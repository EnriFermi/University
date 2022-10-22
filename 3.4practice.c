#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define varSize 4
/*
struct Node
{
    struct Node *prev, *next;
    char *elem;
};
struct List
{
    struct Node *first, *last;
};
*/
struct Node *add(struct List *pl, struct Node *pointer, struct Node *data) {
    if(pl->first == NULL || pl->last == NULL) { // нет элементов в списке
        pl->first = data;
        pl->last = data;
        data->next = NULL;
        data->prev = NULL;
        return data;
    }
    if(pointer == NULL) { // Вставка перед всеми элементами
        data->next = pl->first;
        pl->first->prev = data;
        data->prev = NULL;
        pl->first = data;
        return data;
    }
    if(pointer->next == NULL && pointer->prev == NULL) { // один элемент в списке
        pointer->next = data;
        data->prev = pointer;
        data->next = NULL;
        pl->first = pointer;
        pl->last = data;
        return data;
    }
    if(pointer->next == NULL) { // Вставка последним элементом
        pointer->next = data;
        data->prev = pointer;
        data->next = NULL;
        pl->last = data;
        return data;
    } // Вставка посередине
    data->next = pointer->next;
    data->prev = pointer;
    pointer->next->prev = data;
    pointer->next = data;
    return data;
}
struct List* newList() {
    struct List* list = malloc(sizeof(struct List));
    list->first = NULL;
    list->last = NULL;
    return list;
}
void mergeList(struct List *first, struct List *last, struct List *pl) {
    if(first->last != NULL && last->first != NULL) { // Оба ненулевые
        first->last->next = last->first;
        last->first->prev = first->last;
        pl->first = first->first;
        pl->last = last->last;
    } else if(first->last == NULL && last->first != NULL) {
        pl->first = last->first;
        pl->last = last->last;
    } else if(first->last != NULL && last->first == NULL) {
        pl->first = first->first;
        pl->last = last->last;
    } else {
        pl->first = NULL;
        pl->last = NULL;
    }
    free(first);
    free(last);
    return;
}
void process(struct List *pl, const char *str)
{
    if (pl->first == NULL)
    {
        return;
    }
    //Есть хотя бы один элемент в списке
    struct List *moved = newList();
    struct List *nondeleted = newList();
    struct Node *runner = pl->first;
    struct Node *mPointer = NULL;
    struct Node *ndPointer = NULL;
    struct Node *buffer = NULL;
    int cmp, flag = 1;
    while (flag) {
        cmp = strcmp(runner->elem, str);
        if (cmp < 0)
        {
            buffer = runner->next;
            if(buffer != NULL)
                buffer->prev = NULL;
            mPointer = add(nondeleted, mPointer, runner);
            runner = buffer;
            
        } else if (cmp > 0) {
            buffer = runner ->next;
            if(buffer != NULL)
                buffer->prev = NULL;
            ndPointer = add(moved, ndPointer ,runner);
            runner = buffer;
        } else {
            buffer = runner->next;
            if(buffer != NULL)
                buffer->prev = NULL;
            free(runner->elem);
            free(runner);
            runner = buffer;
            
        }
        flag = runner != NULL;
    }
    mergeList(nondeleted, moved, pl);
}
/*
char *f()
{
    char c;
    int pointer = 0;
    char *p = (char *)malloc(varSize);
    do
    {
        c = getchar();
        if ((c == '\n') || (c == EOF))
        {
            break;
        }
        p[pointer] = c;
        pointer++;
        if (pointer % varSize == 0)
            p = (char *)realloc(p, pointer + varSize);
    } while (1 == 1);
    p[pointer] = '\0';
    return p;
}
struct List *read()
{
    int n = 0;
    scanf("%d\n", &n);
    int wSize = 0, spaceflag = 0;
    char c;
    struct List *text = malloc(sizeof(struct List));
    text->first = NULL;
    text->last = NULL;
    struct Node *runner = NULL;
    text->first = malloc(sizeof(struct Node));
    runner = text->first;
    runner->elem = f();
    runner->next = NULL;
    runner->prev = NULL;
    for (int i = 0; i < n - 1; i++)
    {
        runner->next = malloc(sizeof(struct Node));
        runner->next->prev = runner;
        runner = runner->next;
        runner->elem = f();
        runner->next = NULL;
    }
    text->last = runner;
    return text;
}
int main()
{
    struct List *list = read();
    char *str = f();
    process(list, str);
    struct Node *node = list->first;
    while (node != NULL)
    {
        printf("%s\n", node->elem);
        node = node->next;
    }
    return 0;
}
*/
