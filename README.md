# Chip8 Assembler
```
      ___           ___                       ___           ___      
     /\  \         /\__\          ___        /\  \         /\  \     
    /::\  \       /:/  /         /\  \      /::\  \       /::\  \  
   /:/\:\  \     /:/__/          \:\  \    /:/\:\  \     /:/\:\  \   
  /:/  \:\  \   /::\  \ ___      /::\__\  /::\~\:\  \   /::\~\:\  \  
 /:/__/ \:\__\ /:/\:\  /\__\  __/:/\/__/ /:/\:\ \:\__\ /:/\:\ \:\__\
 \:\  \  \/__/ \/__\:\/:/  / /\/:/  /    \/__\:\/:/  / \:\ \:\/:/  /
  \:\  \            \::/  /  \::/__/          \::/  /   \:\ \::/  / 
   \:\  \           /:/  /    \:\__\           \/__/     \:\/:/  /   
    \:\__\         /:/  /      \/__/                      \::/  /    
     \/__/         \/__/                                   \/__/     
```

Chip8 is a fictional computer architecture created in the 70s by Jospeh Weisbecker to allow video games to be more easily programmed for a diverse range of computer hardware.
Chip8 is realized in the form of a virtual machine on which ROMs either compiled, assembled or handwritten (byte by byte!) are run.
This repository contains the source code of an assembler for Frédéric Devernay's version of Chip8 assembly (http://devernay.free.fr/hacks/chip8/C8TECH10.HTM) that allows programs written in it to be converted into functioning Chip8 ROMs.

I've also created my own implementation of the Chip8 virtual machine along with an disassembler of Frédéric's Chip8 assembly. 
They can be found here https://github.com/xchg-rax-rax/Chip8-Emulator and here https://github.com/xchg-rax-rax/chip8dasm respectively.

## Compilation

For the moment to compile the program use the following commands (I'll add a make file later...):
```{bash}
$ git clone https://github.com/xchg-rax-rax/chip8asm
$ cd chip8asm
$ gcc ./src/chip8asm.c -o ./bin/chip8asm
```
## To Do

* Some Testing has been done but more testing would be useful to uncover any further bugs
* Should buffer output in some way for efficiency and so that it doesn't modify files without reason
