// Definições do Sistema de Restaurante - Prova N1 - 06/04/2017
// 
#include <iostream>
#include <windows.h>
using namespace std;

// definições do restaurante
#define QTDE_MESAS								100
#define QTDE_PRODUTOS							10
#define PAUSA									system("pause")
#define LIMPAR_TELA								system("cls")
#define VERSAO									"Versão 1.0"
#define TURMA									"Noite"

// opções do menu do operador
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
	int nCodigo;									// código do produto
	double dPrecoUnitario;							// preço unitário do produto
	char cDescricao[25];							// descrição do produto
} PRODUTO;

// layout de cada produto fornecido na mesa do restaurante
//	O produto servido estará na lista ligada dos produtos servidos na mesa
typedef struct tagPROD_SERVIDO						// layout de cada produto servido na mesa
{
	int		nCodigoProduto,							// código do produto
		nQuantidade;								// quantidade do produto
	double dValorProduto;							// valor do produto servido, isto é,
													// nQuantidade * dPreçoUnitario
	tagPROD_SERVIDO *ptrProximo;					// endereço para o proximo produto
} PROD_SERVIDO;										// produto servido à mesa

// layout de cada mesa do restaurante
typedef struct tagMESA
{
	bool flgMesaLivreOuOcupada;						// true - indica ocupada
	int nQtdePessoas;								// quantidade de pessoas à mesa
	double dValorTotal;								// valor total de todos os produtos servidos
	HORA stHoraOcupacao;							// hora de ocupação da mesa
	PROD_SERVIDO *ptrPrimeiro,						// endereço do primeiro produto servido
		*ptrUltimo;									// endereço do último produto servido
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
	// Já está totalmente codificado
	//
	clRestaurante()
	{
		int i;										// índice genérico
		char cNomes[QTDE_PRODUTOS][23] = {
		   //12345678901234567890
			"Porção de Arroz     ",					// código 1
			"Cumbuca de Feijão   ",
			"Salada Completa     ",
			"Feijoada            ",
			"Salada de frutas    ",
			"Bife a milaneza     ",					// ........
			"Arroz troupeiro     ",
			"Salada de batatas   ",
			"Omelete completo    ",
			"Cafe expresso       "};				// código 10

		// vai inicializar a tabela de produtos
		// ----<< Observação >>-----------------------------------------
		// Vamos ser criados automaticamente QTDE_PRODUTOS (10) produtos e 
		// somente esses produtos poderão ser servidos à mesa
		//
		for (i = 0; i < QTDE_PRODUTOS; i++)
		{
			tabProdutos[i].nCodigo = i + 1;			// código vai de 1 a QTDE_PRODUTOS
			// vai copiar o nome do produto na tabela de nomes
			strcpy_s(tabProdutos[i].cDescricao, 25, &cNomes[i][0]);
			tabProdutos[i].dPrecoUnitario = 8.80 + (i * 1.50);

		} // for i

		// 1. Inicializar a tabela de mesas indicando que todas estão livres
		//		No início do programa todas as mesas estarão livres e o programa
		//		recomeça a cada inicio.....
		//		Indicar também que a lista ligada de produtos da mesa está vazia

		//  Já foi codificado
		for(i = 0; i < QTDE_MESAS; i++)
		{
			tabMesas[i].flgMesaLivreOuOcupada = false;	// mesa livre
			tabMesas[i].ptrPrimeiro = NULL;				// não tem lista de produtos
		}
	} // construtor

	// Método que informa os dados do produto
	//	Parâmetros:
	//		Entrada: int nCodigo - código do produto desejado
	//				 PRODUTO *ptrProduto - endereço da struct a receber os dados do produto
	//		Retorno: bool - false = produto não existe e true - produto existe e seus
	//						dados estão na struct cujo endereço foi fornecido pelo
	//						invocador do método
	bool InformaDadosProduto(int nCodigo, PRODUTO *ptrProduto)
	{
		// @@@@<02>@@@@
		// 1. Verificar se o código do produto é válido
		if(nCodigo < 0 || nCodigo > QTDE_PRODUTOS)		// o código está entre 0 e QTDE_PRODUTOS?
			return false;								
		//	1.1 - Se não for válido retornar false
		// 2. Copiar os dados do produto no endereço da struct informado pelo chamador
		memcpy_s(ptrProduto, sizeof(PRODUTO), &tabProdutos[nCodigo - 1], sizeof(PRODUTO));
		// 3. Retornar true
		// Codificar este método
		return true;									// para não dar erro
	}

	// Método que insere um novo produto servido à mesa
	// Esse produto vai ser inserido na lista ligada de produtos da mesa
	//	Parâmetros:
	//		Entrada: int nMesa - número da mesa cujo produto está sendo servido
	//							 A validade deste número tem que ser testada no
	//							 invocador do método
	//				 int nCodProduto - código do produto que está sendo servido na 
	//							 mesa. A validade deste código deve ser testada no
	//							 invocador do método
	//				 int nQtdeProd - qtde do produto que está sendo inserido
	//		Retorno: bool - true - se inserção de novo produto na lista ligada
	//							da mesa foi OK.
	//						false - se não há memória suficiente para a inserção
	//							do novo produto que foi servido na mesa
	bool InsereNovoProdutoNaMesa(int nMesa, int nCodProduto, int nQtdeProd)
	{
		// fazer o new do PROD_SERVIDO para o primeiro produto da mesa
		// ou para o último....
		if(tabMesas[nMesa - 1].ptrPrimeiro == NULL)
			tabMesas[nMesa - 1].ptrPrimeiro = 
			tabMesas[nMesa - 1].ptrUltimo = new PROD_SERVIDO;
		else 
			tabMesas[nMesa - 1].ptrUltimo = 
			tabMesas[nMesa - 1].ptrUltimo->ptrProximo = new PROD_SERVIDO;
		// verificar se havia memória para esse produto e se não há, retornar false.
		if(tabMesas[nMesa - 1].ptrUltimo == NULL)			// não teve memória?
			return false;									 
		// buscar os dados do produto - tem um método para isso
		if(!InformaDadosProduto(nCodProduto, &stProduto))	// produto não existe?
			return false;
		tabMesas[nMesa - 1].ptrUltimo->ptrProximo = NULL;
		tabMesas[nMesa - 1].ptrUltimo->nCodigoProduto = stProduto.nCodigo;
		tabMesas[nMesa - 1].ptrUltimo->dValorProduto = nQtdeProd * stProduto.dPrecoUnitario;
		tabMesas[nMesa - 1].ptrUltimo->nQuantidade = nQtdeProd;
		tabMesas[nMesa - 1].dValorTotal += tabMesas[nMesa - 1].ptrUltimo->dValorProduto;
		tabMesas[nMesa - 1].flgMesaLivreOuOcupada = true;
		// vai completar os dados do produto no produto servido à mesa
		//memcpy_s(tabMesas[nMesa - 1].ptrUltimo, sizeof(PROD_SERVIDO), &stProduto, sizeof(PROD_SERVIDO));
		return true;										// indica que foi tudo OK
	}

	// Método que verifica se a mesa está ocupada
	// Se ela estiver ocupada será retornado true e no ptrMesa serão copiados os
	//	dados da mesa ocupada
	// Se a mesa estiver desocupada retornar false
	//	Parâmetros:
	//		Entrada: int nMesa - mesa a ser testada
	//				 MESA *ptrMesa - ponteiro da struct que irá receber os dados da mesa
	//		Retorno: bool - true - mesa ocupada e os dados dela estão em ptrMesa
	//						false - mesa não ocupada
	bool VerificaSeMesaOcupada(int nMesa, MESA *ptrMesa)
	{
		if(tabMesas[nMesa - 1].flgMesaLivreOuOcupada == false)	// mesa desocupada?
			return false;										// indica mesa desocupada
		// copiar os dados da mesa que está ocupada na struct apontada pelo chamador
		memcpy_s(ptrMesa, sizeof(MESA), &tabMesas[nMesa - 1], sizeof(MESA));	
		return true;											// avisa tudo OK
	}


	// Método que ocupa uma mesa que deve estar desocupada
	// Este método irá verificar se a mesa está ocupada e se
	//	estiver vai devolver um false
	// Vai ocupar a mesa e quardar quantas pessoas estão na
	// mesa e indicar a hora e minuto da ocupação.
	// Não esquecer de zerar o total da mesa e esvaziar a lista ligada de produtos servidos
	//	Parâmetros:
	//		Entrada: int nMesa - número da mesa a ser ocupada
	//				 int nQtdePessoas - quantidade de pessoas que irão ocupar a mesa
	//		Retorno: bool - true - mesa foi ocupada OK
	//						false - mesa já ocupada
	bool OcuparMesa(int nMesa, int nQtdePessoas)
	{
		SYSTEMTIME stTime;
		if(tabMesas[nMesa - 1].flgMesaLivreOuOcupada == true)	// mesa ocupada?
			return false;										// avisa mesa ocupada
		// vamos ocupar a mesa
		tabMesas[nMesa - 1].flgMesaLivreOuOcupada = true;		// mesa ocupada
		tabMesas[nMesa - 1].nQtdePessoas = nQtdePessoas;		// qtde pessoas à mesa
		tabMesas[nMesa - 1].ptrPrimeiro = NULL;					// não tem consumo
		tabMesas[nMesa - 1].dValorTotal = 0.0;					// idem
		GetLocalTime(&stTime);									// hora do sistema
		tabMesas[nMesa - 1].stHoraOcupacao.nHora = stTime.wHour; // hora da ocupação
		tabMesas[nMesa - 1].stHoraOcupacao.nMinuto = stTime.wMinute; // idem
		return true;											// avisa tudo OK
	}

	// Método que lista os produtos da mesa (estão na lista ligada)
	// 
	//  Cada linha conterá os dados abaixo (o que está entre parêntesis é apenas informativo e não vai ser mostrado)
	//	xxx(código produto) xxxx(descriçao)  xxx(qtde) xxxxx(valor total)

	// sprintf_s(cWork, sizeof(cWork), "%3d %s %3d %6.2f %8.2f"
	//	Máscara aconselhada para o sprintf_s está na linha acima.
	void ListaProdutosMesaOcupada(int nMesa)
	{
		PROD_SERVIDO *ptrWork;					// ponteiro do produto corrente
		char cWork[80];							// para formatar a listagem
		for(ptrWork = tabMesas[nMesa - 1].ptrPrimeiro; ptrWork; ptrWork = ptrWork->ptrProximo)
		{
			if(!InformaDadosProduto(ptrWork->nCodigoProduto, &stProduto)) // não encontrou o produto?
			{
				cout << "Produto não encontrado!" << endl;
			}
			else 
			{
				sprintf_s(cWork, sizeof(cWork), "%3d %s %3d %6.2f %8.2f",
					ptrWork->nCodigoProduto, stProduto.cDescricao, ptrWork->nQuantidade
					, stProduto.dPrecoUnitario								// não estava sendo pedido, mas na mascara aparece!
					, ptrWork->dValorProduto); 
				cout << cWork << endl;
			}			
		} 
	}

	// Método que fecha a mesa, isto é,
	//	exibe quantas pessoas ocupam a mesa e a partir de que hora
	//	Depois chama o método que ListaProdutosMesaOcupada que
	//		irá listar os produtos que foram servidos na mesa
	//	Depois irá mostrar o total, calcular 10% de serviço e 
	//  exibir mais o serviço e o novo total e depois mostrar o valor
	//  total dividido pelo número de pessoas à mesa
	//		Layout de impressão:
	//	Mesa: xxx	Qtde Pessoas: xx	Hora Ocupação: hh:mm
	//	xxx xxxx(descriçao)  xxx(qtde) xxxxx(valor total) (esta parte é de outro método)
	//						...... repetir para n produtos
	//											----------------
	//											xxxxxxx(total)
	//								10% serviço:    xxxxx
	//											----------------
	//  Valor por xx pessoas: xxxxxx			xxxxxxxx(Total com serviço)
	//	Parâmetros:
	//		Entrada: int nMesa - mesa que vai ser fechada
	//		Retorno: bool - true - mesa foi fechada OK
	bool FecharMesa(int nMesa)
	{
		char cWork[80];						// para formatar cada linha
		double dServico,					// para valor do serviço
			dWork;							// para trabalho
		sprintf_s(cWork, sizeof(cWork), " Hora da Ocupação: %02d:%02d",
			tabMesas[nMesa - 1].stHoraOcupacao.nHora,
			tabMesas[nMesa - 1].stHoraOcupacao.nMinuto);
		cout << "Mesa: " << nMesa << " Qtde Pessoas: " << 
			tabMesas[nMesa - 1].nQtdePessoas << cWork << endl << endl;
		ListaProdutosMesaOcupada(nMesa);
		cout << "                            ----------" << endl;
		sprintf_s(cWork, sizeof(cWork), "Sub-total: %8.2f",
			tabMesas[nMesa - 1].dValorTotal);
		cout << "                               " << cWork << endl;
		// vai calcular o serviço
		dServico = tabMesas[nMesa - 1].dValorTotal * 10 / 100;
		sprintf_s(cWork, sizeof(cWork), "Serviço: %8.2f", dServico);
		cout << "                           " << cWork << endl;
		// calcular o valor total com serviço
		dWork = tabMesas[nMesa - 1].dValorTotal + dServico;
		sprintf_s(cWork, sizeof(cWork), "Total: %8.2f", dWork);	
		cout << "                             " << cWork << endl;
		cout << "Por pessoa: " << dWork / tabMesas[nMesa - 1].nQtdePessoas << endl;
		return true;
	}

	// Método que libera uma mesa que deve estar ocupada
	// Se a mesa não estiver ocupada retornar false
	//	Parâmetros:
	//		Entrada: int nMesa - número da mesa que vai ser liberada
	//		Retorno: bool - true - mesa foi liberada OK. false - mesa não ocupada
	bool LiberarMesa(int nMesa)
	{
		if(tabMesas[nMesa - 1].flgMesaLivreOuOcupada == false)	// mesa desocupada?
			return false;										// avisa mesa desocupada
		// a mesa está ocupada portanto vamos desocupá-la
		tabMesas[nMesa - 1].flgMesaLivreOuOcupada = false;		// desocupa a mesa
		return true;
	}
	// Método que lista todos os produtos para serem vendidos
	//	Parâmetros:
	//		Entrada: void
	//		Retorno: void
	void ListarProdutos(void)
	{
		int i;													// indexador genérico
		char cWork[100];										// área de trabalho
		cout << "\nCód: Descrição:                Preço:" << endl;
		for (i = 0; i < QTDE_PRODUTOS; i++)
		{
			sprintf_s(cWork, "  %2d %-25s R$%6.2f", tabProdutos[i].nCodigo, tabProdutos[i].cDescricao, tabProdutos[i].dPrecoUnitario);
			cout << cWork << endl;
		}
	}
};