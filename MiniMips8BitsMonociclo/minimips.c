#include "minimips.h"
#include <string.h>
#include <stdlib.h>
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
        
        char binario[len + 1]; //no windows reclama dessa linha
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


void carregarInstrucoes(const char *nomeArquivo, struct memoria_instrucao *mem){

    FILE *arquivoEntrada = fopen(nomeArquivo, "r");  
    if (!arquivoEntrada) {
        printf("Erro ao abrir o arquivo %s.\n", nomeArquivo);
        return;
    }

    char caractere;
    char palavra[17];  // Tamanho instrução + \0
    int n = 0, posicao = 0;

    while ((caractere = fgetc(arquivoEntrada)) != EOF) {
        if (caractere != '\n') {
            palavra[n] = caractere;
            n++;
        } else {
            if (n > 0) {
                palavra[n] = '\0';  // Coloca \0 no final da string
                strcpy(mem->mem_inst[posicao].inst_char, palavra);
                posicao++;
            }
            n = 0;  // Reseta para a próxima linha
        }
    }

    fclose(arquivoEntrada);
    




}

BRegs* alocaBancoRegistradores() {

  BRegs* newBanco = (BRegs *)malloc(sizeof(BRegs));
  newBanco->registradores = NULL;
  newBanco->tamanho = 0;

  return newBanco;
}

regs* criaRegistrador() {

  regs *newReg = (regs *)malloc(sizeof(regs));
  newReg->id = 0;
  newReg->valor = 0;
  newReg->prox = NULL;

  return newReg;
}

void criaBanco(BRegs* bancoRegs, regs* reg){
  if(bancoRegs->registradores == NULL) {
    bancoRegs->registradores = reg;
    bancoRegs->tamanho++;
    bancoRegs->registradores->id = bancoRegs->tamanho;
  }
  else {
    regs *aux = bancoRegs->registradores;

    while(aux->prox != NULL) {
      aux = aux->prox;
    }
    aux->prox = reg;
    bancoRegs->tamanho++;
    aux->prox->id = bancoRegs->tamanho;
  }
}

void imprimeBanco(BRegs* bancoRegs) {
  regs *aux = bancoRegs->registradores;

  while(aux->prox != NULL) {
    imprimeReg(aux);
    aux = aux->prox;
  }
}

void imprimeReg(regs* reg) {
  printf("\n====================\n");
  printf("ID: %d\n", reg->id);
  printf("Valor: %d\n", reg->valor);
  printf("====================\n");
}