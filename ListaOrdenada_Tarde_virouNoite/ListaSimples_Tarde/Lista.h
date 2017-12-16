// Declara��es e Classe da Lista Ligada Simples
#include <iostream>
#include <Windows.h>
using namespace std;
// defini��es
#define PAUSA								system("pause")
#define LIMPAR_TELA							system("cls")
// op��es do menu
#define INCLUIR_CLIENTE						'I'
#define EXCLUIR_CLIENTE						'E'
#define BUSCAR_CLIENTE						'B'
#define CLASSIFICAR_LISTA					'C'
#define ATUALIZAR_CLIENTE					'A'
#define LISTAR_CLIENTES						'L'
#define SAIR_DO_PROGRAMA					'S'

// struct do cliente
typedef struct tagCLIENTE
{
	int nCodCliente;						// c�digo de cliente
	char cNomeCliente[41];					// nome do cliente
	double dSaldoCliente;					// saldo do cliente
	tagCLIENTE *ptrProximo;					// ponteiro para o proximo da lista ligada
} CLIENTE;									// struct

//
// Classe cliente
//
class clCliente
{
	// atributos private da classe
private:
	CLIENTE *ptrPrimeiro,					// ponteiro para o primeiro da lista
		*ptrWork,							// ponteiro para o cliente sendo visto
		stCliente;							// struct para conter os dados de um cliente
	// m�todos p�blicos da classe
public:
	// M�todo construtor
	clCliente()
	{
		ptrPrimeiro = NULL;					// lista vazia
	}
	// M�todo p�blico para inser��o de cliente de forma ordenada
	//	Par�metros:
	//		Entrada: CLIENTE *ptrStCliente - ponteiro para uma struct que cont�m os dados
	//										do cliente a ser inserido
	//		Retorno: bool - true - inser��o OK
	//						false - n�o tem mem�ria dispon�vel para inser��o
	bool InserirCliente(CLIENTE *ptrStCliente)
	{
		CLIENTE *ptrAnterior,					// ponteiro do cliente anterior
			*ptrSalva;							// para salvaguarda de ponteiro
		if(ptrPrimeiro == NULL)				// primeiro da lista?
		{
			ptrPrimeiro = new CLIENTE;		// aloca mem�ria para um cliente
			// verificar se tem mem�ria
			if(ptrPrimeiro == NULL)			// n�o tem mem�ria?
				return false;				// avisa que n�o tem
			ptrPrimeiro->nCodCliente = ptrStCliente->nCodCliente; // copia o c�digo do cliente
			ptrPrimeiro->dSaldoCliente = ptrStCliente->dSaldoCliente; // copia o saldo
			strcpy_s(ptrPrimeiro->cNomeCliente, ptrStCliente->cNomeCliente); // copia o nome
			ptrPrimeiro->ptrProximo = NULL;	// primeiro e �ltimo
			return true;					// indica tudo OK
		}
		else								// n�o � o primeiro
		{	
			for(ptrWork = ptrPrimeiro, ptrAnterior = NULL;	 // inicializa��o
				ptrWork;									// se NULL (false) � o fim da lista
				ptrWork = ptrWork->ptrProximo)				// next step do for
			{	// verificar se em ptrWork temos o ponto de inser��o desejado
				if(ptrStCliente->nCodCliente < ptrWork->nCodCliente && // inserir antes do corrente?
					ptrAnterior == NULL)					// e antes do primeiro cliente?
				{	// inser��o antes do primeiro cliente
					ptrSalva = ptrPrimeiro;					// salva o ponteiro do primeiro
					ptrPrimeiro = new CLIENTE;				// espa�o para o novo cliente
					if(ptrPrimeiro == NULL)					// n�o tem mem�ria?
					{	// n�o tem mem�ria e a lista ligada passou a ser vazia
						ptrPrimeiro = ptrSalva;				// restaura a lista
						return false;						// avisa que n�o tem mem�ria
					}
					// temos mem�ria para o recem primeiro da lista
					ptrPrimeiro->nCodCliente = ptrStCliente->nCodCliente; // copia o c�digo
					ptrPrimeiro->dSaldoCliente = ptrStCliente->dSaldoCliente; // copia o saldo
					strcpy_s(ptrPrimeiro->cNomeCliente, ptrStCliente->cNomeCliente); // copia o nome
					ptrPrimeiro->ptrProximo = ptrSalva;		// aponta para quem era o primeiro
					return true;							// avisa que foi tudo OK
				}
				else if(ptrStCliente->nCodCliente < ptrWork->nCodCliente) //antes de um cliente que n�o � o primeiro?
				{	// antes de um cliente que n�o � o primeiro
					ptrSalva = ptrAnterior->ptrProximo;		// salva o endere�o do pr�ximo
					ptrAnterior->ptrProximo = new CLIENTE;	// espa�o de mem�ria para o novo cliente
					if(ptrAnterior->ptrProximo == NULL)		// n�o tem mem�ria?
					{	// a lista vai ser quebrada
						ptrAnterior->ptrProximo = ptrSalva; // restaura a lista
						return false;						// avisa que n�o tem mem�ria
					}
					// temos mem�ria
					ptrAnterior->ptrProximo->nCodCliente = ptrStCliente->nCodCliente; // copia codigo
					ptrAnterior->ptrProximo->dSaldoCliente =
						ptrStCliente->dSaldoCliente;		// copia o saldo
					strcpy_s(ptrAnterior->ptrProximo->cNomeCliente,
						ptrStCliente->cNomeCliente);		// copia o nome
					ptrAnterior->ptrProximo->ptrProximo = ptrSalva; // aponta para quem era o pr�ximo
					return true;							// indica tudo OK
				}
				// vamos testar se � o �ltimo da lista
				if(ptrWork->ptrProximo == NULL)				// � o �ltimo da lista?
				{	// � o �ltimo da lista 
					ptrWork->ptrProximo = new CLIENTE;		// aloca espa�o para o novo cliente
					if(ptrWork->ptrProximo == NULL)			// n�o tem mem�ria?
						return false;						// retorna indicando o erro
					// temos mem�ria
					ptrWork->ptrProximo->nCodCliente = ptrStCliente->nCodCliente; // copia o c�digo
					ptrWork->ptrProximo->dSaldoCliente =
						ptrStCliente->dSaldoCliente;		// copia o saldo
					strcpy_s(ptrWork->ptrProximo->cNomeCliente,
						ptrStCliente->cNomeCliente);		// copia o nome
					ptrWork->ptrProximo->ptrProximo = NULL;	// �ltimo da lista
					return true;							// avisa tudo OK
				}
				ptrAnterior = ptrWork;						// o c�digo do cliente � maior que o corrente
			} // for
		} // else
		return true;						// nunca vai chegar aqui
	}
	// M�todo p�blico que verifica se cliente j� existe
	//	Par�metros:
	//		Entrada: int nCodigo - c�digo do cliente a ser buscado
	//				 CLIENTE *ptrCliente - aponta para uma struct para receber os dados
	//										do cliente encontrado
	//		Retorno: bool - true - cliente foi encontrado
	//						false - cliente n�o existe
	bool VerificaSeClienteExiste(int nCodigo, CLIENTE *ptrStCliente)
	{
		// fazer a varredura da lista
		for(ptrWork = ptrPrimeiro;				// inicia a busca a partir do primeiro
			ptrWork;							// se NULL � false - fim do for e da lista
												// Se n�o NULL � o cliente sendo visto
			ptrWork = ptrWork->ptrProximo)		// ptrWork est� apontado para o corrente
		{
			if(ptrWork->nCodCliente == nCodigo)	// encontrou o cliente?
			{	// cliente existe
				memcpy_s(ptrStCliente, sizeof(CLIENTE), ptrWork, sizeof(CLIENTE));
				return true;					// indica que o cliente foi encontrado
			}
			if(nCodigo < ptrWork->nCodCliente)	// c�digo menor que o do corrente?
				return false;					// avisa que o cliente n�o existe
		} // for
		// cliente n�o existe
		return false;							// avisa que cliente n�o existe
	}

