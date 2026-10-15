#include <cpu/alu.h>
#include <cpu/enums.h>

constexpr uint8_t ASL_CLEAR = ~(Flag::CARRY | Flag::ZERO | Flag::NEGATIVE);
constexpr uint8_t LSR_CLEAR = ~(Flag::CARRY | Flag::ZERO | Flag::NEGATIVE);

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

}
