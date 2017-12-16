// Declarações do programa de Ponto de Venda com Hashing
#include <iostream>
#include <Windows.h>
using namespace std;
// definições do programa
#define TESTE								1
#define PAUSA								system("pause")
#define LIMPAR_TELA							system("cls")
#define QTDE_MAX_PRODUTOS					3000
#define PERCENTUAL_DE_TESTE					50					// percentual de criação de
																// para testes
#define QTDE_HASH							200
#define CAMINHO_CADASTRO					"..\\Produtos.cad" // cadastro de produtos
#define PAIS_BRASIL							setlocale(LC_ALL, "portuguese_brazil")
// opções do menu
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
	int nPosicional;						// posição do produto dentro do cadastro
	char cEAN[14],							// código EAN do produto
		cAtivo;								// 'A' = ativo e 'I' = inativo ou excluido
	tagCHAVE_BUSCA *ptrProxima;				// ponteiro para a próxima chave
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
	char cEAN[14],							// código EAN do produto
		cAtivo,								// 'A' = ativo e 'I' = inativo ou excluido
		cDescricao[41];						// descrição do produto
	double dPrecoUnit,						// preço unitário
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
	int nProxProduto;						// posicional do próximo produto a ser inserido
	FILE *fdProduto;						// file descriptor do produto

	// métodos private
	//	Método private que calcula o hash code de um EAN-13
	//		Parâmetros:
	//			Entrada: char *ptrEAN - ponteiro para um string que contem 
	//									o EAN do produto
	//		Retorno: int - valor do hash code
	int CalcularHashCode(char *ptrEAN)
	{
		int nSomatorio = 0,					// somatório do peso * algarismo ASCII
			i,								// indice e contador genérico
			nPeso = 49;						// peso inicial
		// loop de somatória
		for(i = 0; i < strlen(ptrEAN); i++)
			nSomatorio += nPeso-- * *(ptrEAN + i); // somatório do peso * ASCII
		return nSomatorio % QTDE_HASH;		// retorna o hash code
	}

	// Método private que insere uma chave de busca no hash table
	//	Parâmetros:
	//		Entrada: int nHash - hash code do EAN (chave) que vai ser inserido
	//				 char *ptrEAN - codigo do produto que é a chave de busca
	//				 int nPosicao - posição desse produto no cadastro de produto
	//		Retorno: bool - true - inserção OK
	//						false - não tem memória disponível para nova chave de busca
	bool InsereNoHashTable(int nHash, char *ptrEAN, int nPosicao)
	{
		if(vetHashTable[nHash].ptrPrimeira == NULL)				// lista vazia?
			vetHashTable[nHash].ptrUltima =
			vetHashTable[nHash].ptrPrimeira = new CHAVE_BUSCA;	// aloca memória
		else
			vetHashTable[nHash].ptrUltima =
			vetHashTable[nHash].ptrUltima->ptrProxima = new CHAVE_BUSCA; // aloca memória
		if(vetHashTable[nHash].ptrUltima == NULL)				// sem memória?
			return false;										// avisa o erro
		// preencher a nova chave de busca
		vetHashTable[nHash].ptrUltima->cAtivo = 'A';			// produto ativo
		vetHashTable[nHash].ptrUltima->nPosicional = nPosicao;  // posicional desse EAN
		vetHashTable[nHash].ptrUltima->ptrProxima = NULL;		// indica que última da lista
		strcpy_s(vetHashTable[nHash].ptrUltima->cEAN, 14, ptrEAN); // copia a chave de busca
		return true;											// foi tudo OK
	}

	// Método private para ler posicional um produto do cadastro
	//	Parâmetros:
	//		Entrada: int nPosicao - posição do produto dentro do cadastro
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
	// Método private que grava um produto no cadastro de produto na posição indicada
	//	Parâmetros:
	//		Entrada: int nPosicao - posição relativa desse produto dentro do cadastro
	//				 PRODUTO *ptrStProduto - ponteiro de uma struct que tem os
	//											dados do produto a ser gravado
	//		Retorno: bool - true - gravação com sucesso
	//						false - erro de seek ou de gravação
	bool GravaPosicional(int nPosicao, PRODUTO *ptrStProduto)
	{
		if(fseek(fdProduto, nPosicao * sizeof(PRODUTO), SEEK_SET) != 0) // erro de seek?
			return false;
		if(fwrite(ptrStProduto, sizeof(PRODUTO), 1, fdProduto) == 0)	// erro de gravação?
			return false;
		return true;									// avisa que foi tudo OK
	}
	// métodos públicos da classe
