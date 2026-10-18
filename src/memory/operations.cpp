#include <filesystem>
#include <fstream>
#include <memory>

#include <memory/enums.h>
#include <memory/memory.h>
#include <whereami.h>

void Memory::LoadFile(const std::string& file_name) {
    int length = wai_getExecutablePath(nullptr, 0, nullptr);

    std::unique_ptr<char[]> exe_path = std::make_unique<char[]>(length + 1);
    int dir_name_length;

    wai_getExecutablePath(exe_path.get(), length, &dir_name_length);

    exe_path[dir_name_length + 1] = '\0';

    std::string rom_path = exe_path.get();
    rom_path += "roms\\" + file_name;

    std::uintmax_t file_size = std::filesystem::file_size(rom_path);
    std::ifstream file(rom_path.c_str(), std::ios::binary);

    std::vector<char> buffer(file_size);
    file.read(buffer.data(), file_size);

    size_t cartridge_start = static_cast<size_t>(AddressStart::CARTRIDGE);
    size_t cartridge_end = static_cast<size_t>(AddressStart::CARTRIDGE);

    for (size_t i = cartridge_start; i <= cartridge_end; ++i) {
        size_t buffer_index = i - cartridge_start;
        memory[i] = buffer[buffer_index];
    }
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
    uint16_t effective_address;
    if (address >= AddressStart::INTERNAL_RAM && address <= AddressEnd::INTERNAL_RAM) {
        effective_address = address % static_cast<uint16_t>(MirrorModulo::INTERNAL_RAM);
    } else if (address >= AddressStart::PPU_REGISTERS && address <= AddressEnd::PPU_REGISTERS) {
        effective_address = address % static_cast<uint16_t>(MirrorModulo::PPU_REGISTERS);
    } else {
        effective_address = address;
    }

    memory[effective_address] = value;
}

uint8_t Memory::FetchInterruptVector(InterruptVector vec, InterruptVectorByte byte) {
    return memory[static_cast<size_t>(vec) + static_cast<size_t>(byte)];
}

uint8_t Memory::DirectAccess(uint16_t address) {
    return memory[address];
}
