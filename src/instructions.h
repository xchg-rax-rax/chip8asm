/*
 *      This file includes all of the regular expressions used to translate 
 *      chip8 assembly instructions into their corresponding opcodes.
 */
#include <regex.h> 

// RE strings
char CLS[] = "^\\s*CLS\\s*$";
char RET[] = "^\\s*RET\\s*$";
char SYS_NNN[] = "^\\s*SYS\\s*[a-fA-F0-9]{1,3}\\s*$";
char JP_NNN[] = "^\\s*JP\\s*[a-fA-F0-9]{1,3}\\s*$";
char CALL_NNN[]= "^\\s*CALL\\s*[a-fA-F0-9]{1,3}\\s*$";
char SE_V_NN[]= "^\\s*SE \\s*V[a-fA-F0-9]\\s*\\,\\s*[a-fA-F0-9]{1,2}\\s*$";
char SNE_V_NN[]= "^\\s*SNE \\s*V[a-fA-F0-9]\\s*\\,\\s*[a-fA-F0-9]{1,2}\\s*$";
char SE_V_V[]= "^\\s*SE \\s*V[a-fA-F0-9]\\s*\\,\\s*V[a-fA-F0-9]\\s*$";
char LD_V_NN[]= "^\\s*LD \\s*V[a-fA-F0-9]\\s*\\,\\s*[a-fA-F0-9]{1,2}\\s*$";
char ADD_V_NN[]= "^\\s*ADD \\s*V[a-fA-F0-9]\\s*\\,\\s*[a-fA-F0-9]{1,3}\\s*$";
char LD_V_V[]= "^\\s*LD \\s*V[a-fA-F0-9]\\s*\\,\\s*V[a-fA-F0-9]\\s*$";
char OR_V_V[]= "^\\s*OR \\s*V[a-fA-F0-9]\\s*\\,\\s*V[a-fA-F0-9]\\s*$";
char AND_V_V[]= "^\\s*AND \\s*V[a-fA-F0-9]\\s*\\,\\s*V[a-fA-F0-9]\\s*$";
char XOR_V_V[]= "^\\s*XOR \\s*V[a-fA-F0-9]\\s*\\,\\s*V[a-fA-F0-9]\\s*$";
char ADD_V_V[]= "^\\s*ADD \\s*V[a-fA-F0-9]\\s*\\,\\s*V[a-fA-F0-9]\\s*$";
char SUB_V_V[]= "^\\s*SUB \\s*V[a-fA-F0-9]\\s*\\,\\s*V[a-fA-F0-9]\\s*$";
char SHR_V_V[]= "^\\s*SHR \\s*V[a-fA-F0-9]\\s*\\,\\s*V[a-fA-F0-9]\\s*$";
char SUBN_V_V[]= "^\\s*SUBN \\s*V[a-fA-F0-9]\\s*\\,\\s*V[a-fA-F0-9]\\s*$";
char SHL_V_V[]= "^\\s*SHL \\s*V[a-fA-F0-9]\\s*\\,\\s*V[a-fA-F0-9]\\s*$";
char SNE_V_V[]= "^\\s*SNE \\s*V[a-fA-F0-9]\\s*\\,\\s*V[a-fA-F0-9]\\s*$";
char LD_I_NNN[]= "^\\s*LD \\s*I\\s*\\,\\s*[a-fA-F0-9]{1,3}\\s*$";
char JP_V0_NNN[]= "^\\s*JP \\s*V0\\s*\\,\\s*[a-fA-F0-9]{1,3}\\s*$";
char RND_V_NN[]= "^\\s*RND \\s*V[a-fA-F0-9]\\s*\\,\\s*[a-fA-F0-9]{1,2}\\s*$";
char DRW_V_V_N[]= "^\\s*DRW \\s*V[a-fA-F0-9]\\s*\\,\\s*V[a-fA-F0-9]\\s*,\\s*[a-fA-F0-9]\\s*$";
char SKP_V[]= "^\\s*SKP \\s*V[a-fA-F0-9]\\s*$";
char SKNP_V[]= "^\\s*SKNP \\s*V[a-fA-F0-9]\\s*$";
char LD_V_DT[]= "^\\s*LD \\s*V[a-fA-F0-9]\\s*\\,\\s*DT\\s*$";
char LD_V_K[]= "^\\s*LD \\s*V[a-fA-F0-9]\\s*\\,\\s*K\\s*$";
char LD_DT_V[]= "^\\s*LD \\s*DT\\s*\\,\\s*V[a-fA-F0-9]\\s*$";
char LD_ST_V[]= "^\\s*LD \\s*ST\\s*\\,\\s*V[a-fA-F0-9]\\s*$";
char ADD_I_V[]= "^\\s*ADD \\s*I\\s*\\,\\s*V[a-fA-F0-9]\\s*$";
char LD_F_V[]= "^\\s*LD \\s*F\\s*\\,\\s*V[a-fA-F0-9]\\s*$";
char LD_B_V[]= "^\\s*LD \\s*B\\s*\\,\\s*V[a-fA-F0-9]\\s*$";
char LD_I_V[]= "^\\s*LD \\s*\\[I\\]\\s*\\,\\s*V[a-fA-F0-9]\\s*$";
char LD_V_I[]= "^\\s*LD \\s*V[a-fA-F0-9]\\s*\\,\\s*\\[I\\]\\s*$";
char LD_V_Q[]= "^\\s*LD \\s*V[a-fA-F0-9]\\s*\\,\\s*\\[Q\\]\\s*$";

