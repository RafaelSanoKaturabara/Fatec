// Declarações do algoritmo Binary Search ou Busca Binária ou Acesso Dicotômico
// para testes
//#define TESTE								1
#include <iostream>
#include <Windows.h>
using namespace std;
// define 
#define PAUSA								system("pause")
#define LIMPAR_TELA							system("cls")
#define PAIS_BRASIL							setlocale(LC_ALL, "portuguese_brazil")
// menu do operador
#define MOSTRAR_PRODUTO						'M'
#define EXCLUIR_PRODUTO						'E'
#define	LISTAR_PRODUTOS						'L'
#define SAIR_DO_PROGRAMA					'S'
// para geração de um arquivo de teste
#define SEMENTE_RANDOM						150
#define CAMINHO_CADASTRO					"..\\Produtos.arq"
#define QTDE_REGISTROS						5000
//
// struct do registro de produtos
//
typedef struct tagPRODUTO
{
	int nCodigo;							// código o produto ou chave primária]
	char cDescricao[41],					// descrição do produto
		cAtivo;								// 'A' - Produto ativo e 'I' - Inativo
	double dPrecoUnit;						// preço unitário
} PRODUTO;
//
// Classe Binary Search
//
class clBinarySearch
{
	// atributos private
private:
	PRODUTO stProduto;						// para conter os dados de um produto
	unsigned int nQtdeAcessos,				// quantidade máxima de acessos
		regInf,								// posicional inferior
		regSup,								// posicional superior
		nQtRegistros;						// quantidade totao de registros
	// métodos públicos 
public:
	// método construtor da classe
	// Parâmetros:
	//	Entrada: int nQtRegistros - quantidade total de registros
	clBinarySearch(int nQtRegistros)
	{
		unsigned int nQtdeTrab = nQtRegistros;	// quantitdade total de registros
		this->nQtRegistros = nQtRegistros;		// salva a quantidade de registros
		// divisão sucessiva por dois para obter nQtdeAcessos - obter 2^^n + 1
		for(nQtdeAcessos = 1; nQtdeTrab > 1; nQtdeAcessos++)	// inicia com mais um na qtde acessos
			nQtdeTrab >>= 1;					// divisão por 2
#ifdef TESTE
		cout << "Qtde total = " << nQtRegistros << " Qtde max acessos = " << nQtdeAcessos << endl;
		PAUSA;
#endif
	} // construtor

	// Algoritmo de Busca Binária
	//	Parâmetros:
	//		Entrada: int nKey - chave de busca do produto
	//				 PRODUTO *ptrStProduto - ponteiro de uma struct do invocador do 
	//										 método a receber os dados do produto se existir
	//				 FILE *fdCadastro - file descriptor de um arquivo que foi aberto pelo 
	//									invocador do método
	//		Retôrno: bool - true - o produto foi encontrado e seus dados foram copiados 
	//								na struct do invocador do método
	//						false - o produto não existe
	bool BinarySearch(int nKey, PRODUTO *ptrStProduto, FILE *fdCadastro)
	{
		unsigned int nQtdeAcessos = this->nQtdeAcessos;	// busca a qtde max de acessos
		int regAcessar;									// posicioal do registro a ser acessado
		// inicializar os extremos do primeiro acesso
		regInf = 0;										// extremo inferior
		regSup = nQtRegistros;							// extremo superior (qtde total de registros)
		// loop de acesso
		while(nQtdeAcessos)
		{
			nQtdeAcessos--;								// menos um
			// calcular o regAcessar
			regAcessar = ((regSup - regInf) / 2) + regInf;	// posicional a acessar
			// acesasr o registro do produto
			if(fseek(fdCadastro, regAcessar * sizeof(PRODUTO), SEEK_SET) != 0)	// erro de seek?
				return false;							// retorna como não encontrado
			if(fread_s(&stProduto, sizeof(PRODUTO), sizeof(PRODUTO), 
				1, fdCadastro) == 0)	// erro de leitura
				return false;							// retorna como não encontrado
			// um regisro foi lido
			if(nKey == stProduto.nCodigo)				// encontrou?
			{	// encontrou o produto
				// copiar os dados do produto para o invocador do método
				memcpy_s(ptrStProduto, sizeof(PRODUTO), &stProduto, sizeof(PRODUTO));
				return true;							// indica que econtrou 
			}
			else if(nKey > stProduto.nCodigo)			// a chave está na metade superior
				regInf = regAcessar;					// limite inferior é o registro acessado
			else										// nkey < stProduto.nCodigo
				regSup = regAcessar;					// limite superior é o regAcessar
		} // while
		return false;									// não encontrou
	}
};