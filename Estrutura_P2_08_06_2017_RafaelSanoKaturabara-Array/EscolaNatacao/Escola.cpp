//Prova B2 - Estrutura de Dados 08/06/2017
// FATEC - Mogi das Cruzes - Versão 0.0
#include "Escola.h"

//	Função que pede um período válido (1 - manhã, 2 - tarde ou 3 - noite) ou zero
//		caso o operador vai desistir
//	Parâmetros:
//		Entrada: char *ptrAcao - endereço do string com a ação que está sendo executada
//		Retorno: período desejado ou zero se vai cancelar
int PedirPeriodoValido(char *ptrAcao)
{
	int nOpcao;					// para receber o valor da opção
	// mostrar na tela: Ação: XXXXXXXXXXXXXXXX - ação que está sendo executada
	cout << "\n\t" << ptrAcao << endl;
	// ficar em looping até o operador informar um período válido ou zero para
	//	cancelar
	do
	{
		cout << "Digite um período"<< endl
			<< MANHA << " - Manhã" << endl
			<< TARDE << " - Tarde" << endl
			<< NOITE << " - Noite" << endl
			<< "Zero para sair" << endl
			<< "Selecione: ";
		cin >> nOpcao;
		switch(nOpcao)
		{
			case MANHA:
			case TARDE:
			case NOITE:
			case 0:
				return nOpcao;
			default:
				cout << "Opção inválida!" << endl;
				PAUSA;
		}
	} while(true);
	// retornar o que foi informado
	return 0;							// para não dar erro
}

