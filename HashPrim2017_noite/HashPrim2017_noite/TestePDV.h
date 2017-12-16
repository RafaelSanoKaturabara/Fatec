// Declara��es do programa de Ponto de Venda com Hashing
#include <iostream>
#include <Windows.h>
using namespace std;
// defini��es do programa
#define TESTE								1
#define PAUSA								system("pause")
#define LIMPAR_TELA							system("cls")
#define QTDE_MAX_PRODUTOS					3000
#define PERCENTUAL_DE_TESTE					50					// percentual de cria��o de
																// para testes
#define QTDE_HASH							200
#define CAMINHO_CADASTRO					"..\\Produtos.cad" // cadastro de produtos
#define PAIS_BRASIL							setlocale(LC_ALL, "portuguese_brazil")
// op��es do menu
#define INCLUIR_PRODUTO						'I'
#define EXCLUIR_PRODUTO						'E'
#define MOSTRAR_PRODUTO						'M'
#define VENDER_PRODUTO						'V'
#define LISTAR_HASH_CODE					'L'
#define LISTAR_TODOS_HASH_CODE				'T'
#define SAIR_DO_PROGRAMA					'S'

//
// struct da lista ligada de busca da chave
//
typedef struct tagCHAVE_BUSCA
{
	int nPosicional;						// posi��o do produto dentro do cadastro
	char cEAN[14],							// c�digo EAN do produto
		cAtivo;								// 'A' = ativo e 'I' = inativo ou excluido
	tagCHAVE_BUSCA *ptrProxima;				// ponteiro para a pr�xima chave
} CHAVE_BUSCA;

//
// struct do HASH code
//
typedef struct tagHASH
{
	CHAVE_BUSCA *ptrPrimeira,				// ponteiro para a primeira chave de busca da lista
		*ptrUltima;							// ponteiro para a ultima chave da lista
} HASH;

//
// struct de cada produto
//
typedef struct tagPRODUTO
{
	char cEAN[14],							// c�digo EAN do produto
		cAtivo,								// 'A' = ativo e 'I' = inativo ou excluido
		cDescricao[41];						// descri��o do produto
	double dPrecoUnit,						// pre�o unit�rio
		dTotalVendido;						// valor total vendido
} PRODUTO;

//
// classe ponto de venda
//
class clPontoVenda
{
	// atributos private da classe
private:
	HASH vetHashTable[QTDE_HASH];			// vetor de hash do hash table
	PRODUTO stProduto;						// struct para conter um produto
	int nProxProduto;						// posicional do pr�ximo produto a ser inserido
	FILE *fdProduto;						// file descriptor do produto

	// m�todos private
	//	M�todo private que calcula o hash code de um EAN-13
	//		Par�metros:
	//			Entrada: char *ptrEAN - ponteiro para um string que contem 
	//									o EAN do produto
	//		Retorno: int - valor do hash code
	int CalcularHashCode(char *ptrEAN)
	{
		int nSomatorio = 0,					// somat�rio do peso * algarismo ASCII
			i,								// indice e contador gen�rico
			nPeso = 49;						// peso inicial
		// loop de somat�ria
		for(i = 0; i < strlen(ptrEAN); i++)
			nSomatorio += nPeso-- * *(ptrEAN + i); // somat�rio do peso * ASCII
		return nSomatorio % QTDE_HASH;		// retorna o hash code
	}

