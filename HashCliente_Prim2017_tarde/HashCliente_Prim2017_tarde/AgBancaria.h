// Declarações do programa Agência Bancária com Hash e Cadastro de Clientes
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
	char cAgCodigo[11],					// código da agencia e codigo
		cAtivo;							// cliente ativo = 'A' e inativo ou excluido = 'I'
	int nPosicional;					// posicional do cliente no cadastro
	tagCHAVE_BUSCA *ptrProxima;			// ponteiro para a próxima chave de busca
} CHAVE_BUSCA;
//
// struct do hash da lista ligada
//
typedef struct tagHASH_CODE
{
	CHAVE_BUSCA *ptrPrimeira,			// ponteiro para a primeira chave da lista
		*ptrUltima;						// inserções sempre na última da lista
} HASH_CODE;
//
// struct do cadastro de clientes
//
typedef struct tagCLIENTE
{
	char cAgCodigo[11],					// código da agencia e codigo
		cAtivo,							// cliente ativo = 'A' e inativo ou excluido = 'I'
		cNomeCliente[41];				// nome do cliente
	double dSaldoCliente;				// saldo do cliente
} CLIENTE;
//
// classe agencia bancária
//
class clAgencia
{
	// atributos private da classe
private:
	HASH_CODE vetHashTable[HASH_MAX];	// HASH TABLE com um vetor de hash code
	int nPosProximo;					// posicional do próximo cliente a ser inserido no cadastro
	CLIENTE stCliente;					// struct para conter os dados de um cliente
	FILE *fdCadastro;					// file descriptor do cadastro

	// métodos públicos da classe
public:
	// método construtor
	//	Parâmetros:
	//		Entrada: bool *ptrStatus - ponteiro de uma bool que reberá os status da
	//									construção da agência bancária
	//									true - tudo OK
	//									false - problema na construção
	clAgencia(bool *ptrStatus)
	{
		int i;							// indexador e contador genérico
		for(i = 0; i < HASH_MAX; i++)	// loop para inicializar o hash table
			vetHashTable[i].ptrPrimeira = NULL; // todas as listas de chaves estão vazias
		// vamos remontar o hash table em memória
		// se for a primeira vez que o programa será executado iremos
		// "formatar" o cadastro de clientes
		//	abrir o arquivo em r+b = leitura e gravação e o arquivo precisa existir
		if(fopen_s(&fdCadastro, CAMINHO_CADASTRO, "r+b") != 0) // erro de abertura?
		{	// o arquivo não foi encontrado - não existe
			// abrir o arquivo em modo w+b - gravação e leitura e será destruido se existir
			if(fopen_s(&fdCadastro, CAMINHO_CADASTRO, "w+b") != 0) // erro de abertura?
			{	// não conseguiu abrir o arquivo em modo gravação e leitura
				cout << "Erro de abertura do cadastro: " << CAMINHO_CADASTRO << endl;
				PAUSA;
				*ptrStatus = false;						// problema no construtor
				return;									// cai fora do construtor
			}
		}

	} // construtor
};





