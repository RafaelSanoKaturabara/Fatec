// Defini��es do Sistema de Restaurante - Prova B1 - 12/04/2012
// Turma da Noite
#include <iostream>
#include <windows.h>
using namespace std;
// defini��es do restaurante
#define QTDE_MESAS								100
#define QTDE_PRODUTOS							10
#define PAUSA									system("pause")
#define LIMPAR_TELA								system("cls")
#define VERSAO									"Vers�o 0.0"
#define TURMA									"Noite"

// op��es do menu do operador
#define OCUPAR_MESA								'O'
#define FECHAR_MESA								'F'
#define SERVIR_PRODUTO_MESA						'P'
#define CONSULTAR_MESA							'C'
#define LIBERAR_MESA							'L'
#define SAIR_DO_PROGRAMA						'S'

// layout da struct de hora
typedef struct tagHORA
{
	unsigned short int nHora, nMinuto;				// hora e minuto
} HORA;												// struct da hora
// layout de cada produto do restaurante
typedef struct tagPRODUTO
{
	int nCodigo;									// c�digo do produto
	double dPrecoUnitario;							// pre�o unit�rio do produto
	char cDescricao[26];							// descri��o do produto
} PRODUTO;
// layout de cada produto fornecido na mesa do restaurante
typedef struct tagPROD_SERVIDO						// layout de cada produto servido na mesa
{
	int		nCodigoProduto,							// c�digo do produto
		nQuantidade;								// quantidade do produto
	double dValorProduto;							// valor do produto servido, isto �,
													// nQuantidade * dPre�oUnitario
	tagPROD_SERVIDO *ptrProximo;					// endere�o para o proximo produto
} PROD_SERVIDO;										// produto servido � mesa

// layout de cada mesa do restaurante
typedef struct tagMESA
{
	bool flgMesaLivreOuOcupada;						// true - indica ocupada
	int nQtdePessoas;								// quantidade de pessoas � mesa
	double dValorTotal;								// valor total de todos os produtos servidos
	HORA stHoraOcupacao;							// hora de ocupa��o da mesa
	PROD_SERVIDO *ptrPrimeiro,						// endere�o do primeiro produto servido
		*ptrUltimo;									// endere�o do �ltimo produto servido
} MESA;

// classe restaurante
class clRestaurante
{
private:
	MESA tabMesas[QTDE_MESAS];						// tabela de mesas do restaurante
	PRODUTO tabProdutos[QTDE_PRODUTOS],				// tabela de produtos
		stProduto;									// para buscar os dados de um produto

public:
	// constructor do restaurante
	clRestaurante()
	{
		int i;										// �ndice gen�rico
		char cNomes[QTDE_PRODUTOS][26] = {
		   //12345678901234567890
			"Por��o de Arroz     ",
			"Cumbuca de Feij�o   ",
			"Salada Completa     ",
			"Feijoada            ",
			"Salada de frutas    ",
			"Bife a milaneza     ",
			"Arroz troupeiro     ",
			"Salada de batatas   ",
			"Omelete completo    ",
			"Cafe expresso       "};
		// vai inicializar a tabela de produtos
		// ----<< Observa��o >>-----------------------------------------
		// Vamos ser criados automaticamente QTDE_PRODUTOS (10) produtos e 
		// somente esses produtos poder�o ser servidos � mesa
		//
		for (i = 0; i < QTDE_PRODUTOS; i++)
		{
			tabProdutos[i].nCodigo = i + 1;			// c�digo vai de 1 a QTDE_PRODUTOS
			// vai copiar o nome do produto na tabela de nomes
			strcpy_s(tabProdutos[i].cDescricao, &cNomes[i][0]);
			tabProdutos[i].dPrecoUnitario = 8.80 + (i * 1.50);
		} // for - inicializa��o de produtos
		// @@@@<01>@@@@
		// 1. Inicializar a tabela de mesas indicando que todas est�o livres
		//		No in�cio do programa todas as mesas estar�o livres e o programa
		//		recome�a a cada inicio.....
		//		Indicar tamb�m que a lista ligada de produtos da mesa est� vazia
		for(i = 0; i < QTDE_MESAS; i++)
		{
			tabMesas[i].flgMesaLivreOuOcupada = false;	// mesa livre
			tabMesas[i].ptrPrimeiro = NULL;				// n�o tem lista de produtos
		}
	} // construtor

	// M�todo que informa os dados do produto
	//	Par�metros:
	//		Entrada: int nCodigo - c�digo do produto desejado
	//				 PRODUTO *ptrProduto - endere�o da struct a receber os dados do produto
	//		Retorno: bool - false = produto n�o existe e true - produto existe e seus
	//						dados est�o na struct cujo endere�o foi fornecido pelo
	//						invocador do m�todo
	bool InformaDadosProduto(int nCodigo, PRODUTO *ptrProduto)
	{
		// @@@@<02>@@@@
		// 1. Verificar se o c�digo do produto � v�lido
		//	1.1 - Se n�o for v�lido retornar false
		// 2. Copiar os dados do produto no endere�o da struct informado pelo chamador
		if(nCodigo < 1 || nCodigo > QTDE_PRODUTOS)		// c�digo inv�lido?
			return false;								// avisa que c�digo inv�lido
		memcpy(ptrProduto, &tabProdutos[nCodigo - 1], sizeof(PRODUTO));
		return true;									// indica que foi tudo OK
	}

