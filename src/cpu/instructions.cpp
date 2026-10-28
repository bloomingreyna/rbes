#include <cpu/cpu.h>
#include <cpu/instructions.h>
#include <memory/memory.h>

void CPU::FetchInstruction() {
    rw_line = RWline::READ;

    address_bus = program_counter++;
    data_bus = memory->CPURead(address_bus);

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

    if (inst_cycle_count == -1) { // Branch instruction behavior
        PollInterrupts();
    }

    inst_step = InstructionStep::CALCULATE_ADDRESS;
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

    bool is_store = (
        inst_func == instructions::access::StoreAccumulator ||
        inst_func == instructions::access::StoreX ||
        inst_func == instructions::access::StoreY
    );
    if (is_store || inst_func == instructions::jump::Jump) {
        ExecuteInstruction();
    }
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
