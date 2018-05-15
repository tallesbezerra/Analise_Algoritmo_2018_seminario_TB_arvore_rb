#define BLACK 0
#define RED 1

typedef struct no {
	int valor;
	int cor;
	struct no *pai;
	struct no *esq;
	struct no *dir;
}no_arvrb;

no_arvrb *cria_arvrb(){
	no_arvrb *raiz = (no_arvrb*)malloc(sizeof(no_arvrb));
	raiz->esq = raiz->dir = raiz->pai = NULL;
	if(raiz != NULL)
		raiz = raiz->esq = raiz->dir = raiz->pai = NULL;
	return raiz;
}

void rot_esq(no_arvrb **raiz, no_arvrb *x){
	no_arvrb *y = x->dir;
	x->dir = y->esq;
	if (y->esq != NULL)
		y->esq->pai = x;
	y->pai = x->pai;
	if(x->pai == NULL)
		*raiz = y;
	else{
		if (x == x->pai->esq)
			x->pai->esq = y;
		else
			x->pai->dir = y;
	}
	y->esq = x;
	x->pai = y;
}

void rot_dir(no_arvrb **raiz, no_arvrb *x){
	no_arvrb *y = x->esq;
	x->esq = y->dir;
	if (y->dir != NULL)
		y->dir->pai = x;
	y->pai = x->pai;
	if(x->pai == NULL)
		*raiz = y;
	else{
		if (x == x->pai->dir)
			x->pai->dir = y;
		else
			x->pai->esq = y;
	}
	y->dir = x;
	x->pai = y;
}

void insere_arvrb(no_arvrb **raiz, int valor){
	no_arvrb *z,*y,*x;
	y = NULL;
	z = (no_arvrb*)malloc(sizeof(no_arvrb));
	z->valor = valor;
	z->cor = RED;
	z->esq = NULL;
	z->dir = NULL;
	x = *raiz;
	while(x!=NULL){
		y = x;
		if (z->valor < x->valor)
			x = x->esq;
		else
			x = x->dir;
	}
	z->pai = y;
	if (y==NULL){
		*raiz = z;
	}
	else{
		if (z->valor < y->valor)
			y->esq = z;
		else
			y->dir = z;
	}

	while(z!=NULL && z->pai != NULL && z->pai->cor == RED){
		if(z->pai == z->pai->pai->esq){
			y = z->pai->pai->dir;
			if(y==NULL){
				rot_dir(&(*raiz),z->pai->pai);
				z->pai->cor = BLACK;
				z->cor = RED;
				z->pai->dir->cor = RED;
				z = z->pai->pai;
			}
			else{
				if (y->cor == RED){
					z->pai->cor = BLACK;
					y->cor = BLACK;
					z->pai->pai->cor = RED;
					z = z->pai->pai;					
				}
				else if (z == z->pai->dir){
					z = z->pai;
					rot_esq(&(*raiz),z);
					z->pai->cor = BLACK;
					z->pai->pai->cor = RED;
					rot_dir(&(*raiz),z->pai->pai);				
				}
			}
		}
		else{
			y = z->pai->pai->esq;
			if(y==NULL){
				rot_esq(&(*raiz),z->pai->pai);
				z->pai->cor = BLACK;
				z->cor = RED;
				z->pai->esq->cor = RED;
				z = z->pai->pai;
			}else{
				if (y->cor == RED){
					z->pai->cor = BLACK;
					y->cor = BLACK;
					z->pai->pai->cor = RED;
					z = z->pai->pai;
				}
				else if (z == z->pai->esq){
					z = z->pai;
					rot_dir(&(*raiz),z);
					z->pai->cor = BLACK;
					z->pai->pai->cor = RED;
					rot_esq(&(*raiz),z->pai->pai);				
				}
			}
		}
	}
	(*raiz)->cor = BLACK;
	return;
}

void libera_no(struct no *no){
	if(no==NULL)
		return;
	libera_no(no->esq);
	libera_no(no->dir);
	free(no);
	no = NULL;
}

void libera_arvrb(no_arvrb *raiz){
	if (raiz==NULL)
		return;
	libera_no(raiz);
	free(raiz);
}

void paddind(char ch, int n){
    int i;
    for(i=0;i<n;i++)
        putchar(ch);
}

void imprimir(no_arvrb *raiz, int level){
    int i;
    if(raiz==NULL){
        paddind('\t',level);
        puts(" ");
    } else {
        imprimir(raiz->dir, level+1);
        paddind('\t',level);
        printf("%d", raiz->valor);
        if (raiz->cor == 0)
        	printf("(B)\n");
        else
        	printf("(R)\n");
        imprimir(raiz->esq, level+1);
    }
}