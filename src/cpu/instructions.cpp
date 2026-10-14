#include <cpu/cpu.h>

void CPU::FetchInstruction() {
    rw_line = RWline::READ;
    instruction = static_cast<Instruction>(data_bus);
    address_bus = ++program_counter;
    inst_step = InstructionStep::CALCULATE_ADDRESS;
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

void CPU::CompleteInstruction() {
    inst_step = InstructionStep::FETCH;
    cycle_step = 0;
}
