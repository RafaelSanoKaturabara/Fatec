// Declara��es da Escola Natacao
#include <iostream>
#include <windows.h>
using namespace std;

#define PAUSA										system("pause")
#define LIMPA_TELA									system("cls")
// Op��es do menu
#define MATRICULAR_ALUNO							'M'		
#define LISTAR_ALUNOS_DE_UM_PERIODO					'P'
#define LISTAR_TODOS_OS_ALUNOS						'T'
#define CANCELAR_MATRICULA							'C'
#define LANCAR_DESPESA_EM_UM_ALUNO					'D'
#define CONSULTAR_UM_DADO_ALUNO						'U'
#define SAIR_DO_PROGRAMA							'S'
// quantidades de raias
#define QTDE_MIN_RAIAS								3	// Qtde m�nima de raias na piscina
#define QTDE_MAX_RAIAS								10	// Qtde m�xima de raias na piscina
// tabela de transa��es
#define LANCHONETE									1
#define ACESSORIOS									2
#define HIGIENE										3

// tabela de periodos								
#define MANHA										1
#define TARDE										2
#define NOITE										3
// Coment�rio:
//	A escola de nata��o tem uma piscina que funciona em tr�s per�odos (manh�, tarde, noite)
//	A quantidade de raias que a piscina tem ser� informado pelo operador na main.
//	Cada raia pode ter um e apenas um aluno matriculado

// tabela de pre�o da mensalidade
#define	MENSALIDADE_BASICA							90.00
#define DESCONTO_MAIS_UM_MESMO_SOBRENOME			10				// 10%
#define DESCONTO_MAXIMO								40				// 40%
// Coment�rio:
//		O primeiro aluno da fam�lia (Sobrenome) paga R$ 90.00
//		O segundo membro da mesma fam�lia paga 90.00 - 10%
//		O terceiro membro da mesma fam�lia paga 90.00 - 20%
//		O quarto membro da mesma fam�lia para 90.00 - 30%
//		O quinto e os demais membros da fam�lia pagam 90 - 40%

// struct dos dados do aluno
typedef struct tagALUNO
{
	char cSobrenome[21],						// sobrenome ou nome de fam�lia
		cPrenome[31];							// prenome que pode ter brancos entre eles
	double dMensalidade;						// valor da mensalidade
} ALUNO;

// struct de cada transa��o aplicada a cada raia da piscina em um dado periodo
typedef struct tagTRANSACAO
{
	int nTipo;									// tipo da transa��o conforme tabela de transa��es
	double dValor;								// valor da transa��o
	tagTRANSACAO *ptrProxima;					// ponteiro para pr�xima transa��o
} TRANSACAO;			

// struct de cada raia da escola de nata��o
typedef struct tagRAIA							
{
	int	nPeriodo,								// periodo conforme tabela de periodos	
		nNumeroDaRaia;							// n�mero da raia da piscina (1, 2, 3 ..... 
	bool	flgLivreOuOcupado;					// true = ocupado, false = livre.
	ALUNO	stAluno;							// dados do aluno associado ao periodo e a 
												// raia da piscina
	double	dValorTotalTransacoes;				// valor total das transa��es
	TRANSACAO *ptrPrimeira,						// ponteiro para a primeira transa��o
		*ptrUltima;								// ponteiro para a ultima transa��o
} RAIA;

// classe da Escola Nata��o 
class clEscolaNatacao
{
	
	// codificar atributos e metodos necess�rios para as atividades impostas pelo menu
private:
	// aqui ser� 
	RAIA *ptrVetRaias,							// ponteiro para o vetor de raias
		*ptrVetSalva;							// ponteiro de salvaguarda do vetor de
												// raias
	int	nSalvaQtdeRaia;							// vai receber a quantidade de raias
												// que tem a piscina (momento da constru��o).

