/*
 * Universidade Federal do ABC
 * MCTA028-15 - Programação Estruturada - Turma A1
 *
 * Projeto Googol – Parte 2
 *
 * INTEGRANTES:
 *
 * Dimitri Leandro de Oliveira Silva 
 * Lucas Fernandes Muniz 
 * Matheus Costa Damasceno 
 *
 *
 *
 * -------------------------------------------------
 * ESSA É A CAPIVARA DO ESTUDO　　　
 *         /)―ヘ
 *    __ ／　　　＼
 *  ／　          ●　　●丶
 * |　 　　              ▼  　|
 * |_ 　　    　   亠 ノ
 *   U￣U￣￣￣U￣
 * ELA ESTÁ PEDINDO DESCULPAS PELO ENVIO ATRASADO <3
 */


#include <stdio.h>
#include <string.h>

/* ------------ ASSINATURA DE FUNÇÕES ------------ */

/* Função que recebe um inteiro n e o armazena em num, retornando a quantidade de dígitos */
int criaNumeraodeInt(int n, int num[]);

/* Função que recebe uma string str que contém um número e armazena os dígitos dele em num, retornando a quantidade de dígitos */
int criaNumeraoDeString(char str[], int num[]);

/* Função que recebe um numerão com tamNum dígitos e o imprime: */
void imprimeNumerao(int num[], int tamNum);

/* [para testes] função que recebe dois vetores e seus tamanhos e faz a copia de um para outro. */
void copiar(int original[], int copiado[], int tamanho);

/*  função que soma os numA e numB a partir da entrada de seus vetores e tamanhos. A soma é salva no próprio numA e retorna o tamanho do vetor numA (numero de algarismos do resultado) */
int soma(int numA[], int tamA, int numB[], int tamB);

/* subtrai dois numerões sem considerar seu sinal e salva no numA; numA deve necessariamente ser o de maior magnitude; caso numB seja maior, deve-se passar os parâmetros invertidos */
int subtrai(int numA[], int tamA, int numB[], int tamB);

/* funcao que multiplica numA e numB e armazena o resultado em numC e retorna o tamanho de numC */
int multiplica(int numA[], int tamA, int numB[], int tamB, int numC[]);

/* SE O PRIMEIRO FOR MAIOR -> -1; SE FOREM IGUAIS -> 0; SE O SEGUNDO FOR MAIOR -> 1 */
int verificarMaiorMagnitude(int numA[], int tamA, int numB[], int tamB);

/* função que considera os diversos casos possíveis para soma */
int casoSoma(int numA[], int tamA, int numB[], int tamB);

/* Função que calcula todos os casos de subtração para números positivos e negativos, retornando o tamanho do número resultante da subtração. */
int casoSubtracao (int numA[], int tamA, int numB[], int tamB, int *vetor);

/* funcao que verifica o sinal da multiplicacao e casos simples de multiplicacao por 0 ou por 1 para economizar tempo. Retorna tamC */
int casoMultiplicacao(int numA[], int tamA, int numB[], int tamB, int numC[],  int *vetorIndicador);

/* Função que verifica o sinal da divisão e se divisão contém 0 ou 1.  */
int casoDivisao(int numA[], int tamA, int numB[], int tamB, int numC[], int *vetorIndicador);

/* função que ajusta o sinal do resto e prossegue para a função de resto */
int casoResto(int numA[], int tamA, int numB[], int tamB, int numC[], int resto[], int *vetorIndicador);

/* Função que inverte a ordem dos valores de um vetor.*/
void inverteVetor(int num[], int tam);

/* Função que calcula qual o multiplo que irá compor o quociente da divisão,
obtêm o resto da divisão e retorna o tamanho do resto. */
int quocienteBusca (int num[], int tam, int numB[], int tamB,  int *tamResto);

/* Função que calcula a divisão, salvando-a no vetor resultado e retornando o
tamanho do resultado. */
int divide(int numA[], int tamA, int numB[], int tamB, int resultado[], int *vetorIndicador);

/* Funçãão que calcula o resto da divisão, retornando o tamanho do resto. */
int restoDivInteira(int numA[], int tamA, int numB[], int tamB, int resultado[], int numAux[], int *vetorIndicador, int sinal);

