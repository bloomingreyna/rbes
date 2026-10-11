#include <cstdint>
#include <memory>

class Memory {
public:
    inline uint8_t Read(uint16_t address);
    inline uint8_t ReadStack(uint8_t stack_pointer);

    inline void Write(uint16_t address, uint8_t value);
    inline void WriteStack(uint8_t stack_pointer, uint8_t value);
private:
    std::unique_ptr<uint8_t> memory;
};