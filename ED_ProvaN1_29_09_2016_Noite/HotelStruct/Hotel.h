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
#define QUANTIDADE_ANDARES				20			// quantidade de andares do hotel
#define QUANTIDADE_QUARTOS				10			// quantidade de quartos por andar

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
	// Atributos e m�todos p�blicos do sistema
public:
								
	// M�todo construtor da classe
	//	Par�metros: 
	//		Entrada: void
	//	O que fazer:
	//		Inicializar o vetor de quartos indicando que n�o tem nenhum
	//			quarto ocupado (flgLivreOcupado), zerar o total de servi�os e total geral.
	//			Para cada quarto colocar o seu andar e quarto dentro do andar e o valor
	//			 da di�ria corresponde ao quarto segundo a tabela. Zerar a lista ligada 
	//			 de servi�os de cada quarto.
	clHotel(void)
	{
	}
	// M�todo p�blico que verifica se o quarto est� livre ou ocupado
	//	Par�metros:
	//		Entrada: int nAndar - andar do quarto entre 1 e QUANTIDADE_ANDARES
	//				 int nQuarto - quarto dentro do andar entre 1 e QUANTIDADE_QUARTOS
	//				 QUARTO *ptrStQuarto - ponteiro de um struct que conter� os dados
	//										do quarto se ele estiver ocupado
	//		Retorno: bool - true - indica que o quarto est� ocupado e os seus dados 
	//								foram copiados na struct indica pelo invocador do
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
	//					no quarto, indicar a data e hora da ocupa��o e zerar 
	//					total de servi�os e total geral.
	bool CheckInHospede(int nAndar, int nQuarto, char *ptrNomeHospede)
	{
		return true;							// para n�o dar erro
	}
	// M�todo p�blico que faz o check-out do h�spede.
	//	Par�metros:
	//		Entrada: int nAndar - andar do quarto entre 1 e QUANTIDADE_ANDARES
	//				 int nQuarto - quarto dentro do andar entre 1 e QUANTIDADE_QUARTOS
	//		Retorno: bool - true - o check-out foi realizado com sucesso
	//						false - o quarto n�o estava ocupado
	//		O que fazer:
	//				verificar se o quarto est� ocupado e se n�o estiver retornar false.
	//				Calcular o indice do vetor de quartos para trat�-lo indexado.
	//				Se estiver ocupado simplesmente desocupar o quarto com um false.
	bool CheckOutHospede(int nAndar, int nQuarto)
	{
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
	//			Andar Quarto H�spede                Dt.Ocupa��o Vlr.Di�ria Tot.Servi�os Tot.Geral
	//			  AA	QQ	 HHHHHHHHHHHHHHHHHHHHHH	DD/MM HH:MM DDDDDDD.DD  SSSSSSS.SS  TTTTTT.TT
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
	//			SSSSSS.SS - total de servi�os
	//			TTTTTT.TT - total geral de di�rias e servi�os
	//			NNNNNNNNN - nome do servi�o
	//			VSVSVSVS.VS - valor do servi�o
	//	
	void ListarTodosQuartos()
	{
		char vetNomesServicos[5][15] =	   {"Restaurante",
											"Lavanderia",
											"Bar",
											"Piscina",
											"Boate"};

	}

	// M�todo p�blico que lan�a uma di�ria nos quartos ocupados
	//	Par�metros: nenhum
	//		O que fazer:
	//			Percorrer o vetor de quartos e aquele que estiver ocupado somar o valor
	//				de sua di�ria no total de di�rias e no total geral.
	void LancarDiarias()
	{
	}
};