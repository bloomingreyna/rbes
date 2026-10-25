#include <cpu/cpu.h>
#include <memory/memory.h>

void CPU::FetchInstruction() {
    rw_line = RWline::READ;

    instruction = static_cast<Instruction>(data_bus);
    if (service_interrupt) {
        instruction = Instruction::BRK;
        service_interrupt = false;
        is_hardware_interrupt = true;
    }

    size_t index = static_cast<size_t>(instruction);
    addr_func = addressing_mode_array[index];
    inst_func = instruction_array[index];
    inst_cycle_count = cycle_count_array[index];

    inst_step = InstructionStep::CALCULATE_ADDRESS;
    program_counter++;

    if (inst_cycle_count == -1) { // Branch behavior
        PollInterrupts();
    }
}

void CPU::CalculateAddress() {
    addr_func(*this, cycle_step++); 
}

void CPU::ExecuteInstruction() {
    inst_func(*this, cycle_step++);
}

void CPU::CompleteAddressingMode() {
    cycle_step = 0;
    inst_step = InstructionStep::EXECUTE;
}

void CPU::CheckInterruptInputs() {
    if (!nmi_last_state && nmi_input) {
        nmi_signal = true;
    }
    nmi_last_state = nmi_input;

    if (irq_input && (status & Flag::INTERRUPT_DISABLE) != 0) {
        irq_signal = true;
    }
}

void CPU::PollInterrupts() {
    service_interrupt = irq_signal || nmi_signal;
}

void CPU::CompleteInstruction() {
    inst_step = InstructionStep::FETCH;
    cycle_step = 0;
}
