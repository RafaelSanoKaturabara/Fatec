// Declara��es do programa Ag�ncia Banc�ria com Hash e Cadastro de Clientes
// Condi��o para teste do programa
#define TESTE							1
#include <iostream>
#include <Windows.h>
using namespace std;
// defines do programa
#define PAUSA							system("pause")
#define LIMPAR_TELA						system("cls")
#define HASH_MAX						200
#define QTDE_MAX_CLIENTES				5000
#define PERCENTUAL_CLIENTES_TESTE		50
#define CAMINHO_CADASTRO				"..\\Cadastro.cad"
#define PAIS_BRASIL						setlocale(LC_ALL, "portuguese_brazil")
// op��es do menu do operador
#define INCLUIR_CLIENTE					'I'
#define EXCLUIR_CLIENTE					'E'
#define MOSTRAR_CLIENTE					'M'
#define DEPOSITAR_VALOR					'D'
#define SACAR_VALOR						'S'
#define LISTAR_UM_DADO_HASH				'H'
#define LISTAR_TODOS_CLIENTES			'L'
#define SAIR_DO_PROGRAMA				'X'
//
//	struct para a chave de busca na lista ligada
//
typedef struct tagCHAVE_BUSCA
{
	char cAgCodigo[11],					// c�digo da agencia e codigo
		cAtivo;							// cliente ativo = 'A' e inativo ou excluido = 'I'
	int nPosicional;					// posicional do cliente no cadastro
	tagCHAVE_BUSCA *ptrProxima;			// ponteiro para a pr�xima chave de busca
} CHAVE_BUSCA;
//
// struct do hash da lista ligada
//
typedef struct tagHASH_CODE
{
	CHAVE_BUSCA *ptrPrimeira,			// ponteiro para a primeira chave da lista
		*ptrUltima;						// inser��es sempre na �ltima da lista
} HASH_CODE;
//
// struct do cadastro de clientes
//
typedef struct tagCLIENTE
{
	char cAgCodigo[11],					// c�digo da agencia e codigo
		cAtivo,							// cliente ativo = 'A' e inativo ou excluido = 'I'
										// 'F' - fim do arquivo l�gico
		cNomeCliente[41];				// nome do cliente
	double dSaldoCliente;				// saldo do cliente
} CLIENTE;
//
// classe agencia banc�ria
//
class clAgencia
{
	// atributos private da classe
private:
	HASH_CODE vetHashTable[HASH_MAX];	// HASH TABLE com um vetor de hash code
	int nPosProximo;					// posicional do pr�ximo cliente a ser inserido no cadastro
	CLIENTE stCliente;					// struct para conter os dados de um cliente
	FILE *fdCadastro;					// file descriptor do cadastro

