#include <iostream>

using namespace std;

struct noh {

	int valor, altd, alte;
	noh *esquerda, *direita, *pai;
};

struct arvore
{
	noh *raiz;
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
	n->alte = 0;

	if (arv.raiz == NULL)
		arv.raiz = n;
	else
		insereRec(arv.raiz, n);
}

void insereRec(noh* raiz, noh* n)
{
	if (raiz->valor < n->valor)
	{
		if (raiz->direita != NULL)
			insereRec(raiz->direita, n);
		else
		{
			raiz->direita = n;
			n->pai = raiz;
		}
	}
	else {
		if (raiz->esquerda != NULL)
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
	if (n != NULL)
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
	if (n != NULL)
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
	if (n != NULL)
	{
		posOrdemRec(n->esquerda);
		posOrdemRec(n->direita);
		cout << n->valor << ", ";
	}
}

noh* maisEsquerda(noh* raiz)
{
	noh* p = raiz;

	while (p->esquerda != NULL)
		p = p->esquerda;

	return p;
}

noh* maisDireita(noh* raiz)
{
	noh* p = raiz;

	while (p->direita != NULL)
		p = p->direita;

	return p;
}

int altura(noh* raiz)
{
	if (raiz == NULL)
		return 0;

	int he = altura(raiz->esquerda);
	int hd = altura(raiz->direita);

	int maior = (he > hd) ? he : hd;

	return 1 + maior;
}

noh* rotacaoEsq(noh* n) {
	noh *aux1, *aux2;
	aux1 = n->direita;
	aux2 = aux1->esquerda;
	n->direita = aux2;
	aux1->esquerda = n;

	if (n->direita == NULL) {
		n->altd = 0;
	}
	else if (n->direita->alte > n->direita->altd) {
		n->altd = n->direita->alte + 1;
	}
	else {
		n->altd = n->direita->altd + 1;
	}
	if (aux1->esquerda->alte > aux1->esquerda->altd) {
		aux1->alte = aux1->esquerda->alte + 1;
	}
	else {
		aux1->alte = aux1->esquerda->altd + 1;

	}	return aux1;

}

noh* rotacaoDir(noh* n) {
	noh *aux1, *aux2;
	aux1 = n->esquerda;
	aux2 = aux1->direita;
	n->esquerda = aux2;
	aux1->direita = n;
	if (n->esquerda == NULL) {
		n->alte = 0;
	}
	else if (n->esquerda->alte > n->esquerda->altd) {
		n->alte = n->esquerda->alte + 1;
	}
	else {
		n->alte = n->esquerda->altd + 1;
	}
	if (aux1->direita->alte > aux1->direita->altd) {
		aux1->altd = aux1->direita->altd + 1;
	}
	else {
		aux1->altd = aux1->direita->altd + 1;

	}	return aux1;
}

noh* fatorb(noh* n) {
	int d, df;
	d = n->altd - n->alte;
	if (d == 2) {
		df = n->direita->altd - n->direita->alte;
		if (df >= 0) {
			n = rotacaoEsq(n);
		}
		else {
			n->direita = rotacaoDir(n->direita);
			n = rotacaoEsq(n);
		}
	}
	else if (d == -2) {
		df = n->esquerda->altd - n->esquerda->alte;
		if (df <= 0) {
			n = rotacaoDir(n);
		}
		else {
			n->esquerda = rotacaoEsq(n->esquerda);
			n = rotacaoDir(n);
		}
	}
	return n;
}

noh* busca(arvore &a, int val)
{
	noh* r = a.raiz;

	if (r == NULL) return NULL;

	while (r != NULL && r->valor != val)
	{
		if (val <= r->valor)
			r = r->esquerda;
		else
			r = r->direita;
	}

	return r;
}

void remover(arvore &a, int val)
{
	noh* n = busca(a, val);

	if (n == NULL) return;

	removerRec(n);
}

void removerRec(noh* n)
{
	if (n->esquerda == NULL && n->direita == NULL)
	{
		noh* p = n->pai;
		if (n == p->esquerda) p->esquerda = NULL;
		else p->direita = NULL;
		delete n;
		return;
	}

	noh* a;
	if (n->esquerda != NULL)
		a = maisDireita(n->esquerda);
	else
		a = maisEsquerda(n->direita);

	n->valor = a->valor;
	removerRec(a);
}

noh* desalocar(noh* n) {
	if (n != NULL)
	{
		n->esquerda = desalocar(n->esquerda);
		n->direita = desalocar(n->direita);
	}
	return NULL;
}

int main()
{
	arvore a;
	noh* aux;
	int op, valor;

	// A arvore está vazia, logo:
	a.raiz = NULL;

	do {
		
		system("cls");
		
		cout << "\n----- MENU DE OPCOES -----" << endl;
		cout << "1 - Inserir na arvore" << endl;
		cout << "2 - Consultar um noh da arvore" << endl;
		cout << "3 - Consultar toda a arvore em Pre-ordem" << endl;
		cout << "4 - Consultar toda a arvore Em ordem" << endl;
		cout << "5 - Consultar toda a arvore em Pos-ordem" << endl;
		cout << "6 - Excluir um noh da arvore" << endl;
		cout << "7 - Esvaziar a arvore" << endl;
		cout << "8 - Sair" << endl;
		cout << "\nInsira sua opcao: " << endl;
		cin >> op;
		
		
		if (op < 1 || op > 8)
		{
			cout << "Opcao invalida!!!" << endl;
			system("pause");
		}
		else if (op == 1)
		{
			cout << "Digite o numero a ser inserido na arvore: " << endl;
			cin >> valor;

			insereNoh(a, valor);
		}
		else if (op == 2)
		{
			if (a.raiz == NULL) {
				cout << "A arvore esta vazia!!!" << endl;
				system("pause");
			}
			else
			{
				cout << "Digite o elemento a ser consultado: " << endl;
				cin >> valor;

				aux = busca(a, valor);

				if (aux == NULL)
				{
					cout << "Numero nao encontrado na arvore!" << endl;
					system("pause");
				}
				else
				{
					cout << "Numero encontrado na arvore!" << endl;
					system("pause");
				}
			}
		}
		else if (op == 3)
		{
			if (a.raiz == NULL) {
				cout << "A arvore esta vazia!!!" << endl;
				system("pause");
			}
			else
			{
				cout << "Listando os elementos da arvore em Pre-ordem:" << endl;
				preOrdem(a);
				system("pause");
			}
		}
		else if (op == 4)
		{
			if (a.raiz == NULL) {
				cout << "A arvore esta vazia!!!" << endl;
				system("pause");
			}
			else
			{
				cout << "Listando os elementos da arvore Em Ordem:" << endl;
				emOrdem(a);
				system("pause");
			}
		}
		else if (op == 5)
		{
			if (a.raiz == NULL) {
				cout << "A arvore esta vazia!!!" << endl;
				system("pause");
			}
			else
			{
				cout << "Listando os elementos da arvore em pos-ordem:" << endl;
				posOrdem(a);
				system("pause");
			}
		}
		else if (op == 6)
		{
			if (a.raiz == NULL) {
				cout << "A arvore esta vazia!!!" << endl;
				system("pause");
			}
			else
			{
				cout << "Digite o numero que deseja excluir:" << endl;
				cin >> valor;

				aux = busca(a, valor);

				if (aux == NULL)
				{
					cout << "Numero nao encontrado na arvore!" << endl;
					system("pause");
				}
				else
				{
					remover(a, valor);
					cout << "Numero excluido da arvore!" << endl;
					system("pause");
				}
			}
		}
		else if (op == 7)
		{
			if (a.raiz == NULL) {
				cout << "A arvore esta vazia!!!" << endl;
				system("pause");
			}
			else
			{
				a.raiz = desalocar(a.raiz);
				cout << "Arvore esvaziada!!!" << endl;
				system("pause");
			}
		}

	} while (op != 8);

	system("pause");
	return 0;
}
