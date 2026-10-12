#include <cpu/addressing_modes.h>
#include <cpu/cpu.h>

inline void addressing_modes::Immediate(CPU& cpu, int step) {
    cpu.program_counter++;

    cpu.CompleteAddressingMode();
    cpu.ExecuteInstruction();
}