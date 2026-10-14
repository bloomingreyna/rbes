#include <cpu/cpu.h>
#include <cpu/instructions.h>

void instructions::transfer::TransferAccumulatorToX(CPU& cpu, int step) {
    cpu.x_index = cpu.accumulator;
    cpu.CompleteInstruction();
}

void instructions::transfer::TransferAccumulatorToY(CPU& cpu, int step) {
    cpu.y_index = cpu.accumulator;
    cpu.CompleteInstruction();
}

void instructions::transfer::TransferXtoAccumulator(CPU& cpu, int step) {
    cpu.accumulator = cpu.x_index;
    cpu.CompleteInstruction();
}

void instructions::transfer::TransferYtoAccumulator(CPU& cpu, int step) {
    cpu.accumulator = cpu.y_index;
    cpu.CompleteInstruction();
}
