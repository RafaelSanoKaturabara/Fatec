// Declara��es e classe da lista ligada simples
#include <iostream>
#include <Windows.h>
using namespace std;
// defines
#define PAUSA								system("pause")
#define LIMPAR_TELA							system("cls")
#define PAIS_BRASIL							setlocale(LC_ALL, "portuguese_brazil")
// op��es do menu
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
	tagALUNO *ptrProximo;					// ponteiro para o pr�ximo da lista ligada
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
	// m�todos p�blicos da classe
public:
	// M�todo construtor
	clAluno(void)
	{
		ptrPrimeiro = NULL;					// lista vazia
	}
	// M�todo para inser��o de um aluno na lista ligada - de forma ordenada
	//	Par�metros:
	//		Entrada: ALUNO *ptrStAluno - endere�o de uma struct que cont�m
	//									os dados do aluno a ser inserido na lista
	//		Retorno - bool - true - inser��o foi OK
	//						 false - n�o tem mem�ria dispon�vel para a inser��o
	bool InsercaoDeAluno(ALUNO *ptrStAluno)
	{
		ALUNO *ptrSalva,					// salva u endere�o que ser� perdido
			*ptrAnterior = 0;				// aponta para o pr�ximo aluno
		if(ptrPrimeiro == NULL)				// inser��o no primeiro da lista?
		{
			ptrPrimeiro = new ALUNO;		// inser��o do primeiro e �ltimo
			if(ptrPrimeiro == NULL)			// testar se tem mem�ria
				return false;				// avisa que n�o tem mem�ria
			// tem mem�ria do novo aluno
			memcpy_s(ptrPrimeiro, sizeof(ALUNO), ptrStAluno, sizeof(ALUNO));
			ptrPrimeiro->ptrProximo == NULL;	// primeiro e ultimo da lista
			return true;						// avisa que foi tudo ok
		}
		else	// n�o � o primeiro da lista - vamos procurar o ponto de inser��o
		{
			// varrer a lista para encontrar o ponto de inser��o
			for(ptrCorrente = ptrPrimeiro; ptrCorrente; ptrCorrente = ptrCorrente->ptrProximo)
			{
				if(ptrStAluno->nCodAluno < ptrCorrente->nCodAluno)	// no ponto de inser��o?
				{	// vamos testar se o novo aluno ser� o primeiro da lista
					if(ptrAnterior == 0)			// n�o passou pelo primeiro da lista?
					{
						ptrSalva = ptrPrimeiro;		// salva o ponteiro do atual primeiro da lista
						ptrPrimeiro = new ALUNO;	// aloca um espa�o de mem�ria para o aluno
						if(ptrPrimeiro == NULL)		// n�o tem mem�ria?
						{
							ptrPrimeiro = ptrSalva;	// restaura a lista ligada
							return false;
						}
						// tem mem�ria
						memcpy_s(ptrPrimeiro, sizeof(ALUNO), ptrStAluno, sizeof(ALUNO));
						ptrPrimeiro->ptrProximo = ptrSalva;	// aponta para o aluno que era o primeiro
						return true;				// indica tudo ok
					}	// inser��o como o primeiro da lista
					else
					{	// o ponto de inser��o � ap�s o primeiro
						ptrSalva = ptrAnterior->ptrProximo;
						ptrAnterior->ptrProximo = new ALUNO;	// aloca mem�ria
						if(ptrAnterior->ptrProximo == NULL)		// sem mem�ria?
						{
							ptrAnterior->ptrProximo = ptrSalva;	// restaura a lista
							return false;			// avisa o erro
						}
						// tem mem�ria
						memcpy_s(ptrAnterior->ptrProximo, sizeof(ALUNO), ptrStAluno, sizeof(ALUNO));
						ptrAnterior->ptrProximo->ptrProximo = ptrSalva;
						return true;
					}
				}
				// o c�digo do novo aluno � maior que o c�digo do aluno corrente
				// testar se o corrente � o ultimo
				if(ptrCorrente->ptrProximo == NULL)	// �ltimo aluno?
				{	// inserir o novo aluno sobre esse e ser� o ultimo
					ptrCorrente->ptrProximo = new ALUNO;	// aloca mem�ria
					if (ptrCorrente->ptrProximo == NULL)	// sem mem�ria?
						return false;				// indica o erro
					memcpy_s(ptrCorrente->ptrProximo, sizeof(ALUNO), ptrStAluno, sizeof(ALUNO));
					ptrCorrente->ptrProximo->ptrProximo = NULL;	// o novo � o ultimo
					return true;					// indica tudo ok
				}
				ptrAnterior = ptrCorrente;			// o corrente � o anterior
			} // for
		}
	}
	// M�todo que verifica se o aluno j� est� na lista
	//	Par�metros:
	//		Entrada: int nCodAluno - c�digo do aluno a ser verificado
	//				 ALUNO *ptrStAluno - endere�o de uma struct a receber os dados do
	//									aluno se ele j� estiver na lista
	//		Retorno: bool - true - o aluno j� est� na lista
	//						false - o aluno n�o est� na lista
	bool VerificaSeAlunoExiste(int nCodAluno, ALUNO *ptrStAluno)
	{
		for(ptrCorrente = ptrPrimeiro;			// o corrente se existir � o primeiro da lista
			ptrCorrente;						// se nulo significa fim da lista (false)
			ptrCorrente = ptrCorrente->ptrProximo) // o corrente � o pr�ximo dele mesmo
		{	// temos um aluno no ptrCorrente
			if(ptrCorrente->nCodAluno == nCodAluno) // o aluno est� na lista?
			{	// aluno est� na lista - copiar os seus dados para o invocador do m�todo
				memcpy_s(ptrStAluno, sizeof(ALUNO), ptrCorrente, sizeof(ALUNO));
				return true;						// indica que existe
			}
		} // for
		return false;								// indica que aluno n�o est� na lista
	}
	// M�todo p�blico que lista todos o alunos da lista ligada
	void ListarAlunos(void)
	{
		char cWork[200];						// para o sprintf_s
		LIMPAR_TELA;
		cout << "\n\tListagem total dos alunos" << endl;
		sprintf_s(cWork, "C�digo        Nome                           Mensalidade");
		cout << cWork << endl;
		for(ptrCorrente = ptrPrimeiro;			// o corrente se existir � o primeiro da lista
			ptrCorrente;						// se nulo significa fim da lista (false)
			ptrCorrente = ptrCorrente->ptrProximo) // o corrente � o pr�ximo dele mesmo
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
	// M�todo p�blico para classificar em ordem crescente de c�digo os alunos 
	//	da lista ligada
	void ClassificarAlunos()
	{
		bool flgHouveTroca;					// indica que houve troca de posi��o
		ALUNO stWorkAluno;					// auxiliar na troca de posi��o
		int nExten = sizeof(ALUNO);


		int nExtensao = sizeof(ALUNO) - sizeof(ALUNO *);
		do
		{
			flgHouveTroca = false;			// n�o houve troca ainda
			// loop de compara��o do elem[i] com o elem[i+1]
			for(ptrCorrente = ptrPrimeiro; ptrCorrente; ptrCorrente = ptrCorrente->ptrProximo)
			{
				if(ptrCorrente->ptrProximo == NULL)		// �ltimo da lista?
					break;					// cai fora do for
				if(ptrCorrente->nCodAluno > ptrCorrente->ptrProximo->nCodAluno) // fora de ordem
				{	// fora de ordem - fazer a troca de posi��o
					stWorkAluno.nCodAluno = ptrCorrente->nCodAluno;
					strcpy_s(stWorkAluno.cNomeAluno, ptrCorrente->cNomeAluno);
					stWorkAluno.dMensalidade = ptrCorrente->dMensalidade;
					// copia o pr�ximo sobre o corrente
					ptrCorrente->nCodAluno = ptrCorrente->ptrProximo->nCodAluno;
					strcpy_s(ptrCorrente->cNomeAluno, ptrCorrente->ptrProximo->cNomeAluno);
					ptrCorrente->dMensalidade = ptrCorrente->ptrProximo->dMensalidade;
					// copiar o corrente (stWorkAluno) sobre o pr�ximo
					ptrCorrente->ptrProximo->nCodAluno = stWorkAluno.nCodAluno;
					strcpy_s(ptrCorrente->ptrProximo->cNomeAluno, stWorkAluno.cNomeAluno);
					ptrCorrente->ptrProximo->dMensalidade = stWorkAluno.dMensalidade;
					flgHouveTroca = true;					// indica que houve troca
				}
			} // for
		}while(flgHouveTroca);				// fa�a enquanto houver troca
	}
	// M�todo publico que exclui um aluno da lista ligada
	//	Par�metros:
	//		Entrada: int nCodigo - codigo do aluno a ser excluido
	//		Retorno: bool - true - exclus�o ok
	//						false - o aluno n�o existe
	bool ExcluirAluno(int nCodigo)
	{
		ALUNO *ptrSalva,					// salva u endere�o que ser� perdido
			*ptrAnterior = 0;				// aponta para o pr�ximo aluno
		// loop de busca do aluno a ser exclu�do
		for(ptrCorrente = ptrPrimeiro; ptrCorrente; ptrCorrente = ptrCorrente->ptrProximo)
		{
			if(nCodigo == ptrCorrente->nCodAluno)		// � o aluno desejado?
			{	// o aluno foi encontrado
				if(ptrAnterior == NULL)		// primeiro da lista
				{	// primeiro da lista
					ptrSalva = ptrPrimeiro->ptrProximo;	// salva quem vai ser o primeiro
					delete(ptrPrimeiro);		// libera a memoria do aluno
					ptrPrimeiro = ptrSalva;	// o primeiro da lista � o seguinte ao excluido
				}
				else						// n�o � o primeiro
				{
					ptrAnterior->ptrProximo = ptrCorrente->ptrProximo;	// link anterior para o pr�ximo
					delete ptrCorrente;
				}
				return true;				// exclus�o ok
			}	// encontrou o aluno
			// n�o encontrou o aluno ainda
			ptrAnterior = ptrCorrente;		// o corrente passa a ser anterior
		} // for 
		// n�o encontrou o aluno
		return false;						// avisa que n�o encontrou
	}
};






