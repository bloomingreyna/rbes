#include <cpu/cpu.h>

inline void CPU::FetchInstruction() {
    address_bus = ++program_counter;
    instruction = static_cast<Instruction>(data_bus);
    inst_step = InstructionStep::CALCULATE_ADDRESS;
}

inline void CPU::CalculateAddress() {
    uint8_t opcode = static_cast<uint8_t>(instruction);
    addressing_mode_array[static_cast<size_t>(opcode)](*this, cycle_step++);
}

inline void CPU::ExecuteInstruction() {
    uint8_t opcode = static_cast<uint8_t>(instruction);
    instruction_array[static_cast<size_t>(opcode)](*this, cycle_step++);
}

inline void CPU::CompleteAddressingMode() {
    cycle_step = 0;
    inst_step = InstructionStep::EXECUTE;
}

inline void CPU::CompleteInstruction() {
    address_bus = program_counter;
    inst_step = InstructionStep::FETCH;
}