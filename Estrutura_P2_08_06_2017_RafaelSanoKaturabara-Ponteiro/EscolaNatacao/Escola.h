// Declarações da Escola Natacao
#include <iostream>
#include <windows.h>
using namespace std;

#define PAUSA										system("pause")
#define LIMPA_TELA									system("cls")
// Opções do menu
#define MATRICULAR_ALUNO							'M'		
#define LISTAR_ALUNOS_DE_UM_PERIODO					'P'
#define LISTAR_TODOS_OS_ALUNOS						'T'
#define CANCELAR_MATRICULA							'C'
#define LANCAR_DESPESA_EM_UM_ALUNO					'D'
#define CONSULTAR_UM_DADO_ALUNO						'U'
#define SAIR_DO_PROGRAMA							'S'
// quantidades de raias
#define QTDE_MIN_RAIAS								3	// Qtde mínima de raias na piscina
#define QTDE_MAX_RAIAS								10	// Qtde máxima de raias na piscina
// tabela de transações
#define LANCHONETE									1
#define ACESSORIOS									2
#define HIGIENE										3

// tabela de periodos								
#define MANHA										1
#define TARDE										2
#define NOITE										3
// Comentário:
//	A escola de natação tem uma piscina que funciona em três períodos (manhã, tarde, noite)
//	A quantidade de raias que a piscina tem será informado pelo operador na main.
//	Cada raia pode ter um e apenas um aluno matriculado

// tabela de preço da mensalidade
#define	MENSALIDADE_BASICA							90.00
#define DESCONTO_MAIS_UM_MESMO_SOBRENOME			10				// 10%
#define DESCONTO_MAXIMO								40				// 40%
// Comentário:
//		O primeiro aluno da família (Sobrenome) paga R$ 90.00
//		O segundo membro da mesma família paga 90.00 - 10%
//		O terceiro membro da mesma família paga 90.00 - 20%
//		O quarto membro da mesma família para 90.00 - 30%
//		O quinto e os demais membros da família pagam 90 - 40%

// struct dos dados do aluno
typedef struct tagALUNO
{
	char cSobrenome[21],						// sobrenome ou nome de família
		cPrenome[31];							// prenome que pode ter brancos entre eles
	double dMensalidade;						// valor da mensalidade
} ALUNO;

// struct de cada transação aplicada a cada raia da piscina em um dado periodo
typedef struct tagTRANSACAO
{
	int nTipo;									// tipo da transação conforme tabela de transações
	double dValor;								// valor da transação
	tagTRANSACAO *ptrProxima;					// ponteiro para próxima transação
} TRANSACAO;			

// struct de cada raia da escola de natação
typedef struct tagRAIA							
{
	int	nPeriodo,								// periodo conforme tabela de periodos	
		nNumeroDaRaia;							// número da raia da piscina (1, 2, 3 ..... 
	bool	flgLivreOuOcupado;					// true = ocupado, false = livre.
	ALUNO	stAluno;							// dados do aluno associado ao periodo e a 
												// raia da piscina
	double	dValorTotalTransacoes;				// valor total das transações
	TRANSACAO *ptrPrimeira,						// ponteiro para a primeira transação
		*ptrUltima;								// ponteiro para a ultima transação
} RAIA;

// classe da Escola Natação 
class clEscolaNatacao
{
	
	// codificar atributos e metodos necessários para as atividades impostas pelo menu
private:
	// aqui será 
	RAIA *ptrVetRaias,							// ponteiro para o vetor de raias
		*ptrVetSalva;							// ponteiro de salvaguarda do vetor de
												// raias
	int	nSalvaQtdeRaia;							// vai receber a quantidade de raias
												// que tem a piscina (momento da construção).

