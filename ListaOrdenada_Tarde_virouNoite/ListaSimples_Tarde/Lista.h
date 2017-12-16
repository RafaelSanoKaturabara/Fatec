// Declarações e Classe da Lista Ligada Simples
#include <iostream>
#include <Windows.h>
using namespace std;
// definições
#define PAUSA								system("pause")
#define LIMPAR_TELA							system("cls")
// opções do menu
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
	int nCodCliente;						// código de cliente
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
	// métodos públicos da classe
public:
	// Método construtor
	clCliente()
	{
		ptrPrimeiro = NULL;					// lista vazia
	}
	// Método público para inserção de cliente de forma ordenada
	//	Parâmetros:
	//		Entrada: CLIENTE *ptrStCliente - ponteiro para uma struct que contém os dados
	//										do cliente a ser inserido
	//		Retorno: bool - true - inserção OK
	//						false - não tem memória disponível para inserção
	bool InserirCliente(CLIENTE *ptrStCliente)
	{
		CLIENTE *ptrAnterior,					// ponteiro do cliente anterior
			*ptrSalva;							// para salvaguarda de ponteiro
		if(ptrPrimeiro == NULL)				// primeiro da lista?
		{
			ptrPrimeiro = new CLIENTE;		// aloca memória para um cliente
			// verificar se tem memória
			if(ptrPrimeiro == NULL)			// não tem memória?
				return false;				// avisa que não tem
			ptrPrimeiro->nCodCliente = ptrStCliente->nCodCliente; // copia o código do cliente
			ptrPrimeiro->dSaldoCliente = ptrStCliente->dSaldoCliente; // copia o saldo
			strcpy_s(ptrPrimeiro->cNomeCliente, ptrStCliente->cNomeCliente); // copia o nome
			ptrPrimeiro->ptrProximo = NULL;	// primeiro e último
			return true;					// indica tudo OK
		}
		else								// não é o primeiro
		{	
			for(ptrWork = ptrPrimeiro, ptrAnterior = NULL;	 // inicialização
				ptrWork;									// se NULL (false) é o fim da lista
				ptrWork = ptrWork->ptrProximo)				// next step do for
			{	// verificar se em ptrWork temos o ponto de inserção desejado
				if(ptrStCliente->nCodCliente < ptrWork->nCodCliente && // inserir antes do corrente?
					ptrAnterior == NULL)					// e antes do primeiro cliente?
				{	// inserção antes do primeiro cliente
					ptrSalva = ptrPrimeiro;					// salva o ponteiro do primeiro
					ptrPrimeiro = new CLIENTE;				// espaço para o novo cliente
					if(ptrPrimeiro == NULL)					// não tem memória?
					{	// não tem memória e a lista ligada passou a ser vazia
						ptrPrimeiro = ptrSalva;				// restaura a lista
						return false;						// avisa que não tem memória
					}
					// temos memória para o recem primeiro da lista
					ptrPrimeiro->nCodCliente = ptrStCliente->nCodCliente; // copia o código
					ptrPrimeiro->dSaldoCliente = ptrStCliente->dSaldoCliente; // copia o saldo
					strcpy_s(ptrPrimeiro->cNomeCliente, ptrStCliente->cNomeCliente); // copia o nome
					ptrPrimeiro->ptrProximo = ptrSalva;		// aponta para quem era o primeiro
					return true;							// avisa que foi tudo OK
				}
				else if(ptrStCliente->nCodCliente < ptrWork->nCodCliente) //antes de um cliente que não é o primeiro?
				{	// antes de um cliente que não é o primeiro
					ptrSalva = ptrAnterior->ptrProximo;		// salva o endereço do próximo
					ptrAnterior->ptrProximo = new CLIENTE;	// espaço de memória para o novo cliente
					if(ptrAnterior->ptrProximo == NULL)		// não tem memória?
					{	// a lista vai ser quebrada
						ptrAnterior->ptrProximo = ptrSalva; // restaura a lista
						return false;						// avisa que não tem memória
					}
					// temos memória
					ptrAnterior->ptrProximo->nCodCliente = ptrStCliente->nCodCliente; // copia codigo
					ptrAnterior->ptrProximo->dSaldoCliente =
						ptrStCliente->dSaldoCliente;		// copia o saldo
					strcpy_s(ptrAnterior->ptrProximo->cNomeCliente,
						ptrStCliente->cNomeCliente);		// copia o nome
					ptrAnterior->ptrProximo->ptrProximo = ptrSalva; // aponta para quem era o próximo
					return true;							// indica tudo OK
				}
				// vamos testar se é o último da lista
				if(ptrWork->ptrProximo == NULL)				// é o último da lista?
				{	// é o último da lista 
					ptrWork->ptrProximo = new CLIENTE;		// aloca espaço para o novo cliente
					if(ptrWork->ptrProximo == NULL)			// não tem memória?
						return false;						// retorna indicando o erro
					// temos memória
					ptrWork->ptrProximo->nCodCliente = ptrStCliente->nCodCliente; // copia o código
					ptrWork->ptrProximo->dSaldoCliente =
						ptrStCliente->dSaldoCliente;		// copia o saldo
					strcpy_s(ptrWork->ptrProximo->cNomeCliente,
						ptrStCliente->cNomeCliente);		// copia o nome
					ptrWork->ptrProximo->ptrProximo = NULL;	// último da lista
					return true;							// avisa tudo OK
				}
				ptrAnterior = ptrWork;						// o código do cliente é maior que o corrente
			} // for
		} // else
		return true;						// nunca vai chegar aqui
	}
	// Método público que verifica se cliente já existe
	//	Parâmetros:
	//		Entrada: int nCodigo - código do cliente a ser buscado
	//				 CLIENTE *ptrCliente - aponta para uma struct para receber os dados
	//										do cliente encontrado
	//		Retorno: bool - true - cliente foi encontrado
	//						false - cliente não existe
	bool VerificaSeClienteExiste(int nCodigo, CLIENTE *ptrStCliente)
	{
		// fazer a varredura da lista
		for(ptrWork = ptrPrimeiro;				// inicia a busca a partir do primeiro
			ptrWork;							// se NULL é false - fim do for e da lista
												// Se nâo NULL é o cliente sendo visto
			ptrWork = ptrWork->ptrProximo)		// ptrWork está apontado para o corrente
		{
			if(ptrWork->nCodCliente == nCodigo)	// encontrou o cliente?
			{	// cliente existe
				memcpy_s(ptrStCliente, sizeof(CLIENTE), ptrWork, sizeof(CLIENTE));
				return true;					// indica que o cliente foi encontrado
			}
			if(nCodigo < ptrWork->nCodCliente)	// código menor que o do corrente?
				return false;					// avisa que o cliente não existe
		} // for
		// cliente não existe
		return false;							// avisa que cliente não existe
	}

	// Método público para listagem de clientes
	void ListarClientes(void)
	{
		char cWork[200];						// para o sprintf
		LIMPAR_TELA;
		cout << "\tListagem de clientes" << endl;
		sprintf_s(cWork, "Código Nome Cliente                               Saldo");
		cout << cWork << endl;
		for(ptrWork = ptrPrimeiro; ptrWork; ptrWork = ptrWork->ptrProximo) // loop de varredura
		{	// existe um cliente que está apontado por ptrWork
			sprintf_s(cWork, "%6d %-40s %9.2f",
				ptrWork->nCodCliente, 
				ptrWork->cNomeCliente,
				ptrWork->dSaldoCliente);
			cout << cWork << endl;
		}
		cout << "\n\tFim da listagem" << endl;
		PAUSA;
	}
	// Método público que classifica em ordem crescente uma lista ligada
	//	Parâmetros:
	//		Retorno: bool - true - classificação OK
	//						false - lista está vazia
	bool ClassificarListaLigada(void)
	{
		bool flgHouveTroca;						// true - indica que houve troca
		CLIENTE stWork;							// struct para fazer a troca de posição
		if(ptrPrimeiro == NULL)					// lista vazia?
			return false;						// avisa que lista vazia
		do
		{
			flgHouveTroca = false;				// não houve troca ainda
			for(ptrWork = ptrPrimeiro; ptrWork; ptrWork = ptrWork->ptrProximo) // loop de comparação
			{	// temos o cliente corrente e o próximo se ptrWork->ptrProximo não for nulo
				if(ptrWork->ptrProximo == NULL)	// último da lista?
					break;
				// temos o corrente e um próximo cliente
				if(ptrWork->nCodCliente > ptrWork->ptrProximo->nCodCliente) // fora de ordem?
				{	// fazer a troca de posição dos clientes
					// salvar o cliente corrente em stWork salva o elem[i]
					stWork.nCodCliente = ptrWork->nCodCliente;
					stWork.dSaldoCliente = ptrWork->dSaldoCliente;
					strcpy_s(stWork.cNomeCliente, ptrWork->cNomeCliente);
					// copiar o próximo cliente sobre o cliente corrente
					ptrWork->nCodCliente = ptrWork->ptrProximo->nCodCliente;
					ptrWork->dSaldoCliente = ptrWork->ptrProximo->dSaldoCliente;
					strcpy_s(ptrWork->cNomeCliente, ptrWork->ptrProximo->cNomeCliente);
					// copiar o cliente corrente que foi salvo sobre o próximo cliente
					ptrWork->ptrProximo->nCodCliente = stWork.nCodCliente;
					ptrWork->ptrProximo->dSaldoCliente = stWork.dSaldoCliente;
					strcpy_s(ptrWork->ptrProximo->cNomeCliente, stWork.cNomeCliente);
					flgHouveTroca = true;
				}
			}
		} while(flgHouveTroca);					// enquanto houver troca
		return true;							// avisa que tudo bem
	}
	// Método público para excluir um cliente da lista ligada
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
					ptrSalva = ptrPrimeiro->ptrProximo; // salva o endereço do próximo
					delete(ptrPrimeiro);			// libera a memória do excluido
					ptrPrimeiro = ptrSalva;			// o primeiro é o próximo da lista
				}
				else
				{	// não é o primeiro da lista
					ptrAnterior->ptrProximo = ptrWork->ptrProximo; // encadeia com o próximo
					delete ptrWork;					// libera a memória do excluido
				}
				return true;						// retorna indicando tudo bem
			} // encontrou o cliente
			// este cliente não é o desejado
			ptrAnterior = ptrWork;					// salva o corrente como anterior
		} // for
		return false;								// não encontrou o cliente desejado
	}
};




