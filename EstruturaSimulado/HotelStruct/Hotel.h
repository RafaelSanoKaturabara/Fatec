// Declara��es da prova de Estrutura - N1 - 29/09/2016
#include <iostream>
#include <Windows.h>
using namespace std;
#define PAUSA							system("pause")
#define LIMPAR_TELA						system("cls")
#define EXTEN_NOME						30			// extens�o do nome do h�spede
// op��es do menu
#define FAZER_CHECK_IN					'I'			// fazer o check-in do h�spede
#define FAZER_CHECK_OUT					'O'			// fazer o check-out do h�spede
#define LISTAR_UM_QUARTO				'L'			// listar os dados de um dado quarto
#define LANCAR_DIARIA					'D'			// lan�ar di�rias nos quartos que est�o ocupados
#define LANCAR_SERVICO					'S'			// lan�ar servico em um dado quarto
#define LISTAR_QUARTOS_OCUPADOS			'T'			// Listar todos os quartos ocupados
#define SAIR_DO_PROGRAMA				'X'			// sair do programa		
//#define TESTE							1
// Valores das di�rias para cada quarto de acordo com o andar em que est�
#define DIARIA_QUARTO_SIMPLES			165.00		// Di�ria do quarto simples
#define DIARIA_QUARTO_MEDIO				308.00		// Di�ria do quarto do tipo m�dio
#define DIARIA_QUARTO_SUPER				610.00		// Di�ria do quarto do tipo super
#define DIARIA_QUARTO_SUITE				990.00		// Di�ria do quarto do tipo suite
// Observa��es:
// 1 - Os quartos dos andares 1� ao 2� - s�o quartos do tipo simples
// 2 - Os quartos dos andares 3� ao 4� - s�o quartos do tipo m�dio
// 3 - Os quartos dos andares 5� ao 8� - s�o quartos do tipo super
// 4 - Os quartos dos andares 9� e acima - s�o quartos do tipo suite

// Limita��es do programa
#define QUANTIDADE_ANDARES				27			// quantidade de andares do hotel
#define QUANTIDADE_QUARTOS				6			// quantidade de quartos por andar

// defini��es de tipos de servi�os
#define RESTAURANTE						1			// transa��o de restaurante
#define LAVANDERIA						2			// transa��o de lavanderia
#define BAR								3			// transa��o de bar
#define PISCINA							4			// transa��o de bar da piscina
#define BOATE							5			// transa��o de bar da boate

// struct da data e hora
typedef struct tagDATA_HORA
{
	int nDia, nMes,						// data com dia/mes
		nHora, nMinuto;					// hora com minuto
} DATA_HORA;
// struct de uma despesa
typedef struct tagSERVICO
{
	int nCodigo;						// c�digo do servi�o conforme tabela 
	DATA_HORA stDtHora;					// data e hora do servi�o
	double dVlrServico;					// valor do servi�o prestado ao h�spede do quarto
	tagSERVICO *ptrProximo;				// ponteiro para o pr�ximo servi�o prestado ao quarto
} SERVICO;
// struct do quarto do hotel
typedef struct tagQUARTO
{
	int	nAndar,							// andar do quarto 1 a QUANTIDADE_ANDARES
		nQuarto;						// quarto dentro do andar 1 a QUANTIDADE_QUARTOS
	bool flgLivreOcupado;				// false - indica que o quarto est� livre e true - ocupado
	DATA_HORA stHoraOcupacao;			// indicar a data e hora da ocupa��o do quarto
	char szNomeHospede[EXTEN_NOME + 1];	// nome do h�spede que est� ocupando o quarto
	double dValorDiaria,				// valor da di�ria do quarto
		dVlrTotDiarias,					// valor total das di�rias
		dVlrServicos,					// valor dos servi�os sem as di�rias
		dVlrTotalGeral;					// valor total de total dos servi�os com di�rias inclusive
	SERVICO *ptrPrimeiro,				// ponteiro para o primeiro servi�o do quarto
		*ptrUltimo;						// ponteiro para o �ltimo servi�o do quarto
} QUARTO;
//
// classe do hotel
//
class clHotel
{
	// Atributos e m�todos private do sistema
private:
	QUARTO vetQuartos[QUANTIDADE_ANDARES * QUANTIDADE_QUARTOS], // vetor de quartos
		stQuarto;						// para conter os dados de um quarto	
	SYSTEMTIME stTime;						// para buscar data e hora
	// Atributos e m�todos p�blicos do sistema
public:
								
