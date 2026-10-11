#include <cpu/cpu.h>
#include <memory/memory.h>

inline void CPU::ExecutionLogic() {
    if (rw_line == RWline::WRITE) {
        data_bus = data_queue;
    }

    switch (rw_line) {
        case RWline::WRITE: {
            memory->Write(address_bus, data_bus);
        }
        case RWline::READ: {
            data_bus = memory->Read(address_bus);
        }
    }

    switch (inst_step) {
        case InstructionStep::FETCH: {
            FetchInstruction();
            break;
        }
        case InstructionStep::CALCULATE_ADDRESS: {
            CalculateAddress();
            break;
        };
        case InstructionStep::EXECUTE: {
            ExecuteInstruction();
            break;
        }
    }

    latch_register = data_bus;
}