/* ------------ FUNÇÃO MAIN ------------ */
int main(void) {

    int numA[1002], numB[1002], numC[2004], resto[1002]; /* NUMC VAI SERVIR PRA MULTIPLICAÇÃO */
    int tamA, tamB, tamResultado, vetorIndicador = 0;
    char strA[1002], strB[1002];
    char sinal;

    /* rotina de execução */
    scanf("%s", strA);
    while(strcmp(strA, "FIM") != 0) {
        scanf("%s %c", strB, &sinal);

        /* Variável indicadora que sinaliza em qual vetor o resultado da operação foi salvo. */
        /* 0 -> numA; 1 -> numB; 2 -> numC */
        vetorIndicador = 0;
        tamA = criaNumeraoDeString(strA, numA);
        tamB = criaNumeraoDeString(strB, numB);

        switch(sinal) {
        case '+':
            tamResultado = casoSoma(numA, tamA, numB, tamB);
            break;
        case '-':
            tamResultado = casoSubtracao(numA, tamA, numB, tamB, &vetorIndicador);
            break;
        case '*':
            tamResultado = casoMultiplicacao(numA, tamA, numB, tamB, numC, &vetorIndicador);
            break;
        case '/':
            tamResultado = casoDivisao(numA, tamA, numB, tamB, numC, &vetorIndicador);
            break;
        case '%':
            tamResultado = casoResto(numA, tamA, numB, tamB, numC, resto, &vetorIndicador);
        }

        /* VERIFICANDO ONDE ESTÁ O RESULTADO PARA PRINTAR: 0 -> numA; 1 -> numB; 2 -> numC */
        if(vetorIndicador == 0) {
            imprimeNumerao(numA, tamResultado);
        }
        else if(vetorIndicador == 1) {
            imprimeNumerao(numB, tamResultado);
        }
        else if(vetorIndicador == -1 || vetorIndicador == 2) {
            imprimeNumerao(numC, tamResultado);
        } else {
            imprimeNumerao(resto, tamResultado);
        }

        scanf("%s", strA);
    }

    return 0;
}

/* Função que recebe um inteiro n e o armazena em num, retornando a quantidade de dígitos */
int criaNumeraodeInt(int n, int num[]) {
    int digitos = 1;
    int i = 1;

    /* trata caso em que n é negativo. O primeiro elemento do vetor indica o sinal. Será 0, caso positivo, ou 1 caso negativo */
    if(n < 0) {
        num[0] = 1;
        n = -n;
    }
    else {
        num[0] = 0;
    }

    /* preenche vetor com números e obtem o número de dígitos */
    while(n > 9) {
        num[i] = n % 10;
        n /= 10;

        i++;
        digitos++;
    }
    num[i] = n;

    return digitos;
}


/* Função que recebe uma string str que contém um número e armazena os dígitos dele em num, retornando a quantidade de dígitos */
int criaNumeraoDeString(char str[], int num[]) {
    int quantDigitos = 0;
    int i;

    /* Determina a quantidade de dígitos de uma string */
    while(str[quantDigitos] != '\0' && str[quantDigitos] != '\n') {
        quantDigitos++;
    }

    /* Trata caso em que número da string é negativo, eliminando uma unidade de quantDigitos por causa do caracter '-'. O primeiro elemento do vetor indica o sinal. Será 0, caso positivo, ou 1 caso negativo */
    if(str[0] == '-') {
        num[0] = 1;
        quantDigitos--;
    } else {
        num[0] = 0;
    }

    /* Preenche o vetor num, transformando os caracteres numéricos em inteiros e colocando-os na ordem inversa */
    i = quantDigitos;
    while(i>0) {
        if (num[0] == 1) {
            num[quantDigitos-i+1] = str[i] - '0';
        } else {
            num[quantDigitos-i+1] = str[i-1] - '0';
        }
        i--;
    }

    return quantDigitos;
}


