// Defini��es do programa de controle de estoque
#include <iostream>
#include <windows.h>
using namespace std;
// Dimensionamento do programa
//
// defini��o dos grupos de produtos
//
#define PESADOS						1			// produtos que s�o vendidos por peso
#define CEREAIS						2			// cereais 
#define ENLATADOS					3			// produtos enlatados
#define EMBUTIDOS					4			// produtos embutidos
#define BEBIDAS						5			// bebidas
#define LIMPEZA						6			// produtos de limpeza
#define HIGIENE						7			// produtos de higiene

// quantidade de itens nos Hash Tables
#define QUANTIDADE_HASH_GRUPOS		7			
#define QUANTIDADE_HASH_PRODUTOS	200

// O arquivo: Produtos.arq est� no sub-diret�rio anterior onde
//	estiver o execut�vel do programa
//	portanto est� dentro do seu projeto
#define CAMINHO_DO_ARQUIVO		".\\..\\Produtos.arq"
#define PAUSA						system("pause")
#define LIMPAR_TELA					system("cls")
// Defini��es do menu do programa
#define CADASTRAR_PRODUTO			'C'	// cadastrar um novo produto
#define EXIBIR_DADOS_PRODUTO		'M'	// exibir dados do produto
#define DAR_ENTRADA_ESTOQUE			'E'	// dar entrada no estoque de uma compra
#define DAR_BAIXA_ESTOQUE			'B'	// baixa no estoque (saida de produto)
#define LISTAGEM_GERAL_PRODUTOS		'L'	// listagem geral de produtos
#define LISTAGEM_GERAL_GRUPO		'G' // listagem geral do grupo
#define EXCLUIR_PRODUTO				'X'	// excluir um dado produto
#define SAIR_DO_PROGRAMA			'S'	// sair do programa

// struct de cada produto
typedef struct tagPRODUTO
{
	int nCodigoGrupo,					// codigo do Grupo de PESADOS a HIGIENE
		nCodProdGrupo;					// c�digo do produto dentro do grupo de 1 a qtde de produtos do grupo
	char cDescricaoProd[51],			// descri��o do produto
		cDataUltimaCompra[17],			// dd/mm/aaaa hh:mm
		cProdutoAtivo;					// 'A' - produto ativo, 'N' - n�o est� ativo
	double dEstoque,					// quantidade em estoque do produto (QE)
		dPrecoUnitMedio,				// pre�o unit�rio m�dio (PUM)
		dValorTotalEstoque;				// valor total do estoque (VTE)
	// C�lculo do Pre�o Unit�rio Medio (PUM) em nova compra
	// Valor total nova compra (NVTC)
	// Qtde nova compra	(NQC)
	// PUM = (NVTC + VTE) / (NQC + QE)
} PRODUTO;								// struct de produto

typedef struct tagLISTA_GRUPO
{
	int nGrupo,							// codigo do grupo
		nCodigo,						// c�digo do produto
		nPosicional;					// c�digo posicional dentro do arquivo de produtos
	char cAtivo;						// 'A' - ativo e 'N' - inativo ou excluido
	tagLISTA_GRUPO *ptrProximo;			// ponteiro para o pr�ximo da lista
} LISTA_GRUPO;							// lista ligada dos produtos de cada grupo

typedef struct tagHASH_TABLE_GRUPO
{
	LISTA_GRUPO *ptrPrimeiro,			// ponteiro para o primeiro da lista ligada de cada grupo
		*ptrUltimo;						// ponteiro para o �ltimo da lista ligada de cada grupo
}HASH_TABLE_GRUPO;

typedef struct tagHASH_TABLE_PRODUTO
{
	LISTA_GRUPO *ptrPrimeiro,			// primeiro da lista ligada de produto
		*ptrUltimo;						// ponteiro do �ltimo da lista ligada de produto
} HASH_TABLE_PRODUTO;

