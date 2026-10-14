#include <cstdint>
#include <memory>

class Memory {
public:
    uint8_t Read(uint16_t address);
    uint8_t ReadStack(uint8_t stack_pointer);

    void Write(uint16_t address, uint8_t value);
    void WriteStack(uint8_t stack_pointer, uint8_t value);
private:
    std::unique_ptr<uint8_t> memory;
};