/* Função que recebe um numerão com tamNum dígitos e o imprime: */
void imprimeNumerao(int num[], int tamNum) {
    int i;
    /* ABRINDO UM FILE SÓ PARA TESTES */
    /*FILE *f = fopen("file.txt", "a"); */

    /*if(f == NULL){
        printf("Erro no arquivo...\n");
    } */

    /* imprime o sinal negativo, caso o número seja */
    if(num[0] == 1) {
        printf("-");
        /*fprintf(f, "-"); */
    }

    for(i=tamNum; i>0; i--) {
        printf("%d", num[i]);
        /*fprintf(f, "%d", num[i]); */
    }
    printf("\n");
    /*fprintf(f, "\n");

    fclose(f); */
}


void copiar(int original[], int copiado[], int tamanho) {
    int i;
    for(i=0; i<=tamanho; i++) {
        copiado[i] = original[i];
    }
}

/* função que soma os numA e numB a partir da entrada de seus vetores e tamanhos. A soma é salva no próprio numA retorna o tamanho do vetor numA (numero de algarismos do resultado) */
int soma(int numA[], int tamA, int numB[], int tamB) {
    int sobe=0, subiu=0, i;

    int tamAux=tamA, maior=1; /* maior=1, caso tamA seja maior; maior=0 caso tamB seja maior */

    /* caso tamB seja maior, utiliza ele como tamanho do resultado */
    if(tamB > tamA) {
        tamA = tamB;
        maior = 0;
    }

    /* preenche preenche as "casas vazias" com zeros para evitar lixo */
    if(maior) {
        for(i=tamB+1; i<=tamAux; i++) {
            numB[i] = 0;
        }
    }
    else {
        for(i=tamAux+1; i<=tamB; i++) {
            numA[i] = 0;
        }
    }

    /* faz soma, salvando resultado no vetor numA */
    for(i=1; i<=tamA; i++) {

        subiu = sobe;
        sobe = 0;

        if(numA[i]+numB[i] + subiu < 10) {
            numA[i] = numA[i] + numB[i] + subiu;
            sobe = 0;
        }
        else {
            sobe = 1;
            numA[i] = numA[i]+numB[i]+subiu - 10;
        }
    }

    /* após fazer as somas, caso o resultado tenha uma casa a mais */
    if(sobe) {
        numA[tamA+1] = 1;
        tamA++;
    }

    return tamA;
}

/* subtrai dois numerões sem considerar seu sinal e salva no numA; numA deve necessariamente ser o de maior magnitude; caso numB seja maior, deve-se passar os parâmetros invertidos */
int subtrai(int numA[], int tamA, int numB[], int tamB) {
    int tamC = 0, desce = 0, num, i;
    int maior = (tamA > tamB)? tamA : tamB;
    int menor = (tamA < tamB)? tamA : tamB;

    for(i=1; i<=maior || desce == 1; i++) {

        /*
         * Preeche com zero os valores do vetor que não foram preenchido.
         */
        if (i>maior) {
            numB[i] = 0;
        } else if (i>menor) {
            numB[i] = 0;
        }

        /* Condicional que verifica se adiciona ao número caso tenha
         * havido um "empréstimo" na operação anterior.
         */
        num = numB[i];
        if(desce) {
            num++;
            desce = 0;
        }

        if(num > numA[i]) {
            numA[i] += 10;

            /* Operação da subtração após o "empréstimo".*/
            numA[i] -= num;
            tamC++;
            /* Variável indicadora que marca se houve um "empréstimo".*/
            desce = 1;

        } else {
            /* Operação de subtração normal.*/
            numA[i] -= num;
            tamC++;
        }

    }

    /* Contagem do número de zeros da esquerda para a direita do número, * retirando esses zeros do número de dígitos do resultado da
     * subtração.
     */
    int numZeros = 0;
    for(i=1; i<=tamC; i++) {
        if(numA[i] == 0) {
            numZeros++;
        } else {
            numZeros = 0;
        }
    }
    /* Eliminação dos zeros no número. */
    tamC -= numZeros;
    if (tamC == 0) {
        tamC = 1;
    }
    return tamC;
}

