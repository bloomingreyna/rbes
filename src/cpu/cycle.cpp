#include <cpu/cpu.h>
#include <memory/memory.h>

void CPU::Tick() {
    cycle_count++;

    switch (cycle_type) {
        case CycleType::INITIALIZE: {
            Initialize();
            break;
        }
        case CycleType::FETCH: {
            FetchInstruction();
            break;
        }
        case CycleType::CALCULATE_ADDRESS: {
            CalculateAddress();
            break;
        };
        case CycleType::EXECUTE: {
            ExecuteInstruction();
            break;
        }
    }

    bool branch_page_cross_poll = (
        inst_cycle_count == -1 &&
        cycle_count == 3 &&
        ((alu.status & Flag::OVERFLOW) != 0 || (alu.status & Flag::NEGATIVE) != 0)
    );
    if ((cycle_count == inst_cycle_count || branch_page_cross_poll) && !is_hardware_interrupt) {
        PollInterrupts();
    }

    if (cycle_type == CycleType::FETCH) {
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
