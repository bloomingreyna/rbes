#include <cpu/addressing_modes.h>
#include <cpu/cpu.h>

inline void addressing_modes::Absolute(CPU& cpu, int step) {
    switch (step) {
        case 0: { // Low address byte latched
            cpu.address_bus = ++cpu.program_counter;
            cpu.program_counter++;
            break;
        }
        case 1: {
            cpu.address_bus = (cpu.data_bus << 8) | cpu.latch_register;

            cpu.CompleteAddressingMode();
            break;
        }
    }
}

inline void addressing_modes::AbsoluteX(CPU& cpu, int step) {
    switch (step) {
        case 0: { // Low base address byte latched
            cpu.address_bus = ++cpu.program_counter;
            cpu.program_counter++;
            break;
        }
        case 1: {
            cpu.alu.AddWithCarry(cpu.latch_register, cpu.x_index, false);
            cpu.address_bus = (cpu.data_bus << 8) | cpu.alu.result;

            // TODO: Always "oops" for store instructions
            if ((cpu.alu.status & Flag::CARRY) == 0) {
                cpu.CompleteAddressingMode();
            }
            break;
        }
        case 2: {
            if ((cpu.alu.status & Flag::CARRY) == 0) {
                cpu.address_bus += 0x01 << 8;
            }

            cpu.CompleteAddressingMode();
            break;
        }
    }
}

inline void addressing_modes::AbsoluteY(CPU& cpu, int step) {
    switch (step) {
        case 0: { // Low base address byte latched
            cpu.address_bus = ++cpu.program_counter;
            cpu.program_counter++;
            break;
        }
        case 1: {
            cpu.alu.AddWithCarry(cpu.latch_register, cpu.y_index, false);
            cpu.address_bus = (cpu.data_bus << 8) | cpu.alu.result;

            // TODO: Always "oops" for store instructions
            if ((cpu.alu.status & Flag::CARRY) != 0) {
                cpu.CompleteAddressingMode();
            }
            break;
        }
        case 2: {
            if ((cpu.alu.status & Flag::CARRY) != 0) {
                cpu.address_bus += 0x01 << 8;
            }

            cpu.CompleteAddressingMode();
            break;
        }
    }
}