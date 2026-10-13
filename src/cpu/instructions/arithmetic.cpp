#include <cpu/cpu.h>
#include <cpu/instructions.h>

inline void instructions::arithmetic::AddWithCarry(CPU& cpu, int step) {
    cpu.alu.AddWithCarry(
        cpu.accumulator, cpu.data_bus, (cpu.status & Flag::CARRY) != 0
    );
    cpu.accumulator = cpu.alu.result;
    cpu.status &= cpu.alu.clear_mask;
    cpu.status |= cpu.alu.status;

    cpu.CompleteInstruction();
}

inline void instructions::arithmetic::SubtractWithCarry(CPU& cpu, int step) {
    cpu.alu.AddWithCarry(
        cpu.accumulator, ~cpu.data_bus, (cpu.status & Flag::CARRY) != 0
    );
    cpu.accumulator = cpu.alu.result;
    cpu.status &= cpu.alu.clear_mask;
    cpu.status |= cpu.alu.status;

    cpu.CompleteInstruction();
}

inline void instructions::arithmetic::IncrementMemory(CPU& cpu, int step) {
    switch (step) {
        case 0: {
            cpu.alu.Increment(cpu.data_bus);
            cpu.status &= cpu.alu.clear_mask;
            cpu.status |= cpu.alu.status;
            break;
        }
        case 1: { // Simulate routing ALU output to data bus
            cpu.rw_line = RWline::WRITE;
            break;
        }
        case 2: {
            cpu.data_bus = cpu.alu.result;
            cpu.CompleteInstruction();
            break;
        }
    }
}

inline void instructions::arithmetic::IncrementX(CPU& cpu, int step) {
    cpu.alu.Increment(cpu.x_index);

    cpu.x_index = cpu.alu.result;
    cpu.status &= cpu.alu.clear_mask;
    cpu.status |= cpu.alu.status;

    cpu.CompleteInstruction();
}

inline void instructions::arithmetic::IncrementY(CPU& cpu, int step) {
    cpu.alu.Increment(cpu.y_index);

    cpu.y_index = cpu.alu.result;
    cpu.status &= cpu.alu.clear_mask;
    cpu.status |= cpu.alu.status;

    cpu.CompleteInstruction();
}

inline void instructions::arithmetic::DecrementMemory(CPU& cpu, int step) {
    switch (step) {
        case 0: {
            cpu.alu.Decrement(cpu.data_bus);
            cpu.status &= cpu.alu.clear_mask;
            cpu.status |= cpu.alu.status;
            break;
        }
        case 1: { // Simulate routing ALU output to data bus
            cpu.rw_line = RWline::WRITE;
            break;
        }
        case 2: {
            cpu.data_bus = cpu.alu.result;
            cpu.CompleteInstruction();
            break;
        }
    }
}

inline void instructions::arithmetic::DecrementX(CPU& cpu, int step) {
    cpu.alu.Decrement(cpu.x_index);

    cpu.x_index = cpu.alu.result;
    cpu.status &= cpu.alu.clear_mask;
    cpu.status |= cpu.alu.status;

    cpu.CompleteInstruction();
}

inline void instructions::arithmetic::DecrementY(CPU& cpu, int step) {
    cpu.alu.Decrement(cpu.y_index);
    
    cpu.y_index = cpu.alu.result;
    cpu.status &= cpu.alu.clear_mask;
    cpu.status |= cpu.alu.status;

    cpu.CompleteInstruction();
}
