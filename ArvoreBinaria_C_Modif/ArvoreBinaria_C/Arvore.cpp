//Autor: Filipe Areias N�vola  
//Ano: 2007  
//Programa: Opera��es em �rvore Bin�ria  
//Licensa: Voc� pode usar e alterar, mas deve manter o Autor  
  
#include <iostream>
#include <windows.h>
using namespace std;  
  
//estrutura para representar um N�,  
//onde k � a chave  
//l � o ponteiro para o filho esquerdo  
//r � o ponteiro para o filho direito  
typedef struct tagNO_ARVORE
{  
    int nValorNoNoh;				// valor inteiro dentro de um n�
    tagNO_ARVORE *ptrNohLeft;		// ponteiro para o n� filho esquerdo (menor valor)
    tagNO_ARVORE *ptrNohRight;		// ponteiro para o n� filho direito (maior valor)
    tagNO_ARVORE():ptrNohLeft(NULL),ptrNohRight(NULL){} //inicializando os ponteiros  
}NO_ARVORE;  
  
//estrutura para representar uma �rvore,  
//onde ptrNohArvore � o ponteiro da raiz da �rvore  
typedef struct tagARVORE
{  
    NO_ARVORE *ptrNohArvore;		// ponteiro para a raiz da �rvore
}ARVORE;  
  
// imprime a �rvore em ordem crescente de valor
// apartir do n� ptrNoh 
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
//Porque passar a raiz somente aqui e n�o chamar direto?  
//Para abstrair, ou seja, o usu�rio n�o precisa saber que existe uma raiz  
//ele necessita apenas saber que tem uma �rvore (todas as fun��es est�o dessa maneira)  
void imprimir(ARVORE arvore)
{  
    imprimirpt(arvore.ptrNohArvore);  
}  
  
// insere em x a altura da �rvore (est� recebendo por refer�ncia o endere�o
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
  
//chama alturapt passando a raiz e ir� retornar a altura (um inteiro)  
int altura(ARVORE arvore)
{  
    int altAux = 0;							// altura auxiliar
    alturapt(arvore.ptrNohArvore, altAux);  // busca a altura da �rvore
    return altAux;							// retorna a altura que foi encontrada
}  
  
// insere elem na �rvore transformando a referencia da �rvore em
// ponteiro
// Retorno:
//		false - n�o tem mais mem�ria para inserir o novo n� da �rvore
//		true - foi sucesso a inser��o do novo n�
bool inserirpt(NO_ARVORE *&pt, int elem)
{  
   if(pt!=NULL)
   {  
        if(elem >= pt->nValorNoNoh)					// se elemento a ser inserido � maior ou igual
		{											// ao elemento deste n� ele vai ser inserido	  
            return inserirpt(pt->ptrNohRight,elem); // � direita como filho deste n� 
        }  
        else
		{	// sendo menor que o elemento deste n�  
            return inserirpt(pt->ptrNohLeft,elem);	// vai ser inserido a esquerda deste n�  
        }  
    }  
    else
	{	// vai alocar mem�ria para inserir este novo n�  
        pt = new NO_ARVORE;  
        if(pt == NULL)								// n�o h� mem�ria suficiente?
            return false;							// avisa que n�o pode inserir
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
  
// encontra um substituto para o n� removido
// ptrNohRemovido = ponteiro do n� sendo removido
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
  
//remove nElemARemover de uma �rvore  
bool removerpt(NO_ARVORE **pt, int nElemARemover)
{  
    if((*pt)!=NULL)
	{  
        if(nElemARemover > (*pt)->nValorNoNoh)  
            return removerpt(&(*pt)->ptrNohRight,nElemARemover);  
        if(nElemARemover < (*pt)->nValorNoNoh)  
            return removerpt(&(*pt)->ptrNohLeft,nElemARemover);  
        if((*pt)->ptrNohRight==NULL && (*pt)->ptrNohLeft==NULL)
		{  // vai excluir um n� folha (n�o tem n�s filhos)
            //delete []pt;				// corre��o em 05/06/2011
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
  
//alguns testes no c�digo  
int main()
{  
    ARVORE arvore;  
    int nElemento,							// elemento a ser inserido na �rvore
		nQtdeElementos;						// quantidade de elementos da �rvore
	char cOpcao;							// Op��o de escolha do menu
    arvore.ptrNohArvore=NULL;				// inicializa a �rvore
    cout << "\tEntre com o numero de elementos para serem";  
    cout << "\n\tinseridos na arvore binaria de busca: ";  
    cin >> nQtdeElementos;					// quantidade de elementos da �rvore  
    for(int i=0; i < nQtdeElementos; ++i)	// loop para buscar os elementos da �rvore
	{   
        cout << "\n\tEntre com um elemento de ordem " << i + 1 << " :";  
        cin	>> nElemento;					// pegar o elemento a ser inserido  
        if(!inserir(arvore, nElemento))		// inserir o elemento na �rvore  
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
		cin >> cOpcao;						// op��o escolhida do menu
		cOpcao = toupper(cOpcao);			// para aceitar mesmo que digitado min�scula
		switch(cOpcao)						// avaliar a op��o escolhida
		{
			case 'L':						// Listar os elementos?
				imprimir(arvore);			// listar os elementos em ordem crescente
				break;						// sai do switch
			case 'I':						// Inserir novo elemento?
				cout << "Informe elemento a ser inserido:";
				cin	>> nElemento;			
				if(!inserir(arvore, nElemento))		// inserir o elemento na �rvore  
					cout << "Elemento " << nElemento
					<< " nao foi inserido!" << endl;
				else
					cout << "Elemento " << nElemento
					<< " foi inserido com sucesso!" << endl;
				break;						// sai do switch
			case 'E':						// excluir elemento da �rvore?
				cout << "Informe elemento a ser excluido:";
				cin	>>	nElemento;			// pegar o elemento
				if (!remover(arvore, nElemento))
					cout << "\nNao existe um noh que contenha " 
					<< nElemento << "!!!" << endl;
				else
					cout << "\nElemento " 
					<< nElemento << " foi excluido com sucesso!!!" << endl;
				break;						// sai do switch
			case 'A':						// altura da �rvore?
				cout << "Altura da arvore " << altura(arvore) << endl; 
				system("pause");
				break;						// sai fora do switch
			case 'S':						// sair do programa?
				cout << "Vai sair realmente? (S ou N):";
				cin	>> cOpcao;				// pegar o S ou N
				cOpcao = toupper(cOpcao);	// n�o desprezar se foi min�scula
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
