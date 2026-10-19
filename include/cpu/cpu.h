#pragma once

#include <array>
#include <cstdint>
#include <vector>

#include <cpu/alu.h>
#include <cpu/enums.h>

class Memory;

class CPU {
public:
    CPU(Memory* mem);

    void Initialize();

    void InitializeAddressingModes();
    void InitializeInstructions();

    void ExecutionLogic();

    void FetchInstruction();
    void CalculateAddress();
    void ExecuteInstruction();

    void HardwareInterrupt();

    void CompleteAddressingMode();
    void PollInterrupts();
    void CompleteInstruction();

    /* ----|----|---- */

    ALU alu;
    Memory* memory;

    int cycle_step = 0;

    std::array<void(*)(CPU&, int), 256> addressing_mode_array;
    std::array<void(*)(CPU&, int), 256> instruction_array;

    Instruction instruction;
    InstructionStep inst_step = InstructionStep::INITIALIZE;

    uint16_t address_bus;
    uint8_t data_bus;

    uint8_t latch_register;
    uint8_t second_latch;
    uint16_t pc_latch;
    bool pc_jump = false;

    bool interrupt_delay_signal = false; // Allows for flag and pull instructions to delay flag effect.
    bool interrupt_delay_value; // Determines value of allow_irq when interrupt_delay_signal is true.

    bool allow_irq = false;
    bool irq_interrupt = false;
    bool nmi_interrupt = false; // Ignores I flag on status register
    bool hardware_interrupt = false; // Determines behaviors in BRK instruction
    bool interrupt_poll = false;

    RWline rw_line = RWline::READ;

    uint8_t accumulator, x_index, y_index = 0x00;
    uint8_t status = static_cast<uint8_t>(Flag::INTERRUPT_DISABLE);

    uint16_t program_counter = 0xFFFC;
    uint8_t stack_pointer = 0xFD; // Address calculated by: 0x0100 + stack_pointer
};