	// m�todos private
	//	Par�metros:
	//		Entrada: char *ptrCodigo = ponteiro para o primeiro byte do string que
	//									cont�m o c�digo do cliente
	//		Retorno: int - valor do hash code
	int CalcularHash(char *ptrCodigo)
	{
		int nSomatoria = 0,						// somat�ria do peso * digito ASCII
			i,									// indexador e contador
			nPesoInicial = 51;					// peso inicial
		// loop de c�lculo
		for(i = 0; i < strlen(ptrCodigo); i++, nPesoInicial--)	
		{
			nSomatoria += *(ptrCodigo + i) * nPesoInicial;
		}
		return nSomatoria % HASH_MAX;			// retorna o Hash Code
	}
	// M�todo private que insere uma chave de busca no Hash Table
	//	Par�metros:
	//		Entrada: int nHash - hash code do c�digo
	//				 char *ptrCodigo - ponteiro do string que cont�m o c�digo
	//				 int nPosicional - posicional do cliente no disco (cadastro)
	//		Retorno: bool - true - tudo OK e false - n�o tem mem�ria para a 
	//						insers�o no Hash table
	bool InserirChaveDeBusca(int nHash, char *ptrCodigo, int nPosicional)
	{
		if(vetHashTable[nHash].ptrPrimeira == NULL)			// lista vazia?
			vetHashTable[nHash].ptrUltima =
			vetHashTable[nHash].ptrPrimeira = new CHAVE_BUSCA; // mem�ria para nova chave da lista
		else		// n�o � a primeira chave da lista
			vetHashTable[nHash].ptrUltima = 
			vetHashTable[nHash].ptrUltima->ptrProxima = new CHAVE_BUSCA; // aloca mem�ria
		// testar se tem mem�ria
		if(vetHashTable[nHash].ptrUltima == NULL)
			return false;									// indica que n�o tem mem�ria
		// preencher a chave de busca com os dados
		vetHashTable[nHash].ptrUltima->cAtivo = 'A';		// indica cliente ativo
		vetHashTable[nHash].ptrUltima->nPosicional = nPosicional; // posi��o no disco
		strcpy_s(vetHashTable[nHash].ptrUltima->cAgCodigo, ptrCodigo);
		vetHashTable[nHash].ptrUltima->ptrProxima = NULL;		// indica que � o �ltimo da lista
		return true;
	}
	// M�todo private que l� um cliente em modo posicional
	//	Par�metros:
	//		Entrada: int nPosicao - posicional do cliente dentro do arquivo
	//				 CLIENTE *ptrStCliente - ponteiro da struct que receber� os dados do
	//										cliente
	//		Retorno: bool - true - leitura OK
	//						false - erro de seek ou de leitura
	bool LerClientePosicional(int nPosicao, CLIENTE *ptrStCliente)
	{
		if(fseek(fdCadastro, nPosicao * sizeof(CLIENTE), SEEK_SET) != 0)	// erro de seek?
			return false;								// retorna em condi��o de erro
		if(fread_s(ptrStCliente, sizeof(CLIENTE), sizeof(CLIENTE), 1, fdCadastro) == 0) // erro?
			return false;
		return true;									// avisa que foi tudo OK
	}
	// M�todo private que grava um cliente no cadastro de forma posicional
	//	Par�metros:
	//		Entrada: int nPosicao - posicional do cliente dentro do cadastro
	//				 CLIENTE *ptrStCliente - ponteiro para os dados do cliente a ser
	//										gravado
	//		Retorno: bool - true - grava��o OK
	//						false - erro de grava��o ou de seek
	bool GravarClientePosicional(int nPosicao, CLIENTE *ptrStCliente)
	{
		if(fseek(fdCadastro, nPosicao * sizeof(CLIENTE), SEEK_SET) != 0)	// erro de seek?
			return false;								// retorna em condi��o de erro
		if(fwrite(ptrStCliente, sizeof(CLIENTE), 1, fdCadastro) == 0)		// erro de grava��o?
			return false;
		return true;								// grava��o OK
	}
	// m�todos p�blicos da classe
public:
	// m�todo construtor
	//	Par�metros:
	//		Entrada: bool *ptrStatus - ponteiro de uma bool que reber� os status da
	//									constru��o da ag�ncia banc�ria
	//									true - tudo OK
	//									false - problema na constru��o
	clAgencia(bool *ptrStatus)
	{
		int i;							// indexador e contador gen�rico
		nPosProximo = 0;				// posicional do pr�ximo cliente a ser inserido
		for(i = 0; i < HASH_MAX; i++)	// loop para inicializar o hash table
			vetHashTable[i].ptrPrimeira = NULL; // todas as listas de chaves est�o vazias
		// vamos remontar o hash table em mem�ria
		// se for a primeira vez que o programa ser� executado iremos
		// "formatar" o cadastro de clientes
		//	abrir o arquivo em r+b = leitura e grava��o e o arquivo precisa existir
		if(fopen_s(&fdCadastro, CAMINHO_CADASTRO, "r+b") != 0) // erro de abertura?
		{	// o arquivo n�o foi encontrado - n�o existe
			// abrir o arquivo em modo w+b - grava��o e leitura e ser� destruido se existir
			if(fopen_s(&fdCadastro, CAMINHO_CADASTRO, "w+b") != 0) // erro de abertura?
			{	// n�o conseguiu abrir o arquivo em modo grava��o e leitura
				cout << "Erro de abertura do cadastro: " << CAMINHO_CADASTRO << endl;
				PAUSA;
				*ptrStatus = false;						// problema no construtor
				return;									// cai fora do construtor
			}
			// abriu com sucesso - loop de grava��o de registros vazios com cAtivo = 'F'
			for(i = 0; i < QTDE_MAX_CLIENTES; i++)
			{
				stCliente.cAtivo = 'F';					// indica vazio
				stCliente.cAgCodigo[0] = NULL;			// c�digo vazio
				stCliente.cNomeCliente[0] = NULL;		// nome vazio
				stCliente.dSaldoCliente = 0.0;			// saldo zero
				// gravar esse cliente vazio em modo sequencial
				if(fwrite(&stCliente, sizeof(CLIENTE), 1, fdCadastro) == 0) // erro de grava��o?
				{
					fclose(fdCadastro);					// fechar o arquivo
					cout << "Erro de grava��o no cadastro!" << endl;
					*ptrStatus = false;					// indica que tem erro na constru��o
					PAUSA;
					return;								// cai fora do construtor
				}
			} // for i
			// em condi��o de teste criar clientes random
#ifdef TESTE
			srand(300);									// semente para n�meros rand�micos
			// loop de cria��o de c�digos de clientes para teste
			for(i = 0; i < QTDE_MAX_CLIENTES * 50 / 100; i++)
			{
				_itoa_s(rand(), stCliente.cAgCodigo, 11, 10); // converte para string uma int random
				// verificar se este c�digo j� est� cadastrado
				if(VerificaSeClienteExiste(stCliente.cAgCodigo, &stCliente)) // j� existe?
				{	// cliente j� existe vamos sortear outro
					i--;								// para conseguir sortear a qtde desejada
					continue;							// continua no for
				}
				sprintf_s(stCliente.cNomeCliente, 41, "Cliente de codigo %s", stCliente.cAgCodigo);
				stCliente.dSaldoCliente = rand() * 1.456;	// saldo
				if(!InserirCliente(&stCliente))			// erro na inser��o de cliente de teste?
				{	// erro na inser��o do cliente 
					fclose(fdCadastro);					// fechar o arquivo
					cout << "Erro na inser��o de cliente em teste!" << endl;
					*ptrStatus = false;					// avisa o erro
					PAUSA;
					return;								// cai fora do construtor
				}
			} // for i
#endif
		} //arquivo n�o existe
		else
		{	// o arquivo j� existe - leitura sequencial de cada cliente
			// verificar se est� ativo - sen�o ler o pr�ximo
			// calcular o hash e inserir a chave de busca no hash table correspondente
			while(true)								// loop infinito
			{
				if(fread_s(&stCliente, sizeof(CLIENTE), 
					sizeof(CLIENTE), 1, fdCadastro) == 0)		// erro de leitura?
				{	// erro de leitura
					fclose(fdCadastro);							// fechar o arquivo
					*ptrStatus = false;							// avisa o erro
					cout << "Erro de leitura na constru��o!" << endl;
					PAUSA;
					return;										// sai do construtor
				}
				// lido com sucesso
				if(stCliente.cAtivo == 'I')						// cliente inativo?
				{	// considerar que ele ocupa uma posi��o dentro do disco
					nPosProximo++;								// considera sua posi��o
					continue;									// vai ler o pr�ximo
				}
				if(stCliente.cAtivo == 'F')						// fim l�gico do arquivo?
					break;										// cai fora do while
				// cliente ativo - calcular o seu hash code
				if(!InserirChaveDeBusca(CalcularHash(stCliente.cAgCodigo),
					stCliente.cAgCodigo, nPosProximo))			// n�o tem mem�ria?
				{
					fclose(fdCadastro);							// fechar o arquivo
					*ptrStatus = false;							// avisa o problema
					cout << "N�o tem mem�ria dispon�vel!" << endl;
					PAUSA;
					return;										// cai fora do construtor
				}
				nPosProximo++;									// incrementa para o pr�ximo
			} // while
		} // arquivo existe
		*ptrStatus = true;									// foi tudo bem
	} // construtor
	// M�todo p�blico que verifica se o cliente j� est� cadastrado
	//	Par�metros:
	//		Entrada: char *ptrCodigo - ponteiro para o string que cont�m o c�digo do cliente
	//				 CLIENTE *ptrStCliente - ponteiro de uma struct que ir� receber
	//										os dados do cliente se ele j� existir
	//		Retorno: true - o cliente j� est� cadastrado e seus dados est�o
	//						na struct passada pelo invocador do m�todo
	//				 false - o cliente n�o existe
	bool VerificaSeClienteExiste(char *ptrCodigo, CLIENTE *ptrStCliente)
	{
		CHAVE_BUSCA *ptrCorrente;							// chave de busca corrente
		int nHash = CalcularHash(ptrCodigo);				// calcular o hash
		// buscar o cliente no hash table
		for(ptrCorrente = vetHashTable[nHash].ptrPrimeira;
			ptrCorrente;									// se null indica o fim da lista
			ptrCorrente = ptrCorrente->ptrProxima)			// aponta para a pr�xima chave
		{
			if(ptrCorrente->cAtivo != 'A')					// cliente excluido?
				continue;									// continua no for
			if(strcmp(ptrCodigo, ptrCorrente->cAgCodigo) == 0)	// encontrou o cliente?
			{	// vamos ler o cliente para a struct do invocador do m�todo - posicional
				if(!LerClientePosicional(ptrCorrente->nPosicional, ptrStCliente))
					return false;							// como se n�o existisse
				return true;								// indica que o cliente existe
			}
		} // for
		return false;										// cliente n�o existe
	}
	// M�todo p�blico que insere um cliente no cadastro e sua chave de busca
	//		no hash table
	//	Par�metros:
	//		Entrada: CLIENTE *ptrStCliente - ponteiro da struct que cont�m os dados do 
	//										cliente
	//		Retorno: bool - true - inser��o OK
	//						false - problema na inser��o
	bool InserirCliente(CLIENTE *ptrStCliente)		
	{
		int nHash = CalcularHash(ptrStCliente->cAgCodigo);		// hash deste cliente
		ptrStCliente->cAtivo = 'A';								// cliente ativo
		if(!GravarClientePosicional(nPosProximo, ptrStCliente)) // erro de grava��o?
			return false;										// indica erro
		if(!InserirChaveDeBusca(nHash, ptrStCliente->cAgCodigo, nPosProximo)) // erro inser��o
			return false;
		nPosProximo++;											// indica a posi��o do pr�ximo
		return true;											// indica tudo OK
	}

