// Declarações da prova de Estrutura - N1 - 29/09/2016
#include <iostream>
#include <Windows.h>
using namespace std;
#define PAUSA							system("pause")
#define LIMPAR_TELA						system("cls")
#define EXTEN_NOME						30			// extensão do nome do hóspede
// opções do menu
#define FAZER_CHECK_IN					'I'			// fazer o check-in do hóspede
#define FAZER_CHECK_OUT					'O'			// fazer o check-out do hóspede
#define LISTAR_UM_QUARTO				'L'			// listar os dados de um dado quarto
#define LANCAR_DIARIA					'D'			// lançar diárias nos quartos que estão ocupados
#define LANCAR_SERVICO					'S'			// lançar servico em um dado quarto
#define LISTAR_QUARTOS_OCUPADOS			'T'			// Listar todos os quartos ocupados
#define SAIR_DO_PROGRAMA				'X'			// sair do programa		
//#define TESTE							1
// Valores das diárias para cada quarto de acordo com o andar em que está
#define DIARIA_QUARTO_SIMPLES			165.00		// Diária do quarto simples
#define DIARIA_QUARTO_MEDIO				308.00		// Diária do quarto do tipo médio
#define DIARIA_QUARTO_SUPER				610.00		// Diária do quarto do tipo super
#define DIARIA_QUARTO_SUITE				990.00		// Diária do quarto do tipo suite
// Observações:
// 1 - Os quartos dos andares 1º ao 2º - são quartos do tipo simples
// 2 - Os quartos dos andares 3º ao 4º - são quartos do tipo médio
// 3 - Os quartos dos andares 5º ao 8º - são quartos do tipo super
// 4 - Os quartos dos andares 9º e acima - são quartos do tipo suite

// Limitações do programa
#define QUANTIDADE_ANDARES				27			// quantidade de andares do hotel
#define QUANTIDADE_QUARTOS				6			// quantidade de quartos por andar

// definições de tipos de serviços
#define RESTAURANTE						1			// transação de restaurante
#define LAVANDERIA						2			// transação de lavanderia
#define BAR								3			// transação de bar
#define PISCINA							4			// transação de bar da piscina
#define BOATE							5			// transação de bar da boate

// struct da data e hora
typedef struct tagDATA_HORA
{
	int nDia, nMes,						// data com dia/mes
		nHora, nMinuto;					// hora com minuto
} DATA_HORA;
// struct de uma despesa
typedef struct tagSERVICO
{
	int nCodigo;						// código do serviço conforme tabela 
	DATA_HORA stDtHora;					// data e hora do serviço
	double dVlrServico;					// valor do serviço prestado ao hóspede do quarto
	tagSERVICO *ptrProximo;				// ponteiro para o próximo serviço prestado ao quarto
} SERVICO;
// struct do quarto do hotel
typedef struct tagQUARTO
{
	int	nAndar,							// andar do quarto 1 a QUANTIDADE_ANDARES
		nQuarto;						// quarto dentro do andar 1 a QUANTIDADE_QUARTOS
	bool flgLivreOcupado;				// false - indica que o quarto está livre e true - ocupado
	DATA_HORA stHoraOcupacao;			// indicar a data e hora da ocupação do quarto
	char szNomeHospede[EXTEN_NOME + 1];	// nome do hóspede que está ocupando o quarto
	double dValorDiaria,				// valor da diária do quarto
		dVlrTotDiarias,					// valor total das diárias
		dVlrServicos,					// valor dos serviços sem as diárias
		dVlrTotalGeral;					// valor total de total dos serviços com diárias inclusive
	SERVICO *ptrPrimeiro,				// ponteiro para o primeiro serviço do quarto
		*ptrUltimo;						// ponteiro para o último serviço do quarto
} QUARTO;
//
// classe do hotel
//
class clHotel
{
	// Atributos e métodos private do sistema
private:
	QUARTO vetQuartos[QUANTIDADE_ANDARES * QUANTIDADE_QUARTOS], // vetor de quartos
		stQuarto;						// para conter os dados de um quarto	
	SYSTEMTIME stTime;						// para buscar data e hora
	// Atributos e métodos públicos do sistema
public:
								