	// Método privado que devolve a quantidade de desconto
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
	// Este dado será informado no momento da construção do objeto
	//	Parâmetros:
	//		Entrada: int nQtdeRaias - quantidade de raias informado pelo instanciador da
	//									classe
	//				 bool *flgAlocacaoOK - endereço para receber true - se foi tudo ok
	//									ou false se alocação dinâmica falhou
	clEscolaNatacao(int nQtdeRaias, bool *flgAlocacaoOK)
	{
		int i, j; // indexador 
		// Salvar a quantidade de raias para uso futuro
		nSalvaQtdeRaia = nQtdeRaias;
		// Fazer a alocação dinâmica do vetor de raias considerando que são três 
		//	períodos e cada período tem nQtdeRaias.
		//	Se houver problema na alocação dinâmica (insuficiência de memória)
		//	mover false para o endereço apontado por flgAlocacaoOK	
		ptrVetRaias = new RAIA[nQtdeRaias * 3];
		if(ptrVetRaias == NULL)
			*flgAlocacaoOK = false;
		else
			*flgAlocacaoOK = true;
		// Inicializar o vetor de raias indicando o periodo, número da raia (1, 2, 3...)
		//	indicar que a raia está livre e não tem nenhuma transação realizada....
		if(*flgAlocacaoOK)
		{
			for ( i = 0; i < nQtdeRaias * 3; i++)
			{
			//	Em cada período as raias serão numeradas de 1 a nQtdeRaias.
			//	Inicializar cada raia indicando o seu período e dentro do periodo seu número
			//		e indicar que cada raia está livre
			
				(ptrVetRaias + i)->nNumeroDaRaia = (i % nQtdeRaias) + 1; // número da ráia
				(ptrVetRaias + i)->nPeriodo = (i / nQtdeRaias) + 1; // número do período
				(ptrVetRaias + i)->flgLivreOuOcupado = false;
			//	Indicar que nenhuma raia tem a lista ligada de transação
				(ptrVetRaias + i)->ptrPrimeira = NULL;
			}
		}		 
		//ptrVetRaias = ptrVetSalva;
		//cout << ptrVetRaias[10].nNumeroDaRaia<< ptrVetRaias[10].nPeriodo<< endl;
		//PAUSA;
		// Mover true para o endereço indicado em flgAlocacaoOK	
		*flgAlocacaoOK = true; // repetindo pois foi pedido
	}
	// Método para matricular um aluno em um dado período
	//	Parâmetros:
	//		Entrada: int nPeriodo - período desejado para matrícula (1 ou 2 ou 3)
	//				 ALUNO *ptrAluno - endereço de uma struct que contem nome e sobrenome
	//						do aluno...
	//		Retorno: o número da raia que o aluno foi matriculado ou zero se não havia
	//				nenhuma raia livre no período.....
	int MatricularAluno(int nPeriodo, ALUNO *ptrAluno)
	{
		int i;
		// Este método irá procurar a primeira raia livre do período e vai associar
		//	o aluno à raia livre encontrada.
		for(i = ((nPeriodo - 1) * nSalvaQtdeRaia); i < ((nPeriodo - 1) * nSalvaQtdeRaia) + nSalvaQtdeRaia; i++)
		{
			if((ptrVetRaias + i)->flgLivreOuOcupado == false) // encontrou raia libre?
			{
				(ptrVetRaias + i)->flgLivreOuOcupado = true;
				(ptrVetRaias + i)->dValorTotalTransacoes = 0.0;
				ptrAluno->dMensalidade = CalculaMensalidadeComDesconto(ptrAluno->cSobrenome); // antes de adicionar os dados de um aluno
				memcpy_s(&(ptrVetRaias + i)->stAluno, sizeof(ALUNO), ptrAluno, sizeof(ALUNO));				
				(ptrVetRaias + i)->ptrPrimeira = NULL;
				return (ptrVetRaias + i)->nNumeroDaRaia; // retora o número da raia
			}
		}
			// Se não houver nenhuma raia livre no período o método retorna zero e caso
			//	contrário retornará o número da raia que foi encontrada livre.
			// O ptrAluno aponta para uma struct da main que contém sobrenome e prenome e
			//	o valor da mensalidade será calculado em função do número de membros da
			//	mesma família matriculados na escola
			// Se houver algum aluno matriculado em qualquer período com o mesmo sobrenome,
			//	o valor da mensalidade terá desconto conforme tabela de descontos
			// Se for o primeiro membro da família o valor da mensalidade é o valor básico
			//	Zerar o total de transações e indicar que não tem nenhuma transação na
			//		lista ligada
			//	Indicar que a raia está ocupada
		// ... codificar a partir daqui
		return 0;							// para não dar erro
	}//metodo

