// Programa que estuda Lista Simples
// FATEC - MC - JCB - Versão 0.0 - 28/02/2017
#include"Lista.h"
// Função que pede um código de um aluno
//	Parâmetros:
//		Entrada: *ptrCodAluno - ponteiro com o endereço do código do aluno
//		Retorno: bool - true - Código escolhido com sucesso!
//						false - Operador cancelou a operação!
bool pedirCodAluno(int *ptrCodAluno, char *ptrAcao)
{
	cout << "\n\t" << ptrAcao << endl;
	cout << "Digite o código do aluno\nOu zero para cancelar a operaçao: ";
	cin >> *ptrCodAluno;
	if(*ptrCodAluno == 0)							// Cancelou a operação?
	{
		cout <<	"Operação cancelada!" << endl;
		PAUSA;
		return false;								// cancelou
	}
	return true;									// tudo ok!
}
//
// entry point do programa
//
void main(void)
{
	ALUNO stAluno;									// para conter os dados de um aluno
	char cOpcao;									// opção do usuário
	clAluno objAluno;								// cria um objeto do aluno
	PAIS_BRASIL;
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
		switch (cOpcao)
		{
			case INCLUIR_ALUNO:
				if(!pedirCodAluno(&stAluno.nCodAluno, "Incluir um aluno"))
					break;
				if(objAluno.VerificarSeAlunoExiste(&stAluno))
				{
					cout << "Código de um aluno existente!" << endl
						<< "Aluno: " << stAluno.cNomeAluno << endl
						<< "Mensalidade: R$ " << stAluno.dMensalidade << endl;
					PAUSA;
					break;
				}
				cin.ignore(1, EOF);
				cout << "Nome do aluno: ";
				cin.getline(stAluno.cNomeAluno, 40, '\n');
				cout << "Mensalidade: ";
				cin >> stAluno.dMensalidade;
				if(!objAluno.IncluirUmAluno(&stAluno))
					break;
				cout << "Aluno incluído com sucesso!" << endl;
				break;
			case EXCLUIR_ALUNO:
				break;
			case LISTAR_ALUNOS:
				objAluno.ListarAlunos();
				break;
			case MOSTRAR_ALUNO:
				break;
			case CLASSIFICAR_ALUNOS:
				break;
			case SAIR_DO_PROGRAMA:
				cout << "Confirma sair? (S/N): ";
				cin >> cOpcao;
				if (cOpcao == 's'||cOpcao == 'S')
					return;
				break;
			default:
				cout << "Opção inválida!" << endl;
				PAUSA;
		}
	} // while(true)
}