#include <cpu/cpu.h>
#include <cpu/instructions.h>

inline void instructions::compare::CompareAccumulator(CPU& cpu, int step) {
    cpu.alu.Compare(cpu.accumulator, cpu.data_bus);

    cpu.status &= cpu.alu.clear_mask;
    cpu.status |= cpu.alu.status;

    cpu.CompleteInstruction();
}

inline void instructions::compare::CompareX(CPU& cpu, int step) {
    cpu.alu.Compare(cpu.x_index, cpu.data_bus);

    cpu.status &= cpu.alu.clear_mask;
    cpu.status |= cpu.alu.status;

    cpu.CompleteInstruction();
}

inline void instructions::compare::CompareY(CPU& cpu, int step) {
    cpu.alu.Compare(cpu.y_index, cpu.data_bus);

    cpu.status &= cpu.alu.clear_mask;
    cpu.status |= cpu.alu.status;

    cpu.CompleteInstruction();
}