	// M�todo privado que devolve a quantidade de desconto
	double CalculaMensalidadeComDesconto(char *sobrenome)
	{
		bool valorMensalidadeDesconto;
		int i,
			nQtdeParentes = 0;
		for ( i = 0; i < nSalvaQtdeRaia * 3; i++)
		{
			if(strcmp(sobrenome, (ptrVetRaias + i)->stAluno.cSobrenome) == 0)
			{
				nQtdeParentes++;
			}
		}	
		if(nQtdeParentes > 4) // limite de 4 parentes?
			nQtdeParentes = 4;
		if(nQtdeParentes == 0)
			return MENSALIDADE_BASICA;
		return MENSALIDADE_BASICA * (100.00 - (nQtdeParentes * DESCONTO_MAIS_UM_MESMO_SOBRENOME)) / 100.00; 
	}
public:
	// Codificar o construtor recebendo a quantidade raias que a piscina tem
	// Este dado ser� informado no momento da constru��o do objeto
	//	Par�metros:
	//		Entrada: int nQtdeRaias - quantidade de raias informado pelo instanciador da
	//									classe
	//				 bool *flgAlocacaoOK - endere�o para receber true - se foi tudo ok
	//									ou false se aloca��o din�mica falhou
	clEscolaNatacao(int nQtdeRaias, bool *flgAlocacaoOK)
	{
		int i, j; // indexador 
		// Salvar a quantidade de raias para uso futuro
		nSalvaQtdeRaia = nQtdeRaias;
		// Fazer a aloca��o din�mica do vetor de raias considerando que s�o tr�s 
		//	per�odos e cada per�odo tem nQtdeRaias.
		//	Se houver problema na aloca��o din�mica (insufici�ncia de mem�ria)
		//	mover false para o endere�o apontado por flgAlocacaoOK	
		ptrVetRaias = new RAIA[nQtdeRaias * 3];
		if(ptrVetRaias == NULL)
			*flgAlocacaoOK = false;
		else
			*flgAlocacaoOK = true;
		// Inicializar o vetor de raias indicando o periodo, n�mero da raia (1, 2, 3...)
		//	indicar que a raia est� livre e n�o tem nenhuma transa��o realizada....
		if(*flgAlocacaoOK)
		{
			for ( i = 0; i < nQtdeRaias * 3; i++)
			{
			//	Em cada per�odo as raias ser�o numeradas de 1 a nQtdeRaias.
			//	Inicializar cada raia indicando o seu per�odo e dentro do periodo seu n�mero
			//		e indicar que cada raia est� livre
			
				(ptrVetRaias + i)->nNumeroDaRaia = (i % nQtdeRaias) + 1; // n�mero da r�ia
				(ptrVetRaias + i)->nPeriodo = (i / nQtdeRaias) + 1; // n�mero do per�odo
				(ptrVetRaias + i)->flgLivreOuOcupado = false;
			//	Indicar que nenhuma raia tem a lista ligada de transa��o
				(ptrVetRaias + i)->ptrPrimeira = NULL;
			}
		}		 
		//ptrVetRaias = ptrVetSalva;
		//cout << ptrVetRaias[10].nNumeroDaRaia<< ptrVetRaias[10].nPeriodo<< endl;
		//PAUSA;
		// Mover true para o endere�o indicado em flgAlocacaoOK	
		*flgAlocacaoOK = true; // repetindo pois foi pedido
	}
	// M�todo para matricular um aluno em um dado per�odo
	//	Par�metros:
	//		Entrada: int nPeriodo - per�odo desejado para matr�cula (1 ou 2 ou 3)
	//				 ALUNO *ptrAluno - endere�o de uma struct que contem nome e sobrenome
	//						do aluno...
	//		Retorno: o n�mero da raia que o aluno foi matriculado ou zero se n�o havia
	//				nenhuma raia livre no per�odo.....
	int MatricularAluno(int nPeriodo, ALUNO *ptrAluno)
	{
		int i;
		// Este m�todo ir� procurar a primeira raia livre do per�odo e vai associar
		//	o aluno � raia livre encontrada.
		for(i = ((nPeriodo - 1) * nSalvaQtdeRaia); i < ((nPeriodo - 1) * nSalvaQtdeRaia) + nSalvaQtdeRaia; i++)
		{
			if((ptrVetRaias + i)->flgLivreOuOcupado == false) // encontrou raia libre?
			{
				(ptrVetRaias + i)->flgLivreOuOcupado = true;
				(ptrVetRaias + i)->dValorTotalTransacoes = 0.0;
				ptrAluno->dMensalidade = CalculaMensalidadeComDesconto(ptrAluno->cSobrenome); // antes de adicionar os dados de um aluno
				memcpy_s(&(ptrVetRaias + i)->stAluno, sizeof(ALUNO), ptrAluno, sizeof(ALUNO));				
				(ptrVetRaias + i)->ptrPrimeira = NULL;
				return (ptrVetRaias + i)->nNumeroDaRaia; // retora o n�mero da raia
			}
		}
			// Se n�o houver nenhuma raia livre no per�odo o m�todo retorna zero e caso
			//	contr�rio retornar� o n�mero da raia que foi encontrada livre.
			// O ptrAluno aponta para uma struct da main que cont�m sobrenome e prenome e
			//	o valor da mensalidade ser� calculado em fun��o do n�mero de membros da
			//	mesma fam�lia matriculados na escola
			// Se houver algum aluno matriculado em qualquer per�odo com o mesmo sobrenome,
			//	o valor da mensalidade ter� desconto conforme tabela de descontos
			// Se for o primeiro membro da fam�lia o valor da mensalidade � o valor b�sico
			//	Zerar o total de transa��es e indicar que n�o tem nenhuma transa��o na
			//		lista ligada
			//	Indicar que a raia est� ocupada
		// ... codificar a partir daqui
		return 0;							// para n�o dar erro
	}//metodo

