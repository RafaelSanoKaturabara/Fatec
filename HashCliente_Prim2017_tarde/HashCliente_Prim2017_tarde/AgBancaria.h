// Declara��es do programa Ag�ncia Banc�ria com Hash e Cadastro de Clientes
#include <iostream>
#include <Windows.h>
using namespace std;
// defines do programa
#define PAUSA							system("pause")
#define LIMPAR_TELA						system("cls")
#define HASH_MAX						200
#define QTDE_MAX_CLIENTES				5000
#define CAMINHO_CADASTRO				"..\\Cadastro.cad"
//
//	struct para a chave de busca na lista ligada
//
typedef struct tagCHAVE_BUSCA
{
	char cAgCodigo[11],					// c�digo da agencia e codigo
		cAtivo;							// cliente ativo = 'A' e inativo ou excluido = 'I'
	int nPosicional;					// posicional do cliente no cadastro
	tagCHAVE_BUSCA *ptrProxima;			// ponteiro para a pr�xima chave de busca
} CHAVE_BUSCA;
//
// struct do hash da lista ligada
//
typedef struct tagHASH_CODE
{
	CHAVE_BUSCA *ptrPrimeira,			// ponteiro para a primeira chave da lista
		*ptrUltima;						// inser��es sempre na �ltima da lista
} HASH_CODE;
//
// struct do cadastro de clientes
//
typedef struct tagCLIENTE
{
	char cAgCodigo[11],					// c�digo da agencia e codigo
		cAtivo,							// cliente ativo = 'A' e inativo ou excluido = 'I'
		cNomeCliente[41];				// nome do cliente
	double dSaldoCliente;				// saldo do cliente
} CLIENTE;
//
// classe agencia banc�ria
//
class clAgencia
{
	// atributos private da classe
private:
	HASH_CODE vetHashTable[HASH_MAX];	// HASH TABLE com um vetor de hash code
	int nPosProximo;					// posicional do pr�ximo cliente a ser inserido no cadastro
	CLIENTE stCliente;					// struct para conter os dados de um cliente
	FILE *fdCadastro;					// file descriptor do cadastro

	// m�todos p�blicos da classe
public:
	// m�todo construtor
	//	Par�metros:
	//		Entrada: bool *ptrStatus - ponteiro de uma bool que reber� os status da
	//									constru��o da ag�ncia banc�ria
	//									true - tudo OK
	//									false - problema na constru��o
	clAgencia(bool *ptrStatus)
	{
		int i;							// indexador e contador gen�rico
		for(i = 0; i < HASH_MAX; i++)	// loop para inicializar o hash table
			vetHashTable[i].ptrPrimeira = NULL; // todas as listas de chaves est�o vazias
		// vamos remontar o hash table em mem�ria
		// se for a primeira vez que o programa ser� executado iremos
		// "formatar" o cadastro de clientes
		//	abrir o arquivo em r+b = leitura e grava��o e o arquivo precisa existir
		if(fopen_s(&fdCadastro, CAMINHO_CADASTRO, "r+b") != 0) // erro de abertura?
		{	// o arquivo n�o foi encontrado - n�o existe
			// abrir o arquivo em modo w+b - grava��o e leitura e ser� destruido se existir
			if(fopen_s(&fdCadastro, CAMINHO_CADASTRO, "w+b") != 0) // erro de abertura?
			{	// n�o conseguiu abrir o arquivo em modo grava��o e leitura
				cout << "Erro de abertura do cadastro: " << CAMINHO_CADASTRO << endl;
				PAUSA;
				*ptrStatus = false;						// problema no construtor
				return;									// cai fora do construtor
			}
		}

	} // construtor
};





