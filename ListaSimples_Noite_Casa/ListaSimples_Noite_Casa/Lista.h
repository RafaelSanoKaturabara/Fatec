// Declara��es e classe da lista ligada simples
#include <iostream>
#include <Windows.h>
using namespace std;
// defines
#define PAUSA						system("pause")
#define LIMPAR_TELA					system("cls")
#define PAIS_BRASIL					setlocale(LC_ALL, "portuguese_brazil")
// op��es do menu
#define INCLUIR_ALUNO				'I'
#define EXCLUIR_ALUNO				'E'
#define LISTAR_ALUNOS				'L'
#define MOSTRAR_ALUNO				'M'
#define CLASSIFICAR_ALUNOS			'C'
#define SAIR_DO_PROGRAMA			'S'
// struct do aluno
typedef struct tagALUNO
{
	int nCodAluno;					// c�digo do aluno
	char cNomeAluno[41];			// nome do aluno
	double dMensalidade;			// mensalidade do aluno
	tagALUNO *ptrProximo;			// ponteiro para o pr�ximo da lista ligada
}ALUNO;
//
// classe aluno
//
class clAluno
{
	// atributos private da classe
private:
	ALUNO *ptrPrimeiro,				// ponteiro para o primeiro da lista
		*ptrUltimo,					// ponteiro para o �ltimo da lista
		*ptrAnterior,				// ponteiro para o anterior do corrente
		*ptrCorrente;				// ponteiro para o aluno sendo visto
// m�todos p�blicos da classe
public:
	// M�todo construtor
	clAluno(void)
	{
		ptrPrimeiro = NULL;			// Lista est� vazia
	}
	// m�todo para iner��o de um aluno na lista ligada
	//	Par�metros:
	//		Entrada: ALUNO *ptrAtAluno - endere�o de uma struct que cont�m
	//									os dados do aluno a ser inserido na lista
	//		Retorno: - bool - true - inser��o foi OK
	//						  false - n�o tem mem�ria dispon�vel para a inser��o
	bool InsercaoDeAluno(ALUNO *ptrStAluno)
	{
		if (ptrPrimeiro == NULL)			// inser��o no primeiro da lista?
			ptrUltimo = ptrPrimeiro = new ALUNO;	// inser��o do primeiro e �ltimo
		else
			ptrUltimo = ptrUltimo->ptrProximo = new ALUNO; // insere no �ltimo da lista
														   // temos mem�ria:
		if (ptrUltimo == NULL)			// n�o tem mem�ria?
			return false;				// avisa que n�o tem mem�ria
		memcpy_s(ptrUltimo, sizeof(ALUNO), ptrStAluno, sizeof(ALUNO));	// copia os dados do aluno
		ptrUltimo->ptrProximo = NULL;	// ultimo da lista
		return true;					// tudo OK
	}
	// M�todo para excluir um aluno
	//	Par�metros:
	//		Entrada: int nCodAluno - c�digo do aluno a ser verificado
	//				 ALUNO *ptrStAluno - endere�o de uma struct a receber os dados do aluno
	//									 se ele j� estiver na lista
	//		Retorno: bool - true - o aluno foi exclu�do com sucesso
	//						false - erro ao excluir
	bool ExcluirAluno(int nCodAluno, ALUNO *ptrStAluno)
	{
		char cOpcao;					// op��o do menu
		ptrAnterior = NULL;
		for (ptrCorrente = ptrPrimeiro;	// o corrente se existir � o primeiro da lista
			ptrCorrente;				// se nulo significa fim da lista (false)
			ptrCorrente = ptrCorrente->ptrProximo)	// o corrente � o pr�ximo dele mesmo
		{	// temos um aluno no ptrCorrente
			if (ptrCorrente->nCodAluno == nCodAluno) // o aluno est� na lista?
			{ // aluno est� na lista				
				cout << "\nAluno: " << ptrCorrente->cNomeAluno << endl
					<< "Mensalidade: " << ptrCorrente->dMensalidade << endl
					<< "Deseja realmente excluir o aluno? (S/N): ";
				cin >> cOpcao;
				cOpcao = toupper(cOpcao);
				if (cOpcao == 's' || cOpcao == 'S') // Deseja excluir?
				{
					if (ptrAnterior == NULL) // � o primeiro da lista?
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
				cout << "Aluno n�o cancelado!" << endl;
				PAUSA;
				return false;			// indica que existe
			}
			ptrAnterior = ptrCorrente;
		} // for
		return false;					// indica que aluno n�o est� na lista
	}
	// m�doto que verifica se o aluno j� est� na lista
	//	Par�metros:
	//		Entrada: int nCodAluno - c�digo do aluno a ser verificado
	//				 ALUNO *ptrStAluno - endere�o de uma struct a receber os dados do aluno
	//									 se ele j� estiver na lista
	//		Retorno: bool - true - o aluno j� est� na lista
	//						false - o aluno n�o est� na lista
	bool VerificaSeAlunoExiste(int nCodAluno, ALUNO *ptrStAluno)
	{
		for (ptrCorrente = ptrPrimeiro;	// o corrente se existir � o primeiro da lista
			ptrCorrente;				// se nulo significa fim da lista (false)
			ptrCorrente = ptrCorrente->ptrProximo)	// o corrente � o pr�ximo dele mesmo
		{	// temos um aluno no ptrCorrente
			if (ptrCorrente->nCodAluno == nCodAluno) // o aluno est� na lista?
			{ // aluno est� na lista - copiar os seus dados para o invocador do m�todo
				memcpy_s(ptrStAluno, sizeof(ALUNO), ptrCorrente, sizeof(ALUNO));
				return true;			// indica que existe
			}
		} // for
		return false;					// indica que aluno n�o est� na lista
	}
	// M�todo p�blico que lista todos os alunos da lista ligada
	void ListarAlunos(void)
	{
		char cWork[200];				// para o sprintf_s
		LIMPAR_TELA;
		cout << "\n\tListagem total dos alunos" << endl;
		sprintf_s(cWork, "C�digo Nome                 Mensalidade");
		cout << cWork << endl;
		for (ptrCorrente = ptrPrimeiro;	// o corrente se existir � o primeiro da lista
			ptrCorrente;				// se nulo significa fim da lista (false)
			ptrCorrente = ptrCorrente->ptrProximo)	// o corrente � o pr�ximo dele mesmo
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
	// M�todo que mostra um aluno atrav�s do seu c�digo
	//	Par�metros
	//		Entrada: ALUNO ptrStAluno - Buffer para conter o aluno escolhido
	//		Retorno: bool - true - foi encontrado um aluno
	//						false - n�o encontrado nenhum aluno correspondente
	bool MostraAluno(int nCodAluno, ALUNO *ptrStAluno)
	{
		for (ptrCorrente = ptrPrimeiro;	// o corrente se existir � o primeiro da lista
			ptrCorrente;				// se nulo significa fim da lista (false)
			ptrCorrente = ptrCorrente->ptrProximo)	// o corrente � o pr�ximo dele mesmo
		{	// temos um aluno no ptrCorrente
			if (ptrCorrente->nCodAluno == nCodAluno) // o aluno est� na lista?
			{ // aluno est� na lista - copiar os seus dados para o invocador do m�todo
				memcpy_s(ptrStAluno, sizeof(ALUNO), ptrCorrente, sizeof(ALUNO));
				return true;			// indica que existe
			}
		} // for
		return false;					// indica que aluno n�o est� na lista
	}
	// M�todo p�blico para classificar em ordem crescente de c�digo os alunos 
	//  da lista ligada
	void ClassificarAlunos()
	{
		bool flgHouveTroca;					// indica que houve troca de posi��o
		ALUNO stWorkAluno;					// auxiliar na troca de posi��o
		int nExten = sizeof(ALUNO);
		int nExtensao = sizeof(ALUNO) - sizeof(ALUNO *);
		do
		{
			flgHouveTroca = false;			// n�o houve troca ainda
											// loop de compara��o do elemento[i] com o elemento[i + 1]
			for (ptrCorrente = ptrPrimeiro; ptrCorrente; ptrCorrente = ptrCorrente->ptrProximo)
			{
				if (ptrCorrente->ptrProximo == NULL)	// �ltimo da lista?
					break;					// cai fora do for
				if (ptrCorrente->nCodAluno > ptrCorrente->ptrProximo->nCodAluno) // fora de ordem?
				{ // fora de ordem - fazer a troca de posi��o
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
