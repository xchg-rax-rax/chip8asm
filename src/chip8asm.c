#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <regex.h>

#include <sys/stat.h>
#include <sys/mman.h>

#include "instructions.h"

int read_instruction(char** asm_ptr, char* instruction) {
    int instruction_len = 0;
    while (**asm_ptr == '\n') {
        (*asm_ptr)++;
    }
    while ((*asm_ptr)[instruction_len] != '\n' && (*asm_ptr)[instruction_len] != EOF) {
        instruction_len++;
    }
    strncpy(instruction, *asm_ptr, instruction_len & 0xFF);
    instruction[instruction_len] = 0;
    *asm_ptr += instruction_len; // might me an off by one error here
    return instruction_len;
}

char* skip_spaces(char * instruction) {
    while(*instruction == ' ') {
        instruction++;
    }
    return instruction;
}

void translate_NNN_instruction(char* instruction, char* opcode, char leader, unsigned short instruction_len) {
        unsigned short addr
        instruction = skip_spaces(instruction + instruction_len);
        addr = (unsigned short) strtol(instruction, NULL, 16);
        opcode[0] = (unsigned char) (leader << 4) | ((0xF00 & addr) >> 8);
        opcode[1] = (unsigned char) 0xFF & addr;
}

void translate_V_V_instruction(char* instruction, char* opcode, char leader, char finisher, unsigned short instruction_len) {
        unsigned char X, Y;
        instruction = skip_spaces(instruction + instruction_len) + 1;
        X = (unsigned char) strtol(instruction, NULL, 16);
        instruction = skip_spaces(instruction + 1) + 1;
        Y = (unsigned char) strtol(instruction, NULL, 16);
        opcode[0] = (leader << 4) | X;
        opcode[1] = (Y << 4) | finisher;
}

void translate_V_NN_instruction(char* instruction, char* opcode, char leader, unsigned short instruction_len) {
        unsigned char X, byte;
        instruction = skip_spaces(instruction + instruction_len) + 1;
        X = (unsigned char) strtol(instruction, NULL, 16);
        instruction = skip_spaces(instruction + 1);
        byte = (unsigned char) strtol(instruction, NULL, 16);
        opcode[0] = (leader << 4) | X;
        opcode[1] = byte;
}

void translate_V_instruction(char* instruction, char* opcode, char leader, char finisher, unsigned short instruction_len) {
        instruction = skip_spaces(instruction + instruction_len) + 1;
        X = (unsigned char) strtol(instruction, NULL, 16);
        opcode[0] = (leader << 4) | X;
        opcode[1] = finisher;
}

void translate_Z_V_instruction(char* instruction, char* opcode, char leader, char finisher, unsigned short instruction_len, unsigned short Z_len) {
        instruction = skip_spaces(skip_spaces(instruction + instruction_len) + Z_len) + 1;
        X = (unsigned char) strtol(instruction, NULL, 16);
        opcode[0] = (leader << 4) | X;
        opcode[1] = finisher;
}

void translate_Z_NNN_instruction(char* instruction, char* opcode, char leader, unsigned short instruction_len, unsigned short Z_len) {
        instruction = skip_spaces(skip_spaces(instruction + instruction_len) + Z_len);
        addr = (unsigned short) strtol(instruction, NULL, 16);
        opcode[0] = (unsigned char) (leader << 4) | ((0xF00 & addr) >> 8);
        opcode[1] =(unsigned char) 0xFF & addr;
}