//
// Classe para o controle de estoque
//
class clEstoque
{
	// atributos private da classe estoque
private:
	HASH_TABLE_GRUPO vetHashGrupo[QUANTIDADE_HASH_GRUPOS];		// hash table dos grupos
	HASH_TABLE_PRODUTO vetHashProduto[QUANTIDADE_HASH_PRODUTOS]; // hash table dos produtos
	PRODUTO stProduto;											// para conter os dados de um produto
	LISTA_GRUPO stListaGrupoProduto;							// struct para conter um elemento da lista
																// ligada de grupo ou de produto
	FILE *fdProduto;											// file description do arquivo de produtos
	int nPosicProximo;											// posicional para o pr�ximo produto no arquivo
	//
	// M�todo private que calcula o Hash do produto
	//	Entrada: int nGrupo - c�digo do grupo do produto
	//			 int nCodProduto - c�digo do produto
	//	Retorno: int - valor do hash do produto
	int CalcularHashProduto(int nGrupo, int nCodProduto)
	{
		return (nGrupo * nCodProduto) % QUANTIDADE_HASH_PRODUTOS;	// devolve o HashCalculado
	}
	//
	// M�todo private que calcula o Hash do grupo do produto
	//
	//	Entrada: int nGrupo - grupo do produto
	int CalcularHashGrupo(int nGrupo)
	{
		return nGrupo - 1;											// hash � o grupo - 1 (o grupo 1 � indice zero)
	}
	//
	// M�todo que insere no hash table de grupos
	//	Entrada: int nGrupo - grupo do produto
	//			 int nCodProduto - codigo do produto
	//			 int nHash - hash do grupo
	//	Retorno: bool - true - a inser��o foi OK
	//					false - n�o tem mem�ria para inser��o
	bool InsereHashTableGrupo(int nGrupo, int nCodProduto, int nHash)
	{
		// <<<<< >>>>> - codificar este m�todo
		LISTA_GRUPO *ptrSalvaUltimo = 
			vetHashGrupo[nHash].ptrUltimo;		// salva o �ltimo caso n�o tenha mem�ria
		if (vetHashGrupo[nHash].ptrPrimeiro == NULL)	// primeiro da lista ligada?
			vetHashGrupo[nHash].ptrUltimo = 
			vetHashGrupo[nHash].ptrPrimeiro = new LISTA_GRUPO();	// insere no primeiro e no �ltimo
		else 
			vetHashGrupo[nHash].ptrUltimo = 
			vetHashGrupo[nHash].ptrUltimo->ptrProximo = new LISTA_GRUPO(); // insere no pr�ximo do �ltimo
		if (vetHashGrupo[nHash].ptrUltimo == NULL)	// n�o teve mem�ria?
		{
			vetHashGrupo[nHash].ptrUltimo = ptrSalvaUltimo;
			return false;
		}
		vetHashGrupo[nHash].ptrUltimo->cAtivo = 'A';
		vetHashGrupo[nHash].ptrUltimo->nCodigo = nCodProduto;
		vetHashGrupo[nHash].ptrUltimo->nGrupo = nGrupo;
		vetHashGrupo[nHash].ptrUltimo->nPosicional = nPosicProximo;
		vetHashGrupo[nHash].ptrUltimo->ptrProximo = NULL;
		return true;							// para n�o dar erro
	}
	//
	// M�todo que insere no hash table de produtos
	//	Entrada: int nGrupo - grupo do produto
	//			 int nCodProduto - codigo do produto
	//			 int nHash - hash do grupo
	//	Retorno: bool - true - a inser��o foi OK
	//					false - n�o tem mem�ria para inser��o
	bool InsereHashTableProduto(int nGrupo, int nCodProduto, int nHash)
	{
		LISTA_GRUPO *ptrSalvaUltimo =									// para salvar o ponteiro do �ltimo caso n�o
			vetHashProduto[nHash].ptrUltimo;							// tenha mais mem�ria
		if(vetHashProduto[nHash].ptrPrimeiro == NULL)					// primeiro da lista ligada?
			vetHashProduto[nHash].ptrUltimo =
			vetHashProduto[nHash].ptrPrimeiro = new LISTA_GRUPO;		// vale para grupo ou produto
		else
			vetHashProduto[nHash].ptrUltimo = 
			vetHashProduto[nHash].ptrUltimo->ptrProximo =  new LISTA_GRUPO; // insere no proximo do �ltimo
		if(vetHashProduto[nHash].ptrUltimo == NULL)						// sem mem�ria?
		{	// n�o tem mais mem�ria
			vetHashProduto[nHash].ptrUltimo = ptrSalvaUltimo;			// restaura o que foi perdido
			return false;
		}
		// vai mover os dados para o novo elemento da lista
		vetHashProduto[nHash].ptrUltimo->cAtivo = 'A';
		vetHashProduto[nHash].ptrUltimo->nCodigo = nCodProduto;
		vetHashProduto[nHash].ptrUltimo->nGrupo = nGrupo;
		vetHashProduto[nHash].ptrUltimo->nPosicional = nPosicProximo;
		vetHashProduto[nHash].ptrUltimo->ptrProximo = NULL;				// �ltimo da lista
		return true;													// indica tudo bem
	}
	//
	//	M�todo private que grava um produto no arquivo de produtos
	//
	//	Entrada: PRODUTO *ptrStProduto - ponteiro para uma struct que contem os dados do produto
	//	Retorno: bool - true - indica que foi tudo bem
	//					false - indica que houve erro de fseek ou fwrite
	bool GravaProduto(PRODUTO *ptrStProduto)
	{
		if(fseek(fdProduto, nPosicProximo * sizeof(PRODUTO), SEEK_SET) != 0)	
		{	// erro de fseek
			return false;
		}
		if(fwrite(ptrStProduto, sizeof(PRODUTO), 1, fdProduto) == 0)
		{	// erro de grava��o
			return false;
		}
		return true;
	}

