// Declarações do programa Agência Bancária com Hash e Cadastro de Clientes
// Condição para teste do programa
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
// opções do menu do operador
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
	char cAgCodigo[11],					// código da agencia e codigo
		cAtivo;							// cliente ativo = 'A' e inativo ou excluido = 'I'
	int nPosicional;					// posicional do cliente no cadastro
	tagCHAVE_BUSCA *ptrProxima;			// ponteiro para a próxima chave de busca
} CHAVE_BUSCA;
//
// struct do hash da lista ligada
//
typedef struct tagHASH_CODE
{
	CHAVE_BUSCA *ptrPrimeira,			// ponteiro para a primeira chave da lista
		*ptrUltima;						// inserções sempre na última da lista
} HASH_CODE;
//
// struct do cadastro de clientes
//
typedef struct tagCLIENTE
{
	char cAgCodigo[11],					// código da agencia e codigo
		cAtivo,							// cliente ativo = 'A' e inativo ou excluido = 'I'
										// 'F' - fim do arquivo lógico
		cNomeCliente[41];				// nome do cliente
	double dSaldoCliente;				// saldo do cliente
} CLIENTE;
//
// classe agencia bancária
//
class clAgencia
{
	// atributos private da classe
private:
	HASH_CODE vetHashTable[HASH_MAX];	// HASH TABLE com um vetor de hash code
	int nPosProximo;					// posicional do próximo cliente a ser inserido no cadastro
	CLIENTE stCliente;					// struct para conter os dados de um cliente
	FILE *fdCadastro;					// file descriptor do cadastro

