// Programa de teste do algoritmo Busca Bin�ria
// FATEC - MC - JBC - 23/03/2017 - Vers�o 0.0
#include "Binary.h"
// Entry point do programa
//
void main(void)
{
	PRODUTO stProduto,								// struct para conter os dados de um produto
		vetProdutos[QTDE_REGISTROS];				// vetor de produtos 
	FILE *fdCadastro;								// file descriptor do arquivo
	char cWork[200],								// para o sprintf_s
		cOpcao;										// op��o do operador
	int i, j;										// indexadores e contadores
	bool flgRepetido,								// para eliminar c�digos repetidos
		flgHouveTroca;								// para classifica��o Buble Sort

	PAIS_BRASIL;
	// gerar um arquivo de teste
	srand(SEMENTE_RANDOM);							// semente rand�mica
	// loop de gera��o de arquivo
	for(i = 0; i < QTDE_REGISTROS; i++)
	{
		vetProdutos[i].nCodigo = rand();			// random de 0 a 32k
		if(vetProdutos[i].nCodigo == 0)
			vetProdutos[i].nCodigo = 1;				// modifica o zero para um
		//	verificar se c�digo repetido
		for(j = 0, flgRepetido = false;				// n�o encontrou repetido ainda
			j < i;									// varrer o vetor at� imediatamente antes do �ndice [i]
			j++)
		{
			if(vetProdutos[j].nCodigo == vetProdutos[i].nCodigo)	// repetido?
			{
				i--;								// desconsiderar esse random
				flgRepetido = true;					// � um c�digo repetido
				break;								// cai fora do for j
			}
		}	// for j
		if(flgRepetido)								// c�digo repetido?
			continue;								// continua no for i
		// criar um produto com um c�digo que n�o est� repetido
		sprintf_s(vetProdutos[i].cDescricao, sizeof(stProduto.cDescricao), 
			"Produto de c�digo: %8d", vetProdutos[i].nCodigo);
		vetProdutos[i].cAtivo = 'A';
		vetProdutos[i].dPrecoUnit = rand() * 0.4587;
	}	// for i
	// classificar o vetor de produtos antes de gravar
	do
	{
		// loop de compara��o de c�digos dois a dois
		for(i = 0, flgHouveTroca = false; i < QTDE_REGISTROS - 1; i++)
		{
			if(vetProdutos[i].nCodigo > vetProdutos[i + 1].nCodigo)	// fora de ordem?
			{	// fazer a troca de posi��o
				memcpy_s(&stProduto, sizeof(PRODUTO), 
					&vetProdutos[i], sizeof(PRODUTO));	// salva o elemento[i]
				memcpy_s(&vetProdutos[i], sizeof(PRODUTO), 
					&vetProdutos[i + 1], sizeof(PRODUTO));	// troca o elemento[i + 1]
				memcpy_s(&vetProdutos[i + 1], sizeof(PRODUTO), 
					&stProduto, sizeof(PRODUTO));		// troca o elemento[i]
				flgHouveTroca = true;					// houve troca
			}
		}
	}while(flgHouveTroca);
	// gravar o arquivo sequencial
	if(fopen_s(&fdCadastro, CAMINHO_CADASTRO, "w+b") != 0)	// erro de abertura?
	{
		cout << "Erro de abertura do arquivo do cadastro!" << endl;
		PAUSA;
		return;											// volta ao S.O.
	}
	// loop de grava��o dos registros do produto 
	for(i = 0; i < QTDE_REGISTROS; i++)
	{
		if(fwrite(&vetProdutos[i], sizeof(PRODUTO), 1, fdCadastro) == 0)	// erro de grava��o?
		{
			fclose(fdCadastro);							// fechar o arquivo
			cout << "Erro de grava��o!" << endl;
			PAUSA;
			return;										// volta ao sistema operacional
		} 
	}	// for i
	// instanciar a classe BinarySearch e criar um objeto
	clBinarySearch objBinary(QTDE_REGISTROS);
	// loop de teste
	while(true)
	{
		LIMPAR_TELA;
		cout << "\n\tPrograma de teste do binary search" << endl;
		// montar o menu
		cout << MOSTRAR_PRODUTO << " - Mostrar um produto" << endl
			<< EXCLUIR_PRODUTO << " - Excluir produto" << endl
			<< LISTAR_PRODUTOS << " - Listar produtos" << endl
			<< SAIR_DO_PROGRAMA	<< " - Sair do programa" << endl
			<< "\tSeleciona: ";
		cin >> cOpcao;
		cOpcao = toupper(cOpcao);						// op��o para mai�scula
		switch(cOpcao)									// avalia a op��o
		{
			case MOSTRAR_PRODUTO:
				break;									// volta ao menu
			case EXCLUIR_PRODUTO:
				break;									// volta ao menu
			case LISTAR_PRODUTOS:
				break;									// volta ao menu
			case SAIR_DO_PROGRAMA:
				cout << "\n\tSair realmente? (S ou N): ";
				cin >> cOpcao;
				if(cOpcao == 's' || cOpcao == 'S')
				{
					fclose(fdCadastro);					// fecha o arquivo
					return;								// volta ao sistema operaional
				}
				break;									// volta ao menu
			default:
				cout << "\n\tOp��o inv�lida!" << endl;
				PAUSA;
		}	// switch
	}	// while
} // main