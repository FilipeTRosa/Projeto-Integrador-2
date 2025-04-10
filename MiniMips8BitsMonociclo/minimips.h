typedef struct bancoRegistradores BRegs;
typedef struct registrador regs;
typedef struct controle CTRL;
typedef struct memoria_instrucao memInstruc;
typedef struct memoria_dados memDados;
typedef struct nodoInstrucao noInstruc;
typedef struct descPilhaInstrucao descPilha;

enum classe_inst{
    tipo_R, tipo_I, tipo_J, tipo_OUTROS
    };

struct instrucao{
enum classe_inst tipo_inst;
char inst_char[17];
char assembly[50];
int opcode;
int rs;
int rt;
int rd;
int funct;
int imm;
int addr;
    };

struct memoria_instrucao{
    struct instrucao *mem_inst;
    int tamanho;
    };

struct dado{
char dado_char[8];
int dado;
    };

struct memoria_dados{
struct dado *mem_dados;
int tamanho;
    };

struct bancoRegistradores
{
    regs *registradores;
    int tamanho;
};

struct registrador
{
    int id;
    int valor;
    regs *prox;
};

struct controle {
    int regDest;
    int srcB;
    int memReg;
    int ulaOP;
    int memWrite;
    int regWrite;
    int branch;
};

struct noPilha{
    int pc;
    BRegs bancoReg;
    //mem dados;
    //ultima instrucao;
};

struct nodoInstrucao {
    BRegs* bancoRegs;
    memInstruc* memoriaInstrucao;
    memDados* memoriaDados;
    int pc;
    noInstruc *prox;
};

struct descPilhaInstrucao {
    noInstruc* instrucoes;
    int tamanho;
};


// ================= CONFIGURAÇÕES DA FUNÇÃO BACK =================== //

descPilha* criaPilha();
noInstruc* criaNodo(BRegs* bancoRegs, memInstruc* memoriaInstrucao, memDados* memoriaDados, int programCounter);
void inserePilha(descPilha* pilha, noInstruc* instruc);


// ================= BANCO DE REGISTRADORES ========================= //

BRegs* alocaBancoRegistradores();
regs* criaRegistrador();
void criaBanco(BRegs* bancoRegs, regs* reg);
void imprimeReg(regs* reg);
void imprimeBanco(BRegs* bancoRegs);
int* buscaBancoRegs(BRegs* bancoRegs, int rs, int rt, int rd, int defDest);
void salvaDadoReg(BRegs* bancoRegistradores, int resultadoULA, int vetBuscaReg,  int sinalControle);

// ================== MEMORIA DE DADOS  ============================= //
void carregarDados(const char *nomeArquivo, struct memoria_dados *memDados);
void imprimeDado(struct dado dado);
void imprimeMemDados(struct memoria_dados *mem);
void insereMemDados(struct memoria_dados *mem, int endereco, int valor, int sinalControle);
int getDado(struct memoria_dados *mem, int endereco);
void salvarMemoriaEmArquivo(const char *nomeArquivo, struct memoria_dados *memDados);

// =================== CONTROLE ===================================== //
CTRL* criaControle();
void setSignal(CTRL* control, int opcode, int funct);
int fuctionMux(int op1, int op2, int controleULA);
const char* imprimeTipo(enum classe_inst tipo);
// ===================== ULA ======================================== //
void imprimeULA(int *resultadoULA);
int* processamentoULA(int op1, int op2, int ulaOP);
int verificaOverflow(int opResult);
int comparaRegs(int op1, int op2);
void converteDecimalParaBinario(char * palavra, int num);
void imprimeMemInstrucoes(struct memoria_instrucao *mem);
int conversorBinParaDecimal (int compDeDois, char * palavra);
struct instrucao buscaInstrucao(struct memoria_instrucao * memoria, int pc);
void carregarInstrucoes(const char *nomeArquivo, struct memoria_instrucao *mem);
void imprimeInstrucao(struct instrucao inst);
void salvarAsm(const char *nomeArquivo, struct memoria_instrucao *memInst);
// ===================== STEP ======================================= //

void imprimeControle(CTRL *controle);
void step(int *parada, int *pc, struct memoria_dados *memDados, struct memoria_instrucao *memInst, BRegs *bancoReg, CTRL *controle);

// ===================== DECODIFICACAO ============================== //
struct instrucao decodificaInstrucao(struct instrucao inst);
void getOpcode(const char * palavra, char *opcode);
void getRs(const char *palavra, char *rs);
void getRt(const char *palavra, char *rt);
void getRd(const char *palavra, char *rd);
void getFunct(const char *palavra, char *funct);
void getImm(const char *palavra, char *imm);
void getAddr(const char *palavra, char *addr);
void estenderSinalImm(char * imm, char * immExtendido);
char* getNomeFunct(int funct);
char* getNomeOpcode(int opcode);
// ================================================================== //