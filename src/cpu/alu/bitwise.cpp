#include <cpu/alu.h>
#include <cpu/enums.h>

void ALU::AND(uint8_t lhs, uint8_t rhs) {
    result = lhs & rhs;

    status = 0x00;
    clear_mask = 0x7D;
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
    clear_mask = 0x7D;
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
    clear_mask = 0x7D;
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
    clear_mask = 0x3D;
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
