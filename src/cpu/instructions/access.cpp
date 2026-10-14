#include <cpu/cpu.h>
#include <cpu/instructions.h>

void instructions::access::LoadAccumulator(CPU& cpu, int step) {
    cpu.accumulator = cpu.data_bus;
    cpu.CompleteInstruction();
}

void instructions::access::LoadX(CPU& cpu, int step) {
    cpu.x_index = cpu.data_bus;
    cpu.CompleteInstruction();
}

void instructions::access::LoadY(CPU& cpu, int step) {
    cpu.y_index = cpu.data_bus;
    cpu.CompleteInstruction();
}

void instructions::access::StoreAccumulator(CPU& cpu, int step) {
    cpu.rw_line = RWline::WRITE;
    cpu.data_bus = cpu.accumulator;

    cpu.CompleteInstruction();
}

void instructions::access::StoreX(CPU& cpu, int step) {
    cpu.rw_line = RWline::WRITE;
    cpu.data_bus = cpu.x_index;

    cpu.CompleteInstruction();
}

void instructions::access::StoreY(CPU& cpu, int step) {
    cpu.rw_line = RWline::WRITE;
    cpu.data_bus = cpu.y_index;

    cpu.CompleteInstruction();
}
