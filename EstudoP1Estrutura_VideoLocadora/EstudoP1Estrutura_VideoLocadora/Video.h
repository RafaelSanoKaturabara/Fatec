// Declarações do Programa de Video Locadora
#include <iostream>
#include <windows.h>
#include <tchar.h>
using namespace std;
// Definições
#define PAUSA					system("pause")
#define LIMPAR_TELA				system("cls")
#define QTDE_FILMES				4000
#define QTDE_A_SORTEAR			QTDE_FILMES / 4	// Qtde filmes a preencher por sorteio
#define QTDE_NOMES_ARTISTA		10				// Qtde de nomes artista princ ou coadju
#define MENOR_CODIGO			1
#define MAIOR_CODIGO			QTDE_FILMES
#define QTDE_HASH				200				// Qtde de entrada no Hash Table
#define CAMINHO_ARQUIVO			TEXT("..\\Filmes.cad") // caminho arquivo
// Menu de Opções do Operador
#define CADASTRAR_FILME			'C'
#define ALUGAR_FILME			'A'
#define DEVOLVER_FILME			'D'
#define MOSTRAR_FILME			'M'
#define LISTAR_FILMES			'L'
#define LISTAR_FILMES_ART_PRINC	'P'
#define LISTAR_FILMES_ART_COADJ	'J'
#define EXCLUIR_FILME			'E'
#define SAIR_DO_PROGRAMA		'S'
// Indicações
#define FILME_CADASTRADO		'C'
#define FILME_NAO_CADASTRADO	'N'
#define FILME_ALUGADO			'A'
#define FILME_NAO_ALUGADO		'N'
#define TODOS_FILMES			'T'
// Tipos de Filmes
#define AVENTURA				'A'
#define COMEDIA					'C'
#define ROMANCE					'R'
#define EPICO					'E'
#define SEXO					'S'
#define QTDE_TIPOS				5
// definições de tipos artistas
#define ARTISTA_PRINCIPAL		'P'
#define ARTISTA_COADJUVANTE		'C'
// Struct de cada filme
typedef struct tagFILME
{
	int nCodFilme;				// código sequencial (1, 2, 3, ......QTDE_FILMES
	char cExiste,				// 'C' - Filme Cadastrado e 'N' - Filme não cadastrado
		cTipo,					// Tipo de Filme:	A - Aventura
								// 					C - Comédia
								//					R - Romance
								//					E - Épico
								//					S - Sexo
		cAlugado,				// 'A' - Alugado e 'N' - não alugado
		cNomeFilme[51],			// Nome do filme
		cArtPrincipal[41],		// Nome do(a) Artista Principal
		cArtCoadjuvante[41];	// Nome do(a) Artista Coadjuvante
} FILME;

// struct para indicar o índice do filme onde participa o artista principal ou
// artista coadjuvante
typedef struct tagLISTA_ARTISTA
{
	int nIndice;					// Indice no vetor de filmes
	char cArtPrinOuCoadju[41];		// nome do Artista Principal ou nome do Coadjuvante
	tagLISTA_ARTISTA *ptrProximo;	// indica o proximo da lista 
}LISTA_ARTISTA;

// struct para cada lista ligada dentro do Hash Table do Artista Principal e
//		do Coadjuvante
typedef struct tagHASH_ARTISTA
{
	LISTA_ARTISTA *ptrPrimeiro,	// primeiro da lista ligada (Principal ou Coadjuvante)
		*ptrUltimo;				// ponteiro para o último da lista ligada
}HASH_ARTISTA;

