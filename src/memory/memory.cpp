#include <memory/memory.h>

inline uint8_t Memory::Read(uint16_t address) {
    return memory.get()[address];
}

inline uint8_t Memory::ReadStack(uint8_t stack_pointer) {
    return memory.get()[0x0100 + stack_pointer];
}

inline void Memory::Write(uint16_t address, uint8_t value) {
    memory.get()[address] = value;
}

inline void Memory::WriteStack(uint8_t stack_pointer, uint8_t value) {
    memory.get()[0x0100 + stack_pointer] = value;
}