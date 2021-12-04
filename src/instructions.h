/*
 *      This file includes all of the regular expressions used to translate 
 *      chip8 assembly instructions into their corresponding opcodes.
 */
#pragma once
#include <regex.h> 

// RE strings
char CLS[] = "^ *CLS *$";
char RET[] = "^ *RET *$";
char SYS_NNN[] = "^ *SYS *[a-fA-F0-9]\\{1,3\\} *$";
char JP_NNN[] = "^ *JP *[a-fA-F0-9]\\{1,3\\} *$";
char CALL_NNN[]= "^ *CALL *[a-fA-F0-9]\\{1,3\\} *$";
char SE_V_NN[]= "^ *SE *V[a-fA-F0-9] *\\, *[a-fA-F0-9]\\{1,2\\} *$";
char SNE_V_NN[]= "^ *SNE *V[a-fA-F0-9] *\\, *[a-fA-F0-9]\\{1,2\\} *$";
char SE_V_V[]= "^ *SE *V[a-fA-F0-9] *\\, *V[a-fA-F0-9] *$";
char LD_V_NN[]= "^ *LD *V[a-fA-F0-9] *\\, *[a-fA-F0-9]\\{1,2\\} *$";
char ADD_V_NN[]= "^ *ADD *V[a-fA-F0-9] *\\, *[a-fA-F0-9]\\{1,2\\} *$";
char LD_V_V[]= "^ *LD *V[a-fA-F0-9] *\\, *V[a-fA-F0-9] *$";
char OR_V_V[]= "^ *OR *V[a-fA-F0-9] *\\, *V[a-fA-F0-9] *$";
char AND_V_V[]= "^ *AND *V[a-fA-F0-9] *\\, *V[a-fA-F0-9] *$";
char XOR_V_V[]= "^ *XOR *V[a-fA-F0-9] *\\, *V[a-fA-F0-9] *$";
char ADD_V_V[]= "^ *ADD *V[a-fA-F0-9] *\\, *V[a-fA-F0-9] *$";
char SUB_V_V[]= "^ *SUB *V[a-fA-F0-9] *\\, *V[a-fA-F0-9] *$";
char SHR_V_V[]= "^ *SHR *V[a-fA-F0-9] *\\, *V[a-fA-F0-9] *$";
char SUBN_V_V[]= "^ *SUBN *V[a-fA-F0-9] *\\, *V[a-fA-F0-9] *$";
char SHL_V_V[]= "^ *SHL *V[a-fA-F0-9] *\\, *V[a-fA-F0-9] *$";
char SNE_V_V[]= "^ *SNE *V[a-fA-F0-9] *\\, *V[a-fA-F0-9] *$";
char LD_I_NNN[]= "^ *LD *I *\\, *[a-fA-F0-9]\\{1,3\\} *$";
char JP_V0_NNN[]= "^ *JP *V0 *\\, *[a-fA-F0-9]\\{1,3\\} *$";
char RND_V_NN[]= "^ *RND *V[a-fA-F0-9] *\\, *[a-fA-F0-9]\\{1,2\\} *$";
char DRW_V_V_N[]= "^ *DRW *V[a-fA-F0-9] *\\, *V[a-fA-F0-9] *, *[a-fA-F0-9] *$";
char SKP_V[]= "^ *SKP *V[a-fA-F0-9] *$";
char SKNP_V[]= "^ *SKNP *V[a-fA-F0-9] *$";
char LD_V_DT[]= "^ *LD *V[a-fA-F0-9] *\\, *DT *$";
char LD_V_K[]= "^ *LD *V[a-fA-F0-9] *\\, *K *$";
char LD_DT_V[]= "^ *LD *DT *\\, *V[a-fA-F0-9] *$";
char LD_ST_V[]= "^ *LD *ST *\\, *V[a-fA-F0-9] *$";
char ADD_I_V[]= "^ *ADD *I *\\, *V[a-fA-F0-9] *$";
char LD_F_V[]= "^ *LD *F *\\, *V[a-fA-F0-9] *$";
char LD_B_V[]= "^ *LD *B *\\, *V[a-fA-F0-9] *$";
char LD_I_V[]= "^ *LD *\\[I\\] *\\, *V[a-fA-F0-9] *$";
char LD_V_I[]= "^ *LD *V[a-fA-F0-9] *\\, *\\[I\\] *$";

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

void compile_instruction_regs(){
    int error_code = 0;
    char error_msg[128];

    if((error_code =regcomp(&CLS_re, CLS, REG_ICASE))) {
        regerror(error_code, &CLS_re, error_msg, 128);
        printf("A CLS failed to compile: %s\n", error_msg);
        exit(1);
    }
    if((error_code = regcomp(&RET_re, RET, REG_ICASE))) {
        regerror(error_code, &CLS_re, error_msg, 128);
        printf("A RET failed to compile: %s\n", error_msg);
        exit(1);
    }
    if((error_code = regcomp(&SYS_NNN_re, SYS_NNN, REG_ICASE))) {
        regerror(error_code, &CLS_re, error_msg, 128);
        printf("A SYS_NNN failed to compile: %s\n", error_msg);
        exit(1);
    }
    regcomp(&JP_NNN_re, JP_NNN, REG_ICASE);
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
    if((error_code = regcomp(&LD_I_V_re ,LD_I_V, REG_ICASE))) {
        regerror(error_code, &CLS_re, error_msg, 128);
        printf("A SYS_NNN failed to compile: %s\n", error_msg);
        exit(1);
    }
    regcomp(&LD_V_I_re ,LD_V_I, REG_ICASE);
}
