#include <cpu/cpu.h>
#include <cpu/instructions.h>
#include <memory/memory.h>
#include <memory/enums.h>

void instructions::jump::Jump(CPU& cpu, int step) {
    cpu.program_counter = cpu.data_bus;
    cpu.CompleteInstruction();
}

void instructions::jump::JumpToSubroutine(CPU&cpu, int step) {
    switch (step) {
        case 0: {
            cpu.latch_register = cpu.data_bus;
            break;
        }
        case 1: { break; }
        case 2: {
            cpu.rw_line = RWline::WRITE;

            cpu.data_bus = cpu.program_counter >> 8;
            cpu.address_bus = 0x0100 + cpu.stack_pointer--;
            break;
        }
        case 3: {
            cpu.data_bus = cpu.program_counter & 0xFF;
            cpu.address_bus = 0x0100 + cpu.stack_pointer--;
            break;
        }
        case 4: {
            cpu.rw_line = RWline::READ;

            cpu.second_latch = cpu.memory->DirectAccess(++cpu.program_counter);
            cpu.program_counter = (cpu.second_latch << 8) | cpu.latch_register;

            cpu.CompleteInstruction();
            break;
        }
    }
}

void instructions::jump::ReturnFromSubroutine(CPU& cpu, int step) {
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

void instructions::jump::ReturnFromInterrupt(CPU& cpu, int step) {
    switch (step) {
        case 0: { break; } // Dead cycle
        case 1: {
            cpu.address_bus = 0x0100 + ++cpu.stack_pointer;
            break;
        }
        case 2: {
            cpu.status &= 0b00110000;
            cpu.status |= cpu.data_bus & 0b11001111;

            cpu.allow_irq = !static_cast<bool>(cpu.status & Flag::INTERRUPT_DISABLE);

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
}

// No, FetchInterruptVector doesn't count as a fucking memory access and you can't convince me otherwise
void instructions::jump::Break(CPU& cpu, int step) {
    switch (step) {
        case 0: { break; }
        case 1: {
            cpu.rw_line = RWline::WRITE;

            if (!cpu.hardware_interrupt) {
                cpu.program_counter++; // BRK weirdness
            }

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
            cpu.data_bus = cpu.status | 0b00100000;
            if (!cpu.hardware_interrupt) {
                cpu.data_bus |= Flag::BREAK;
            }
            cpu.address_bus = 0x0100 + cpu.stack_pointer--;
            break;
        }
        case 4: {
            cpu.rw_line = RWline::READ;
            cpu.address_bus = 0xFFFE;

            InterruptVector vec = cpu.nmi_interrupt ? InterruptVector::NMI : InterruptVector::IRQ;
            cpu.program_counter &= 0xFF00;
            cpu.program_counter = cpu.memory->FetchInterruptVector(vec, InterruptVectorByte::LOW);
            break;
        }
        case 5: {
            cpu.status |= Flag::INTERRUPT_DISABLE;

            InterruptVector vec = cpu.nmi_interrupt ? InterruptVector::NMI : InterruptVector::IRQ;
            cpu.program_counter &= 0xFF;
            cpu.program_counter |= cpu.memory->FetchInterruptVector(vec, InterruptVectorByte::HIGH) << 8;

            cpu.hardware_interrupt = false;
            cpu.CompleteInstruction();
            break;
        }
    }
}
