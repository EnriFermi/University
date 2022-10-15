#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define varSize 4

struct Node
{
    struct Node *prev, *next;
    char *elem;
};
struct List
{
    struct Node *first, *last;
};

void add(struct List *pl, struct Node *pointer, struct Node *data) {
    if(pl->first == NULL || pl->last == NULL) {
        pl->first = data;
        pl->last = data;
        data->next = NULL;
        data->prev = NULL;
        return;
    }
    if(pointer == NULL) {
        data->next = pl->first;
        pl->first->prev = data;
        data->prev = NULL;
        pl->first = data;
        return;
    }
    if(pointer->next == NULL && pointer->prev == NULL) {
        pointer->next = data;
        data->prev = pointer;
        data->next = NULL;
        pl->first = pointer;
        pl->last = data;
        return;
    }
    if(pointer->next == NULL) {
        pointer->next = data;
        data->prev = pointer;
        data->next = NULL;
        pl->last = data;
        return;
    }
    data->next = pointer->next;
    data->prev = pointer;
    pointer->next->prev = data;
    pointer->next = data;
    return;
}
struct List* newList() {
    struct List* list = malloc(sizeof(struct List));
    list->first = NULL;
    list->last = NULL;
    return list;
}


void process(struct List *pl, const char *str)
{
    if (pl->first == NULL)
    {
        return;
    }
    //Есть хотя бы один элемент в списке
    struct List *moved = newList();
    struct List *deleted = newList();
    struct Node *runner = pl->first;
    int cmp, flag = 1;
    while (flag)
    {
        flag = runner != pl->last;
        /*
        struct Node *node = pl->first;
        while (node != NULL)
        {
            printf("%s ", node->elem);
            node = node->next;
        }
        printf("|\n");
        node = end;
        while (node != NULL)
        {
            printf("%s ", node->elem);
            node = node->next;
        }
        printf("|%s %d \n", runner->elem, flag);
        getchar();
        */
        cmp = strcmp(runner->elem, str);
        if (cmp == 0)
        {
            
        }

        else if (cmp > 0)
        {
            if (runner->next == NULL)
            { //Удаляем последний элемент в списке и завершаем работу

            } else if (runner->prev == NULL)
            { //Удаляем первый элемент в списке
            } 
            else
            { //Удаляем элемент посередине
            }
        }
        else
        {
            runner = runner->next;
        }
    }
    
}


void process(struct List *pl, const char *str)
{
    if (pl->first == NULL)
    {
        return;
    }
    struct Node *runner = pl->first;
    struct Node *buffer;
    struct Node *end = NULL;
    struct Node *pointer = NULL;
    int cmp, flag = 1;
    while (flag)
    {
        flag = runner != pl->last;
        /*
        struct Node *node = pl->first;
        while (node != NULL)
        {
            printf("%s ", node->elem);
            node = node->next;
        }
        printf("|\n");
        node = end;
        while (node != NULL)
        {
            printf("%s ", node->elem);
            node = node->next;
        }
        printf("|%s %d \n", runner->elem, flag);
        getchar();
        */
        cmp = strcmp(runner->elem, str);
        if (cmp == 0)
        {
            if (runner->next == NULL)
            { //Удаляем последний элемент в списке и завершаем работу
                if(runner->prev == NULL) {
                    pl->first = NULL;
                    free(runner->elem);
                    free(runner);
                    pl->last = NULL;
                } else {
                    pl->last = runner->prev;
                    free(runner->elem);
                    free(runner);
                    runner = pl->last;
                    runner->next = NULL;
                }
            } else if (runner->prev == NULL)
            { //Удаляем первый элемент в списке
                pl->first = runner->next;
                free(runner->elem);
                free(runner);
                runner = pl->first;
                runner->prev = NULL;
            } 
            else
            { //Удаляем элемент посередине
                buffer = runner;
                runner = runner->next;
                buffer->next->prev = buffer->prev;
                buffer->prev->next = buffer->next;
                free(buffer->elem);
                free(buffer);
            }
        }

        else if (cmp > 0)
        {
            if (runner->next == NULL)
            { //Удаляем последний элемент в списке и завершаем работу
                pl->last = runner->prev;
                if(runner->prev == NULL) {
                    pl->first = NULL;
                }
                if (end == NULL)
                {
                    end = runner;
                    pointer = end;
                    end->prev = NULL;
                    end->next = NULL;
                }
                else
                {
                    pointer->next = runner;
                    pointer->next->prev = pointer;
                    pointer = pointer->next;
                    pointer->next = NULL;
                }
                runner = pl->last;
                if(runner != NULL) {
                    runner->next = NULL;
                }

            } else if (runner->prev == NULL)
            { //Удаляем первый элемент в списке
                pl->first = runner->next;
                if(runner->next != NULL) {
                    runner->next->prev = NULL;
                }
                if (end == NULL)
                {
                    end = runner;
                    pointer = end;
                    end->prev = NULL;
                    end->next = NULL;
                }
                else
                {
                    pointer->next = runner;
                    pointer->next->prev = pointer;
                    pointer = pointer->next;
                    pointer->next = NULL;
                }
                runner = pl->first;
            } 
            else
            { //Удаляем элемент посередине

                buffer = runner;
                runner = runner -> next;
                buffer->next->prev = buffer->prev;
                buffer->prev->next = buffer->next;
                if (end == NULL)
                {
                    end = buffer;
                    pointer = end;
                    end->prev = NULL;
                    end->next = NULL;
                }
                else
                {
                    pointer->next = buffer;
                    pointer->next->prev = pointer;
                    pointer = pointer->next;
                    pointer->next = NULL;
                }
            }
        }
        else
        {
            runner = runner->next;
        }
    }
    if(pl->first != NULL) {
        if (end != NULL)
        {
            runner->next = end;
            end->prev = runner;
            pl->last = pointer;
        }
        else
        {
            pl->last = runner;
        }
    } else {
        pl->first = end;
        pl->last = pointer;
    }
    
}

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

