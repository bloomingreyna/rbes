#include <cpu/cpu.h>
#include <cpu/instructions.h>

void instructions::shift::ArithmeticShiftLeft(CPU& cpu, int step) {
    switch (step) {
        case 0: {
            if (cpu.instruction == Instruction::ASL_ACC) {
                cpu.alu.ArithmeticShiftLeft(cpu.accumulator);
                cpu.accumulator = cpu.alu.result;

                cpu.CompleteInstruction();
            } else {
                cpu.rw_line = RWline::WRITE;
                cpu.alu.ArithmeticShiftLeft(cpu.data_bus);
            }
            cpu.status &= cpu.alu.clear_mask;
            cpu.status |= cpu.alu.status;
            break;
        }
        case 1: {
            cpu.data_bus = cpu.alu.result;
            cpu.CompleteInstruction();
            break;
        }
    }
}

void instructions::shift::LogicalShiftRight(CPU& cpu, int step) {
    switch (step) {
        case 0: {
            if (cpu.instruction == Instruction::ASL_ACC) {
                cpu.alu.LogicalShiftRight(cpu.accumulator);
                cpu.accumulator = cpu.alu.result;

                cpu.CompleteInstruction();
            } else {
                cpu.rw_line = RWline::WRITE;
                cpu.alu.LogicalShiftRight(cpu.data_bus);
            }
            cpu.status &= cpu.alu.clear_mask;
            cpu.status |= cpu.alu.status;
            break;
        }
        case 1: {
            cpu.data_bus = cpu.alu.result;
            cpu.CompleteInstruction();
            break;
        }
    }
}

void instructions::shift::RotateLeft(CPU& cpu, int step) {
    switch (step) {
        case 0: {
            bool carry = (cpu.status & Flag::CARRY) != 0;
            if (cpu.instruction == Instruction::ROL_ACC) {
                cpu.alu.RotateLeft(cpu.accumulator, carry);
                cpu.accumulator = cpu.alu.result;

                cpu.CompleteInstruction();
            } else {
                cpu.rw_line = RWline::WRITE;
                cpu.alu.RotateLeft(cpu.data_bus, carry);
            }
            cpu.status &= cpu.alu.clear_mask;
            cpu.status |= cpu.alu.status;
            break;
        }
        case 1: {
            cpu.data_bus = cpu.alu.result;
            cpu.CompleteInstruction();
            break;
        }
    }
}

void instructions::shift::RotateRight(CPU& cpu, int step) {
    switch (step) {
        case 0: {
            bool carry = (cpu.status & Flag::CARRY) != 0;
            if (cpu.instruction == Instruction::ROL_ACC) {
                cpu.alu.RotateRight(cpu.accumulator, carry);
                cpu.accumulator = cpu.alu.result;

                cpu.CompleteInstruction();
            } else {
                cpu.rw_line = RWline::WRITE;
                cpu.alu.RotateRight(cpu.data_bus, carry);
            }
            cpu.status &= cpu.alu.clear_mask;
            cpu.status |= cpu.alu.status;
            break;
        }
        case 1: {
            cpu.data_bus = cpu.alu.result;
            cpu.CompleteInstruction();
            break;
        }
    }
}
