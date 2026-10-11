#include <cpu/addressing_modes.h>
#include <cpu/cpu.h>

inline void Indirect(CPU& cpu, int step) {
    switch (step) {
        case 0: { // Low pointer byte latched
            cpu.address_bus = ++cpu.program_counter;
            cpu.program_counter++;
            break;
        }
        case 1: {
            cpu.address_bus = (cpu.data_bus << 8) | cpu.latch_register;
            break;
        }
        case 2: { // Low target address byte latched

            // Due to a bug in the original CPU, incrementing the pointer address to
            // retrieve the high byte of the target address does not properly cross 
            // pages. The below code intentionally implements this bug.

            uint8_t ptr_low_byte = cpu.address_bus & 0xFF;
            ptr_low_byte++;
            cpu.address_bus &= 0xFF00;
            cpu.address_bus |= ptr_low_byte;

            break;
        }
        case 3: {
            cpu.address_bus = (cpu.data_bus << 8) | cpu.latch_register;
            
            cpu.CompleteAddressingMode();
            break;
        }
    }
}

inline void IndirectX(CPU& cpu, int step) {
    switch (step) {
        case 0: {
            cpu.address_bus = cpu.data_bus;
            cpu.program_counter++;
            break;
        }
        case 1: {
            cpu.address_bus += cpu.x_index;
            cpu.address_bus &= 0xFF;
            break;
        }
        case 2: { // Low target address byte latched
            cpu.address_bus++;
            cpu.address_bus &= 0xFF;
            break;
        }
        case 3: {
            cpu.address_bus = (cpu.data_bus << 8) | cpu.latch_register;

            cpu.CompleteAddressingMode();
            break;
        }
    }
}

inline void IndirectY(CPU& cpu, int step) {
    switch (step) {
        case 0: {
            cpu.address_bus = cpu.data_bus;
            cpu.program_counter++;
            break;
        }
        case 1: { // Low target address byte latched
            cpu.address_bus++;
            cpu.address_bus &= 0xFF;
            break;
        }
        case 2: {
            cpu.alu.AddWithCarry(cpu.latch_register, cpu.y_index, false);
            cpu.address_bus = (cpu.data_bus << 8) | cpu.alu.result;

            // TODO: Always "oops" for store instructions
            if ((cpu.alu.status & Flag::CARRY) == 0) {
                cpu.CompleteAddressingMode();
            }
            break;
        }
        case 3: {
            if ((cpu.alu.status & Flag::CARRY) == 0) {
                cpu.address_bus += 0x01 << 8;
            }

            cpu.CompleteAddressingMode();
            break;
        }
    }
}