int translate_instruction(char* instruction, char* opcode){
    unsigned char byte, nibble, X, Y;
    unsigned short addr;
    // instruction MUST be null terminated
    instruction = skip_spaces(instruction);

    // I am being very silly here
    // This can and should be refactored
    if(!regexec(CLS_re, instruction, 0, NULL, 0)) {
        opcode[0] = 0;
        opcode[1] = 0xE0;
    }
    else if(!regexec(RET_re, instruction, 0 NULL, 0)) {
        opcode[0] = 0;
        opcode[1] = 0xEE;
    }
    else if(!regexec(SYS_NNN_re, instruction, 0 NULL, 0)) {
        translate_NNN_instruction(instruction, opcode, 0x0, 3);
    }
    else if(!regexec(JP_NNN_re, instruction, 0, NULL, 0)) {
        translate_NNN_instruction(instruction, opcode, 0x1, 2);
    }
    else if(!regexec(CALL_NNN_re, instruction, 0, NULL, 0)) {
        translate_NNN_instruction(instruction, opcode, 0x2, 3);
    }
    else if(!regexec(SE_V_NN_re, instruction, 0, NULL, 0)) {
        translate_V_NN_instruction(instruction, opcode, 0x3, 2);
    }
    else if(!regexec(SNE_V_NN_re, instruction, 0, NULL, 0)) {
        translate_V_NN_instruction(instruction, opcode, 0x4, 3);
    }
    else if(!regexec(SE_V_V_re, instruction, 0, NULL, 0)) {
        translate_V_V_instruction(instruction, opcode, 0x5, 2);
    }
    else if(!regexec(LD_V_NN_re, instruction, 0, NULL, 0)) {
        translate_V_NN_instruction(instruction, opcode, 0x6, 2);
    }
    else if(!regexec(ADD_V_NN_re, instruction, 0, NULL, 0)) {
        translate_V_NN_instruction(instruction, opcode, 0x7, 3);
    }
    else if(!regexec(LD_V_V_re, instruction, 0, NULL, 0)) {
        translate_V_V_instruction(instruction, opcode, 0x8, 0x0, 2);
    }
    else if(!regexec(OR_V_V_re, instruction, 0, NULL, 0)) {
        translate_V_V_instruction(instruction, opcode, 0x8, 0x1, 2);
    }
    else if(!regexec(AND_V_V_re, instruction, 0, NULL, 0)) {
        translate_V_V_instruction(instruction, opcode, 0x8, 0x2, 3);
    }
    else if(!regexec(XOR_V_V_re, instruction, 0, NULL, 0)) {
        translate_V_V_instruction(instruction, opcode, 0x8, 0x3, 3);
    }
    else if(!regexec(ADD_V_V_re, instruction, 0, NULL, 0)) {
        translate_V_V_instruction(instruction, opcode, 0x8, 0x4, 3);
    }
    else if(!regexec(SUB_V_V_re, instruction, 0, NULL, 0)) {
        translate_V_V_instruction(instruction, opcode, 0x8, 0x5, 3);
    }
    else if(!regexec(SHR_V_V_re, instruction, 0, NULL, 0)) {
        translate_V_V_instruction(instruction, opcode, 0x8, 0x6, 3);
    }
    else if(!regexec(SUBN_V_V_re, instruction, 0, NULL, 0)) {
        translate_V_V_instruction(instruction, opcode, 0x8, 0x7, 4);
    }
    else if(!regexec(SHL_V_V_re, instruction, 0, NULL, 0)) {
        translate_V_V_instruction(instruction, opcode, 0x8, 0xE, 3);
    }
    else if(!regexec(SNE_V_V_re, instruction, 0, NULL, 0)) {
        translate_V_V_instruction(instruction, opcode, 0x9, 0x0, 3);
    }
    else if(!regexec(LD_I_NNN_re, instruction, 0, NULL, 0)) {
        translate_Z_NNN_instruction(instruction, opcode, 0xA, 2, 1)
    }
    else if(!regexec(JP_V0_NNN_re, instruction, 0, NULL, 0)) {
        translate_Z_NNN_instruction(instruction, opcode, 0xB, 2, 2)
    }
    else if(!regexec(RND_V_NN_re, instruction, 0, NULL, 0)) {
        translate_V_NN_instruction(instruction, opcode, 0xC, 3);
    }
    else if(!regexec(DRW_V_V_N_re, instruction, 0, NULL, 0)) {
        // this one is unique, might still be a good idea to refactor into it's own function for readability 
        instruction = skip_spaces(instruction + 3) + 1;
        X = (unsigned char) strtol(instruction, NULL, 16);
        instruction = skip_spaces(instruction + 1) + 1;
        Y = (unsigned char) strtol(instruction, NULL, 16);
        instruction = skip_spaces(instruction + 1);
        byte = (unsigned char) strtol(instruction, NULL, 16);
        opcode[0] = 0xD0 | X;
        opcode[1] = (Y << 4) | byte;
    }
    else if(!regexec(SKP_V_re, instruction, 0, NULL, 0)) {
        translate_V_instruction(instruction, opcode, 0xE, 0x9E, 3);
    }
    else if(!regexec(SKNP_V_re, instruction, 0, NULL, 0)) {
        translate_V_instruction(instruction, opcode, 0xE, 0xA1, 4);
    }
    else if(!regexec(LD_V_DT_re, instruction, 0, NULL, 0)) {
        translate_V_instruction(instruction, opcode, 0xF, 0x07, 2, 2);
    }
    else if(!regexec(LD_V_K_re, instruction, 0, NULL, 0)) {
        translate_V_instruction(instruction, opcode, 0xF, 0x0A, 2, 1);
    }
    else if(!regexec(LD_DT_V_re, instruction, 0, NULL, 0)) {
        translate_Z_V_instruction(instruction, opcode, 0xF, 0x15, 2, 2);
    }
    else if(!regexec(LD_ST_V_re, instruction, 0, NULL, 0)) {
        translate_Z_V_instruction(instruction, opcode, 0xF, 0x18, 2, 2);
    }
    else if(!regexec(ADD_I_V_re, instruction, 0, NULL, 0)) {
        translate_Z_V_instruction(instruction, opcode, 0xF, 0x1E, 3, 1);
    }
    else if(!regexec(LD_F_V_re, instruction, 0, NULL, 0)) {
        translate_Z_V_instruction(instruction, opcode, 0xF, 0x29, 2, 1);
    }
    else if(!regexec(LD_B_V_re, instruction, 0, NULL, 0)) {
        translate_Z_V_instruction(instruction, opcode, 0xF, 0x33, 2, 1);
    }
    else if(!regexec(LD_I_V_re, instruction, 0, NULL, 0)) {
        translate_Z_V_instruction(instruction, opcode, 0xF, 0x55, 2, 1);
    }
    else if(!regexec(LD_V_I_re, instruction, 0, NULL, 0)) {
        translate_V_instruction(instruction, opcode, 0xF, 0x65, 2, 3);
    }
    else {
        return -1;
    }
    return 0;
} 


