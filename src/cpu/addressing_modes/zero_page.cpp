#include <cpu/addressing_modes.h>
#include <cpu/cpu.h>

inline void addressing_modes::ZeroPage(CPU& cpu, int step) {
    cpu.address_bus = cpu.data_bus;
    cpu.program_counter++;

    cpu.CompleteAddressingMode();
}

inline void addressing_modes::ZeroPageX(CPU& cpu, int step) {
    switch (step) {
        case 0: {
            cpu.address_bus = cpu.data_bus;
            cpu.program_counter++;
            break;
        }
        case 1: {
            cpu.address_bus += cpu.x_index;
            cpu.address_bus &= 0xFF;

            cpu.CompleteAddressingMode();
            break;
        }
    }
}

inline void addressing_modes::ZeroPageY(CPU& cpu, int step) {
    switch (step) {
        case 0: {
            cpu.address_bus = cpu.data_bus;
            cpu.program_counter++;
            break;
        }
        case 1: {
            cpu.address_bus += cpu.y_index;
            cpu.address_bus &= 0xFF;

            cpu.CompleteAddressingMode();
            break;
        }
    }
}