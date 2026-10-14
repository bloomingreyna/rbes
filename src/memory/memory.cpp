#include <memory/memory.h>

uint8_t Memory::Read(uint16_t address) {
    return memory.get()[address];
}

void Memory::Write(uint16_t address, uint8_t value) {
    memory.get()[address] = value;
}
