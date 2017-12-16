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
	// loop para pedir um andar válido
	do
	{
		cout << "Andar entre 1 e " << QUANTIDADE_ANDARES << endl <<
			"Ou zero para cancelar a transação: ";
		cin >> *ptrAndar;					// recebe o andar
		if(*ptrAndar == 0)					// cancelar a transação?
			return false;					// indica que cancelou
	} while(*ptrAndar < 1 || *ptrAndar > QUANTIDADE_ANDARES);
	// loop para pedir um quarto válido
	do
	{
		cout << "Quarto entre 1 e " << QUANTIDADE_QUARTOS << endl <<
			"Ou zero para cancelar a transação: ";
		cin >> *ptrQuarto;					// recebe o quarto
		if(*ptrQuarto == 0)					// cancelou a transação?
			return false;					// avisa que cancelou
	} while(*ptrQuarto < 1 || *ptrQuarto > QUANTIDADE_QUARTOS);
	return true;							// indica que tem andar e quarto
}
//
// Função principal
//
void main(void)
{
	int  i,									// indice genérico
		nCodServico,						// código do serviço
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
				// 2 - Se retornou true indicando que foram informados andar e quarto válidos
				//	   invocar o método que verifica se o quarto está ocupado (VerificarQuartoLivre)
				// 3 - Se estiver ocupado exibir ao operador que o
				//		quarto está ocupado e o nome do hóspede que está ocupando o quarto, dar uma
				//		pausa para o operador poder ler e voltar ao menu.
				// 4 - Se não estiver ocupado Pedir o nome do hóspede considerando que tem nome e sobrenome
				// 5 - Invocar o método CheckInHospede
				// 6 - Voltar ao menu
				if(!PedirAndarQuarto(&nAndarHotel, &nQuartoHotel, "Check-in de hóspede"))
					break;										// volta ao menu
				// verificar se o quarto está ocupado
				if(objHotel.VerificarQuartoLivre(nAndarHotel, nQuartoHotel, &stQuarto)) // quarto ocupado?
				{	// o quarto está ocupado
					sprintf_s(cWork, sizeof(cWork),
						"\nAndar:%2d Quarto:%2d Hóspede:%-30s\nQuarto está ocupado!",
						stQuarto.nAndar, stQuarto.nQuarto, stQuarto.szNomeHospede);
					cout << cWork << endl;
					PAUSA;
					break;										// volta ao menu
				}
				cin.ignore(1, EOF);							// ignora a tecla Enter anterior
				cout << "Nome: ";
				cin.getline(stQuarto.szNomeHospede, EXTEN_NOME, '\n'); // pega nome e sobrenome
				if(!objHotel.CheckInHospede(nAndarHotel, nQuartoHotel, stQuarto.szNomeHospede)) 
				{	// houve problema no check-in
					cout << "Problema no check-in!" << endl;
					PAUSA;
				}
				else
				{
					sprintf_s(cWork, sizeof(cWork),
						"\nCheck-in no Andar:%2d Quarto:%2d Hóspede:%-30s\nValor Diária:%9.2f",
						stQuarto.nAndar, stQuarto.nQuarto, stQuarto.szNomeHospede, 
						stQuarto.dValorDiaria);
					cout << cWork << endl;
					PAUSA;
				}
				break;						// para sair do switch e voltar ao menu
			case FAZER_CHECK_OUT:
				// <<<< 03 >>>>
				// 1 - Pedir o andar e o quarto da mesma forma que no item anterior indicando que a transação 
				//		é "Check-out"
				// 2 - Verificar se a transação foi cancelada e voltar ao menu
				// 3 - Verificar se o quarto está ocupado e se estiver exibir o nome do hóspede e
				//		o total de diárias do quarto
				// 4 - Pedir a confirmação do operador com um S ou N
				//		Se for indicado 'S' ou 's' invocar o método CheckOutHospede
				break;						// para sair do switch e voltar ao menu
			case LANCAR_DIARIA:
				// <<<< 05 >>>> 
				// 1 - Pedir a data e hora do sistema e apresentar ao operador
				// 2 - Confirmar com o operador se ele realmente deseja lançar as diárias no horário
				//		apresentado
				// 3 - Se o operador confirmar invocar o método LancarDiarias
				// 4 - Caso o operador não confirme voltar ao menu.
				break;						// para sair do switch e voltar ao menu
			case LISTAR_UM_QUARTO:
				// <<<< 06 >>>> 
				// 1 - Pedir Andar e Quarto conforme itens anteriores
				// 2 - Verificar se o quarto está ocupado passando o endereço da struct stQuarto
				//		e se não estiver, avisar ao operador e voltar ao menu
				//		Se estiver ocupado o programa receberá na struct os dados do quarto que
				//			serão exibidos conforme layout abaixo
				// 3 - Se estiver ocupado listar os dados do quarto indicando nome do hóspede e valor da
				//		diária do quarto e o total de diárias utilizando o sprintf_s
				//		Formato: 
				//				 Andar Quarto Hóspede            Vlr.Diária Tot.Diárias
				//				  A      Q    XXXXXXXXXXXXXXXXX  DDDDD.DD   TTTTTT.TT
				//
				break;						// para sair do switch e voltar ao menu
			case LANCAR_SERVICO:
				// <<<< 07 >>>> 
				// 1 - Pedir Andar e Quarto conforme itens anteriores
				// 2 - Verificar se o quarto está ocupado passando o endereço da struct stQuarto
				//		e se não estiver, avisar ao operador e voltar ao menu
				//		Se estiver ocupado o programa receberá na struct os dados do quarto que
				//			serão exibidos conforme layout abaixo
				// 3 - Se estiver ocupado listar os dados do quarto indicando nome do hóspede e valor da
				//		diária do quarto e o total de diárias utilizando o sprintf_s
				//		Formato: 
				//				 Andar Quarto Hóspede            Vlr.Diária Tot.Serviços
				//				  A      Q    XXXXXXXXXXXXXXXXX  DDDDD.DD   TTTTTT.TT
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
				//  5 - Invocar o método LancarServico
				if(!PedirAndarQuarto(&nAndarHotel, &nQuartoHotel, "Lançar serviço em um quarto"))
					break;										// volta ao menu
				// verificar se o quarto está ocupado
				if(objHotel.VerificarQuartoLivre(nAndarHotel, nQuartoHotel, &stQuarto)) // quarto ocupado?
				{	// o quarto está ocupado
					LIMPAR_TELA;
					sprintf_s(cWork, sizeof(cWork),
						"Andar Quarto Hóspede			            Vlr.Diária Vlr.Tot.Serviços");
					cout << cWork << endl;
					sprintf_s(cWork, sizeof(cWork),
						"  %2d   %2d    %-30s          %9.2f      %9.2f",
						stQuarto.nAndar, stQuarto.nQuarto, stQuarto.szNomeHospede,
						stQuarto.dValorDiaria, stQuarto.dVlrServicos);
					cout << cWork << endl;
					do
					{
						cout << "\n\t\tServiços do hotel" << endl;
						cout << "\t" << RESTAURANTE << " - " << vetNomesServicos[0] << endl;
						cout << "\t" << LAVANDERIA << " - " << vetNomesServicos[1] << endl;
						cout << "\t" << BAR << " - " << vetNomesServicos[2] << endl;
						cout << "\t" << PISCINA << " - " << vetNomesServicos[3] << endl;
						cout << "\t" << BOATE << " - " << vetNomesServicos[4] << endl;
						cout << "\t0 - Cancelar o lançamento do serviço" << endl;
						cout << "\t\tSelecione: ";
						cin >> nCodServico;						// recebe o serviço
					} while(nCodServico < 0 || 
						nCodServico > BOATE);
					if(nCodServico == 0)					// cancelar?
						break;								// volta ao menu
					cout << "Valor do serviço: ";
					cin >> dValor;								// recebe o valor do serviço
					if(!objHotel.LancarServico(nAndarHotel, nQuartoHotel, 
						nCodServico, dValor))					// sem memória
					{
						cout << "Sem memória disponível!" << endl;
						PAUSA;
					}
					break;										// volta ao menu
				}
				else
				{
					cout << "Quarto está livre!" << endl;
					PAUSA;
				}
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
