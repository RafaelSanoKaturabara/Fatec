// Declara��es do programa de ponto de venda com hashing
#include<iostream>
#include<Windows.h>
using namespace std;
// defini��es do programa
#define PAUSA								system("pause")
#define LIMPAR_TELA							syste("cls")
#define QTDE_MAX_PRODUTOS					3000
#define QTDE_HASH							200
#define CAMINHO_CADASTRO					"..\\Produtos.cad"	// cadastro de produtos
//
// struct da lista ligada de busca da chave
//
typedef struct tagCHAVE_BUSCA
{
	int nPosicional;							// posi��o do produto dentro do cadastro
	char cEAN[14],								// c�digo EAN do produto
		cAtivo;									// 'A' = Ativo e 'I' = Inativo ou exclu�do
	tagCHAVE_BUSCA *ptrProxima;					// ponteiro para a pr�xima chave
} CHAVE_BUSCA;

//
// struct do HASH code
typedef struct tagHASH
{
	CHAVE_BUSCA *ptrPrimeira,					// ponteiro para a primeira chave de busca da lista
		*ptrUltima;								// ponteiro para a ultima chave da lista
} HASH;

//
// struct de cada produto
typedef struct tagPRODUTO
{
	char cEAN[14],								// c�digo EAN do produto
		cAtivo,									// 'A' = Ativo e 'I' = Inativo ou exclu�do
		cDescricao[41];							// descri��o do produto
	double dPrecoUnit,							// pre�o unit�rio
		dTotalVendido;							// valor total vendido
} PRODUTO;

//
// classe ponto de venda
//
class clPontoVenda
{
	// atriburos private da classe
private:
	HASH vetHashTable[QTDE_HASH];				// vetor de hash do hash table
	PRODUTO stProduto;							// struct para conter um produto
	int nProxProduto;							// posicional do pr�ximo produto a ser inserido
	FILE *fdProduto;							// file descriptor do produto

	// M�todos p�blicos da classe
public:
	// M�todo construtor da classe
	//	Par�metros:
	//		Entrada: Bool *ptrStatus - ponteiro de uma bool do instanciador da classe
	//									true - indica que a constru��o foi ok
	//									false - indica que a constru��o teve problema
	clPontoVenda(bool *ptrStatus)
	{
		int i;									// indexador e contador gen�rico
		nProxProduto = 0;						// posicional do pr�ximo produto no cadastro
		// loop para indicar que cada hash do hash table tem uma lista vazia
		for(i = 0; i < QTDE_HASH; i++)
			vetHashTable[i].ptrPrimeira = NULL;		// lista vazia deste hash code
		// abrir o cadastro de produtos em modo leitura, grava��o e bin�rio - precisa existir
		if(fopen_s(&fdProduto, CAMINHO_CADASTRO, "r+b") != 0)		// arquivo n�o existe?
		{	// arquivo n�o existe - primeira vez em que o programa � executado
			if(fopen_s(&fdProduto, CAMINHO_CADASTRO, "w+b") != 0)	// erro irrecuper�vel?
			{
				cout << "Erro irrecuper�vel na abertura do arquivo: " << CAMINHO_CADASTRO << endl;
				PAUSA;
				*ptrStatus = false;				// indica problema
				return;							// cai fora do construtor
			}
		}
		// abrimos um arquivo novo - vamos "formatar" esse arquivo de produto
		for(i = 0; i < QTDE_MAX_PRODUTOS; i++)
		{
			stProduto.cAtivo = 'F';				// indica formatado
			stProduto.cEAN[0] = NULL;			// string vazio
			stProduto.cDescricao[0] = NULL;		// idem
			stProduto.dPrecoUnit = stProduto.dTotalVendido = 0.0;
			// gravar esse produto
		}
	}
};
