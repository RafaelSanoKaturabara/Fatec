// Prova N1 - Estrutura de Dados - 06/04/2017 - Turma da Tarde
// FATEC-MC - JCB - Vers�o 0.0
#include "Restaurante.h"

// Fun��o que pede uma mesa v�lida
// Esta fun��o vai ficar em loop at� o operador informar um n�mero 
// de mesa v�lido
//	Par�metros:
//		Entrada: char *ptrNomeAcao - nome da op��o que est� sendo executada
//		Retorno - int - o n�mero v�lido da mesa ou zero se o operador desistiu
int PedirMesaValida(char *ptrNomeAcao)
{
	int nMesa;								// para receber o n�mero da mesa
	cout << "\t\tA��o: " << ptrNomeAcao << endl << endl;
	do
	{
		cout << "N�mero da mesa entre 1 e " << QTDE_MESAS << endl
			<< "Ou zero para desistir: ";
		cin >> nMesa;
	} while(nMesa < 0 || nMesa > QTDE_MESAS);
	return nMesa;							// retorna a mesa ou zero na desist�ncia
}

void main(void)
{
	int nNumMesa,							// para receber o n�mero da mesa
		nQtdePessoas,						// quantidade de pessoas � mesa
		nCodProduto,						// produto servido � mesa
		nQtdeProduto;						// quantidade do produto sendo servido
	PRODUTO stProduto;						// para receber os dados de um produto
	MESA stMesa;							// para receber os dados de uma mesa
	char cOpcao,							// Op��o de escolha do operador
		cNomeAluno[] = "Digitar nome do aluno",	// informar o seu nome
		cRA[] = "Informar o RA do aluno",		// informar o seu RA
		cWork[100];							// �rea de trabalho
	SYSTEMTIME stTime;						// struct para buscar data e hora do sistema
	// instanciar a classe restaurante
	clRestaurante objRestaurante;			// criar o objeto restaurante
	setlocale(LC_ALL, "portuguese_brazil"); // para aceitar s�mbolos gr�ficos do Brasil
	//
	// para tratamento do ponto decimal
	//
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);
	while(true)						// loop infinito
	{
		LIMPAR_TELA;
		GetLocalTime(&stTime);		// buscar data e hora do sistema
		// formatar o cabe�alho do menu
		sprintf_s(cWork, sizeof(cWork),
			"\n\tRestaurante FATEC-MC - %02d/%02d/%04d %02d:%02d:%02d %s",
			stTime.wDay,
			stTime.wMonth,
			stTime.wYear,
			stTime.wHour,
			stTime.wMinute,
			stTime.wSecond,
			VERSAO);
		cout << cWork << endl;
		cout << "\tAluno: " << cNomeAluno << " RA: " << cRA << " Turma:" << TURMA << endl << endl;
		cout << OCUPAR_MESA << " - Ocupar uma mesa" << endl;
		cout << SERVIR_PRODUTO_MESA << " - Servir produto em mesa ocupada" << endl;
		cout << FECHAR_MESA << " - Fechar mesa que est� ocupada" << endl;
		cout << CONSULTAR_MESA << " - Consultar mesa" << endl;
		cout << LIBERAR_MESA << " - Liberar mesa" << endl;
		cout << SAIR_DO_PROGRAMA << " - Sair do programa" << endl;
		cout << "\tSelecione: ";
		cin >> cOpcao;						// pegar a op��o operador
		cOpcao = toupper(cOpcao);			// converter op��o para mai�scula
		switch(cOpcao)						// avaliar a op��o escolhida
		{
			case OCUPAR_MESA:
				// chamar a fun��o que pede uma mesa v�lida (est� definida antes da main)
				// verificar se o operador desistiu da a��o a ser executada
				// chamar o m�todo que verifica se mesa est� ocupada
				// Se a mesa estiver ocupada exibir os seus dados dar pausa e sair do
				//	switch (Indicar mesa ocupada, quantas pessoas, desde que hora e o total
				//	at� agora
				// Se a mesa estiver livre, pedir qtde de pessoas na mesa e chamar o m�todo
				// que ocupa a mesa. Analisar o resultado
				nNumMesa = PedirMesaValida("Ocupar uma mesa");
				if(nNumMesa == 0)				// cancelou a transa��o
					break;						// volta ao menu se desistiu...

				// verificar se a mesa est� ocupada invocando o m�todo
				// VerificaSeMesaOcupada e se a mesa estiver ocupada
				if(objRestaurante.VerificaSeMesaOcupada(nNumMesa, &stMesa))
				// exibir os dados da mesa: n�mero da mesa, qtde de pessoas 
				//	hora e minuto da ocupa��o total gasto na mesa com sprintf_s
				//	dar uma pausa e voltar ao menu
				{
					sprintf_s(cWork, "Mesa: %02d Valor total: R$%5.2f \nPossui: %2d pessoas Ocupada em: %02d:%02d", nNumMesa, stMesa.dValorTotal
						, stMesa.nQtdePessoas, stMesa.stHoraOcupacao.nHora
						, stMesa.stHoraOcupacao.nMinuto);
					cout << cWork << endl;
					PAUSA;
					break;
				}
				// Pedir a quantidade de pessoas na mesa e 
				cout << "Digite a quantidade de pessoas na mesa: ";
				cin >> stMesa.nQtdePessoas;
				// invocar o m�todo OcuparMesa e analisar o resultado
				if(objRestaurante.OcuparMesa(nNumMesa, stMesa.nQtdePessoas))
				{
					cout << "Mesa ocupada com sucesso!" << endl;
					PAUSA;
					break;
				}
				cout << "Mesa n�o estava vazia!Opera��o cancelada!" << endl;
				PAUSA;
				// e voltar ao menu
				break;

			case SERVIR_PRODUTO_MESA:
				// chamar a fun��o que pede uma mesa v�lida (est� definida antes da main)
				nNumMesa = PedirMesaValida("Servir produto na mesa");
				// verificar se o operador desistiu da a��o a ser executada				
				if(nNumMesa == 0)				// cancelou a transa��o
					break;						// volta ao menu se desistiu...
				// chamar o m�todo que verifica se mesa est� ocupada.
				if(!objRestaurante.VerificaSeMesaOcupada(nNumMesa, &stMesa))
				// Se a mesa estiver livre avisar ao operador e sair do switch e voltar ao menu
				{
					cout << "A mesa " << nNumMesa << " n�o est� ocupada!" << endl;
					PAUSA;
					break;
				}
				// Pedir o c�digo do produto e chamar o m�todo que verifica se produto
				// existe e receber os dados do produto.
				do
				{
					cout << "Digite o c�digo do produto ou zero para cancelar: ";
					cin >> nCodProduto;
				// Se operador digitar 0, cancelar a a��o...
					if(nCodProduto == 0)
						break;
				}while(nCodProduto < 1 || nCodProduto > QTDE_PRODUTOS);				
				// Exibir descri��o do produto e pedir quantidade e se for zero cancelar a a��o.
				if(!objRestaurante.InformaDadosProduto(nCodProduto, &stProduto))
				{
					cout << "C�digo de produto inv�lido!" << endl;
					PAUSA;
					break;
				}
				do
				{
					cout << stProduto.cDescricao << ". Digite a quantidade do produto ou zero para sair: ";
					cin >> nQtdeProduto;
					if(nQtdeProduto == 0)
						break;
				}while (nQtdeProduto < 0);				
				// Chamar o m�todo que insere o produto na lista ligada da mesa
				if(objRestaurante.InsereNovoProdutoNaMesa(nNumMesa, nCodProduto, nQtdeProduto))
				// Codificar

				break;							// volta ao menu
			case FECHAR_MESA:
				// chamar a fun��o que pede uma mesa v�lida (est� definida antes da main)
				// verificar se o operador desistiu da a��o a ser executada
				// chamar o m�todo que verifica se mesa est� ocupada.
				// Se a mesa estiver livre avisar ao operador e sair do switch
				// Invocar o m�todo que faz o fechamento da mesa
				// Codificar

				break;
			case CONSULTAR_MESA:
				// chamar a fun��o que pede uma mesa v�lida (est� definida antes da main)
				// verificar se o operador desistiu da a��o a ser executada
				// chamar o m�todo que verifica se mesa est� ocupada.
				// Se a mesa estiver livre avisar ao operador e sair do switch
				// Se a mesa estiver ocupada os seus dados vieram para a struct cujo endere�o
				// foi passado
				// Mostrar quantas pessoas est�o ocupando e qual � o total da mesa e hora da
				//	ocupa��o da mesa
				// Codificar

				break;
			case LIBERAR_MESA:
				// chamar a fun��o que pede uma mesa v�lida (est� definida antes da main)
				// verificar se o operador desistiu da a��o a ser executada
				// chamar o m�todo que verifica se mesa est� ocupada.
				// Se a mesa estiver livre avisar ao operador e sair do switch
				// Invocar o m�todo que libera a mesa
				// Codificar
				break;
			case SAIR_DO_PROGRAMA:
				cout << "\n\tVai sair do programa realmente? (S ou N): ";
				cin >> cOpcao;
				if(cOpcao == 's' || cOpcao == 'S')
					return;					// sai fora do programa
				break;
			default:
				cout << "\n\tDigite uma op��o v�lida!" << endl << "\t";
				PAUSA;
				LIMPAR_TELA;
		} // switch
	} // while (true)
} // main