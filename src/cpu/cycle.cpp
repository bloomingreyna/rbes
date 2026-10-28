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

    bool branch_page_cross_poll = (
        inst_cycle_count == -1 &&
        cycle_count == 3 &&
        ((alu.status & Flag::OVERFLOW) != 0 || (alu.status & Flag::NEGATIVE) != 0)
    );
    if (cycle_count == inst_cycle_count || branch_page_cross_poll) {
        PollInterrupts();
    }

    if (inst_step == InstructionStep::FETCH) {
        cycle_count = 0;
    }

    switch (rw_line) {
        case RWline::WRITE: {
            memory->CPUWrite(address_bus, data_bus);
            break;
        }
        case RWline::READ: {
            if (cycle_count > 1) {
                data_bus = memory->CPURead(address_bus);
            } else if (cycle_count == 0) {
                FetchInstruction();
                cycle_count++;
            }
            break;
        }
    }

    irq_signal = false;
    CheckInterruptInputs();
}
