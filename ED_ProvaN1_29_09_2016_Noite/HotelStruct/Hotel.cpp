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
	return true;							// para não dar erro
}
//
// Função principal
//
void main(void)
{
	int  i,									// indice genérico
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
				//				 Andar Quarto Hóspede            Vlr.Diária Tot.Diárias
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
				char vetNomesServicos[5][15] =	   {"Restaurante",
													"Lavanderia",
													"Bar",
													"Piscina",
													"Boate"};

				break;
			case LISTAR_QUARTOS_OCUPADOS:
				// <<<< 08 >>>>>
				//	1 - Invocar o método ListarTodosQuartos
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
