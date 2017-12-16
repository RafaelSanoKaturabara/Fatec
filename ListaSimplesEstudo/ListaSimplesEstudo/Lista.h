// Declara��es e classes do programa
#include<iostream>
#include<Windows.h>
using namespace std;
// defini��es
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
// classe Aluno
//
class clAluno
{
	// atributos private da classe
private:
	ALUNO *ptrPrimeiro,						// ponteiro do primeiro item da lista
		*ptrUltimo,							// ponteiro do ultimo da lista
		*ptrCorrente;						// ponteiro para o aluno sendo visto
	// m�todos P�blicos da classe
public:
	// m�todo construtor
	clAluno()
	{
		ptrPrimeiro = NULL;					// lista vazia
	}
	// M�todo que inclui um aluno 
	//	Par�metros:
	//		Entrada: ALUNO - *ptrStAluno - endere�o de uma struct que cont�m os dados do aluno a ser inclu�do
	//		Retorno: bool - true - Aluno inserido com sucesso
	//						false - Mem�ria insulficiente 
	bool IncluirUmAluno(ALUNO *ptrStAluno)
	{
		if(ptrPrimeiro == NULL)
			ptrPrimeiro = ptrUltimo = new ALUNO;
		else
			ptrUltimo = ptrUltimo->ptrProximo = new ALUNO;
		if(ptrUltimo == NULL)				// n�o tem mem�ria?
		{					// avisa que n�o tem mem�ria
			cout << "Mem�ria insulficiente!\nFeche alguns programas e tente novamente!" << endl;
			PAUSA;
			return false;
		}
		memcpy_s(ptrUltimo, sizeof(ALUNO), ptrStAluno, sizeof(ALUNO));
		ptrUltimo->ptrProximo = NULL;		// �ltimo da lista
		return true;						// tudo OK
	}
	// M�todo que lista todos os alunos
	void ListarAlunos()
	{
		char cWork[200];					// char de trabalho para sprintf_s
		LIMPAR_TELA;
		cout << "Listagem total de alunos!" << endl;
		cout << "C�d  Nome                           Mensalidade" << endl;
		for (ptrCorrente = ptrPrimeiro; ptrCorrente; ptrCorrente = ptrCorrente->ptrProximo)
		{
			sprintf_s(cWork, " %03d %-30s R$ %6.2f",
				ptrCorrente->nCodAluno, ptrCorrente->cNomeAluno, ptrCorrente->dMensalidade);
			cout << cWork << endl;
		} // for
		cout << "\n\tFim da contagem!" << endl;
		PAUSA;
	}
	// M�todo que verifica se o aluno existe
	bool VerificarSeAlunoExiste(ALUNO *ptrCodAluno)
	{
		for(ptrCorrente = ptrPrimeiro; ptrCorrente; ptrCorrente = ptrCorrente->ptrProximo)
		{
			if(ptrCorrente->nCodAluno == ptrCodAluno->nCodAluno)
			{
				memcpy_s(ptrCodAluno, sizeof(ALUNO), ptrCorrente, sizeof(ALUNO));
				return true;
			}
		}
		return false;
	}
}; 