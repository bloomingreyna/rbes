#include <cpu/addressing_modes.h>
#include <cpu/cpu.h>
#include <cpu/instructions.h>

void addressing_modes::Indirect(CPU& cpu, int step) {
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
            break;
        }
        case 3: {
            cpu.latch = cpu.data_bus;

            // There is a bug in the original CPU that does not allow the pointer increment to properly cross pages. The below code implements this bug.
            uint8_t ptr_low = cpu.address_bus & 0xFF;
            ptr_low++;
            cpu.address_bus &= 0xFF00;
            cpu.address_bus |= ptr_low;

            break;
        }
        case 4: {
            cpu.address_bus = (cpu.data_bus << 8) | cpu.latch;
            cpu.CompleteAddressingMode();
            break;
        }
    }
}

void addressing_modes::IndirectX(CPU& cpu, int step) {
    switch (step) {
        case 0: {
            cpu.address_bus = cpu.program_counter++;
            break;
        }
        case 1: {
            cpu.address_bus = cpu.data_bus;
            break;
        }
        case 2: {
            cpu.address_bus += cpu.x_index;
            cpu.address_bus &= 0xFF;
            break;
        }
        case 3: {
            cpu.latch = cpu.data_bus;
            cpu.address_bus++;
            cpu.address_bus &= 0xFF;
            break;
        }
        case 4: {
            cpu.address_bus = (cpu.data_bus << 8) | cpu.latch;
            cpu.CompleteAddressingMode();
            break;
        }
    }
}

void addressing_modes::IndirectY(CPU& cpu, int step) {
    switch (step) {
        case 0: {
            cpu.address_bus = cpu.program_counter++;
            break;
        }
        case 1: {
            cpu.address_bus = cpu.data_bus;
            break;
        }
        case 2: {
            cpu.latch = cpu.data_bus;
            cpu.address_bus++;
            cpu.address_bus &= 0xFF;
            break;
        }
        case 3: {
            cpu.alu.Add(cpu.latch, cpu.y_index);
            cpu.address_bus = (cpu.data_bus << 8) | cpu.alu.result;

            bool is_store = cpu.inst_func == instructions::access::StoreAccumulator;
            if (!is_store && (cpu.alu.status & Flag::CARRY) == 0) {
                cpu.CompleteAddressingMode();
            }
            break;
        }
        case 4: {
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
