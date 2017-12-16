// Programa de teste de uma lista ligada simples
// FATEC - MC - JCB - 16/02/2017 - Vers�o 0.0
#include "Lista.h"
// Fun��o que pede o c�digo do aluno
//	Par�metro:
//		Entrada: int *ptrCodAluno - endere�o de uma inteira para receber o c�digo
//				 char *ptrAcao - a��o que est� sendo executada
//		Retorno: bool - true - indica que foi informado um c�digo
//						false - indica que o operador cancelou a a��o pedida 
bool PedeCodigoAluno(int *ptrCodAluno, char *ptrAcao)
{
	cout << "\n\t" << ptrAcao << endl;
	cout << "Informe o c�digo do aluno" << endl
		<< "Ou zero para cancelar a a��o: ";
	cin >> *ptrCodAluno;						// recebe o c�digo ou zero
	if (*ptrCodAluno == 0)						// cancelar a��o?
	{
		cout << "Aluno n�o encontrado!" << endl;
		return false;							// indica que cancelou
	}
	return true;								// indica que digitou um c�digo
}
// 
// entry point do programa
//
void main(void)
{
	char cOpcao;								// op��o do operador
	ALUNO stAluno;								// para conter e receber os dados de um aluno
	PAIS_BRASIL;								// acentua��o brasileira
												// instanciar a classe aluno e criar um objeto
	clAluno objAluno;							// cria o objeto aluno
												// loop infinito do programa
	while (true)
	{
		LIMPAR_TELA;
		cout << "\n\tFATEC-MC - Lista ligada simples" << endl;
		cout << INCLUIR_ALUNO << " - Incluir um novo aluno" << endl
			<< EXCLUIR_ALUNO << " - Excluir um aluno existente" << endl
			<< LISTAR_ALUNOS << " - Listar todos os alunos da lista" << endl
			<< MOSTRAR_ALUNO << " - Mostrar os dados de um aluno" << endl
			<< CLASSIFICAR_ALUNOS << " - Classificar os alunos" << endl
			<< SAIR_DO_PROGRAMA << " - Sair do programa" << endl
			<< "\n\tSelecione: ";
		cin >> cOpcao;							// op��o escolhida
		cOpcao = toupper(cOpcao);				// op��o mai�scula
		switch (cOpcao)							// avaliar a escolha
		{
		case INCLUIR_ALUNO:
			if (!PedeCodigoAluno(&stAluno.nCodAluno, "Incluir Aluno")) // cancelou?
				break;						// volta ao menu
			if (objAluno.VerificaSeAlunoExiste(stAluno.nCodAluno, &stAluno)) // aluno existe?
			{	// aluno j� est� na lista
				cout << "Aluno: " << stAluno.nCodAluno << " Nome: "
					<< stAluno.cNomeAluno << endl << "\tJ� est� na lista" << endl;
				PAUSA;
				break;						// volta ao menu
			}
			// o aluno n�o est� na lista
			cin.ignore(1, EOF);				// ignorar a tecla ENTER do buffer do teclado
			cout << "Nome: ";
			cin.getline(stAluno.cNomeAluno, 40, '\n');
			cout << "Mensalidade: ";
			cin >> stAluno.dMensalidade;
			// incluir o aluno na lista
			if (!objAluno.InsercaoDeAluno(&stAluno)) // n�o incluir OK?
			{ // n�o tem mem�ria
				cout << "N�o tem mem�ria dispon�vel!" << endl;
				PAUSA;
			}
			break;							// volta ao menu
		case EXCLUIR_ALUNO:
			if (!PedeCodigoAluno(&stAluno.nCodAluno, "Excluir um aluno")) // cancelou?
				break;						// volta ao menu
			if (!objAluno.ExcluirAluno(stAluno.nCodAluno, &stAluno))
			{
				break;
			}
			break;							// volta ao menu
		case LISTAR_ALUNOS:
			objAluno.ListarAlunos();
			break;							// volta ao menu
		case MOSTRAR_ALUNO:
			if (!PedeCodigoAluno(&stAluno.nCodAluno, "Mostrar um aluno v�lido"))
			{
				cout << "Opera��o cancelada!";
				PAUSA;
				break;
			}
			if (!objAluno.MostraAluno(stAluno.nCodAluno, &stAluno))
			{
				cout << "Aluno n�o encontrado!" << endl;
				PAUSA;
				break;
			}
			cout << "Aluno: " << stAluno.cNomeAluno << endl
				<< "Mensalidade:" << stAluno.dMensalidade << endl;
			PAUSA;
			break;
		case CLASSIFICAR_ALUNOS:
			objAluno.ClassificarAlunos();
			break;							// volta ao menu
		case SAIR_DO_PROGRAMA:
			cout << "Sair realmente? (S ou N): ";
			cin >> cOpcao;
			if (cOpcao == 'S' || cOpcao == 's')	// sair realmente
				return;							// volta ao sistema operacional
			break;							// volta ao menu
		default:
			cout << "\nOp��o inv�lida!" << endl;
			PAUSA;
		} // switch
	} // while
} // main