	// M�todo private que insere uma chave de busca no hash table
	//	Par�metros:
	//		Entrada: int nHash - hash code do EAN (chave) que vai ser inserido
	//				 char *ptrEAN - codigo do produto que � a chave de busca
	//				 int nPosicao - posi��o desse produto no cadastro de produto
	//		Retorno: bool - true - inser��o OK
	//						false - n�o tem mem�ria dispon�vel para nova chave de busca
	bool InsereNoHashTable(int nHash, char *ptrEAN, int nPosicao)
	{
		if(vetHashTable[nHash].ptrPrimeira == NULL)				// lista vazia?
			vetHashTable[nHash].ptrUltima =
			vetHashTable[nHash].ptrPrimeira = new CHAVE_BUSCA;	// aloca mem�ria
		else
			vetHashTable[nHash].ptrUltima =
			vetHashTable[nHash].ptrUltima->ptrProxima = new CHAVE_BUSCA; // aloca mem�ria
		if(vetHashTable[nHash].ptrUltima == NULL)				// sem mem�ria?
			return false;										// avisa o erro
		// preencher a nova chave de busca
		vetHashTable[nHash].ptrUltima->cAtivo = 'A';			// produto ativo
		vetHashTable[nHash].ptrUltima->nPosicional = nPosicao;  // posicional desse EAN
		vetHashTable[nHash].ptrUltima->ptrProxima = NULL;		// indica que �ltima da lista
		strcpy_s(vetHashTable[nHash].ptrUltima->cEAN, 14, ptrEAN); // copia a chave de busca
		return true;											// foi tudo OK
	}

