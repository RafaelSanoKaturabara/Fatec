// Declarações do programa de ponto de venda com hashing
#include<iostream>
#include<Windows.h>
using namespace std;
// definições do programa
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
	int nPosicional;							// posição do produto dentro do cadastro
	char cEAN[14],								// código EAN do produto
		cAtivo;									// 'A' = Ativo e 'I' = Inativo ou excluído
	tagCHAVE_BUSCA *ptrProxima;					// ponteiro para a próxima chave
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
	char cEAN[14],								// código EAN do produto
		cAtivo,									// 'A' = Ativo e 'I' = Inativo ou excluído
		cDescricao[41];							// descrição do produto
	double dPrecoUnit,							// preço unitário
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
	int nProxProduto;							// posicional do próximo produto a ser inserido
	FILE *fdProduto;							// file descriptor do produto

	// Métodos públicos da classe
public:
	// Método construtor da classe
	//	Parâmetros:
	//		Entrada: Bool *ptrStatus - ponteiro de uma bool do instanciador da classe
	//									true - indica que a construção foi ok
	//									false - indica que a construção teve problema
	clPontoVenda(bool *ptrStatus)
	{
		int i;									// indexador e contador genérico
		nProxProduto = 0;						// posicional do próximo produto no cadastro
		// loop para indicar que cada hash do hash table tem uma lista vazia
		for(i = 0; i < QTDE_HASH; i++)
			vetHashTable[i].ptrPrimeira = NULL;		// lista vazia deste hash code
		// abrir o cadastro de produtos em modo leitura, gravação e binário - precisa existir
		if(fopen_s(&fdProduto, CAMINHO_CADASTRO, "r+b") != 0)		// arquivo não existe?
		{	// arquivo não existe - primeira vez em que o programa é executado
			if(fopen_s(&fdProduto, CAMINHO_CADASTRO, "w+b") != 0)	// erro irrecuperável?
			{
				cout << "Erro irrecuperável na abertura do arquivo: " << CAMINHO_CADASTRO << endl;
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
