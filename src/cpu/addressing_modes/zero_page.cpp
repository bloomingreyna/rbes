#include <cpu/addressing_modes.h>
#include <cpu/cpu.h>

void addressing_modes::ZeroPage(CPU& cpu, int step) {
    switch (step) {
        case 0: {
            cpu.address_bus = cpu.program_counter++;
            break;
        }
        case 1: {
            cpu.address_bus = cpu.data_bus;
            cpu.CompleteAddressingMode();
            break;
        }
    }
}

void addressing_modes::ZeroPageX(CPU& cpu, int step) {
    switch (step) {
        case 0: {
            cpu.address_bus = cpu.program_counter++;
            break;
        }
        case 1: {
            cpu.address_bus = cpu.data_bus;
            cpu.alu.Add(cpu.data_bus, cpu.x_index);
            break;
        }
        case 2: {
            cpu.address_bus = cpu.alu.result;
            cpu.CompleteAddressingMode();
            break;
        }
    }
}

void addressing_modes::ZeroPageY(CPU& cpu, int step) {
    switch (step) {
        case 0: {
            cpu.address_bus = cpu.program_counter++;
            break;
        }
        case 1: {
            cpu.address_bus = cpu.data_bus;
            cpu.alu.Add(cpu.data_bus, cpu.y_index);
            break;
        }
        case 2: {
            cpu.address_bus = cpu.alu.result;
            cpu.CompleteAddressingMode();
            break;
        }
    }

}