int multiplica(int numA[], int tamA, int numB[], int tamB, int numC[]) {
    int i, j;
    int carry, resposta, tamC = (tamA + tamB);

    /* PREECNHO COM ZEROS APENAS O NECESSÁRIO */
    for(i = 1; i <= tamC; i++) {
        numC[i] = 0;
    }

    /* COMEÇANDO O ALGORITMO */
    for(i=1; i<=tamA; i++) {

        carry = 0;

        for(j=1; j<=tamB; j++) {
            resposta = numB[j] * numA[i] + carry;

            if(resposta > 9) {
                carry = resposta / 10;
                resposta = resposta % 10;
            } else {
                carry = 0;
            }

            /* AQUI EU JÁ TENHO O RESULTADO, É SÓ SOMAR EM numAux[i + j - 1] */
            numC[i + j - 1] += resposta;

            /* SE O RESULTADO DA SOMA PASSAR DE 9, EU JOGO O CARRY DESSA SOMA PRA PRÓXIMA POSIÇÃO DO VETOR*/
            if(numC[i + j - 1] > 9) {
                numC[i + j] += numC[i + j - 1] / 10;
                numC[i + j - 1] = numC[i + j - 1] % 10;
            }
        }

        /* QUANDO SAIR DO FOR DO J DEVO SOMAR O CARRY NA PRÓXIMA CASA */
        numC[i + j - 1] += carry;
    }

    /* PODE ACABAR TENDO UMA CASA NO COMEÇO DO NÚMERO COM 0, AI NÃO PRECISO EXIBI-LA */
    if(numC[tamC] == 0) {
        tamC--;
    }

    return tamC;
}

/* SE O PRIMEIRO FOR MAIOR -> -1; SE FOREM IGUAIS -> 0; SE O SEGUNDO FOR MAIOR -> 1 */
int verificarMaiorMagnitude(int numA[], int tamA, int numB[], int tamB) {
    int pos = tamA;

    if(tamA > tamB) {
        return -1;
    }
    else if(tamB > tamA) {
        return 1;
    }
    else {
        do {
            if(numB[pos] > numA[pos]) {
                return 1;
            }
            else if(numA[pos] > numB[pos]) {
                return -1;
            }
            pos -= 1;
        } while (pos>0);

        return 0;
    }
}

/* função que considera os diversos casos possíveis para soma */
int casoSoma(int numA[], int tamA, int numB[], int tamB) {
    int positivos=0, qualMaior=0, i;

    /* conta quantos positivos */
    if(numA[0] == 0) {
        positivos++;
    }
    if(numB[0] == 0) {
        positivos++;
    }

    /* caso ambos positivos, soma simples */
    if(positivos == 2 || positivos == 0) {
        tamA = soma(numA, tamA, numB, tamB);
        return tamA;
    } else { /* caso sinais diferentes */


        /* VERIFICANDO QUAL DELES É O MAIOR: SE FOR NUMA -> -1; SE FOREM IGUAIS -> 0; SE FOR NUMB -> 1 */
        qualMaior = verificarMaiorMagnitude(numA, tamA, numB, tamB);

        /* SE O PRIMEIRO É MAIOR */
        if(qualMaior == -1) {
            tamA = subtrai(numA, tamA, numB, tamB);
        }
        /* SE O SEGUNDO É O MAIOR */
        else if(qualMaior == 1) {
            tamA = subtrai(numB, tamB, numA, tamA);

            /* reescreve numB com valores de numA */
            for(i=1; i<=tamB; i++) {
                numA[i] = numB[i];
            }

            numA[0] = numB[0]; /* caso numB seja maior, numA recebe sinal de numB */
        }
        /* SE AS MAGNITUDES SÃO IGUAIS */
        else {
            tamA = 1;
            numA[0] = 0;
            numA[1] = 0;
            return tamA;
        }

        return tamA;
    }
}

