#include <filesystem>
#include <fstream>
#include <iostream>
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

    for (size_t i = 0x8000; i < 0x8000 + 1024 * 32; ++i) {
        size_t buffer_index = i - 0x8000 + 16;
        cpu_bus[i] = buffer[buffer_index];
    }
}