	// M�todo para listar os alunos de um dado per�odo
	//	Per�odo: 1(manh�), 2(tarde) e 3(noite)
	void ListarUmPeriodo(int nPeriodo)
	{
		char vetPeriodos[3][7] = 
			{
				"Manh�", 
				"Tarde", 
				"Noite"
			},
			cWork[200];
		int i,
			contAluno = 0;
		// Este m�todo ir� listar os alunos que est�o matriculados no per�odo
		// Formato:
		//		Alunos do periodo: xxxxxx (escrever o per�odo: "manha", "tarde" ou "noite")
		//		Nome: xxxxxxxxxxxxxxxx
		//		Sobrenome: xxxxxxxxxx
		//		Raia: nn  Valor Mensalidade: zzzzz.zz
		//		No final da listagem exibir:
		//		Qtde total de alunos: nn
		cout << "Alunos do periodo: " << vetPeriodos[nPeriodo - 1] << endl << endl;
		for( i = ((nPeriodo - 1) * nSalvaQtdeRaia); i < ((nPeriodo - 1) * nSalvaQtdeRaia) + nSalvaQtdeRaia; i++)
		{
			if((ptrVetRaias + i)->flgLivreOuOcupado == true) // encontrou raia ocupada?
			{
				sprintf_s(cWork, "Nome: %s\nSobrenome: %s\nRaia: %02d  Valor Mensalidade: %8.2f", 
					(ptrVetRaias + i)->stAluno.cPrenome, (ptrVetRaias + i)->stAluno.cSobrenome, (ptrVetRaias + i)->nNumeroDaRaia,
					(ptrVetRaias + i)->stAluno.dMensalidade);
				cout << cWork << endl << endl;
				contAluno++;
			}
		}
		sprintf_s(cWork, "Qtde total de alunos: %02d", contAluno);
		cout << cWork << endl;
		PAUSA;
		return;
	}
	// M�todo para listar todos os per�odos 
	void ListarTodosPeriodos()
	{
		// Este m�todo ir� listar os alunos matriculados nos tr�s periodos no
		// mesmo layout do m�todo anterior 
		// No final da listagem exibir:
		//		Qtde total de alunos em todos periodos: nnn
		char vetPeriodos[3][7] = 
			{
				"Manh�", 
				"Tarde", 
				"Noite"
			},
			cWork[200];
		int i, j,
			contAluno = 0,
			nPeriodo;	// inicia com per�odo 1
		for (nPeriodo = 1; nPeriodo <= 3; nPeriodo++)
		{
			cout << "Alunos do periodo: " << vetPeriodos[nPeriodo - 1] << endl << endl;
			for( i = ((nPeriodo - 1) * nSalvaQtdeRaia); i < ((nPeriodo - 1) * nSalvaQtdeRaia) + nSalvaQtdeRaia; i++)
			{
				if((ptrVetRaias + i)->flgLivreOuOcupado == true) // encontrou raia ocupada?
				{
					sprintf_s(cWork, "Nome: %s\nSobrenome: %s\nRaia: %02d  Valor Mensalidade: %8.2f", 
						(ptrVetRaias + i)->stAluno.cPrenome, (ptrVetRaias + i)->stAluno.cSobrenome, (ptrVetRaias + i)->nNumeroDaRaia,
						(ptrVetRaias + i)->stAluno.dMensalidade);
					cout << cWork << endl << endl;
					contAluno++;
				}
			} // for i
		} // for nPeriodo
		sprintf_s(cWork, "Qtde total de alunos: %02d", contAluno);
		cout << cWork << endl;
		PAUSA;
	}//metodo