/* Função que calcula todos os casos de subtração para números positivos e negativos, retornando o tamanho do número resultante da subtração. */
int casoSubtracao (int numA[], int tamA, int numB[], int tamB, int *vetor) {
    /* Casos em que o primeiro é positivo. */
    if(numA[0] == 0) {
        /* Se o segundo for positivo, o sinal da subtração dependerá da
         * da magnitude do segundo número. */
        if(numB[0] == 0) {
            /* SE NUMA É MAIOR */
            if(verificarMaiorMagnitude(numA, tamA, numB, tamB) == -1) {
                tamA = subtrai(numA, tamA, numB, tamB);
                numA[0]= 0;

            } else if(verificarMaiorMagnitude(numA, tamA, numB, tamB) == 1) {
                /* SE NUMB É MAIOR */
                if(verificarMaiorMagnitude(numA, tamA, numB, tamB) == 1) {
                    tamB = subtrai(numB, tamB, numA, tamA);
                    numB[0] = 1;
                    *vetor = 1;
                    return tamB;
                }
            } else {
                *vetor = 0;
                numA[0] = 0;
                numA[1] = 0;
                tamA = 1;
            }
            /* Se o segundo for negativo, será feita uma soma que resulta
             *  um número positivo. */
        } else {
            tamA = soma(numA, tamA, numB, tamB);
            numA[0] = 0;
        }

        /* Casos em que o primeiro é negativo. */
    } else {
        /* Se o segundo for positivo, será feita uma soma que resulta
         *  um número negativo. */
        if(numB[0] == 0) {
            tamA = soma(numA, tamA, numB, tamB);
            numA[0] = 1;
            /* Se o segundo for negativo, o sinal da subtração dependerá da
             * da magnitude do segundo número. */
        } else {
            /* SE NUMA FOR MAIOR QUE NUMB EM MAGNITUDE */
            if(verificarMaiorMagnitude(numA, tamA, numB, tamB) == -1) {
                tamA = subtrai(numA, tamA, numB, tamB);
                numA[0] = 1;
            } else if (verificarMaiorMagnitude(numA, tamA, numB, tamB) == 1) {
                /* SE NUMB FOR MAIOR QUE NUMA EM MAGNITUDE */
                if(verificarMaiorMagnitude(numA, tamA, numB, tamB) == 1) {
                    tamB = subtrai(numB, tamB, numA, tamA);
                    numB[0] = 0;
                    *vetor = 1;
                    return tamB;
                }
            }
            else {
                *vetor = 0;
                numA[0] = 0;
                numA[1] = 0;
                tamA = 1;
            }
        }
    }
    return tamA;
}

int casoMultiplicacao(int numA[], int tamA, int numB[], int tamB, int numC[], int *vetorIndicador) {
    int sinal;

    /* AQUI A PRIMEIRA COISA A FAZER É VERIFICAR O SINAL */
    /* se os sinais forem iguais então o resultado é + */
    if(numA[0] == numB[0]) {
        sinal = 0;
    }
    /* senão é - */
    else {
        sinal = 1;
    }

    /* VERIFICANDO SE HÁ MULTIPLICACAO POR 0 */
    if((tamA == 1 && numA[1] == 0) || (tamB == 1 && numB[1] == 0)) {
        /* se o numA for 0 */
        if(tamA == 1 && numA[1] == 0) {
            /* o resultado será o próprio numA */
            *vetorIndicador = 0;
            numA[0] = 0;
            return tamA;
        }
        /* se o numB for 0 */
        if(tamB == 1 && numB[1] == 0) {
            /* o resultado será o próprio numB */
            *vetorIndicador = 1;
            numB[0] = 0;
            return tamB;
        }
    }

    /* VERIFICANDO SE HÁ MULTIPLICACAO POR 1 */
    if((tamA == 1 && numA[1] == 1) || (tamB == 1 && numB[1] == 1)) {
        /* se o numA for 1 */
        if(tamA == 1 && numA[1] == 1) {
            /* o resultado será numB */
            *vetorIndicador = 1;
            numB[0] = sinal;
            return tamB;
        }
        /* se o numB for 1 */
        if(tamB == 1 && numB[1] == 1) {
            /* o resultado será numA */
            *vetorIndicador = 0;
            numA[0] = sinal;
            return tamA;
        }
    }

    /* SE PASSOU POR TODOS OS IFS E NÃO RETORNOU NADA, ENTÃO SEGUE PRA MULTIPLICACAO NORMAL E ARMAZENA O RESULTADO EM NUMC */
    *vetorIndicador = 2;
    numC[0] = sinal;
    return multiplica(numA, tamA, numB, tamB, numC);
}

