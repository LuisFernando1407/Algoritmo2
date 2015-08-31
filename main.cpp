#include <iostream>

using namespace std;

struct noh{

    int valor , altd , alte;
    noh *esquerda, *direita, *pai;
};

struct arvore
{
    noh* raiz;
};

void insereNoh(arvore &arv, int val);
void insereRec(noh* raiz, noh* n);
void preOrdem(arvore &arv);
void preOrdemRec(noh* n);
void emOrdem(arvore &arv);
void emOrdemRec(noh* n);
void posOrdem(arvore &arv);
void posOrdemRec(noh* n);
noh* maisEsquerda(noh* raiz);
noh* maisDireita(noh* raiz);
int altura(noh* raiz);
noh* busca(arvore &a, int val);
void remover(arvore &a, int val);
void removerRec(noh* n);

void insereNoh(arvore &arv, int val)
{
    noh* n = new noh();
    n->valor = val;
    n->esquerda = NULL;
    n->direita = NULL;
    n->pai = NULL;
   	n->altd = 0;
   	n->alte =0;

    if(arv.raiz == NULL)
        arv.raiz = n;
    else
        insereRec(arv.raiz, n);
}

void insereRec(noh* raiz, noh* n)
{
    if(raiz->valor < n->valor)
    {
        if(raiz->direita != NULL)
            insereRec(raiz->direita, n);
        else
        {
            raiz->direita = n;
            n->pai = raiz;
        }
    }else{
       if(raiz->esquerda != NULL)
            insereRec(raiz->esquerda, n);
       else
       {
            raiz->esquerda = n;
            n->pai = raiz;
       }
    }
}

void preOrdem(arvore &arv)
{
    preOrdemRec(arv.raiz);
}

void preOrdemRec(noh* n)
{
    if(n != NULL)
    {
        cout << n->valor << ", ";
        preOrdemRec(n->esquerda);
        preOrdemRec(n->direita);
    }
}

void emOrdem(arvore &arv)
{
    emOrdemRec(arv.raiz);
}

void emOrdemRec(noh* n)
{
    if(n != NULL)
    {
        emOrdemRec(n->esquerda);
        cout << n->valor << ", ";
        emOrdemRec(n->direita);
    }
}

void posOrdem(arvore &arv)
{
    posOrdemRec(arv.raiz);
}

void posOrdemRec(noh* n)
{
    if(n != NULL)
    {
        posOrdemRec(n->esquerda);
        posOrdemRec(n->direita);
        cout << n->valor << ", ";
    }
}

noh* maisEsquerda(noh* raiz)
{
    noh* p = raiz;

    while(p->esquerda != NULL)
        p = p->esquerda;

    return p;
}

noh* maisDireita(noh* raiz)
{
    noh* p = raiz;

    while(p->direita != NULL)
        p = p->direita;

    return p;
}

int altura(noh* raiz)
{
    if(raiz == NULL)
        return 0;

    int he = altura(raiz->esquerda);
    int hd = altura(raiz->direita);

    int maior = (he > hd) ? he : hd;

    return 1 + maior;
}
noh* rotacaoEsq(noh* n){
	noh *aux1 , *aux2;
	aux1 = n->direita;
	aux2 = aux1->esquerda;
	n->direita = aux2;
	aux1->esquerda= n;
	
	if(n->direita == NULL){
		n->altd = 0;
	}
 	else if(n->direita->alte > n->direita->altd){
 		n->altd = n->direita->alte+1;
	 }else{
	 	n->altd = n->direita->altd+1;
	 }
	 if(aux1->esquerda->alte > aux1->esquerda->altd){
	 	aux1->alte = aux1->esquerda->alte+1;
	 }else{
	 	aux1->alte = aux1->esquerda->altd+1;
	 
	 }	return aux1;
	 
}
noh* rotacaoDir(noh* n){
	noh *aux1 , *aux2;
	aux1 = n->esquerda;
	aux2 = aux1->direita;
	n->esquerda = aux2;
	aux1->direita= n;
	
	if(n->esquerda == NULL){
		n->alte = 0;
	}
 	else if(n->esquerda->alte > n->esquerda->altd){
 		n->alte = n->esquerda->alte+1;
	 }else{
	 	n->alte= n->esquerda->altd+1;
	 }
	 if(aux1->direita->alte > aux1->direita->altd){
	 	aux1->altd = aux1->direita->altd+1;
	 }else{
	 	aux1->altd = aux1->direita->altd+1;
	 
	 }	return aux1;
}
noh* fatorb (noh* n){
	int d , df;
	d = n->altd - n->alte;
	if(d == 2){
		df = n->direita->altd - n->direita->alte;
		if(df >=0 ){
			n = rotacaoEsq(n);
		}else{
			n->direita = rotacaoDir(n->direita);
			n = rotacaoEsq(n);
		}
	}
	else if (d == -2){
		df = n->esquerda->altd - n->esquerda->alte;
		if(df <= 0){
			n = rotacaoDir(n);
		}else{
			n->esquerda = rotacaoEsq(n->esquerda);
			n = rotacaoDir(n);
		}
	}
	return n;
}
noh* busca(arvore &a, int val)
{
    noh* r = a.raiz;

    if(r == NULL) return NULL;

    while(r != NULL && r->valor != val)
    {
        if(val <= r->valor)
            r = r->esquerda;
        else
            r = r->direita;
    }

    return r;
}

void remover(arvore &a, int val)
{
    noh* n = busca(a, val);

    if(n == NULL) return;

    removerRec(n);
}

void removerRec(noh* n)
{
    if(n == NULL) return;

    if(n->esquerda == NULL && n->direita == NULL)
    {
        noh* p = n->pai;
        if(n == p->esquerda) p->esquerda = NULL;
        else p->direita = NULL;
        delete n;
        return;
    }

    noh* a;
    if(n->esquerda != NULL)
        a = maisDireita(n->esquerda);
    else
        a = maisEsquerda(n->direita);

    n->valor = a->valor;
    removerRec(a);
}

int main()
{
    arvore a;
    a.raiz = NULL;

    insereNoh(a, 20);
    insereNoh(a, 10);
    insereNoh(a, 30);
    insereNoh(a, 40);
    insereNoh(a, 15);
    insereNoh(a, 20);
    insereNoh(a, 0);

    emOrdem(a);

    remover(a, 0);
    remover(a, 10);

    cout << endl;
    emOrdem(a);

    return 0;
}

