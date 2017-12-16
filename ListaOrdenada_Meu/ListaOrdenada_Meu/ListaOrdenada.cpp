// Programa de teste de uma lista ligada simples
// FATEC - MC - JCB - 16/02/2017 - Versão 0.0
#include "Lista.h"
// Função que pede o código do aluno
//	Parâmetros:
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
	if(*ptrCodAluno == 0)						// cancelar ação
		return false;							// indica que cancelou
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
	while(true)
	{
		LIMPAR_TELA;
		cout << "\n\tFATEC-MC - Lista Ligada Simples" << endl;
		cout << INCLUIR_ALUNO << " - Incluir um novo aluno" << endl;
		cout << EXCLUIR_ALUNO << " - Excluir um aluno existente" << endl;
		cout << LISTAR_ALUNOS << " - Listar todos os alunos da lista" << endl;
		cout << MOSTRAR_ALUNO << " - Mostrar os dados de um aluno" << endl;
		cout << CLASSIFICAR_ALUNOS << " - Classificar os alunos" << endl;
		cout << SAIR_DO_PROGRAMA << " - Sair do programa" << endl;
		cout << "\n\tSelecione: ";
		cin >> cOpcao;							// opção escolhida
		cOpcao = toupper(cOpcao);				// opção em maiúscula
		switch(cOpcao)							// avaliar a escolha
		{
			case INCLUIR_ALUNO:
				if(!PedeCodigoAluno(&stAluno.nCodAluno, "Incluir aluno")) // cancelou?
					break;						// volta ao menu
				if(objAluno.VerificaSeAlunoExiste(stAluno.nCodAluno, &stAluno)) // aluno existe?
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
				if(!objAluno.InsercaoDeAluno(&stAluno))	// não incluir OK
				{	// não tem memória
					cout << "Não tem memória disponível!" << endl;
					PAUSA;
				}
				break;							// volta ao menu
			case EXCLUIR_ALUNO:
				if(!PedeCodigoAluno(&stAluno.nCodAluno, "Excluir aluno")) // cancelou?
					break;						// volta ao menu
				if(objAluno.VerificaSeAlunoExiste(stAluno.nCodAluno, &stAluno)) // aluno existe?
				{	// aluno já está na lista
					cout << "Aluno: " << stAluno.nCodAluno << " Nome: " 
						<< stAluno.cNomeAluno << endl 
						<< "\tDeseja excluir? (S ou N): ";
					cin >> cOpcao;
					if(cOpcao != 'S' && cOpcao != 's') // excluir realmente?
						break;							// volta ao menu

					// vai excluir
					if(!objAluno.ExcluirAluno(stAluno.nCodAluno))	// problema na exclusão?
					{
						cout << "Problema na exclusão!" << endl;
						PAUSA;
					}
					break;						// volta ao menu
				}
				else 
				{
					cout << "O aluno de código: " << stAluno.nCodAluno << " não existe!" << endl;
					PAUSA;
				}
				break;							// volta ao menu
			case LISTAR_ALUNOS:
				objAluno.ListarAlunos();
				break;							// volta ao menu
			case MOSTRAR_ALUNO:
				break;							// volta ao menu
			case SAIR_DO_PROGRAMA:
				cout << "Sair realmente? (S ou N): ";
				cin >> cOpcao;
				if(cOpcao == 'S' || cOpcao == 's')	// sair realmente?
					return;						// volta ao sistema operacional
				break;							// volta ao menu
			default:
				cout << "\nOpção inválida!" << endl;
				PAUSA;
		} // switch
	} // while
} // main