/* Função que verifica o sinal da divisão e se divisão contém 0 ou 1.  */
int casoDivisao(int numA[], int tamA, int numB[], int tamB, int numC[], int *vetorIndicador) {
    int sinal;

    /* AQUI A PRIMEIRA COISA A FAZER É VERIFICAR O SINAL */
    /* se os sinais forem iguais então o resultado é + */
    if(numA[0] == numB[0]) {
        sinal = 0;
    }
    /* senão é - */
    else {
        sinal = 1;
    }

    /* VERIFICANDO SE HÁ 0/algumacoisa */
    if(tamA == 1 && numA[1] == 0) {
        /* o resultado será o próprio numA (ou seja, 0) */
        *vetorIndicador = 0;
        numA[0] = 0;
        return tamA;
    }

    /* VERIFICANDO ALGUMACOISA DIVIDIDO POR 1 */
    if(tamA == 1 && numA[1] == 1) {
        /* o resultado será o próprio numA */
        *vetorIndicador = 0;
        numA[0] = sinal;
        return tamA;
    }

    /* VERIFICANDO ALGUMACOISA DIVIDIDO POR -1 */
    if(tamA == 1 && numA[1] == -1) {
        /* o resultado será o próprio numA com sinal invertido */
        *vetorIndicador = 0;
        numA[0] = sinal;
        return tamA;
    }

    /* DEPOIS, DEVO VERIFICAR SE O DIVISOR É MAIOR QUE O DIVIDENDO. SE FOR, RETORNO 0 */
    if(verificarMaiorMagnitude(numA, tamA, numB, tamB) == 1) {
        *vetorIndicador = 0;
        numA[0] = 0;
        numA[1] = 0;
        tamA = 1;
        return tamA;
    }

    /* SE PASSOU POR TODOS OS IFS E NÃO RETORNOU NADA, ENTÃO SEGUE PRA DIVISAO NORMAL */
    numC[0] = sinal;
    return divide(numA, tamA, numB, tamB, numC, vetorIndicador);
}
/* função que ajusta o sinal do resto e prossegue para a função de resto */
int casoResto(int numA[], int tamA, int numB[], int tamB, int numC[], int resto[], int *vetorIndicador) {
    int sinal;

    /* AQUI A PRIMEIRA COISA A FAZER É VERIFICAR O SINAL */

    /* positivo com positivo */
    if(numA[0] == 0 && numB[0] == 0) {
        sinal = 0;
    }

    /* negativo com negativo */
    if(numA[0] == 1 && numB[0] == 1) {
        sinal = 1;
    }

    /* positivo com negativo */
    if(numA[0] == 0 && numB[0] == 1) {
        sinal = 0;
    }

    /* negativo com positivo */
    if(numA[0] == 1 && numB[0] == 0) {
        sinal = 1;
    }

    /* DEPOIS, DEVO VERIFICAR SE O DIVISOR É MENOR QUE O DIVIDENDO. SE NÃO FOR, RETORNO O PŔOPRIO DIVIDENDO */
    if(verificarMaiorMagnitude(numA, tamA, numB, tamB) == 1) {
        *vetorIndicador = 0;
        numA[0] = sinal;
        return tamA;
    }

    /* PROSSEGUINDO */
    return restoDivInteira(numA, tamA, numB, tamB, numC, resto, vetorIndicador, sinal);
}

/* Inverte o vetor para adapta-lo a nossa notação de numerão. */
void inverteVetor(int num[], int tam) {
    int metade = tam/2;
    int i, p1 = 0, p2 = tam, aux;
    for(i=1; i<=metade; i++) {
        aux = num[i];
        num[i] = num[tam-(i-1)];
        num[tam-(i-1)] = aux;
    }
}

