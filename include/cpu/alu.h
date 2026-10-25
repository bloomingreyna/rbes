#pragma once

#include <cstdint>

struct ALU {
    // SBC is implemented by bitwise NOT'ing the memory operand and calling ADC.
    void AddWithCarry(uint8_t lhs, uint8_t rhs, bool carry);
    void Increment(uint8_t operand);
    void Decrement(uint8_t operand);

    void AND(uint8_t lhs, uint8_t rhs);
    void OR(uint8_t lhs, uint8_t rhs);
    void XOR(uint8_t lhs, uint8_t rhs);
    void BIT(uint8_t lhs, uint8_t rhs);

    void Compare(uint8_t lhs, uint8_t rhs);

    void ArithmeticShiftLeft(uint8_t operand);
    void LogicalShiftRight(uint8_t operand);
    void RotateLeft(uint8_t operand, bool carry);
    void RotateRight(uint8_t operand, bool carry);

    // Helper function; not a core part of any instructions.
    void Add(uint8_t lhs, uint8_t rhs);

    uint8_t result;
    uint8_t status;
    uint8_t clear_mask;
};
