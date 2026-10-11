#include <cpu/cpu.h>
#include <memory/memory.h>

inline void CPU::PhaseOne() {
    address_bus = target_address;
    if (rw_line == RWline::WRITE) {
        data_bus = data_queue;
    }
}

inline void CPU::PhaseTwo() {
    if (fetching) {
        FetchInstruction();
    } else {
        ExecuteInstruction();
    }

    switch (rw_line) {
        case RWline::WRITE: {
            memory->Write(address_bus, data_bus);
        }
        case RWline::READ: {
            data_bus = memory->Read(address_bus);
        }
    }
}
