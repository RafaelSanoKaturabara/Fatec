// Declarações e classe da lista ligada simples
#include <iostream>
#include <Windows.h>
using namespace std;
// defines
#define PAUSA						system("pause")
#define LIMPAR_TELA					system("cls")
#define PAIS_BRASIL					setlocale(LC_ALL, "portuguese_brazil")
// opções do menu
#define INCLUIR_ALUNO				'I'
#define EXCLUIR_ALUNO				'E'
#define LISTAR_ALUNOS				'L'
#define MOSTRAR_ALUNO				'M'
#define CLASSIFICAR_ALUNOS			'C'
#define SAIR_DO_PROGRAMA			'S'
// struct do aluno
typedef struct tagALUNO
{
	int nCodAluno;					// código do aluno
	char cNomeAluno[41];			// nome do aluno
	double dMensalidade;			// mensalidade do aluno
	tagALUNO *ptrProximo;			// ponteiro para o próximo da lista ligada
}ALUNO;
//
// classe aluno
//
class clAluno
{
	// atributos private da classe
private:
	ALUNO *ptrPrimeiro,				// ponteiro para o primeiro da lista
		*ptrUltimo,					// ponteiro para o último da lista
		*ptrAnterior,				// ponteiro para o anterior do corrente
		*ptrCorrente;				// ponteiro para o aluno sendo visto
// métodos públicos da classe
public:
	// Método construtor
	clAluno(void)
	{
		ptrPrimeiro = NULL;			// Lista está vazia
	}
	// método para inerção de um aluno na lista ligada
	//	Parâmetros:
	//		Entrada: ALUNO *ptrAtAluno - endereço de uma struct que contém
	//									os dados do aluno a ser inserido na lista
	//		Retorno: - bool - true - inserção foi OK
	//						  false - não tem memória disponível para a inserção
	bool InsercaoDeAluno(ALUNO *ptrStAluno)
	{
		if (ptrPrimeiro == NULL)			// inserção no primeiro da lista?
			ptrUltimo = ptrPrimeiro = new ALUNO;	// inserção do primeiro e último
		else
			ptrUltimo = ptrUltimo->ptrProximo = new ALUNO; // insere no último da lista
														   // temos memória:
		if (ptrUltimo == NULL)			// não tem memória?
			return false;				// avisa que não tem memória
		memcpy_s(ptrUltimo, sizeof(ALUNO), ptrStAluno, sizeof(ALUNO));	// copia os dados do aluno
		ptrUltimo->ptrProximo = NULL;	// ultimo da lista
		return true;					// tudo OK
	}
	// Método para excluir um aluno
	//	Parâmetros:
	//		Entrada: int nCodAluno - código do aluno a ser verificado
	//				 ALUNO *ptrStAluno - endereço de uma struct a receber os dados do aluno
	//									 se ele já estiver na lista
	//		Retorno: bool - true - o aluno foi excluído com sucesso
	//						false - erro ao excluir
	bool ExcluirAluno(int nCodAluno, ALUNO *ptrStAluno)
	{
		char cOpcao;					// opção do menu
		ptrAnterior = NULL;
		for (ptrCorrente = ptrPrimeiro;	// o corrente se existir é o primeiro da lista
			ptrCorrente;				// se nulo significa fim da lista (false)
			ptrCorrente = ptrCorrente->ptrProximo)	// o corrente é o próximo dele mesmo
		{	// temos um aluno no ptrCorrente
			if (ptrCorrente->nCodAluno == nCodAluno) // o aluno está na lista?
			{ // aluno está na lista				
				cout << "\nAluno: " << ptrCorrente->cNomeAluno << endl
					<< "Mensalidade: " << ptrCorrente->dMensalidade << endl
					<< "Deseja realmente excluir o aluno? (S/N): ";
				cin >> cOpcao;
				cOpcao = toupper(cOpcao);
				if (cOpcao == 's' || cOpcao == 'S') // Deseja excluir?
				{
					if (ptrAnterior == NULL) // é o primeiro da lista?
					{						
						ptrPrimeiro = ptrCorrente->ptrProximo;						
					}
					else
					{
						ptrAnterior->ptrProximo = ptrCorrente->ptrProximo;
					}
					delete ptrCorrente;
					cout << "Excluido com sucesso!" << endl;
					PAUSA;
					return true;
				}
				cout << "Aluno não cancelado!" << endl;
				PAUSA;
				return false;			// indica que existe
			}
			ptrAnterior = ptrCorrente;
		} // for
		return false;					// indica que aluno não está na lista
	}
	// médoto que verifica se o aluno já está na lista
	//	Parâmetros:
	//		Entrada: int nCodAluno - código do aluno a ser verificado
	//				 ALUNO *ptrStAluno - endereço de uma struct a receber os dados do aluno
	//									 se ele já estiver na lista
	//		Retorno: bool - true - o aluno já está na lista
	//						false - o aluno não está na lista
	bool VerificaSeAlunoExiste(int nCodAluno, ALUNO *ptrStAluno)
	{
		for (ptrCorrente = ptrPrimeiro;	// o corrente se existir é o primeiro da lista
			ptrCorrente;				// se nulo significa fim da lista (false)
			ptrCorrente = ptrCorrente->ptrProximo)	// o corrente é o próximo dele mesmo
		{	// temos um aluno no ptrCorrente
			if (ptrCorrente->nCodAluno == nCodAluno) // o aluno está na lista?
			{ // aluno está na lista - copiar os seus dados para o invocador do método
				memcpy_s(ptrStAluno, sizeof(ALUNO), ptrCorrente, sizeof(ALUNO));
				return true;			// indica que existe
			}
		} // for
		return false;					// indica que aluno não está na lista
	}
	// Método público que lista todos os alunos da lista ligada
	void ListarAlunos(void)
	{
		char cWork[200];				// para o sprintf_s
		LIMPAR_TELA;
		cout << "\n\tListagem total dos alunos" << endl;
		sprintf_s(cWork, "Código Nome                 Mensalidade");
		cout << cWork << endl;
		for (ptrCorrente = ptrPrimeiro;	// o corrente se existir é o primeiro da lista
			ptrCorrente;				// se nulo significa fim da lista (false)
			ptrCorrente = ptrCorrente->ptrProximo)	// o corrente é o próximo dele mesmo
		{	// temos um aluno no ptrCorrente
			sprintf_s(cWork, "   %03d %-20s R$ %6.2f",
				ptrCorrente->nCodAluno,
				ptrCorrente->cNomeAluno,
				ptrCorrente->dMensalidade);
			cout << cWork << endl;
		} // for
		cout << "Fim da listagem!" << endl;
		PAUSA;
	}
	// Método que mostra um aluno através do seu código
	//	Parâmetros
	//		Entrada: ALUNO ptrStAluno - Buffer para conter o aluno escolhido
	//		Retorno: bool - true - foi encontrado um aluno
	//						false - não encontrado nenhum aluno correspondente
	bool MostraAluno(int nCodAluno, ALUNO *ptrStAluno)
	{
		for (ptrCorrente = ptrPrimeiro;	// o corrente se existir é o primeiro da lista
			ptrCorrente;				// se nulo significa fim da lista (false)
			ptrCorrente = ptrCorrente->ptrProximo)	// o corrente é o próximo dele mesmo
		{	// temos um aluno no ptrCorrente
			if (ptrCorrente->nCodAluno == nCodAluno) // o aluno está na lista?
			{ // aluno está na lista - copiar os seus dados para o invocador do método
				memcpy_s(ptrStAluno, sizeof(ALUNO), ptrCorrente, sizeof(ALUNO));
				return true;			// indica que existe
			}
		} // for
		return false;					// indica que aluno não está na lista
	}
	// Método público para classificar em ordem crescente de código os alunos 
	//  da lista ligada
	void ClassificarAlunos()
	{
		bool flgHouveTroca;					// indica que houve troca de posição
		ALUNO stWorkAluno;					// auxiliar na troca de posição
		int nExten = sizeof(ALUNO);
		int nExtensao = sizeof(ALUNO) - sizeof(ALUNO *);
		do
		{
			flgHouveTroca = false;			// não houve troca ainda
											// loop de comparação do elemento[i] com o elemento[i + 1]
			for (ptrCorrente = ptrPrimeiro; ptrCorrente; ptrCorrente = ptrCorrente->ptrProximo)
			{
				if (ptrCorrente->ptrProximo == NULL)	// Último da lista?
					break;					// cai fora do for
				if (ptrCorrente->nCodAluno > ptrCorrente->ptrProximo->nCodAluno) // fora de ordem?
				{ // fora de ordem - fazer a troca de posição
					stWorkAluno.nCodAluno = ptrCorrente->nCodAluno;
					strcpy_s(stWorkAluno.cNomeAluno, ptrCorrente->cNomeAluno);
					stWorkAluno.dMensalidade = ptrCorrente->dMensalidade;

					ptrCorrente->nCodAluno = ptrCorrente->ptrProximo->nCodAluno;
					strcpy_s(ptrCorrente->cNomeAluno, ptrCorrente->ptrProximo->cNomeAluno);
					ptrCorrente->dMensalidade = ptrCorrente->ptrProximo->dMensalidade;

					ptrCorrente->ptrProximo->nCodAluno = stWorkAluno.nCodAluno;
					strcpy_s(ptrCorrente->ptrProximo->cNomeAluno, stWorkAluno.cNomeAluno);
					ptrCorrente->ptrProximo->dMensalidade = stWorkAluno.dMensalidade;

					flgHouveTroca = true;			// indica que houve troca
				}
			} // for
		} while (flgHouveTroca);
	}
}; 