// regular expressions
regex_t CLS_re;
regex_t RET_re;
regex_t SYS_NNN_re;
regex_t JP_NNN_re;
regex_t CALL_NNN_re;
regex_t SE_V_NN_re;
regex_t SNE_V_NN_re;
regex_t SE_V_V_re;
regex_t LD_V_NN_re;
regex_t ADD_V_NN_re;
regex_t LD_V_V_re;
regex_t OR_V_V_re;
regex_t AND_V_V_re;
regex_t XOR_V_V_re;
regex_t ADD_V_V_re;
regex_t SUB_V_V_re;
regex_t SHR_V_V_re;
regex_t SUBN_V_V_re;
regex_t SHL_V_V_re;
regex_t SNE_V_V_re;
regex_t LD_I_NNN_re;
regex_t JP_V0_NNN_re;
regex_t RND_V_NN_re;
regex_t DRW_V_V_N_re;
regex_t SKP_V_re;
regex_t SKNP_V_re;
regex_t LD_V_DT_re;
regex_t LD_V_K_re;
regex_t LD_DT_V_re;
regex_t LD_ST_V_re;
regex_t ADD_I_V_re;
regex_t LD_F_V_re;
regex_t LD_B_V_re;
regex_t LD_I_V_re;
regex_t LD_V_I_re;
regex_t LD_V_Q_re;

void compile_instruction_regs(){
    regcomp(&CLS_re, CLS, REG_ICASE);
    regcomp(&RET_re, RET, REG_ICASE);
    regcomp(&SYS_NNN_re , SYS_NNN, REG_ICASE);
    regcomp(&JP_NNN_re ,JP_NNN, REG_ICASE);
    regcomp(&CALL_NNN_re ,CALL_NNN, REG_ICASE);
    regcomp(&SE_V_NN_re ,SE_V_NN, REG_ICASE);
    regcomp(&SNE_V_NN_re ,SNE_V_NN, REG_ICASE);
    regcomp(&SE_V_V_re ,SE_V_V, REG_ICASE);
    regcomp(&LD_V_NN_re ,LD_V_NN, REG_ICASE);
    regcomp(&ADD_V_NN_re ,ADD_V_NN, REG_ICASE);
    regcomp(&LD_V_V_re ,LD_V_V, REG_ICASE);
    regcomp(&OR_V_V_re ,OR_V_V, REG_ICASE);
    regcomp(&AND_V_V_re ,AND_V_V, REG_ICASE);
    regcomp(&XOR_V_V_re ,XOR_V_V, REG_ICASE);
    regcomp(&ADD_V_V_re ,ADD_V_V, REG_ICASE);
    regcomp(&SUB_V_V_re, SUB_V_V, REG_ICASE);
    regcomp(&SHR_V_V_re ,SHR_V_V, REG_ICASE);
    regcomp(&SUBN_V_V_re ,SUBN_V_V, REG_ICASE);
    regcomp(&SHL_V_V_re ,SHL_V_V, REG_ICASE);
    regcomp(&SNE_V_V_re ,SNE_V_V, REG_ICASE);
    regcomp(&LD_I_NNN_re ,LD_I_NNN, REG_ICASE);
    regcomp(&JP_V0_NNN_re ,JP_V0_NNN, REG_ICASE);
    regcomp(&RND_V_NN_re ,RND_V_NN, REG_ICASE);
    regcomp(&DRW_V_V_N_re ,DRW_V_V_N, REG_ICASE);
    regcomp(&SKP_V_re ,SKP_V, REG_ICASE);
    regcomp(&SKNP_V_re ,SKNP_V, REG_ICASE);
    regcomp(&LD_V_DT_re ,LD_V_DT, REG_ICASE);
    regcomp(&LD_V_K_re ,LD_V_K, REG_ICASE);
    regcomp(&LD_DT_V_re ,LD_DT_V, REG_ICASE);
    regcomp(&LD_ST_V_re ,LD_ST_V, REG_ICASE);
    regcomp(&ADD_I_V_re ,ADD_I_V, REG_ICASE);
    regcomp(&LD_F_V_re ,LD_F_V, REG_ICASE);
    regcomp(&LD_B_V_re ,LD_B_V, REG_ICASE);
    regcomp(&LD_I_V_re ,LD_I_V, REG_ICASE);
    regcomp(&LD_V_I_re ,LD_V_I, REG_ICASE);
    regcomp(&LD_V_Q_re ,LD_V_Q, REG_ICASE);
}
