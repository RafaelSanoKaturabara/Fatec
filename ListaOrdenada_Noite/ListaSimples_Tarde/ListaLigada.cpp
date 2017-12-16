// Programa exemplo de uma lista ligada simples com inserção no último da lista
// FATEC - MC - JCB - 16/02/2017 - Versão 0.0
#include "Lista.h"
// Função que pede o código do cliente
//	Parâmetros:
//		Entrada: char *ptrTransacao - ponteiro para um string que contém a ação sendo executada
//				 int *ptrCodigo - ponteiro da inteira a receber o código
//		Retorno: bool - true - foi informado um código do cliente
//						false - a ação foi cancelada
bool PedeCodigoCliente(char *ptrTransacao, int *ptrCodigo)
{
	cout << "\n\t" << ptrTransacao << endl;
	cout << "\nInforme o código do cliente" << endl
		<< "Ou zero para cancelar a ação pedida: ";
	cin >> *ptrCodigo;						// a inteira apontada recebe o código
	if(*ptrCodigo == 0)						// cancelar a ação?
		return false;						// avisa que cancelou
	return true;							// indica que tem um código digitado
}

//
//	entry point do programa
//
void main(void)
{
	CLIENTE stCliente;								// para conter os dados de um cliente
	char cOpcao;									// opção de escolha do operador
	setlocale(LC_ALL, "portuguese_brazil");			// acentuação brasileira
	// instanciar a classe cliente e criar um objeto
	clCliente objCliente;							// criou o objCliente
	// loop infinito do programa
	while(true)
	{
		LIMPAR_TELA;
		cout << "\n\tFATEC - MC - Programa de teste da lista ligada simples" << endl;
		cout << INCLUIR_CLIENTE << " - Incluir novo cliente" << endl;
		cout << EXCLUIR_CLIENTE	<< " - Excluir cliente existente" << endl;
		cout << BUSCAR_CLIENTE << " - Buscar um cliente" << endl;
		cout << CLASSIFICAR_LISTA << " - Classificar lista de clientes" << endl;
		cout << LISTAR_CLIENTES << " - Listar clientes" << endl;
		cout << SAIR_DO_PROGRAMA << " - Sair do programa" << endl;
		cout << "\tSelecione: ";
		cin >> cOpcao;								// recebe a opção do operador
		cOpcao = toupper(cOpcao);					// opção em maiúscula
		switch(cOpcao)								// avaliar a opção escolhida
		{
			case INCLUIR_CLIENTE:
				if(!PedeCodigoCliente("Incluir cliente", &stCliente.nCodCliente)) // cancelou?
					break;							// volta ao menu
				// verificar se o cliente existe
				if(objCliente.VerificaSeClienteExiste(stCliente.nCodCliente, &stCliente))
				{	// cliente existe
					cout << "\nCliente: " << stCliente.nCodCliente << " Nome: " 
						<< stCliente.cNomeCliente << endl << "\tJá existe!" << endl;
					PAUSA;
					break;							 // volta ao menu
				}
				// cliente não existe
				cout << "\nNome do cliente: ";
				cin.ignore(1, EOF);					// ignorar a tecla ENTER do buffer do teclado
				cin.getline(stCliente.cNomeCliente, 40, '\n'); // recebe um texto com ENTER
				cout << "Saldo do cliente: ";
				cin >> stCliente.dSaldoCliente;
				// fazer a inserção
				if(!objCliente.InserirCliente(&stCliente))	// problema na inserção?
				{	// não tem memória disponível para inserção do cliente
					cout << "Não tem memória disponível!" << endl;
					PAUSA;
				}
				break;								// volta ao menu
			case EXCLUIR_CLIENTE:
				if(!PedeCodigoCliente("Excluir cliente", &stCliente.nCodCliente)) // cancelou?
					break;							// volta ao menu
				// verificar se o cliente existe
				if(objCliente.VerificaSeClienteExiste(stCliente.nCodCliente, &stCliente))
				{	// cliente existe
					cout << "\nCliente: " << stCliente.nCodCliente << " Nome: " 
						<< stCliente.cNomeCliente << endl 
						<< "\tConfirma a exclusão? (S ou N): ";
					cin >> cOpcao;					 // recebe a confirmação ou não
					if(cOpcao != 'S' && cOpcao != 's') // não foi S ou s?
						break;						 // volta ao menu
					// fazer a exclusão
					if(!objCliente.ExcluirClienteDaLista(stCliente.nCodCliente)) // não encontrou?
					{
						cout << "Problema na exclusão!" << endl;
						PAUSA;
					}
					break;							 // volta ao menu
				}
				else
				{	// cliente não existe
					cout << "Cliente de código: " << stCliente.nCodCliente 
						<< " não existe!" << endl;
					PAUSA;
				}
				break;								// volta ao menu
			case BUSCAR_CLIENTE:
				if(!PedeCodigoCliente("Buscar cliente", &stCliente.nCodCliente)) // cancelou?
					break;							// volta ao menu
				// verificar se o cliente existe
				if(objCliente.VerificaSeClienteExiste(stCliente.nCodCliente, &stCliente))
				{	// cliente existe
					cout << "\nCliente: " << stCliente.nCodCliente << " Nome: " 
						<< stCliente.cNomeCliente
						<< endl << "Saldo: " << stCliente.dSaldoCliente << endl;
					PAUSA;
					break;							 // volta ao menu
				}
				else
				{	// cliente não existe
					cout << "Cliente de código: " << stCliente.nCodCliente 
						<< " não existe!" << endl;
					PAUSA;
				}
				break;								// volta ao menu
			case CLASSIFICAR_LISTA:
				if(!objCliente.ClassificarListaLigada())
				{	// lista está vazia
					cout << "Lista vazia!" << endl;
					PAUSA;
				}
				break;								// volta ao menu
			case LISTAR_CLIENTES:					
				objCliente.ListarClientes();
				break;								// volta ao menu
			case SAIR_DO_PROGRAMA:
				cout << "Sair realmente? (S ou N): ";
				cin >> cOpcao;
				if(cOpcao == 'S' || cOpcao == 's')	// sair realmente?
					return;							// volta ao sistema operacional
				break;
			default:
				cout << "\nOpção inválida!" << endl;
				PAUSA;
		} // switch
	} // while
} // main





