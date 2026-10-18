#include <cpu/cpu.h>
#include <cpu/instructions.h>

void instructions::stack::PushAccumulator(CPU& cpu, int step) {
    switch (step) {
        case 0: { break; } // Dead cycle
        case 1: {
            cpu.rw_line = RWline::WRITE;

            cpu.address_bus = 0x0100 + cpu.stack_pointer--;
            cpu.data_bus = cpu.accumulator;

            cpu.CompleteInstruction();
            break;
        }
    }
}

void instructions::stack::PullAccumulator(CPU& cpu, int step) {
    switch (step) {
        case 0: { break; } // Dead cycle
        case 1: {
            cpu.address_bus = 0x0100 + ++cpu.stack_pointer;
            break;
        }
        case 2: {
            cpu.accumulator = cpu.data_bus;
            cpu.CompleteInstruction();
            break;
        }
    }
}

void instructions::stack::PushStatus(CPU& cpu, int step) {
    switch (step) {
        case 0: { break; } // Dead cycle
        case 1: {
            cpu.rw_line = RWline::WRITE;

            cpu.address_bus = 0x0100 + cpu.stack_pointer--;
            cpu.data_bus = cpu.status | 0b00110000;

            cpu.CompleteInstruction();
            break;
        }
    }
}

void instructions::stack::PullStatus(CPU& cpu, int step) {
    switch (step) {
        case 0: { break; } // Dead cycle
        case 1: {
            cpu.address_bus = 0x0100 + ++cpu.stack_pointer;
            break;
        }
        case 2: {
            cpu.status &= 0b00110000;
            cpu.status |= cpu.data_bus & 0b11001111;

            cpu.interrupt_delay_signal = true;
            cpu.interrupt_delay_value = !static_cast<bool>(cpu.status & Flag::INTERRUPT_DISABLE);

            cpu.CompleteInstruction();
            break;
        }
    }
}

void instructions::stack::TransferXtoStack(CPU& cpu, int step) {
    cpu.stack_pointer = cpu.x_index;
    cpu.CompleteInstruction();
}

void instructions::stack::TransferStackToX(CPU& cpu, int step) {
    cpu.x_index = cpu.stack_pointer;
    cpu.CompleteInstruction();
}
