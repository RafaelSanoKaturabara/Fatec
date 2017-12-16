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
		*ptrCorrente;						// ponteiro para o aluno sendo visto
	// métodos públicos da classe
public:
	// Método construtor
	clAluno(void)
	{
		ptrPrimeiro = NULL;					// lista vazia
	}
	// Método para inserção de um aluno na lista ligada - de forma ordenada
	//	Parâmetros:
	//		Entrada: ALUNO *ptrStAluno - endereço de uma struct que contém
	//									os dados do aluno a ser inserido na lista
	//		Retorno - bool - true - inserção foi OK
	//						 false - não tem memória disponível para a inserção
	bool InsercaoDeAluno(ALUNO *ptrStAluno)
	{
		ALUNO *ptrSalva,					// salva u endereço que será perdido
			*ptrAnterior = 0;				// aponta para o próximo aluno
		if(ptrPrimeiro == NULL)				// inserção no primeiro da lista?
		{
			ptrPrimeiro = new ALUNO;		// inserção do primeiro e último
			if(ptrPrimeiro == NULL)			// testar se tem memória
				return false;				// avisa que não tem memória
			// tem memória do novo aluno
			memcpy_s(ptrPrimeiro, sizeof(ALUNO), ptrStAluno, sizeof(ALUNO));
			ptrPrimeiro->ptrProximo == NULL;	// primeiro e ultimo da lista
			return true;						// avisa que foi tudo ok
		}
		else	// não é o primeiro da lista - vamos procurar o ponto de inserção
		{
			// varrer a lista para encontrar o ponto de inserção
			for(ptrCorrente = ptrPrimeiro; ptrCorrente; ptrCorrente = ptrCorrente->ptrProximo)
			{
				if(ptrStAluno->nCodAluno < ptrCorrente->nCodAluno)	// no ponto de inserção?
				{	// vamos testar se o novo aluno será o primeiro da lista
					if(ptrAnterior == 0)			// não passou pelo primeiro da lista?
					{
						ptrSalva = ptrPrimeiro;		// salva o ponteiro do atual primeiro da lista
						ptrPrimeiro = new ALUNO;	// aloca um espaço de memória para o aluno
						if(ptrPrimeiro == NULL)		// não tem memória?
						{
							ptrPrimeiro = ptrSalva;	// restaura a lista ligada
							return false;
						}
						// tem memória
						memcpy_s(ptrPrimeiro, sizeof(ALUNO), ptrStAluno, sizeof(ALUNO));
						ptrPrimeiro->ptrProximo = ptrSalva;	// aponta para o aluno que era o primeiro
						return true;				// indica tudo ok
					}	// inserção como o primeiro da lista
					else
					{	// o ponto de inserção é após o primeiro
						ptrSalva = ptrAnterior->ptrProximo;
						ptrAnterior->ptrProximo = new ALUNO;	// aloca memória
						if(ptrAnterior->ptrProximo == NULL)		// sem memória?
						{
							ptrAnterior->ptrProximo = ptrSalva;	// restaura a lista
							return false;			// avisa o erro
						}
						// tem memória
						memcpy_s(ptrAnterior->ptrProximo, sizeof(ALUNO), ptrStAluno, sizeof(ALUNO));
						ptrAnterior->ptrProximo->ptrProximo = ptrSalva;
						return true;
					}
				}
				// o código do novo aluno é maior que o código do aluno corrente
				// testar se o corrente é o ultimo
				if(ptrCorrente->ptrProximo == NULL)	// último aluno?
				{	// inserir o novo aluno sobre esse e será o ultimo
					ptrCorrente->ptrProximo = new ALUNO;	// aloca memória
					if (ptrCorrente->ptrProximo == NULL)	// sem memória?
						return false;				// indica o erro
					memcpy_s(ptrCorrente->ptrProximo, sizeof(ALUNO), ptrStAluno, sizeof(ALUNO));
					ptrCorrente->ptrProximo->ptrProximo = NULL;	// o novo é o ultimo
					return true;					// indica tudo ok
				}
				ptrAnterior = ptrCorrente;			// o corrente é o anterior
			} // for
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
		sprintf_s(cWork, "Código        Nome                           Mensalidade");
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
	// Método público para classificar em ordem crescente de código os alunos 
	//	da lista ligada
	void ClassificarAlunos()
	{
		bool flgHouveTroca;					// indica que houve troca de posição
		ALUNO stWorkAluno;					// auxiliar na troca de posição
		int nExten = sizeof(ALUNO);


		int nExtensao = sizeof(ALUNO) - sizeof(ALUNO *);
		do
		{
			flgHouveTroca = false;			// não houve troca ainda
			// loop de comparação do elem[i] com o elem[i+1]
			for(ptrCorrente = ptrPrimeiro; ptrCorrente; ptrCorrente = ptrCorrente->ptrProximo)
			{
				if(ptrCorrente->ptrProximo == NULL)		// último da lista?
					break;					// cai fora do for
				if(ptrCorrente->nCodAluno > ptrCorrente->ptrProximo->nCodAluno) // fora de ordem
				{	// fora de ordem - fazer a troca de posição
					stWorkAluno.nCodAluno = ptrCorrente->nCodAluno;
					strcpy_s(stWorkAluno.cNomeAluno, ptrCorrente->cNomeAluno);
					stWorkAluno.dMensalidade = ptrCorrente->dMensalidade;
					// copia o próximo sobre o corrente
					ptrCorrente->nCodAluno = ptrCorrente->ptrProximo->nCodAluno;
					strcpy_s(ptrCorrente->cNomeAluno, ptrCorrente->ptrProximo->cNomeAluno);
					ptrCorrente->dMensalidade = ptrCorrente->ptrProximo->dMensalidade;
					// copiar o corrente (stWorkAluno) sobre o próximo
					ptrCorrente->ptrProximo->nCodAluno = stWorkAluno.nCodAluno;
					strcpy_s(ptrCorrente->ptrProximo->cNomeAluno, stWorkAluno.cNomeAluno);
					ptrCorrente->ptrProximo->dMensalidade = stWorkAluno.dMensalidade;
					flgHouveTroca = true;					// indica que houve troca
				}
			} // for
		}while(flgHouveTroca);				// faça enquanto houver troca
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
					delete(ptrPrimeiro);		// libera a memoria do aluno
					ptrPrimeiro = ptrSalva;	// o primeiro da lista é o seguinte ao excluido
				}
				else						// não é o primeiro
				{
					ptrAnterior->ptrProximo = ptrCorrente->ptrProximo;	// link anterior para o próximo
					delete ptrCorrente;
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