int main(int argc, char** argv) {
    int asm_fd, error;
    struct stat asm_file_stat;
    FILE* output_fs;
    char* asm_ptr, *asm_path, *output_path; 
    char instruction[256];
    unsigned char opcode[2];


    if(argc != 3) {
        printf("Usage: %s <asm file> <output file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // open input file and mmap it
    asm_path = argv[1];
    if((asm_fd= open(asm_path, O_RDONLY)) == -1) {
        printf("[!] Error: Could not open asm file %s.\n", asm_path);
        exit(EXIT_FAILURE);
    }

    if(fstat(asm_fd, &asm_file_stat) == -1) {
        printf("[!] Error: Could not get size of asm file %s.\n", asm_path);
        exit(EXIT_FAILURE);
    }
    if(!(asm_ptr = (char*) mmap(0, asm_file_stat.st_size, PROT_READ, MAP_PRIVATE, asm_fd, 0)) ) {
        printf("[!] Error: Could not mmap asm file %s.\n", asm_path);
        exit(EXIT_FAILURE);
    }
    close(asm_fd);

    // open output file 
    output_path = argv[2];
    if((output_fs = fopen(output_path, "wb")) == NULL) {
        printf("[!] Error: Could not open output file %s.\n",output_path);
        exit(EXIT_FAILURE);
    }

    error = 0;
    while(read_instruction(&asm_ptr, instruction)) {
        if (translate_instruction(instruction, opcode) == -1) {
            printf("[!] Invalid instruction '%s' on line %d\n");
            error = 1;
        }
        if (!error) {
            if(!fwrite(opcode, 2, 1, output_fs)){
                printf("[!] Fatal Error: Failed to write to output file.\n");
                error = 1;
                break;
            }
        }
    }

    // close files and if there was an error delete the output file
    munmap(asm_ptr,asm_file_stat.st_size);
    fclose(output_fs);
    if (error) {
        remove(output_path);     
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}