	// M�todo construtor da classe
	//	Par�metros: 
	//		Entrada: void
	//	O que fazer:
	//		Inicializar o vetor de quartos indicando que n�o tem nenhum
	//			quarto ocupado (flgLivreOcupado), zerar o total de servi�os e total geral.
	//			O quarto vai ter a sua lista de servi�os vazia
	//			Para cada quarto colocar o seu andar e quarto dentro do andar e o valor
	//			 da di�ria corresponde ao quarto segundo a tabela. Zerar a lista ligada 
	//			 de servi�os de cada quarto.
	clHotel(void)
	{
		int i,j,k;								// indexador gen�rico
		for(i = 0; i < QUANTIDADE_ANDARES * QUANTIDADE_QUARTOS; ) // for total
		{
			for(j = 1; j < QUANTIDADE_ANDARES + 1; j++) // for de andares
			{
				for (k = 1; k < QUANTIDADE_QUARTOS + 1; i++, k++) // for de quartos
				{
					switch (j)
					{
						case 1:
						case 2:
							vetQuartos[i].dValorDiaria = DIARIA_QUARTO_SIMPLES;
							break;
						case 3:
						case 4:
							vetQuartos[i].dValorDiaria = DIARIA_QUARTO_MEDIO;
							break;
						case 5:
						case 6:
						case 7:
						case 8:
							vetQuartos[i].dValorDiaria = DIARIA_QUARTO_SUPER;
							break;
						default:
							vetQuartos[i].dValorDiaria = DIARIA_QUARTO_SUITE;
					}
					vetQuartos[i].flgLivreOcupado = false;
					vetQuartos[i].nAndar = j;
					vetQuartos[i].nQuarto = k;
					vetQuartos[i].dVlrServicos = 0.0;
					vetQuartos[i].dVlrTotalGeral = 0.0;
					vetQuartos[i].dVlrTotDiarias = 0.0;
					vetQuartos[i].ptrPrimeiro = NULL;
				}
			}
		} // for i

#ifdef TESTE
		for(i = 0; i < QUANTIDADE_ANDARES * QUANTIDADE_QUARTOS; i++)
		{
			vetQuartos[i].flgLivreOcupado = false;
			vetQuartos[i].nAndar = (i / QUANTIDADE_QUARTOS) + 1;
			vetQuartos[i].nQuarto = (i % QUANTIDADE_QUARTOS) + 1;
			vetQuartos[i].dVlrServicos = 0.0;
			vetQuartos[i].dVlrTotalGeral = 0.0;
			vetQuartos[i].dVlrTotDiarias = 0.0;
			if(i < ((1 * QUANTIDADE_QUARTOS) + QUANTIDADE_QUARTOS))
				vetQuartos[i].dValorDiaria = DIARIA_QUARTO_SIMPLES;
			else if(i < (3 * QUANTIDADE_QUARTOS) + (QUANTIDADE_QUARTOS))
				vetQuartos[i].dValorDiaria = DIARIA_QUARTO_MEDIO;
			else if(i < (7 * QUANTIDADE_QUARTOS) + (QUANTIDADE_QUARTOS))
				vetQuartos[i].dValorDiaria = DIARIA_QUARTO_SUPER;
			else 
				vetQuartos[i].dValorDiaria = DIARIA_QUARTO_SUITE;
			vetQuartos[i].ptrPrimeiro = NULL;
		}
#endif
		// loop para mostrar se o valor foi certo
		for (i = 0; i < QUANTIDADE_ANDARES * QUANTIDADE_QUARTOS; )
		{
			for (int j = 0; j < QUANTIDADE_QUARTOS; j++, i++)
			{
				cout << vetQuartos[i].nAndar << vetQuartos[i].dValorDiaria << "\t";
				if(i == QUANTIDADE_ANDARES * QUANTIDADE_QUARTOS)
					break;
			}
			cout << endl;
		}
		PAUSA;
	}
	// M�todo p�blico que verifica se o quarto est� livre ou ocupado
	//	Par�metros:
	//		Entrada: int nAndar - andar do quarto entre 1 e QUANTIDADE_ANDARES
	//				 int nQuarto - quarto dentro do andar entre 1 e QUANTIDADE_QUARTOS
	//				 QUARTO *ptrStQuarto - ponteiro de um struct que conter� os dados
	//										do quarto se ele estiver ocupado
	//		Retorno: bool - true - indica que o quarto est� ocupado e os seus dados 
	//								foram copiados na struct indicada pelo invocador do
	//								m�todo.
	//						false - indica que o quarto est� livre
	//			O que fazer:
	//				Calcular o indice do vetor de quartos. Este indice � fun��o do
	//				   andar, quantidade de quartos por andar e o quarto dentro do andar.
	//				Verificar se o quarto indexado est� livre e se estiver retornar false.
	//				Se n�o estiver livre copiar o quarto indexado para a struct do 
	//					invocador do m�todo e retornar true.
	bool VerificarQuartoLivre(int nAndar, int nQuarto, QUARTO *ptrStQuarto)
	{
		int iIndice = (nAndar - 1) * QUANTIDADE_QUARTOS + (nQuarto - 1);	// calculo do indice do quarto
		if(vetQuartos[iIndice].flgLivreOcupado == false)
			return false;
		// quarto ocupado
		memcpy_s(ptrStQuarto, sizeof(QUARTO), &vetQuartos[iIndice], sizeof(QUARTO));
		return true;							// para n�o dar erro
	}
	// M�todo p�blico que faz o check_in do h�spede em um determinado andar e quarto
	//	Par�metros:
	//		Entrada: int nAndar - andar do quarto entre 1 e QUANTIDADE_ANDARES
	//				 int nQuarto - quarto dentro do andar entre 1 e QUANTIDADE_QUARTOS
	//				 char *ptrNomeHospede - ponteiro de um string com o nome do h�spede
	//		Retorno: bool - true - o check_in foi realizado com sucesso
	//						false - o quarto j� estava ocupado por outro h�spede
	//		O que fazer:
	//				 verificar se o quarto est� livre e se n�o estiver devolver false.
	//				 Calcular o indice do vetor de quartos para trat�-lo indexado.
	//				 Se estiver livre indicar que est� ocupado, copiar o nome do h�spede
	//					no quarto, indicar a data e hora da ocupa��o e zerar total di�rias
	//					total de servi�os e total geral.
	bool CheckInHospede(int nAndar, int nQuarto, char *ptrNomeHospede)
	{						
		GetLocalTime(&stTime);
		if(VerificarQuartoLivre(nAndar, nQuarto, &stQuarto))
			return false;
		int iIndice = (nAndar - 1) * QUANTIDADE_QUARTOS + (nQuarto - 1);	// calculo do indice do quarto
		vetQuartos[iIndice].flgLivreOcupado = true;
		strcpy_s(vetQuartos[iIndice].szNomeHospede, ptrNomeHospede);
		vetQuartos[iIndice].stHoraOcupacao.nDia = stTime.wDay;
		vetQuartos[iIndice].stHoraOcupacao.nHora = stTime.wHour;
		vetQuartos[iIndice].stHoraOcupacao.nMes = stTime.wMonth;
		vetQuartos[iIndice].stHoraOcupacao.nMinuto = stTime.wMinute;
		vetQuartos[iIndice].dVlrTotDiarias = 0.0;
		vetQuartos[iIndice].dVlrServicos = 0.0;
		vetQuartos[iIndice].dVlrTotalGeral = 0.0;
		return true;							// para n�o dar erro
	}
	// M�todo p�blico que faz o check-out do h�spede.
	//	Par�metros:
	//		Entrada: int nAndar - andar do quarto entre 1 e QUANTIDADE_ANDARES
	//				 int nQuarto - quarto dentro do andar entre 1 e QUANTIDADE_QUARTOS
	//		Retorno: bool - true - o check-out foi realizado com sucesso
	//						false - o quarto n�o estava ocupado
	//		O que fazer:
	//				Calcular o indice do vetor de quartos para trat�-lo indexado.
	//				verificar se o quarto est� ocupado e se n�o estiver retornar false.
	//				Se estiver ocupado simplesmente desocupar o quarto com um false.
	bool CheckOutHospede(int nAndar, int nQuarto)
	{
		int iIndice = (nAndar - 1) * QUANTIDADE_QUARTOS + (nQuarto - 1);	// calculo do indice do quarto
		if(vetQuartos[iIndice].flgLivreOcupado == false)
			return false;
		vetQuartos[iIndice].flgLivreOcupado = false;
		return true;							// para n�o dar erro
	}
	// M�todo p�blico que inclui um servi�o em um dado quarto
	//	Par�metros:
	//		Entrada: int nAndar - andar do quarto entre 1 e QUANTIDADE_ANDARES
	//				 int nQuarto - quarto dentro do andar entre 1 e QUANTIDADE_QUARTOS
	//				 int nCodServico - c�digo do servi�o prestado
	//				 double dVlrServico - valor do servi�o prestado
	//		Retorno: bool - true - indica que foi tudo OK
	//						false - indica que n�o tem mem�ria para incluir esse
	//								servi�o na lista ligada de servi�os
	//		O que fazer:
	//				 A verifica��o do quarto ocupado ou n�o deve ter sido feito
	//					anteriormente.
	//				 Buscar data e hora do sistema para complementar os dados do servi�o
	//				 Calcular o indice do vetor de quartos para trat�-lo indexado.
	//				 Incluir este servi�o na lista ligada que deve ser feita no
	//					�ltimo.
	//				 Somar este servi�o nos totais de servi�os e totais gerais do
	//					quarto.
	//					
	bool LancarServico(int nAndar, int nQuarto, int nCodServico, double dVlrServico)
	{
		GetLocalTime(&stTime);		
		int iIndice = (nAndar - 1) * QUANTIDADE_QUARTOS + (nQuarto - 1);	// calculo do indice do quarto
		if(vetQuartos[iIndice].ptrPrimeiro == NULL)
			vetQuartos[iIndice].ptrPrimeiro 
				= vetQuartos[iIndice].ptrUltimo = new SERVICO;
		else
			vetQuartos[iIndice].ptrUltimo 
				= vetQuartos[iIndice].ptrUltimo->ptrProximo = new SERVICO;
		if(vetQuartos[iIndice].ptrUltimo == NULL)
			return false;
		vetQuartos[iIndice].ptrUltimo->dVlrServico = dVlrServico;
		vetQuartos[iIndice].ptrUltimo->nCodigo = nCodServico;
		vetQuartos[iIndice].ptrUltimo->stDtHora.nDia = stTime.wDay;
		vetQuartos[iIndice].ptrUltimo->stDtHora.nMes = stTime.wMonth;
		vetQuartos[iIndice].ptrUltimo->stDtHora.nHora = stTime.wHour;
		vetQuartos[iIndice].ptrUltimo->stDtHora.nMinuto = stTime.wMinute;
		vetQuartos[iIndice].ptrUltimo->ptrProximo = NULL;
		vetQuartos[iIndice].dVlrServicos += dVlrServico;
		vetQuartos[iIndice].dVlrTotalGeral += dVlrServico;
		return true;								// para n�o dar erro
	}
	// M�todo p�blico que lista todos os quartos ocupados
	//	Par�metros: nenhum
	//		O que fazer:
	//			Apagar a tela e emitir um cabe�alho indicando o tipo da listagem.
	//			Percorrer o vetor de quartos e se estiver ocupado exibir andar, quarto, nome do h�spede
	//				valor da di�ria, total de servi�os e total geral.
	//			Percorrer a lista ligada exibindo os valores de cada servi�o prestado 
	//				As linhas de impress�o devem ser formatadas com sprintf_s.
	//
	//				Observe o layout abaixo: 
	//					Listagem dos quartos ocupados em dd/mm/aaaa �s hh:mm (Cabe�alho da listagem - uma vez)
	//			(<<<<<As linhas abaixo repetem para cada quarto ocupado>>>>>>)
	// Andar Quarto H�spede             Dt.Ocupa��o Vlr.Di�ria Tot.Di�rias Tot.Servi�os Tot.Geral
	//	AA	QQ	 HHHHHHHHHHHHHHHHHHHHHH	DD/MM HH:MM DDDDDDD.DD TDTDTDTD.TD  SSSSSSS.SS  TTTTTT.TT
	//															 
	//											Servi�o      Dt.Servi�o   Vlr.Servi�o
	//											NNNNNNNNNNNN DD/MM HH:MM  VSVSVSVS.VS
	//											NNNNNNNNNNNN DD/MM HH:MM  VSVSVSVS.VS
	//											NNNNNNNNNNNN DD/MM HH:MM  VSVSVSVS.VS .....quantos houver
	//													
	//			(<<<<<<<na ultima linha da listagem apresentar o seguinte:>>>>>>>
	//													Total Geral: GGGGGGG.GG (somat�ria dos totais gerais)

