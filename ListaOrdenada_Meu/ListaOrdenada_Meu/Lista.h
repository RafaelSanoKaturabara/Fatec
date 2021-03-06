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
		*ptrUltimo,							// ponteiro para o �ltimo da lista
		*ptrCorrente;						// ponteiro para o aluno sendo visto
	// m�todos p�blicos da classe
public:
	// M�todo construtor
	clAluno(void)
	{
		ptrPrimeiro = NULL;					// lista vazia
	}
	// M�todo para inser��o de um aluno na lista ligada
	//	Par�metros:
	//		Entrada: ALUNO *ptrStAluno - endere�o de uma struct que cont�m
	//									os dados do aluno a ser inserido na lista
	//		Retorno - bool - true - inser��o foi OK
	//						 false - n�o tem mem�ria dispon�vel para a inser��o
	bool InsercaoDeAluno(ALUNO *ptrStAluno)
	{
		ALUNO *ptrAnterior,
			*ptrWork;						// ponteiro de trabalho para aluno
		if(ptrPrimeiro == NULL)				// inser��o no primeiro da lista?
		{
			ptrUltimo = ptrPrimeiro = new ALUNO; // inser��o do primeiro e �ltimo
			memcpy_s(ptrUltimo, sizeof(ALUNO), ptrStAluno, sizeof(ALUNO)); // copia os dados do aluno
			ptrUltimo->ptrProximo = NULL;	// �ltimo da lista
			if(ptrUltimo == NULL)			// n�o tem mem�ria?
				return false;				// avisa que n�o tem mem�ria
			return true;					// tudo ok
		}
		ptrWork = new ALUNO;	
		if(ptrWork == NULL)					// n�o tem mem�ria?
			return false;					// avisa que nao tem mem�ria
		ptrAnterior = NULL;
		// loop de verifica��o para colocar na ordem correta
		for(ptrCorrente = ptrPrimeiro; ptrCorrente; ptrCorrente = ptrCorrente->ptrProximo)
		{
			if(ptrStAluno->nCodAluno < ptrCorrente->nCodAluno) // Encontrou a posi��o?
			{
				memcpy_s(ptrWork, sizeof(ALUNO), ptrStAluno, sizeof(ALUNO)); // copia os dados do aluno para ptrWork
				if(ptrAnterior == NULL)		// primeiro?
				{					
					ptrWork->ptrProximo = ptrCorrente;
					ptrPrimeiro = ptrWork;
				}
				else						// posi��o central?
				{
					ptrAnterior->ptrProximo = ptrWork;
					ptrWork->ptrProximo = ptrCorrente;
				}
				return true;
			}
			
			ptrAnterior = ptrCorrente;
		}	// for
		if(ptrCorrente == NULL)				// Ult�mo?
		{
			memcpy_s(ptrWork, sizeof(ALUNO), ptrStAluno, sizeof(ALUNO)); // copia os dados do aluno para ptrWork
			ptrUltimo = ptrAnterior->ptrProximo = ptrWork;
			ptrWork->ptrProximo = NULL;
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
		sprintf_s(cWork, "C�digo Nome                           Mensalidade");
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
					delete ptrPrimeiro;		// libera a memoria do aluno
					ptrPrimeiro = ptrSalva;	// o primeiro da lista � o seguinte ao excluido
				}
				else						// n�o � o primeiro
				{
					ptrAnterior->ptrProximo = ptrCorrente->ptrProximo;	// link anterior para o pr�ximo
					delete ptrCorrente;
					if(ptrAnterior->ptrProximo == NULL)	// �ltimo?
						ptrUltimo = ptrAnterior;		// aponta para quem era o penultimo
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






