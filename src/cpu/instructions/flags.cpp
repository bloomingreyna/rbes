#include <cpu/cpu.h>
#include <cpu/instructions.h>

void ClearCarry(CPU& cpu, int step) {
    cpu.status &= ~Flag::CARRY;
    cpu.CompleteInstruction();
}

void ClearInterruptDisable(CPU& cpu, int step) {
    cpu.status &= ~Flag::INTERRUPT_DISABLE;
    cpu.interrupt_delay_signal = true;
    cpu.interrupt_delay_value = true;

    cpu.CompleteInstruction();
}

void ClearDecimal(CPU& cpu, int step) {
    cpu.status &= ~Flag::DECIMAL;
    cpu.CompleteInstruction();
}

void ClearOverflow(CPU& cpu, int step) {
    cpu.status &= ~Flag::OVERFLOW;
    cpu.CompleteInstruction();
}

void SetCarry(CPU& cpu, int step) {
    cpu.status |= Flag::CARRY;
    cpu.CompleteInstruction();
}

void SetInterruptDisable(CPU& cpu, int step) {
    cpu.status |= Flag::INTERRUPT_DISABLE;
    cpu.interrupt_delay_signal = true;
    cpu.interrupt_delay_value = false;

    cpu.CompleteInstruction();
}

void SetDecimal(CPU& cpu, int step) {
    cpu.status |= Flag::DECIMAL;
    cpu.CompleteInstruction();
}
