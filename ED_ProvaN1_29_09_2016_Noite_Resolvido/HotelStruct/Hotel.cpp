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
	// loop para pedir um andar v�lido
	do
	{
		cout << "Andar entre 1 e " << QUANTIDADE_ANDARES << endl <<
			"Ou zero para cancelar a transa��o: ";
		cin >> *ptrAndar;					// pega o andar
		if(*ptrAndar == 0)					// cancelar?
			return false;					// indica que cancelou
	} while(*ptrAndar < 1 || *ptrAndar > QUANTIDADE_ANDARES);
	// loop para pedir um quarto v�lido
	do
	{
		cout << "Quarto entre 1 e " << QUANTIDADE_QUARTOS << endl << 
			"Ou zero para cancelar a transa��o: ";
		cin >> *ptrQuarto;
		if(*ptrQuarto == 0)					// cancelar?
			return false;					// indica que cancelou
	} while(*ptrQuarto < 1 || *ptrQuarto > QUANTIDADE_QUARTOS);
	return true;							// indica que tem andar e quarto digitado
}
//
// Fun��o principal
//
void main(void)
{
	int  i,									// indice gen�rico
		nCodServico,						// codigo do servi�o
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
	//
	SYSTEMTIME stTime;						// para buscar data e hora
	char vetNomesServicos[5][15] =	   {"Restaurante",
										"Lavanderia",
										"Bar",
										"Piscina",
										"Boate"};

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
				// 2 - Se retornou true indicando que foram informados andar e quarto v�lidos
				//	   invocar o m�todo que verifica se o quarto est� ocupado (VerificarQuartoLivre)
				// 3 - Se estiver ocupado exibir ao operador que o
				//		quarto est� ocupado e o nome do h�spede que est� ocupando o quarto, dar uma
				//		pausa para o operador poder ler e voltar ao menu.
				// 4 - Se n�o estiver ocupado Pedir o nome do h�spede considerando que tem nome e sobrenome
				// 5 - Invocar o m�todo CheckInHospede
				// 6 - Voltar ao menu
				if(!PedirAndarQuarto(&nAndarHotel, &nQuartoHotel, "Check-in de um h�spede")) // cancelou?
					break;										// volta ao menu
				// verificar se quarto livre
				if(objHotel.VerificarQuartoLivre(nAndarHotel, nQuartoHotel, &stQuarto)) // quarto ocupado?
				{	// quarto ocupado
					sprintf_s(cWork, sizeof(cWork),
						"\nAndar: %2d Quarto: %2d H�spede: %-30s\nQuarto ocupado!",
						stQuarto.nAndar, stQuarto.nQuarto, stQuarto.szNomeHospede);
					cout << cWork << endl;
					PAUSA;
					break;										// volta ao menu
				}
				// quarto est� livre
				cin.ignore(1, EOF);								// ignorar a tecla ENTER
				cout << "Nome: ";
				cin.getline(stQuarto.szNomeHospede, EXTEN_NOME, '\n');
				if(!objHotel.CheckInHospede(nAndarHotel, nQuartoHotel, stQuarto.szNomeHospede)) // problema?
				{
					cout << "Problema no check-in!" << endl;
				}
				else						// check-in foi OK
				{
					sprintf_s(cWork, sizeof(cWork),
						"\nAndar: %2d Quarto: %2d H�spede: %-30s\nDi�ria: %9.2f Check-in OK",
						stQuarto.nAndar, stQuarto.nQuarto, stQuarto.szNomeHospede,
						stQuarto.dValorDiaria);
					cout << cWork << endl;
				}
				PAUSA;
				break;						// para sair do switch e voltar ao menu
			case FAZER_CHECK_OUT:
				// <<<< 03 >>>>
				// 1 - Pedir o andar e o quarto da mesma forma que no item anterior indicando que a transa��o 
				//		� "Check-out"
				// 2 - Verificar se a transa��o foi cancelada e voltar ao menu
				// 3 - Verificar se o quarto est� ocupado e se estiver exibir o nome do h�spede e
				//		o total de di�rias do quarto
				// 4 - Pedir a confirma��o do operador com um S ou N
				//		Se for indicado 'S' ou 's' invocar o m�todo CheckOutHospede
				break;						// para sair do switch e voltar ao menu
			case LANCAR_DIARIA:
				// <<<< 05 >>>> 
				// 1 - Pedir a data e hora do sistema e apresentar ao operador
				// 2 - Confirmar com o operador se ele realmente deseja lan�ar as di�rias no hor�rio
				//		apresentado
				// 3 - Se o operador confirmar invocar o m�todo LancarDiarias
				// 4 - Caso o operador n�o confirme voltar ao menu.
				break;						// para sair do switch e voltar ao menu
			case LISTAR_UM_QUARTO:
				// <<<< 06 >>>> 
				// 1 - Pedir Andar e Quarto conforme itens anteriores
				// 2 - Verificar se o quarto est� ocupado passando o endere�o da struct stQuarto
				//		e se n�o estiver, avisar ao operador e voltar ao menu
				//		Se estiver ocupado o programa receber� na struct os dados do quarto que
				//			ser�o exibidos conforme layout abaixo
				// 3 - Se estiver ocupado listar os dados do quarto indicando nome do h�spede e valor da
				//		di�ria do quarto e o total de di�rias utilizando o sprintf_s
				//		Formato: 
				//				 Andar Quarto H�spede            Vlr.Di�ria Tot.Di�rias
				//				  A      Q    XXXXXXXXXXXXXXXXX  DDDDD.DD   TTTTTT.TT
				//
				break;						// para sair do switch e voltar ao menu
			case LANCAR_SERVICO:
				// <<<< 07 >>>> 
				// 1 - Pedir Andar e Quarto conforme itens anteriores
				// 2 - Verificar se o quarto est� ocupado passando o endere�o da struct stQuarto
				//		e se n�o estiver, avisar ao operador e voltar ao menu
				//		Se estiver ocupado o programa receber� na struct os dados do quarto que
				//			ser�o exibidos conforme layout abaixo
				// 3 - Se estiver ocupado listar os dados do quarto indicando nome do h�spede e valor da
				//		di�ria do quarto e o total de di�rias utilizando o sprintf_s
				//		Formato: 
				//				 Andar Quarto H�spede            Vlr.Di�ria Tot.Servi�os
				//				  A      Q    XXXXXXXXXXXXXXXXX  DDDDD.DD   TTTTTT.TT
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
				//  5 - Invocar o m�todo LancarServico
				if(!PedirAndarQuarto(&nAndarHotel, &nQuartoHotel, "Lan�ar Servi�o em um quarto")) // cancelou?
					break;										// volta ao menu
				// verificar se quarto livre
				if(objHotel.VerificarQuartoLivre(nAndarHotel, nQuartoHotel, &stQuarto)) // quarto ocupado?
				{	// quarto ocupado
					//				 Andar Quarto H�spede            Vlr.Di�ria Tot.Servi�os
					//				  A      Q    XXXXXXXXXXXXXXXXX  DDDDD.DD   TTTTTT.TT
					sprintf_s(cWork, sizeof(cWork),
						"Andar Quarto H�spede                       Vlr.Di�ria Tot.Servi�os");
					cout << cWork << endl;
					sprintf_s(cWork, sizeof(cWork),
						" %2d   %2d     %-30s %9.2f %9.2f",
						stQuarto.nAndar, stQuarto.nQuarto, stQuarto.szNomeHospede,
						stQuarto.dValorDiaria, stQuarto.dVlrServicos);
					cout << cWork << endl;
					// loop para pedir o servi�o
					do
					{
						cout << "\t\t\tServi�o prestado" << endl;
						cout << "\t" << RESTAURANTE << " - " << vetNomesServicos[0] << endl;
						cout << "\t" << LAVANDERIA << " - " << vetNomesServicos[1] << endl;
						cout << "\t" << BAR << " - " << vetNomesServicos[2] << endl;
						cout << "\t" << PISCINA << " - " << vetNomesServicos[3] << endl;
						cout << "\t" << BOATE << " - " << vetNomesServicos[4] << endl;
						cout << "\t0 - Cancelar o lan�amento do servi�o" << endl;
						cout << "\t\tSelecione: ";
						cin >> nCodServico;						// recebe o c�digo
					} while(nCodServico < 0 || nCodServico > BOATE);
					if(nCodServico == 0)
						break;									// volta ao menu
					cout << "\n\tValor do servi�o: ";
					cin >> dValor;								// recebe valor do servi�o
					if(!objHotel.LancarServico(nAndarHotel, nQuartoHotel, nCodServico, dValor)) //
					{	// sem mem�ria
						cout << "N�o tem mem�ria dispon�vel!" << endl;
					}
				}
				else
				{
					cout << "Quarto n�o est� ocupado!" << endl;
				}
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
