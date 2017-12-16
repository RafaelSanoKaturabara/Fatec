// Declara��es do algoritmo Binary Search ou Busca Bin�ria ou Acesso Dicot�mico
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
// para gera��o de um arquivo de teste
#define SEMENTE_RANDOM						150
#define CAMINHO_CADASTRO					"..\\Produtos.arq"
#define QTDE_REGISTROS						5000
//
// struct do registro de produtos
//
typedef struct tagPRODUTO
{
	int nCodigo;							// c�digo o produto ou chave prim�ria]
	char cDescricao[41],					// descri��o do produto
		cAtivo;								// 'A' - Produto ativo e 'I' - Inativo
	double dPrecoUnit;						// pre�o unit�rio
} PRODUTO;
//
// Classe Binary Search
//
class clBinarySearch
{
	// atributos private
private:
	PRODUTO stProduto;						// para conter os dados de um produto
	unsigned int nQtdeAcessos,				// quantidade m�xima de acessos
		regInf,								// posicional inferior
		regSup,								// posicional superior
		nQtRegistros;						// quantidade totao de registros
	// m�todos p�blicos 
public:
	// m�todo construtor da classe
	// Par�metros:
	//	Entrada: int nQtRegistros - quantidade total de registros
	clBinarySearch(int nQtRegistros)
	{
		unsigned int nQtdeTrab = nQtRegistros;	// quantitdade total de registros
		this->nQtRegistros = nQtRegistros;		// salva a quantidade de registros
		// divis�o sucessiva por dois para obter nQtdeAcessos - obter 2^^n + 1
		for(nQtdeAcessos = 1; nQtdeTrab > 1; nQtdeAcessos++)	// inicia com mais um na qtde acessos
			nQtdeTrab >>= 1;					// divis�o por 2
#ifdef TESTE
		cout << "Qtde total = " << nQtRegistros << " Qtde max acessos = " << nQtdeAcessos << endl;
		PAUSA;
#endif
	} // construtor

	// Algoritmo de Busca Bin�ria
	//	Par�metros:
	//		Entrada: int nKey - chave de busca do produto
	//				 PRODUTO *ptrStProduto - ponteiro de uma struct do invocador do 
	//										 m�todo a receber os dados do produto se existir
	//				 FILE *fdCadastro - file descriptor de um arquivo que foi aberto pelo 
	//									invocador do m�todo
	//		Ret�rno: bool - true - o produto foi encontrado e seus dados foram copiados 
	//								na struct do invocador do m�todo
	//						false - o produto n�o existe
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
				return false;							// retorna como n�o encontrado
			if(fread_s(&stProduto, sizeof(PRODUTO), sizeof(PRODUTO), 
				1, fdCadastro) == 0)	// erro de leitura
				return false;							// retorna como n�o encontrado
			// um regisro foi lido
			if(nKey == stProduto.nCodigo)				// encontrou?
			{	// encontrou o produto
				// copiar os dados do produto para o invocador do m�todo
				memcpy_s(ptrStProduto, sizeof(PRODUTO), &stProduto, sizeof(PRODUTO));
				return true;							// indica que econtrou 
			}
			else if(nKey > stProduto.nCodigo)			// a chave est� na metade superior
				regInf = regAcessar;					// limite inferior � o registro acessado
			else										// nkey < stProduto.nCodigo
				regSup = regAcessar;					// limite superior � o regAcessar
		} // while
		return false;									// n�o encontrou
	}
};