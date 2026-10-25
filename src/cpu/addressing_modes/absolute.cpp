#include <cpu/addressing_modes.h>
#include <cpu/cpu.h>
#include <cpu/instructions.h>

void addressing_modes::Absolute(CPU& cpu, int step) {
    switch (step) {
        case 0: {
            cpu.address_bus = cpu.program_counter++;
            break;
        }
        case 1: {
            cpu.latch = cpu.data_bus;
            cpu.address_bus = cpu.program_counter++;
            break;
        }
        case 2: {
            cpu.address_bus = (cpu.data_bus << 8) | cpu.latch;
            cpu.CompleteAddressingMode();
            break;
        }
    }
}

void addressing_modes::AbsoluteX(CPU& cpu, int step) {
    switch (step) {
        case 0: {
            cpu.address_bus = cpu.program_counter++;
            break;
        }
        case 1: {
            cpu.latch = cpu.data_bus;
            cpu.alu.Add(cpu.data_bus, cpu.x_index);
            cpu.address_bus = cpu.program_counter++;
            break;
        }
        case 2: {
            cpu.address_bus = (cpu.data_bus << 8) | cpu.alu.result;
            bool is_store = cpu.inst_func == instructions::access::StoreAccumulator;
            if (!is_store && (cpu.alu.status & Flag::CARRY) == 0) {
                cpu.CompleteAddressingMode();
            }
            break;
        }
        case 3: {
            bool is_store = cpu.inst_func == instructions::access::StoreAccumulator;
            if (!is_store) {
                cpu.inst_cycle_count++;
            }

            if ((cpu.alu.status & Flag::CARRY) != 0) {
                cpu.address_bus += 0x01 << 8;
            }

            cpu.CompleteAddressingMode();
            break;
        }
    }
}

void addressing_modes::AbsoluteY(CPU& cpu, int step) {
    switch (step) {
        case 0: {
            cpu.address_bus = cpu.program_counter++;
            break;
        }
        case 1: {
            cpu.latch = cpu.data_bus;
            cpu.alu.Add(cpu.data_bus, cpu.y_index);
            cpu.address_bus = cpu.program_counter++;
            break;
        }
        case 2: {
            cpu.address_bus = (cpu.data_bus << 8) | cpu.alu.result;
            bool is_store = cpu.inst_func == instructions::access::StoreAccumulator;
            if (!is_store && (cpu.alu.status & Flag::CARRY) == 0) {
                cpu.CompleteAddressingMode();
            }
            break;
        }
        case 3: {
            bool is_store = cpu.inst_func == instructions::access::StoreAccumulator;
            if (!is_store) {
                cpu.inst_cycle_count++;
            }

            if ((cpu.alu.status & Flag::CARRY) != 0) {
                cpu.address_bus += 0x01 << 8;
            }

            cpu.CompleteAddressingMode();
            break;
        }
    }
}
