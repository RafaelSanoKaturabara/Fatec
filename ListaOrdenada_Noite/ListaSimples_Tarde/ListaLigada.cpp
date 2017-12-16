// Programa exemplo de uma lista ligada simples com inser��o no �ltimo da lista
// FATEC - MC - JCB - 16/02/2017 - Vers�o 0.0
#include "Lista.h"
// Fun��o que pede o c�digo do cliente
//	Par�metros:
//		Entrada: char *ptrTransacao - ponteiro para um string que cont�m a a��o sendo executada
//				 int *ptrCodigo - ponteiro da inteira a receber o c�digo
//		Retorno: bool - true - foi informado um c�digo do cliente
//						false - a a��o foi cancelada
bool PedeCodigoCliente(char *ptrTransacao, int *ptrCodigo)
{
	cout << "\n\t" << ptrTransacao << endl;
	cout << "\nInforme o c�digo do cliente" << endl
		<< "Ou zero para cancelar a a��o pedida: ";
	cin >> *ptrCodigo;						// a inteira apontada recebe o c�digo
	if(*ptrCodigo == 0)						// cancelar a a��o?
		return false;						// avisa que cancelou
	return true;							// indica que tem um c�digo digitado
}

//
//	entry point do programa
//
void main(void)
{
	CLIENTE stCliente;								// para conter os dados de um cliente
	char cOpcao;									// op��o de escolha do operador
	setlocale(LC_ALL, "portuguese_brazil");			// acentua��o brasileira
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
		cin >> cOpcao;								// recebe a op��o do operador
		cOpcao = toupper(cOpcao);					// op��o em mai�scula
		switch(cOpcao)								// avaliar a op��o escolhida
		{
			case INCLUIR_CLIENTE:
				if(!PedeCodigoCliente("Incluir cliente", &stCliente.nCodCliente)) // cancelou?
					break;							// volta ao menu
				// verificar se o cliente existe
				if(objCliente.VerificaSeClienteExiste(stCliente.nCodCliente, &stCliente))
				{	// cliente existe
					cout << "\nCliente: " << stCliente.nCodCliente << " Nome: " 
						<< stCliente.cNomeCliente << endl << "\tJ� existe!" << endl;
					PAUSA;
					break;							 // volta ao menu
				}
				// cliente n�o existe
				cout << "\nNome do cliente: ";
				cin.ignore(1, EOF);					// ignorar a tecla ENTER do buffer do teclado
				cin.getline(stCliente.cNomeCliente, 40, '\n'); // recebe um texto com ENTER
				cout << "Saldo do cliente: ";
				cin >> stCliente.dSaldoCliente;
				// fazer a inser��o
				if(!objCliente.InserirCliente(&stCliente))	// problema na inser��o?
				{	// n�o tem mem�ria dispon�vel para inser��o do cliente
					cout << "N�o tem mem�ria dispon�vel!" << endl;
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
						<< "\tConfirma a exclus�o? (S ou N): ";
					cin >> cOpcao;					 // recebe a confirma��o ou n�o
					if(cOpcao != 'S' && cOpcao != 's') // n�o foi S ou s?
						break;						 // volta ao menu
					// fazer a exclus�o
					if(!objCliente.ExcluirClienteDaLista(stCliente.nCodCliente)) // n�o encontrou?
					{
						cout << "Problema na exclus�o!" << endl;
						PAUSA;
					}
					break;							 // volta ao menu
				}
				else
				{	// cliente n�o existe
					cout << "Cliente de c�digo: " << stCliente.nCodCliente 
						<< " n�o existe!" << endl;
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
				{	// cliente n�o existe
					cout << "Cliente de c�digo: " << stCliente.nCodCliente 
						<< " n�o existe!" << endl;
					PAUSA;
				}
				break;								// volta ao menu
			case CLASSIFICAR_LISTA:
				if(!objCliente.ClassificarListaLigada())
				{	// lista est� vazia
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
				cout << "\nOp��o inv�lida!" << endl;
				PAUSA;
		} // switch
	} // while
} // main





