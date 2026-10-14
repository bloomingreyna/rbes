#pragma once

#include <cstdint>

struct ALU {
    // Arithmetic
    void AddWithCarry(uint8_t lhs, uint8_t rhs, bool carry) {}
    void Increment(uint8_t operand) {}
    void Decrement(uint8_t operand) {}

    // Bitwise
    void AND(uint8_t lhs, uint8_t rhs) {}
    void OR(uint8_t lhs, uint8_t rhs) {}
    void XOR(uint8_t lhs, uint8_t rhs) {}
    void BIT(uint8_t lhs, uint8_t rhs) {}

    // Compare (obviously)
    void Compare(uint8_t lhs, uint8_t rhs) {}

    // Shift
    void ArithmeticShiftLeft(uint8_t operand) {}
    void LogicalShiftRight(uint8_t operand) {}
    void RotateLeft(uint8_t operand) {}
    void RotateRight(uint8_t operand) {}

    uint8_t result;
    uint8_t status;
    uint8_t clear_mask;
};
