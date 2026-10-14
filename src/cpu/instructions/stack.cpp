#include <cpu/cpu.h>
#include <cpu/instructions.h>

inline void instructions::stack::PushAccumulator(CPU& cpu, int step) {
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

inline void instructions::stack::PullAccumulator(CPU& cpu, int step) {
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

inline void instructions::stack::PushStatus(CPU& cpu, int step) {
    switch (step) {
        case 0: { break; } // Dead cycle
        case 1: {
            cpu.rw_line = RWline::WRITE;

            cpu.address_bus = 0x0100 + cpu.stack_pointer--;
            cpu.data_bus = cpu.status_register | 0b00110000;

            cpu.CompleteInstruction();
            break;
        }
    }
}

inline void instructions::stack::PullStatus(CPU& cpu, int step) {
    switch (step) {
        case 0: { break; } // Dead cycle
        case 1: {
            cpu.address_bus = 0x0100 + ++cpu.stack_pointer;
            break;
        }
        case 2: {
            cpu.status_register &= 0b00110000;
            cpu.status_register |= cpu.data_bus & 0b11001111;

            // TODO: Delay interrupt flag effect

            cpu.CompleteInstruction();
            break;
        }
    }
}

inline void instructions::stack::TransferXtoStack(CPU& cpu, int step) {
    cpu.stack_pointer = cpu.x_index;
    cpu.CompleteInstruction();
}

inline void instructions::stack::TransferStackToX(CPU& cpu, int step) {
    cpu.x_index = cpu.stack_pointer;
    cpu.CompleteInstruction();
}
