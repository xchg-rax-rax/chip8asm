#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

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

int translate_instruction(char* instruction, char* opcode){
    opcode[0] = 0x41;
    opcode[1] = 0x41;
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
