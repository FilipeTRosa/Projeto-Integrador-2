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
    //Variaveis do conversor de bin
    int dec;
    int comp2 = 1;
    //Fim conversor
    
    //Configuracao de variaveis do sistema
    int menu = 0;
    int pc = 0;

    // CRIANDO BANCO DE REGISTRADORES //

    regs *reg = NULL;
    BRegs *bancoRegistradores = NULL;

    bancoRegistradores = alocaBancoRegistradores();

    for (int i = 0; i <  8; i++) {
        reg = criaRegistrador();
        criaBanco(bancoRegistradores, reg);
    }

    //imprimeBanco(bancoRegistradores); // Testando se o banco de registradores foi criado de maneira correta

    //Fim config do sistema

    do {
        printf("\n===== MENU =====\n");
        printf("1 - Carregar memoria de instrucoes (.mem)\n");
        printf("2 - Carregar memoria de Dados (.dat)\n");
        printf("3 - Imprimir memorias (instrucoes e dados)\n");
        printf("4 - Imprimir banco de registradores\n");
        printf("5 - Imprimir todo o simulador (registradores e memorias)\n");
        printf("6 - Converter binario .asm\n"); //// TESTE de funcao
        printf("7 - Salvar .dat\n");
        printf("8 - Executa Programa (run)\n");
        printf("9 - Executa uma instrucao (Step)\n");
        printf("10 - Volta uma instrucao (Back)\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &menu);

        switch (menu) {
            case 1:        
                carregarInstrucoes("programaTestaInstrucoes.mem", &mem);
                break;
            case 2:
                break;
            case 3:
                //imprime memorias
                system("clear");

                for (int i = 0; i < 30; i++) { // tamanho 10 só para teste
                    //teste de impressão
                    imprimeInstrucao(mem.mem_inst[i]);
                }
                break;
            case 4:
                system("clear");
                imprimeBanco(bancoRegistradores); // Testando se o banco de registradores foi criado de maneira correta
                break;
            case 5:
                break;
            case 6:
                system("clear");
                comp2 = 1;
                dec = conversorBinParaDecimal(comp2,mem.mem_inst[2].inst_char);
                printf("Valor em decimal com comp de 2: [%d]\n", dec);
                comp2 = 0;
                dec = conversorBinParaDecimal(comp2,mem.mem_inst[2].inst_char);
                printf("Valor em decimal sem comp de 2: [%d]\n", dec);
                break;
            case 7:
                break;
            case 8:
                break;
            case 9:
                decodificaInstrucao(buscaInstrucao(&mem, 5));
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
