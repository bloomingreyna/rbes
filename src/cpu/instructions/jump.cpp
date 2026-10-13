#include <cpu/cpu.h>
#include <cpu/instructions.h>

inline void instructions::jump::Jump(CPU& cpu, int step) {
    cpu.program_counter = cpu.data_bus;
    cpu.CompleteInstruction();
}

inline void instructions::jump::JumpToSubroutine(CPU&cpu, int step) {
    switch (step) {
        case 0: {
            cpu.rw_line = RWline::WRITE;

            cpu.latch_register = cpu.data_bus;
            cpu.data_bus = cpu.program_counter >> 8;
            cpu.address_bus = 0x0100 + cpu.stack_pointer--;
            break;
        }
        case 1: {
            cpu.data_bus = cpu.program_counter & 0xFF;
            cpu.address_bus = 0x0100 + cpu.stack_pointer--;
            break;
        }
        case 2: {
            cpu.rw_line = RWline::READ;
            cpu.program_counter = cpu.latch_register;

            cpu.CompleteInstruction();
            break;
        }
    }
}

inline void instructions::jump::ReturnFromSubroutine(CPU& cpu, int step) {
    switch (step) {
        case 0: { break; } // Dead cycle
        case 1: {
            cpu.address_bus = 0x0100 + ++cpu.stack_pointer;
            break;
        }
        case 2: {
            cpu.program_counter &= 0xFF00;
            cpu.program_counter |= cpu.data_bus;

            cpu.address_bus = 0x0100 + ++cpu.stack_pointer;
            break;
        }
        case 3: {
            cpu.program_counter &= 0xFF;
            cpu.program_counter |= cpu.data_bus << 8;
            break;
        }
        case 4: {
            cpu.program_counter++;
            cpu.CompleteInstruction();
            break;
        }
    }
}

inline void instructions::jump::ReturnFromInterrupt(CPU& cpu, int step) {
    switch (step) {
        case 0: { break; } // Dead cycle
        case 1: {
            cpu.address_bus = 0x0100 + ++cpu.stack_pointer;
            break;
        }
        case 2: {
            cpu.status_register &= 0b00110000;
            cpu.status_register |= cpu.data_bus & 0b11001111;

            cpu.irq_interrupt = (cpu.status_register & Flag::INTERRUPT_DISABLE) == 0;

            cpu.address_bus = 0x0100 + ++cpu.stack_pointer;
            break;
        }
        case 3: {
            cpu.program_counter &= 0xFF00;
            cpu.program_counter |= cpu.data_bus;

            cpu.address_bus = 0x0100 + ++cpu.stack_pointer;
            break;
        }
        case 4: {
            cpu.program_counter &= 0xFF;
            cpu.program_counter |= cpu.data_bus << 8;

            cpu.CompleteInstruction();
            break;
        }
}

inline void instructions::jump::Break(CPU& cpu, int step) {
    switch (step) {
        case 0: {
            cpu.rw_line = RWline::WRITE;

            cpu.data_bus = cpu.status_register | 0b00110000;
            cpu.address_bus = 0x0100 + cpu.stack_pointer--;
            break;
        }
        case 1: {
            cpu.program_counter++; // BRK weirdness

            cpu.data_bus = cpu.program_counter >> 8;
            cpu.address_bus = 0x0100 + cpu.stack_pointer--;
            break;
        }
        case 2: {
            cpu.data_bus = cpu.program_counter & 0xFF;
            cpu.address_bus = 0x0100 + cpu.stack_pointer--;
            break;
        }
        case 3: {
            cpu.rw_line = RWline::READ;
            cpu.address_bus = 0xFFFE;
            break;
        }
        case 4: {
            cpu.latch_register = cpu.data_bus;
            cpu.address_bus = 0xFFFF;
            break;
        }
        case 5: {
            cpu.program_counter = (cpu.data_bus << 8) | cpu.latch_register;
            cpu.CompleteInstruction();
            break;
        }
    }
}