int quocienteBusca (int num[], int tam, int numB[], int tamB, int *tamResto) {
    int comparacao, multp = -1, i;
    int mult[2], res[1002], numCopia[tam];
    int tamM = 1, tamResultado;
    res[0] = 0;
    mult[0] = 0;
    numCopia[0] = 0;

    /* Testa qual o multiplo deve ser usado para a composição do resultado. */
    for(i=1; i<=9; i++) {
        mult[1] = i;
        tamResultado = multiplica(mult, tamM, numB, tamB, res);
        comparacao = verificarMaiorMagnitude(res, tamResultado, num, tam);
        if(comparacao == 0) {
            multp = i;
            break;
        }
        /* Se o multiplo for maior que o número que será dividido,
        * retorna ao multiplo anterior. */
        else if(comparacao == -1) {
            multp = i-1;
            mult[1] = multp;
            tamResultado = multiplica(mult, tamM, numB, tamB, res);
            break;
        }
    }

    /* Definindo  o multiplo como 9 caso esse seja o maior multiplo 
     * possível, mesmo sendo o resultado de sua multiplicação seja 
     * MENOR  do que o número que será dividido. */
    if(multp == -1) {
        multp = 9;
    }

    /* Calculando o resto da subtração. */
    *tamResto = subtrai(num, tam, res, tamResultado);
    return multp;
}

int divide(int numA[], int tamA, int numB[], int tamB, int resultado[], int *vetorIndicador) {
    int maior = (tamA > tamB)? tamA : tamB;
    int numAux[maior];
    *vetorIndicador = -1;
    int maiorMagnitude;

    int tamAux = 0, tamResultado = 0, tamResto = -1, indice, i, num = 0,
        tamEscolhido = 0, quociente, pos, numZero = 0;
    numAux[0] = 0;


    /* Caso o divisor seja maior do que o dividendo */
    if(verificarMaiorMagnitude(numA, tamA, numB, tamB) == 1) {
        resultado[1] = 0;
        tamResultado = 1;
        return 1;

    } else {

        /* Enquanto for possível dividir o número A. */
        while(tamA > 0  && tamA - tamResto > 0) {
            tamEscolhido = 0;
            tamResultado++;
            numZero = 0;

            if(tamResto > 0){
                tamAux = tamResto-1;
            } else {
                tamAux = tamB-1;
            }

            /* Identificar a parte que será dividida. */
            maiorMagnitude = verificarMaiorMagnitude(numAux, tamAux, numB, tamB);
            while(maiorMagnitude == 1 && tamAux <= tamA) {
                tamAux++;
                indice = 1;
                tamEscolhido = 0;

                /* Verifica caso haja um zero no dividendo. */
                if(numA[tamA] == 0) {
                    resultado[tamResultado] = 0;
                    tamEscolhido++;
                    numZero = 1;
                    tamAux = 0;
                    break;
                }
                /* Adiciona zero ao quociente caso seja necessário "descer"
                 *mais de um número do dividendo */
                else if((tamAux - tamResto) >= 2 && tamResto != -1 && tamAux <= tamA) {
                    resultado[tamResultado] = 0;
                    tamResultado++;
                }
                /* Verifica caso não seja mais possível "descer" um número do
                 * dividendo. */
                else if (tamAux-tamA == 1 && maiorMagnitude) {
                    tamAux--;
                    resultado[tamResultado] = 0;
                    tamEscolhido = tamA;
                    break;
                }


                for(i=tamA; i>(tamA-tamAux); i--) {
                    numAux[indice] = numA[i];
                    indice++;
                    tamEscolhido++;
                }

                inverteVetor(numAux, tamAux);
                maiorMagnitude = verificarMaiorMagnitude(numAux, tamAux, numB, tamB);
            }

            //imprimeNumerao(numA, tamA);

            /* Caso chegue no final da divisão e haja resto*/
            if(tamA-tamAux == 0 && maiorMagnitude == 1) {
                tamResto = tamAux;
            } else if (!numZero) {
                /* Calcula o quociente e guarda o resto da divisão em numAux. */
                quociente = quocienteBusca(numAux, tamAux, numB, tamB, &tamResto);
                resultado[tamResultado] =  quociente;
            }

            int aux;
            /* Atualização do dividendo após uma subtração.*/
            for(i=tamA-tamEscolhido, aux = 1; aux<=tamResto; aux++) {
                numA[i+aux] = numAux[aux];
            }

            /* Caso o resto da divisão seja zero ou no final da divisão
             * tenha sobrado um resto. */
            if((numAux[1] == 0 && tamResto == 1) || (tamA-tamAux == 0 && maiorMagnitude)) {
                tamResto = 0;
            }

            tamA -= (tamEscolhido - tamResto);
        }
    }

    inverteVetor(resultado, tamResultado);

    return tamResultado;

}