public:
	// Método construtor da classe
	//	Parâmetros:
	//		Entrada: bool *ptrStatus - ponteiro de uma bool do instanciador da classe
	//									true - indica que a construção foi OK
	//									false - indica que a construção teve problema
	clPontoVenda(bool *ptrStatus)
	{
		int i;								// indexador e contador genérico
		nProxProduto = 0;					// posicional do próximo produto no cadastro
		// loop para indicar que cada hash do hash table tem uma lista vazia
		for(i = 0; i < QTDE_HASH; i++)
			vetHashTable[i].ptrPrimeira = NULL;		// lista vazia deste hash code
		// abrir o cadastro de produtos em modo leitura, gravação e binário - precisa existir
		if(fopen_s(&fdProduto, CAMINHO_CADASTRO, "r+b") != 0)			// arquivo não existe?
		{	// arquivo não existe - primeira vez em que o programa é executado
			if(fopen_s(&fdProduto, CAMINHO_CADASTRO, "w+b") != 0)	// erro irrecuperável?
			{
				cout << "Erro irrecuperável na abertura do arquivo: " << CAMINHO_CADASTRO << endl;
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
				if(fwrite(&stProduto, sizeof(PRODUTO), 1, fdProduto) == 0) // erro de gravação?
				{
					fclose(fdProduto);
					*ptrStatus = false;					// avisa que houve problema
					cout << "Erro de gravação!" << endl;
					PAUSA;
					return;								// cai fora do construtor
				}
			} // for
#ifdef TESTE
			// gerar produtos para melhor testar o programa
			srand(500);									// semente random
			for(i = 0; i < QTDE_MAX_PRODUTOS * PERCENTUAL_DE_TESTE / 100; i++)
			{	// loop de criação de produtos
				_itoa_s(rand(), stProduto.cEAN, 14, 10);	// string que contém o código EAN
				if(VerificaSeExiste(stProduto.cEAN, &stProduto))	// produto já existe?
				{	// produto já existe
					i--;									// desconsidera esse código
					continue;								// vai tentar o próximo
				}
				// produto não existe vai ser incluido
				sprintf_s(stProduto.cDescricao, 40, "Produto de codigo %s",
					stProduto.cEAN);						// descrição do produto
				stProduto.dPrecoUnit = rand() * 0.937;		// preço unitário
				stProduto.dTotalVendido = 0.0;				// total vendido
				if(!IncluirNovoProduto(&stProduto))			// erro na inclusão?
				{	
					fclose(fdProduto);						// fechar o arquivo
					*ptrStatus = false;						// avisa o instanciador da classe
					cout << "Erro na inclusão de produtos no teste" << endl;
					PAUSA;
					return;									// cai fora do construtor
				}
			} // for
#endif
		} // arquivo não existe
		else
		{	// o arquivo de produtos já existe
			// leitura sequencial e criar o hash table na memória
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
					continue;							// continua no while e lê o próximo
				}
				// inserir a chave de busca deste produto ativo
				// calcular o Hash e inserir na lista deste hash
				if(!InsereNoHashTable(CalcularHashCode(stProduto.cEAN),
					stProduto.cEAN, nProxProduto))		// erro de inserção?
				{
					fclose(fdProduto);					// fecha o arquivo
					*ptrStatus = false;					// avisa o erro
					cout << "Não tem memória para a chave de busca!" << endl;
					PAUSA;
					return;								// cai fora do construtor
				}
				nProxProduto++;							// incrementa para o proximo produto
			} // while
			*ptrStatus = true;							// foi tudo OK
		} // arquivo existe
		*ptrStatus = true;
	} // construtor 
	// Método público que verifica se o produto já está cadastrado
	//	Parâmetros:
	//		Entrada: char *ptrEAN - ponteiro do string que tem o EAN do produto
	//				 PRODUTO *ptrStProduto - ponteiro de uma struct que irá
	//										receber os dados do produto se ele existir
	//		Retorno: bool - true - o produto existe e seus dados foram copiados
	//								para o invocador do método
	//						false - o produto não existe
	bool VerificaSeExiste(char *ptrEAN, PRODUTO *ptrStProduto)
	{
		CHAVE_BUSCA *ptrCorrente;						// aponta para chave corrente
		int nHash = CalcularHashCode(ptrEAN);			// calcular o hash code
		for(ptrCorrente = vetHashTable[nHash].ptrPrimeira;
			ptrCorrente;								// se NULL fim da lista
			ptrCorrente = ptrCorrente->ptrProxima)		// aponta para a próxima chave
		{	// tenho uma chave de busca
			if(ptrCorrente->cAtivo != 'A')				// produto inativo?
				continue;								// vai buscar a próxima chave
			if(strcmp(ptrCorrente->cEAN, ptrEAN) == 0)	// mesmo código?
			{	// vai buscar os dados deste produto no cadastro - leitura posicional
				if(!LerPosicional(ptrCorrente->nPosicional, ptrStProduto)) // erro
					return false;
				return true;							// indica que tem o produto
			}
		} // for
		return false;									// não encontrou o produto
	}
	// Método público para inserção de um novo produto no cadastro
	//	Parâmetros:
	//		Entrada: PRODUTO *ptrStProduto - ponteiro para uma struct que
	//										contém todos os dados do produto
	//										Essa struct está no invocador deste método
	//		Retorno: bool - true - a inclusão foi OK
	//						false - houve problema na inclusão 
	bool IncluirNovoProduto(PRODUTO *ptrStProduto)
	{
		int nHash = CalcularHashCode(ptrStProduto->cEAN);	// calcular o Hash Code desse produto
		ptrStProduto->cAtivo = 'A';							// produto ativo
		if(!GravaPosicional(nProxProduto, ptrStProduto))	// erro de gravação?
			return false;									// avisa que tem erro
		if(!InsereNoHashTable(nHash, ptrStProduto->cEAN, nProxProduto)) // erro na inserção?
			return false;
		nProxProduto++;										// posiciona para proximo produto
		return true;										// avisa que tudo OK
	}
	// Método público que fecha o cadastro
	void FecharCadastro(void)
	{
		fclose(fdProduto);									// fechar o cadastro
	}
	// Método público que lista todos os códigos EAN do mesmo Hash Code
	//	Parâmetros:
	//		Entrada: int nHash - valor do hash code a ser listado
	//		Retorno: bool - true - tem chaves de busca neste hash code e foram listados
	//						false - não tem chave de busca porque o hash code está vazio
	bool ListarCodigosDeHashCode(int nHash)
	{
		int nQtde = 0,								// qtde de chaves encontradas
			nLinha = 0;								// contador por linha
		CHAVE_BUSCA *ptrCorrente;					// chave de busca corrente
		if(vetHashTable[nHash].ptrPrimeira == NULL) // lista vazia?
			return false;							// retorna indicando vazia
		for(ptrCorrente = vetHashTable[nHash].ptrPrimeira; 
			ptrCorrente;							// nulo é fim da lista
			ptrCorrente = ptrCorrente->ptrProxima)	// indexa para próxima chave
		{	// no ptrCorrente - tem uma chave de busca
			if(ptrCorrente->cAtivo != 'A')			// inativa?
				continue;							// vai para a próxima
			if(nLinha >= 8)							// já listou 8 na linha
			{
				nLinha = 0;							// inicializa
				cout << endl;						// pula de linha
			}
			// listar um código
			cout << ptrCorrente->cEAN << "\t";
			nLinha++;								// um a mais na linha
			nQtde++;								// mais uma chave de busca no Hash
		} // for
		cout << endl << "\tHash " << nHash << " Qtde: " << nQtde << endl;
	}
};










