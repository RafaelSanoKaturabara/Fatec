//Prova B2 - Estrutura de Dados 08/06/2017
// FATEC - Mogi das Cruzes - Vers�o 0.0
#include "Escola.h"

//	Fun��o que pede um per�odo v�lido (1 - manh�, 2 - tarde ou 3 - noite) ou zero
//		caso o operador vai desistir
//	Par�metros:
//		Entrada: char *ptrAcao - endere�o do string com a a��o que est� sendo executada
//		Retorno: per�odo desejado ou zero se vai cancelar
int PedirPeriodoValido(char *ptrAcao)
{
	int nOpcao;					// para receber o valor da op��o
	// mostrar na tela: A��o: XXXXXXXXXXXXXXXX - a��o que est� sendo executada
	cout << "\n\t" << ptrAcao << endl;
	// ficar em looping at� o operador informar um per�odo v�lido ou zero para
	//	cancelar
	do
	{
		cout << "Digite um per�odo"<< endl
			<< MANHA << " - Manh�" << endl
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
				cout << "Op��o inv�lida!" << endl;
				PAUSA;
		}
	} while(true);
	// retornar o que foi informado
	return 0;							// para n�o dar erro
}

void main(void)
{
	// codificar as vari�veis necess�rias
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

	// perguntar quantas raias tem a piscina ( m�nimo QTDE_MIN_RAIAS e no m�ximo
	//	QTDE_MAX_RAIAS).
	// Instanciar a classe clEscolaNatacao informando a quantidade de raias e
	//	endere�o da bool a receber o retorno do contrutor da classe.
	// Analisar o retorno para ver se o programa ser� abortado
	// Ficar em um loop infinito exibindo o menu das op��es do operador

	// .... codificar a partir daqui
	do
	{
		cout << "Qtde de raias m�nimo de " << QTDE_MIN_RAIAS << " e " << QTDE_MAX_RAIAS <<
			" : " ;
		cin >> nQuantidadeRaias;
	} while(nQuantidadeRaias < QTDE_MIN_RAIAS ||
		nQuantidadeRaias > QTDE_MAX_RAIAS);
	clEscolaNatacao objEscola = clEscolaNatacao(nQuantidadeRaias, &flgResult);
	// analisar o retorno de flgResult
	// se false avisar o operador e sair do programa
	
	while(true)	//la�o infinito
	{
		// Pedir data e hora do sistema
		GetLocalTime(&stTime);
		LIMPA_TELA;
		sprintf(cWork,
			"Escola de Nata��o FATEC - MC - Turma Tarde - %02d/%02d/%04d �s %02d:%02d",
			stTime.wDay, stTime.wMonth, stTime.wYear, 
			stTime.wHour, stTime.wMinute);
		cout << cWork << endl;
		sprintf(cWork, "\tAluno: %s RA: %s",
			cNomeAluno, cRA_Aluno);
		cout << cWork << endl;
		cout << "M - Matricular aluno" << endl;
		cout << "P - Listar alunos de um per�odo" << endl;
		cout << "T - Listar todos os alunos" << endl;
		cout << "C - Cancelar Matr�cula" << endl;
		cout << "D - Lan�ar despesa em um aluno" << endl;
		cout << "U - Consultar um dado aluno" << endl;
		cout << "S - Sair do Programa" << endl;
		cout << "\tSelecione: ";
		cin >> cOpcao;					//recebendo o desejo do operador
		cOpcao = toupper(cOpcao);		//convertendo para caixa alta
		switch(cOpcao)
		{
		case MATRICULAR_ALUNO:			//matriculando um novo aluno
			// chamar a fun��o PedirPeriodoValido e analisar o retorno.
			nPeriodo = PedirPeriodoValido("Matricular aluno");
			//	Se o operador desistiu, voltar ao menu principal
			if (nPeriodo == 0)
			{
				cout << "Cancelado!" << endl;
				PAUSA;
				break;
			}			
			// Pedir o prenome e sobrenome do aluno (stAluno) n�o se esquecendo que
			//	tanto o prenome e sobrenome podem ter brancos no meio...
			cin.ignore(1, EOF);
			cout << "Digite o nome do aluno: ";
			cin.getline(stAluno.cPrenome, 30, '\n');
			cout << "Digite o sobrenome do aluno: ";
			cin.getline(stAluno.cSobrenome, 20, '\n');
			// invocar o m�todo para matricular e analizar o retorno...
			nRaia = objEscola.MatricularAluno(nPeriodo, &stAluno);
			if (nRaia == 0)
			{
				cout << "Nenhuma raia livre!";
				PAUSA;
				break;
			}
			//	se o retorno for zero significa que n�o tinha raia livre naquele
			//  per�odo e assim avisar ao operador e voltar ao menu principal...
			cout << "Aluno matriculado na raia " << nRaia << endl;
			PAUSA;
			//	Exibir a raia que o aluno foi matriculado...
			break;

		case LISTAR_ALUNOS_DE_UM_PERIODO:
			// chamar a fun��o PedirPeriodoValido e analisar o retorno.
			nPeriodo = PedirPeriodoValido("Listar aluno por per�odo");
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
			// chamar a fun��o PedirPeriodoValido e analisar o retorno.
			nPeriodo = PedirPeriodoValido("Cancelar matricula de um aluno");
			//	Se o operador desistiu, voltar ao menu principal
			if (nPeriodo == 0)
			{
				cout << "Cancelado!" << endl;
				PAUSA;
				break;
			}			
			//	Ficar em looping pedindo a raia do aluno que tem que ser v�lida ou
			//		zero se vai desistir....
			do
			{
				cout << "Digite a raia do aluno de 1 at� " << nQuantidadeRaias << "(0 - desiste): ";
				cin >> nRaia;
			} while(nRaia < 0 || nRaia > nQuantidadeRaias);
			if(nRaia == 0)
				break;	
			// Invocar o m�todo que cancela a matr�cula....
			//	Analisar o resultado
			if(!objEscola.CancelarMatricula(nPeriodo, nRaia))
			// verifica��o dentro do proprio m�todo
				break;
			break;
		case LANCAR_DESPESA_EM_UM_ALUNO:
			// chamar a fun��o PedirPeriodoValido e analisar o retorno.
			nPeriodo = PedirPeriodoValido("Lan�ar despesa de um aluno");
			//	Se o operador desistiu, voltar ao menu principal
			if (nPeriodo == 0)
			{
				cout << "Cancelado!" << endl;
				PAUSA;
				break;
			}	//	Se o operador desistiu, voltar ao menu principal
			//	Ficar em looping pedindo a raia do aluno que tem que ser v�lida ou
			//		zero se vai desistir....
			do
			{
				cout << "Digite a raia do aluno de 1 at� " << nQuantidadeRaias << "(0 - desiste): ";
				cin >> nRaia;
			} while(nRaia < 0 || nRaia > nQuantidadeRaias);
			if(nRaia == 0)
				break;
			// Ficar em looping pedindo um tipo de despesa v�lido ou zero para
			//		desistir..
			do
			{
				cout << "Digite um tipo de despesa:" << endl
					<< LANCHONETE << " - Lanchonete" << endl
					<< ACESSORIOS << " - Acess�rios" << endl
					<< HIGIENE << " - Higiene" << endl
					<< "Digite: ";
				cin >> nTipo;
			} while(nTipo < 0 || nTipo > 3);
			if(nTipo == 0)
				break;
			// Pedir o valor da despesa
			cout << "Digite o valor da despesa: ";
			cin >> dValor;
			// Invocar o m�todo que lan�a a despesa....
			if(!objEscola.LancarDespesa(nPeriodo, nRaia, nTipo, dValor))
			{
				cout << "Erro ao lan�ar a despesa!" << endl;
				PAUSA;
				break;
			}
			cout << "Inserido com sucesso!" << endl;
			PAUSA;
			//	Analisar o resultado...
			break;

		case CONSULTAR_UM_DADO_ALUNO:			//consultando um dado aluno
			// chamar a fun��o PedirPeriodoValido e analisar o retorno.
			nPeriodo = PedirPeriodoValido("Consultar um dado aluno");
			//	Se o operador desistiu, voltar ao menu principal
			if (nPeriodo == 0)
			{
				cout << "Cancelado!" << endl;
				PAUSA;
				break;
			}
			//	Ficar em looping pedindo a raia do aluno que tem que ser v�lida ou
			//		zero se vai desistir....
			do
			{
				cout << "Digite a raia do aluno de 1 at� " << nQuantidadeRaias << "(0 - desiste): ";
				cin >> nRaia;
			} while(nRaia < 0 || nRaia > nQuantidadeRaias);
			if(nRaia == 0)
				break;
			// Invocar o m�todo que consulta um dado aluno....
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
				//n�o
				break;
			default:
				cout << "Op��o invalida!!!" << endl;
				PAUSA;
		}
	}
} // main