void main(void)
{
	// codificar as variáveis necessárias
	int nQuantidadeRaias,						// quantidade de rais		
		nPeriodo,								// periodo da aula
		nRaia,									// raia da piscina
		nTipo,									// tipo de despesa
		nOpcao;
	double dValor;								// valor da despesa
	char cOpcao,								// opcao do operador
		cNomeAluno[] = "Rafael Sano Katurabara",
		cRA_Aluno[] = "1840481612043",
		cWork[100];								// para trabalho
	bool flgResult;								// flg para resultado do construtor
	ALUNO stAluno;								// struct para o nome e sobrenome
	SYSTEMTIME stTime;							// para receber data e hora do sistema

	// para tratamento do ponto decimal
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);
	setlocale(LC_ALL, "portuguese_brazil");

	// perguntar quantas raias tem a piscina ( mínimo QTDE_MIN_RAIAS e no máximo
	//	QTDE_MAX_RAIAS).
	// Instanciar a classe clEscolaNatacao informando a quantidade de raias e
	//	endereço da bool a receber o retorno do contrutor da classe.
	// Analisar o retorno para ver se o programa será abortado
	// Ficar em um loop infinito exibindo o menu das opções do operador

	// .... codificar a partir daqui
	do
	{
		cout << "Qtde de raias mínimo de " << QTDE_MIN_RAIAS << " e " << QTDE_MAX_RAIAS <<
			" : " ;
		cin >> nQuantidadeRaias;
	} while(nQuantidadeRaias < QTDE_MIN_RAIAS ||
		nQuantidadeRaias > QTDE_MAX_RAIAS);
	clEscolaNatacao objEscola = clEscolaNatacao(nQuantidadeRaias, &flgResult);
	// analisar o retorno de flgResult
	// se false avisar o operador e sair do programa
	
	while(true)	//laço infinito
	{
		// Pedir data e hora do sistema
		GetLocalTime(&stTime);
		LIMPA_TELA;
		sprintf(cWork,
			"Escola de Natação FATEC - MC - Turma Tarde - %02d/%02d/%04d às %02d:%02d",
			stTime.wDay, stTime.wMonth, stTime.wYear, 
			stTime.wHour, stTime.wMinute);
		cout << cWork << endl;
		sprintf(cWork, "\tAluno: %s RA: %s",
			cNomeAluno, cRA_Aluno);
		cout << cWork << endl;
		cout << "M - Matricular aluno" << endl;
		cout << "P - Listar alunos de um período" << endl;
		cout << "T - Listar todos os alunos" << endl;
		cout << "C - Cancelar Matrícula" << endl;
		cout << "D - Lançar despesa em um aluno" << endl;
		cout << "U - Consultar um dado aluno" << endl;
		cout << "S - Sair do Programa" << endl;
		cout << "\tSelecione: ";
		cin >> cOpcao;					//recebendo o desejo do operador
		cOpcao = toupper(cOpcao);		//convertendo para caixa alta
		switch(cOpcao)
		{
		case MATRICULAR_ALUNO:			//matriculando um novo aluno
			// chamar a função PedirPeriodoValido e analisar o retorno.
			nPeriodo = PedirPeriodoValido("Matricular aluno");
			//	Se o operador desistiu, voltar ao menu principal
			if (nPeriodo == 0)
			{
				cout << "Cancelado!" << endl;
				PAUSA;
				break;
			}			
			// Pedir o prenome e sobrenome do aluno (stAluno) não se esquecendo que
			//	tanto o prenome e sobrenome podem ter brancos no meio...
			cin.ignore(1, EOF);
			cout << "Digite o nome do aluno: ";
			cin.getline(stAluno.cPrenome, 30, '\n');
			cout << "Digite o sobrenome do aluno: ";
			cin.getline(stAluno.cSobrenome, 20, '\n');
			// invocar o método para matricular e analizar o retorno...
			nRaia = objEscola.MatricularAluno(nPeriodo, &stAluno);
			if (nRaia == 0)
			{
				cout << "Nenhuma raia livre!";
				PAUSA;
				break;
			}
			//	se o retorno for zero significa que não tinha raia livre naquele
			//  período e assim avisar ao operador e voltar ao menu principal...
			cout << "Aluno matriculado na raia " << nRaia << endl;
			PAUSA;
			//	Exibir a raia que o aluno foi matriculado...
			break;

		case LISTAR_ALUNOS_DE_UM_PERIODO:
			// chamar a função PedirPeriodoValido e analisar o retorno.
			nPeriodo = PedirPeriodoValido("Listar aluno por período");
			//	Se o operador desistiu, voltar ao menu principal
			if (nPeriodo == 0)
			{
				cout << "Cancelado!" << endl;
				PAUSA;
				break;
			}
			objEscola.ListarUmPeriodo(nPeriodo);
			break;

		case LISTAR_TODOS_OS_ALUNOS:
			// invocar o metodo para listar todos os alunos
			objEscola.ListarTodosPeriodos();
			break;

		case CANCELAR_MATRICULA:
			// chamar a função PedirPeriodoValido e analisar o retorno.
			nPeriodo = PedirPeriodoValido("Cancelar matricula de um aluno");
			//	Se o operador desistiu, voltar ao menu principal
			if (nPeriodo == 0)
			{
				cout << "Cancelado!" << endl;
				PAUSA;
				break;
			}			
			//	Ficar em looping pedindo a raia do aluno que tem que ser válida ou
			//		zero se vai desistir....
			do
			{
				cout << "Digite a raia do aluno de 1 até " << nQuantidadeRaias << "(0 - desiste): ";
				cin >> nRaia;
			} while(nRaia < 0 || nRaia > nQuantidadeRaias);
			if(nRaia == 0)
				break;	
			// Invocar o método que cancela a matrícula....
			//	Analisar o resultado
			if(!objEscola.CancelarMatricula(nPeriodo, nRaia))
			// verificação dentro do proprio método
				break;
			break;
		case LANCAR_DESPESA_EM_UM_ALUNO:
			// chamar a função PedirPeriodoValido e analisar o retorno.
			nPeriodo = PedirPeriodoValido("Lançar despesa de um aluno");
			//	Se o operador desistiu, voltar ao menu principal
			if (nPeriodo == 0)
			{
				cout << "Cancelado!" << endl;
				PAUSA;
				break;
			}	//	Se o operador desistiu, voltar ao menu principal
			//	Ficar em looping pedindo a raia do aluno que tem que ser válida ou
			//		zero se vai desistir....
			do
			{
				cout << "Digite a raia do aluno de 1 até " << nQuantidadeRaias << "(0 - desiste): ";
				cin >> nRaia;
			} while(nRaia < 0 || nRaia > nQuantidadeRaias);
			if(nRaia == 0)
				break;
			// Ficar em looping pedindo um tipo de despesa válido ou zero para
			//		desistir..
			do
			{
				cout << "Digite um tipo de despesa:" << endl
					<< LANCHONETE << " - Lanchonete" << endl
					<< ACESSORIOS << " - Acessórios" << endl
					<< HIGIENE << " - Higiene" << endl
					<< "Digite: ";
				cin >> nTipo;
			} while(nTipo < 0 || nTipo > 3);
			if(nTipo == 0)
				break;
			// Pedir o valor da despesa
			cout << "Digite o valor da despesa: ";
			cin >> dValor;
			// Invocar o método que lança a despesa....
			if(!objEscola.LancarDespesa(nPeriodo, nRaia, nTipo, dValor))
			{
				cout << "Erro ao lançar a despesa!" << endl;
				PAUSA;
				break;
			}
			cout << "Inserido com sucesso!" << endl;
			PAUSA;
			//	Analisar o resultado...
			break;

		case CONSULTAR_UM_DADO_ALUNO:			//consultando um dado aluno
			// chamar a função PedirPeriodoValido e analisar o retorno.
			nPeriodo = PedirPeriodoValido("Consultar um dado aluno");
			//	Se o operador desistiu, voltar ao menu principal
			if (nPeriodo == 0)
			{
				cout << "Cancelado!" << endl;
				PAUSA;
				break;
			}
			//	Ficar em looping pedindo a raia do aluno que tem que ser válida ou
			//		zero se vai desistir....
			do
			{
				cout << "Digite a raia do aluno de 1 até " << nQuantidadeRaias << "(0 - desiste): ";
				cin >> nRaia;
			} while(nRaia < 0 || nRaia > nQuantidadeRaias);
			if(nRaia == 0)
				break;
			// Invocar o método que consulta um dado aluno....
			if(!objEscola.ConsultarAluno(nPeriodo, nRaia))
			{
				cout << "Erro ao consultar o aluno!" << endl;
			}
			PAUSA;
			break;

		case SAIR_DO_PROGRAMA:				//sair
				cout << "tem certeza que deseja finalizar o sistema (S/N)?" << endl;
				cin >> cOpcao;
				cOpcao = toupper(cOpcao);		//convertendo para caixa alta
				if(cOpcao == 'S')				//deseja sair?
				{//sim
					cout << "Finalizando o sistema..." << endl;
					PAUSA;
					return;
				}
				//não
				break;
			default:
				cout << "Opção invalida!!!" << endl;
				PAUSA;
		}
	}
} // main
