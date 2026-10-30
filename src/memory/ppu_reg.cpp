#include <memory/memory.h>

uint8_t Memory::PPURegisterRead(PPUregister reg) {
    return cpu_bus[static_cast<size_t>(reg)];
}

void Memory::PPURegisterWrite(PPUregister reg, uint8_t value) {
    cpu_bus[static_cast<size_t>(reg)] = value;
}

void Memory::CPU_PPURegisterReadHandler(uint16_t address) {

}

void Memory::CPU_PPURegisterWriteHandler(uint16_t address, uint8_t value) {
    switch (static_cast<PPUregister>(address)) {
        case PPUregister::PPUCTRL: {
            ppu_bus[static_cast<size_t>(PPUregister::PPUCTRL)] = value;
            break;
        }
        default: { break; }
    }
}
