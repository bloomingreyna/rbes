#include <cpu/cpu.h>
#include <cpu/instructions.h>
#include <memory/memory.h>

void instructions::jump::Jump(CPU& cpu, int step) {
    cpu.program_counter = cpu.address_bus;
    cpu.CompleteInstruction();
}

void instructions::jump::JumpToSubroutine(CPU&cpu, int step) {
    switch (step) {
        case 0: {
            cpu.latch = cpu.data_bus;
            break;
        }
        case 1: {
            cpu.rw_line = RWline::WRITE;

            cpu.address_bus = 0x0100 + cpu.stack_pointer--;
            cpu.data_bus = cpu.program_counter >> 8;
            break;
        }
        case 2: {
            cpu.address_bus = 0x0100 + cpu.stack_pointer--;
            cpu.data_bus = cpu.program_counter & 0xFF;
            break;
        }
        case 3: {
            cpu.rw_line = RWline::READ;
            cpu.address_bus = cpu.program_counter++;
            cpu.program_counter = cpu.latch;
            break;
        }
        case 4: {
            cpu.program_counter |= cpu.data_bus << 8;
            cpu.CompleteInstruction();
            break;
        }
    }
}

void instructions::jump::ReturnFromSubroutine(CPU& cpu, int step) {
    switch (step) {
        case 0: {
            cpu.address_bus = 0x0100 + ++cpu.stack_pointer;
            break;
        }
        case 1: {
            cpu.program_counter &= 0xFF00;
            cpu.program_counter |= cpu.data_bus;
            cpu.address_bus = 0x0100 + ++cpu.stack_pointer;
            break;
        }
        case 2: {
            cpu.program_counter &= 0xFF;
            cpu.program_counter |= cpu.data_bus << 8;
            break;
        }
        case 3: {
            cpu.program_counter++;
            cpu.CompleteInstruction();
            break;
        }
    }
}

void instructions::jump::ReturnFromInterrupt(CPU& cpu, int step) {
    switch (step) {
        case 0: {
            cpu.address_bus = 0x0100 + ++cpu.stack_pointer;
            break;
        }
        case 1: {
            cpu.status &= 0b00110000;
            cpu.status |= cpu.data_bus & 0b11001111;
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

            cpu.CompleteInstruction();
            break;
        }
    }
}

void instructions::jump::Break(CPU& cpu, int step) {
    switch (step) {
        case 0: {
             cpu.rw_line = RWline::WRITE;
             cpu.address_bus = 0x0100 + cpu.stack_pointer--;
             cpu.data_bus = cpu.program_counter >> 8;
             break;
        }
        case 1: {
            cpu.address_bus = 0x0100 + cpu.stack_pointer--;
            cpu.data_bus = cpu.program_counter & 0xFF;
            break;
        }
        case 2: {
            cpu.address_bus = 0x0100 + cpu.stack_pointer--;
            cpu.data_bus = cpu.status | 0b00100000;
            if (!cpu.is_hardware_interrupt) {
                cpu.data_bus |= Flag::BREAK;
            }
            break;
        }
        case 3: {
            cpu.rw_line = RWline::READ;
            cpu.address_bus = cpu.nmi_signal ? 0xFFFA : 0xFFFE;
            break;
        }
        case 4: {
            cpu.program_counter &= 0xFF00;
            cpu.program_counter |= cpu.data_bus;
            cpu.address_bus = cpu.nmi_signal ? 0xFFFB : 0xFFFF;
            break;
        }
        case 5: {
            cpu.program_counter &= 0xFF;
            cpu.program_counter |= cpu.data_bus << 8;

            cpu.is_hardware_interrupt = false;
            cpu.CompleteInstruction();
            break;
        }
    }
}
