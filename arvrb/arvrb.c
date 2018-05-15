#include <stdio.h>
#include <stdlib.h>
#include "arvrb.h"

int main(){
	no_arvrb *raiz = cria_arvrb();
	insere_arvrb(&raiz,11);
	insere_arvrb(&raiz,14);
	insere_arvrb(&raiz,2);
	insere_arvrb(&raiz,1);
	insere_arvrb(&raiz,7);
	insere_arvrb(&raiz,15);
	insere_arvrb(&raiz,5);
	insere_arvrb(&raiz,8);
	insere_arvrb(&raiz,4);

	imprimir(raiz,0);

	//libera_arvrb(raiz);
}