	// M�todo para cancelar matr�cula
	//	Par�metros:
	//		Entrada: int nPeriodo - periodo 1 ou 2 ou 3
	//				 int nRaia - n�mero da raia dentro do per�odo
	//		Retorno: true - se a raia tinha aluno matriculado e
	//				 false - se a a raia estava livre...
	bool CancelarMatricula(int nPeriodo, int nRaia)
	{
		// Se a raia estiver desocupada no per�odo informado, retornar false
		// Informar:
		//		Nome: xxxxxxxxxxxxxxxx
		//		Sobrenome: xxxxxxxxx
		//		Periodo: n Raia: nn
		//		Matricula cancelada!
		//	Retornar true
		int nIndiceRaia;
		char cWork[200],
			cOpcao;
		nIndiceRaia = ((nPeriodo - 1) * nSalvaQtdeRaia) + (nRaia - 1);
		if(!(ptrVetRaias + nIndiceRaia)->flgLivreOuOcupado)
		{
			cout << "Raia n�o ocupada!" << endl;
			PAUSA;
			return false;
		}
		sprintf_s(cWork, "Nome: %s\nSobrenome: %s\nRaia: %02d  Valor Mensalidade: %8.2f", 
			(ptrVetRaias + nIndiceRaia)->stAluno.cPrenome, (ptrVetRaias + nIndiceRaia)->stAluno.cSobrenome, (ptrVetRaias + nIndiceRaia)->nNumeroDaRaia,
			(ptrVetRaias + nIndiceRaia)->stAluno.dMensalidade);
		cout << cWork << endl;
		cout << "Confirma a exlus�o do aluno? (S/N): ";
		cin >> cOpcao;
		if (cOpcao == 'S' || cOpcao == 's')
		{
			(ptrVetRaias + nIndiceRaia)->flgLivreOuOcupado = false;
			(ptrVetRaias + nIndiceRaia)->ptrPrimeira = NULL;
			cout << "Exclu�do!" << endl;
			PAUSA;
			return true;
		}
		cout << "Cancelado!" << endl;
		PAUSA;
		return false;								// apenas para n�o dar erro
	}
	// M�todo para lan�ar despesa para um dado aluno
	//	Par�metros:
	//		Entrada: int nPeriodo - periodo 1 ou 2 ou 3
	//				 int nRaia - raia dentro do per�odo
	//				 int nTipo - tipo de despesa (conforme .h)
	//				 double dValor - valor da despesa
	bool LancarDespesa(int nPeriodo, int nRaia, int nTipo, double dValor)
	{	
		int nIndiceRaia;
		nIndiceRaia = ((nPeriodo - 1) * nSalvaQtdeRaia) + (nRaia - 1);
		// Se a raia estiver desocupada no per�odo, retornar false
		if(!(ptrVetRaias + nIndiceRaia)->flgLivreOuOcupado)
		{
			cout << "Raia n�o ocupada!" << endl;
			PAUSA;
			return false;
		}
		// Somar o dValor no total de transa��es da raia e inserir esta
		(ptrVetRaias + nIndiceRaia)->dValorTotalTransacoes += dValor;
		// transa��o na lista ligada....
		if((ptrVetRaias + nIndiceRaia)->ptrPrimeira == NULL) // nenhum item na lista ligada?
			(ptrVetRaias + nIndiceRaia)->ptrPrimeira =
			(ptrVetRaias + nIndiceRaia)->ptrUltima = new TRANSACAO();
		else
			(ptrVetRaias + nIndiceRaia)->ptrUltima =
			(ptrVetRaias + nIndiceRaia)->ptrUltima->ptrProxima = new TRANSACAO();
		if((ptrVetRaias + nIndiceRaia)->ptrUltima == NULL) // n�o teve mem�ria?
		{
			cout << "N�o tem mem�ria sulficiente!" << endl;
			PAUSA;
			return false;
		}
		(ptrVetRaias + nIndiceRaia)->ptrUltima->dValor = dValor;
		(ptrVetRaias + nIndiceRaia)->ptrUltima->nTipo = nTipo;
		(ptrVetRaias + nIndiceRaia)->ptrUltima->ptrProxima = NULL;
		// retornar true 
		return true;						// apenas para n�o dar erro
	}

