// Prova B1 - Estrutura de Dados - 12/04/2012 - Turma da Noite
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
		sprintf(cWork, "\tFATEC-MC Estrutura de dados B1 %02d/%02d/%04d %02d:%02d:%02d %s",
			stTime.wDay,
			stTime.wMonth,
			stTime.wYear,
			stTime.wHour,
			stTime.wMinute,
			stTime.wSecond,
			VERSAO);
		cout << cWork << endl;
		cout << "\tAluno: " << cNomeAluno << " RA: " << cRA << " Turma:" << TURMA << endl;
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
				if(nNumMesa == 0) break;		// volta ao menu se desistiu...
				if(objRestaurante.VerificaSeMesaOcupada(nNumMesa, &stMesa)) // mesa ocupada?
				{	// mesa est� ocupada - vamos exibir a sua situa��o
					sprintf(cWork, " desde %02d:%02d", 
						stMesa.stHoraOcupacao.nHora,
						stMesa.stHoraOcupacao.nMinuto);
					cout << "Mesa: " << nNumMesa << " j� est� ocupada!" << endl
						<< "Qtde Pessoas: " << stMesa.nQtdePessoas << cWork
						<< " Total: " << stMesa.dValorTotal << endl << endl;
					PAUSA;
					break;								// volta ao menu
				} // if ocupada
				// vai ocupar a mesa com uma quantidade de pessoas a ser informado
				cout << "Qtde pessoas: ";
				cin >> nQtdePessoas;
				if(!objRestaurante.OcuparMesa(nNumMesa, nQtdePessoas)) // problema?
				{	// houve problema na ocupa��o da mesa
					cout << "Problema na ocupa��o da mesa " << nNumMesa << endl;
					PAUSA;
				}
				break;
			case SERVIR_PRODUTO_MESA:
				// chamar a fun��o que pede uma mesa v�lida (est� definida antes da main)
				// verificar se o operador desistiu da a��o a ser executada
				// chamar o m�todo que verifica se mesa est� ocupada.
				// Se a mesa estiver livre avisar ao operador e sair do switch
				// Pedir o c�digo do produto e chamar o m�todo que verifica se produto
				// existe e receber os dados do produto.
				// Se operador digitar 0, cancelar a a��o...
				// Exibir descri��o do produto e pedir quantidade e se for zero cancelar a a��o.
				// Chamar o m�todo que insere o produto na lista ligada da mesa
				nNumMesa = PedirMesaValida("Servir um produto na mesa");
				if(nNumMesa == 0) break;		// volta ao menu se desistiu...
				// testar se a mesa est� desocupada
				if(!objRestaurante.VerificaSeMesaOcupada(nNumMesa, &stMesa))
				{	// mesa est� desocupada e portanto n�o pode ser servido um produto
					cout << "Mesa: " << nNumMesa << " est� desocupada!" << endl;
					PAUSA;
					break;							// volta ao menu
				}
				do
				{
					cout << "C�digo do produto: ";
					cin >> nCodProduto;
				} while(nCodProduto < 0 || nCodProduto > QTDE_PRODUTOS);
				// verificar se vai cancelar
				if(nCodProduto == 0)			// cancelar?
					break;						// volta ao menu
				if(!objRestaurante.InformaDadosProduto(nCodProduto, &stProduto))
				{	// o produto n�o existe!
					cout << "Produto: " << nCodProduto << " n�o existe!" << endl;
					PAUSA;
					break;						// volta ao menu
				}
				// o produto existe e seus dados est�o em stProduto
				cout << "Qtde do produto " << stProduto.cDescricao << " : ";
				cin >> nQtdeProduto;
				if(nQtdeProduto == 0)			// vai desistir?
					break;						// volta ao menu
				if(!objRestaurante.InsereNovoProdutoNaMesa(nNumMesa, nCodProduto,
					nQtdeProduto))
				{	// problema na inser��o do produto na lista da mesa
					cout << "Problema na inser��o do produto " <<
						nCodProduto << " na mesa " << nNumMesa << endl;
					PAUSA;
				}
				break;							// volta ao menu
			case FECHAR_MESA:
				// chamar a fun��o que pede uma mesa v�lida (est� definida antes da main)
				// verificar se o operador desistiu da a��o a ser executada
				// chamar o m�todo que verifica se mesa est� ocupada.
				// Se a mesa estiver livre avisar ao operador e sair do switch
				// Invocar o m�todo que faz o fechamento da mesa
				nNumMesa = PedirMesaValida("Fechar uma mesa");
				if(nNumMesa == 0) break;		// volta ao menu se desistiu...
				// testar se a mesa est� desocupada
				if(!objRestaurante.VerificaSeMesaOcupada(nNumMesa, &stMesa))
				{	// mesa est� desocupada e portanto n�o pode ser servido um produto
					cout << "Mesa: " << nNumMesa << " est� desocupada!" << endl;
					PAUSA;
					break;							// volta ao menu
				}
				objRestaurante.FecharMesa(nNumMesa);
				PAUSA;
				break;
			case CONSULTAR_MESA:
				// chamar a fun��o que pede uma mesa v�lida (est� definida antes da main)
				nNumMesa = PedirMesaValida("Consultar Mesa");
				if(nNumMesa == 0) break;		// volta ao menu se desistiu...
				// verificar se o operador desistiu da a��o a ser executada
				// chamar o m�todo que verifica se mesa est� ocupada.
				if(!objRestaurante.VerificaSeMesaOcupada(nNumMesa, &stMesa))
				{	// mesa est� desocupada e portanto n�o pode ser servido um produto
					cout << "Mesa: " << nNumMesa << " est� desocupada!" << endl;
					PAUSA;
					break;							// volta ao menu
				}
				// Se a mesa estiver livre avisar ao operador e sair do switch
				// Se a mesa estiver ocupada os seus dados vieram para a struct cujo endere�o
				// foi passado
				// Mostrar quantas pessoas est�o ocupando e qual � o total da mesa e hora da
				//	ocupa��o da mesa
				cout << "Mesa ocupada por " << stMesa.nQtdePessoas << " pessoas.\nTotal: " << stMesa.dValorTotal << endl;
				cout << "Hor�rio da ocupa��o: " << stMesa.stHoraOcupacao.nHora << ":" << stMesa.stHoraOcupacao.nMinuto << endl;
				PAUSA;
				break;
			case LIBERAR_MESA:
				// chamar a fun��o que pede uma mesa v�lida (est� definida antes da main)
				// verificar se o operador desistiu da a��o a ser executada
				nNumMesa = PedirMesaValida("Liberar Mesa");
				if(nNumMesa == 0) break;		// volta ao menu se desistiu...
				// chamar o m�todo que verifica se mesa est� ocupada.
				// Se a mesa estiver livre avisar ao operador e sair do switch
				if(!objRestaurante.VerificaSeMesaOcupada(nNumMesa, &stMesa))
				{	// mesa est� desocupada e portanto n�o pode ser servido um produto
					cout << "Mesa: " << nNumMesa << " est� desocupada!" << endl;
					PAUSA;
					break;							// volta ao menu
				}
				// Invocar o m�todo que libera a mesa
				if(!objRestaurante.LiberarMesa(nNumMesa))
				{
					cout << "Mesa n�o estava ocupada!" << endl;
					PAUSA;
					break;
				}
				cout << "Liberado com sucesso!" << endl;
				PAUSA;
				break;
			case SAIR_DO_PROGRAMA:
				cout << "Vai sair do programa realmente? (S ou N): ";
				cin >> cOpcao;
				if(cOpcao == 's' || cOpcao == 'S')
					return;					// sai fora do programa
				break;
			default:
				cout << "Digite uma op��o v�lida!" << endl;
				PAUSA;
				LIMPAR_TELA;
		} // switch
	} // while (true)
} // main