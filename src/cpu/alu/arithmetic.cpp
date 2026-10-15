#include <cpu/alu.h>
#include <cpu/enums.h>

constexpr uint8_t ADC_CLEAR = ~(Flag::CARRY | Flag::ZERO | Flag::OVERFLOW | Flag::NEGATIVE);
constexpr uint8_t INC_CLEAR = ~(Flag::ZERO | Flag::NEGATIVE);
constexpr uint8_t DEC_CLEAR = ~(Flag::ZERO | Flag::NEGATIVE);

void ALU::AddWithCarry(uint8_t lhs, uint8_t rhs, bool carry) {
    uint16_t add_result = lhs + rhs + carry;
    result = add_result & 0xFF;

    status = 0x00;
    clear_mask = ADC_CLEAR;
    if (add_result > 0xFF) {
        status |= Flag::CARRY;
    }
    if ((add_result & 0xFF) == 0) {
        status |= Flag::ZERO;
    }
    if (((add_result ^ lhs) & (add_result ^ lhs) & 0x80) != 0) {
        status |= Flag::OVERFLOW;
    }
    if ((add_result & 0x80) != 0) {
        status |= Flag::NEGATIVE;
    }
}

void ALU::Increment(uint8_t operand) {
    result = operand + 1;

    status = 0x00;
    clear_mask = INC_CLEAR;
    if (result == 0) {
        status |= Flag::ZERO;
    }
    if ((result & 0x80) != 0) {
        status |= Flag::NEGATIVE;
    }
}

void ALU::Decrement(uint8_t operand) {
    result = operand - 1;

    status = 0x00;
    clear_mask = INC_CLEAR;
    if (result == 0) {
        status |= Flag::ZERO;
    }
    if ((result & 0x80) != 0) {
        status |= Flag::NEGATIVE;
    }
}

