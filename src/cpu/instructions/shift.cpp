#include <cpu/cpu.h>
#include <cpu/instructions.h>

// TODO: Do this whole fuckin file

void instructions::shift::ArithmeticShiftLeft(CPU& cpu, int step) {
    switch (step) {
        case 0: {
            if (cpu.instruction == Instruction::ASL_ACC) {
                cpu.alu.ArithmeticShiftLeft(cpu.accumulator);

                cpu.accumulator = cpu.alu.result;
                cpu.status &= cpu.alu.clear_mask;
                cpu.status |= cpu.alu.status;

                cpu.CompleteInstruction();
            } else {
                cpu.alu.ArithmeticShiftLeft(cpu.data_bus);

                cpu.status &= cpu.alu.clear_mask;
                cpu.status |= cpu.alu.status;
            }
            break;
        }
        case 1: {
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

void instructions::shift::LogicalShiftRight(CPU& cpu, int step) {
    switch (step) {
        case 0: {
            if (cpu.instruction == Instruction::LSR_ACC) {
                cpu.alu.LogicalShiftRight(cpu.accumulator);

                cpu.accumulator = cpu.alu.result;
                cpu.status &= cpu.alu.clear_mask;
                cpu.status |= cpu.alu.status;

                cpu.CompleteInstruction();
            } else {
                cpu.alu.LogicalShiftRight(cpu.data_bus);

                cpu.status &= cpu.alu.clear_mask;
                cpu.status |= cpu.alu.status;
            }
            break;
        }
        case 1: {
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

void instructions::shift::RotateLeft(CPU &cpu, int step) {
    switch (step) {}
}