// struct para Nomes de Artistas Principais e Coadjuvantes
typedef struct tagNOME
{
	char cNomeArtista[41];
} NOME;
//
// classe da VideoLocadora
//
class clVideo
{
	// atributos private da classe
private:
	HASH_ARTISTA vetHashArtPrinc[QTDE_HASH],	// Hash Table para o artista principal
		vetHashArtCoadju[QTDE_HASH];			// Hash Table para o artista coadjuvante
	FILME vetFilmes[QTDE_FILMES],				// vetor que contem todos os possiveis
												// filmes da video locadora
		stFilme;								// struct para conter os dados de um filme
	HANDLE hFile;								// handle do arquivo
	// Método que calcula o Hash do nome do Artista Principal ou do Artista Coadjuvante
	// <<<<*****Método já codificado*****>>>>
	//	Parâmetros:
	//		Entrada: char *ptrPrincOuCoadju - ponteiro para um string que contem o nome
	//					do artista principal ou coadjuvante
	//		Retorno: int - valor do hash calculado do nome do artista ou coadjuvante
	int CalcularHash(char *ptrPrincOuCoadju)
	{
		int i,										// indice genérico
			nExtensao = strlen(ptrPrincOuCoadju),	// extensão do nome
			nSomatoria = 0,							// somatória
			nPesoIni = 13;							// peso da primeira letra do nome
		for (i = 0; i < nExtensao; i++, nPesoIni++) // loop para somatória letra * peso
			nSomatoria += nPesoIni * *(ptrPrincOuCoadju + i); // letra * peso
		return nSomatoria % QTDE_HASH;				// retorna o hash
	}
	// Método que mostra os dados de um filme cujo código é informado
	//	Parâmetros:
	//		Entrada:int nCodFilme - código do filme a ter seu dados exibidos
	//		Retorno: void
	void MostrarDadosDeUmFilme(int nCodFilme)
	{
		//****<< 0002 >>****
		// Codificar a exibição conforme apresentado em 
		// ListarFilmesPorArtista
	}

	// Método que insere o nome do artista principal no Hash Table de 
	// Artistas Principais
	// <<<<*****Método já codificado*****>>>>
	//	Parâmetros:
	//		Entrada:int nHash - hash do nome do artista principal
	//				int nIndice - indice do filme dentro do vetor de filmes que vai
	//								de zero a QTDE_FILMES - 1
	//				char *ptrArtPrinc - nome do artista principal
	//		Retorno: bool - true - inserção foi OK
	//						false - não tem memória disponível para o novo Art. Principal
	bool InserirHashPrincipal(int nHash, int nIndice, char *ptrArtPrinc)
	{
		if(vetHashArtPrinc[nHash].ptrPrimeiro == NULL)		// é o primeiro da lista?
			vetHashArtPrinc[nHash].ptrUltimo = 
			vetHashArtPrinc[nHash].ptrPrimeiro = new LISTA_ARTISTA;
		else												// vai ser o último
			vetHashArtPrinc[nHash].ptrUltimo = 
			vetHashArtPrinc[nHash].ptrUltimo->ptrProximo = new LISTA_ARTISTA;
		//	vai testar se tem memória
		if(vetHashArtPrinc[nHash].ptrUltimo == NULL)
			return false;									// indica que não tem memória
		// vai mover os dados do chamador
		vetHashArtPrinc[nHash].ptrUltimo->nIndice = nIndice;
		strcpy(vetHashArtPrinc[nHash].ptrUltimo->cArtPrinOuCoadju,
			ptrArtPrinc);
		vetHashArtPrinc[nHash].ptrUltimo->ptrProximo = NULL;	// indica que último
		return true;										// avisa que foi tudo bem
	}
	// Método que insere o nome do artista coadjuvante no Hash Table de 
	// Artistas Coadjuvantes
	//	Parâmetros:
	//		Entrada:int nHash - hash do nome do artista coadjuvante
	//				int nIndice - indice do filme dentro do vetor de filmes que vai
	//								de zero a QTDE_FILMES - 1
	//				char *ptrArtPrinc - nome do artista coadjuvante
	//		Retorno: bool - true - inserção foi OK
	//						false - não tem memória disponível para o novo Artista
	//						coadjuvante
	bool InserirHashCoadjuvante(int nHash, int nIndice, char *ptrArtCoadju)
	{
		//*****<< 0001 >>*****
		// codificar a inserção do artista coadjuvante no hash table
		// muito semelhante a inserção no Hash Table de artista principal
		return true;							// para não dar erro ??????????
	}
	// Método para gravar um filme
	//	Parâmetros:
	//		Entrada: LPCVOID stFilme - ponteiro de uma struct que contem filme
	bool GravarFilme(LPCVOID stFilme)
	{
		LPDWORD lpBytesEscritos = 0;
		BOOL flgResult = WriteFile(
			hFile,
			stFilme,
			(DWORD) sizeof(FILME),
			lpBytesEscritos,
			NULL);
		if(FALSE == flgResult)
			return false;
		return true;
	}

