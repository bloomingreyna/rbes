#include <cpu/addressing_modes.h>
#include <cpu/cpu.h>

void addressing_modes::Implied(CPU& cpu, int step) {
    cpu.address_bus = cpu.program_counter;
    cpu.CompleteAddressingMode();
    if (cpu.instruction == Instruction::BRK && !cpu.is_hardware_interrupt) {
        cpu.program_counter++;
    }
}

void addressing_modes::Immediate(CPU& cpu, int step) {
    cpu.address_bus = cpu.program_counter++;
    cpu.CompleteAddressingMode();
}
