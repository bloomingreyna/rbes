#include <cpu/alu.h>
#include <cpu/enums.h>

constexpr uint8_t AND_CLEAR = ~(Flag::ZERO | Flag::NEGATIVE);
constexpr uint8_t OR_CLEAR = ~(Flag::ZERO | Flag::NEGATIVE);
constexpr uint8_t XOR_CLEAR = ~(Flag::ZERO | Flag::NEGATIVE);
constexpr uint8_t BIT_CLEAR = ~(Flag::CARRY | Flag::OVERFLOW | Flag::NEGATIVE);

void ALU::AND(uint8_t lhs, uint8_t rhs) {
    result = lhs & rhs;

    status = 0x00;
    clear_mask = AND_CLEAR;
    if (result == 0) {
        status |= Flag::ZERO;
    }
    if ((result & 0x80) != 0) {
        status |= Flag::NEGATIVE;
    }
}

void ALU::OR(uint8_t lhs, uint8_t rhs) {
    result = lhs | rhs;

    status = 0x00;
    clear_mask = OR_CLEAR;
    if (result == 0) {
        status |= Flag::ZERO;
    }
    if ((result & 0x80) != 0) {
        status |= Flag::NEGATIVE;
    }
}

void ALU::XOR(uint8_t lhs, uint8_t rhs) {
    result = lhs ^ rhs;

    status = 0x00;
    clear_mask = XOR_CLEAR;
    if (result == 0) {
        status |= Flag::ZERO;
    }
    if ((result & 0x80) != 0) {
        status |= Flag::NEGATIVE;
    }
}

void ALU::BIT(uint8_t lhs, uint8_t rhs) {
    result = lhs & rhs;

    status = 0x00;
    clear_mask = BIT_CLEAR;
    if (result == 0) {
        status |= Flag::ZERO;
    }
    if ((result & 0x40) != 0) {
        status |= Flag::OVERFLOW;
    }
    if ((result & 0x80) != 0) {
        status |= Flag::NEGATIVE;
    }
}
