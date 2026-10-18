#include <cpu/addressing_modes.h>
#include <cpu/cpu.h>
#include <cpu/instructions.h>

void addressing_modes::Absolute(CPU& cpu, int step) {
    switch (step) {
        case 0: {
            cpu.latch_register = cpu.data_bus;
            cpu.address_bus = ++cpu.program_counter;
            break;
        }
        case 1: {
            cpu.address_bus = (cpu.data_bus << 8) | cpu.latch_register;
            cpu.program_counter++;

            cpu.CompleteAddressingMode();
            if (cpu.instruction == Instruction::JMP_ABS) {
                cpu.ExecuteInstruction();
            }
            break;
        }
    }
}

void addressing_modes::AbsoluteX(CPU& cpu, int step) {
    switch (step) {
        case 0: {
            cpu.latch_register = cpu.data_bus;
            cpu.address_bus = ++cpu.program_counter;
            break;
        }
        case 1: {
            cpu.alu.AddWithCarry(cpu.latch_register, cpu.x_index, false);
            cpu.address_bus = (cpu.data_bus << 8) | cpu.alu.result;
            cpu.program_counter++;

            auto inst_func = cpu.instruction_array[static_cast<size_t>(cpu.instruction)];
            if (inst_func == instructions::access::StoreAccumulator || (cpu.alu.status & Flag::CARRY) == 0) {
                cpu.CompleteAddressingMode();
            }
            break;
        }
        case 2: {
            if ((cpu.alu.status & Flag::CARRY) == 0) {
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
            cpu.latch_register = cpu.data_bus;
            cpu.address_bus = ++cpu.program_counter;
            break;
        }
        case 1: {
            cpu.alu.AddWithCarry(cpu.latch_register, cpu.y_index, false);
            cpu.address_bus = (cpu.data_bus << 8) | cpu.alu.result;
            cpu.program_counter++;

            auto inst_func = cpu.instruction_array[static_cast<size_t>(cpu.instruction)];
            if (inst_func == instructions::access::StoreAccumulator || (cpu.alu.status & Flag::CARRY) == 0) {
                cpu.CompleteAddressingMode();
            }
            break;
        }
        case 2: {
            if ((cpu.alu.status & Flag::CARRY) != 0) {
                cpu.address_bus += 0x01 << 8;
            }

            cpu.CompleteAddressingMode();
            break;
        }
    }
}
