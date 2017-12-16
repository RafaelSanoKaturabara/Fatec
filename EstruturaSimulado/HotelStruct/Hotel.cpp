// Hotel.cpp - Programa de Hotel para prova de Estrutura de Dados - 29/09/2016
// FATEC - Mogi das Cruzes
#include "Hotel.h"
// Função que pede o andar e  quarto válido
//	Parâmetros:
//		Entrada: int *ptrAndar - ponteiro de uma inteira que receberá o andar
//				 int *ptrQuarto - ponteiro de uma inteira que receberá o quarto dentro do andar
//				 char *ptrTransacao - ponteiro de um string que contém a transação que está sendo
//					executada.
//		Retorno: bool - true - indica que foram informados o andar e o quarto válido
//						false - indica que foi informado um andar zero ou quarto zero para
//									cancelar a transação

bool	PedirAndarQuarto(int *ptrAndar, int *ptrQuarto, char *ptrTransacao)
{
	cout << "\n\t" << ptrTransacao << endl;				// exibe a transação que está sendo executada
	do
	{
		cout << "Digite um andar válido ou zero para sair: ";
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
		cout << "Digite um número de quarto válido ou zero para sair: ";
		cin >> *ptrQuarto;
		if (*ptrQuarto == 0)
		{
			cout << "Cancelado!" << endl;
			PAUSA;
			return false;
		}
	} while (*ptrQuarto < 0 || *ptrQuarto > QUANTIDADE_QUARTOS);
	return true;							// para não dar erro
}
//
// Função principal
//
void main(void)
{
	int  i,									// indice genérico
		nOpcao,								// opção do menu em números inteiros
		nQtdeAndares,						// para receber a quantidade de andares do hotel
		nQtdeQuartosPorAndar,				// para receber a quantidade de quartos por andar
		nAndarHotel,						// para receber o número do andar
		nQuartoHotel;						// para receber o número do quarto dentro do andar
	char cOpcaoOper,						// local para receber a opção escolhida do menu
		cNomeHospede[41],					// local para receber o nome do hóspede do hotel
		cWork[200],							// para formatação de sprintf
		cNomeAluno[] = "Preencher o seu nome";
	double dValor;							// local para receber o valor dos serviços do hotel
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
	// <<<<<<0>>>>>>> - Antes de entregar o Pen drive - renomear o diretório principal do projeto que
	// está ED_ProvaN1_29_09_2016_Noite para ED_ProvaN1_SeuNomeComLetrasMaiúsculasMinúsculas

	//
	// <<<<< 01 >>>>>>>	Instanciar a classe hotel e criar o objeto - isso já está codificado
	//
	clHotel objHotel;						// foi criado o objeto
	//
	while(true)								// loop infinito
	{
		LIMPAR_TELA;
		GetLocalTime(&stTime);
		sprintf_s(cWork, sizeof(cWork), 
			"\n\tFATEC-MC - Sistema de Hotel %02d/%02d/%04d às %02d:%02d:%02d\n\t\tOperador: %s Turma: noite",
			stTime.wDay, stTime.wMonth, stTime.wYear,
			stTime.wHour, stTime.wMinute, stTime.wSecond,
			cNomeAluno);
		cout << cWork << endl;
		// Mostrar o menu de opções para o operador
		cout << FAZER_CHECK_IN << " - Check-in de um hospede" << endl;
		cout << FAZER_CHECK_OUT << " - Check-out de um hospede" << endl;
		cout << LANCAR_SERVICO << " - Lançar serviço em um dado quarto" << endl;
		cout << LANCAR_DIARIA << " - Lancar diarias em todos os quartos ocupados" << endl;
		cout << LISTAR_UM_QUARTO << " - Listar um quarto" << endl;
		cout << LISTAR_QUARTOS_OCUPADOS << " - Listar todos os quartos ocupados" << endl;
		cout << SAIR_DO_PROGRAMA << " - Sair do programa" << endl;
		cout << "\tSelecione: ";
		cin	 >> cOpcaoOper;					// opção escolhida pelo operador
		cOpcaoOper = toupper(cOpcaoOper);	// converte para upper case a opção escolhida
		switch(cOpcaoOper)					// avaliar a opção que foi escolhida pelo operador
		{
			case FAZER_CHECK_IN:
				// <<<< 02 >>>>
				// 1 - Chamar a função PedirAndarQuarto passando os endereço de nAndarHotel para receber
				//		o número do andar e o endereço de nQuartoHotel para receber o número do quarto no
				//			andar e indicar que a transação é "Check-in de hóspede"
				//		Se retornar false cancelar a transação e voltar ao menu
				if(!PedirAndarQuarto(&nAndarHotel, &nQuartoHotel, "Check-in de hóspede"))
					break;
				// 2 - Se retornou true indicando que foram informados andar e quarto válidos
				//	   invocar o método que verifica se o quarto está ocupado (VerificarQuartoLivre)
				if(objHotel.VerificarQuartoLivre(nAndarHotel, nQuartoHotel, &stQuarto))
				// 3 - Se estiver ocupado exibir ao operador que o
				//		quarto está ocupado e o nome do hóspede que está ocupando o quarto, dar uma
				//		pausa para o operador poder ler e voltar ao menu.
				{
					cout << "Quarto já está ocupado por: " << stQuarto.szNomeHospede << endl;
					PAUSA;
					break;
				}
				// 4 - Se não estiver ocupado Pedir o nome do hóspede considerando que tem nome e sobrenome
				cout << "Digite o nome do Hóspede: ";
				cin.ignore(1,EOF);
				cin.getline(stQuarto.szNomeHospede, 30, '\n');
				// 5 - Invocar o método CheckInHospede
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
				// 1 - Pedir o andar e o quarto da mesma forma que no item anterior indicando que a transação 
				//		é "Check-out"
				if(!PedirAndarQuarto(&nAndarHotel, &nQuartoHotel, "Check-out"))
					break;
				// 2 - Verificar se a transação foi cancelada e voltar ao menu
				// 3 - Verificar se o quarto está ocupado e se estiver exibir o nome do hóspede e
				//		o total de diárias do quarto
				if(!objHotel.VerificarQuartoLivre(nAndarHotel, nQuartoHotel, &stQuarto))
					break;
				cout << "Quarto ocupado por: " << stQuarto.szNomeHospede << endl;
				// 4 - Pedir a confirmação do operador com um S ou N
				//		Se for indicado 'S' ou 's' invocar o método CheckOutHospede
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
					cout << "Quarto não possui ninguém vazio!" << endl;
					PAUSA;
					break;
				}
				break;						// para sair do switch e voltar ao menu
			case LANCAR_DIARIA:
				// <<<< 05 >>>> 
				// 1 - Pedir a data e hora do sistema e apresentar ao operador
				GetLocalTime(&stTime);
				sprintf_s(cWork, "Data: %02d/%02d/%4d e Hora: %02d:%02d\nDeseja lançar todas as diárias? (S/N):"
					, stTime.wDay, stTime.wMonth, stTime.wYear, stTime.wHour, stTime.wMinute);
				cout << cWork;
				// 2 - Confirmar com o operador se ele realmente deseja lançar as diárias no horário
				//		apresentad
				cin >> cOpcaoOper;
				if(cOpcaoOper = 'S' && cOpcaoOper != 's')
					break;
				// 3 - Se o operador confirmar invocar o método LancarDiarias
				objHotel.LancarDiarias();
				// 4 - Caso o operador não confirme voltar ao menu.
				break;						// para sair do switch e voltar ao menu
			case LISTAR_UM_QUARTO:
				// <<<< 06 >>>> 
				// 1 - Pedir Andar e Quarto conforme itens anteriores]
				if(!PedirAndarQuarto(&nAndarHotel, &nQuartoHotel, "Listar um quarto"))
					break;
				// 2 - Verificar se o quarto está ocupado passando o endereço da struct stQuarto
				//		e se não estiver, avisar ao operador e voltar ao menu
				//		Se estiver ocupado o programa receberá na struct os dados do quarto que
				//			serão exibidos conforme layout abaixo
				if(!objHotel.VerificarQuartoLivre(nAndarHotel, nQuartoHotel, &stQuarto))
				{
					cout << "O quarto está vazio!" << endl;
					PAUSA;
					break;
				}
				// 3 - Se estiver ocupado listar os dados do quarto indicando nome do hóspede e valor da
				//		diária do quarto, o total de diárias, o total serviços e total geral
				//		utilizando o sprintf_s
				//		Formato: 
				//	Andar Quarto Hóspede            Vlr.Diária Tot.Diárias Tot.Serviços Tot.Geral
				//	  A      Q   XXXXXXXXXXXXXXXXX    DDDDD.DD TDTDTDTD.TD  TSTSTSTS.TS TTTTTT.TT
				//
				cout << "Andar Quarto Hóspede            Vlr.Diária Tot.Diárias Tot.Serviços Tot.Geral" << endl;
				sprintf_s(cWork, "%3d   %4d   %-17s    %8.2f %11.2f  %11.2f %9.2f"
					, stQuarto.nAndar, stQuarto.nQuarto, stQuarto.szNomeHospede, stQuarto.dValorDiaria, stQuarto.dVlrTotDiarias
					, stQuarto.dVlrServicos, stQuarto.dVlrTotalGeral);
				cout << cWork << endl;
				PAUSA;
				break;						// para sair do switch e voltar ao menu
			case LANCAR_SERVICO:
				// <<<< 07 >>>> 
				// 1 - Pedir Andar e Quarto conforme itens anteriores
				if(!PedirAndarQuarto(&nAndarHotel, &nQuartoHotel, "Lançar Serviços"))
					break;
				// 2 - Verificar se o quarto está ocupado passando o endereço da struct stQuarto
				//		e se não estiver, avisar ao operador e voltar ao menu
				//		Se estiver ocupado o programa receberá na struct os dados do quarto que
				//			serão exibidos conforme layout abaixo
				if(!objHotel.VerificarQuartoLivre(nAndarHotel, nQuartoHotel, &stQuarto))
				{
					cout << "O quarto está vazio!" << endl;
					PAUSA;
					break;
				}
				// 3 - Se estiver ocupado listar os dados do quarto indicando nome do hóspede e valor da
				//		diária do quarto e o total de diárias utilizando o sprintf_s
				//		Formato: 
				//	Andar Quarto Hóspede            Vlr.Diária Tot.Diárias Tot.Serviços Tot.Geral
				//	  A      Q    XXXXXXXXXXXXXXXXX  DDDDD.DD  TDTDTDTD.TD TSTSTSTS.TS  TTTTTT.TT
				cout << "Andar Quarto Hóspede            Vlr.Diária Tot.Diárias Tot.Serviços Tot.Geral" << endl;
				sprintf_s(cWork, "%3d   %4d   %-17s    %8.2f %11.2f  %11.2f %9.2f"
					, stQuarto.nAndar, stQuarto.nQuarto, stQuarto.szNomeHospede, stQuarto.dValorDiaria, stQuarto.dVlrTotDiarias
					, stQuarto.dVlrServicos, stQuarto.dVlrTotalGeral);
				cout << cWork << endl;
				//	4 - Pedir o código do serviço executado e seu valor no
				//		formato:
				//			1 - Restaurante
				//			2 - Lavanderia
				//			3 - Bar		
				//			4 - Piscina	
				//			5 - Boate
				//			0 - Cancelar a transação
				//				Selecione: X
				//		O valor informado tem que ser um código válido
				//			Se o código for 0(zero) - cancelar a transação
				//			Pedir o valor:
				//				Valor: VVVVVV.VV
				do
				{
					cout << RESTAURANTE << " - Restaurante" << endl
						<< LAVANDERIA << " - Lavanderia" << endl
						<< BAR << " - Bar" << endl
						<< PISCINA << " - Piscina" << endl
						<< BOATE << " - Boate" << endl
						<< "0 - Cancelar a transação" << endl
						<< "\tSelecione: ";
					cin >> nOpcao;
				}while(nOpcao < 0 || nOpcao > sizeof(vetNomesServicos) / 15);
				if(nOpcao == 0)
						break;
				cout << "Digite o valor so serviço R$: ";
				cin >> dValor;
				//  5 - Invocar o método LancarServico
				if(!objHotel.LancarServico(nAndarHotel, nQuartoHotel, nOpcao, dValor))
				{
					cout << "Sem memória para a gravação do serviço!" << endl;
					PAUSA;
					break;
				}
				cout << "Gravado com sucesso!" << endl;
				PAUSA;
				break;
			case LISTAR_QUARTOS_OCUPADOS:
				// <<<< 08 >>>>>
				//	1 - Invocar o método ListarTodosQuartos
				objHotel.ListarTodosQuartos();
				break;
			case SAIR_DO_PROGRAMA:
				cout << "\nDeseja sair realmente? (S ou N): ";
				cin >> cOpcaoOper;
				if(cOpcaoOper == 'S' || cOpcaoOper == 's')		// sair realmente?
					return;
				break;						// para sair do switch e decidir se vai sair realmente
			default:
				// Avisar que foi escolhida uma opção errada
				cout << "\nOpcao inválida!" << endl;
				PAUSA;
		} // switch
	} // while(true)
} // main
