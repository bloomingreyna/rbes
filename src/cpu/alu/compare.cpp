#include <cpu/alu.h>
#include <cpu/enums.h>

constexpr uint8_t CMP_CLEAR = ~(Flag::CARRY | Flag::ZERO | Flag::NEGATIVE);

void ALU::Compare(uint8_t lhs, uint8_t rhs) {
    result = lhs - rhs;

    status = 0x00;
    clear_mask = CMP_CLEAR;
    if (lhs >= rhs) {
        status |= Flag::CARRY;
    }
    if (lhs == rhs) {
        status |= Flag::ZERO;
    }
    if ((result & 0x80) != 0) {
        status |= Flag::NEGATIVE;
    }
}