	// Método construtor da classe
	//	Parâmetros: 
	//		Entrada: void
	//	O que fazer:
	//		Inicializar o vetor de quartos indicando que não tem nenhum
	//			quarto ocupado (flgLivreOcupado), zerar o total de serviços e total geral.
	//			O quarto vai ter a sua lista de serviços vazia
	//			Para cada quarto colocar o seu andar e quarto dentro do andar e o valor
	//			 da diária corresponde ao quarto segundo a tabela. Zerar a lista ligada 
	//			 de serviços de cada quarto.
	clHotel(void)
	{
		int i,j,k;								// indexador genérico
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
	// Método público que verifica se o quarto está livre ou ocupado
	//	Parâmetros:
	//		Entrada: int nAndar - andar do quarto entre 1 e QUANTIDADE_ANDARES
	//				 int nQuarto - quarto dentro do andar entre 1 e QUANTIDADE_QUARTOS
	//				 QUARTO *ptrStQuarto - ponteiro de um struct que conterá os dados
	//										do quarto se ele estiver ocupado
	//		Retorno: bool - true - indica que o quarto está ocupado e os seus dados 
	//								foram copiados na struct indicada pelo invocador do
	//								método.
	//						false - indica que o quarto está livre
	//			O que fazer:
	//				Calcular o indice do vetor de quartos. Este indice é função do
	//				   andar, quantidade de quartos por andar e o quarto dentro do andar.
	//				Verificar se o quarto indexado está livre e se estiver retornar false.
	//				Se não estiver livre copiar o quarto indexado para a struct do 
	//					invocador do método e retornar true.
	bool VerificarQuartoLivre(int nAndar, int nQuarto, QUARTO *ptrStQuarto)
	{
		int iIndice = (nAndar - 1) * QUANTIDADE_QUARTOS + (nQuarto - 1);	// calculo do indice do quarto
		if(vetQuartos[iIndice].flgLivreOcupado == false)
			return false;
		// quarto ocupado
		memcpy_s(ptrStQuarto, sizeof(QUARTO), &vetQuartos[iIndice], sizeof(QUARTO));
		return true;							// para não dar erro
	}
	// Método público que faz o check_in do hóspede em um determinado andar e quarto
	//	Parâmetros:
	//		Entrada: int nAndar - andar do quarto entre 1 e QUANTIDADE_ANDARES
	//				 int nQuarto - quarto dentro do andar entre 1 e QUANTIDADE_QUARTOS
	//				 char *ptrNomeHospede - ponteiro de um string com o nome do hóspede
	//		Retorno: bool - true - o check_in foi realizado com sucesso
	//						false - o quarto já estava ocupado por outro hóspede
	//		O que fazer:
	//				 verificar se o quarto está livre e se não estiver devolver false.
	//				 Calcular o indice do vetor de quartos para tratá-lo indexado.
	//				 Se estiver livre indicar que está ocupado, copiar o nome do hóspede
	//					no quarto, indicar a data e hora da ocupação e zerar total diárias
	//					total de serviços e total geral.
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
		return true;							// para não dar erro
	}
	// Método público que faz o check-out do hóspede.
	//	Parâmetros:
	//		Entrada: int nAndar - andar do quarto entre 1 e QUANTIDADE_ANDARES
	//				 int nQuarto - quarto dentro do andar entre 1 e QUANTIDADE_QUARTOS
	//		Retorno: bool - true - o check-out foi realizado com sucesso
	//						false - o quarto não estava ocupado
	//		O que fazer:
	//				Calcular o indice do vetor de quartos para tratá-lo indexado.
	//				verificar se o quarto está ocupado e se não estiver retornar false.
	//				Se estiver ocupado simplesmente desocupar o quarto com um false.
	bool CheckOutHospede(int nAndar, int nQuarto)
	{
		int iIndice = (nAndar - 1) * QUANTIDADE_QUARTOS + (nQuarto - 1);	// calculo do indice do quarto
		if(vetQuartos[iIndice].flgLivreOcupado == false)
			return false;
		vetQuartos[iIndice].flgLivreOcupado = false;
		return true;							// para não dar erro
	}
	// Método público que inclui um serviço em um dado quarto
	//	Parâmetros:
	//		Entrada: int nAndar - andar do quarto entre 1 e QUANTIDADE_ANDARES
	//				 int nQuarto - quarto dentro do andar entre 1 e QUANTIDADE_QUARTOS
	//				 int nCodServico - código do serviço prestado
	//				 double dVlrServico - valor do serviço prestado
	//		Retorno: bool - true - indica que foi tudo OK
	//						false - indica que não tem memória para incluir esse
	//								serviço na lista ligada de serviços
	//		O que fazer:
	//				 A verificação do quarto ocupado ou não deve ter sido feito
	//					anteriormente.
	//				 Buscar data e hora do sistema para complementar os dados do serviço
	//				 Calcular o indice do vetor de quartos para tratá-lo indexado.
	//				 Incluir este serviço na lista ligada que deve ser feita no
	//					último.
	//				 Somar este serviço nos totais de serviços e totais gerais do
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
		return true;								// para não dar erro
	}
	// Método público que lista todos os quartos ocupados
	//	Parâmetros: nenhum
	//		O que fazer:
	//			Apagar a tela e emitir um cabeçalho indicando o tipo da listagem.
	//			Percorrer o vetor de quartos e se estiver ocupado exibir andar, quarto, nome do hóspede
	//				valor da diária, total de serviços e total geral.
	//			Percorrer a lista ligada exibindo os valores de cada serviço prestado 
	//				As linhas de impressão devem ser formatadas com sprintf_s.
	//
	//				Observe o layout abaixo: 
	//					Listagem dos quartos ocupados em dd/mm/aaaa às hh:mm (Cabeçalho da listagem - uma vez)
	//			(<<<<<As linhas abaixo repetem para cada quarto ocupado>>>>>>)
	// Andar Quarto Hóspede             Dt.Ocupação Vlr.Diária Tot.Diárias Tot.Serviços Tot.Geral
	//	AA	QQ	 HHHHHHHHHHHHHHHHHHHHHH	DD/MM HH:MM DDDDDDD.DD TDTDTDTD.TD  SSSSSSS.SS  TTTTTT.TT
	//															 
	//											Serviço      Dt.Serviço   Vlr.Serviço
	//											NNNNNNNNNNNN DD/MM HH:MM  VSVSVSVS.VS
	//											NNNNNNNNNNNN DD/MM HH:MM  VSVSVSVS.VS
	//											NNNNNNNNNNNN DD/MM HH:MM  VSVSVSVS.VS .....quantos houver
	//													
	//			(<<<<<<<na ultima linha da listagem apresentar o seguinte:>>>>>>>
	//													Total Geral: GGGGGGG.GG (somatória dos totais gerais)

	//			Onde:
	//			AA - andar
	//			QQ - quarto
	//			HHHHHH....H - Nome do hóspede
	//			DD/MM - dia e mes
	//			HH/MM - hora e minuto
	//			DDDDDD.DD - valor da diária
	//			TDTDTDTD.TD - total de diárias
	//			SSSSSS.SS - total de serviços
	//			TTTTTT.TT - total geral de diárias e serviços
	//			NNNNNNNNN - nome do serviço
	//			VSVSVSVS.VS - valor do serviço
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
				sprintf_s(cWork, "Listagem dos quartos ocupados em %02d/%02d/%04d às %02d:%02d",
					stTime.wDay, stTime.wMonth, stTime.wYear, stTime.wHour, stTime.wMinute);
				cout << "\t" << cWork << endl;
				cout << "Andar Quarto Hóspede             Dt.Ocupação Vlr.Diária Tot.Diárias Tot.Serviços Tot.Geral" << endl;
				sprintf_s(cWork, "%3d  %2d   %-22s %02d/%02d %02d:%02d %10.2f %11.2f  %10.2f  %9.2f",
					vetQuartos[i].nAndar, vetQuartos[i].nQuarto, vetQuartos[i].szNomeHospede, vetQuartos[i].stHoraOcupacao.nDia, vetQuartos[i].stHoraOcupacao.nMes
					, vetQuartos[i].stHoraOcupacao.nHora, vetQuartos[i].stHoraOcupacao.nMinuto, vetQuartos[i].dValorDiaria, vetQuartos[i].dVlrTotDiarias, vetQuartos[i].dVlrServicos,
					vetQuartos[i].dVlrTotalGeral);
				cout << cWork << endl;
				cout << "\n\t\t\t\t\t\tServiço      Dt.Serviço   Vlr.Serviço" << endl;
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

	// Método público que lança uma diária nos quartos ocupados
	//	Parâmetros: nenhum
	//		O que fazer:
	//			Percorrer o vetor de quartos e aquele que estiver ocupado somar o valor
	//				de sua diária no total de diárias e no total geral.
	void LancarDiarias()
	{
		int i;									// indexador genérico
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