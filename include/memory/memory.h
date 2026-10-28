#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include <memory/enums.h>

constexpr size_t MEMORY_MAP_SIZE = 0x10000; // 64 KB

class Memory {
public:
    Memory();

    void LoadFile(const std::string& file_name);

    uint8_t CPURead(uint16_t address);
    void CPUWrite(uint16_t address, uint8_t value);
private:
    std::vector<char> cpu_bus = std::vector<char>(MEMORY_MAP_SIZE);
    std::vector<char> ppu_bus = std::vector<char>();
};
