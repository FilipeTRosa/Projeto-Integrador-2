
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


int conversorBinParaDecimal (int compDeDois, char * palavra);
struct instrucao buscaInstrucao(struct memoria_instrucao * memoria, int pc);
