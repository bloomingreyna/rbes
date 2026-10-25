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
    void InitializeCycleCounts();

    void Tick();

    void FetchInstruction();
    void CalculateAddress();
    void ExecuteInstruction();

    void CheckInterruptInputs();
    void PollInterrupts();

    void CompleteAddressingMode();
    void CompleteInstruction();

    /* ----|----|---- */

    ALU alu;
    Memory* memory;

    int cycle_step = 0;
    int cycle_count = 0;

    std::array<void(*)(CPU&, int), 256> addressing_mode_array;
    std::array<void(*)(CPU&, int), 256> instruction_array;
    std::array<int, 256> cycle_count_array;

    void(*addr_func)(CPU&, int);
    void(*inst_func)(CPU&, int);
    int inst_cycle_count;

    Instruction instruction;
    InstructionStep inst_step = InstructionStep::INITIALIZE;

    uint16_t address_bus;
    uint8_t data_bus;

    uint8_t latch;

    bool irq_input = false;
    bool nmi_input = false; // Ignores I flag on status register
    bool nmi_last_state = false; // NMI interrupts are edge-sensitive

    bool irq_signal = false;
    bool nmi_signal = false;

    bool service_interrupt = false;
    bool is_hardware_interrupt = false;

    RWline rw_line = RWline::READ;

    uint8_t accumulator, x_index, y_index = 0x00;
    uint8_t status = static_cast<uint8_t>(Flag::INTERRUPT_DISABLE);

    uint16_t program_counter = 0xFFFC;
    uint8_t stack_pointer = 0xFD; // Address calculated by: 0x0100 + stack_pointer
};
