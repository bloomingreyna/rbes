#include <cpu/cpu.h>
#include <cpu/instructions.h>

void instructions::other::NOP(CPU &cpu, int step) {
    cpu.CompleteInstruction(); // Literally waste time
}
