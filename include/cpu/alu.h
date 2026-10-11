#include <cstdint>

struct ALU {
    inline void AddWithCarry(uint8_t lhs, uint8_t rhs, bool carry);

    uint8_t result;
    uint8_t status;
    uint8_t clear_mask;
};