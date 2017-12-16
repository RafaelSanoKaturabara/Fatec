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
#define ANDAR_1							1
#define ANDAR_2							2
#define ANDAR_3							3
#define ANDAR_4							4
#define ANDAR_5							5
#define ANDAR_6							6
#define ANDAR_7							7
#define ANDAR_8							8
#define ANDAR_9							9
// Limitações do programa
#define QUANTIDADE_ANDARES				20			// quantidade de andares do hotel
#define QUANTIDADE_QUARTOS				10			// quantidade de quartos por andar

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
	int nQtde,							// quantidade total de quartos
		iIndQuarto;						// para calcular o indice do quarto
	// Atributos e métodos públicos do sistema
	char vetNomesServicos[5][15],		// nomes dos serviços
		cWork[200];						// para o sprintf

public:
								
	// Método construtor da classe
	//	Parâmetros: 
	//		Entrada: void
	//	O que fazer:
	//		Inicializar o vetor de quartos indicando que não tem nenhum
	//			quarto ocupado (flgLivreOcupado), zerar o total de serviços e total geral.
	//			Para cada quarto colocar o seu andar e quarto dentro do andar e o valor
	//			 da diária corresponde ao quarto segundo a tabela. Zerar a lista ligada 
	//			 de serviços de cada quarto.
	clHotel(void)
	{
		int i, j, k;								// indices genéricos
		char vetNomesServicos[5][15] = {"Restaurante",
										"Lavanderia",
										"Bar",
										"Piscina",
										"Boate"};
		for(i = 0; i < 5; i++)						// copiar os nomes dos serviços
			strcpy_s(this->vetNomesServicos[i], 15, vetNomesServicos[i]);
		nQtde = QUANTIDADE_ANDARES * QUANTIDADE_QUARTOS;	// total de quartos
		for(i = 1, k = 0; k < nQtde; i++)			// i = andar e k é o indice de todos os quartos
		{
			for(j = 1; j <= QUANTIDADE_QUARTOS; j++, k++) // j = quarto dentro do andar
			{
				vetQuartos[k].nAndar = i;				// andar
				vetQuartos[k].nQuarto = j;				// quarto dentro do andar
				vetQuartos[k].flgLivreOcupado = false;	// quarto livre
				vetQuartos[k].dVlrServicos =
					vetQuartos[k].dVlrTotalGeral = 0.0; // zerar os totais
				vetQuartos[k].ptrPrimeiro = NULL;		// lista de serviços vazia
				switch(i)								// avalia o andar
				{
					case ANDAR_1:
					case ANDAR_2:
						vetQuartos[k].dValorDiaria = DIARIA_QUARTO_SIMPLES;
						break;							// cai fora do switch
					case ANDAR_3:
					case ANDAR_4:
						vetQuartos[k].dValorDiaria = DIARIA_QUARTO_MEDIO;
						break;							// cai fora do switch
					case ANDAR_5:
					case ANDAR_6:
					case ANDAR_7:
					case ANDAR_8:
						vetQuartos[k].dValorDiaria = DIARIA_QUARTO_SUPER;
						break;							// cai fora do switch
					case ANDAR_9:
						vetQuartos[k].dValorDiaria = DIARIA_QUARTO_SUITE;
						break;							// cai fora do switch
					default:
						vetQuartos[k].dValorDiaria = DIARIA_QUARTO_SUITE;
				} // switch i
			} // for j
		} // for k

	}
	// Método público que verifica se o quarto está livre ou ocupado
	//	Parâmetros:
	//		Entrada: int nAndar - andar do quarto entre 1 e QUANTIDADE_ANDARES
	//				 int nQuarto - quarto dentro do andar entre 1 e QUANTIDADE_QUARTOS
	//				 QUARTO *ptrStQuarto - ponteiro de um struct que conterá os dados
	//										do quarto se ele estiver ocupado
	//		Retorno: bool - true - indica que o quarto está ocupado e os seus dados 
	//								foram copiados na struct indica pelo invocador do
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
		iIndQuarto = ((nAndar - 1) * QUANTIDADE_QUARTOS) + (nQuarto - 1);
		memcpy_s(ptrStQuarto, sizeof(QUARTO), &vetQuartos[iIndQuarto], sizeof(QUARTO));
		if(vetQuartos[iIndQuarto].flgLivreOcupado == true)			// quarto ocupado?
			return true;						// indica que está ocupado
		return false;							// indica que o quarto está livre
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
	//					no quarto, indicar a data e hora da ocupação e zerar 
	//					total de serviços e total geral.
	bool CheckInHospede(int nAndar, int nQuarto, char *ptrNomeHospede)
	{
		SYSTEMTIME stTime;										// para data e hora do sistema
		iIndQuarto = ((nAndar - 1) * QUANTIDADE_QUARTOS) + (nQuarto - 1);
		if(vetQuartos[iIndQuarto].flgLivreOcupado)				// quarto ocupado?
			return false;										// indica que o quarto está ocupado
		// ocupar o quarto
		vetQuartos[iIndQuarto].flgLivreOcupado = true;			// quarto ocupado
		strcpy_s(vetQuartos[iIndQuarto].szNomeHospede, EXTEN_NOME, ptrNomeHospede);
		vetQuartos[iIndQuarto].ptrPrimeiro = NULL;				// esvazia a lista de serviços
		vetQuartos[iIndQuarto].dVlrServicos =
			vetQuartos[iIndQuarto].dVlrTotalGeral = 0.0;		// zerar os totais
		GetLocalTime(&stTime);									// data e hora do sistema
		vetQuartos[iIndQuarto].stHoraOcupacao.nDia = stTime.wDay;
		vetQuartos[iIndQuarto].stHoraOcupacao.nMes = stTime.wMonth;
		vetQuartos[iIndQuarto].stHoraOcupacao.nHora = stTime.wHour;
		vetQuartos[iIndQuarto].stHoraOcupacao.nMinuto = stTime.wMinute;
		return true;							// indica check-in OK
	}
	// Método público que faz o check-out do hóspede.
	//	Parâmetros:
	//		Entrada: int nAndar - andar do quarto entre 1 e QUANTIDADE_ANDARES
	//				 int nQuarto - quarto dentro do andar entre 1 e QUANTIDADE_QUARTOS
	//		Retorno: bool - true - o check-out foi realizado com sucesso
	//						false - o quarto não estava ocupado
	//		O que fazer:
	//				verificar se o quarto está ocupado e se não estiver retornar false.
	//				Calcular o indice do vetor de quartos para tratá-lo indexado.
	//				Se estiver ocupado simplesmente desocupar o quarto com um false.
	bool CheckOutHospede(int nAndar, int nQuarto)
	{
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
		SYSTEMTIME stTime;										// para data e hora do sistema
		SERVICO *ptrSalva;										// salva o ponteiro da lista
		iIndQuarto = ((nAndar - 1) * QUANTIDADE_QUARTOS) + (nQuarto - 1);
		ptrSalva = vetQuartos[iIndQuarto].ptrUltimo;			// salva o endereço do último serviço
		if(vetQuartos[iIndQuarto].ptrPrimeiro == NULL)			// primeiro serviço?
			vetQuartos[iIndQuarto].ptrUltimo =
			vetQuartos[iIndQuarto].ptrPrimeiro = new SERVICO;	// aloca memória para o serviço
		else
			vetQuartos[iIndQuarto].ptrUltimo =
			vetQuartos[iIndQuarto].ptrUltimo->ptrProximo = new SERVICO; // aloca memória
		// tinha memória?
		if(vetQuartos[iIndQuarto].ptrUltimo == NULL)			// sem memória
		{
			vetQuartos[iIndQuarto].ptrUltimo = ptrSalva;		// restaura o ponteiro
			return false;										// indica que não tem memória
		}
		vetQuartos[iIndQuarto].ptrUltimo->nCodigo = nCodServico;
		vetQuartos[iIndQuarto].ptrUltimo->dVlrServico = dVlrServico;
		vetQuartos[iIndQuarto].dVlrServicos += dVlrServico;
		vetQuartos[iIndQuarto].dVlrTotalGeral += dVlrServico;
		vetQuartos[iIndQuarto].ptrUltimo->ptrProximo = NULL;		// último da lista
		GetLocalTime(&stTime);									// data e hora do serviço
		vetQuartos[iIndQuarto].ptrUltimo->stDtHora.nDia = stTime.wDay;
		vetQuartos[iIndQuarto].ptrUltimo->stDtHora.nMes = stTime.wMonth;
		vetQuartos[iIndQuarto].ptrUltimo->stDtHora.nHora = stTime.wHour;
		vetQuartos[iIndQuarto].ptrUltimo->stDtHora.nMinuto = stTime.wMinute;
		return true;								// indica tudo OK
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
	//			Andar Quarto Hóspede                Dt.Ocupação Vlr.Diária Tot.Serviços Tot.Geral
	//			  AA	QQ	 HHHHHHHHHHHHHHHHHHHHHH	DD/MM HH:MM DDDDDDD.DD  SSSSSSS.SS  TTTTTT.TT
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
	//			SSSSSS.SS - total de serviços
	//			TTTTTT.TT - total geral de diárias e serviços
	//			NNNNNNNNN - nome do serviço
	//			VSVSVSVS.VS - valor do serviço
	//	
	void ListarTodosQuartos()
	{
		int i;									// indice genérico
		SERVICO *ptrWork;						// ponteiro para percorrer a lista ligada
		LIMPAR_TELA;
		cout << "\tListagem de todos os quartos ocupados" << endl;
		// loop para percorrer o vetor de todos os quartos
		for(i = 0; i < nQtde; i++)
		{
			if(!vetQuartos[i].flgLivreOcupado)			// quarto livre?
				continue;								// continua no for
	//			Andar Quarto Hóspede                Dt.Ocupação Vlr.Diária Tot.Serviços Tot.Geral
	//			  AA	QQ	 HHHHHHHHHHHHHHHHHHHHHH	DD/MM HH:MM DDDDDDD.DD  SSSSSSS.SS  TTTTTT.TT
			sprintf_s(cWork, sizeof(cWork),
				"Andar Quarto Hóspede               Dt.Ocupação Vlr.Diária Tot.Serviços Tot.Geral");
			cout << cWork << endl;
			sprintf_s(cWork, sizeof(cWork),
				"  %2d  %2d %-30s %02d/%02d %02d:%02d %9.2f %9.2f %9.2f",
				vetQuartos[i].nAndar, vetQuartos[i].nQuarto, vetQuartos[i].szNomeHospede,
				vetQuartos[i].stHoraOcupacao.nDia, vetQuartos[i].stHoraOcupacao.nMes,
				vetQuartos[i].stHoraOcupacao.nHora, vetQuartos[i].stHoraOcupacao.nMinuto,
				vetQuartos[i].dValorDiaria, vetQuartos[i].dVlrServicos,
				vetQuartos[i].dVlrTotalGeral);
			cout << cWork << endl;
			sprintf_s(cWork, sizeof(cWork),
				"\tServiço     Dt.Serviço   Vlr.Serviço");
			cout << cWork << endl;
			// loop para percorrer a lista
	//											NNNNNNNNNNNN DD/MM HH:MM  VSVSVSVS.VS
	//											NNNNNNNNNNNN DD/MM HH:MM  VSVSVSVS.VS
			for(ptrWork = vetQuartos[i].ptrPrimeiro; ptrWork; ptrWork = ptrWork->ptrProximo)
			{
				sprintf_s(cWork, sizeof(cWork),
					"%-15s %02d/%02d %02d:%02d %9.2f",
					vetNomesServicos[ptrWork->nCodigo - 1],
					ptrWork->stDtHora.nDia, ptrWork->stDtHora.nMes,
					ptrWork->stDtHora.nHora, ptrWork->stDtHora.nMinuto,
					ptrWork->dVlrServico);
				cout << cWork << endl;
			}
		} // for i
		PAUSA;
	}

	// Método público que lança uma diária nos quartos ocupados
	//	Parâmetros: nenhum
	//		O que fazer:
	//			Percorrer o vetor de quartos e aquele que estiver ocupado somar o valor
	//				de sua diária no total de diárias e no total geral.
	void LancarDiarias()
	{
	}
};