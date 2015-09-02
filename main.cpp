
#include <iostream>

using namespace std;

struct noh {

	int valor, fb;
	noh *esquerda, *direita, *pai;
};

struct arvore
{
	noh *raiz;
};

// Assinaturas de métodos:
void preOrdem(arvore &arv);
void preOrdemRec(noh* n);
void emOrdem(arvore &arv);
void emOrdemRec(noh* n);
void posOrdem(arvore &arv);
void posOrdemRec(noh* n);

void insereNoh(arvore &arv, int val);
void insereRec(noh* raiz, noh* n);

int altura(noh* raiz);
int calcula_fb(noh* n);
noh* balanceamento(noh* n);

noh* busca(arvore &a, int val);
noh* maisEsquerda(noh* raiz);
noh* maisDireita(noh* raiz);

void remover(arvore &a, int val);
void removerRec(noh* n);


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

void insereNoh(arvore &arv, int val)
{
	noh* n = new noh();
	n->valor = val;
	n->esquerda = NULL;
	n->direita = NULL;
	n->pai = NULL;
	n->fb = 0;

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

	if (n->direita != NULL) {
		n->direita->pai = n->pai;
		n->pai = n->direita;
		n->direita = n->pai->esquerda;
		n->direita->pai = n;
		n->pai->esquerda = n;

	}
	return n;

}

noh* rotacaoDir(noh* n) {
	if (n->esquerda != NULL) {

		n->esquerda->pai = n->pai;
		n->pai = n->esquerda;
		n->esquerda = n->pai->direita;
		n->esquerda->pai = n;
		n->pai->direita = n;

	}
	return n;
}
noh* rotacaoDirEsq(noh* n) {
	if (n->direita && n->esquerda != NULL) {
		rotacaoDir(n->direita);
		rotacaoEsq(n);
	}return n;

}
noh* rotacaoEsqDir(noh* n) {
	if (n->esquerda && n->direita != NULL) {
		rotacaoEsq(n->esquerda);
		rotacaoDir(n);
	}return n;
}


int calcula_fb(noh* n) {
	if (n == NULL) return 0;
	int hd = altura(n->direita);
	int he = altura(n->esquerda);
	return n->fb = hd - he;
}

noh* balanceamento(noh* n) {


	if (n != NULL) {

		n->fb = calcula_fb(n);

		if (n->fb == 2) {
			n->esquerda->fb = calcula_fb(n->esquerda);
			if (n->esquerda->fb > 0) {
				n = rotacaoDir(n);
			}
			else {
				n = rotacaoDirEsq(n);

			}
		}

		if (n->direita->fb == -2) {
			n->esquerda->fb = calcula_fb(n->direita);
			if (n->direita->fb < 0)
				n = rotacaoEsq(n);

		}
		else {
			n = rotacaoEsqDir(n);

		}
		n->esquerda = balanceamento(n->esquerda);
		n->direita = balanceamento(n->direita);
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

	// A arvore esta vazia, logo:
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


		switch (op) {

		case 1:

			cout << "Digite o numero a ser inserido na arvore: " << endl;
			cin >> valor;

			insereNoh(a, valor);
			break;

		case 2:

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
			break;

		case 3:

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
			break;

		case 4:


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
			break;
		case 5:

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
			break;

		case 6:

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

		case 7:

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
			break;

		case 8:
			op = 8;
			break;

		default:
			cout << "Opcao invalida" << endl;
		}
	} while (op != 8);


	system("pause");
	return 0;
}