	// Método para listar os alunos de um dado período
	//	Período: 1(manhã), 2(tarde) e 3(noite)
	void ListarUmPeriodo(int nPeriodo)
	{
		char vetPeriodos[3][7] = 
			{
				"Manhã", 
				"Tarde", 
				"Noite"
			},
			cWork[200];
		int i,
			contAluno = 0;
		// Este método irá listar os alunos que estão matriculados no período
		// Formato:
		//		Alunos do periodo: xxxxxx (escrever o período: "manha", "tarde" ou "noite")
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
	// Método para listar todos os períodos 
	void ListarTodosPeriodos()
	{
		// Este método irá listar os alunos matriculados nos três periodos no
		// mesmo layout do método anterior 
		// No final da listagem exibir:
		//		Qtde total de alunos em todos periodos: nnn
		char vetPeriodos[3][7] = 
			{
				"Manhã", 
				"Tarde", 
				"Noite"
			},
			cWork[200];
		int i, j,
			contAluno = 0,
			nPeriodo;	// inicia com período 1
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


	// Método para cancelar matrícula
	//	Parâmetros:
	//		Entrada: int nPeriodo - periodo 1 ou 2 ou 3
	//				 int nRaia - número da raia dentro do período
	//		Retorno: true - se a raia tinha aluno matriculado e
	//				 false - se a a raia estava livre...
	bool CancelarMatricula(int nPeriodo, int nRaia)
	{
		// Se a raia estiver desocupada no período informado, retornar false
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
			cout << "Raia não ocupada!" << endl;
			PAUSA;
			return false;
		}
		sprintf_s(cWork, "Nome: %s\nSobrenome: %s\nRaia: %02d  Valor Mensalidade: %8.2f", 
			(ptrVetRaias + nIndiceRaia)->stAluno.cPrenome, (ptrVetRaias + nIndiceRaia)->stAluno.cSobrenome, (ptrVetRaias + nIndiceRaia)->nNumeroDaRaia,
			(ptrVetRaias + nIndiceRaia)->stAluno.dMensalidade);
		cout << cWork << endl;
		cout << "Confirma a exlusão do aluno? (S/N): ";
		cin >> cOpcao;
		if (cOpcao == 'S' || cOpcao == 's')
		{
			(ptrVetRaias + nIndiceRaia)->flgLivreOuOcupado = false;
			(ptrVetRaias + nIndiceRaia)->ptrPrimeira = NULL;
			cout << "Excluído!" << endl;
			PAUSA;
			return true;
		}
		cout << "Cancelado!" << endl;
		PAUSA;
		return false;								// apenas para não dar erro
	}
	// Método para lançar despesa para um dado aluno
	//	Parâmetros:
	//		Entrada: int nPeriodo - periodo 1 ou 2 ou 3
	//				 int nRaia - raia dentro do período
	//				 int nTipo - tipo de despesa (conforme .h)
	//				 double dValor - valor da despesa
	bool LancarDespesa(int nPeriodo, int nRaia, int nTipo, double dValor)
	{	
		int nIndiceRaia;
		nIndiceRaia = ((nPeriodo - 1) * nSalvaQtdeRaia) + (nRaia - 1);
		// Se a raia estiver desocupada no período, retornar false
		if(!(ptrVetRaias + nIndiceRaia)->flgLivreOuOcupado)
		{
			cout << "Raia não ocupada!" << endl;
			PAUSA;
			return false;
		}
		// Somar o dValor no total de transações da raia e inserir esta
		(ptrVetRaias + nIndiceRaia)->dValorTotalTransacoes += dValor;
		// transação na lista ligada....
		if((ptrVetRaias + nIndiceRaia)->ptrPrimeira == NULL) // nenhum item na lista ligada?
			(ptrVetRaias + nIndiceRaia)->ptrPrimeira =
			(ptrVetRaias + nIndiceRaia)->ptrUltima = new TRANSACAO();
		else
			(ptrVetRaias + nIndiceRaia)->ptrUltima =
			(ptrVetRaias + nIndiceRaia)->ptrUltima->ptrProxima = new TRANSACAO();
		if((ptrVetRaias + nIndiceRaia)->ptrUltima == NULL) // não teve memória?
		{
			cout << "Não tem memória sulficiente!" << endl;
			PAUSA;
			return false;
		}
		(ptrVetRaias + nIndiceRaia)->ptrUltima->dValor = dValor;
		(ptrVetRaias + nIndiceRaia)->ptrUltima->nTipo = nTipo;
		(ptrVetRaias + nIndiceRaia)->ptrUltima->ptrProxima = NULL;
		// retornar true 
		return true;						// apenas para não dar erro
	}

	// Método para consultar um dado aluno: os seus dados e suas despesas
	//	Parâmetros:
	//		Entrada: int nPeriodo - período 1, 2 ou 3
	//				 int nRaia - número raia dentro do período
	bool ConsultarAluno(int nPeriodo, int nRaia)
	{
		// Exibir o seguinte:
		//		Nome: xxxxxxxxxxxxxxx
		//		Sobrenome: xxxxxxxx
		//		Raia: nn	Valor Mensalidade: zzzzz.zz
		//		Total transacoes: zzzzzz.zz
		//			Tipo: x		Valor: zzzz.zz		(lista ligada de transações)
		//											(listar todas as transações)
		int nIndiceRaia;
		char cOpcao,
			cWork[200];
		TRANSACAO *ptrCorrente;
		nIndiceRaia = ((nPeriodo - 1) * nSalvaQtdeRaia) + (nRaia - 1);
		// Se a raia estiver desocupada retornar false
		if(!(ptrVetRaias + nIndiceRaia)->flgLivreOuOcupado)
		{
			cout << "Raia não ocupada!" << endl;
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
		return true;					// apenas para não dar erro
	}
};