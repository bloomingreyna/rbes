#include <cpu/cpu.h>

inline void CPU::FetchInstruction() {
    program_counter++;
    instruction = static_cast<Instruction>(data_bus);
    fetching = false;
}

inline void CPU::ExecuteInstruction() {
    
}

inline void CPU::CompleteInstruction() {
    target_address = program_counter;
    fetching = true;
}