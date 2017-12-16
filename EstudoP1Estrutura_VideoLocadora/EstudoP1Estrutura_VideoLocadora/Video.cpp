// Prova B2 - Estrutura de Dados - Turma da Noite
// FATEC - MC - 28/11/2013 - JCB/Vers�o 2013
#include "Video.h"

// Fun��o que pede o codigo do filme que tem que ser entre 
//	MENOR_CODIGO e MAIOR_CODIGO ou zero para cancelar a 
//	transa��o
//	Par�metros:
//		Entrada: int *ptrCodigo - ponteiro para uma inteira do
//					chamador para receber um c�digo v�lido digitado pelo
//					operador.
//				 char *ptrTransacao - ponteiro para um string, passado pelo
//					chamador indicando qual � a transa��o que est� sendo
//					realizada: "Cadastramento", "Aluguel Filme" e etc....
//		Retorno: bool - true - indica que o operador digitou um c�digo v�lido
//						false - indica que o operador cancelou a transa��o
//								(desistiu de realizar a transa��o)
bool PedirCodigoFilme(int *ptrCodigo, char *ptrTransacao)
{
	// ****<<??>>******
	// ?.1 - Exibir no video a transa��o que est� sendo realizada
	//	Esta informa��o � um ponteiro de string passado pelo chamador
	// ?.2 - Ficar em loop at� que o operador informe o c�digo de um
	//		 filme v�lido ou digite zero para cancelar
	// ?.3 - Se o operador informou um c�digo v�lido copie-o no local
	//			indicado pelo ponteiro informado pelo chamador e
	//			retorne true
	// ?.4 - Se digitou zero como c�digo do filme, retorne false.
	
	cout << "\n\tA��o: " << ptrTransacao << endl;
	do
	{
		cout << "C�digo do filme entre " << MENOR_CODIGO << " e " << MAIOR_CODIGO << endl;
		cout << "Ou zero para cancelar a a��o: ";
		cin >> *ptrCodigo;							// c�digo
		if(*ptrCodigo == 0)							// cancelou?
			return false;
	}while(*ptrCodigo < MENOR_CODIGO ||
		*ptrCodigo > MAIOR_CODIGO);
	return true;									// indica que foi tudo ok
}

