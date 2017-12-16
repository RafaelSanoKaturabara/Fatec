// Programa que controla uma Ag�ncia Banc�ria
// FATEC - MC - JCB - 09/03/2017 - Vers�o 0.0
#include "AgBancaria.h"
// Fun��o que pede o c�digo do cliente
//	Par�metros:
//		Entrada: char *ptrCodigo - ponteiro de um vetor de char a receber o c�digo do cliente 
//				 char *ptrTransacao - ponteiro do string que informa a transa��o sendo realizada
//		Retorno: true - foi informado um c�digo de cliente
//				 false - indica que o operador digitou zero e Enter cancelando
//							a transa��o
bool PedirCodigoCliente(char *ptrCodigo, char *ptrTransacao)
{
	char szCodigo[20];					// para receber o c�digo do cliente
	do
	{
		cout << "\n" << ptrTransacao << endl;
		cout << "Digite o c�digo do cliente" << endl 
			<<	"Ou zero e Enter para cancelar a transa��o: ";
		cin >> szCodigo;							// informa o c�digo
		if(strcmp(szCodigo, "0") == 0)				// digitou zero e enter?
			return false;							// cancela a transa��o
	} while(strlen(szCodigo) > 10);				// loop enquanto o c�digo for maior que possivel 
	// digitou algo v�lido
	strcpy_s(ptrCodigo, 11, szCodigo);				// copia o c�digo
	return true;
}
//
// entry point do programa
//
void main(void)
{
	int nHash,										// para receber um dado hash
		nQtde;										// para contagem de clientes
	CLIENTE stCliente;								// para conter os dados de um cliente
	bool flgStatus;									// status da constru��o
	char cOpcao;									// op��o do operador
	PAIS_BRASIL;									// acentua��o brasileira
	clAgencia objAgencia(&flgStatus);				// instancia a classe clAgencia e cria o
													// objeto objAgencia e em flgStatus receber
													// os status da constru��o
	if(!flgStatus)									// problema na constru��o?
	{
		cout << "Houve problema na constru��o da Ag�ncia Banc�ria!" << endl;
		PAUSA;
		return;
	}
	// loop infinito de op��es do operador
	while(true)
	{
		LIMPAR_TELA;
		cout << "\n\tFATEC - Ag�ncia Banc�ria" << endl;
		cout << INCLUIR_CLIENTE << " - Incluir novo cliente" << endl;
		cout << EXCLUIR_CLIENTE << " - Excluir cliente existente" << endl;
		cout << MOSTRAR_CLIENTE << " - Mostrar dados do cliente" << endl;
		cout << DEPOSITAR_VALOR << " - Fazer dep�sito" << endl;
		cout << SACAR_VALOR << " - Fazer saque" << endl;
		cout << LISTAR_UM_DADO_HASH << " - Listar um dado hash code" << endl;
		cout << LISTAR_TODOS_CLIENTES << " - Listar todos os clientes de todos os hash" << endl;
		cout << SAIR_DO_PROGRAMA << " - Sair do programa" << endl;
		cout << "\tSelecione: ";
		cin >> cOpcao;					// op��o do operador
		cOpcao = toupper(cOpcao);		// op��o em mai�scula
		switch(cOpcao)					// avaliar a op��o escolhida
		{
			case INCLUIR_CLIENTE:
				if(!PedirCodigoCliente(stCliente.cAgCodigo, "Incluir novo cliente")) 
					break;				// volta ao menu porque retornou falso
				if(objAgencia.VerificaSeClienteExiste(stCliente.cAgCodigo, &stCliente)) 
				{	// o cliente j� est� cadastrado
					cout << "Cliente: " << stCliente.cAgCodigo << " Nome: " 
						<< stCliente.cNomeCliente << endl << " Saldo: " << stCliente.dSaldoCliente
						<< "\tJ� est� cadastrado!" << endl;
					PAUSA;
					break;				// volta ao menu
				}
				// o cliente n�o existe
				cin.ignore(1, EOF);		// retira a tecla Enter do buffer do teclado
				cout << "Nome: ";
				cin.getline(stCliente.cNomeCliente, 40, '\n'); // nome e sobrenome do cliente
				cout << "Saldo: ";
				cin >> stCliente.dSaldoCliente;
				if(!objAgencia.InserirCliente(&stCliente))		// problema na inser��o?
				{	// houve problema na inser��o do cliente
					cout << "Problema na inser��o do cliente: " << stCliente.cAgCodigo << endl
						<< " Nome: " << stCliente.cNomeCliente << endl;
					PAUSA;
				}
				break;					// volta ao menu
			case EXCLUIR_CLIENTE:
				break;					// volta ao menu
			case MOSTRAR_CLIENTE:
				break;					// volta ao menu
			case DEPOSITAR_VALOR:
				break;					// volta ao menu
			case SACAR_VALOR:
				break;					// volta ao menu
			case LISTAR_UM_DADO_HASH:
				// loop para ter um hash v�lido
				do
				{
					cout << "Informe o hash code entre 0 e " << HASH_MAX - 1 << ": ";
					cin >> nHash;
				} while(nHash < 0 || nHash > HASH_MAX - 1);
				if(!objAgencia.ListarClientesPorUmDadoHash(nHash))	// n�o tem cliente neste HASH?
				{	// n�o tem clientes neste HASH
					cout << "Sem clientes neste hash code" << endl;
					PAUSA;
				}
				else
					PAUSA;
				break;					// volta ao menu
			case LISTAR_TODOS_CLIENTES:
				LIMPAR_TELA;
				cout << "\tListagem de todos os clientes de todos os hash code" << endl;
				for( nHash = nQtde = 0; nHash < HASH_MAX; nHash++)
				{
					if(!objAgencia.ListarClientesPorUmDadoHash(nHash)) // hash vazio?
					{
						cout << "Hash: " << nHash << " vazio" << endl;
					}
					nQtde++;
					if(nQtde == 20)						// listou 20 hash?
					{
						nQtde = 0;						// re-inicia a quantidade
						cout << "Continuar a listagem? (S ou N): ";
						cin >> cOpcao;
						if(cOpcao != 'S' && cOpcao != 's')	// n�o vai continuar?
							break;						// cai fora do for
					}
				}
				cout << "\n\tFim da listagem" << endl;
				PAUSA;
				break;
			case SAIR_DO_PROGRAMA:
				cout << "\n\tSair realmente? (S ou N): ";
				cin >> cOpcao;		
				if(cOpcao == 'S' || cOpcao == 's')		// sair realmente?
				{
					objAgencia.FecharCadastro();		// fechar o cadastro de clientes
					return;								// volta ao Sistema Operacional
				}
				break;					// volta ao menu
			default:
				cout << "Op��o inv�lida!" << endl;
				PAUSA;
		} // switch
	} // while
} // main