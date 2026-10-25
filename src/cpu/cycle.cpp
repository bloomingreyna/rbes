#include <cpu/cpu.h>
#include <memory/memory.h>

void CPU::Tick() {
    cycle_count++;

    switch (inst_step) {
        case InstructionStep::INITIALIZE: {
            Initialize();
            break;
        }
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

    if (inst_cycle_count != -1) {
        if (cycle_count == inst_cycle_count) {
            PollInterrupts();
        }
    } else {
        switch (cycle_count) {
            case 1: {
                PollInterrupts();
                break;
            }
            case 3: {
                if (inst_step != InstructionStep::FETCH) {
                    PollInterrupts();
                }
                break;
            }
        }
    }

    if (inst_step == InstructionStep::FETCH) {
        cycle_count = 0;
    }

    switch (rw_line) {
        case RWline::WRITE: {
            memory->Write(address_bus, data_bus);
            break;
        }
        case RWline::READ: {
            if (inst_step != InstructionStep::FETCH) {
                data_bus = memory->Read(address_bus);
            } else {
                address_bus = program_counter;
                data_bus = memory->Read(address_bus);

                // Fetch cycle overlaps with final cycle of previous instruction
                FetchInstruction();
                cycle_count++;
            }
            break;
        }
    }

    irq_signal = false;
    CheckInterruptInputs();
}
