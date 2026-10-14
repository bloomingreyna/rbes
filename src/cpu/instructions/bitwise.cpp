#include <cpu/cpu.h>
#include <cpu/instructions.h>

void instructions::bitwise::AND(CPU& cpu, int step) {
    cpu.alu.AND(cpu.accumulator, cpu.data_bus);

    cpu.accumulator = cpu.alu.result;
    cpu.status &= cpu.alu.clear_mask;
    cpu.status |= cpu.alu.status;

    cpu.CompleteInstruction();
}

void instructions::bitwise::OR(CPU& cpu, int step) {
    cpu.alu.OR(cpu.accumulator, cpu.data_bus);

    cpu.accumulator = cpu.alu.result;
    cpu.status &= cpu.alu.clear_mask;
    cpu.status |= cpu.alu.status;

    cpu.CompleteInstruction();
}

void instructions::bitwise::XOR(CPU& cpu, int step) {
    cpu.alu.XOR(cpu.accumulator, cpu.data_bus);

    cpu.accumulator = cpu.alu.result;
    cpu.status &= cpu.alu.clear_mask;
    cpu.status |= cpu.alu.status;

    cpu.CompleteInstruction();
}

void instructions::bitwise::BIT(CPU& cpu, int step) {
    cpu.alu.BIT(cpu.accumulator, cpu.data_bus);

    cpu.status &= cpu.alu.clear_mask;
    cpu.status |= cpu.alu.status;

    cpu.CompleteInstruction();
}
