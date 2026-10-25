#include <cpu/alu.h>
#include <cpu/enums.h>

void ALU::Add(uint8_t lhs, uint8_t rhs) {
    uint16_t add_result = lhs + rhs;
    result = add_result & 0xFF;

    status = 0x00;

    // Unsigned overflow
    if (add_result > 0xFF) {
        status |= Flag::CARRY;
    }

    // Signed over/underflow checks (U8 + S8)
    if ((rhs & 0x80) == 0 && result < lhs) {
        status |= Flag::OVERFLOW;
    } else if ((rhs & 0x80) != 0 && result > lhs) {
        status |= Flag::NEGATIVE;
    }
}
