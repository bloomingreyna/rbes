#include <memory/enums.h>
#include <memory/memory.h>

uint8_t Memory::CPURead(uint16_t address) {
    uint16_t effective_address;
    if (address >= AddressStart::INTERNAL_RAM && address <= AddressEnd::INTERNAL_RAM) {
        effective_address = address % static_cast<uint16_t>(MirrorModulo::INTERNAL_RAM);
    } else if (address >= AddressStart::PPU_REGISTERS && address <= AddressEnd::PPU_REGISTERS) {
        effective_address = address % static_cast<uint16_t>(MirrorModulo::PPU_REGISTERS);
        CPU_PPURegisterReadHandler(effective_address);
        return 0; // TODO: Handle read and open bus behavior
    } else {
        effective_address = address;
    }

    return cpu_bus[effective_address];
}

void Memory::CPUWrite(uint16_t address, uint8_t value) {
    uint16_t effective_address;
    if (address >= AddressStart::INTERNAL_RAM && address <= AddressEnd::INTERNAL_RAM) {
        effective_address = address % static_cast<uint16_t>(MirrorModulo::INTERNAL_RAM);
    } else if (address >= AddressStart::PPU_REGISTERS && address <= AddressEnd::PPU_REGISTERS) {
        effective_address = address % static_cast<uint16_t>(MirrorModulo::PPU_REGISTERS);
        CPU_PPURegisterWriteHandler(effective_address, value);
        return;
    } else {
        effective_address = address;
    }

    cpu_bus[effective_address] = value;
}
