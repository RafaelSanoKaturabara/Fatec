// Programa de controle de estoque
// FATEC - MC - 20/11/2014
// Período - Noite
#include "Estoque.h"


// Função que pede um código válido de grupo e um código de produto
//	Esta função vai ficar em looping pedindo um grupo válido e
//  um código de produto ou zero no grupo 
//	ou zero no código do produto se o operador desejar cancelar.
//	Parâmetros: 
//		Entrada:
//				int *ptrGrupo - ponteiro do código do grupo - indica onde
//								será armazenado o código do grupo
//				int *ptrCodigo - ponteiro do código do produto - indica 
//								onde será armazenado o código do produto
//				char *ptrTransacao - ponteiro de um string que contém a transação que
//								está sendo realizada
//		Retorno: bool - true - indica que a transação não foi cancelada e nas variáveis
//								indicadas pelos ponteiros estão dados válidos
//						false - a transação foi cancelada
//
bool PedeValidaGrupoCodigoProduto(int *ptrGrupo, int *ptrCodigo, char *ptrTransacao)
{
	bool flgEncontrou = true;
	char vetNomesGrupos[][10] = 
	{
		"Pesados",
		"Cereais",
		"Enlatados",
		"Embutidos",
		"Bebidas",
		"Limpeza",
		"Higiene"
	};
	int i,
		vetGrupos[] =					// tabela de grupos de produtos
	{
		PESADOS, 
		CEREAIS,
		ENLATADOS,
		EMBUTIDOS,
		BEBIDAS,
		LIMPEZA,
		HIGIENE 
	};
	cout << endl;
	do
	{
		for (i = 0; i < (sizeof(vetNomesGrupos) / (sizeof(char)*10)); i++)
		{
			cout << i + 1 << " - " << vetNomesGrupos[i] << endl;
		}
		cout << "\n\tDigite o grupo do produto de 1 até " << QUANTIDADE_HASH_GRUPOS << " ou zero para sair: ";
		cin >> *ptrGrupo;
		if(*ptrGrupo == 0)	// digitou sair?
			return false;
		// loop de verificação do grupo válido
		for (i = 0; i < (sizeof(vetGrupos) / sizeof(int)); i++)
		{
			if (vetGrupos[i] == *ptrGrupo)
			{
				flgEncontrou = false;
				break;
			}
		}
	} while (flgEncontrou);
	do
	{
		cout << "Digite o código do produto do grupo " << vetNomesGrupos[*ptrGrupo - 1] << " ou zero para cancelar: ";
		cin >> *ptrCodigo;
		if(*ptrCodigo == 0)	// digitou número negativo ou zero?
			return false;	// retorna
	} while (*ptrCodigo < 0);	
	return true;						// Para não dar erro!!!!!!
}

