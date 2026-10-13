#include <cstdint>

struct ALU {
    inline void AddWithCarry(uint8_t lhs, uint8_t rhs, bool carry);
    inline void Increment(uint8_t operand);
    inline void Decrement(uint8_t operand);
    inline void AND(uint8_t lhs, uint8_t rhs);
    inline void OR(uint8_t lhs, uint8_t rhs);
    inline void XOR(uint8_t lhs, uint8_t rhs);
    inline void BIT(uint8_t lhs, uint8_t rhs);
    inline void Compare(uint8_t lhs, uint8_t rhs);

    uint8_t result;
    uint8_t status;
    uint8_t clear_mask;
};
