#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

#include "../src/instructions.h"

int main() {
    char CLS[] = "CLS";
    char SYS[] = "SYS 0A7";
    compile_instruction_regs();
    printf("%s, %d\n",CLS,regexec(&CLS_re, CLS, 0, NULL, 0));
    printf("%s, %d\n", SYS,regexec(&SYS_NNN_re, SYS, 0, NULL, 0));
}
