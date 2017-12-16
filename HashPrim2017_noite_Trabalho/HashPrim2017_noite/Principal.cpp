// Programa de Ponto de Venda com hashing
// FATEC - MC - JCB - 09/03/2017 - Versão 0.0
#include "PDV.h"
// Função que pede e recebe um código EAN
//	Parâmetros:
//		Entrada: char *ptrEAN - ponteiro de um vetor de char que receberá o string
//								contendo o código EAN
//				 char *ptrAcao - ponteiro para um string que contém a ação em execução
//		Retorno: bool - true - foi digitado um EAN válido
//						false - o operador digitou zero e Enter para cancelar
//								a transação
bool PedeRecebeEAN(char *ptrEAN, char *ptrAcao)
{
	char szCodigo[30];					// para receber o código EAN com o máximo de 13 digitos
	do
	{
		cout << "\n\t" << ptrAcao << endl;
		cout << "Digite o código EAN" << endl
			<< "Ou zero e Enter para cancelar: ";
		cin >> szCodigo;
		if(strcmp(szCodigo, "0") == 0)			// cancelou?
			return false;
	} while(strlen(szCodigo) > 13);
	strcpy_s(ptrEAN, 14, szCodigo);
	return true;								
}
//
// entry point do programa
//
void main(void)
{
	int nHash,										// hash code a ser listado
		nQtde;										// qtde de hash listado
	bool flgStatus;									// recebe os status da construção
	char cOpcao;									// opção do operador
	PRODUTO stProduto;								// struct para conter os dados de um produto
	CHAVE_BUSCA stChaveBusca;						// struct para conter os dados de uma chave de busca

	PAIS_BRASIL;									// acentuação brasileira
	clPontoVenda objPDV(&flgStatus);				// instancia a classe e cria o objeto
	if(!flgStatus)									// erro na construção do objeto?
	{
		cout << "Erro na construção!" << endl;
		PAUSA;
		return;										// volta ao Sistema Operacional
	}
	// loop infinito
	while(true)
	{
		LIMPAR_TELA;
		cout << "\n\tFATEC-Ponto de Venda" << endl;
		cout << INCLUIR_PRODUTO << " - Incluir um novo produto" << endl;
		cout << EXCLUIR_PRODUTO << " - Excluir um produto existente" << endl;
		cout << MOSTRAR_PRODUTO << " - Mostrar os dados de um produto" << endl;
		cout << VENDER_PRODUTO << " - Vender um produto" << endl;
		cout << LISTAR_HASH_CODE << " - Listar os produtos de um dado hash" << endl;
		cout << LISTAR_TODOS_HASH_CODE << " - Listar todos o produtos de todos hash code" << endl;
		cout << SAIR_DO_PROGRAMA << " - Sair do programa" << endl;
		cout << "\n\tSelecione: ";
		cin >> cOpcao;						// opção do operador
		cOpcao = toupper(cOpcao);			// converte para maiúscula
		switch(cOpcao)						// avaliar a opção escolhida
		{
			case INCLUIR_PRODUTO:
				if(!PedeRecebeEAN(stProduto.cEAN, "Incluir produto")) // cancelou?
					break;
				// verificar se o produto existe
				// incluir o produto
				if(objPDV.VerificaSeExiste(stProduto.cEAN, &stProduto, &stChaveBusca))	// produto existe?
				{	// produto já cadastrado
					cout << "Produto: " << stProduto.cEAN << " Descrição: " <<
						stProduto.cDescricao << endl << "Já existe!" << endl;
					PAUSA;
					break;					// volta ao menu
				}
				// não existe - pedir seus dados e incluir
				cin.ignore(1, EOF);			// ignorar a tecla Enter
				cout << "Descrição: ";
				cin.getline(stProduto.cDescricao, 40, '\n');
				cout << "Preço unitário: ";
				cin >> stProduto.dPrecoUnit;
				stProduto.dTotalVendido = 0.0;
				if(!objPDV.IncluirNovoProduto(&stProduto))		// problema na inclusão?
				{
					cout << "Problema na inclusão do produto: " << stProduto.cEAN << endl;
					PAUSA;
				}
				break;						// voltar ao menu
			case EXCLUIR_PRODUTO:
				if(!PedeRecebeEAN(stProduto.cEAN, "Excluir produto")) // cancelou?
					break;
				// verificar se o produto existe
				// incluir o produto
				if(!objPDV.VerificaSeExiste(stProduto.cEAN, &stProduto, &stChaveBusca))	// produto existe?
				{	// produto já cadastrado
					cout << "Produto não encontrado!" << endl;
					break;					// volta ao menu
				}
				cout << "\n\tDeseja realmente excluir" << endl
					<< "Descrição: " << stProduto.cDescricao << endl
					<< "" << stProduto.dPrecoUnit << endl
					<< "" << stProduto.dTotalVendido << endl
					<< "Digite (S/N): ";
				cin >> cOpcao;
				if(cOpcao != 'S' && cOpcao != 's')
				{
					cout << "Cancelou!" << endl;
					PAUSA;
					break;
				}
				objPDV.ExcluirProduto(&stProduto, stChaveBusca.nPosicional);
				break;						// voltar ao menu
			case MOSTRAR_PRODUTO:
				if(!PedeRecebeEAN(stProduto.cEAN, "Mostrar Produto")) // cancelou?
					break;
				if(objPDV.VerificaSeExiste(stProduto.cEAN, &stProduto, &stChaveBusca))	// produto existe?
				{	// produto já cadastrado
					cout << "Produto: " << stProduto.cEAN << " Descrição: " <<
						stProduto.cDescricao << endl 
						<< "Preço: " << stProduto.dPrecoUnit << endl
						<< "Quantidade total vendida: " << stProduto.dTotalVendido << endl;
					PAUSA;
					break;					// volta ao menu
				}
				break;						// voltar ao menu
			case VENDER_PRODUTO:	
				if(!PedeRecebeEAN(stProduto.cEAN, "Vender Produto")) // cancelou?
					break;
				if(objPDV.VerificaSeExiste(stProduto.cEAN, &stProduto, &stChaveBusca))	// produto existe?
				{	// produto já cadastrado
					do
					{
						cout << "Produto: " << stProduto.cEAN << "\nDescrição: " <<
						stProduto.cDescricao 
						<< " Preço: " << stProduto.dPrecoUnit << endl
						<< "Digite a quantidade vendida: ";
					cin >> nQtde;
					} while(nQtde < 0);
					cout << "Cobrar R$ " << stProduto.dPrecoUnit * nQtde << endl;
					stProduto.dTotalVendido += nQtde;		// adiciona a quantidade vendida do momento
					if(!objPDV.VenderProduto(&stProduto, stChaveBusca.nPosicional))
					{
						cout << "Erro de gravação!" << endl;
						PAUSA;
					}
					PAUSA;
					break;					// volta ao menu
				}
				break;						// voltar ao menu
			case LISTAR_HASH_CODE:
				do
				{
					cout << "Informe um hash code entre 0 e " << QTDE_HASH - 1 << " : ";
					cin >> nHash;
				} while(nHash < 0 || nHash > QTDE_HASH - 1);
				if(!objPDV.ListarCodigosDeHashCode(nHash))		// hash code vazio?
				{
					cout << "Hash code " << nHash << " está vazio!" << endl;
				}
				PAUSA;
				break;						// voltar ao menu
			case LISTAR_TODOS_HASH_CODE:
				LIMPAR_TELA;
				cout << "\n\tListagem de todos os produtos de todos hash code" << endl;
				for(nHash = nQtde = 0; nHash < QTDE_HASH; nHash++)
				{
					if(++nQtde == 20)				// já listou vinte hash code?
					{
						nQtde = 0;
						cout << "\tContinuar a listagem? (S ou N): ";
						cin >> cOpcao;
						if(cOpcao != 'S' && cOpcao != 's')	// não vai continuar?
							break;					// cai fora do for
					}
					if(!objPDV.ListarCodigosDeHashCode(nHash))			// vazio?
					{
						cout << "\tHash code " << nHash << " Qtde: 0" << endl;
						continue;
					}
				} // for nHash
				cout << "\n\tFim da listagem" << endl;
				PAUSA;
				break;
			case SAIR_DO_PROGRAMA:
				cout << "Sair realmente? (S ou N): ";
				cin >> cOpcao;
				if(cOpcao == 'S' || cOpcao == 's')	// sair realmente?
				{	// vai encerrar o programa
					objPDV.FecharCadastro();		// fecha o cadastro
					return;							// volta ao Sistema Operacional
				}
				break;						// voltar ao menu
			default:
				cout << "Opção inválida!" << endl;
				PAUSA;
		} // switch
	} // while
} // main



