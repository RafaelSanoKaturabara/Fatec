// Programa de ponto de venda com hashing
// FATEC - MC - JCB - 09/03/2017 - Vers�o 0.0
#include "PDV.h"
// Fun��o que pede e recebe um c�dido EAN
//	Par�metros: 
//		Entrada: char *ptrEAN - ponteiro de um vetor de char que receber� o string
//							   contendo o c�digo EAN
//					char *ptrAcao - ponteiro para um string que cont�m a a��o em execu��o
//		Retorno: bool - true - foi digitado um EAN v�lido
//						false - o operador digitou zero e enter para cancelar
//								a transa��o
bool PedeRecebeEAN(char *ptrEAN, char *ptrAcao)
{
	char szCodigo[30];										// para receber o c�digo EAN com o m�ximo de 13 digitos	
	do
	{
		LIMPAR_TELA;
		cout << "\n\t" << ptrAcao << endl;
		cout << "Digite o c�digo EAN" << endl 
			<< "Ou zero e Enter para cancelar: ";
		cin >> szCodigo;
		if(strcmp(szCodigo, "0") == 0)					// cancelou?
			return false;		
	} while (strlen(szCodigo) > 13);
	strcpy_s(ptrEAN, 14, szCodigo);
	return true;										
}
// 
// entry point do programa
//
void main(void)
{
	int nHash,												// hash code a ser listado
		nQtde;												// indexador gen�rico
	bool flgStatus,											// recebe os status da constru��o
		flgListar;											// true continua listando - false - para de listar
	char cOpcao;											// op��o do operador 
	
	PRODUTO stProduto;										// struct para conter os dados de um produto

	PAIS_BRASIL;											// acentua��o brasileira
	clPontoVenda objPDV(&flgStatus);						// instancia a classe e cria o objeto
	if(!flgStatus)											// erro na constru��o do objeto?
	{
		cout << "Erro na constru��o!" << endl;
		PAUSA;
		return;												// volta ao sistema operacional
	}
	// loop infinito
	while(true)
	{
		LIMPAR_TELA;
		cout << "\n\tFATEC-Ponto de Venda" << endl;
		cout << INCLUIR_PRODUTO << " - Incluir um novo produto" << endl
			<< EXCLUIR_PRODUTO << " - Excluir um produto existente" << endl
			<< MOSTRAR_PRODUTO << " - Mostrar os dados de um produto" << endl
			<< VENDER_PRODUTO << " - Vender um produto" << endl
			<< LISTAR_HASH_CODE << " - Listar os produto de um dado hash" << endl
			<< LISTAR_TODOS_HASH_CODE << " - Listar todos os produtos de todos hash code" << endl
			<< SAIR_DO_PROGRAMA << " - Sair do programa" << endl
			<< "\n\tSelecione: ";
		cin >> cOpcao;										// op��o do operador
		cOpcao = toupper(cOpcao);							// converte para mai�scula
		switch(cOpcao)
		{
			case INCLUIR_PRODUTO:
				if(!PedeRecebeEAN(stProduto.cEAN, "Incluir um novo produto"))
				{
					cout << "Operador cancelou a opera��o!" << endl;
					PAUSA;
					break;
				}
				// verificar se o produto existe
				// incluir o produto
				if(objPDV.VerificaSeExiste(stProduto.cEAN, &stProduto))	// produto existe?
				{	// produto j� cadastrado
					cout << "Produto: " << stProduto.cEAN << " Descri��o: " << 
						stProduto.cDescricao << endl << "J� existe!" << endl;
					PAUSA;
					break;									// voltar ao menu
				}
				// n�o existe - pedir seus dados e incluir
				cin.ignore(1, EOF);							// ignorar a tecla enter 
				cout << "Descri��o: ";
				cin.getline(stProduto.cDescricao, 40, '\n');
				cout << "Pre�o unit�rio: ";
				cin >> stProduto.dPrecoUnit;
				stProduto.dTotalVendido = 0.0;
				if(!objPDV.IncluirNovoProduto(&stProduto))	// problema na inclus�o?
				{
					cout << "Problema na inclus�o do produto: " << stProduto.cEAN << endl;
					PAUSA;
					break;
				}
				break;										// voltar ao menu
			case EXCLUIR_PRODUTO:
				break;										// voltar ao menu
			case MOSTRAR_PRODUTO:
				break;										// voltar ao menu
			case VENDER_PRODUTO:
				break;										// voltar ao menu
			case LISTAR_HASH_CODE:
				do
				{
					cout << "Informe um hash code entre 0 e " << QTDE_HASH - 1<< ": ";
					cin >> nHash;
				} while(nHash < 0 || nHash > QTDE_HASH - 1);
				if(!objPDV.ListarCodigosDeHashCode(nHash))	// hash code vazio?
				{
					cout << "Hash code " << nHash << " est� vazio!" << endl;
				}
				PAUSA;
				break;										// voltar ao menu
			case LISTAR_TODOS_HASH_CODE:
				LIMPAR_TELA;
				cout << "\n\tListagem de todos os produtos de todos hash code" << endl;
				for(nHash = nQtde = 0; nHash < QTDE_HASH; nHash++)
				{
					if(!objPDV.ListarCodigosDeHashCode(nHash))			// vazio?
					{
						cout << "\tHash code " << nHash << " Qtde: 0" << endl;
						continue;
					}

					if(++nQtde == 20)				// j� listou vinte hash code?
					{
						nQtde = 0;
						cout << "\tContinuar a listagem? (S ou N): ";
						cin >> cOpcao;
						if(cOpcao != 'S' && cOpcao != 's')	// n�o vai continuar?
							break;					// cai fora do for
					}
				} // for nHash
				cout << "\n\tFim da listagem" << endl;
				PAUSA;
				break;
				break;										// volta ao menu
			case SAIR_DO_PROGRAMA:
				cout << "Deseja realmente sair? (S ou N): ";
				cin >> cOpcao;
				if(cOpcao == 'S' || cOpcao == 's')			// sair realmente?
				{	// vai encerrar o programa
					objPDV.FecharCadastro();				// fecha o cadastro
					return;									// volta ao sistema operacional
				}
				break;										// voltar ao menu
			default:
				cout << "Op��o inv�lida!" << endl;
				PAUSA;
		} // switch
	} // while
} // main