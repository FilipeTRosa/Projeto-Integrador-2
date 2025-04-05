typedef struct bancoRegistradores BRegs;
typedef struct registrador regs;
typedef struct controle CTRL;

enum classe_inst{
    tipo_R, tipo_I, tipo_J, tipo_OUTROS
    };

struct instrucao{
enum classe_inst tipo_inst;
char inst_char[17];
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


// ================= BANCO DE REGISTRADORES ========================= //

BRegs* alocaBancoRegistradores();
regs* criaRegistrador();
void criaBanco(BRegs* bancoRegs, regs* reg);
void imprimeReg(regs* reg);
void imprimeBanco(BRegs* bancoRegs);
int* buscaBancoRegs(BRegs* bancoRegs, int rs, int rt, int rd, int defDest);
void salvaDadoReg(BRegs* bancoRegistradores, int resultadoULA, int vetBuscaReg);

// ================================================================== //
void carregarDados(const char *nomeArquivo, struct memoria_dados *memDados);
void imprimeDado(struct dado dado);
void imprimeMemDados(struct memoria_dados *mem);
CTRL* criaControle();
void setSignal(CTRL* control, int opcode, int funct);
int fuctionMux(int op1, int op2, int controleULA);
// ===================== ULA ======================================== //

int* processamentoULA(int op1, int op2, int funct);
int verificaOverflow(int opResult);
int comparaRegs(int op1, int op2);
void converteDecimalParaBinario(char * palavra, int num);
void imprimeMemInstrucoes(struct memoria_instrucao *mem);
int conversorBinParaDecimal (int compDeDois, char * palavra);
struct instrucao buscaInstrucao(struct memoria_instrucao * memoria, int pc);
void carregarInstrucoes(const char *nomeArquivo, struct memoria_instrucao *mem);
void imprimeInstrucao(struct instrucao inst);
struct instrucao decodificaInstrucao(struct instrucao inst);
void getOpcode(const char * palavra, char *opcode);
void getRs(const char *palavra, char *rs);
void getRt(const char *palavra, char *rt);
void getRd(const char *palavra, char *rd);
void getFunct(const char *palavra, char *funct);
void getImm(const char *palavra, char *imm);
void getAddr(const char *palavra, char *addr);
void estenderSinalImm(char * imm, char * immExtendido);