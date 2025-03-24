#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "minimips.h"

int main(int argc, char const *argv[])
{
    //Alocando memoria de instrução
    struct memoria_instrucao mem;
    mem.mem_inst = (struct instrucao *)malloc(256 *sizeof(struct instrucao));
    mem.tamanho = 256;
    //Fim alocação de memoria de instrucao

    //Configuracao de variaveis do sistema
    int menu = 0;
    //Fim config do sistema




    do {
        printf("\n===== MENU =====\n");
        printf("1 - Carregar memória de instruções (.mem)\n");
        printf("2 - Carregar memória de Dados (.dat)\n");
        printf("3 - Imprimir memórias (instruções e dados)\n");
        printf("4 - Imprimir banco de registradores\n");
        printf("5 - Imprimir todo o simulador (registradores e memórias)\n");
        printf("6 - Converter binario .asm\n"); //// TESTE de funcao
        printf("7 - Salvar .dat\n");
        printf("8 - Executa Programa (run)\n");
        printf("9 - Executa uma instrução (Step)\n");
        printf("10 - Volta uma instrução (Back)\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &menu);

        switch (menu) {
            case 1:
                FILE *arquivoEntrada;
                arquivoEntrada = fopen("programaTestaInstrucoes.mem", "r"); 
                char caractere;
                char palavra[17];
                int n=0, posicao=0;
                while ((caractere = fgetc(arquivoEntrada)) !=EOF) //enquanto n acha o fim do arquivo... anda
                {
                    if (caractere != '\n') //enquanto nao acha o fim da frase guarda palavra
                    {
                        palavra[n] = caractere;
                        n++;
                    }else
                    {//achou o \n
                        if (n>0)
                        {
                            palavra[n] = '\n';
                            strcpy(mem.mem_inst[posicao].inst_char, strtok(palavra,"\n"));
                            posicao++;
                        }
                        n=0;
                        palavra[n] = '\n';
                    }                   
                }
                
                break;
            case 2:
                break;
            case 3:
                //imprime memorias
                for (int i = 0; i < 256; i++) { // tamanho 10 só para teste
                
                        printf("Instrucao %d:Binario: %s, opcode: %d, rs: %d, rt: %d, rd: %d, funct: %d, imm: %d, addr: %d\n",
                            i, mem.mem_inst[i].inst_char, mem.mem_inst[i].opcode, mem.mem_inst[i].rs,
                            mem.mem_inst[i].rt, mem.mem_inst[i].rd, mem.mem_inst[i].funct,
                            mem.mem_inst[i].imm, mem.mem_inst[i].addr);
                    
                }
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                int dec;
                int comp2 = 1;
                dec = conversorBinParaDecimal(comp2,mem.mem_inst[6].inst_char);
                printf("Valor em decimal: [%d]", dec);
                break;
            case 7:
                break;
            case 8:
                break;
            case 9:
                break;
            case 10:
                break;
            case 0: printf("Saindo...\n"); 
                break;
            default: printf("Opção inválida! Tente novamente.\n");
        }
    } while (menu != 0);
    


    free(mem.mem_inst);
    return 0;
}
