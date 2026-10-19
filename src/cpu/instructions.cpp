#include <cpu/cpu.h>
#include <memory/memory.h>

#define Implied nullptr

void CPU::FetchInstruction() {
    rw_line = RWline::READ;

    if (interrupt_poll) {
        instruction = Instruction::BRK;
        hardware_interrupt = true;

        interrupt_poll = false;
    } else {
        instruction = static_cast<Instruction>(data_bus);
        address_bus = ++program_counter;
    }

    if (interrupt_delay_signal) {
        allow_irq = interrupt_delay_value;
    }

    uint8_t opcode = static_cast<uint8_t>(instruction);
    if (addressing_mode_array[opcode] != Implied) {
        inst_step = InstructionStep::CALCULATE_ADDRESS;
    } else {
        inst_step = InstructionStep::EXECUTE;
    }
}

void CPU::CalculateAddress() {
    uint8_t opcode = static_cast<uint8_t>(instruction);
    addressing_mode_array[opcode](*this, cycle_step++);
}

void CPU::ExecuteInstruction() {
    uint8_t opcode = static_cast<uint8_t>(instruction);
    instruction_array[opcode](*this, cycle_step++);
}

void CPU::CompleteAddressingMode() {
    cycle_step = 0;
    inst_step = InstructionStep::EXECUTE;
}

void CPU::PollInterrupts() {
    if ((allow_irq && irq_interrupt) || nmi_interrupt) {
        interrupt_poll = true;
    }
}

void CPU::CompleteInstruction() {
    inst_step = InstructionStep::FETCH;
    cycle_step = 0;
}
