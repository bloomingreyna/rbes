#include <cstdint>
#include <string>
#include <vector>

constexpr uint16_t INTERNAL_RAM_SIZE = 0x0800; // Mirrored three times from $0800-$0FFF.
constexpr uint16_t PPU_SIZE = 0x0008; // Mirrored from $2008-$3FFF, repeating every 8 bytes.
constexpr uint16_t APU_IO_SIZE = 0x0018;
constexpr uint16_t APU_IO_DISABLED_FUNCTIONALITY_SIZE = 0x0008;
constexpr uint16_t CARTRIDGE_SIZE = 0xBFE0;

class Memory {
public:
    Memory();

    void LoadFile(const std::string& file_name);

    uint8_t Read(uint16_t address);
    void Write(uint16_t address, uint8_t value);
private:
    std::vector<uint8_t> memory; // TODO: Placeholder to prevent build errors. Remove when ready.

    std::vector<uint8_t> internal_ram;
    std::vector<uint8_t> ppu_registers;
    std::vector<uint8_t> apu_io_registers;
    std::vector<uint8_t> apu_io_disabled_functionality;
    std::vector<uint8_t> cartridge;
};
