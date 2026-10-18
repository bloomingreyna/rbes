#include <cpu/cpu.h>
#include <cpu/instructions.h>

void instructions::flags::ClearCarry(CPU& cpu, int step) {
    cpu.status &= ~Flag::CARRY;
    cpu.CompleteInstruction();
}

void instructions::flags::ClearInterruptDisable(CPU& cpu, int step) {
    cpu.status &= ~Flag::INTERRUPT_DISABLE;
    cpu.interrupt_delay_signal = true;
    cpu.interrupt_delay_value = true;

    cpu.CompleteInstruction();
}

void instructions::flags::ClearDecimal(CPU& cpu, int step) {
    cpu.status &= ~Flag::DECIMAL;
    cpu.CompleteInstruction();
}

void instructions::flags::ClearOverflow(CPU& cpu, int step) {
    cpu.status &= ~Flag::OVERFLOW;
    cpu.CompleteInstruction();
}

void instructions::flags::SetCarry(CPU& cpu, int step) {
    cpu.status |= Flag::CARRY;
    cpu.CompleteInstruction();
}

void instructions::flags::SetInterruptDisable(CPU& cpu, int step) {
    cpu.status |= Flag::INTERRUPT_DISABLE;
    cpu.interrupt_delay_signal = true;
    cpu.interrupt_delay_value = false;

    cpu.CompleteInstruction();
}

void instructions::flags::SetDecimal(CPU& cpu, int step) {
    cpu.status |= Flag::DECIMAL;
    cpu.CompleteInstruction();
}