	// M�todo p�blico que fecha o cadastro de clientes
	void FecharCadastro(void)
	{
		fclose(fdCadastro);									// fechar o cadastro
	}

	// M�todo p�blico que lista os clientes de um dado hash code
	//	Par�metros:
	//		Entrada: int nHash - hash code informado
	//		Retorno: bool - true - tem clientes neste hash e foram listados
	//						false - n�o tem clientes neste hash
	bool ListarClientesPorUmDadoHash(int nHash)
	{
		int nQtdeClientes = 0,							// qtde de clientes neste hash code
			nContaPorLinha = 0;							// contagem por linha
		CHAVE_BUSCA *ptrCorrente;						// ponteiro para o cliente corrente
		if(vetHashTable[nHash].ptrPrimeira == NULL)		// lista vazia?
			return false;								// n�o tem clientes neste hash
		// varrer a lista ligada deste hash code
		for(ptrCorrente = vetHashTable[nHash].ptrPrimeira;
			ptrCorrente;								// se NULL - fim da lista
			ptrCorrente = ptrCorrente->ptrProxima)		// aponta para o pr�ximo da lista
		{
			if(nContaPorLinha >= 8)
			{
				nContaPorLinha = 1;						// inicia para proxima linha
				cout << endl;							// pula para a proxima linha
			}
			else
			{	
				nContaPorLinha++;						// conta mais um por linha
			}
			cout << ptrCorrente->cAgCodigo << "\t";
			nQtdeClientes++;
		} // for
		// todos os c�digos foram listados
		cout << endl << "Hash: " << nHash << " Qtde: " << nQtdeClientes << endl;
	}
};