	// M�todo que insere um novo produto servido � mesa
	// Esse produto vai ser inserido na lista ligada de produtos da mesa
	//	Par�metros:
	//		Entrada: int nMesa - n�mero da mesa cujo produto est� sendo servido
	//							 A validade deste n�mero tem que ser testada no
	//							 invocador do m�todo
	//				 int nCodProduto - c�digo do produto que est� sendo servido na 
	//							 mesa. A validade deste c�digo deve ser testada no
	//							 invocador do m�todo
	//				 int nQtdeProd - qtde do produto que est� sendo inserido
	//		Retorno: bool - true - se inser��o de novo produto na lista ligada
	//							da mesa foi OK.
	//						false - se n�o havia mem�ria suficiente para a inser��o
	//							do novo produto que foi servido na mesa
	bool InsereNovoProdutoNaMesa(int nMesa, int nCodProduto, int nQtdeProd)
	{
		if(tabMesas[nMesa - 1].ptrPrimeiro == NULL)			// primeiro produto servido na mesa?
			tabMesas[nMesa - 1].ptrUltimo = 
			tabMesas[nMesa - 1].ptrPrimeiro = new PROD_SERVIDO; // aloca��o de mem�ria para um produto
		else												// n�o � o primeiro produto
			tabMesas[nMesa - 1].ptrUltimo =
			tabMesas[nMesa - 1].ptrUltimo->ptrProximo = new PROD_SERVIDO; // aloca mem�ria para produto
		if(tabMesas[nMesa - 1].ptrUltimo == NULL)			// sem mem�ria dispon�vel?
			return false;									// indica que n�o tem mem�ria dispon�vel
		// vamos completar o produto servido com o pre�o total e este produto � o �ltimo da lista da mesa
		tabMesas[nMesa - 1].ptrUltimo->nCodigoProduto = nCodProduto; // copiar o c�digo do produto
		tabMesas[nMesa - 1].ptrUltimo->nQuantidade = nQtdeProd;      // copiar a quantidade
		tabMesas[nMesa - 1].ptrUltimo->dValorProduto =
			tabProdutos[nCodProduto - 1].dPrecoUnitario * nQtdeProd; // calcular o valor total do produto
		tabMesas[nMesa - 1].dValorTotal += 
			tabMesas[nMesa - 1].ptrUltimo->dValorProduto;			 // somar no total da mesa
		tabMesas[nMesa - 1].ptrUltimo->ptrProximo = NULL;		     // produto �ltimo da lista
		return true;										// indica que foi tudo OK
	}

	// M�todo que verifica se a mesa est� ocupada
	// Se ela estiver ocupada ser� retornado true e no ptrMesa ser�o copiados os
	//	dados da mesa ocupada
	// Se a mesa estiver desocupada retornar false
	//	Par�metros:
	//		Entrada: int nMesa - mesa a ser testada
	//				 MESA *ptrMesa - ponteiro da struct que ir� receber os dados da mesa
	//		Retorno: bool - true - mesa ocupada e os dados dela est�o em ptrMesa
	//						false - mesa n�o ocupada
	bool VerificaSeMesaOcupada(int nMesa, MESA *ptrMesa)
	{
		if(tabMesas[nMesa - 1].flgMesaLivreOuOcupada == false)	// mesa desocupada?
			return false;										// indica mesa desocupada
		// copiar os dados da mesa que est� ocupada na struct apontada pelo chamador
		memcpy(ptrMesa, &tabMesas[nMesa - 1], sizeof(MESA));	
		return true;											// avisa tudo OK
	}


	// M�todo que ocupa uma mesa que deve estar desocupada
	// Este m�todo ir� verificar se a mesa est� ocupada e se
	//	estiver vai devolver um false
	// Vai ocupar a mesa e quardar quantas pessoas est�o na
	// mesa e indicar a hora e minuto da ocupa��o.
	// N�o esquecer de zerar o total da mesa e esvaziar a lista ligada de produtos servidos
	//	Par�metros:
	//		Entrada: int nMesa - n�mero da mesa a ser ocupada
	//				 int nQtdePessoas - quantidade de pessoas que ir�o ocupar a mesa
	//		Retorno: bool - true - mesa foi ocupada OK
	//						false - mesa j� ocupada
	bool OcuparMesa(int nMesa, int nQtdePessoas)
	{
		SYSTEMTIME stTime;
		GetLocalTime(&stTime);									// busca a hora local
		if(tabMesas[nMesa - 1].flgMesaLivreOuOcupada)			// mesa j� ocupada?
			return false;
		tabMesas[nMesa - 1].flgMesaLivreOuOcupada = true;		// ocupa a mesa
		tabMesas[nMesa - 1].stHoraOcupacao.nHora = stTime.wHour; // hora da ocupa��o
		tabMesas[nMesa - 1].stHoraOcupacao.nMinuto = stTime.wMinute; // minuto da ocupa��o
		tabMesas[nMesa - 1].nQtdePessoas = nQtdePessoas;			// qtde de pessoas ocupando a mesa
		tabMesas[nMesa - 1].dValorTotal = 0.0;				    // zerar o total da mesa que est� sendo ocupada
		tabMesas[nMesa - 1].ptrPrimeiro = NULL;					// lista vazia de produtos servidos
		return true;											// avisa tudo OK
	}

