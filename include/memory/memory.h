#include <cstdint>
#include <string>
#include <vector>

constexpr uint16_t INTERNAL_RAM_START = 0x0000;
constexpr uint16_t INTERNAL_RAM_END = 0x1FFF;

constexpr uint16_t PPU_START = 0x2000;
constexpr uint16_t PPU_END = 0x3FFF;

constexpr uint16_t APU_IO_START = 0x4000;
constexpr uint16_t APU_IO_END = 0x4017;

class Memory {
public:
    Memory();

    void LoadFile(const std::string& file_name);

    uint8_t Read(uint16_t address);
    void Write(uint16_t address, uint8_t value);
private:
    std::vector<uint8_t> memory;
};
