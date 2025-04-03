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
        if ((palavra[0] - '0') == 0)
        {
            /* numero positivo */
            return conversorBinParaDecimal(0, palavra);
        }else
        {
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
                /* numero negativo */
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
    }

    return decimal;
    
}

// retorna uma copia da instrução
struct instrucao buscaInstrucao(struct memoria_instrucao * memoria, int pc){
    struct instrucao inst;    
    if (pc < 0 || pc >= memoria->tamanho) {
        printf("Erro: PC fora do intervalo.\n");
        return inst;  // Retorna uma instrução inválida (inicializada)
    }
    
    return memoria->mem_inst[pc];
}

void carregarDados(const char *nomeArquivo, struct memoria_dados *memDados){
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", nomeArquivo);
        return;
    }

    char linha[32];
    int posicao = 0;

    // Inicializa a memória com um valor padrão (0 para indicar "vazio")
    for (int i = 0; i < memDados->tamanho; i++) {
        memDados->mem_dados[i].dado = 0;
        strcpy(memDados->mem_dados[i].dado_char, "vazio");
    }

    while (posicao < memDados->tamanho && fgets(linha, sizeof(linha), arquivo) != NULL) {
        // Remove quebras de linha e espaços extras
        linha[strcspn(linha, "\r\n")] = '\0';

        if (strlen(linha) > 0) {  // Se a linha não estiver vazia
            memDados->mem_dados[posicao].dado = atoi(linha);
            snprintf(memDados->mem_dados[posicao].dado_char, sizeof(memDados->mem_dados[posicao].dado_char), "%d", memDados->mem_dados[posicao].dado);
        }
        posicao++;
    }

    fclose(arquivo);
}


void carregarInstrucoes(const char *nomeArquivo, struct memoria_instrucao *mem){
    struct instrucao instrucaoDecodificada;
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
                instrucaoDecodificada = decodificaInstrucao(mem->mem_inst[posicao]);
                mem->mem_inst[posicao].opcode = instrucaoDecodificada.opcode;
                mem->mem_inst[posicao].rs = instrucaoDecodificada.rs;
                mem->mem_inst[posicao].rt = instrucaoDecodificada.rt;
                mem->mem_inst[posicao].rd = instrucaoDecodificada.rd;
                mem->mem_inst[posicao].funct = instrucaoDecodificada.funct;
                mem->mem_inst[posicao].imm = instrucaoDecodificada.imm;
                mem->mem_inst[posicao].addr = instrucaoDecodificada.addr;
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
        bancoRegs->registradores->id = bancoRegs->tamanho;
        bancoRegs->tamanho++;
        bancoRegs->registradores->valor = 1;
    }
    else {
        regs *aux = bancoRegs->registradores;

        while(aux->prox != NULL) {
        aux = aux->prox;
        }
        aux->prox = reg;
        aux->prox->id = bancoRegs->tamanho;
        bancoRegs->tamanho++;
    }
}

void imprimeBanco(BRegs* bancoRegs) {
    regs *aux = bancoRegs->registradores;

    while(aux->prox != NULL) {
        imprimeReg(aux);
        aux = aux->prox;
    }
}

 

void imprimeInstrucao(struct instrucao inst){ 
    printf("Binario: [%s], opcode: [%d], rs: [%d], rt: [%d], rd: [%d], funct: [%d], imm: [%d], addr: [%d]\n",
        inst.inst_char, inst.opcode, inst.rs,
        inst.rt, inst.rd, inst.funct,
        inst.imm, inst.addr);
}

void imprimeMemInstrucoes(struct memoria_instrucao *mem){
    printf("==== Memoria de instruçoes ====\n");
    for (int i = 0; i < mem->tamanho; i++)
    {
        printf("Posicao: [%d], ", i);
        imprimeInstrucao(mem->mem_inst[i]);
    }
    printf("===============================\n");
}

void imprimeDado(struct dado dado){
    printf("Valor: [%d]\n", dado.dado);
}

void imprimeMemDados(struct memoria_dados *mem){
    printf("==== Memoria de dados ====\n");
    for (int i = 0; i < mem->tamanho; i++)
    {
        printf("Posicao: [%d], ", i);
        imprimeDado(mem->mem_dados[i]);
    }
    printf("==========================\n");
}

int* buscaBancoRegs(BRegs* bancoRegs, int rs, int rt, int rd, int defDest) {
    
    regs* aux = bancoRegs->registradores;
    int* vetBusca = (int *)malloc(3 * sizeof(int));

    if(defDest == 0) {
        rd = rt;
    }

    while(aux->id != rs) {
        aux = aux->prox;
    }

    vetBusca[0] = aux->valor;

    while(aux->id != rt) {
        aux = aux->prox;
    }

    vetBusca[1] = aux->valor;

    while(aux->id != rd) {
        aux = aux->prox;
    }

    vetBusca[2] = aux->id;

    return vetBusca;
}

