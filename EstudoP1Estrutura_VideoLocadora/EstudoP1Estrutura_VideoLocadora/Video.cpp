// Prova B2 - Estrutura de Dados - Turma da Noite
// FATEC - MC - 28/11/2013 - JCB/Versão 2013
#include "Video.h"

// Função que pede o codigo do filme que tem que ser entre 
//	MENOR_CODIGO e MAIOR_CODIGO ou zero para cancelar a 
//	transação
//	Parâmetros:
//		Entrada: int *ptrCodigo - ponteiro para uma inteira do
//					chamador para receber um código válido digitado pelo
//					operador.
//				 char *ptrTransacao - ponteiro para um string, passado pelo
//					chamador indicando qual é a transação que está sendo
//					realizada: "Cadastramento", "Aluguel Filme" e etc....
//		Retorno: bool - true - indica que o operador digitou um código válido
//						false - indica que o operador cancelou a transação
//								(desistiu de realizar a transação)
bool PedirCodigoFilme(int *ptrCodigo, char *ptrTransacao)
{
	// ****<<??>>******
	// ?.1 - Exibir no video a transação que está sendo realizada
	//	Esta informação é um ponteiro de string passado pelo chamador
	// ?.2 - Ficar em loop até que o operador informe o código de um
	//		 filme válido ou digite zero para cancelar
	// ?.3 - Se o operador informou um código válido copie-o no local
	//			indicado pelo ponteiro informado pelo chamador e
	//			retorne true
	// ?.4 - Se digitou zero como código do filme, retorne false.
	
	cout << "\n\tAção: " << ptrTransacao << endl;
	do
	{
		cout << "Código do filme entre " << MENOR_CODIGO << " e " << MAIOR_CODIGO << endl;
		cout << "Ou zero para cancelar a ação: ";
		cin >> *ptrCodigo;							// código
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
	int i,						// indice genérico
		nCodFilme;				// para receber o código do filme
	FILME stFilme;				// conter os dados de um filme
	char cNomeAluno[] = "Rafael Sano Katurabara",// nome do aluno a ser preenchido
		cOpcao,					// opção do operador
		cRaAluno[] = "RA do aluno",	// RA do aluno a ser preenchido
		cWork[300];				// para formatação de cabeçalhos
	SYSTEMTIME	stTime;			// para buscar data e hora
	setlocale(LC_ALL, "portuguese_brazil");	// aceita acentuação portuguesa
	// Instanciar a classe clVideo e criar o objeto objVideoloc
	// O construtor da classe já está codificado e o vetor de filmes é
	// incializado e 1/4 de filmes são criados por sorteio com o
	// nome do artista principal e o coadjuvante
	clVideo objVideoLoc(&flgOK); // instanciar a classe clVideo
	// ****<<?????>> testar se a construção foi realizada com sucesso

	// ****<< 00 >>**** preencher o seu nome e seu RA
	// Preencher com seu nome o campo cNomeAluno e com seu
	//	RA no campo cRaAluno
	//
	//	Quando for entregar o seu projeto copie o diretório completo para um
	//		"pendrive" e renomei-o para VideoLocadora_xxxxxxxxxx - (xxxx) seu nome
	//
	//	loop infinito com as ações do operador
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
		cout << cWork << endl;		// exibir o cabeçalho do menu
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
		cin >> cOpcao;					// opção do operador
		cin.ignore(1, EOF);				// ignorar a tecla ENTER
		cOpcao = toupper(cOpcao);		// converte opção para maiúscula
		switch(cOpcao)					// avaliar a opção do operador
		{
			case CADASTRAR_FILME:
				// ****<< 02 >>****
				// 2.1 - Chamar a função PedirCodigoFilme informando o endereço
				//		 para receber o código do filme e a transação 
				//		 "Cadastrar Filme".
				//		 Analisar o retorno: se false voltar ao menu principal
				//			se true ir para o passo seguinte...
				// 2.2 - Invocar o método que verificar se o filme já está cadastrado. 
				//			Se estiver avisar ao operador e voltar ao menu principal...
				// 2.3 - Pedir os demais dados sendo que o tipo tem que ser
				//			um dos válidos...(Aventura, comédia, etc....)
				// 2.4 - Invocar o método que cadastra o filme
				// 2.5 - Analisar o retorno do método e avisar ao operador se houve erro
				//			voltar ao menu principal
				if(!PedirCodigoFilme(&nCodFilme, "Cadastrar Filme"))		// operador cancelou?
					break;									// volta ao menu
				// chamar o método para verificar se o filme está cadastrado
				if(objVideoLoc.VerificarSeCadastrado(nCodFilme, &stFilme))
				{	// filme já cadastrado - vai avisar ao operador
					sprintf(cWork, "Código:% 4d Nome: %-50s\nAlugado: %c\nPrinc: %-40s\nCoadj: %-40s",  
						stFilme.nCodFilme, stFilme.cNomeFilme, stFilme.cAlugado,
						stFilme.cArtPrincipal, stFilme.cArtCoadjuvante);
					cout << cWork << endl;
					cout << "\tFilme já cadastrado!" << endl;
					PAUSA;
					break;									// volta ao menu
				}
				// ******<<<<>>>>*********
				//	
				//	continuar a codificação apartir daqui ?????????
				do
				{
					cout << endl
						<< AVENTURA << "- Aventura" << endl 
						<< COMEDIA << " - Comédia" << endl
						<< ROMANCE << " - Romance" << endl
						<< EPICO << " - Épico" << endl
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
				// 3.1 - Chamar a função PedirCodigoFilme informando o endereço
				//		 para receber o código do filme e a transação 
				//		 "Alugar Filme".
				//		 Analisar o retorno: se false voltar ao menu principal
				//			se true ir para o passo seguinte...
				// 3.2 - Chamar o método que verifica se o filme já está alugado. Se estiver
				//			avisar ao operador e voltar ao menu principal...
				// 3.3 - Chamar o método que vai alugar o filme (indica que está alugado) e
				//			volta ao menu principal
				break;
			case DEVOLVER_FILME:
				// ****<< 04 >>****
				// 4.1 - Chamar a função PedirCodigoFilme informando o endereço
				//		 para receber o código do filme e a transação 
				//		 "Devolver Filme".
				//		 Analisar o retorno: se false voltar ao menu principal
				//			se true ir para o passo seguinte...
				// 4.2 - Invocar o método que faz a devolução do filme(indica
				//			que não está alugado).
				// 4.3 - Analisar o retorno do método avisando que ao operador
				//			que o filme não estava alugado ou que estava alugado e
				//			agora não mais.
				break;
			case MOSTRAR_FILME:
				// ****<< 05 >>****
				// 5.1 - Chamar a função PedirCodigoFilme informando o endereço
				//		 para receber o código do filme e a transação 
				//		 "Mostrar Filme".
				//		 Analisar o retorno: se false voltar ao menu principal
				//			se true ir para o passo seguinte...
				// 5.2 - Invocar o método que verifica se o filme está cadastrado ou 
				//		 não.
				// 5.3 - Se o filme não estiver cadastrado avisar ao operador e 
				//			retornar ao menu principal
				// 5.4 - Invocar o método para mostrar os dados do filme e aguardar a
				//			tecla Enter do operador
				break;
			case EXCLUIR_FILME:
				// ****<< 06 >>****
				// 6.1 - Chamar a função PedirCodigoFilme informando o endereço
				//		 para receber o código do filme e a transação 
				//		 "Excluir Filme".
				//		 Analisar o retorno: se false voltar ao menu principal
				//			se true ir para o passo seguinte...
				// 6.2 - Invocar o método que verifica se o filme está cadastrado ou 
				//		 não.
				// 6.3 - Se o filme não estiver cadastrado, avisar ao operador
				//			e voltar ao menu principal.
				// 6.4 - Invocar o método que mostra os dados do filme
				// 6.5 - Solicitar confirmação da exclusão ao operador 
				// 6.6 - Se não confirmar, voltar ao menu principal e
				//			caso contrário invocar o método que exclui o filme
				//			e voltar ao menu principal.
				break;
			case LISTAR_FILMES:
				// ****<< 07 >>****
				// 7.1 - Perguntar qual é o código a iniciar a listagem ou zero para 
				//			desistir da transação...Ficar em loop até que seja
				//			informado um código válido ou zero para cancelar a
				//			transação de listagem
				// 7.2 - Invocar o método que lista os filmes a partir do código 
				//		 Informado
				break;
			case LISTAR_FILMES_ART_PRINC:
				// ****<< 07 >>****
				// 7.1 - Perguntar qual é o nome do artista ou *** para cancelar
				// 7.2 - Se o operador cancelou, voltar ao menu principal
				// 7.3 - Perguntar se Alugado ou Não alugado ou Todos e ficar em loop se
				//			não informar algo válido
				// 7.4 - Invocar o método que lista o artista principal dentro da condição
				//			anteriormente informada pelo operador
				break;
			case LISTAR_FILMES_ART_COADJ:
				// ****<< 08 >>****
				// 8.1 - Perguntar qual é o nome do artista ou *** para cancelar
				// 8.2 - Se o operador cancelou, voltar ao menu principal
				// 8.3 - Perguntar se Alugado ou Não alugado ou Todos e ficar em loop se
				//			não informar algo válido
				// 8.4 - Invocar o método que lista o artista coadjuvante dentro da condição
				//			anteriormente informada pelo operador
				break;
			case SAIR_DO_PROGRAMA:
				cout << "Deseja sair realmente! (S ou N): ";
				cin >> cOpcao;
				if(cOpcao == 'S' || cOpcao == 's')		// sair realmente?
					return;								// sai do programa
				break;
			default:
				cout << "Opção errada!" << endl;
				PAUSA;
		} // switch
	} // while(true)
} // main
