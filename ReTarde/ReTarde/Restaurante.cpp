// Prova N1 - Estrutura de Dados - 06/04/2017 - Turma da Tarde
// FATEC-MC - JCB - Versão 0.0
#include "Restaurante.h"

// Função que pede uma mesa válida
// Esta função vai ficar em loop até o operador informar um número 
// de mesa válido
//	Parâmetros:
//		Entrada: char *ptrNomeAcao - nome da opção que está sendo executada
//		Retorno - int - o número válido da mesa ou zero se o operador desistiu
int PedirMesaValida(char *ptrNomeAcao)
{
	int nMesa;								// para receber o número da mesa
	cout << "\t\tAção: " << ptrNomeAcao << endl << endl;
	do
	{
		cout << "Número da mesa entre 1 e " << QTDE_MESAS << endl
			<< "Ou zero para desistir: ";
		cin >> nMesa;
	} while(nMesa < 0 || nMesa > QTDE_MESAS);
	return nMesa;							// retorna a mesa ou zero na desistência
}

void main(void)
{
	int nNumMesa,							// para receber o número da mesa
		nQtdePessoas,						// quantidade de pessoas à mesa
		nCodProduto,						// produto servido à mesa
		nQtdeProduto;						// quantidade do produto sendo servido
	PRODUTO stProduto;						// para receber os dados de um produto
	MESA stMesa;							// para receber os dados de uma mesa
	char cOpcao,							// Opção de escolha do operador
		cNomeAluno[] = "Digitar nome do aluno",	// informar o seu nome
		cRA[] = "Informar o RA do aluno",		// informar o seu RA
		cWork[100];							// área de trabalho
	SYSTEMTIME stTime;						// struct para buscar data e hora do sistema
	// instanciar a classe restaurante
	clRestaurante objRestaurante;			// criar o objeto restaurante
	setlocale(LC_ALL, "portuguese_brazil"); // para aceitar símbolos gráficos do Brasil
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
		// formatar o cabeçalho do menu
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
		cout << FECHAR_MESA << " - Fechar mesa que está ocupada" << endl;
		cout << CONSULTAR_MESA << " - Consultar mesa" << endl;
		cout << LIBERAR_MESA << " - Liberar mesa" << endl;
		cout << SAIR_DO_PROGRAMA << " - Sair do programa" << endl;
		cout << "\tSelecione: ";
		cin >> cOpcao;						// pegar a opção operador
		cOpcao = toupper(cOpcao);			// converter opção para maiúscula
		switch(cOpcao)						// avaliar a opção escolhida
		{
			case OCUPAR_MESA:
				// chamar a função que pede uma mesa válida (está definida antes da main)
				// verificar se o operador desistiu da ação a ser executada
				// chamar o método que verifica se mesa está ocupada
				// Se a mesa estiver ocupada exibir os seus dados dar pausa e sair do
				//	switch (Indicar mesa ocupada, quantas pessoas, desde que hora e o total
				//	até agora
				// Se a mesa estiver livre, pedir qtde de pessoas na mesa e chamar o método
				// que ocupa a mesa. Analisar o resultado
				nNumMesa = PedirMesaValida("Ocupar uma mesa");
				if(nNumMesa == 0)				// cancelou a transação
					break;						// volta ao menu se desistiu...

				// verificar se a mesa está ocupada invocando o método
				// VerificaSeMesaOcupada e se a mesa estiver ocupada
				if(objRestaurante.VerificaSeMesaOcupada(nNumMesa, &stMesa))
				// exibir os dados da mesa: número da mesa, qtde de pessoas 
				//	hora e minuto da ocupação total gasto na mesa com sprintf_s
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
				// invocar o método OcuparMesa e analisar o resultado
				if(objRestaurante.OcuparMesa(nNumMesa, stMesa.nQtdePessoas))
				{
					cout << "Mesa ocupada com sucesso!" << endl;
					PAUSA;
					break;
				}
				cout << "Mesa não estava vazia!Operação cancelada!" << endl;
				PAUSA;
				// e voltar ao menu
				break;

			case SERVIR_PRODUTO_MESA:
				// chamar a função que pede uma mesa válida (está definida antes da main)
				nNumMesa = PedirMesaValida("Servir produto na mesa");
				// verificar se o operador desistiu da ação a ser executada				
				if(nNumMesa == 0)				// cancelou a transação
					break;						// volta ao menu se desistiu...
				// chamar o método que verifica se mesa está ocupada.
				if(!objRestaurante.VerificaSeMesaOcupada(nNumMesa, &stMesa))
				// Se a mesa estiver livre avisar ao operador e sair do switch e voltar ao menu
				{
					cout << "A mesa " << nNumMesa << " não está ocupada!" << endl;
					PAUSA;
					break;
				}
				// Pedir o código do produto e chamar o método que verifica se produto
				// existe e receber os dados do produto.
				do
				{
					cout << "Digite o código do produto ou zero para cancelar: ";
					cin >> nCodProduto;
				// Se operador digitar 0, cancelar a ação...
					if(nCodProduto == 0)
						break;
				}while(nCodProduto < 1 || nCodProduto > QTDE_PRODUTOS);				
				// Exibir descrição do produto e pedir quantidade e se for zero cancelar a ação.
				if(!objRestaurante.InformaDadosProduto(nCodProduto, &stProduto))
				{
					cout << "Código de produto inválido!" << endl;
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
				// Chamar o método que insere o produto na lista ligada da mesa
				if(objRestaurante.InsereNovoProdutoNaMesa(nNumMesa, nCodProduto, nQtdeProduto))
				// Codificar

				break;							// volta ao menu
			case FECHAR_MESA:
				// chamar a função que pede uma mesa válida (está definida antes da main)
				// verificar se o operador desistiu da ação a ser executada
				// chamar o método que verifica se mesa está ocupada.
				// Se a mesa estiver livre avisar ao operador e sair do switch
				// Invocar o método que faz o fechamento da mesa
				// Codificar

				break;
			case CONSULTAR_MESA:
				// chamar a função que pede uma mesa válida (está definida antes da main)
				// verificar se o operador desistiu da ação a ser executada
				// chamar o método que verifica se mesa está ocupada.
				// Se a mesa estiver livre avisar ao operador e sair do switch
				// Se a mesa estiver ocupada os seus dados vieram para a struct cujo endereço
				// foi passado
				// Mostrar quantas pessoas estão ocupando e qual é o total da mesa e hora da
				//	ocupação da mesa
				// Codificar

				break;
			case LIBERAR_MESA:
				// chamar a função que pede uma mesa válida (está definida antes da main)
				// verificar se o operador desistiu da ação a ser executada
				// chamar o método que verifica se mesa está ocupada.
				// Se a mesa estiver livre avisar ao operador e sair do switch
				// Invocar o método que libera a mesa
				// Codificar
				break;
			case SAIR_DO_PROGRAMA:
				cout << "\n\tVai sair do programa realmente? (S ou N): ";
				cin >> cOpcao;
				if(cOpcao == 's' || cOpcao == 'S')
					return;					// sai fora do programa
				break;
			default:
				cout << "\n\tDigite uma opção válida!" << endl << "\t";
				PAUSA;
				LIMPAR_TELA;
		} // switch
	} // while (true)
} // main