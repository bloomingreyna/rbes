#include <cpu/addressing_modes.h>
#include <cpu/cpu.h>
#include <memory/memory.h>

inline void addressing_modes::Immediate(CPU& cpu, int step) {
    cpu.CompleteAddressingMode();
    cpu.ExecuteInstruction();
}