	// M�todo para consultar um dado aluno: os seus dados e suas despesas
	//	Par�metros:
	//		Entrada: int nPeriodo - per�odo 1, 2 ou 3
	//				 int nRaia - n�mero raia dentro do per�odo
	bool ConsultarAluno(int nPeriodo, int nRaia)
	{
		// Exibir o seguinte:
		//		Nome: xxxxxxxxxxxxxxx
		//		Sobrenome: xxxxxxxx
		//		Raia: nn	Valor Mensalidade: zzzzz.zz
		//		Total transacoes: zzzzzz.zz
		//			Tipo: x		Valor: zzzz.zz		(lista ligada de transa��es)
		//											(listar todas as transa��es)
		int nIndiceRaia;
		char cOpcao,
			cWork[200];
		TRANSACAO *ptrCorrente;
		nIndiceRaia = ((nPeriodo - 1) * nSalvaQtdeRaia) + (nRaia - 1);
		// Se a raia estiver desocupada retornar false
		if(!(ptrVetRaias + nIndiceRaia)->flgLivreOuOcupado)
		{
			cout << "Raia n�o ocupada!" << endl;
			PAUSA;
			return false;
		}
		sprintf_s(cWork, "\tNome: %s\n\tSobrenome: %s\n\tRaia: %02d  Valor Mensalidade: %8.2f\n\tTotal transacoes: %9.2f", 
			(ptrVetRaias + nIndiceRaia)->stAluno.cPrenome, (ptrVetRaias + nIndiceRaia)->stAluno.cSobrenome, (ptrVetRaias + nIndiceRaia)->nNumeroDaRaia,
			(ptrVetRaias + nIndiceRaia)->stAluno.dMensalidade, (ptrVetRaias + nIndiceRaia)->dValorTotalTransacoes);
		cout << cWork << endl;
		for (ptrCorrente = (ptrVetRaias + nIndiceRaia)->ptrPrimeira; ptrCorrente;
			ptrCorrente = ptrCorrente->ptrProxima)
		{
			sprintf(cWork, "\t\tTipo: %1d \tValor: %7.2f",
				ptrCorrente->nTipo, ptrCorrente->dValor);
			cout << cWork << endl;
		}
		//		Retornar true
		return true;					// apenas para n�o dar erro
	}
};