	// métodos private
	//	Parâmetros:
	//		Entrada: char *ptrCodigo = ponteiro para o primeiro byte do string que
	//									contém o código do cliente
	//		Retorno: int - valor do hash code
	int CalcularHash(char *ptrCodigo)
	{
		int nSomatoria = 0,						// somatória do peso * digito ASCII
			i,									// indexador e contador
			nPesoInicial = 51;					// peso inicial
		// loop de cálculo
		for(i = 0; i < strlen(ptrCodigo); i++, nPesoInicial--)	
		{
			nSomatoria += *(ptrCodigo + i) * nPesoInicial;
		}
		return nSomatoria % HASH_MAX;			// retorna o Hash Code
	}
	// Método private que insere uma chave de busca no Hash Table
	//	Parâmetros:
	//		Entrada: int nHash - hash code do código
	//				 char *ptrCodigo - ponteiro do string que contém o código
	//				 int nPosicional - posicional do cliente no disco (cadastro)
	//		Retorno: bool - true - tudo OK e false - não tem memória para a 
	//						insersão no Hash table
	bool InserirChaveDeBusca(int nHash, char *ptrCodigo, int nPosicional)
	{
		if(vetHashTable[nHash].ptrPrimeira == NULL)			// lista vazia?
			vetHashTable[nHash].ptrUltima =
			vetHashTable[nHash].ptrPrimeira = new CHAVE_BUSCA; // memória para nova chave da lista
		else		// não é a primeira chave da lista
			vetHashTable[nHash].ptrUltima = 
			vetHashTable[nHash].ptrUltima->ptrProxima = new CHAVE_BUSCA; // aloca memória
		// testar se tem memória
		if(vetHashTable[nHash].ptrUltima == NULL)
			return false;									// indica que não tem memória
		// preencher a chave de busca com os dados
		vetHashTable[nHash].ptrUltima->cAtivo = 'A';		// indica cliente ativo
		vetHashTable[nHash].ptrUltima->nPosicional = nPosicional; // posição no disco
		strcpy_s(vetHashTable[nHash].ptrUltima->cAgCodigo, ptrCodigo);
		vetHashTable[nHash].ptrUltima->ptrProxima = NULL;		// indica que é o último da lista
		return true;
	}
	// Método private que lê um cliente em modo posicional
	//	Parâmetros:
	//		Entrada: int nPosicao - posicional do cliente dentro do arquivo
	//				 CLIENTE *ptrStCliente - ponteiro da struct que receberá os dados do
	//										cliente
	//		Retorno: bool - true - leitura OK
	//						false - erro de seek ou de leitura
	bool LerClientePosicional(int nPosicao, CLIENTE *ptrStCliente)
	{
		if(fseek(fdCadastro, nPosicao * sizeof(CLIENTE), SEEK_SET) != 0)	// erro de seek?
			return false;								// retorna em condição de erro
		if(fread_s(ptrStCliente, sizeof(CLIENTE), sizeof(CLIENTE), 1, fdCadastro) == 0) // erro?
			return false;
		return true;									// avisa que foi tudo OK
	}
	// Método private que grava um cliente no cadastro de forma posicional
	//	Parâmetros:
	//		Entrada: int nPosicao - posicional do cliente dentro do cadastro
	//				 CLIENTE *ptrStCliente - ponteiro para os dados do cliente a ser
	//										gravado
	//		Retorno: bool - true - gravação OK
	//						false - erro de gravação ou de seek
	bool GravarClientePosicional(int nPosicao, CLIENTE *ptrStCliente)
	{
		if(fseek(fdCadastro, nPosicao * sizeof(CLIENTE), SEEK_SET) != 0)	// erro de seek?
			return false;								// retorna em condição de erro
		if(fwrite(ptrStCliente, sizeof(CLIENTE), 1, fdCadastro) == 0)		// erro de gravação?
			return false;
		return true;								// gravação OK
	}
	// métodos públicos da classe
public:
	// método construtor
	//	Parâmetros:
	//		Entrada: bool *ptrStatus - ponteiro de uma bool que reberá os status da
	//									construção da agência bancária
	//									true - tudo OK
	//									false - problema na construção
	clAgencia(bool *ptrStatus)
	{
		int i;							// indexador e contador genérico
		nPosProximo = 0;				// posicional do próximo cliente a ser inserido
		for(i = 0; i < HASH_MAX; i++)	// loop para inicializar o hash table
			vetHashTable[i].ptrPrimeira = NULL; // todas as listas de chaves estão vazias
		// vamos remontar o hash table em memória
		// se for a primeira vez que o programa será executado iremos
		// "formatar" o cadastro de clientes
		//	abrir o arquivo em r+b = leitura e gravação e o arquivo precisa existir
		if(fopen_s(&fdCadastro, CAMINHO_CADASTRO, "r+b") != 0) // erro de abertura?
		{	// o arquivo não foi encontrado - não existe
			// abrir o arquivo em modo w+b - gravação e leitura e será destruido se existir
			if(fopen_s(&fdCadastro, CAMINHO_CADASTRO, "w+b") != 0) // erro de abertura?
			{	// não conseguiu abrir o arquivo em modo gravação e leitura
				cout << "Erro de abertura do cadastro: " << CAMINHO_CADASTRO << endl;
				PAUSA;
				*ptrStatus = false;						// problema no construtor
				return;									// cai fora do construtor
			}
			// abriu com sucesso - loop de gravação de registros vazios com cAtivo = 'F'
			for(i = 0; i < QTDE_MAX_CLIENTES; i++)
			{
				stCliente.cAtivo = 'F';					// indica vazio
				stCliente.cAgCodigo[0] = NULL;			// código vazio
				stCliente.cNomeCliente[0] = NULL;		// nome vazio
				stCliente.dSaldoCliente = 0.0;			// saldo zero
				// gravar esse cliente vazio em modo sequencial
				if(fwrite(&stCliente, sizeof(CLIENTE), 1, fdCadastro) == 0) // erro de gravação?
				{
					fclose(fdCadastro);					// fechar o arquivo
					cout << "Erro de gravação no cadastro!" << endl;
					*ptrStatus = false;					// indica que tem erro na construção
					PAUSA;
					return;								// cai fora do construtor
				}
			} // for i
			// em condição de teste criar clientes random
#ifdef TESTE
			srand(300);									// semente para números randômicos
			// loop de criação de códigos de clientes para teste
			for(i = 0; i < QTDE_MAX_CLIENTES * 50 / 100; i++)
			{
				_itoa_s(rand(), stCliente.cAgCodigo, 11, 10); // converte para string uma int random
				// verificar se este código já está cadastrado
				if(VerificaSeClienteExiste(stCliente.cAgCodigo, &stCliente)) // já existe?
				{	// cliente já existe vamos sortear outro
					i--;								// para conseguir sortear a qtde desejada
					continue;							// continua no for
				}
				sprintf_s(stCliente.cNomeCliente, 41, "Cliente de codigo %s", stCliente.cAgCodigo);
				stCliente.dSaldoCliente = rand() * 1.456;	// saldo
				if(!InserirCliente(&stCliente))			// erro na inserção de cliente de teste?
				{	// erro na inserção do cliente 
					fclose(fdCadastro);					// fechar o arquivo
					cout << "Erro na inserção de cliente em teste!" << endl;
					*ptrStatus = false;					// avisa o erro
					PAUSA;
					return;								// cai fora do construtor
				}
			} // for i
#endif
		} //arquivo não existe
		else
		{	// o arquivo já existe - leitura sequencial de cada cliente
			// verificar se está ativo - senão ler o próximo
			// calcular o hash e inserir a chave de busca no hash table correspondente
			while(true)								// loop infinito
			{
				if(fread_s(&stCliente, sizeof(CLIENTE), 
					sizeof(CLIENTE), 1, fdCadastro) == 0)		// erro de leitura?
				{	// erro de leitura
					fclose(fdCadastro);							// fechar o arquivo
					*ptrStatus = false;							// avisa o erro
					cout << "Erro de leitura na construção!" << endl;
					PAUSA;
					return;										// sai do construtor
				}
				// lido com sucesso
				if(stCliente.cAtivo == 'I')						// cliente inativo?
				{	// considerar que ele ocupa uma posição dentro do disco
					nPosProximo++;								// considera sua posição
					continue;									// vai ler o próximo
				}
				if(stCliente.cAtivo == 'F')						// fim lógico do arquivo?
					break;										// cai fora do while
				// cliente ativo - calcular o seu hash code
				if(!InserirChaveDeBusca(CalcularHash(stCliente.cAgCodigo),
					stCliente.cAgCodigo, nPosProximo))			// não tem memória?
				{
					fclose(fdCadastro);							// fechar o arquivo
					*ptrStatus = false;							// avisa o problema
					cout << "Não tem memória disponível!" << endl;
					PAUSA;
					return;										// cai fora do construtor
				}
				nPosProximo++;									// incrementa para o próximo
			} // while
		} // arquivo existe
		*ptrStatus = true;									// foi tudo bem
	} // construtor
	// Método público que verifica se o cliente já está cadastrado
	//	Parâmetros:
	//		Entrada: char *ptrCodigo - ponteiro para o string que contém o código do cliente
	//				 CLIENTE *ptrStCliente - ponteiro de uma struct que irá receber
	//										os dados do cliente se ele já existir
	//		Retorno: true - o cliente já está cadastrado e seus dados estão
	//						na struct passada pelo invocador do método
	//				 false - o cliente não existe
	bool VerificaSeClienteExiste(char *ptrCodigo, CLIENTE *ptrStCliente)
	{
		CHAVE_BUSCA *ptrCorrente;							// chave de busca corrente
		int nHash = CalcularHash(ptrCodigo);				// calcular o hash
		// buscar o cliente no hash table
		for(ptrCorrente = vetHashTable[nHash].ptrPrimeira;
			ptrCorrente;									// se null indica o fim da lista
			ptrCorrente = ptrCorrente->ptrProxima)			// aponta para a próxima chave
		{
			if(ptrCorrente->cAtivo != 'A')					// cliente excluido?
				continue;									// continua no for
			if(strcmp(ptrCodigo, ptrCorrente->cAgCodigo) == 0)	// encontrou o cliente?
			{	// vamos ler o cliente para a struct do invocador do método - posicional
				if(!LerClientePosicional(ptrCorrente->nPosicional, ptrStCliente))
					return false;							// como se não existisse
				return true;								// indica que o cliente existe
			}
		} // for
		return false;										// cliente não existe
	}
	// Método público que insere um cliente no cadastro e sua chave de busca
	//		no hash table
	//	Parâmetros:
	//		Entrada: CLIENTE *ptrStCliente - ponteiro da struct que contém os dados do 
	//										cliente
	//		Retorno: bool - true - inserção OK
	//						false - problema na inserção
	bool InserirCliente(CLIENTE *ptrStCliente)		
	{
		int nHash = CalcularHash(ptrStCliente->cAgCodigo);		// hash deste cliente
		ptrStCliente->cAtivo = 'A';								// cliente ativo
		if(!GravarClientePosicional(nPosProximo, ptrStCliente)) // erro de gravação?
			return false;										// indica erro
		if(!InserirChaveDeBusca(nHash, ptrStCliente->cAgCodigo, nPosProximo)) // erro inserção
			return false;
		nPosProximo++;											// indica a posição do próximo
		return true;											// indica tudo OK
	}

	// Método público que fecha o cadastro de clientes
	void FecharCadastro(void)
	{
		fclose(fdCadastro);									// fechar o cadastro
	}

	// Método público que lista os clientes de um dado hash code
	//	Parâmetros:
	//		Entrada: int nHash - hash code informado
	//		Retorno: bool - true - tem clientes neste hash e foram listados
	//						false - não tem clientes neste hash
	bool ListarClientesPorUmDadoHash(int nHash)
	{
		int nQtdeClientes = 0,							// qtde de clientes neste hash code
			nContaPorLinha = 0;							// contagem por linha
		CHAVE_BUSCA *ptrCorrente;						// ponteiro para o cliente corrente
		if(vetHashTable[nHash].ptrPrimeira == NULL)		// lista vazia?
			return false;								// não tem clientes neste hash
		// varrer a lista ligada deste hash code
		for(ptrCorrente = vetHashTable[nHash].ptrPrimeira;
			ptrCorrente;								// se NULL - fim da lista
			ptrCorrente = ptrCorrente->ptrProxima)		// aponta para o próximo da lista
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
		// todos os códigos foram listados
		cout << endl << "Hash: " << nHash << " Qtde: " << nQtdeClientes << endl;
	}
};