	// Método para posicionar a gravação
	bool PosicionarGravacao(int nCodigoFilme)
	{
		DWORD dwReturn = SetFilePointer(
			hFile,
			(LONG) (nCodigoFilme - 1) * sizeof(FILME),
			0,
			FILE_BEGIN);
		if(dwReturn == INVALID_SET_FILE_POINTER)
			return false;
		return true;
	}
	// Métodos publicos
public:
	// Método construtor
	//	Parametro de entrada: bool *ptrOK - ponteiro de uma bool para indicar que a
	//										construção do objeto foi OK
	//										true - indica que a construção foi OK
	//										false - indica que não há memória suficiente
	//												para criar os hashings
	clVideo(bool *ptrOK)
	{
		int i,							// índice genérico
			nIndiceFilme;				// índice do filme
		LPCVOID ptrStruct = &stFilme;	// declaração do ponteiro da struct
		bool *ptrSorteados = new bool[QTDE_FILMES];
		// Os nomes inseridos neste vetor são para cadastrar alguns filmes para 
		// agilizar os testes do programa	
		NOME vetPrincipal[QTDE_NOMES_ARTISTA] = {
					"Stalone",
					"Kevin Spacey",
					"Shelton Melo",
					"Jodie Foster",
					"Adam Sandler",
					"Marco Nanini",
					"Penelope Cruz",
					"Ashley Judd",
					"Tobey Maguire",
					"Roman Duris"},
			vetCoadjuvante[QTDE_NOMES_ARTISTA] = {
					"Shelton Melo",
					"Fernanda Montenegro",
					"Dan Stulbach",
					"Mariana Lima",
					"Maria Flor",
					"Martin Freeman",
					"Danny Devito",
					"Morgan Freeman",
					"Jayme Matarazzo",
					"Natalie Portman"};
		char vetTipos[QTDE_TIPOS] = {
			AVENTURA, 
			COMEDIA, 
			ROMANCE, 
			EPICO, 
			SEXO };
		// Inicialização dos Hash Tables de Artistas Principal e Coadjuvante
		//	Insere nulo em todos os ponteiros do primeiro da lista de cada hash
		for(i = 0; i < QTDE_HASH; i++)
		{	
			vetHashArtPrinc[i].ptrPrimeiro = NULL;
			vetHashArtCoadju[i].ptrPrimeiro = NULL;
		}
		// Abrir um arquivo usando API - CreateFile

		hFile = CreateFile(
			(LPCTSTR) CAMINHO_ARQUIVO,				// nome do arquivo
			GENERIC_READ | GENERIC_WRITE,			// leitura e gravação
			FILE_SHARE_READ,						// compartilha leitura
			NULL,									// segurança normal
			OPEN_EXISTING,							// precisa existir
			FILE_ATTRIBUTE_NORMAL,					// arquivo normal
			NULL);									// sem teplate (leitura assincrona)
		if(hFile == INVALID_HANDLE_VALUE)			// arquivo não existe
		{	// o arquivo não existe
			hFile = CreateFile(
				(LPCTSTR) CAMINHO_ARQUIVO,				// nome do arquivo
				GENERIC_READ | GENERIC_WRITE,			// leitura e gravação
				FILE_SHARE_READ,						// compartilha leitura
				NULL,									// segurança normal
				CREATE_NEW,								// criar um novo
				FILE_ATTRIBUTE_NORMAL,					// arquivo normal
				NULL);									// sem teplate (leitura assincrona)
			if(hFile == INVALID_HANDLE_VALUE)			// erro de abertura?
			{
				*ptrOK = false;							// indica o erro
				return;									// sai do construtor
			}
			// formatar o arquivo de filmes
			for(i = 0; i < QTDE_FILMES; i++)
			{
				stFilme.nCodFilme = i + 1;
				stFilme.cExiste = 'N';					// filme não cadastrado
				// chamar um método para gravar o filme
				if(!GravarFilme(ptrStruct))
				{	// erro de gravação
					CloseHandle(hFile);					// fechar o arquivo
					*ptrOK = false;						// indica o erro
					return;								// cai fora do construtor
				}
			} // for
			// gerar por sorteio um quarto da quantidade de filmes
			for(i = 0; i < QTDE_FILMES; i++)
				*(ptrSorteados + i) = false;			// ninguem sorteado
			srand(210);									// semente para número aleatórios
			// loop de sorteio
			for(i = 0; i < QTDE_A_SORTEAR; i++)
			{
				nIndiceFilme = rand() % QTDE_FILMES;	// índice do filme
				if(*(ptrSorteados + nIndiceFilme))		// já sorteado
				{
					i--;								// vai sortear 1/4
					continue;							// loop do for
				}
				stFilme.nCodFilme = nIndiceFilme + 1;
				// vai sortear o artista principal
				strcpy(stFilme.cArtPrincipal, 
					vetPrincipal[rand() % QTDE_NOMES_ARTISTA].cNomeArtista);
				// vai sortear o artista coadjuvante
				strcpy(stFilme.cArtCoadjuvante, 
					vetCoadjuvante[rand() % QTDE_NOMES_ARTISTA].cNomeArtista);
				// vai montar o nome do filme
				sprintf(stFilme.cNomeFilme,
					"Filme de código: %05d", nIndiceFilme + 1);
				stFilme.cExiste = FILME_CADASTRADO;
				// a instrução abaixo é um "if" ternário
				rand() % 2 == 1 ? stFilme.cAlugado = FILME_NAO_ALUGADO :
					stFilme.cAlugado = FILME_ALUGADO;
				stFilme.cTipo = vetTipos[rand() % QTDE_TIPOS];
				// vai inserir o nome do artista principal na lista ligada do hash
				// correspondente
				if(!InserirHashPrincipal(CalcularHash(stFilme.cArtPrincipal),
					nIndiceFilme, stFilme.cArtPrincipal))
				{	// problema na inserção do Hash Table dos artistas principais
					*ptrOK = false;							// indica que não tem memória
					return;									// cai fora do método
				}
				if(!InserirHashCoadjuvante(CalcularHash(stFilme.cArtCoadjuvante),
					nIndiceFilme, stFilme.cArtCoadjuvante))
				{	// problema na inserção do Hash Table dos artistas coadjuvantes
					*ptrOK = false;
					return;
				}
				// gravar o filme no seu posicional
				
			}  // for

		} // arquivo não existe



		// Inicializar o vetor de filmes na memória indicando o seu código 1, 2, 3, ....
		//	e que o filme não está cadastrado
		for(i = 0; i < QTDE_FILMES; i++)
		{	// vai inicializar o vetor de filmes 
			vetFilmes[i].nCodFilme = i + 1;					// codigo do filme
			vetFilmes[i].cExiste = FILME_NAO_CADASTRADO;	// indica que o filme não está cadastrado
		}
		//
		// Vai criar filmes para popular o vetor de filmes
		//	Este trecho do construtor irá, por sorteio randômico, criar uma 
		//	quantidade de filmes (QTDE_A_SORTEAR) para agilizar os testes
		//
		srand(210);									// semente para número aleatórios
		for(i = 0; i < QTDE_A_SORTEAR; i++)
		{
			nIndiceFilme = rand() % QTDE_FILMES;	// índice do filme
			// vai verificar se o filme já foi sorteado portando já cadastrado
			if(vetFilmes[nIndiceFilme].cExiste == FILME_CADASTRADO)
			{
				i--;
				continue;
			}
			// vai sortear o artista principal
			strcpy(vetFilmes[nIndiceFilme].cArtPrincipal, 
				vetPrincipal[rand() % QTDE_NOMES_ARTISTA].cNomeArtista);
			// vai sortear o artista coadjuvante
			strcpy(vetFilmes[nIndiceFilme].cArtCoadjuvante, 
				vetCoadjuvante[rand() % QTDE_NOMES_ARTISTA].cNomeArtista);
			// vai montar o nome do filme
			sprintf(vetFilmes[nIndiceFilme].cNomeFilme,
				"Filme de código: %05d", nIndiceFilme + 1);
			vetFilmes[nIndiceFilme].cExiste = FILME_CADASTRADO;
			// a instrução abaixo é um "if" ternário
			rand() % 2 == 1 ? vetFilmes[nIndiceFilme].cAlugado = FILME_NAO_ALUGADO :
				vetFilmes[nIndiceFilme].cAlugado = FILME_ALUGADO;
			vetFilmes[nIndiceFilme].cTipo = vetTipos[rand() % QTDE_TIPOS];
			// vai inserir o nome do artista principal na lista ligada do hash
			// correspondente
			if(!InserirHashPrincipal(CalcularHash(vetFilmes[nIndiceFilme].cArtPrincipal),
				nIndiceFilme, vetFilmes[nIndiceFilme].cArtPrincipal))
			{	// problema na inserção do Hash Table dos artistas principais
				*ptrOK = false;							// indica que não tem memória
				return;									// cai fora do método
			}
			if(!InserirHashCoadjuvante(CalcularHash(vetFilmes[nIndiceFilme].cArtCoadjuvante),
				nIndiceFilme, vetFilmes[nIndiceFilme].cArtCoadjuvante))
			{	// problema na inserção do Hash Table dos artistas coadjuvantes
				*ptrOK = false;
			}
			else
				*ptrOK = true;
		} // for do loop de criação de filmes por sorteio
	} // constructor