	// M�todo que lista os produtos da mesa (est�o na lista ligada)
	// 
	//  Cada linha conter� os dados abaixo (o que est� entre par�ntesis � apenas informativo e n�o vai ser mostrado)
	//	xxx(c�digo produto) xxxx(descri�ao)  xxx(qtde) xxxxx(valor total)
	void ListaProdutosMesaOcupada(int nMesa)
	{
		PROD_SERVIDO *ptrWork;					// ponteiro do produto corrente
		char cWork[200];							// para formatar a listagem
		for(ptrWork = tabMesas[nMesa - 1].ptrPrimeiro; // primeiro produto da mesa
			ptrWork;							// true se ptrWork != 0
			ptrWork = ptrWork->ptrProximo)		// o proximo da lista ser� o corrente
		{
			InformaDadosProduto(ptrWork->nCodigoProduto, &stProduto);
			sprintf_s(cWork, sizeof(cWork), "%03d %s % 3d %6.2f %8.2f",
				ptrWork->nCodigoProduto,
				stProduto.cDescricao,
				ptrWork->nQuantidade,
				stProduto.dPrecoUnitario,
				ptrWork->dValorProduto);
			cout << cWork << endl;
		} // for
	}

	// M�todo que fecha a mesa, isto �,
	//	exibe quantas pessoas ocupam a mesa e a partir de que hora
	//	Depois chama o m�todo que ListaProdutosMesaOcupada que
	//		ir� listar os produtos que foram servidos na mesa
	//	Depois ir� mostrar o total, calcular 10% de servi�o e 
	//  exibir mais o servi�o e o novo total e depois mostrar o valor
	//  total dividido pelo n�mero de pessoas � mesa
	//		Layout de impress�o:
	//	Mesa: xxx	Qtde Pessoas: xx	Hora Ocupa��o: hh:mm
	//	xxx xxxx(descri�ao)  xxx(qtde) xxxxx(valor total) (esta parte � de outro m�todo)
	//						...... repetir para n produtos
	//											----------------
	//											xxxxxxx(total)
	//								10% servi�o:    xxxxx
	//											----------------
	//  Valor por xx pessoas: xxxxxx			xxxxxxxx(Total com servi�o)
	//	Par�metros:
	//		Entrada: int nMesa - mesa que vai ser fechada
	//		Retorno: bool - true - mesa foi fechada OK
	bool FecharMesa(int nMesa)
	{
		char cWork[50];						// para formatar cada linha
		double dServico,					// para valor do servi�o
			dWork;							// para trabalho
		sprintf(cWork, " Hora da Ocupa��o: %02d:%02d",
			tabMesas[nMesa - 1].stHoraOcupacao.nHora,
			tabMesas[nMesa - 1].stHoraOcupacao.nMinuto);
		cout << "Mesa: " << nMesa << " Qtde Pessoas: " << 
			tabMesas[nMesa - 1].nQtdePessoas << cWork << endl << endl;
		ListaProdutosMesaOcupada(nMesa);
		cout << "                            ----------" << endl;
		sprintf_s(cWork, sizeof(cWork), "Sub-total: %8.2f",
			tabMesas[nMesa - 1].dValorTotal);
		cout << "                               " << cWork << endl;
		// vai calcular o servi�o
		dServico = tabMesas[nMesa - 1].dValorTotal * 10 / 100;
		sprintf(cWork, "Servi�o: %8.2f", dServico);
		cout << "                           " << cWork << endl;
		// calcular o valor total com servi�o
		dWork = tabMesas[nMesa - 1].dValorTotal + dServico;
		sprintf(cWork, "Total: %8.2f", dWork);	
		cout << "                             " << cWork << endl;
		cout << "Por pessoa: " << dWork / tabMesas[nMesa - 1].nQtdePessoas << endl;
		return true;
	}

	// M�todo que libera uma mesa que deve estar ocupada
	// Se a mesa n�o estiver ocupada retornar false
	//	Par�metros:
	//		Entrada: int nMesa - n�mero da mesa que vai ser liberada
	//		Retorno: bool - true - mesa foi liberada OK. false - mesa n�o ocupada
	bool LiberarMesa(int nMesa)
	{
		if(tabMesas[nMesa - 1].flgMesaLivreOuOcupada == false)	// mesa desocupada?
			return false;										// avisa mesa desocupada
		// a mesa est� ocupada portanto vamos desocup�-la
		tabMesas[nMesa - 1].flgMesaLivreOuOcupada = false;		// desocupa a mesa
		return true;
	}
};