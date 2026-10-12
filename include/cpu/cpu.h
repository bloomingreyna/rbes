#include <array>
#include <cstdint>

#include <cpu/alu.h>
#include <cpu/enums.h>

class Memory;

class CPU {
public:
    inline void ExecutionLogic();

    inline void FetchInstruction();
    inline void CalculateAddress();
    inline void ExecuteInstruction();

    inline void CompleteAddressingMode();
    inline void CompleteInstruction();

    /* ----|----|---- */

    ALU alu;
    Memory* memory;

    int cycle_step = 0;

    std::array<void(*)(CPU&, int), 256> addressing_mode_array;
    std::array<void(*)(CPU&, int), 256> instruction_array;

    Instruction instruction;
    InstructionStep inst_step = InstructionStep::FETCH;

    uint16_t address_bus;
    uint8_t data_bus;

    uint8_t latch_register;

    bool irq_interrupt = false;
    bool nmi_interrupt = false; // Ignores I flag on status register

    RWline rw_line = RWline::READ;

    uint8_t accumulator;
    uint8_t x_index;
    uint8_t y_index;
    uint8_t status;

    uint16_t program_counter;
    uint8_t stack_pointer; // Address calculated by: 0x0100 + stack_pointer
};