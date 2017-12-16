// Exercicio para aula de estrutura
// FATEC-MC - JCB - 19/04/2017 - Versão 0.0
#include "Header.h"
// 
// entry point do programa
//
void main(void)
{
	bool flgStatus;									// para receber os status da construção da classe
	ALUNO stAluno;									// struct para conter os dados de um aluno

	setlocale(LC_ALL, "portuguese_brazil");
	// instanciar a classe e criar o objeto aluno
	clAluno objAluno(&flgStatus);				
	if(!flgStatus)									// erro?
	{ 
		cout << "Erro na construção!" << endl;
		PAUSA;
		return;										// volta ao sistema operacional
	}
	// loop infinito do programa
	while(true)
	{
		// estruturar o programa com um menu:
		/* Incluir aluno
		Excluir Aluno
		Mostrar Aluno
		Sair do programa
		*/
	} // while
} // main