	// Método que Lista os Filmes por um dado Artista Principal ou Coadjuvante
	//	Parâmetros:
	//		Entrada: char *ptrArtista - nome do artista principal ou coadjuvante
	//				 char cPrincOuCoadju - indica se listagem de artista principal ou
	//								coadjuvante identificado por
	//									ARTISTA_PRINCIPAL
	//									ARTISTA_COADJUVANTE
	//				 char cAlugOuNao - indica o tipo de busca:
	//								FILME_ALUGADO - lista os filmes alugados deste artista
	//								FILME_NAO_ALUGADO - idem não alugado
	//								TODOS_FILMES - lista todos alugados ou não
	//		Retorno: void
	void ListarFilmesPorArtista(char *ptrArtista, char cPrincOuCoadju, char cAlugOuNao)
	{
		int nHash = CalcularHash(ptrArtista),// hash do artista principal ou coadjuvante
			nContador = 0;					// contagem de filmes
		char cDecisao,						// para decisão do operador
			cTipo[25],						// para especificar o tipo
			cAlugado[25],					// para especificar se alugado
			cTipoListagem[20];				// tipo de listagem (principal ou coadjuvante)
		LISTA_ARTISTA *ptrWork,				// ponteiro de trabalho
			*ptrPrimPrcOuCoadj;				// para receber o ponteiro do primeiro da lista
											// ligada do hash table artista principal ou
											// coadjuvante
		cPrincOuCoadju == ARTISTA_COADJUVANTE ? ptrPrimPrcOuCoadj = 
			vetHashArtCoadju[nHash].ptrPrimeiro : ptrPrimPrcOuCoadj =
			vetHashArtPrinc[nHash].ptrPrimeiro; 
		cPrincOuCoadju == ARTISTA_PRINCIPAL ? strcpy(cTipoListagem, "Principal") :
			strcpy(cTipoListagem, "Coadjuvante");
		switch(cAlugOuNao)
		{
			case FILME_ALUGADO:
				strcpy(cAlugado, "Filmes alugados");
				break;
			case FILME_NAO_ALUGADO:
				strcpy(cAlugado, "Filmes não alugados");
				break;
			case TODOS_FILMES:
				strcpy(cAlugado, "Todos os filmes");
				break;
			default:
				strcpy(cAlugado, "Todos os filmes");
		} // switch

		cout << "\tListagem de filmes pelo " << cTipoListagem << ": " << ptrArtista << endl
			<< "\tLista " << cAlugado << endl;
		for(ptrWork = ptrPrimPrcOuCoadj;			// ponteiro do primeiro da lista ligada
			ptrWork;
			ptrWork = ptrWork->ptrProximo)
		{	// para cada um da lista ligada que tem o mesmo hash
			if(strcmp(ptrWork->cArtPrinOuCoadju, ptrArtista) == 0 &&
				( vetFilmes[ptrWork->nIndice].cAlugado == cAlugOuNao ||
				cAlugOuNao == TODOS_FILMES ))
			{	// mesmo artista coadjuvante a ser listado

				switch( vetFilmes[ptrWork->nIndice].cTipo )
				{	// avaliar o tipo de filme
					case AVENTURA:
						strcpy(cTipo, "Aventura");
						break;
					case COMEDIA:
						strcpy(cTipo, "Comédia");
						break;
					case EPICO:
						strcpy(cTipo, "Épico");
						break;
					case ROMANCE:
						strcpy(cTipo, "Romance");
						break;
					case SEXO:
						strcpy(cTipo, "Sexo");
						break;
					default:
						strcpy(cTipo, "Desconhecido");
				} // switch
				cout << "Código: " << vetFilmes[ptrWork->nIndice].nCodFilme
					<< " Nome: " << vetFilmes[ptrWork->nIndice].cNomeFilme << endl
					<< "Principal: " << vetFilmes[ptrWork->nIndice].cArtPrincipal << endl
					<< "Coadjuvante: " << vetFilmes[ptrWork->nIndice].cArtCoadjuvante << endl
					<< "Alugado: " << vetFilmes[ptrWork->nIndice].cAlugado 
					<< " Tipo: " << cTipo << endl;
				nContador++;
				if(nContador == 5)				// listou todos?
				{	// listou todos
					nContador = 0;
					cout << "Vai continuar? (S ou N):";
					cin >> cDecisao;
					if(cDecisao != 'S' && cDecisao != 's')
						break;		
				}
			}
		} // for
		PAUSA;
	} // lista

