//Declara��es do Ensaio para a Prova P2
#include <iostream>
#include <Windows.h>
using namespace std;
// Defini��es do programa
#define PAUSA							system("pause")
#define LIMPAR_TELA						system("cls")
#define CAMINHO_CADASTRO				"..\\Alunos.cad"
#define ATIVO							'A'
#define EXCLUIDO						'E'
#define EXTENSAO_NOME					30
// Op��es do menu
#define CADASTRAR_ALUNO					'C'
#define EXCLUIR_ALUNO					'E'
#define MOSTRAR_ALUNO					'M'
#define SAIR_DO_PROGRAMA				'S'
// Dados para o Hashing
#define QTDE_HASH						300
// struct do Aluno
typedef struct tagALUNO
{
	char cRA[13],						// c�digo do aluno
		cAtivo,							// 'A' - ativo e 'E' - excluido
		szNome[EXTENSAO_NOME + 1];		// nome do aluno
	double dMensalidade;				// mensalidade do aluno
} ALUNO;
// struct com a chave de busca do aluno no cadastro
typedef struct tagCHAVE
{
	char cRA[13],						// c�digo do aluno - chave de busca
		cAtivo;							// se aluno ativo ou excluido
	int nPosicional;					// posi��o do aluno dentro do cadastro
	tagCHAVE *ptrProxima;				// ponteiro para a pr�xima chave dentro da lista ligada
} CHAVE;
// struct para o Hash Code
typedef struct tagHASH
{
	CHAVE *ptrPrimeira,					// ponteiro para primeira chave da lista
		*ptrUltima;						// ponteiro para a ultima chave da lista
} HASH;		
// classe aluno
class clAluno
{
private:
	// atributos private
	HASH vetHash[QTDE_HASH];			// hash table
	int nPosProximo;					// posicional do pr�ximo aluno no cadastro
	FILE *fdCadastro;					// file descriptor do cadastro
	ALUNO stAluno;						// struct para conter os dados de um aluno
	// m�todos private
	// M�todo que calcula o hash code 
	//	Par�metros:
	//		Entrada: char *ptrRA - ponteiro para um string que cont�m o c�digo do aluno
	//		Retorno - int - hash code do c�digo do aluno
	int CalcularHash(char *ptrRA)
	{
		int i,							// indice e contador
			nSomatoria = 0,				// somat�ria do ascii digito * peso
			nPesoInicial = 37;			// indice zero * 37, indice 1 * 36 ....somatoria
		// looping para multiplicar o peso pelo char e fazer a somat�ria
		for(i = 0; i < strlen(ptrRA) ; i++, nPesoInicial--)
			nSomatoria += *(ptrRA + i) * nPesoInicial;
		return (nSomatoria % QTDE_HASH);	// devolve o Hash
	}
	// M�todo que insere uma chave de busca na lista ligada do hash code correspondente
	//	Par�metros:
	//		Entrada: int nHash - hash code calculado
	//				 int nPosicional - posicional do registro do cadastro de alunos
	//				 char *ptrRA - ponteiro do string que cont�m o c�digo do aluno
	//		Retorno: bool - true - inser��o OK
	//						false - n�o tem mem�ria para o new CHAVE
	bool InsereChaveNaListaDoHash(int nHash, int nPosicional, char *ptrRA)
	{
		if(vetHash[nHash].ptrPrimeira == NULL)			// primeira chave da lista?
			vetHash[nHash].ptrUltima =
			vetHash[nHash].ptrPrimeira = new CHAVE;		// aloca mem�ria para chave de busca
		else											// liga a new chave na �ltima chave
			vetHash[nHash].ptrUltima =
			vetHash[nHash].ptrUltima->ptrProxima = new CHAVE; // liga a new na �ltima chave
		// tem mem�ria?
		if(vetHash[nHash].ptrUltima == NULL)			// sem mem�ria?
			return false;								// indica o erro
		// o new foi sucesso
		vetHash[nHash].ptrUltima->cAtivo = ATIVO;		// aluno ativo
		vetHash[nHash].ptrUltima->nPosicional = nPosicional; // posicional do cadastro
		vetHash[nHash].ptrUltima->ptrProxima = NULL;	// indica o fim da lista
		strcpy_s(vetHash[nHash].ptrUltima->cRA, 12, ptrRA); // copia a chave
		return true;									// indica tudo OK
	}
	//	M�todo para ler um aluno de forma posicional
	//		Par�metros:
	//			Entrada: int nPosicional - posicional do aluno
	//					 ALUNO *ptrStAluno - ponteiro da struct para receber a leitura
	//			Retorno: bool - true - leitura OK
	//							false - houve problema de seek ou de leitura
	bool LerAlunoPosicional(int nPosicional, ALUNO *ptrStAluno)
	{
	}
	//	M�todo para gravar um aluno de forma posicional
	//		Par�metros:
	//			Entrada: int nPosicional - posicional do aluno
	//					 ALUNO *ptrStAluno - ponteiro da struct que cont�m os dados
	//										do aluno a serem gravados
	//			Retorno: bool - true - grava��o OK
	//							false - houve problema de seek ou de grava��o
	bool GravarAlunoPosicional(int nPosicional, ALUNO *ptrStAluno)
	{
	}
public:
	// construtor da classe
	// Par�metros:
	//	Entrada: bool *ptrStatus - endere�o do instanciador da classe para receber os
	//								status da constru��o: true - tudo OK e false - houve problema
	clAluno(bool *ptrStatus)
	{
		int i;							// indice e contador
		nPosProximo = 0;				// indice inicial do pr�ximo
		for(i = 0; i < QTDE_HASH; i++)	// loop de inicializa��o do hash table
			vetHash[i].ptrPrimeira = NULL; // todos os hash code com lista vazia
		// abrir o arquivo de cadastro de aluno 
		if(fopen_s(&fdCadastro, CAMINHO_CADASTRO, "r+b") != 0) // o arquivo n�o existe?
		{ 
			if(fopen_s(&fdCadastro, CAMINHO_CADASTRO, "w+b") != 0) // erro irrecuper�vel
			{
				cout << "Erro irrecuper�vel na abertura do arquivo!" << endl;
				*ptrStatus = false;									// avisa o erro
				PAUSA;
				return;									// cai fora do construtor
			}
		} // arquivo n�o existe
		else
		{	// o cadastro j� existe
			while(true)
			{
				if(fread_s(&stAluno, sizeof(ALUNO), sizeof(ALUNO), 1, fdCadastro) == 0) // fim?
				{
					*ptrStatus = true;					// avisa tudo OK
					return;								// cai fora do construtor
				}
				// foi lido um aluno - verificar se ativo
				if(stAluno.cAtivo != ATIVO)				// aluno n�o ativo?
				{
					nPosProximo++;						// incrementar para o proximo posicional
					continue;							// vai ler o pr�ximo
				}
				// aluno ativo
				// calcular o hash 
				// inserir a chave na lista ligada do hash code correspondente
				// incrementar para o pr�ximo
				// continuar no pr�ximo
				if(!InsereChaveNaListaDoHash(CalcularHash(stAluno.cRA), nPosProximo, 
					stAluno.cRA))						// erro? N�o tem mem�ria
				{
					*ptrStatus = false;					// indica o erro
					return;								// cai fora do construtor
				}
				nPosProximo++;							// incrementa para o pr�ximo posicional
			} // while
		} // cadastro existe
		*ptrStatus = true;								// indica que constru��o OK
	} // construtor
	// M�todo que verifica se o aluno j� est� cadastrado e ativo
	//	Se estiver cadastrado o m�todo vai copiar os dados do aluno na struct do
	//		invocador do m�todo
	//	Par�metros:
	//		Entrada: char *ptrRA - ponteiro do string que cont�m o c�digo do aluno
	//				 ALUNO *ptrStAluno - ponteiro de uma struct do invocador do 
	//									m�todo para receber os dados do aluno se j� cadastrado
	//		Retorno: bool - true - aluno j� cadastrado e seus dados informados
	//						false - aluno n�o cadastrado
	bool VerificaSeAlunoExiste(char *ptrRA, ALUNO *ptrStAluno)
	{
	}
	// M�todo que cadastra um aluno novo
	// Par�metros:
	//	Entrada: ALUNO *ptrStAluno - ponteiro de uma struct que � passada com os dados do
	//								aluno a ser cadastrado
	//	Retorno: bool - true - cadastramento OK
	//					false - houve problema no cadastramento
	bool CadastrarAluno(ALUNO *ptrStAluno)
	{
		// 1. grava posicional a struct do aluno
		// 2. calcular o hash e inserir a chave na lista ligada do hash correspondente
		// 3. incrementar o posicional
	}
	// M�todo que fecha o cadastro de aluno
	void FecharCadastro(void)
	{
		fclose(fdCadastro);
	}
}; // fim da classe aluno







