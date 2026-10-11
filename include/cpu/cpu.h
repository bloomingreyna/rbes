#include <cstdint>

#include <cpu/enums.h>

class Memory;

class CPU {
public:
    inline void PhaseOne();
    inline void PhaseTwo();

    inline void FetchInstruction();
    inline void ExecuteInstruction();
    inline void CompleteInstruction();
private:
    Memory* memory;

    int cycle_step = 0;

    Instruction instruction;
    bool fetching = true;

    uint16_t address_bus;
    uint8_t data_bus;

    // Instructions modify these values to modify address/data buses for next cycle
    uint16_t target_address;
    uint8_t data_queue;

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