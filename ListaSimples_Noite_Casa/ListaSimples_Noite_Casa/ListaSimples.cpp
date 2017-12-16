// Programa de teste de uma lista ligada simples
// FATEC - MC - JCB - 16/02/2017 - Versão 0.0
#include "Lista.h"
// Função que pede o código do aluno
//	Parâmetro:
//		Entrada: int *ptrCodAluno - endereço de uma inteira para receber o código
//				 char *ptrAcao - ação que está sendo executada
//		Retorno: bool - true - indica que foi informado um código
//						false - indica que o operador cancelou a ação pedida 
bool PedeCodigoAluno(int *ptrCodAluno, char *ptrAcao)
{
	cout << "\n\t" << ptrAcao << endl;
	cout << "Informe o código do aluno" << endl
		<< "Ou zero para cancelar a ação: ";
	cin >> *ptrCodAluno;						// recebe o código ou zero
	if (*ptrCodAluno == 0)						// cancelar ação?
	{
		cout << "Aluno não encontrado!" << endl;
		return false;							// indica que cancelou
	}
	return true;								// indica que digitou um código
}
// 
// entry point do programa
//
void main(void)
{
	char cOpcao;								// opção do operador
	ALUNO stAluno;								// para conter e receber os dados de um aluno
	PAIS_BRASIL;								// acentuação brasileira
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
		cin >> cOpcao;							// opção escolhida
		cOpcao = toupper(cOpcao);				// opção maiúscula
		switch (cOpcao)							// avaliar a escolha
		{
		case INCLUIR_ALUNO:
			if (!PedeCodigoAluno(&stAluno.nCodAluno, "Incluir Aluno")) // cancelou?
				break;						// volta ao menu
			if (objAluno.VerificaSeAlunoExiste(stAluno.nCodAluno, &stAluno)) // aluno existe?
			{	// aluno já está na lista
				cout << "Aluno: " << stAluno.nCodAluno << " Nome: "
					<< stAluno.cNomeAluno << endl << "\tJá está na lista" << endl;
				PAUSA;
				break;						// volta ao menu
			}
			// o aluno não está na lista
			cin.ignore(1, EOF);				// ignorar a tecla ENTER do buffer do teclado
			cout << "Nome: ";
			cin.getline(stAluno.cNomeAluno, 40, '\n');
			cout << "Mensalidade: ";
			cin >> stAluno.dMensalidade;
			// incluir o aluno na lista
			if (!objAluno.InsercaoDeAluno(&stAluno)) // não incluir OK?
			{ // não tem memória
				cout << "Não tem memória disponível!" << endl;
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
			if (!PedeCodigoAluno(&stAluno.nCodAluno, "Mostrar um aluno válido"))
			{
				cout << "Operação cancelada!";
				PAUSA;
				break;
			}
			if (!objAluno.MostraAluno(stAluno.nCodAluno, &stAluno))
			{
				cout << "Aluno não encontrado!" << endl;
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
			cout << "\nOpção inválida!" << endl;
			PAUSA;
		} // switch
	} // while
} // main
