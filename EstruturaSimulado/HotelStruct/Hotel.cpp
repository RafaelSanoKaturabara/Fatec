// Hotel.cpp - Programa de Hotel para prova de Estrutura de Dados - 29/09/2016
// FATEC - Mogi das Cruzes
#include "Hotel.h"
// Fun��o que pede o andar e  quarto v�lido
//	Par�metros:
//		Entrada: int *ptrAndar - ponteiro de uma inteira que receber� o andar
//				 int *ptrQuarto - ponteiro de uma inteira que receber� o quarto dentro do andar
//				 char *ptrTransacao - ponteiro de um string que cont�m a transa��o que est� sendo
//					executada.
//		Retorno: bool - true - indica que foram informados o andar e o quarto v�lido
//						false - indica que foi informado um andar zero ou quarto zero para
//									cancelar a transa��o

bool	PedirAndarQuarto(int *ptrAndar, int *ptrQuarto, char *ptrTransacao)
{
	cout << "\n\t" << ptrTransacao << endl;				// exibe a transa��o que est� sendo executada
	do
	{
		cout << "Digite um andar v�lido ou zero para sair: ";
		cin >> *ptrAndar;
		if (*ptrAndar == 0)
		{
			cout << "Cancelado!" << endl;
			PAUSA;
			return false;
		}
	} while (*ptrAndar < 0 || *ptrAndar > QUANTIDADE_ANDARES);
	do
	{
		cout << "Digite um n�mero de quarto v�lido ou zero para sair: ";
		cin >> *ptrQuarto;
		if (*ptrQuarto == 0)
		{
			cout << "Cancelado!" << endl;
			PAUSA;
			return false;
		}
	} while (*ptrQuarto < 0 || *ptrQuarto > QUANTIDADE_QUARTOS);
	return true;							// para n�o dar erro
}
//
// Fun��o principal
//
void main(void)
{
	int  i,									// indice gen�rico
		nOpcao,								// op��o do menu em n�meros inteiros
		nQtdeAndares,						// para receber a quantidade de andares do hotel
		nQtdeQuartosPorAndar,				// para receber a quantidade de quartos por andar
		nAndarHotel,						// para receber o n�mero do andar
		nQuartoHotel;						// para receber o n�mero do quarto dentro do andar
	char cOpcaoOper,						// local para receber a op��o escolhida do menu
		cNomeHospede[41],					// local para receber o nome do h�spede do hotel
		cWork[200],							// para formata��o de sprintf
		cNomeAluno[] = "Preencher o seu nome";
	double dValor;							// local para receber o valor dos servi�os do hotel
	QUARTO stQuarto;						// para conter os dados de um quarto
	char vetNomesServicos[5][15] =	   {"Restaurante",
										"Lavanderia",
										"Bar",
										"Piscina",
										"Boate"};
	
	//
	SYSTEMTIME stTime;						// para buscar data e hora

	setlocale(LC_ALL, "portuguese_brazil");
	// comandos para estabelecer o numero de casas decimais
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);						// duas casas decimais
	// <<<<<<0>>>>>>> - Antes de entregar o Pen drive - renomear o diret�rio principal do projeto que
	// est� ED_ProvaN1_29_09_2016_Noite para ED_ProvaN1_SeuNomeComLetrasMai�sculasMin�sculas

	//
	// <<<<< 01 >>>>>>>	Instanciar a classe hotel e criar o objeto - isso j� est� codificado
	//
	clHotel objHotel;						// foi criado o objeto
	//
	while(true)								// loop infinito
	{
		LIMPAR_TELA;
		GetLocalTime(&stTime);
		sprintf_s(cWork, sizeof(cWork), 
			"\n\tFATEC-MC - Sistema de Hotel %02d/%02d/%04d �s %02d:%02d:%02d\n\t\tOperador: %s Turma: noite",
			stTime.wDay, stTime.wMonth, stTime.wYear,
			stTime.wHour, stTime.wMinute, stTime.wSecond,
			cNomeAluno);
		cout << cWork << endl;
		// Mostrar o menu de op��es para o operador
		cout << FAZER_CHECK_IN << " - Check-in de um hospede" << endl;
		cout << FAZER_CHECK_OUT << " - Check-out de um hospede" << endl;
		cout << LANCAR_SERVICO << " - Lan�ar servi�o em um dado quarto" << endl;
		cout << LANCAR_DIARIA << " - Lancar diarias em todos os quartos ocupados" << endl;
		cout << LISTAR_UM_QUARTO << " - Listar um quarto" << endl;
		cout << LISTAR_QUARTOS_OCUPADOS << " - Listar todos os quartos ocupados" << endl;
		cout << SAIR_DO_PROGRAMA << " - Sair do programa" << endl;
		cout << "\tSelecione: ";
		cin	 >> cOpcaoOper;					// op��o escolhida pelo operador
		cOpcaoOper = toupper(cOpcaoOper);	// converte para upper case a op��o escolhida
		switch(cOpcaoOper)					// avaliar a op��o que foi escolhida pelo operador
		{
			case FAZER_CHECK_IN:
				// <<<< 02 >>>>
				// 1 - Chamar a fun��o PedirAndarQuarto passando os endere�o de nAndarHotel para receber
				//		o n�mero do andar e o endere�o de nQuartoHotel para receber o n�mero do quarto no
				//			andar e indicar que a transa��o � "Check-in de h�spede"
				//		Se retornar false cancelar a transa��o e voltar ao menu
				if(!PedirAndarQuarto(&nAndarHotel, &nQuartoHotel, "Check-in de h�spede"))
					break;
				// 2 - Se retornou true indicando que foram informados andar e quarto v�lidos
				//	   invocar o m�todo que verifica se o quarto est� ocupado (VerificarQuartoLivre)
				if(objHotel.VerificarQuartoLivre(nAndarHotel, nQuartoHotel, &stQuarto))
				// 3 - Se estiver ocupado exibir ao operador que o
				//		quarto est� ocupado e o nome do h�spede que est� ocupando o quarto, dar uma
				//		pausa para o operador poder ler e voltar ao menu.
				{
					cout << "Quarto j� est� ocupado por: " << stQuarto.szNomeHospede << endl;
					PAUSA;
					break;
				}
				// 4 - Se n�o estiver ocupado Pedir o nome do h�spede considerando que tem nome e sobrenome
				cout << "Digite o nome do H�spede: ";
				cin.ignore(1,EOF);
				cin.getline(stQuarto.szNomeHospede, 30, '\n');
				// 5 - Invocar o m�todo CheckInHospede
				if(!objHotel.CheckInHospede(nAndarHotel, nQuartoHotel, stQuarto.szNomeHospede))
				{
					cout << "Erro!" << endl;
					PAUSA;
					break;
				}
				// 6 - Voltar ao menu
				cout << "Check In realizado com sucesso!" << endl;
				PAUSA;
				break;						// para sair do switch e voltar ao menu
			case FAZER_CHECK_OUT:
				// <<<< 03 >>>>
				// 1 - Pedir o andar e o quarto da mesma forma que no item anterior indicando que a transa��o 
				//		� "Check-out"
				if(!PedirAndarQuarto(&nAndarHotel, &nQuartoHotel, "Check-out"))
					break;
				// 2 - Verificar se a transa��o foi cancelada e voltar ao menu
				// 3 - Verificar se o quarto est� ocupado e se estiver exibir o nome do h�spede e
				//		o total de di�rias do quarto
				if(!objHotel.VerificarQuartoLivre(nAndarHotel, nQuartoHotel, &stQuarto))
					break;
				cout << "Quarto ocupado por: " << stQuarto.szNomeHospede << endl;
				// 4 - Pedir a confirma��o do operador com um S ou N
				//		Se for indicado 'S' ou 's' invocar o m�todo CheckOutHospede
				cout << "Deseja realmente realizar o check-out? (S/N):";
				cin >> cOpcaoOper;
				if(cOpcaoOper == 'S' || cOpcaoOper == 's')
				{
					if(objHotel.CheckOutHospede(nAndarHotel, nQuartoHotel))
					{
						cout << "Check-out realizado com sucesso!" << endl;
						PAUSA;
						break;
					}
					cout << "Quarto n�o possui ningu�m vazio!" << endl;
					PAUSA;
					break;
				}
				break;						// para sair do switch e voltar ao menu
			case LANCAR_DIARIA:
				// <<<< 05 >>>> 
				// 1 - Pedir a data e hora do sistema e apresentar ao operador
				GetLocalTime(&stTime);
				sprintf_s(cWork, "Data: %02d/%02d/%4d e Hora: %02d:%02d\nDeseja lan�ar todas as di�rias? (S/N):"
					, stTime.wDay, stTime.wMonth, stTime.wYear, stTime.wHour, stTime.wMinute);
				cout << cWork;
				// 2 - Confirmar com o operador se ele realmente deseja lan�ar as di�rias no hor�rio
				//		apresentad
				cin >> cOpcaoOper;
				if(cOpcaoOper = 'S' && cOpcaoOper != 's')
					break;
				// 3 - Se o operador confirmar invocar o m�todo LancarDiarias
				objHotel.LancarDiarias();
				// 4 - Caso o operador n�o confirme voltar ao menu.
				break;						// para sair do switch e voltar ao menu
			case LISTAR_UM_QUARTO:
				// <<<< 06 >>>> 
				// 1 - Pedir Andar e Quarto conforme itens anteriores]
				if(!PedirAndarQuarto(&nAndarHotel, &nQuartoHotel, "Listar um quarto"))
					break;
				// 2 - Verificar se o quarto est� ocupado passando o endere�o da struct stQuarto
				//		e se n�o estiver, avisar ao operador e voltar ao menu
				//		Se estiver ocupado o programa receber� na struct os dados do quarto que
				//			ser�o exibidos conforme layout abaixo
				if(!objHotel.VerificarQuartoLivre(nAndarHotel, nQuartoHotel, &stQuarto))
				{
					cout << "O quarto est� vazio!" << endl;
					PAUSA;
					break;
				}
				// 3 - Se estiver ocupado listar os dados do quarto indicando nome do h�spede e valor da
				//		di�ria do quarto, o total de di�rias, o total servi�os e total geral
				//		utilizando o sprintf_s
				//		Formato: 
				//	Andar Quarto H�spede            Vlr.Di�ria Tot.Di�rias Tot.Servi�os Tot.Geral
				//	  A      Q   XXXXXXXXXXXXXXXXX    DDDDD.DD TDTDTDTD.TD  TSTSTSTS.TS TTTTTT.TT
				//
				cout << "Andar Quarto H�spede            Vlr.Di�ria Tot.Di�rias Tot.Servi�os Tot.Geral" << endl;
				sprintf_s(cWork, "%3d   %4d   %-17s    %8.2f %11.2f  %11.2f %9.2f"
					, stQuarto.nAndar, stQuarto.nQuarto, stQuarto.szNomeHospede, stQuarto.dValorDiaria, stQuarto.dVlrTotDiarias
					, stQuarto.dVlrServicos, stQuarto.dVlrTotalGeral);
				cout << cWork << endl;
				PAUSA;
				break;						// para sair do switch e voltar ao menu
			case LANCAR_SERVICO:
				// <<<< 07 >>>> 
				// 1 - Pedir Andar e Quarto conforme itens anteriores
				if(!PedirAndarQuarto(&nAndarHotel, &nQuartoHotel, "Lan�ar Servi�os"))
					break;
				// 2 - Verificar se o quarto est� ocupado passando o endere�o da struct stQuarto
				//		e se n�o estiver, avisar ao operador e voltar ao menu
				//		Se estiver ocupado o programa receber� na struct os dados do quarto que
				//			ser�o exibidos conforme layout abaixo
				if(!objHotel.VerificarQuartoLivre(nAndarHotel, nQuartoHotel, &stQuarto))
				{
					cout << "O quarto est� vazio!" << endl;
					PAUSA;
					break;
				}
				// 3 - Se estiver ocupado listar os dados do quarto indicando nome do h�spede e valor da
				//		di�ria do quarto e o total de di�rias utilizando o sprintf_s
				//		Formato: 
				//	Andar Quarto H�spede            Vlr.Di�ria Tot.Di�rias Tot.Servi�os Tot.Geral
				//	  A      Q    XXXXXXXXXXXXXXXXX  DDDDD.DD  TDTDTDTD.TD TSTSTSTS.TS  TTTTTT.TT
				cout << "Andar Quarto H�spede            Vlr.Di�ria Tot.Di�rias Tot.Servi�os Tot.Geral" << endl;
				sprintf_s(cWork, "%3d   %4d   %-17s    %8.2f %11.2f  %11.2f %9.2f"
					, stQuarto.nAndar, stQuarto.nQuarto, stQuarto.szNomeHospede, stQuarto.dValorDiaria, stQuarto.dVlrTotDiarias
					, stQuarto.dVlrServicos, stQuarto.dVlrTotalGeral);
				cout << cWork << endl;
				//	4 - Pedir o c�digo do servi�o executado e seu valor no
				//		formato:
				//			1 - Restaurante
				//			2 - Lavanderia
				//			3 - Bar		
				//			4 - Piscina	
				//			5 - Boate
				//			0 - Cancelar a transa��o
				//				Selecione: X
				//		O valor informado tem que ser um c�digo v�lido
				//			Se o c�digo for 0(zero) - cancelar a transa��o
				//			Pedir o valor:
				//				Valor: VVVVVV.VV
				do
				{
					cout << RESTAURANTE << " - Restaurante" << endl
						<< LAVANDERIA << " - Lavanderia" << endl
						<< BAR << " - Bar" << endl
						<< PISCINA << " - Piscina" << endl
						<< BOATE << " - Boate" << endl
						<< "0 - Cancelar a transa��o" << endl
						<< "\tSelecione: ";
					cin >> nOpcao;
				}while(nOpcao < 0 || nOpcao > sizeof(vetNomesServicos) / 15);
				if(nOpcao == 0)
						break;
				cout << "Digite o valor so servi�o R$: ";
				cin >> dValor;
				//  5 - Invocar o m�todo LancarServico
				if(!objHotel.LancarServico(nAndarHotel, nQuartoHotel, nOpcao, dValor))
				{
					cout << "Sem mem�ria para a grava��o do servi�o!" << endl;
					PAUSA;
					break;
				}
				cout << "Gravado com sucesso!" << endl;
				PAUSA;
				break;
			case LISTAR_QUARTOS_OCUPADOS:
				// <<<< 08 >>>>>
				//	1 - Invocar o m�todo ListarTodosQuartos
				objHotel.ListarTodosQuartos();
				break;
			case SAIR_DO_PROGRAMA:
				cout << "\nDeseja sair realmente? (S ou N): ";
				cin >> cOpcaoOper;
				if(cOpcaoOper == 'S' || cOpcaoOper == 's')		// sair realmente?
					return;
				break;						// para sair do switch e decidir se vai sair realmente
			default:
				// Avisar que foi escolhida uma op��o errada
				cout << "\nOpcao inv�lida!" << endl;
				PAUSA;
		} // switch
	} // while(true)
} // main