	// Método que lista filmes a partir de um dado código 
	//	Parâmetros:
	//		Entrada: int nCodInicial - código inicial da listagem dos filmes 
	//		Retorno: void
	void ListarApartirCodigo(int nCodInicial)
	{
		//*****<< >>******
		// Codificar o método não se esquecendo que o índice do vetor de filmes
		//			começa de zero e o código do filme começa de um...
		//	Fazer um cabeçalho para indicar a listagem a partir de ....
		// Codificar um método private que mostra os dados do filme como
		//		em ListarFilmesPorArtista e chamar esse método a cada filme
		//		a ser listado ( MostrarDadosDeUmFilme )
		// Listar cinco filmes e perguntar se continua ou não

	}
	// Método para cadastrar um novo filme
	//	Parâmetros:
	//		Entrada: FILME *ptrStFilme - ponteiro para uma struct que contém os 
	//									dados do novo filme
	//		Retorno: bool - true - indica que foi tudo bem
	//						false - não tem memória para o hashing do artista
	//								principal ou coadjuvante
	bool CadastrarFilme(FILME *ptrStFilme)
	{
		//*****<< 0003 >>******
		// Codificar o método não se esquecendo que o índice do vetor de filmes
		//			começa de zero e o código do filme começa de um...

		return true;					// para não dar erro ?????????
	}
	// Método que executa a devolução do filme 
	//	Parâmetros:
	//		Entrada: int nCodFilme - código do filme que está sendo devolvido 
	//		Retorno: bool - true - indica que o filme agora está não alugado
	//						false - indica que o filme não estava alugado
	bool DevolucaoFilme(int nCodFilme)
	{
		//*****<< 0004 >>******
		// Codificar o método não se esquecendo que o índice do vetor de filmes
		//			começa de zero e o código do filme começa de um...
	}

