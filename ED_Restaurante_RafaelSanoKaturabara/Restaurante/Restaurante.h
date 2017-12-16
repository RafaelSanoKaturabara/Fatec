// Defini��es do Sistema de Restaurante - Prova N1 - 06/04/2017
// 
#include <iostream>
#include <windows.h>
using namespace std;

// defini��es do restaurante
#define QTDE_MESAS								100
#define QTDE_PRODUTOS							10
#define PAUSA									system("pause")
#define LIMPAR_TELA								system("cls")
#define VERSAO									"Vers�o 1.0"
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
	char cDescricao[25];							// descri��o do produto
} PRODUTO;

// layout de cada produto fornecido na mesa do restaurante
//	O produto servido estar� na lista ligada dos produtos servidos na mesa
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
	//
	// J� est� totalmente codificado
	//
	clRestaurante()
	{
		int i;										// �ndice gen�rico
		char cNomes[QTDE_PRODUTOS][23] = {
		   //12345678901234567890
			"Por��o de Arroz     ",					// c�digo 1
			"Cumbuca de Feij�o   ",
			"Salada Completa     ",
			"Feijoada            ",
			"Salada de frutas    ",
			"Bife a milaneza     ",					// ........
			"Arroz troupeiro     ",
			"Salada de batatas   ",
			"Omelete completo    ",
			"Cafe expresso       "};				// c�digo 10

		// vai inicializar a tabela de produtos
		// ----<< Observa��o >>-----------------------------------------
		// Vamos ser criados automaticamente QTDE_PRODUTOS (10) produtos e 
		// somente esses produtos poder�o ser servidos � mesa
		//
		for (i = 0; i < QTDE_PRODUTOS; i++)
		{
			tabProdutos[i].nCodigo = i + 1;			// c�digo vai de 1 a QTDE_PRODUTOS
			// vai copiar o nome do produto na tabela de nomes
			strcpy_s(tabProdutos[i].cDescricao, 25, &cNomes[i][0]);
			tabProdutos[i].dPrecoUnitario = 8.80 + (i * 1.50);

		} // for i

		// 1. Inicializar a tabela de mesas indicando que todas est�o livres
		//		No in�cio do programa todas as mesas estar�o livres e o programa
		//		recome�a a cada inicio.....
		//		Indicar tamb�m que a lista ligada de produtos da mesa est� vazia

		//  J� foi codificado
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
		if(nCodigo < 0 || nCodigo > QTDE_PRODUTOS)		// o c�digo est� entre 0 e QTDE_PRODUTOS?
			return false;								
		//	1.1 - Se n�o for v�lido retornar false
		// 2. Copiar os dados do produto no endere�o da struct informado pelo chamador
		memcpy_s(ptrProduto, sizeof(PRODUTO), &tabProdutos[nCodigo - 1], sizeof(PRODUTO));
		// 3. Retornar true
		// Codificar este m�todo
		return true;									// para n�o dar erro
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
	//						false - se n�o h� mem�ria suficiente para a inser��o
	//							do novo produto que foi servido na mesa
	bool InsereNovoProdutoNaMesa(int nMesa, int nCodProduto, int nQtdeProd)
	{
		// fazer o new do PROD_SERVIDO para o primeiro produto da mesa
		// ou para o �ltimo....
		if(tabMesas[nMesa - 1].ptrPrimeiro == NULL)
			tabMesas[nMesa - 1].ptrPrimeiro = 
			tabMesas[nMesa - 1].ptrUltimo = new PROD_SERVIDO;
		else 
			tabMesas[nMesa - 1].ptrUltimo = 
			tabMesas[nMesa - 1].ptrUltimo->ptrProximo = new PROD_SERVIDO;
		// verificar se havia mem�ria para esse produto e se n�o h�, retornar false.
		if(tabMesas[nMesa - 1].ptrUltimo == NULL)			// n�o teve mem�ria?
			return false;									 
		// buscar os dados do produto - tem um m�todo para isso
		if(!InformaDadosProduto(nCodProduto, &stProduto))	// produto n�o existe?
			return false;
		tabMesas[nMesa - 1].ptrUltimo->ptrProximo = NULL;
		tabMesas[nMesa - 1].ptrUltimo->nCodigoProduto = stProduto.nCodigo;
		tabMesas[nMesa - 1].ptrUltimo->dValorProduto = nQtdeProd * stProduto.dPrecoUnitario;
		tabMesas[nMesa - 1].ptrUltimo->nQuantidade = nQtdeProd;
		tabMesas[nMesa - 1].dValorTotal += tabMesas[nMesa - 1].ptrUltimo->dValorProduto;
		tabMesas[nMesa - 1].flgMesaLivreOuOcupada = true;
		// vai completar os dados do produto no produto servido � mesa
		//memcpy_s(tabMesas[nMesa - 1].ptrUltimo, sizeof(PROD_SERVIDO), &stProduto, sizeof(PROD_SERVIDO));
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
		memcpy_s(ptrMesa, sizeof(MESA), &tabMesas[nMesa - 1], sizeof(MESA));	
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
		if(tabMesas[nMesa - 1].flgMesaLivreOuOcupada == true)	// mesa ocupada?
			return false;										// avisa mesa ocupada
		// vamos ocupar a mesa
		tabMesas[nMesa - 1].flgMesaLivreOuOcupada = true;		// mesa ocupada
		tabMesas[nMesa - 1].nQtdePessoas = nQtdePessoas;		// qtde pessoas � mesa
		tabMesas[nMesa - 1].ptrPrimeiro = NULL;					// n�o tem consumo
		tabMesas[nMesa - 1].dValorTotal = 0.0;					// idem
		GetLocalTime(&stTime);									// hora do sistema
		tabMesas[nMesa - 1].stHoraOcupacao.nHora = stTime.wHour; // hora da ocupa��o
		tabMesas[nMesa - 1].stHoraOcupacao.nMinuto = stTime.wMinute; // idem
		return true;											// avisa tudo OK
	}

	// M�todo que lista os produtos da mesa (est�o na lista ligada)
	// 
	//  Cada linha conter� os dados abaixo (o que est� entre par�ntesis � apenas informativo e n�o vai ser mostrado)
	//	xxx(c�digo produto) xxxx(descri�ao)  xxx(qtde) xxxxx(valor total)

	// sprintf_s(cWork, sizeof(cWork), "%3d %s %3d %6.2f %8.2f"
	//	M�scara aconselhada para o sprintf_s est� na linha acima.
	void ListaProdutosMesaOcupada(int nMesa)
	{
		PROD_SERVIDO *ptrWork;					// ponteiro do produto corrente
		char cWork[80];							// para formatar a listagem
		for(ptrWork = tabMesas[nMesa - 1].ptrPrimeiro; ptrWork; ptrWork = ptrWork->ptrProximo)
		{
			if(!InformaDadosProduto(ptrWork->nCodigoProduto, &stProduto)) // n�o encontrou o produto?
			{
				cout << "Produto n�o encontrado!" << endl;
			}
			else 
			{
				sprintf_s(cWork, sizeof(cWork), "%3d %s %3d %6.2f %8.2f",
					ptrWork->nCodigoProduto, stProduto.cDescricao, ptrWork->nQuantidade
					, stProduto.dPrecoUnitario								// n�o estava sendo pedido, mas na mascara aparece!
					, ptrWork->dValorProduto); 
				cout << cWork << endl;
			}			
		} 
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
		char cWork[80];						// para formatar cada linha
		double dServico,					// para valor do servi�o
			dWork;							// para trabalho
		sprintf_s(cWork, sizeof(cWork), " Hora da Ocupa��o: %02d:%02d",
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
		sprintf_s(cWork, sizeof(cWork), "Servi�o: %8.2f", dServico);
		cout << "                           " << cWork << endl;
		// calcular o valor total com servi�o
		dWork = tabMesas[nMesa - 1].dValorTotal + dServico;
		sprintf_s(cWork, sizeof(cWork), "Total: %8.2f", dWork);	
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
	// M�todo que lista todos os produtos para serem vendidos
	//	Par�metros:
	//		Entrada: void
	//		Retorno: void
	void ListarProdutos(void)
	{
		int i;													// indexador gen�rico
		char cWork[100];										// �rea de trabalho
		cout << "\nC�d: Descri��o:                Pre�o:" << endl;
		for (i = 0; i < QTDE_PRODUTOS; i++)
		{
			sprintf_s(cWork, "  %2d %-25s R$%6.2f", tabProdutos[i].nCodigo, tabProdutos[i].cDescricao, tabProdutos[i].dPrecoUnitario);
			cout << cWork << endl;
		}
	}
};