// Função principal do programa
void main(void)
{
	bool flgStatus;						// status da construção
	double dQtde,	
		dValorTotalEntrada;
	char cOpcao,						// Opção do menu informada pelo operador
		cWork[200];						// para formatar os sprintf
	int i, j,							// índice genérico
		nGrupo,							// para receber o grupo do produto
		nCodigo,						// para receber o código produto
		nPosicional;					// para receber o posicional do registro de produto para regravação
	int vetGrupos[] =					// tabela de grupos de produtos
	{
		PESADOS, 
		CEREAIS,
		ENLATADOS,
		EMBUTIDOS,
		BEBIDAS,
		LIMPEZA,
		HIGIENE 
	};
	char vetNomesGrupos[][10] = 
	{
		"Pesados",
		"Cereais",
		"Enlatados",
		"Embutidos",
		"Bebidas",
		"Limpeza",
		"Higiene"
	};
	PRODUTO stProduto;					// struct para conter dados de um produto
	SYSTEMTIME	stTime;					// para receber data e hora
	// <<<<< 2 >>>>> Codificar abaixo o seu nome e seu RA
	char szNomeAluno[] = "Informar seu nome",
		szRA_Aluno[] = "Informar seu RA";
	setlocale(LC_ALL, "portuguese_brazil");		// para aceitar acentuação brasileira

	// o código abaixo é para tratamento do ponto decimal
	// que está sendo fixado a duas decimais
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);
	// Instanciar a classe clEstoque e criar o objeto objEstoque.
	clEstoque objEstoque(&flgStatus);
	if(!flgStatus)							// erro de construção?
	{	// não tem memória disponível para os Hash Tables e Listas Ligadas
		cout << "Erro de construção!" << endl
			<< "Termine a execução de outros programas inúteis" << endl
			<< "Recarregue este programa novamente!" << endl;
		PAUSA;
		return;								// cai fora do programa
	}
	
	//
	//	loop infinito
	//
	while(true)								// loop infinito
	{
		// exibir o menu de ações a serem realizadas pelo operador
		system("cls");
		GetLocalTime(&stTime);
		sprintf(cWork, "\tFATEC-MC - SisEstoque %02d/%02d/%04d às %02d:%02d\n\tOperador:%s Matrícula:%s",
			stTime.wDay, stTime.wMonth, stTime.wYear,
			stTime.wHour, stTime.wMinute,
			szNomeAluno, szRA_Aluno);
		cout << cWork << endl;
		cout << CADASTRAR_PRODUTO << " - cadastrar um novo produto" << endl;
		cout << EXIBIR_DADOS_PRODUTO << " - mostrar os dados do produto" << endl;
		cout << DAR_ENTRADA_ESTOQUE << " - dar entrada no estoque de um produto" << endl;
		cout << DAR_BAIXA_ESTOQUE << " - dar baixa no estoque de um produto" << endl;
		cout << LISTAGEM_GERAL_PRODUTOS << " - listagem geral dos produtos" << endl;
		cout << LISTAGEM_GERAL_GRUPO << " - listagem de um grupo válido" << endl;
		cout << EXCLUIR_PRODUTO << " - excluir um dado produto" << endl;
		cout << SAIR_DO_PROGRAMA << " - sair do programa" << endl;
		cout << "\tSelecione: ";
		cin		>> cOpcao;						// escolha do operador
		cOpcao = toupper(cOpcao);				// converte sempre para maiúsculo
		// analisar a opção feita pelo operador
		switch(cOpcao)							// avalia a opção escolhida
		{
			case CADASTRAR_PRODUTO:
				// <<<<4>>>>. Buscar o grupo do produto e o produto
				//				através da função PedeValidaGrupoCodigoProduto
				//				Verificar se a transação foi cancelada e voltar ao menu
				if(!PedeValidaGrupoCodigoProduto(&nGrupo, &nCodigo, "Cadastrar produto"))
				{
					cout << "Cancelou!" << endl;
					PAUSA;
					break;
				}
				//			 Buscar os dados do produto invocando o método
				//			 objEstoque.VerificaSeExiste
				//			 Analisar o retorno deste metodo
				if (objEstoque.VerificaSeExiste(nGrupo, nCodigo, &nPosicional, &stProduto))
				//			Se o produto já existe avisar ao operador exibindo os
				//				dados do produto e 
				//			aguardar sua visualização e voltar ao menu
				{
					cout << "Produto já existente" << endl;
					sprintf_s(cWork, "Descrição: %-50s Estoque: %-4.0f\nPreço unitário médio: R$ %-7.2f Valor total do estoque: R$%-10.2f\nAtivo: %c", 
						stProduto.cDescricaoProd, stProduto.dEstoque, stProduto.dPrecoUnitMedio, stProduto.dValorTotalEstoque, stProduto.cProdutoAtivo); 
					cout << cWork << endl;
					PAUSA;
					break;
				}
				//			Caso não exista pedir os dados do novo produto (Apenas Descrição)  ao
				//			operador. Indicar que o produto está ativo e zerar preço unitário e quantidades
				//			Gravar o novo produto através do método  objEstoque.CadastrarProduto
				cout << "Digite a descrição do produto: ";
				cin.ignore(1, EOF);
				cin.getline(stProduto.cDescricaoProd, 50, '\n');
				stProduto.cProdutoAtivo = 'A';
				stProduto.dEstoque = 0;
				stProduto.nCodigoGrupo = nGrupo;
				stProduto.nCodProdGrupo = nCodigo;
				stProduto.dPrecoUnitMedio = 0.0;
				stProduto.dValorTotalEstoque = 0.0;
				if (!objEstoque.CadastrarProduto(&stProduto))
				//			analisar o seu retorno e voltar ao menu
				//			Sempre testar os erros possíveis e avisar ao
				//			perador caso haja erro.
				// ....
				{
					cout << "Erro ao cadastrar o produto!" << endl;
					PAUSA;
					break;
				}
				cout << "Produto inserido!" << endl;
				PAUSA;
				break;							// cai fora do switch
			case EXIBIR_DADOS_PRODUTO:
				// <<<<5>>>>. Buscar o grupo do produto e o produto
				//				através da função PedeValidaGrupoCodigoProduto
				if(!PedeValidaGrupoCodigoProduto(&nGrupo, &nCodigo, "Exibir produto"))
				{
					cout << "Cancelou!" << endl;
					PAUSA;
					break;
				}
				//				Verificar se a transação foi cancelada e voltar ao menu
				//			 Buscar os dados do produto invocando o método
				//			 objEstoque.VerificaSeExiste
				//			 Analisar o retorno desta metodo
				if (objEstoque.VerificaSeExiste(nGrupo, nCodigo, &nPosicional, &stProduto))
				{
					cout << "Produto encontrado!" << endl;
					sprintf_s(cWork, "Descrição: %-50s Estoque: %-4.0f\nPreço unitário médio: R$ %-7.2f Valor total do estoque: R$%-10.2f\nAtivo: %c", 
						stProduto.cDescricaoProd, stProduto.dEstoque, stProduto.dPrecoUnitMedio, stProduto.dValorTotalEstoque, stProduto.cProdutoAtivo); 
					cout << cWork << endl;
					PAUSA;
					break;
				}
				cout << "Não foi encontrado um produto para o mesmo código!" << endl;
				//			Se o produto já existe avisar ao operador exibindo os
				//				dados do produto e 
				//			aguardar sua visualização e voltar ao menu
				//			Caso não exista avisar ao operador e voltar ao menu
				// ......
				PAUSA;
				break;							// cai fora do switch
			case DAR_ENTRADA_ESTOQUE:
				// <<<<6>>>>. Buscar o grupo do produto e o produto
				//				através da função PedeValidaGrupoCodigoProduto
				if(!PedeValidaGrupoCodigoProduto(&nGrupo, &nCodigo, "Entrada de produto"))
				{
					cout << "Cancelou!" << endl;
					PAUSA;
					break;
				}
				//				Verificar se a transação foi cancelada e voltar ao menu
				//			 Buscar os dados do produto invocando o método
				//			 objEstoque.VerificaSeExiste
				//			 Analisar o retorno desta metodo
				//			Se o produto não está cadastrado ou não existe 
				//				avisar ao operador e voltar ao menu
				if (!objEstoque.VerificaSeExiste(nGrupo, nCodigo, &nPosicional, &stProduto))
				{
					cout << "Produto não encontrado!" << endl;
					PAUSA;
					break;
				}
				cout << "Produto encontrado!" << endl;
				sprintf_s(cWork, "Descrição: %-50s Estoque: %-4.0f\nPreço unitário médio: R$ %-7.2f Valor total do estoque: R$%-10.2f\nAtivo: %c", 
						stProduto.cDescricaoProd, stProduto.dEstoque, stProduto.dPrecoUnitMedio, stProduto.dValorTotalEstoque, stProduto.cProdutoAtivo); 
				cout << cWork << endl;
				PAUSA;
				//			Caso exista os seus dados já estão na struct que
				//			foi passada.
				//			Exibir os dados do produto e (mesma visualização com sprintf que já foi feita)
				//			pedir a quantidade e valor total da entrada.
				do
				{
					cout << "Digite a quantidade total de entrada: ";
					cin >> dQtde;
				}while (dQtde < 1);
				do
				{
					cout << "Digite o valor total da entrada em R$: ";
					cin >> dValorTotalEntrada;
				} while(dValorTotalEntrada <= 0);
				//			Atualizar os dados do produto quanto a preço
				//			médio, quantidade em estoque etc, conforme
				//			especificado no Estoque.h
				stProduto.dEstoque += dQtde;
				stProduto.dValorTotalEstoque += dValorTotalEntrada;
				stProduto.dPrecoUnitMedio = (stProduto.dValorTotalEstoque) / (stProduto.dEstoque);
				//			Formatar a data e hora da última compra com sprintf no formato especificado
				//			na struct do produto.
				GetLocalTime(&stTime);
				//			Gravar o novo registro agora com o estoque
				sprintf_s(stProduto.cDataUltimaCompra, "%02d/%02d/%04d %02d:%02d", 
					stTime.wDay, stTime.wMonth, stTime.wYear, stTime.wHour, stTime.wMinute);
				//			atualizado atraves do método objEstoque.RegravaProduto
				//			Informar ao operador se houve qualquer erro
				if(!objEstoque.RegravaProduto(nPosicional, &stProduto))
				{
					cout << "Erro ao regravar o produto!" << endl;
					PAUSA;
					break;
				}
				//			Voltar ao menu
				// ....
				cout << "Alterado com sucesso!" << endl;
				PAUSA;
				break;							// cai fora do switch
			case DAR_BAIXA_ESTOQUE:
				// <<<<7>>>>. Buscar o grupo do produto e o produto
				//				através da função PedeValidaGrupoCodigoProduto
				//				Verificar se a transação foi cancelada e voltar ao menu
				if(!PedeValidaGrupoCodigoProduto(&nGrupo, &nCodigo, "Baixa de produto"))
				{
					cout << "Cancelou!" << endl;
					PAUSA;
					break;
				}
				//			 Buscar os dados do produto invocando o método
				//			 objEstoque.VerificaSeExiste
				//			 Analisar o retorno desta metodo
				if (!objEstoque.VerificaSeExiste(nGrupo, nCodigo, &nPosicional, &stProduto))
				{
					cout << "Produto não encontrado!" << endl;
					PAUSA;
					break;
				}
				//			Se o produto não está cadastrado ou não existe 
				//				avisar ao operador e voltar ao menu
				//			Caso exista os seus dados já estão na struct que
				//			foi passada.
				//			Exibir os dados do produto e (mesma visualização com sprintf que já foi feita)
				cout << "Produto encontrado!" << endl;
				sprintf_s(cWork, "Descrição: %-50s Estoque: %-4.0f\nPreço unitário médio: R$ %-7.2f Valor total do estoque: R$%-10.2f\nAtivo: %c", 
						stProduto.cDescricaoProd, stProduto.dEstoque, stProduto.dPrecoUnitMedio, stProduto.dValorTotalEstoque, stProduto.cProdutoAtivo); 
				cout << cWork << endl;
				PAUSA;
				//			pedir a quantidade a ser dado baixa (saída).
				do
				{
					cout << "Digite a quantidade total de saída: ";
					cin >> dQtde;
				}while (dQtde < 1);
				//			Atualizar apenas a quantidade em estoque e o
				//			valor total do estoque
				stProduto.dEstoque -= dQtde;
				stProduto.dValorTotalEstoque -= (dQtde * stProduto.dPrecoUnitMedio);
				//			Gravar o novo registro agora com o estoque
				//			atualizado atraves da função de gravar
				if(!objEstoque.RegravaProduto(nPosicional, &stProduto))
				{
					cout << "Erro ao gravar o produto!" << endl;
					PAUSA;
					break;
				}
				//			Informar ao operador se houve qualquer erro
				//			Voltar ao menu
				// ....
				cout << "Saída realizada com sucesso!" << endl;
				PAUSA;
				break;							// cai fora do switch
			case LISTAGEM_GERAL_PRODUTOS:
				// <<<<8>>>> - Posicionar no primeiro registro do cadastro de
				//	produtos
				// Fazer um cabeçalho indicando que é listagem geral de produtos
			LIMPAR_TELA;
			cout << "\n\tListagem geral de produtos!" << endl;
				// Fazer um loop para ler até o fim do arquivo
			i = j = 0;
			cout << "Cód       Grupo     Descrição                   Qtd.estoque  Prec.Unit.Médio  Val.Tot.Estoque" << endl;
			while (objEstoque.LerUmProduto(i++, &stProduto))
			{
				// A cada registro lido verificar se produto ativo
				// Se estiver inativo passar para o próximo e se
				// estiver ativo mostrar os dados do produto
				if(stProduto.cProdutoAtivo == 'A')
				{
					sprintf_s(cWork, "%09d %-9s %-27s %-12.0f R$%-14.2f R$%-15.2f", stProduto.nCodProdGrupo, vetNomesGrupos[stProduto.nCodigoGrupo - 1], stProduto.cDescricaoProd, 
						stProduto.dEstoque, stProduto.dPrecoUnitMedio, stProduto.dValorTotalEstoque);
					cout << cWork << endl;
					j++;
				}
				// A cada 5 produtos exibidos perguntar ao operador
				if (j == 5)
				{
					cout << "Deseja listar os próximos itens? (S/N): ";
					cin >> cOpcao;
					// se deseja continuar. Se ele disser que sim listar 
					// mais 5 produtos e assim por diante e se disser que não
					if(cOpcao == 'S' || cOpcao == 's')
					{
						j = 0; // zera a contagem
						continue;	// volta para o while
					}
					break;
				}
			}
			cout << "Fim da listagem!" << endl;	
			PAUSA;
				// Voltar ao menu
				// ....

				break;							// cai fora do switch
			case LISTAGEM_GERAL_GRUPO:
				// <<<<9>>>> - Pedir o grupo a ser listado e invocar o
				//	método objEstoque.ListarProdutosDoGrupo
				do
				{
					cout << "Digite o grupo para ser listado: ";
					cin >> nGrupo;				
				}
				while (nGrupo < 1 || nGrupo > QUANTIDADE_HASH_GRUPOS);
				objEstoque.ListarProdutosDoGrupo(nGrupo);				
				break;
			case EXCLUIR_PRODUTO:
				// <<<<10>>>>. Buscar o grupo do produto e o produto
				//				através da função PedeValidaGrupoCodigoProduto
				//				Verificar se a transação foi cancelada e voltar ao menu
				if(!PedeValidaGrupoCodigoProduto(&nGrupo, &nCodigo, "Entrada de produto"))
				{
					cout << "Cancelou!" << endl;
					PAUSA;
					break;
				}
				//			 Buscar os dados do produto invocando o método
				//			 objEstoque.VerificaSeExiste
				//			 Analisar o retorno desta função
				if (!objEstoque.VerificaSeExiste(nGrupo, nCodigo, &nPosicional, &stProduto))
				{
					cout << "Produto não encontrado!" << endl;
					PAUSA;
					break;
				}
				//			Se o produto já existe avisar ao operador exibindo os
				//				dados do produto e 
				//			aguardar sua visualização e voltar ao menu
				//			Se o produto não está cadastrado ou não existe 
				//				avisar ao operador e voltar ao menu
				cout << "Produto encontrado!" << endl;
				sprintf_s(cWork, "Descrição: %-50s Estoque: %-4.0f\nPreço unitário médio: R$ %-7.2f Valor total do estoque: R$%-10.2f\nAtivo: %c", 
						stProduto.cDescricaoProd, stProduto.dEstoque, stProduto.dPrecoUnitMedio, stProduto.dValorTotalEstoque, stProduto.cProdutoAtivo);  
				cout << cWork << endl;
				PAUSA;
				//			Caso esteja cadastrado, exibir os seus dados e
				//			aguardar a visualização e a confirmação da exclusão pelo
				//			operador.
				cout << "Deseja excluir realmente? (S/N): ";
				cin >> cOpcao;
					//			Se o operador não confirmar volte ao menu
				if(cOpcao != 's' && cOpcao != 'S')
				{
					cout << "Operação cancelada!" << endl;
					PAUSA;
					break;
				}
					//			e caso contrário torne o produto inativo e
				stProduto.cProdutoAtivo = 'I';
					//			regrave o mesmo com a o método para regravar o produto
				if (!objEstoque.RegravaProduto(nPosicional, &stProduto))
				{
					cout << "Erro ao inativar o produto!" << endl;
					PAUSA;
					break;
				}
					//			Analisar erro e voltar ao menu
					// ....
				if(!objEstoque.DesativaHashGrupoEProduto(&stProduto))
				{
					cout << "Produto não foi excluido corretamente dos hashs tables!" << endl;
					PAUSA;
					break;
				}
				cout << "Produto excluído!" << endl;
				PAUSA;
				break;
			case SAIR_DO_PROGRAMA:
				cout << "Deseja mesmo sair do programa? (S ou N):";
				cin	 >> cOpcao;					// pegar opção do operador
				cOpcao = toupper(cOpcao);		// converte para maiúscula
				if (cOpcao == 'S')				// sair realmente?
				{	// vai sair realmente - chamar o método que fecha o arquivo de produtos
					objEstoque.FecharArquivo();	// fechar o arquivo
					cout << "Encerrado pelo operador!!!" << endl;
					PAUSA;
					return;						// sai do programa
				}
				break;							// cai fora do switch
			default:							// opção errada!
				cout << "Opcao do menu errada!!!" << endl;
				system("pause");
		} //switch
	} // while
} // main
