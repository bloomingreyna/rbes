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

    uint8_t Read(uint16_t address);
    void Write(uint16_t address, uint8_t value);

    uint8_t FetchInterruptVector(InterruptVector vec, InterruptVectorByte byte);
    uint8_t DirectAccess(uint16_t address); // Doesn't count as a memory read. Not in my world. Don't fucking ask.
private:
    std::vector<char> memory = std::vector<char>(MEMORY_MAP_SIZE);
};