	// Método que verifica se o filme está cadastrado ou não
	// <<<<*****Método já codificado*****>>>>
	//	Parâmetros:
	//		Entrada: int nCodFilme - código do filme que está sendo verificado 
	//				 FILME *ptrStFilme - ponteiro de uma struct para receber os dados
	//									do filme se o mesmo já estiver cadastrado
	//		Retorno: bool - true - indica que o filme está cadastrado
	//						false - indica que o filme não está cadastrado
	bool VerificarSeCadastrado(int nCodFilme, FILME *ptrStFilme)
	{
		// Codificar o método não se esquecendo que o índice do vetor de filmes
		//			começa de zero e o código do filme começa de um..
		if(vetFilmes[nCodFilme - 1].cExiste == FILME_CADASTRADO)
		{	// filme já está cadastrado - vai copiar os seus dados e avisar
			memcpy_s(ptrStFilme, sizeof(FILME), &vetFilmes[nCodFilme - 1], sizeof(FILME));
			return true;					// indica que filme cadastrado
		}
		return false;						// indica que não cadastrado
	}
	// Método público que verifica se filme já alugado ou não
	//	Parâmetros:
	//		Entrada: int nCodFilme - código do filme que está sendo verificado 
	//				 FILME *ptrStFilme - ponteiro de uma struct para receber os dados
	//									do filme se o mesmo já estiver alugado
	//		Retorno: bool - true - indica que o filme está alugado
	//						false - indica que o filme não está alugado
	bool VerificarSeAlugado(int nCodFilme, FILME *ptrStFilme)
	{
		//*****<< 0005 >>******
		// Codificar o método não se esquecendo que o índice do vetor de filmes
		//			começa de zero e o código do filme começa de um..
		return true;							// para não dar erro
	}
	// Método que aluga um filme que não está alugado - deve ter sido testado antes
	//	Parâmetros:
	//		Entrada: int nCodFilme - código do filme que está sendo verificado 
	void AlugarFilme(int nCodFilme)
	{
		vetFilmes[nCodFilme - 1].cAlugado = FILME_ALUGADO;			// indica que filme alugado
	}
	// Método que mostra os dados de um filme cujo código foi passado 
	//	Parâmetros:
	//		Entrada: int nCodFilme - código do filme a ser mostrado 
	//		Retorno: void
	void MostrarFilme(int nCodFilme)
	{
		//*****<< 0006 >>******
		// Codificar o método não se esquecendo que o índice do vetor de filmes
		//			começa de zero e o código do filme começa de um...
		//		Chamar o método MostrarDadosDeUmFilme passando o código do filme
	}

	// Método que exclui o filme indicando que não está cadastrado
	//	Parâmetros:
	//		Entrada: int nCodFilme - código do filme que está sendo excluido 
	//		Retorno: bool - true - indica que o filme foi excluido
	//						false - indica que o filme não está cadastrado
	bool ExcluirFilme(int nCodFilme)
	{
		//*****<< >>******
		// Codificar o método não se esquecendo que o índice do vetor de filmes
		//			começa de zero e o código do filme começa de um...
		//		Se o filme não estiver cadastrado retornar false e caso contrário
		//			indicar que o filme não está cadastrado
		return true;							// para não dar erro ?????????
	}
};	// fim da classe