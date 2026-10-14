#include <cpu/cpu.h>
#include <memory/memory.h>

void CPU::ExecutionLogic() {
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

    switch (rw_line) {
        case RWline::WRITE: {
            memory->Write(address_bus, data_bus);
            if (inst_step == InstructionStep::FETCH) {
                address_bus = program_counter;
            }
            break;
        }
        case RWline::READ: {
            if (inst_step == InstructionStep::FETCH) {
                address_bus = program_counter;
            }
            data_bus = memory->Read(address_bus);
            break;
        }
    }
}
