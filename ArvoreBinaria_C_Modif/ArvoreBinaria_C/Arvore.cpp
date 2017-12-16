//Autor: Filipe Areias Névola  
//Ano: 2007  
//Programa: Operações em Árvore Binária  
//Licensa: Você pode usar e alterar, mas deve manter o Autor  
  
#include <iostream>
#include <windows.h>
using namespace std;  
  
//estrutura para representar um Nó,  
//onde k é a chave  
//l é o ponteiro para o filho esquerdo  
//r é o ponteiro para o filho direito  
typedef struct tagNO_ARVORE
{  
    int nValorNoNoh;				// valor inteiro dentro de um nó
    tagNO_ARVORE *ptrNohLeft;		// ponteiro para o nó filho esquerdo (menor valor)
    tagNO_ARVORE *ptrNohRight;		// ponteiro para o nó filho direito (maior valor)
    tagNO_ARVORE():ptrNohLeft(NULL),ptrNohRight(NULL){} //inicializando os ponteiros  
}NO_ARVORE;  
  
//estrutura para representar uma Árvore,  
//onde ptrNohArvore é o ponteiro da raiz da árvore  
typedef struct tagARVORE
{  
    NO_ARVORE *ptrNohArvore;		// ponteiro para a raiz da árvore
}ARVORE;  
  
// imprime a árvore em ordem crescente de valor
// apartir do nó ptrNoh 
void imprimirpt(NO_ARVORE *ptrNoh)
{  
    if(ptrNoh!=NULL)
	{  
        imprimirpt(ptrNoh->ptrNohLeft);  
        cout << " " << ptrNoh->nValorNoNoh << " ";  
        imprimirpt(ptrNoh->ptrNohRight);  
    }  
}  
  
//chama a imprimirpt passando a raiz  
//Porque passar a raiz somente aqui e não chamar direto?  
//Para abstrair, ou seja, o usuário não precisa saber que existe uma raiz  
//ele necessita apenas saber que tem uma árvore (todas as funções estão dessa maneira)  
void imprimir(ARVORE arvore)
{  
    imprimirpt(arvore.ptrNohArvore);  
}  
  
// insere em x a altura da árvore (está recebendo por referência o endereço
// a receber altura)  
void alturapt(NO_ARVORE *ptrNoh,int &x)
{  
    int hr, hl;							// auxiliares  
    if(ptrNoh!=NULL)
	{  
        x++;  
        hr=x;  
        hl=x;  
        alturapt(ptrNoh->ptrNohRight,hr);  
        alturapt(ptrNoh->ptrNohLeft,hl);  
        if(hr>x)  
            x=hr;  
        if(hl>x)  
            x=hl;  
    }  
}  
  
//chama alturapt passando a raiz e irá retornar a altura (um inteiro)  
int altura(ARVORE arvore)
{  
    int altAux = 0;							// altura auxiliar
    alturapt(arvore.ptrNohArvore, altAux);  // busca a altura da árvore
    return altAux;							// retorna a altura que foi encontrada
}  
  
// insere elem na árvore transformando a referencia da árvore em
// ponteiro
// Retorno:
//		false - não tem mais memória para inserir o novo nó da árvore
//		true - foi sucesso a inserção do novo nó
bool inserirpt(NO_ARVORE *&pt, int elem)
{  
   if(pt!=NULL)
   {  
        if(elem >= pt->nValorNoNoh)					// se elemento a ser inserido é maior ou igual
		{											// ao elemento deste nó ele vai ser inserido	  
            return inserirpt(pt->ptrNohRight,elem); // à direita como filho deste nó 
        }  
        else
		{	// sendo menor que o elemento deste nó  
            return inserirpt(pt->ptrNohLeft,elem);	// vai ser inserido a esquerda deste nó  
        }  
    }  
    else
	{	// vai alocar memória para inserir este novo nó  
        pt = new NO_ARVORE;  
        if(pt == NULL)								// não há memória suficiente?
            return false;							// avisa que não pode inserir
        pt->nValorNoNoh = elem;  
        pt->ptrNohRight = pt->ptrNohLeft = NULL;  
        return true;								// avisa que foi sucesso!
    }  
}  
  
//chama inserirpt passando a raiz e o elemento  
bool inserir(ARVORE &refArvore, int nElemInserir)
{  
   return inserirpt(refArvore.ptrNohArvore,nElemInserir);  
}  
  
// encontra um substituto para o nó removido
// ptrNohRemovido = ponteiro do nó sendo removido
int substituto(NO_ARVORE *ptrNohRemovido)
{  
    NO_ARVORE *paux,**ppt;  
    int subst;  
    if(ptrNohRemovido->ptrNohLeft!=NULL)
	{  
        ppt=&ptrNohRemovido->ptrNohLeft;  
        while((*ppt)->ptrNohRight!=NULL)  
            ppt=&(*ppt)->ptrNohRight;  
        subst = (*ppt)->nValorNoNoh;  
        paux = *ppt;  
        *ppt = (*ppt)->ptrNohLeft;  
  
    }  
    else
	{  
        ppt = &ptrNohRemovido->ptrNohRight;  
        while((*ppt)->ptrNohLeft != NULL)  
            ppt = &(*ppt)->ptrNohLeft;  
        subst = (*ppt)->nValorNoNoh;  
        paux = *ppt;  
        *ppt = (*ppt)->ptrNohRight;  
    }  
    delete []paux;  
    return subst;  
}  
  
