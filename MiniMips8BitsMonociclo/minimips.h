typedef struct bancoRegistradores BRegs;
typedef struct registrador regs;


enum classe_inst{
    tipo_I, tipo_J, tipo_R, tipo_OUTROS
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
struct instrucao *mem_dados;
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

BRegs* alocaBancoRegistradores();
regs* criaRegistrador();
void criaBanco(BRegs* bancoRegs, regs* reg);
void imprimeReg(regs* reg);
void imprimeBanco(BRegs* bancoRegs);

int conversorBinParaDecimal (int compDeDois, char * palavra);
struct instrucao buscaInstrucao(struct memoria_instrucao * memoria, int pc);
void carregarInstrucoes(const char *nomeArquivo, struct memoria_instrucao *mem);