// Entry Point do Progrma
void main(void)
{
	bool flgOK;					// para receber os status do construtor
	int i,						// indice gen�rico
		nCodFilme;				// para receber o c�digo do filme
	FILME stFilme;				// conter os dados de um filme
	char cNomeAluno[] = "Rafael Sano Katurabara",// nome do aluno a ser preenchido
		cOpcao,					// op��o do operador
		cRaAluno[] = "RA do aluno",	// RA do aluno a ser preenchido
		cWork[300];				// para formata��o de cabe�alhos
	SYSTEMTIME	stTime;			// para buscar data e hora
	setlocale(LC_ALL, "portuguese_brazil");	// aceita acentua��o portuguesa
	// Instanciar a classe clVideo e criar o objeto objVideoloc
	// O construtor da classe j� est� codificado e o vetor de filmes �
	// incializado e 1/4 de filmes s�o criados por sorteio com o
	// nome do artista principal e o coadjuvante
	clVideo objVideoLoc(&flgOK); // instanciar a classe clVideo
	// ****<<?????>> testar se a constru��o foi realizada com sucesso

	// ****<< 00 >>**** preencher o seu nome e seu RA
	// Preencher com seu nome o campo cNomeAluno e com seu
	//	RA no campo cRaAluno
	//
	//	Quando for entregar o seu projeto copie o diret�rio completo para um
	//		"pendrive" e renomei-o para VideoLocadora_xxxxxxxxxx - (xxxx) seu nome
	//
	//	loop infinito com as a��es do operador
	//
	while(true)
	{
		LIMPAR_TELA;
		// exibir o menu principal
		GetLocalTime(&stTime);		// buscar data e hora do sistema
		sprintf(cWork,
			"\tFATEC-MC-EstDados-Video Locadora - Turma Noite %02d/%02d/%04d %02d:%02d\n\tAluno:%s RA:%s",
			stTime.wDay, stTime.wMonth, stTime.wYear,
			stTime.wHour, stTime.wMinute,
			cNomeAluno, cRaAluno);
		cout << cWork << endl;		// exibir o cabe�alho do menu
		cout << CADASTRAR_FILME << " - Cadastrar Filme" << endl;
		cout << ALUGAR_FILME << " - Alugar Filme" << endl;
		cout << DEVOLVER_FILME << " - Devolver Filme" << endl;
		cout << MOSTRAR_FILME << " - Mostrar dados de um filme" << endl;
		cout << LISTAR_FILMES << " - Listar filmes" << endl;
		cout << LISTAR_FILMES_ART_PRINC << " - Listar filmes por artista principal" << endl;
		cout << LISTAR_FILMES_ART_COADJ << " - Listar filmes por artista coadjuvante" << endl;
		cout << EXCLUIR_FILME << " - Excluir um filme" << endl;
		cout << SAIR_DO_PROGRAMA << " - Sair do programa" << endl;
		cout << "\tSelecione: ";
		cin >> cOpcao;					// op��o do operador
		cin.ignore(1, EOF);				// ignorar a tecla ENTER
		cOpcao = toupper(cOpcao);		// converte op��o para mai�scula
		switch(cOpcao)					// avaliar a op��o do operador
		{
			case CADASTRAR_FILME:
				// ****<< 02 >>****
				// 2.1 - Chamar a fun��o PedirCodigoFilme informando o endere�o
				//		 para receber o c�digo do filme e a transa��o 
				//		 "Cadastrar Filme".
				//		 Analisar o retorno: se false voltar ao menu principal
				//			se true ir para o passo seguinte...
				// 2.2 - Invocar o m�todo que verificar se o filme j� est� cadastrado. 
				//			Se estiver avisar ao operador e voltar ao menu principal...
				// 2.3 - Pedir os demais dados sendo que o tipo tem que ser
				//			um dos v�lidos...(Aventura, com�dia, etc....)
				// 2.4 - Invocar o m�todo que cadastra o filme
				// 2.5 - Analisar o retorno do m�todo e avisar ao operador se houve erro
				//			voltar ao menu principal
				if(!PedirCodigoFilme(&nCodFilme, "Cadastrar Filme"))		// operador cancelou?
					break;									// volta ao menu
				// chamar o m�todo para verificar se o filme est� cadastrado
				if(objVideoLoc.VerificarSeCadastrado(nCodFilme, &stFilme))
				{	// filme j� cadastrado - vai avisar ao operador
					sprintf(cWork, "C�digo:% 4d Nome: %-50s\nAlugado: %c\nPrinc: %-40s\nCoadj: %-40s",  
						stFilme.nCodFilme, stFilme.cNomeFilme, stFilme.cAlugado,
						stFilme.cArtPrincipal, stFilme.cArtCoadjuvante);
					cout << cWork << endl;
					cout << "\tFilme j� cadastrado!" << endl;
					PAUSA;
					break;									// volta ao menu
				}
				// ******<<<<>>>>*********
				//	
				//	continuar a codifica��o apartir daqui ?????????
				do
				{
					cout << endl
						<< AVENTURA << "- Aventura" << endl 
						<< COMEDIA << " - Com�dia" << endl
						<< ROMANCE << " - Romance" << endl
						<< EPICO << " - �pico" << endl
						<< SEXO << " - Sexo" << endl
						<< "Zero - Voltar ao menu anterior" << endl
						<< "\tDigite tipo de filme: ";
					cin >> stFilme.cTipo;
					if(stFilme.cTipo == '0')
						break;
					stFilme.cTipo = toupper(stFilme.cTipo);
				}while(stFilme.cTipo != AVENTURA 
					&& stFilme.cTipo != COMEDIA
					&& stFilme.cTipo != ROMANCE
					&& stFilme.cTipo != EPICO
					&& stFilme.cTipo != SEXO);
				
				
				//
				break;										// volta ao menu
			case ALUGAR_FILME:
				// ****<< 03 >>****
				// 3.1 - Chamar a fun��o PedirCodigoFilme informando o endere�o
				//		 para receber o c�digo do filme e a transa��o 
				//		 "Alugar Filme".
				//		 Analisar o retorno: se false voltar ao menu principal
				//			se true ir para o passo seguinte...
				// 3.2 - Chamar o m�todo que verifica se o filme j� est� alugado. Se estiver
				//			avisar ao operador e voltar ao menu principal...
				// 3.3 - Chamar o m�todo que vai alugar o filme (indica que est� alugado) e
				//			volta ao menu principal
				break;
			case DEVOLVER_FILME:
				// ****<< 04 >>****
				// 4.1 - Chamar a fun��o PedirCodigoFilme informando o endere�o
				//		 para receber o c�digo do filme e a transa��o 
				//		 "Devolver Filme".
				//		 Analisar o retorno: se false voltar ao menu principal
				//			se true ir para o passo seguinte...
				// 4.2 - Invocar o m�todo que faz a devolu��o do filme(indica
				//			que n�o est� alugado).
				// 4.3 - Analisar o retorno do m�todo avisando que ao operador
				//			que o filme n�o estava alugado ou que estava alugado e
				//			agora n�o mais.
				break;
			case MOSTRAR_FILME:
				// ****<< 05 >>****
				// 5.1 - Chamar a fun��o PedirCodigoFilme informando o endere�o
				//		 para receber o c�digo do filme e a transa��o 
				//		 "Mostrar Filme".
				//		 Analisar o retorno: se false voltar ao menu principal
				//			se true ir para o passo seguinte...
				// 5.2 - Invocar o m�todo que verifica se o filme est� cadastrado ou 
				//		 n�o.
				// 5.3 - Se o filme n�o estiver cadastrado avisar ao operador e 
				//			retornar ao menu principal
				// 5.4 - Invocar o m�todo para mostrar os dados do filme e aguardar a
				//			tecla Enter do operador
				break;
			case EXCLUIR_FILME:
				// ****<< 06 >>****
				// 6.1 - Chamar a fun��o PedirCodigoFilme informando o endere�o
				//		 para receber o c�digo do filme e a transa��o 
				//		 "Excluir Filme".
				//		 Analisar o retorno: se false voltar ao menu principal
				//			se true ir para o passo seguinte...
				// 6.2 - Invocar o m�todo que verifica se o filme est� cadastrado ou 
				//		 n�o.
				// 6.3 - Se o filme n�o estiver cadastrado, avisar ao operador
				//			e voltar ao menu principal.
				// 6.4 - Invocar o m�todo que mostra os dados do filme
				// 6.5 - Solicitar confirma��o da exclus�o ao operador 
				// 6.6 - Se n�o confirmar, voltar ao menu principal e
				//			caso contr�rio invocar o m�todo que exclui o filme
				//			e voltar ao menu principal.
				break;
			case LISTAR_FILMES:
				// ****<< 07 >>****
				// 7.1 - Perguntar qual � o c�digo a iniciar a listagem ou zero para 
				//			desistir da transa��o...Ficar em loop at� que seja
				//			informado um c�digo v�lido ou zero para cancelar a
				//			transa��o de listagem
				// 7.2 - Invocar o m�todo que lista os filmes a partir do c�digo 
				//		 Informado
				break;
			case LISTAR_FILMES_ART_PRINC:
				// ****<< 07 >>****
				// 7.1 - Perguntar qual � o nome do artista ou *** para cancelar
				// 7.2 - Se o operador cancelou, voltar ao menu principal
				// 7.3 - Perguntar se Alugado ou N�o alugado ou Todos e ficar em loop se
				//			n�o informar algo v�lido
				// 7.4 - Invocar o m�todo que lista o artista principal dentro da condi��o
				//			anteriormente informada pelo operador
				break;
			case LISTAR_FILMES_ART_COADJ:
				// ****<< 08 >>****
				// 8.1 - Perguntar qual � o nome do artista ou *** para cancelar
				// 8.2 - Se o operador cancelou, voltar ao menu principal
				// 8.3 - Perguntar se Alugado ou N�o alugado ou Todos e ficar em loop se
				//			n�o informar algo v�lido
				// 8.4 - Invocar o m�todo que lista o artista coadjuvante dentro da condi��o
				//			anteriormente informada pelo operador
				break;
			case SAIR_DO_PROGRAMA:
				cout << "Deseja sair realmente! (S ou N): ";
				cin >> cOpcao;
				if(cOpcao == 'S' || cOpcao == 's')		// sair realmente?
					return;								// sai do programa
				break;
			default:
				cout << "Op��o errada!" << endl;
				PAUSA;
		} // switch
	} // while(true)
} // main