int* processamentoULA(int* dadosBancoRegs, int funct) {

    int* vetResultadoULA = (int *)malloc(3 * sizeof(int));

    vetResultadoULA[2] = comparaRegs(dadosBancoRegs);

    switch(funct) {
        case 0:
            vetResultadoULA[0] = dadosBancoRegs[0] + dadosBancoRegs[1]; 
            break;
        case 2:
            vetResultadoULA[0] = dadosBancoRegs[0] - dadosBancoRegs[1];
            break;
        case 4:
            vetResultadoULA[0] = dadosBancoRegs[0] && dadosBancoRegs[1];
            break;
        case 5:
            vetResultadoULA[0] = dadosBancoRegs[0] || dadosBancoRegs[1]; 
            break;
        
    }

    return vetResultadoULA;
}

int comparaRegs(int* dadosBancoRegs) {
    
    int flag = 0;

    if(dadosBancoRegs[0] == dadosBancoRegs[1]) {
        flag = 1;
    }

    return flag;
}

void salvaDadoReg(BRegs* bancoRegistradores, int* resultadoULA, int* vetBuscaReg) {
    
    regs *aux = bancoRegistradores->registradores;

    while(aux->id != vetBuscaReg[2]) {
        aux = aux->prox;
    }

    aux->valor = resultadoULA[0];
}


void getOpcode(const char *palavra, char *opcode){
    strncpy(opcode, palavra + 0, 4);
    opcode[4] = '\0';
}

void getRs(const char *palavra, char *rs){
    strncpy(rs, palavra + 4, 3);
    rs[3] = '\0';
}

void getRt(const char *palavra, char *rt){
    strncpy(rt, palavra + 7, 3);
    rt[3] = '\0';
}

void getRd(const char *palavra, char *rd){
    strncpy(rd, palavra + 10, 3);
    rd[3] = '\0';
}

void getFunct(const char *palavra, char *funct){
    strncpy(funct, palavra + 13, 3);
    funct[3] = '\0';
}

void getImm(const char *palavra, char *imm){
    strncpy(imm, palavra + 10, 6);
    imm[6] = '\0';
}

void getAddr(const char *palavra, char *addr){
    strncpy(addr, palavra + 9, 7);
    addr[7] = '\0';
}

void estenderSinalImm(char * imm, char * immExtendido){
    immExtendido[0] = imm[0];
    immExtendido[1] = imm[1];

    strcpy(immExtendido + 2, imm);

    immExtendido[strlen(imm) + 2 ]= '\0';
}

struct instrucao decodificaInstrucao(struct instrucao inst){
    
    //struct instrucao instruc;
    char palavra[17];
    strcpy(palavra, inst.inst_char);

    //Variaveis da instrucao
    char opcode[4];
    char rs[4];
    char rt[4];
    char funct[4];
    char rd[4];
    char imm[6];
    char addr[7];
    char immExtendido[8];

    //Opcode
    getOpcode(inst.inst_char, opcode);
    inst.opcode = conversorBinParaDecimal(0,opcode);
    //Fim do opcode
    
    if (inst.opcode == 0)
    {
        // TIPO R
        
        //RS
        getRs(inst.inst_char,rs);
        inst.rs = conversorBinParaDecimal(0,rs); //coloca o rs na instrucao
        //Fim RS
        
        //RT
        getRt(inst.inst_char, rt);
        inst.rt = conversorBinParaDecimal(0,rt);
        //fim RT

        //RD
        getRd(inst.inst_char, rd);
        inst.rd = conversorBinParaDecimal(0,rd);
        //fim RD

        //Funct
        getFunct(inst.inst_char, funct);
        inst.funct = conversorBinParaDecimal(0,funct);
        //fim Funct
    
        //imprimeInstrucao(inst);
    }else if(inst.opcode == 4 || inst.opcode == 11 || inst.opcode == 15 || inst.opcode == 8)
    {
        // TIPO I
        
        //RS
        getRs(inst.inst_char,rs);
        inst.rs = conversorBinParaDecimal(0,rs); //coloca o rs na instrucao
        //Fim RS
        
        //RT
        getRt(inst.inst_char, rt);
        inst.rt = conversorBinParaDecimal(0,rt);
        //fim RT

        //imm
        getImm(inst.inst_char, imm);
        //printf("\n Imm antes %s \n", imm);
        estenderSinalImm(imm, immExtendido);
        //printf("\n Imm depois %s \n", immExtendido);
        inst.imm = conversorBinParaDecimal(1,immExtendido); //complemento de 2
        //Fim imm
    
        //imprimeInstrucao(inst);
    }else if (inst.opcode == 2)
    {
        // TIPO J
        //Addr
        getAddr(inst.inst_char, addr);
        inst.addr = conversorBinParaDecimal(0,addr); 
        //Fim Addr

    }
    
    return inst;
}