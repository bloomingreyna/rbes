#include <cpu/cpu.h>
#include <cpu/instructions.h>

void instructions::compare::CompareAccumulator(CPU& cpu, int step) {
    cpu.alu.Compare(cpu.accumulator, cpu.data_bus);

    cpu.status &= cpu.alu.clear_mask;
    cpu.status |= cpu.alu.status;

    cpu.CompleteInstruction();
}

void instructions::compare::CompareX(CPU& cpu, int step) {
    cpu.alu.Compare(cpu.x_index, cpu.data_bus);

    cpu.status &= cpu.alu.clear_mask;
    cpu.status |= cpu.alu.status;

    cpu.CompleteInstruction();
}

void instructions::compare::CompareY(CPU& cpu, int step) {
    cpu.alu.Compare(cpu.y_index, cpu.data_bus);

    cpu.status &= cpu.alu.clear_mask;
    cpu.status |= cpu.alu.status;

    cpu.CompleteInstruction();
}

