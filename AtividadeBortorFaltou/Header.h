//Declarações do Ensaio para a Prova P2
#include <iostream>
#include <Windows.h>
using namespace std;
// Definições do programa
#define PAUSA							system("pause")
#define LIMPAR_TELA						system("cls")
#define CAMINHO_CADASTRO				"..\\Alunos.cad"
#define ATIVO							'A'
#define EXCLUIDO						'E'
#define EXTENSAO_NOME					30
// Opções do menu
#define CADASTRAR_ALUNO					'C'
#define EXCLUIR_ALUNO					'E'
#define MOSTRAR_ALUNO					'M'
#define SAIR_DO_PROGRAMA				'S'
// Dados para o Hashing
#define QTDE_HASH						300
// struct do Aluno
typedef struct tagALUNO
{
	char cRA[13],						// código do aluno
		cAtivo,							// 'A' - ativo e 'E' - excluido
		szNome[EXTENSAO_NOME + 1];		// nome do aluno
	double dMensalidade;				// mensalidade do aluno
} ALUNO;
// struct com a chave de busca do aluno no cadastro
typedef struct tagCHAVE
{
	char cRA[13],						// código do aluno - chave de busca
		cAtivo;							// se aluno ativo ou excluido
	int nPosicional;					// posição do aluno dentro do cadastro
	tagCHAVE *ptrProxima;				// ponteiro para a próxima chave dentro da lista ligada
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
	int nPosProximo;					// posicional do próximo aluno no cadastro
	FILE *fdCadastro;					// file descriptor do cadastro
	ALUNO stAluno;						// struct para conter os dados de um aluno
	// métodos private
	// Método que calcula o hash code 
	//	Parâmetros:
	//		Entrada: char *ptrRA - ponteiro para um string que contém o código do aluno
	//		Retorno - int - hash code do código do aluno
	int CalcularHash(char *ptrRA)
	{
		int i,							// indice e contador
			nSomatoria = 0,				// somatória do ascii digito * peso
			nPesoInicial = 37;			// indice zero * 37, indice 1 * 36 ....somatoria
		// looping para multiplicar o peso pelo char e fazer a somatória
		for(i = 0; i < strlen(ptrRA) ; i++, nPesoInicial--)
			nSomatoria += *(ptrRA + i) * nPesoInicial;
		return (nSomatoria % QTDE_HASH);	// devolve o Hash
	}
	// Método que insere uma chave de busca na lista ligada do hash code correspondente
	//	Parâmetros:
	//		Entrada: int nHash - hash code calculado
	//				 int nPosicional - posicional do registro do cadastro de alunos
	//				 char *ptrRA - ponteiro do string que contém o código do aluno
	//		Retorno: bool - true - inserção OK
	//						false - não tem memória para o new CHAVE
	bool InsereChaveNaListaDoHash(int nHash, int nPosicional, char *ptrRA)
	{
		if(vetHash[nHash].ptrPrimeira == NULL)			// primeira chave da lista?
			vetHash[nHash].ptrUltima =
			vetHash[nHash].ptrPrimeira = new CHAVE;		// aloca memória para chave de busca
		else											// liga a new chave na última chave
			vetHash[nHash].ptrUltima =
			vetHash[nHash].ptrUltima->ptrProxima = new CHAVE; // liga a new na última chave
		// tem memória?
		if(vetHash[nHash].ptrUltima == NULL)			// sem memória?
			return false;								// indica o erro
		// o new foi sucesso
		vetHash[nHash].ptrUltima->cAtivo = ATIVO;		// aluno ativo
		vetHash[nHash].ptrUltima->nPosicional = nPosicional; // posicional do cadastro
		vetHash[nHash].ptrUltima->ptrProxima = NULL;	// indica o fim da lista
		strcpy_s(vetHash[nHash].ptrUltima->cRA, 12, ptrRA); // copia a chave
		return true;									// indica tudo OK
	}
	//	Método para ler um aluno de forma posicional
	//		Parâmetros:
	//			Entrada: int nPosicional - posicional do aluno
	//					 ALUNO *ptrStAluno - ponteiro da struct para receber a leitura
	//			Retorno: bool - true - leitura OK
	//							false - houve problema de seek ou de leitura
	bool LerAlunoPosicional(int nPosicional, ALUNO *ptrStAluno)
	{
	}
	//	Método para gravar um aluno de forma posicional
	//		Parâmetros:
	//			Entrada: int nPosicional - posicional do aluno
	//					 ALUNO *ptrStAluno - ponteiro da struct que contém os dados
	//										do aluno a serem gravados
	//			Retorno: bool - true - gravação OK
	//							false - houve problema de seek ou de gravação
	bool GravarAlunoPosicional(int nPosicional, ALUNO *ptrStAluno)
	{
	}
public:
	// construtor da classe
	// Parâmetros:
	//	Entrada: bool *ptrStatus - endereço do instanciador da classe para receber os
	//								status da construção: true - tudo OK e false - houve problema
	clAluno(bool *ptrStatus)
	{
		int i;							// indice e contador
		nPosProximo = 0;				// indice inicial do próximo
		for(i = 0; i < QTDE_HASH; i++)	// loop de inicialização do hash table
			vetHash[i].ptrPrimeira = NULL; // todos os hash code com lista vazia
		// abrir o arquivo de cadastro de aluno 
		if(fopen_s(&fdCadastro, CAMINHO_CADASTRO, "r+b") != 0) // o arquivo não existe?
		{ 
			if(fopen_s(&fdCadastro, CAMINHO_CADASTRO, "w+b") != 0) // erro irrecuperável
			{
				cout << "Erro irrecuperável na abertura do arquivo!" << endl;
				*ptrStatus = false;									// avisa o erro
				PAUSA;
				return;									// cai fora do construtor
			}
		} // arquivo não existe
		else
		{	// o cadastro já existe
			while(true)
			{
				if(fread_s(&stAluno, sizeof(ALUNO), sizeof(ALUNO), 1, fdCadastro) == 0) // fim?
				{
					*ptrStatus = true;					// avisa tudo OK
					return;								// cai fora do construtor
				}
				// foi lido um aluno - verificar se ativo
				if(stAluno.cAtivo != ATIVO)				// aluno não ativo?
				{
					nPosProximo++;						// incrementar para o proximo posicional
					continue;							// vai ler o próximo
				}
				// aluno ativo
				// calcular o hash 
				// inserir a chave na lista ligada do hash code correspondente
				// incrementar para o próximo
				// continuar no próximo
				if(!InsereChaveNaListaDoHash(CalcularHash(stAluno.cRA), nPosProximo, 
					stAluno.cRA))						// erro? Não tem memória
				{
					*ptrStatus = false;					// indica o erro
					return;								// cai fora do construtor
				}
				nPosProximo++;							// incrementa para o próximo posicional
			} // while
		} // cadastro existe
		*ptrStatus = true;								// indica que construção OK
	} // construtor
	// Método que verifica se o aluno já está cadastrado e ativo
	//	Se estiver cadastrado o método vai copiar os dados do aluno na struct do
	//		invocador do método
	//	Parâmetros:
	//		Entrada: char *ptrRA - ponteiro do string que contém o código do aluno
	//				 ALUNO *ptrStAluno - ponteiro de uma struct do invocador do 
	//									método para receber os dados do aluno se já cadastrado
	//		Retorno: bool - true - aluno já cadastrado e seus dados informados
	//						false - aluno não cadastrado
	bool VerificaSeAlunoExiste(char *ptrRA, ALUNO *ptrStAluno)
	{
	}
	// Método que cadastra um aluno novo
	// Parâmetros:
	//	Entrada: ALUNO *ptrStAluno - ponteiro de uma struct que é passada com os dados do
	//								aluno a ser cadastrado
	//	Retorno: bool - true - cadastramento OK
	//					false - houve problema no cadastramento
	bool CadastrarAluno(ALUNO *ptrStAluno)
	{
		// 1. grava posicional a struct do aluno
		// 2. calcular o hash e inserir a chave na lista ligada do hash correspondente
		// 3. incrementar o posicional
	}
	// Método que fecha o cadastro de aluno
	void FecharCadastro(void)
	{
		fclose(fdCadastro);
	}
}; // fim da classe aluno







