using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace AlgiGeneticoPrim_Meu
{
    class Program
    {
        /// <summary>
        /// struct para conter o cromossomo de um individuo
        /// </summary>
        public struct stINDIVIDUO
        {
            public char[] cIndividuo;                                       // cromossomo do individuo
            public Int64 nAvaliacao;                                        // avaliação do individuo 
        }
        /// <summary>
        /// Vetor de individuos da população de soluções do problema
        /// </summary>
        public static stINDIVIDUO[] populacao;                              // população de soluções
        /// <summary>
        /// Struct de trabalho de um indivíduo da população
        /// </summary>
        public static stINDIVIDUO stTrabalho;                               // struct de trabalho para classificação
        /// <summary>
        /// Vetor de pesos dos bits do cromossomo para conversão binário decimal
        /// </summary>
        public static Int64[] pesos;
        /// <summary>
        /// Parametrização do programa para resovler 3x + 2z - 2y = valor
        /// </summary>
        public const int QTDE_INDIVIDUOS_POPULACAO = 100,                   // Tamanho da população de soluções
            SEMENTE_RANDOM = 200,                                           // Semente randômica
            QTDE_BITS_CADA_VARIAVEL = 32,                                   // bits de cada variável
            QTDE_VARIAVEIS = 3,                                             // X, Y, Z
            QTDE_BITS_CADA_INDIVIDUO =
                QTDE_BITS_CADA_VARIAVEL * QTDE_VARIAVEIS,                   // tamanho do croossomo binário do individuo
            INDICE_X = 0,                                                   // indice para conversão decimal
            INDICE_Y = INDICE_X + QTDE_BITS_CADA_VARIAVEL,                  // indice do Y
            INDICE_Z = INDICE_Y + QTDE_BITS_CADA_VARIAVEL,                  // indice do Z
            PERCENTUAL_ELITISMO = 20,                                       // 20% de indivíduos na elite
            PERCENTUAL_MUTACAO = 3,                                         // 3% de mutação dos bits do cromossomo
            QTDE_MUTACAO =
                (QTDE_BITS_CADA_INDIVIDUO * PERCENTUAL_MUTACAO) / 100,      // quantidade de bits a serem mutados
            INDICE_PRIMEIRO_FILHO = PERCENTUAL_ELITISMO,                    // indice do primeiro filho do cruzamento
            QTDE_CRUZAMENTOS =
                (QTDE_INDIVIDUOS_POPULACAO - PERCENTUAL_ELITISMO) / 2,
            QTDE_INDIVIDUOS_RODEIO = 5,                                     // quantidade de indivífuos no rodeio
            QTDE_MAXIMA_GERACOES = 3000;                                    // qtde máxima de gerações
        /// <summary>
        /// Entry point do programa
        /// </summary>
        /// <param name="args">parâmetros da linha de comando</param>
        static void Main(string[] args)
        {
            bool flgHouveTroca = false,                                     // true indica que houve troca
                flgRodeioIgual = false;                                     // true indica que seleção repetida (duplicidade)
            int i, j, k, m, n, p;                                           // indices e contadores genéricos
            Int64 x, y, z,                                                  // variáveis do programa
                nValorEquacao = 0,                                          // valor da equação
                nMelhorAvalicao = 0,                                        // indivíduo com a melhor avaliação no rodeio
                nResultado = 0;                                             // valor a ser obtido na solução da equação
            int nIndice = QTDE_BITS_CADA_VARIAVEL - 2,                      // indice inicial para conversão binário / decimal
                nPontoDeCorte = 0,                                          // ponto de corte para cruzamento
                nBitMutacao = 0,                                            // indice do bit a ser mutado
                nPrimeiroPai = 0,                                           // indice do primeiro pai selecionado
                nSegundoPai = 0;                                            // idem para o cruzamento
            // vetor par seleção dos individuos com método rodeio
            int[] nPartRodeio = new int[QTDE_INDIVIDUOS_RODEIO];
            // dimensionar a população
            populacao = new stINDIVIDUO[QTDE_INDIVIDUOS_POPULACAO];
            // dimensionar e calcular os pesos de 2 ^^ 30 até 2 ^^ 0
            pesos = new Int64[QTDE_BITS_CADA_VARIAVEL - 1];
            for (i = 0; i < QTDE_BITS_CADA_VARIAVEL - 1; i++, nIndice--)
                pesos[i] = Convert.ToInt64(Math.Pow(2, nIndice));
            // pedir o valor da equação
            do
            {
                try
                {
                    Console.Write("Resultado da equação: 3x + 2z - 2y = ");
                    nResultado = Convert.ToInt64(Console.ReadLine());
                    break;                                                  // cai fora do do...while
                }
                catch (Exception)
                {
                    Console.WriteLine("Digite algarismos válidos!");
                    //throw;
                }
            } while (true);
            // 
            // inicializar os cromossomos dos indivíduos da população
            Random rndSorteio = new Random(SEMENTE_RANDOM);
            for (i = 0; i < QTDE_INDIVIDUOS_POPULACAO; i++)
            {
                // dimensionar o cromossomo de cada indivíduo
                populacao[i].cIndividuo = new char[QTDE_BITS_CADA_INDIVIDUO];
                // loop para sorteio de '0' e '1'
                for (j = 0; j < QTDE_BITS_CADA_INDIVIDUO; j++)
                {
                    if (rndSorteio.Next() % 2 == 0)                         // "bit zero"?
                        populacao[i].cIndividuo[j] = '0';                   // "bit zero"
                    else
                        populacao[i].cIndividuo[j] = '1';                   // "bit um"
                } // for j
                populacao[i].nAvaliacao = 0;                                // zero de avaliação para o indivíduo
            } // for i
            // loop para todas as geraões possíveis
            for (j = 0; j < QTDE_MAXIMA_GERACOES; j++)
            {
                // loop de avaliação de cada indivíduo da população
                for (i = 0; i < QTDE_INDIVIDUOS_POPULACAO; i++)
                {
                    // calcular x, y, z e aplicar na equação
                    x = CalcularVariavel(populacao[i].cIndividuo, INDICE_X);
                    y = CalcularVariavel(populacao[i].cIndividuo, INDICE_Y);
                    z = CalcularVariavel(populacao[i].cIndividuo, INDICE_Z);
                    // aplicar na equação
                    try
                    {
                        nValorEquacao = (3 * x) + (2 * z) - (2 * y);
                        populacao[i].nAvaliacao =
                            Math.Abs(nResultado - nValorEquacao);           // aptidão
                    }
                    catch (Exception)
                    {
                        populacao[i].nAvaliacao = Int64.MaxValue;           // pior possível
                        //throw;
                    }
                    // verificar se a equação foi resolvida
                    if (populacao[i].nAvaliacao == 0)                        // chegou ao resultado
                    {
                        Console.WriteLine(
                            "Equação resolvida: x = {0} y = {1} z = {2}\nGeração: {3}", 
                            x, y, z, (j + 1));
                        Console.WriteLine("Digite qualquer tecla para encerrar...");
                        Console.ReadKey();
                        return;
                    }

                } // for i - loop de avaliação
                // solução não foi encontrada]
                // 1. Classificar a população para isolar a elite (elitismo)
                // 2. Selecionar dois pais para a elite para o cruzamento
                //      Operador da seleção será o rodeio
                // 3. Fazer o cruzamento entre dois pais gerando 2 novos indivíduos 
                //      da população
                // 4. Fazer a mutação em cada novo indivíduo
                // 
                // Classificar com o Bubble Sort
                do
                {
                    flgHouveTroca = false;                              // não houve troca ainda
                    for (i = 0; i < QTDE_INDIVIDUOS_POPULACAO - 1; i++)
                    {   // loop de comparação de avaliação de dois a dois indivíduos
                        if (populacao[i].nAvaliacao > populacao[i + 1].nAvaliacao)   // fora de ordem?
                        {   // fazer a troca de posições entre elem[i] e elem[i + 1]
                            stTrabalho = populacao[i];                  // salva o elem[i]
                            populacao[i] = populacao[i + 1];            // troca o elem[i + 1]
                            populacao[i + 1] = stTrabalho;              // troca o elem[i]
                            flgHouveTroca = true;
                        }
                    } // for i
                } while (flgHouveTroca);                                // loop enquanto houver troca
                // temos a elite
                // loop de cruzamentos e mutação
                for (i = 0, k = INDICE_PRIMEIRO_FILHO; i < QTDE_CRUZAMENTOS; i++)
                {
                    // seleção do primeiro pai
                    nMelhorAvalicao = Int64.MaxValue;       // começa com a pior
                    //loop d seleção do primeiro pai
                    for (m = 0; m < QTDE_INDIVIDUOS_RODEIO; m++)
                    {
                        nPartRodeio[m] = rndSorteio.Next(PERCENTUAL_ELITISMO);     // sortear de 0 a 19
                        // loop para verificar se já foi sorteado
                        for (n = 0, flgRodeioIgual = false; n < m; n++)
                        {
                            if (nPartRodeio[n] == nPartRodeio[m])       // mesmo indivíduo?
                            {
                                n--;                                    // repete o sorteio
                                flgRodeioIgual = true;                  // indica que é repetido
                                break;                                  // cai fora do for n
                            }
                        }   // for n
                        if (!flgRodeioIgual)                             // não é repetido?
                        {   // este "indice do indivíduo não foi sorteado antes"
                            if (populacao[nPartRodeio[m]].nAvaliacao < nMelhorAvalicao)  // melhor?
                            {   // melhor avaliação até agora
                                nMelhorAvalicao = 
                                    populacao[nPartRodeio[m]].nAvaliacao; // salva a melhor até agora
                                nPrimeiroPai = nPartRodeio[m];          // possível primeiro pai  
                            }
                        }
                    } // for m - primeiro pai
                    // temos o primeiro pai
                    // O mesmo para encontrar o segundo pai que não pode ser igual ao primeiro
                    do
                    {
                        // seleção do segundo pai
                        nMelhorAvalicao = Int64.MaxValue;       // começa com a pior
                        //loop d seleção do primeiro pai
                        for (m = 0; m < QTDE_INDIVIDUOS_RODEIO; m++)
                        {
                            nPartRodeio[m] = rndSorteio.Next(PERCENTUAL_ELITISMO);     // sortear de 0 a 19
                            // loop para verificar se já foi sorteado
                            for (n = 0, flgRodeioIgual = false; n < m; n++)
                            {
                                if (nPartRodeio[n] == nPartRodeio[m])       // mesmo indivíduo?
                                {
                                    n--;                                    // repete o sorteio
                                    flgRodeioIgual = true;                  // indica que é repetido
                                    break;                                  // cai fora do for n
                                }
                            }   // for n
                            if (!flgRodeioIgual)                             // não é repetido?
                            {   // este "indice do indivíduo não foi sorteado antes"
                                if (populacao[nPartRodeio[m]].nAvaliacao < nMelhorAvalicao)  // melhor?
                                {   // melhor avaliação até agora 
                                    nMelhorAvalicao =
                                        populacao[nPartRodeio[m]].nAvaliacao; // salva a melhor até agora
                                    nSegundoPai = nPartRodeio[m];          // possível segundo pai  
                                }
                            }
                        } // for m - segundo pai
                    } while (nPrimeiroPai == nSegundoPai);              // repete o loop se mesmo pai
                    // termos agora o primeiro e o segundo pai para o cruzamento
                    nPontoDeCorte = rndSorteio.Next(1, QTDE_BITS_CADA_INDIVIDUO);   
                    // vamos cruzar o primeiro filho
                    for (m = n = 0; m < nPontoDeCorte; m++)
                    {   // copiar a primeira parte do primeiro pai
                        stTrabalho.cIndividuo[n++] =
                            populacao[nPrimeiroPai].cIndividuo[m];
                    }   // for m
                    for (; m < QTDE_BITS_CADA_INDIVIDUO; m++)           // copiar até o fim
                    {   // copiar a segunda parte do segundo pai
                        stTrabalho.cIndividuo[n++] = 
                            populacao[nSegundoPai].cIndividuo[m]; 
                    }   // for m
                    // temos o primeiro filho = fazer a mutação
                    for (m = 0; m < QTDE_MUTACAO; m++)
                    {
                        nBitMutacao = rndSorteio.Next(QTDE_BITS_CADA_INDIVIDUO);    // sorteia o bit
                        if (stTrabalho.cIndividuo[nBitMutacao] == '0')   // "bit zero"?
                            stTrabalho.cIndividuo[nBitMutacao] = '1';   // muta para bit um
                        else
                            stTrabalho.cIndividuo[nBitMutacao] = '0';   // muta para zero
                    } // for m
                    // temos o primeiro filho
                    populacao[k++] = stTrabalho;                        // novo indivíduo da população
                    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
                    // vamos cruzar o segundo filho
                    for (m = n = 0; m < nPontoDeCorte; m++)
                    {   // copiar a primeira parte do primeiro pai
                        stTrabalho.cIndividuo[n++] =
                            populacao[nSegundoPai].cIndividuo[m];
                    }   // for m
                    for (; m < QTDE_BITS_CADA_INDIVIDUO; m++)           // copiar até o fim
                    {   // copiar a segunda parte do segundo pai
                        stTrabalho.cIndividuo[n++] =
                            populacao[nPrimeiroPai].cIndividuo[m];
                    }   // for m
                    // temos o primeiro filho = fazer a mutação
                    for (m = 0; m < QTDE_MUTACAO; m++)
                    {
                        nBitMutacao = rndSorteio.Next(QTDE_BITS_CADA_INDIVIDUO);    // sorteia o bit
                        if (stTrabalho.cIndividuo[nBitMutacao] == '0')   // "bit zero"?
                            stTrabalho.cIndividuo[nBitMutacao] = '1';   // muta para bit um
                        else
                            stTrabalho.cIndividuo[nBitMutacao] = '0';   // muta para zero
                    } // for m
                    // temos o segundo filho
                    populacao[k++] = stTrabalho;                        // novo indivíduo da população


                } // for i - loop de cruzamentos

            } // for j - loop de todas as gerações
            // todas as gerações foram executadas e a solulção não foi encontrada
            // calcular o x, y, z do indivíduo com o índice zero (melhor aptidão)
            x = CalcularVariavel(populacao[0].cIndividuo, INDICE_X);
            y = CalcularVariavel(populacao[0].cIndividuo, INDICE_Y);
            z = CalcularVariavel(populacao[0].cIndividuo, INDICE_Z);
            nValorEquacao = (3 * x) + (2 * z) - (2 * y);
            Console.WriteLine("Equação não resolvida: x={0} y={1} z={2}", x, y, z);
            Console.WriteLine("Valor da equação = {0}", nValorEquacao);
            Console.WriteLine("Diferença={0}", (nResultado = nValorEquacao));
            Console.WriteLine("Digite qualquer tecla para encerrar...!");
            Console.ReadKey();
        } // main
        /// <summary>
        /// Método que vai calcular o valor inteiro com sínal da 
        /// variável desejada
        /// </summary>
        /// <param name="cIndividuo"> cromossomo do indivíduo da população</param>
        /// <param name="nIndice">índice inicial de cada variável</param>
        /// <returns>Valor inteiro da variável</returns>
        public static Int64 CalcularVariavel(char[] cIndividuo, int nIndice)
        {
            Int64 nValorInteiro = 0;                        // para calcular o valor inteiro
            int i = nIndice,                                // indice inicial da variável
                j;                                          // indice do peso
            char cSinal = cIndividuo[i++];                  // sinal da variável que indexa para 2 ^^ 30
            // loop para conversão
            for (j = 0; j < QTDE_BITS_CADA_VARIAVEL - 1; j++, i++)   // j indice do peso e i da variável 
            {
                if (cIndividuo[i] == '1')                   // "bit um" ?
                    nValorInteiro += pesos[j];              // soma o peso para conversão
            } // for j
            if (cSinal == '1')                              // negariva?
                return nValorInteiro * -1;                  // devolve negarivo
            return nValorInteiro;                           // devolve positivo
        }
    } // class
}