int restoDivInteira(int numA[], int tamA, int numB[], int tamB, int resultado[], int numAux[], int *vetorIndicador, int sinal) {
    int maior = (tamA > tamB)? tamA : tamB;
    *vetorIndicador = -2;
    int maiorMagnitude;

    int tamAux = 0, tamResultado = 0, tamResto = -1, indice, i, num = 0,
        tamEscolhido = 0, quociente, pos, numZero = 0;
    numAux[0] = 0;


        /* Caso o divisor seja maior do que o dividendo */
    if(verificarMaiorMagnitude(numA, tamA, numB, tamB) == 1) {
        resultado[1] = 0;
        tamResultado = 1;
        return 1;

    } else {

        /* Enquanto for possível dividir o número A. */
        while(tamA > 0  && tamA - tamResto > 0) {
            tamEscolhido = 0;
            tamResultado++;
            numZero = 0;

            if(tamResto > 0){
                tamAux = tamResto-1;
            } else {
                tamAux = tamB-1;
            }

            /* Identificar a parte que será dividida. */
            maiorMagnitude = verificarMaiorMagnitude(numAux, tamAux, numB, tamB);
            while(maiorMagnitude == 1 && tamAux <= tamA) {
                tamAux++;
                indice = 1;
                tamEscolhido = 0;

                /* Verifica caso haja um zero no dividendo. */
                if(numA[tamA] == 0) {
                    resultado[tamResultado] = 0;
                    tamEscolhido++;
                    numZero = 1;
                    tamAux = 0;
                    break;
                }
                /* Adiciona zero ao quociente caso seja necessário "descer"
                 *mais de um número do dividendo */
                else if((tamAux - tamResto) >= 2 && tamResto != -1 && tamAux <= tamA) {
                    resultado[tamResultado] = 0;
                    tamResultado++;
                }
                /* Verifica caso não seja mais possível "descer" um número do
                 * dividendo. */
                else if (tamAux-tamA == 1 && maiorMagnitude) {
                    tamAux--;
                    resultado[tamResultado] = 0;
                    tamEscolhido = tamA;
                    break;
                }


                for(i=tamA; i>(tamA-tamAux); i--) {
                    numAux[indice] = numA[i];
                    indice++;
                    tamEscolhido++;
                }

                inverteVetor(numAux, tamAux);
                maiorMagnitude = verificarMaiorMagnitude(numAux, tamAux, numB, tamB);
            }

            //imprimeNumerao(numA, tamA);

            /* Caso chegue no final da divisão e haja resto*/
            if(tamA-tamAux == 0 && maiorMagnitude == 1) {
                tamResto = tamAux;
            } else if (!numZero) {
                /* Calcula o quociente e guarda o resto da divisão em numAux. */
                quociente = quocienteBusca(numAux, tamAux, numB, tamB, &tamResto);
                resultado[tamResultado] =  quociente;
            }

            int aux;
            /* Atualização do dividendo após uma subtração.*/
            for(i=tamA-tamEscolhido, aux = 1; aux<=tamResto; aux++) {
                numA[i+aux] = numAux[aux];
            }

            /* Caso o resto da divisão seja zero ou no final da divisão
             * tenha sobrado um resto. */
            if((numAux[1] == 0 && tamResto == 1) || (tamA-tamAux == 0 && maiorMagnitude)) {
                tamResto = 0;
            }

            tamA -= (tamEscolhido - tamResto);
        }
    }

    /* possivelmente aparecerão alguns zeros no começo do número. Aqui estamos removendo-os */
    for(i = tamEscolhido; i > 0; i--) {
        if(numAux[i] == 0) {
            tamEscolhido--;
        } else {
            break;
        }
    }

    /* se o resto foi zero, tenho que arrumar o tamanho do vetor */
    if(tamEscolhido == 0) {
        tamEscolhido++;
        sinal = 0;
        numAux[0] = 0;
    }

    /* colocando o sinal do resto na posição 0 */
    numAux[0] = sinal;
    return tamEscolhido;
}
