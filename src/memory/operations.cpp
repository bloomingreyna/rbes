#include <memory/enums.h>
#include <memory/memory.h>

void Memory::LoadFile(const std::string& file_name) {
    // ...
}

uint8_t Memory::Read(uint16_t address) {
    uint16_t effective_address;
    if (address >= AddressStart::INTERNAL_RAM && address <= AddressEnd::INTERNAL_RAM) {
        effective_address = address % static_cast<uint16_t>(MirrorModulo::INTERNAL_RAM);
    } else if (address >= AddressStart::PPU_REGISTERS && address <= AddressEnd::PPU_REGISTERS) {
        effective_address = address % static_cast<uint16_t>(MirrorModulo::PPU_REGISTERS);
    } else {
        effective_address = address;
    }

    return memory[effective_address];
}

void Memory::Write(uint16_t address, uint8_t value) {
    memory[address] = value;
}
