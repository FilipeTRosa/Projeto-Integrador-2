#include "minimips.h"
#include <string.h>
#include <math.h>
#include <stdio.h>


int conversorBinParaDecimal (int compDeDois, char * palavra){
    int decimal = 0;
    int len = strlen(palavra);
    int i, posicao = 0;

    //ASCII//
    // 0 = 48
    // 1 = 49
    // ... //

    if (compDeDois == 1)
    {
        /* complemento de 2 */
        //...

        char binario[len + 1];
        binario[len] = '\0';
        for (int j = 0; j < len ; j++) // for para inverter os bits
        {
            if ((palavra[j] - '0') == 0)
            {
                binario[j] = '1';

            }else
            {
                binario[j] = '0';
            }
            
        }
        //prints de teste
        //system("clear");
        //printf("Original= [%s] \n", palavra);
        //printf("Invertido sem somar= [%s] \n", binario);
        i = len -1;
        for (i; i>=0; i--)// for para somar 1
        {
            if ((binario[i] - '0') == 1)
            {
                binario[i] = '0';
            }else
            {
                binario[i] = '1';
                break;
            }
        }
        //print de teste
        //printf("Invertido e somado= [%s] \n", binario);
        if ((palavra[0] - '0') == 0)
        {
            /* numero positivo */
           //...
            return conversorBinParaDecimal(0, binario);
        }else
        {
            /* numero negativo */
            //...
            int valor = conversorBinParaDecimal(0, binario);
            return -valor;
        }
        
    }else
    {
        /* não é complemento de 2 */
        decimal = 0;
        posicao = 0;
        i = len - 1;

        for (i; i>=0; i--)
        {
            int num = palavra[i] - '0';
            decimal += num * pow(2 , posicao);
            posicao++;
        }
        //printf("Decimal: %d", decimal);
    }

    return decimal;
    
}


// retorna uma copia da instrução pois eu não quero que ela fique decodificada na memoria
struct instrucao buscaInstrucao(struct memoria_instrucao * memoria, int pc){

    struct instrucao inst;
    
    if (pc < 0 || pc >= memoria->tamanho) {
        printf("Erro: PC fora do intervalo.\n");
        return inst;  // Retorna uma instrução inválida (inicializada)
    }
    
    return memoria->mem_inst[pc];
}