	// M�todo que grava um produto posicional
	bool GravaProdutoPosicional(int nPosicional, PRODUTO *ptrStProduto)
	{
		if(fseek(fdProduto, nPosicional * sizeof(PRODUTO), SEEK_SET) != 0)	
		{	// erro de fseek
			return false;
		}
		if(fwrite(ptrStProduto, sizeof(PRODUTO), 1, fdProduto) == 0)
		{	// erro de grava��o
			return false;
		}
		return true;
	}
	// M�todos p�blicos
public:
	//
	//	M�todo que l� um produto sendo dado o seu posicional
	//
	//	Entrada: int nPosicional - posicional do registro do produto dentro do arquivo
	//			 PRODUTO *ptrStProduto - ponteiro da struct que ir� receber os dados
	//							 produto
	//	Retorno: bool - indica que o produto foi lido ok e seus dados est�o na
	//					struct indicada pelo chamador
	//			 false - erro de fseek ou de fread
	bool LerUmProduto(int nPosicional, PRODUTO *ptrStProduto)
	{	
		if(fseek(fdProduto, nPosicional * sizeof(PRODUTO), SEEK_SET) != 0)	
		{	// erro de fseek
			return false;
		}
		if(fread(ptrStProduto, sizeof(PRODUTO), 1, fdProduto) == 0)
		{	// erro de leitura
			return false;
		}
		return true;							// indica tudo bem
	}
	//
	// Construtor da classe
	//
	//	Entrada: bool *ptrStatus - ponteiro de uma bool do chamador que ir� receber os status da constru��o:
	//									  true - indica que foi tudo bem e 
	//									  false - falta de mem�ria ou erro de abertura
	//											  ou grava��o
	clEstoque(bool *ptrStatus)
	{
		int i;													// �ndice gen�rico
		nPosicProximo = 0;										// indica a posi��o de pr�ximo produto a ser gravado
		// vai inicializar os vetores de Hash Table
		for(i = 0; i < QUANTIDADE_HASH_GRUPOS; i++)
			vetHashGrupo[i].ptrPrimeiro = NULL;					// inicializa as listas de grupos
		for(i = 0; i < QUANTIDADE_HASH_PRODUTOS; i++)
			vetHashProduto[i].ptrPrimeiro = NULL;				// inicializa as listas ligadas de cada hash
		// vai abrir o arquivo em modo leitura/grava��o (r+b)
		fdProduto = fopen(CAMINHO_DO_ARQUIVO, "r+b");			// abrir em modo leitura/grava��o
		if(fdProduto == NULL)									// arquivo n�o existe?
		{	// arquivo n�o existe - vai abrir o arquivo em modo grava�ao/leitura - (w+b)
			fdProduto = fopen(CAMINHO_DO_ARQUIVO, "w+b");		// abrir em modo grava��o/leitura
			if(fdProduto == NULL)								// erro de abertura?
			{	// erro de abertura - vai avisar ao instanciador da classe
				*ptrStatus = false;								// indica que houve erro
				return;											// cai fora do construtor
			}
			// abertura de um novo arquivo vazio pela primeira vez que o programa � executado
			*ptrStatus = true;									// indica que foi tudo bem
			return;												// cai fora do construtor
		} // arquivo n�o existe
		else													// o arquivo j� existe
		{	// arquivo j� existe
			// loop infinito para leitura do arquivo de produtos inserindo os produtos e os produtos
			// dos grupos em suas respectivas listas ligadas
			while(true)
			{
				if(fread(&stProduto, sizeof(PRODUTO), 1, fdProduto) == 0)	// fim de arquivo?
				{	// foi fim de arquivo
					*ptrStatus = true;							// indica que foi tudo bem
					return;										// cai fora do construtor
				}
				if(stProduto.cProdutoAtivo != 'A')				// produto n�o ativo
				{	// produto inativo ou excluido
					nPosicProximo++;							// posicional do pr�ximo
					continue;									// continua no loop infinito
				}
				// produto est� ativo
				// vai inserir na lista ligada dos Hash Tables correspondentes
				if(!InsereHashTableGrupo(stProduto.nCodigoGrupo, stProduto.nCodProdGrupo, 
					CalcularHashGrupo(stProduto.nCodigoGrupo)))
				{	// n�o tem mais mem�ria
					*ptrStatus = false;
					return;										// sai fora do construtor
				}
				if(!InsereHashTableProduto(stProduto.nCodigoGrupo, stProduto.nCodProdGrupo,
					CalcularHashProduto(stProduto.nCodigoGrupo, stProduto.nCodProdGrupo)))
				{	// n�o tem mais mem�ria
					*ptrStatus = false;
					return;										// cai fora do construtor
				}
				// o produto foi inserido nas listas ligadas de cada Hash Table
				nPosicProximo++;								// incrementa para o pr�ximo
			} // while
		} // arquivo j� existe
	} // construtor
	//
	// M�todo que verifica se o produto j� existe ou j� foi cadastrado
	//	Entrada: int nGrupo - codigo do grupo do produto
	//			 int nCodigo - codigo do produto
	//			 int *ptrPosicional - ponteiro para receber o posicional deste produto
	//			 PRODUTO *ptrStProduto - ponteiro de uma struct para receber os dados do produto se ele j� existe
	//									 isto �, est� cadastrado.
	//	Retorno: bool - true - produto existe e foi lido para a struct do invocador deste m�todo
	//							e o posicional foi passado para o invocador do m�todo
	//					false - produto n�o existe, isto �, n�o foi cadastrado ou foi excluido
	bool VerificaSeExiste(int nGrupo, int nCodigo, int *ptrPosicional, PRODUTO *ptrStProduto)
	{
		LISTA_GRUPO *ptrWork;
		int nHash = CalcularHashGrupo(nGrupo);					// calcula o hash do grupo
		for(ptrWork = vetHashGrupo[nHash].ptrPrimeiro;			// inicializa��o do for
			ptrWork;											// enquanto o ptrWork n�o for null
			ptrWork = ptrWork->ptrProximo)						// next step do for
		{	// em ptrWork tem um elemento da lista ligada do Hash Table de grupos
			if(ptrWork->nCodigo == nCodigo &&					// se mesmo c�digo de produto e
				ptrWork->cAtivo == 'A')							// produto ativo
			{	// produto existe e est� ativo
				if(!LerUmProduto(ptrWork->nPosicional, ptrStProduto)) // n�o leu o produto no arquivo?
				{	// n�o leu o produto
					return false;
				}
				*ptrPosicional = ptrWork->nPosicional;			// devolve o posicional deste registro
				return true;									// indica que foi lido o produto e existe
			}
		} // for
		// percorreu a lista e n�o encontrou o produto
		return false;											// indica que o produto n�o existe
	}
	//
	// M�todo para listar todos os produtos de um grupo
	//
	void ListarProdutosDoGrupo(int nGrupo)
	{
		// <<<< >>>> - codificar este m�todo
		// Fazer um cabe�alho com data e hora e nome do grupo
		SYSTEMTIME stTime;
		char cWork[200];
		PRODUTO stProduto;								// para conter os dados de um produto
		LISTA_GRUPO *ptrCorrente;
		int nHashGrupo = CalcularHashGrupo(nGrupo);
		char vetNomesGrupos[][10] = 
		{
			"Pesados",
			"Cereais",
			"Enlatados",
			"Embutidos",
			"Bebidas",
			"Limpeza",
			"Higiene"
		};
		GetLocalTime(&stTime);
		sprintf(cWork, "\tFATEC-MC - SisEstoque %02d/%02d/%04d �s %02d:%02d\n\tGrupo: %s",
			stTime.wDay, stTime.wMonth, stTime.wYear,
			stTime.wHour, stTime.wMinute,
			vetNomesGrupos[nHashGrupo]);
		cout << cWork << endl; // cabe�alho
		cout << "C�d       Descri��o                   Qtd.estoque  Prec.Unit.M�dio  Val.Tot.Estoque" << endl;
		for ( ptrCorrente = vetHashGrupo[nHashGrupo].ptrPrimeiro; 
			ptrCorrente; ptrCorrente = ptrCorrente->ptrProximo)
		{
			if (ptrCorrente->cAtivo == 'A')
			{
				if (!LerUmProduto(ptrCorrente->nPosicional, &stProduto))
				{
					cout << "Produto n�o encontrado!" << endl;
				}
				else
				{
					sprintf_s(cWork, "%09d %-27s %-12.0f R$%-14.2f R$%-15.2f", stProduto.nCodProdGrupo, stProduto.cDescricaoProd, 
						stProduto.dEstoque, stProduto.dPrecoUnitMedio, stProduto.dValorTotalEstoque);
					cout << cWork << endl;
				}
			}
		}
		PAUSA;
	}
	//
	// M�todo para cadastrar um produto
	//
	bool CadastrarProduto(PRODUTO *ptrStProduto)
	{
		// <<<< >>>> - codificar este m�todo7
		if(!GravaProduto(ptrStProduto))	// gravou ok?
		{	
			cout << "Erro so salvar no disco" << endl;
			PAUSA;
			return false;										// sai fora do construtor
		}
		// vai inserir na lista ligada dos Hash Tables correspondentes
		if(!InsereHashTableGrupo(ptrStProduto->nCodigoGrupo, ptrStProduto->nCodProdGrupo, 
			CalcularHashGrupo(ptrStProduto->nCodigoGrupo)))
		{	
			cout << "n�o teve mem�ria!" << endl;
			PAUSA;
			return false;										// sai fora do construtor
		}
		if(!InsereHashTableProduto(ptrStProduto->nCodigoGrupo, ptrStProduto->nCodProdGrupo,
			CalcularHashProduto(ptrStProduto->nCodigoGrupo, ptrStProduto->nCodProdGrupo)))
		{	
			cout << "n�o teve mem�ria!" << endl;
			PAUSA;
			return false;										// cai fora do construtor
		}
		nPosicProximo++;							// acrescenta o posicional
		return true;								// para n�o dar erro
	}
	//
	// M�todo para regravar o produto
	bool RegravaProduto(int nPosicional, PRODUTO *ptrStProduto)
	{
		// <<<< >>>> - codificar este m�todo
		if(!GravaProdutoPosicional(nPosicional, ptrStProduto))
		{
			cout << "Erro ao gravar o produto!" << endl;
			PAUSA;
			return false;
		}
		return true;
	}
	//
	// M�todo que inativa os produtos nos hashtables
	bool DesativaHashGrupoEProduto(PRODUTO *ptrStProduto)
	{
		bool flgExluiu;
		int nHashGrupo = CalcularHashGrupo(ptrStProduto->nCodigoGrupo),
		nHashProduto = CalcularHashProduto(ptrStProduto->nCodigoGrupo, ptrStProduto->nCodProdGrupo);
		LISTA_GRUPO *ptrCorrente;

		flgExluiu = false;
		for (ptrCorrente = vetHashGrupo[nHashGrupo].ptrPrimeiro;
			ptrCorrente; ptrCorrente = ptrCorrente->ptrProximo)
		{
			if( ptrCorrente->nCodigo == ptrStProduto->nCodProdGrupo 
				&& ptrCorrente->cAtivo == 'A'
				&& ptrCorrente->nGrupo == ptrStProduto->nCodigoGrupo) // encontrou o produto para inativar?
			{
				ptrCorrente->cAtivo = 'I';
				flgExluiu = true;
				break;										// cai fora do for
			}
		}
		if(!flgExluiu)										// n�o encontrou?
			return false;
		flgExluiu = false;
		for (ptrCorrente = vetHashProduto[nHashProduto].ptrPrimeiro;
			ptrCorrente; ptrCorrente = ptrCorrente->ptrProximo)
		{
			if( ptrCorrente->nCodigo == ptrStProduto->nCodProdGrupo 
				&& ptrCorrente->cAtivo == 'A'
				&& ptrCorrente->nGrupo == ptrStProduto->nCodigoGrupo) // encontrou o produto para excluir?
			{
				ptrCorrente->cAtivo = 'I';
				flgExluiu = true;
				break;										// cai fora do for
			}
		}
		if(!flgExluiu)										// n�o encontrou?
			return false;
		return true;
	}
	//
	// m�todo que fecha o arquivo de produtos
	//
	void FecharArquivo()
	{
		fclose(fdProduto);
	}
};