	//			Onde:
	//			AA - andar
	//			QQ - quarto
	//			HHHHHH....H - Nome do h�spede
	//			DD/MM - dia e mes
	//			HH/MM - hora e minuto
	//			DDDDDD.DD - valor da di�ria
	//			TDTDTDTD.TD - total de di�rias
	//			SSSSSS.SS - total de servi�os
	//			TTTTTT.TT - total geral de di�rias e servi�os
	//			NNNNNNNNN - nome do servi�o
	//			VSVSVSVS.VS - valor do servi�o
	//	
	void ListarTodosQuartos()
	{
		SERVICO *ptrCorrente;						//
		float fTotal;
		int i;										// 
		char cWork[200],
			vetNomesServicos[5][15] =	   {"Restaurante",
											"Lavanderia",
											"Bar",
											"Piscina",
											"Boate"};

		for(i = 0; i < QUANTIDADE_ANDARES * QUANTIDADE_QUARTOS; i++)
		{
			if(vetQuartos[i].flgLivreOcupado == true)
			{
				LIMPAR_TELA;
				GetLocalTime(&stTime);
				sprintf_s(cWork, "Listagem dos quartos ocupados em %02d/%02d/%04d �s %02d:%02d",
					stTime.wDay, stTime.wMonth, stTime.wYear, stTime.wHour, stTime.wMinute);
				cout << "\t" << cWork << endl;
				cout << "Andar Quarto H�spede             Dt.Ocupa��o Vlr.Di�ria Tot.Di�rias Tot.Servi�os Tot.Geral" << endl;
				sprintf_s(cWork, "%3d  %2d   %-22s %02d/%02d %02d:%02d %10.2f %11.2f  %10.2f  %9.2f",
					vetQuartos[i].nAndar, vetQuartos[i].nQuarto, vetQuartos[i].szNomeHospede, vetQuartos[i].stHoraOcupacao.nDia, vetQuartos[i].stHoraOcupacao.nMes
					, vetQuartos[i].stHoraOcupacao.nHora, vetQuartos[i].stHoraOcupacao.nMinuto, vetQuartos[i].dValorDiaria, vetQuartos[i].dVlrTotDiarias, vetQuartos[i].dVlrServicos,
					vetQuartos[i].dVlrTotalGeral);
				cout << cWork << endl;
				cout << "\n\t\t\t\t\t\tServi�o      Dt.Servi�o   Vlr.Servi�o" << endl;
				fTotal = 0.0;
				for(ptrCorrente = vetQuartos[i].ptrPrimeiro; ptrCorrente; ptrCorrente = ptrCorrente->ptrProximo)
				{
					sprintf_s(cWork, "%-12s %02d/%02d %02d:%02d  %11.2f"
						, vetNomesServicos[ptrCorrente->nCodigo - 1], ptrCorrente->stDtHora.nDia, ptrCorrente->stDtHora.nMes
						, ptrCorrente->stDtHora.nHora, ptrCorrente->stDtHora.nMinuto, ptrCorrente->dVlrServico);
					fTotal += ptrCorrente->dVlrServico;
					cout << "\t\t\t\t\t\t" << cWork << endl;
				} // for lista
				sprintf_s(cWork, "Total Geral: %10.2f", fTotal);
				cout << "\t\t\t\t\t\t\t\t\t\t" << cWork << endl;
				PAUSA;
			}
		}	// for i
	}

	// M�todo p�blico que lan�a uma di�ria nos quartos ocupados
	//	Par�metros: nenhum
	//		O que fazer:
	//			Percorrer o vetor de quartos e aquele que estiver ocupado somar o valor
	//				de sua di�ria no total de di�rias e no total geral.
	void LancarDiarias()
	{
		int i;									// indexador gen�rico
		for (i = 0; i < QUANTIDADE_ANDARES * QUANTIDADE_QUARTOS; i++)
		{
			if(vetQuartos[i].flgLivreOcupado == true)
			{
				vetQuartos[i].dVlrTotDiarias += vetQuartos[i].dValorDiaria;
				vetQuartos[i].dVlrTotalGeral += vetQuartos[i].dValorDiaria;
			}
		} // for i
	}
};