// Declarações e classes do programa
#include<iostream>
#include<Windows.h>
using namespace std;
// definições
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
// classe Aluno
//
class clAluno
{
	// atributos private da classe
private:
	ALUNO *ptrPrimeiro,						// ponteiro do primeiro item da lista
		*ptrUltimo,							// ponteiro do ultimo da lista
		*ptrCorrente;						// ponteiro para o aluno sendo visto
	// métodos Públicos da classe
public:
	// método construtor
	clAluno()
	{
		ptrPrimeiro = NULL;					// lista vazia
	}
	// Método que inclui um aluno 
	//	Parâmetros:
	//		Entrada: ALUNO - *ptrStAluno - endereço de uma struct que contém os dados do aluno a ser incluído
	//		Retorno: bool - true - Aluno inserido com sucesso
	//						false - Memória insulficiente 
	bool IncluirUmAluno(ALUNO *ptrStAluno)
	{
		if(ptrPrimeiro == NULL)
			ptrPrimeiro = ptrUltimo = new ALUNO;
		else
			ptrUltimo = ptrUltimo->ptrProximo = new ALUNO;
		if(ptrUltimo == NULL)				// não tem memória?
		{					// avisa que não tem memória
			cout << "Memória insulficiente!\nFeche alguns programas e tente novamente!" << endl;
			PAUSA;
			return false;
		}
		memcpy_s(ptrUltimo, sizeof(ALUNO), ptrStAluno, sizeof(ALUNO));
		ptrUltimo->ptrProximo = NULL;		// último da lista
		return true;						// tudo OK
	}
	// Método que lista todos os alunos
	void ListarAlunos()
	{
		char cWork[200];					// char de trabalho para sprintf_s
		LIMPAR_TELA;
		cout << "Listagem total de alunos!" << endl;
		cout << "Cód  Nome                           Mensalidade" << endl;
		for (ptrCorrente = ptrPrimeiro; ptrCorrente; ptrCorrente = ptrCorrente->ptrProximo)
		{
			sprintf_s(cWork, " %03d %-30s R$ %6.2f",
				ptrCorrente->nCodAluno, ptrCorrente->cNomeAluno, ptrCorrente->dMensalidade);
			cout << cWork << endl;
		} // for
		cout << "\n\tFim da contagem!" << endl;
		PAUSA;
	}
	// Método que verifica se o aluno existe
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