// Programa de ponto de venda com hashing
// FATEC - MC - JCB - 09/03/2017 - Versão 0.0
#include "PDV.h"
// Função que pede e recebe um códido EAN
//	Parâmetros: 
//		Entrada: char *ptrEAN - ponteiro de um vetor de char que receberá o string
//							   contendo o código EAN
//					char *ptrAcao - ponteiro para um string que contém a ação em execução
//		Retorno: bool - true - foi digitado um EAN válido
//						false - o operador digitou zero e enter para cancelar
//								a transação
bool PedeRecebeEAN(char *ptrEAN, char *ptrAcao)
{
	char szCodigo[30];										// para receber o código EAN com o máximo de 13 digitos	
	do
	{
		LIMPAR_TELA;
		cout << "\n\t" << ptrAcao << endl;
		cout << "Digite o código EAN" << endl 
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
		nQtde;												// indexador genérico
	bool flgStatus,											// recebe os status da construção
		flgListar;											// true continua listando - false - para de listar
	char cOpcao;											// opção do operador 
	
	PRODUTO stProduto;										// struct para conter os dados de um produto

	PAIS_BRASIL;											// acentuação brasileira
	clPontoVenda objPDV(&flgStatus);						// instancia a classe e cria o objeto
	if(!flgStatus)											// erro na construção do objeto?
	{
		cout << "Erro na construção!" << endl;
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
		cin >> cOpcao;										// opção do operador
		cOpcao = toupper(cOpcao);							// converte para maiúscula
		switch(cOpcao)
		{
			case INCLUIR_PRODUTO:
				if(!PedeRecebeEAN(stProduto.cEAN, "Incluir um novo produto"))
				{
					cout << "Operador cancelou a operação!" << endl;
					PAUSA;
					break;
				}
				// verificar se o produto existe
				// incluir o produto
				if(objPDV.VerificaSeExiste(stProduto.cEAN, &stProduto))	// produto existe?
				{	// produto já cadastrado
					cout << "Produto: " << stProduto.cEAN << " Descrição: " << 
						stProduto.cDescricao << endl << "Já existe!" << endl;
					PAUSA;
					break;									// voltar ao menu
				}
				// não existe - pedir seus dados e incluir
				cin.ignore(1, EOF);							// ignorar a tecla enter 
				cout << "Descrição: ";
				cin.getline(stProduto.cDescricao, 40, '\n');
				cout << "Preço unitário: ";
				cin >> stProduto.dPrecoUnit;
				stProduto.dTotalVendido = 0.0;
				if(!objPDV.IncluirNovoProduto(&stProduto))	// problema na inclusão?
				{
					cout << "Problema na inclusão do produto: " << stProduto.cEAN << endl;
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
					cout << "Hash code " << nHash << " está vazio!" << endl;
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

					if(++nQtde == 20)				// já listou vinte hash code?
					{
						nQtde = 0;
						cout << "\tContinuar a listagem? (S ou N): ";
						cin >> cOpcao;
						if(cOpcao != 'S' && cOpcao != 's')	// não vai continuar?
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
				cout << "Opção inválida!" << endl;
				PAUSA;
		} // switch
	} // while
} // main