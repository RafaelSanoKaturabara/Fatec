// Declarações e classe da lista ligada simples
#include <iostream>
#include <Windows.h>
using namespace std;
// defines
#define PAUSA								system("pause")
#define LIMPAR_TELA							system("cls")
#define PAIS_BRASIL							setlocale(LC_ALL, "portuguese_brazil")
// opções do menu
#define INCLUIR_ALUNO						'I'
#define EXCLUIR_ALUNO						'E'
#define LISTAR_ALUNOS						'L'
#define MOSTRAR_ALUNO						'M'
#define CLASSIFICAR_ALUNOS					'C'
#define SAIR_DO_PROGRAMA					'S'
// struct do aluno
typedef struct tagALUNO
{
	int nCodAluno;							// codigo do aluno
	char cNomeAluno[41];					// nome do aluno
	double dMensalidade;					// mensalidade do aluno
	tagALUNO *ptrProximo;					// ponteiro para o próximo da lista ligada
}ALUNO;
//
// classe aluno
//
class clAluno
{
	// atributos private da classe
private:
	ALUNO *ptrPrimeiro,						// ponteiro para o primeiro da lista
		*ptrUltimo,							// ponteiro para o último da lista
		*ptrCorrente;						// ponteiro para o aluno sendo visto
	// métodos públicos da classe
public:
	// Método construtor
	clAluno(void)
	{
		ptrPrimeiro = NULL;					// lista vazia
	}
	// Método para inserção de um aluno na lista ligada
	//	Parâmetros:
	//		Entrada: ALUNO *ptrStAluno - endereço de uma struct que contém
	//									os dados do aluno a ser inserido na lista
	//		Retorno - bool - true - inserção foi OK
	//						 false - não tem memória disponível para a inserção
	bool InsercaoDeAluno(ALUNO *ptrStAluno)
	{
		ALUNO *ptrAnterior,
			*ptrWork;						// ponteiro de trabalho para aluno
		if(ptrPrimeiro == NULL)				// inserção no primeiro da lista?
		{
			ptrUltimo = ptrPrimeiro = new ALUNO; // inserção do primeiro e último
			memcpy_s(ptrUltimo, sizeof(ALUNO), ptrStAluno, sizeof(ALUNO)); // copia os dados do aluno
			ptrUltimo->ptrProximo = NULL;	// último da lista
			if(ptrUltimo == NULL)			// não tem memória?
				return false;				// avisa que não tem memória
			return true;					// tudo ok
		}
		ptrWork = new ALUNO;	
		if(ptrWork == NULL)					// não tem memória?
			return false;					// avisa que nao tem memória
		ptrAnterior = NULL;
		// loop de verificação para colocar na ordem correta
		for(ptrCorrente = ptrPrimeiro; ptrCorrente; ptrCorrente = ptrCorrente->ptrProximo)
		{
			if(ptrStAluno->nCodAluno < ptrCorrente->nCodAluno) // Encontrou a posição?
			{
				memcpy_s(ptrWork, sizeof(ALUNO), ptrStAluno, sizeof(ALUNO)); // copia os dados do aluno para ptrWork
				if(ptrAnterior == NULL)		// primeiro?
				{					
					ptrWork->ptrProximo = ptrCorrente;
					ptrPrimeiro = ptrWork;
				}
				else						// posição central?
				{
					ptrAnterior->ptrProximo = ptrWork;
					ptrWork->ptrProximo = ptrCorrente;
				}
				return true;
			}
			
			ptrAnterior = ptrCorrente;
		}	// for
		if(ptrCorrente == NULL)				// Ultímo?
		{
			memcpy_s(ptrWork, sizeof(ALUNO), ptrStAluno, sizeof(ALUNO)); // copia os dados do aluno para ptrWork
			ptrUltimo = ptrAnterior->ptrProximo = ptrWork;
			ptrWork->ptrProximo = NULL;
		}
	}
	// Método que verifica se o aluno já está na lista
	//	Parâmetros:
	//		Entrada: int nCodAluno - código do aluno a ser verificado
	//				 ALUNO *ptrStAluno - endereço de uma struct a receber os dados do
	//									aluno se ele já estiver na lista
	//		Retorno: bool - true - o aluno já está na lista
	//						false - o aluno não está na lista
	bool VerificaSeAlunoExiste(int nCodAluno, ALUNO *ptrStAluno)
	{
		for(ptrCorrente = ptrPrimeiro;			// o corrente se existir é o primeiro da lista
			ptrCorrente;						// se nulo significa fim da lista (false)
			ptrCorrente = ptrCorrente->ptrProximo) // o corrente é o próximo dele mesmo
		{	// temos um aluno no ptrCorrente
			if(ptrCorrente->nCodAluno == nCodAluno) // o aluno está na lista?
			{	// aluno está na lista - copiar os seus dados para o invocador do método
				memcpy_s(ptrStAluno, sizeof(ALUNO), ptrCorrente, sizeof(ALUNO));
				return true;						// indica que existe
			}
		} // for
		return false;								// indica que aluno não está na lista
	}
	// Método público que lista todos o alunos da lista ligada
	void ListarAlunos(void)
	{
		char cWork[200];						// para o sprintf_s
		LIMPAR_TELA;
		cout << "\n\tListagem total dos alunos" << endl;
		sprintf_s(cWork, "Código Nome                           Mensalidade");
		cout << cWork << endl;
		for(ptrCorrente = ptrPrimeiro;			// o corrente se existir é o primeiro da lista
			ptrCorrente;						// se nulo significa fim da lista (false)
			ptrCorrente = ptrCorrente->ptrProximo) // o corrente é o próximo dele mesmo
		{	// temos um aluno no ptrCorrente
			sprintf_s(cWork, "%6d %-40s %8.2f",
				ptrCorrente->nCodAluno, 
				ptrCorrente->cNomeAluno,
				ptrCorrente->dMensalidade);
			cout << cWork << endl;
		} // for
		cout << "\n\tFim da listagem" << endl;
		PAUSA;
	}
	// Método publico que exclui um aluno da lista ligada
	//	Parâmetros:
	//		Entrada: int nCodigo - codigo do aluno a ser excluido
	//		Retorno: bool - true - exclusão ok
	//						false - o aluno não existe
	bool ExcluirAluno(int nCodigo)
	{
		ALUNO *ptrSalva,					// salva u endereço que será perdido
			*ptrAnterior = 0;				// aponta para o próximo aluno
		// loop de busca do aluno a ser excluído
		for(ptrCorrente = ptrPrimeiro; ptrCorrente; ptrCorrente = ptrCorrente->ptrProximo)
		{
			if(nCodigo == ptrCorrente->nCodAluno)		// é o aluno desejado?
			{	// o aluno foi encontrado
				if(ptrAnterior == NULL)		// primeiro da lista
				{	// primeiro da lista
					ptrSalva = ptrPrimeiro->ptrProximo;	// salva quem vai ser o primeiro
					delete ptrPrimeiro;		// libera a memoria do aluno
					ptrPrimeiro = ptrSalva;	// o primeiro da lista é o seguinte ao excluido
				}
				else						// não é o primeiro
				{
					ptrAnterior->ptrProximo = ptrCorrente->ptrProximo;	// link anterior para o próximo
					delete ptrCorrente;
					if(ptrAnterior->ptrProximo == NULL)	// último?
						ptrUltimo = ptrAnterior;		// aponta para quem era o penultimo
				}
				return true;				// exclusão ok
			}	// encontrou o aluno
			// não encontrou o aluno ainda
			ptrAnterior = ptrCorrente;		// o corrente passa a ser anterior
		} // for 
		// não encontrou o aluno
		return false;						// avisa que não encontrou
	}
};






