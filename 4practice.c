#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define varSize 4

struct tNode {
  int field;           // поле данных
  struct tNode *left;  // левый потомок
  struct tNode *right; // правый потомок
};

void treePrint(struct tNode *tree) {
  if (tree!=NULL) {
    treePrint(tree->right);
    printf("%d ", tree->field); 
    treePrint(tree->left);
  }
}
struct tNode *prevLastAdd = NULL;
struct tNode *lastAdd = NULL;
int flag = 0, side = 0;

struct tNode * add(int x, struct tNode *tree) {
  if (tree == NULL) { 
    tree = malloc(sizeof(struct tNode)); 
    lastAdd = tree;
    flag = 1;
    tree->field = x;   
    tree->left =  NULL;
    tree->right = NULL;
  } else  if(x <= tree->field) {
    tree->left = add(x,tree->left);
    if(flag == 1) {
        prevLastAdd = tree;
        flag = 0;
        side = 0;
    }
  } else {
    tree->right = add(x,tree->right);
    if(flag == 1) {
        prevLastAdd = tree;
        flag = 0;
        side = 1;
    }
  }
  return(tree);
}
void removeLast() {
    struct tNode *last = lastAdd, *prev = prevLastAdd;
    free(last);
    if(prev != NULL) {
        if(side == 1)
            prev->right = NULL;
        else
            prev->left = NULL;
    }
    return;
}
struct tNode* removeFirst(struct tNode *tree) {
    struct tNode * move = tree->left, *prev = NULL;
    if(tree->left != NULL){
        while (move->right != NULL)
        {
            prev = move;
            move = move->right;
        }
        if (prev != NULL)
        {
            prev->right = move->left;
            move->left = tree->left;
            
        }
        move->right = tree->right;
        free(tree);
        return move;
    } else {
        move = tree->right;
        free(tree);
        return move;
    }
}
void clear(struct tNode *tree) {
if (tree != NULL) {
    clear(tree->left);
    clear(tree->right);
    free(tree);
}
}
void *readSequences() {
    struct tNode *tree = NULL;
    int c;
    while (scanf("%1d", &c) != EOF) {
        if (c == 0) {
            printf("New way\n");
            treePrint(tree);
            printf("\n");
            if (tree->left != NULL || tree->right != NULL) {
                removeLast();
                tree = removeFirst(tree);
            }
            else {
                tree = NULL;
            }
            treePrint(tree);
            printf("\n");
            clear(tree);
            tree = NULL;
            break;
        }
        tree = add(c, tree);
    }
}
int main() {
    readSequences();
    return 0;
}