	// M�todo p�blico para listagem de clientes
	void ListarClientes(void)
	{
		char cWork[200];						// para o sprintf
		LIMPAR_TELA;
		cout << "\tListagem de clientes" << endl;
		sprintf_s(cWork, "C�digo Nome Cliente                               Saldo");
		cout << cWork << endl;
		for(ptrWork = ptrPrimeiro; ptrWork; ptrWork = ptrWork->ptrProximo) // loop de varredura
		{	// existe um cliente que est� apontado por ptrWork
			sprintf_s(cWork, "%6d %-40s %9.2f",
				ptrWork->nCodCliente, 
				ptrWork->cNomeCliente,
				ptrWork->dSaldoCliente);
			cout << cWork << endl;
		}
		cout << "\n\tFim da listagem" << endl;
		PAUSA;
	}
	// M�todo p�blico que classifica em ordem crescente uma lista ligada
	//	Par�metros:
	//		Retorno: bool - true - classifica��o OK
	//						false - lista est� vazia
	bool ClassificarListaLigada(void)
	{
		bool flgHouveTroca;						// true - indica que houve troca
		CLIENTE stWork;							// struct para fazer a troca de posi��o
		if(ptrPrimeiro == NULL)					// lista vazia?
			return false;						// avisa que lista vazia
		do
		{
			flgHouveTroca = false;				// n�o houve troca ainda
			for(ptrWork = ptrPrimeiro; ptrWork; ptrWork = ptrWork->ptrProximo) // loop de compara��o
			{	// temos o cliente corrente e o pr�ximo se ptrWork->ptrProximo n�o for nulo
				if(ptrWork->ptrProximo == NULL)	// �ltimo da lista?
					break;
				// temos o corrente e um pr�ximo cliente
				if(ptrWork->nCodCliente > ptrWork->ptrProximo->nCodCliente) // fora de ordem?
				{	// fazer a troca de posi��o dos clientes
					// salvar o cliente corrente em stWork salva o elem[i]
					stWork.nCodCliente = ptrWork->nCodCliente;
					stWork.dSaldoCliente = ptrWork->dSaldoCliente;
					strcpy_s(stWork.cNomeCliente, ptrWork->cNomeCliente);
					// copiar o pr�ximo cliente sobre o cliente corrente
					ptrWork->nCodCliente = ptrWork->ptrProximo->nCodCliente;
					ptrWork->dSaldoCliente = ptrWork->ptrProximo->dSaldoCliente;
					strcpy_s(ptrWork->cNomeCliente, ptrWork->ptrProximo->cNomeCliente);
					// copiar o cliente corrente que foi salvo sobre o pr�ximo cliente
					ptrWork->ptrProximo->nCodCliente = stWork.nCodCliente;
					ptrWork->ptrProximo->dSaldoCliente = stWork.dSaldoCliente;
					strcpy_s(ptrWork->ptrProximo->cNomeCliente, stWork.cNomeCliente);
					flgHouveTroca = true;
				}
			}
		} while(flgHouveTroca);					// enquanto houver troca
		return true;							// avisa que tudo bem
	}
	// M�todo p�blico para excluir um cliente da lista ligada
	bool ExcluirClienteDaLista(int nCodigo)
	{
		CLIENTE *ptrAnterior,					// ponteiro do cliente anterior
			*ptrSalva;							// para salvaguarda de ponteiro
		// loop de busca do cliente a ser excluido
		for(ptrWork = ptrPrimeiro, ptrAnterior = NULL; ptrWork; ptrWork = ptrWork->ptrProximo)
		{
			if(nCodigo == ptrWork->nCodCliente)	// mesmo cliente?
			{	// encontrou o cliente a excluir
				if(ptrAnterior == NULL)			// primeiro cliente da lista?
				{	// primeiro cliente da lista
					ptrSalva = ptrPrimeiro->ptrProximo; // salva o endere�o do pr�ximo
					delete(ptrPrimeiro);			// libera a mem�ria do excluido
					ptrPrimeiro = ptrSalva;			// o primeiro � o pr�ximo da lista
				}
				else
				{	// n�o � o primeiro da lista
					ptrAnterior->ptrProximo = ptrWork->ptrProximo; // encadeia com o pr�ximo
					delete ptrWork;					// libera a mem�ria do excluido
				}
				return true;						// retorna indicando tudo bem
			} // encontrou o cliente
			// este cliente n�o � o desejado
			ptrAnterior = ptrWork;					// salva o corrente como anterior
		} // for
		return false;								// n�o encontrou o cliente desejado
	}
};




