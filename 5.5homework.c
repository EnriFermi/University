#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define varSize 4

typedef struct tN // структура для представления узлов дерева
{
	long long key;
    FILE *file;
	unsigned char height;
	struct tN* left;
	struct tN* right;
} tNode;
//-------------------------------------------------
unsigned char height(tNode* p)
{
	return p?p->height:0;
}

int differ(tNode* p)
{
	return height(p->right)-height(p->left);
}

void fHeight(tNode* p)
{
	unsigned char hl = height(p->left);
	unsigned char hr = height(p->right);
	p->height = (hl>hr?hl:hr)+1;
}
//Insert
tNode* rRight(tNode* p) // правый поворот вокруг p
{
	tNode* q = p->left;
	p->left = q->right;
	q->right = p;
	fHeight(p);
	fHeight(q);
	return q;
}

tNode* rLeft(tNode* q) // левый поворот вокруг q
{
	tNode* p = q->right;
	q->right = p->left;
	p->left = q;
	fHeight(q);
	fHeight(p);
	return p;
}

tNode* balance(tNode* p) // балансировка узла p
{
	fHeight(p);
	if( differ(p)==2 )
	{
		if( differ(p->right) < 0 )
			p->right = rRight(p->right);
		return rLeft(p);
	}
	if( differ(p)==-2 )
	{
		if( differ(p->left) > 0  )
			p->left = rLeft(p->left);
		return rRight(p);
	}
	return p; // балансировка не нужна
}

tNode* insert(tNode* p, int k, FILE *file) // вставка ключа k в дерево с корнем p
{
	if( !p ){
        tNode *q = malloc(sizeof(tNode));
        q->height = 1;
        q->file = file;
        q->left = q->right = NULL;
        q->key = k;
        return q;
    };
	if( k<p->key )
		p->left = insert(p->left,k,file);
	else
		p->right = insert(p->right,k,file);
	return balance(p);
}

//Delete
tNode* findmin(tNode* p) // поиск узла с минимальным ключом в дереве p 
{
	return p->left?findmin(p->left):p;
}

tNode* removemin(tNode* p) // удаление узла с минимальным ключом из дерева p
{
	if( p->left==0 )
		return p->right;
	p->left = removemin(p->left);
	return balance(p);
}

tNode* removeElem(tNode* p, int k) // удаление ключа k из дерева p
{
	if( !p ) return NULL;
	if( k < p->key )
		p->left = removeElem(p->left,k);
	else if( k > p->key )
		p->right = removeElem(p->right,k);	
    else //  k == p->key 
	{
		tNode* q = p->left;
		tNode* r = p->right;
		free(p);
		if( !r ) return q;
		tNode* min = findmin(r);
		min->right = removemin(r);
		min->left = q;
		return balance(min);
	}
    return balance(p);
}
//Открывает все файлы
FILE **openf(int argc, char **argv){
    FILE **flist = malloc((argc-1)*sizeof(FILE*));
    for(int i=1; i<argc; i++) {
        flist[i-1] = fopen(argv[i], "r");
    }
    return flist;
}

void process(FILE **flist, int size) {
    FILE *cfile;
    tNode *etree = NULL, *minNode;
    int allEmpty = 0, isRead = 1;
    long long x;
    // Первичное заполнение массива элем для сравнения
    
    for (int i = 0; i < size; i++) {
        if (fscanf(flist[i], "%lld", &x) == EOF)
        {
            fclose(flist[i]);
            flist[i] = NULL;
        }
        else
        {
            etree = insert(etree, x, flist[i]);
        }
    }

    //Если все файлы пустые, то не заходим
    while(etree != NULL) {
        minNode = findmin(etree);
        cfile = minNode->file;
        printf("%lld", minNode->key);
        etree = removeElem(etree, minNode->key);
        if (fscanf(cfile, "%lld", &x) == EOF)
        {
            fclose(cfile);
        }
        else
        {
            etree = insert(etree, x, cfile);
        }
    }
    
}


int main(int argc, char **argv)
{
    if(argc < 2){
        return 0;
    }
    FILE **flist = openf(argc, argv);
    process(flist, argc-1);
    free(flist);
    return 0;
}






/*
    int allEmpty = 0;
    while(!allEmpty)
    {
        long long min = __LONG_LONG_MAX__, elem;
        allEmpty = 1;
        for(int i = 0; i<size; i++) {
            if(flist[i] != NULL) { //Файл открыт
                fscanf(flist[i], "%d", elem)
            }
        }
    } */