	// M�todo private para ler posicional um produto do cadastro
	//	Par�metros:
	//		Entrada: int nPosicao - posi��o do produto dentro do cadastro
	//				 PRODUTO *ptrStProduto - ponteiro da struct para receber os dados
	//										do produto
	//		Retorno: bool - true - leitura OK
	//						false - erro de seek ou de leitura
	bool LerPosicional(int nPosicao, PRODUTO *ptrStProduto)
	{
		if(fseek(fdProduto, nPosicao * sizeof(PRODUTO), SEEK_SET) != 0) // erro de seek?
			return false;
		if(fread_s(ptrStProduto, sizeof(PRODUTO), sizeof(PRODUTO), 1, fdProduto) == 0) // erro
			return false;
		return true;									// leitura OK
	}
	// M�todo private que grava um produto no cadastro de produto na posi��o indicada
	//	Par�metros:
	//		Entrada: int nPosicao - posi��o relativa desse produto dentro do cadastro
	//				 PRODUTO *ptrStProduto - ponteiro de uma struct que tem os
	//											dados do produto a ser gravado
	//		Retorno: bool - true - grava��o com sucesso
	//						false - erro de seek ou de grava��o
	bool GravaPosicional(int nPosicao, PRODUTO *ptrStProduto)
	{
		if(fseek(fdProduto, nPosicao * sizeof(PRODUTO), SEEK_SET) != 0) // erro de seek?
			return false;
		if(fwrite(ptrStProduto, sizeof(PRODUTO), 1, fdProduto) == 0)	// erro de grava��o?
			return false;
		return true;									// avisa que foi tudo OK
	}
	// m�todos p�blicos da classe
public:
	// M�todo construtor da classe
	//	Par�metros:
	//		Entrada: bool *ptrStatus - ponteiro de uma bool do instanciador da classe
	//									true - indica que a constru��o foi OK
	//									false - indica que a constru��o teve problema
	clPontoVenda(bool *ptrStatus)
	{
		int i;								// indexador e contador gen�rico
		nProxProduto = 0;					// posicional do pr�ximo produto no cadastro
		// loop para indicar que cada hash do hash table tem uma lista vazia
		for(i = 0; i < QTDE_HASH; i++)
			vetHashTable[i].ptrPrimeira = NULL;		// lista vazia deste hash code
		// abrir o cadastro de produtos em modo leitura, grava��o e bin�rio - precisa existir
		if(fopen_s(&fdProduto, CAMINHO_CADASTRO, "r+b") != 0)			// arquivo n�o existe?
		{	// arquivo n�o existe - primeira vez em que o programa � executado
			if(fopen_s(&fdProduto, CAMINHO_CADASTRO, "w+b") != 0)	// erro irrecuper�vel?
			{
				cout << "Erro irrecuper�vel na abertura do arquivo: " << CAMINHO_CADASTRO << endl;
				PAUSA;
				*ptrStatus = false;						// indica problema
				return;									// cai fora do construtor
			}
			// abrimos um arquivo novo - vamos "formatar" esse arquivo de produto
			for(i = 0; i < QTDE_MAX_PRODUTOS; i++)
			{
				stProduto.cAtivo = 'F';					// indica formatado
				stProduto.cEAN[0] = NULL;				// string vazio
				stProduto.cDescricao[0] = NULL;			// idem
				stProduto.dPrecoUnit = stProduto.dTotalVendido = 0.0;
				// gravar esse produto
				if(fwrite(&stProduto, sizeof(PRODUTO), 1, fdProduto) == 0) // erro de grava��o?
				{
					fclose(fdProduto);
					*ptrStatus = false;					// avisa que houve problema
					cout << "Erro de grava��o!" << endl;
					PAUSA;
					return;								// cai fora do construtor
				}
			} // for
#ifdef TESTE
			// gerar produtos para melhor testar o programa
			srand(500);									// semente random
			for(i = 0; i < QTDE_MAX_PRODUTOS * PERCENTUAL_DE_TESTE / 100; i++)
			{	// loop de cria��o de produtos
				_itoa_s(rand(), stProduto.cEAN, 14, 10);	// string que cont�m o c�digo EAN
				if(VerificaSeExiste(stProduto.cEAN, &stProduto))	// produto j� existe?
				{	// produto j� existe
					i--;									// desconsidera esse c�digo
					continue;								// vai tentar o pr�ximo
				}
				// produto n�o existe vai ser incluido
				sprintf_s(stProduto.cDescricao, 40, "Produto de codigo %s",
					stProduto.cEAN);						// descri��o do produto
				stProduto.dPrecoUnit = rand() * 0.937;		// pre�o unit�rio
				stProduto.dTotalVendido = 0.0;				// total vendido
				if(!IncluirNovoProduto(&stProduto))			// erro na inclus�o?
				{	
					fclose(fdProduto);						// fechar o arquivo
					*ptrStatus = false;						// avisa o instanciador da classe
					cout << "Erro na inclus�o de produtos no teste" << endl;
					PAUSA;
					return;									// cai fora do construtor
				}
			} // for
#endif
		} // arquivo n�o existe
		else
		{	// o arquivo de produtos j� existe
			// leitura sequencial e criar o hash table na mem�ria
			while(true)									// loop infinito
			{
				if(fread_s(&stProduto, sizeof(PRODUTO), sizeof(PRODUTO),
					1, fdProduto) == 0) // erro de leitura?
				{	
					fclose(fdProduto);					// fecha o arquivo
					*ptrStatus = false;					// avisa o erro
					cout << "Erro de leitura!" << endl;
					PAUSA;
					return;								// cai fora do construtor
				}
				// foi lido um registro com sucesso
				if(stProduto.cAtivo == 'F')				// fim do arquivo?
					break;								// cai fora do while
				if(stProduto.cAtivo != 'A')				// produto inativo?
				{	// ler o proximo produto e considerar o seu posicional
					nProxProduto++;						// considera esse posicional
					continue;							// continua no while e l� o pr�ximo
				}
				// inserir a chave de busca deste produto ativo
				// calcular o Hash e inserir na lista deste hash
				if(!InsereNoHashTable(CalcularHashCode(stProduto.cEAN),
					stProduto.cEAN, nProxProduto))		// erro de inser��o?
				{
					fclose(fdProduto);					// fecha o arquivo
					*ptrStatus = false;					// avisa o erro
					cout << "N�o tem mem�ria para a chave de busca!" << endl;
					PAUSA;
					return;								// cai fora do construtor
				}
				nProxProduto++;							// incrementa para o proximo produto
			} // while
			*ptrStatus = true;							// foi tudo OK
		} // arquivo existe
		*ptrStatus = true;
	} // construtor 
	// M�todo p�blico que verifica se o produto j� est� cadastrado
	//	Par�metros:
	//		Entrada: char *ptrEAN - ponteiro do string que tem o EAN do produto
	//				 PRODUTO *ptrStProduto - ponteiro de uma struct que ir�
	//										receber os dados do produto se ele existir
	//		Retorno: bool - true - o produto existe e seus dados foram copiados
	//								para o invocador do m�todo
	//						false - o produto n�o existe
	bool VerificaSeExiste(char *ptrEAN, PRODUTO *ptrStProduto)
	{
		CHAVE_BUSCA *ptrCorrente;						// aponta para chave corrente
		int nHash = CalcularHashCode(ptrEAN);			// calcular o hash code
		for(ptrCorrente = vetHashTable[nHash].ptrPrimeira;
			ptrCorrente;								// se NULL fim da lista
			ptrCorrente = ptrCorrente->ptrProxima)		// aponta para a pr�xima chave
		{	// tenho uma chave de busca
			if(ptrCorrente->cAtivo != 'A')				// produto inativo?
				continue;								// vai buscar a pr�xima chave
			if(strcmp(ptrCorrente->cEAN, ptrEAN) == 0)	// mesmo c�digo?
			{	// vai buscar os dados deste produto no cadastro - leitura posicional
				if(!LerPosicional(ptrCorrente->nPosicional, ptrStProduto)) // erro
					return false;
				return true;							// indica que tem o produto
			}
		} // for
		return false;									// n�o encontrou o produto
	}
	// M�todo p�blico para inser��o de um novo produto no cadastro
	//	Par�metros:
	//		Entrada: PRODUTO *ptrStProduto - ponteiro para uma struct que
	//										cont�m todos os dados do produto
	//										Essa struct est� no invocador deste m�todo
	//		Retorno: bool - true - a inclus�o foi OK
	//						false - houve problema na inclus�o 
	bool IncluirNovoProduto(PRODUTO *ptrStProduto)
	{
		int nHash = CalcularHashCode(ptrStProduto->cEAN);	// calcular o Hash Code desse produto
		ptrStProduto->cAtivo = 'A';							// produto ativo
		if(!GravaPosicional(nProxProduto, ptrStProduto))	// erro de grava��o?
			return false;									// avisa que tem erro
		if(!InsereNoHashTable(nHash, ptrStProduto->cEAN, nProxProduto)) // erro na inser��o?
			return false;
		nProxProduto++;										// posiciona para proximo produto
		return true;										// avisa que tudo OK
	}
	// M�todo p�blico que fecha o cadastro
	void FecharCadastro(void)
	{
		fclose(fdProduto);									// fechar o cadastro
	}
	// M�todo p�blico que lista todos os c�digos EAN do mesmo Hash Code
	//	Par�metros:
	//		Entrada: int nHash - valor do hash code a ser listado
	//		Retorno: bool - true - tem chaves de busca neste hash code e foram listados
	//						false - n�o tem chave de busca porque o hash code est� vazio
	bool ListarCodigosDeHashCode(int nHash)
	{
		int nQtde = 0,								// qtde de chaves encontradas
			nLinha = 0;								// contador por linha
		CHAVE_BUSCA *ptrCorrente;					// chave de busca corrente
		if(vetHashTable[nHash].ptrPrimeira == NULL) // lista vazia?
			return false;							// retorna indicando vazia
		for(ptrCorrente = vetHashTable[nHash].ptrPrimeira; 
			ptrCorrente;							// nulo � fim da lista
			ptrCorrente = ptrCorrente->ptrProxima)	// indexa para pr�xima chave
		{	// no ptrCorrente - tem uma chave de busca
			if(ptrCorrente->cAtivo != 'A')			// inativa?
				continue;							// vai para a pr�xima
			if(nLinha >= 8)							// j� listou 8 na linha
			{
				nLinha = 0;							// inicializa
				cout << endl;						// pula de linha
			}
			// listar um c�digo
			cout << ptrCorrente->cEAN << "\t";
			nLinha++;								// um a mais na linha
			nQtde++;								// mais uma chave de busca no Hash
		} // for
		cout << endl << "\tHash " << nHash << " Qtde: " << nQtde << endl;
	}
};










