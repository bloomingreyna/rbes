#include <cpu/alu.h>
#include <cpu/enums.h>

constexpr uint8_t ASL_CLEAR = ~(Flag::CARRY | Flag::ZERO | Flag::NEGATIVE);
constexpr uint8_t LSR_CLEAR = ~(Flag::CARRY | Flag::ZERO | Flag::NEGATIVE);
constexpr uint8_t ROL_CLEAR = ~(Flag::CARRY | Flag::ZERO | Flag::NEGATIVE);
constexpr uint8_t ROR_CLEAR = ~(Flag::CARRY | Flag::ZERO | Flag::NEGATIVE);

void ALU::ArithmeticShiftLeft(uint8_t operand) {
    result = operand << 1;

    status = 0x00;
    clear_mask = ASL_CLEAR;
    if ((operand & 0x80) != 0) {
        status |= Flag::CARRY;
    }
    if (result == 0) {
        status |= Flag::ZERO;
    }
    if ((result & 0x80) != 0) {
        status |= Flag::NEGATIVE;
    }
}

void ALU::LogicalShiftRight(uint8_t operand) {
    result = operand >> 1;

    status = 0x00;
    clear_mask = LSR_CLEAR; // Negative flag stays cleared
    if ((operand & 0x01) != 0) {
        status |= Flag::CARRY;
    }
    if (result == 0) {
        status |= Flag::ZERO;
    }
}

void ALU::RotateLeft(uint8_t operand, bool carry) {
    result = operand << 1;
    if (carry) {
        result |= 0x01;
    }

    status = 0x00;
    clear_mask = ROL_CLEAR;
    if ((operand & 0x80) != 0) {
        status |= Flag::CARRY;
    }
    if (result == 0) {
        status |= Flag::ZERO;
    }
    if ((result & 0x80) != 0) {
        status |= Flag::NEGATIVE;
    }
}

void ALU::RotateRight(uint8_t operand, bool carry) {
    result = operand >> 1;
    if (carry) {
        result |= 0x80;
    }

    status = 0x00;
    clear_mask = ROL_CLEAR;
    if ((operand & 0x01) != 0) {
        status |= Flag::CARRY;
    }
    if (result == 0) {
        status |= Flag::ZERO;
    }
    if ((result & 0x80) != 0) {
        status |= Flag::NEGATIVE;
    }
}
