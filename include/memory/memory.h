#include <cstdint>
#include <string>
#include <vector>

constexpr size_t MEMORY_MAP_SIZE = 0x10000; // 64 KB

class Memory {
public:
    Memory();

    void LoadFile(const std::string& file_name);

    uint8_t Read(uint16_t address);
    void Write(uint16_t address, uint8_t value);
private:
    std::vector<char> memory = std::vector<char>(MEMORY_MAP_SIZE);
};