//remove nElemARemover de uma árvore  
bool removerpt(NO_ARVORE **pt, int nElemARemover)
{  
    if((*pt)!=NULL)
	{  
        if(nElemARemover > (*pt)->nValorNoNoh)  
            return removerpt(&(*pt)->ptrNohRight,nElemARemover);  
        if(nElemARemover < (*pt)->nValorNoNoh)  
            return removerpt(&(*pt)->ptrNohLeft,nElemARemover);  
        if((*pt)->ptrNohRight==NULL && (*pt)->ptrNohLeft==NULL)
		{  // vai excluir um nó folha (não tem nós filhos)
            //delete []pt;				// correção em 05/06/2011
			delete *pt;					// pelo prof.FATEC-Mogi das Cruzes
            *pt=NULL;  
        }  
        else  
            (*pt)->nValorNoNoh = substituto(*pt);  
        return true;  
    }  
    return false;  
}  
  
//chama removerpt passando a raiz e o x (elemento a ser removido)  
bool remover(ARVORE &raizArvore,int nValorARemover)
{  
    return removerpt(&raizArvore.ptrNohArvore,nValorARemover);  
}  
  
//alguns testes no código  
int main()
{  
    ARVORE arvore;  
    int nElemento,							// elemento a ser inserido na árvore
		nQtdeElementos;						// quantidade de elementos da árvore
	char cOpcao;							// Opção de escolha do menu
    arvore.ptrNohArvore=NULL;				// inicializa a árvore
    cout << "\tEntre com o numero de elementos para serem";  
    cout << "\n\tinseridos na arvore binaria de busca: ";  
    cin >> nQtdeElementos;					// quantidade de elementos da árvore  
    for(int i=0; i < nQtdeElementos; ++i)	// loop para buscar os elementos da árvore
	{   
        cout << "\n\tEntre com um elemento de ordem " << i + 1 << " :";  
        cin	>> nElemento;					// pegar o elemento a ser inserido  
        if(!inserir(arvore, nElemento))		// inserir o elemento na árvore  
			cout << "Elemento " << nElemento
			<< " nao foi inserido!" << endl;
		else
			cout << "Elemento " << nElemento
			<< " foi inserido com sucesso!" << endl;
    } // for
	while(true)								// loop infinito
	{
		cout << "\n\t\tMenu de Opcoes" << endl;
		cout << "L - Listar os elementos da arvore em ordem crescente" << endl;
		cout << "I - Inserir elemento na arvore" << endl;
		cout << "E - Excluir elemento da arvore" << endl;
		cout << "A - Altura da arvore" << endl;
		cout << "S - Sair do programa" << endl;
		cout << "\t\tSelecione:";
		cin >> cOpcao;						// opção escolhida do menu
		cOpcao = toupper(cOpcao);			// para aceitar mesmo que digitado minúscula
		switch(cOpcao)						// avaliar a opção escolhida
		{
			case 'L':						// Listar os elementos?
				imprimir(arvore);			// listar os elementos em ordem crescente
				break;						// sai do switch
			case 'I':						// Inserir novo elemento?
				cout << "Informe elemento a ser inserido:";
				cin	>> nElemento;			
				if(!inserir(arvore, nElemento))		// inserir o elemento na árvore  
					cout << "Elemento " << nElemento
					<< " nao foi inserido!" << endl;
				else
					cout << "Elemento " << nElemento
					<< " foi inserido com sucesso!" << endl;
				break;						// sai do switch
			case 'E':						// excluir elemento da árvore?
				cout << "Informe elemento a ser excluido:";
				cin	>>	nElemento;			// pegar o elemento
				if (!remover(arvore, nElemento))
					cout << "\nNao existe um noh que contenha " 
					<< nElemento << "!!!" << endl;
				else
					cout << "\nElemento " 
					<< nElemento << " foi excluido com sucesso!!!" << endl;
				break;						// sai do switch
			case 'A':						// altura da árvore?
				cout << "Altura da arvore " << altura(arvore) << endl; 
				system("pause");
				break;						// sai fora do switch
			case 'S':						// sair do programa?
				cout << "Vai sair realmente? (S ou N):";
				cin	>> cOpcao;				// pegar o S ou N
				cOpcao = toupper(cOpcao);	// não desprezar se foi minúscula
				if (cOpcao == 'S')			// vai sair mesmo?
				{
					cout << "Programa encerrado pelo operador!" << endl;
					system("pause");
					return 0;				// sai do programa
				}
				break;						// sai do switch e continua no programa
			default:						// escolha errada?
				cout << "Digite um opcao correta!!!" << endl;
		}// switch
	} // while
}// main  
