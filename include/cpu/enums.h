#pragma once

#include <cstdint>

enum class Flag : uint8_t {
    CARRY = 0x01,
    ZERO = 0x02,
    INTERRUPT_DISABLE = 0x04,
    DECIMAL = 0x08,
    BREAK = 0x10,
    OVERFLOW = 0x40,
    NEGATIVE = 0x80
};

enum class Instruction {
    ADC_IMM = 0x69,
    ADC_ZP = 0x65, ADC_ZP_X = 0x75,
    ADC_ABS = 0x6D, ADC_ABS_X = 0x7D, ADC_ABS_Y = 0x79,
    ADC_IND_X = 0x61, ADC_IND_Y = 0x71,

    AND_IMM = 0x29,
    AND_ZP = 0x25, AND_ZP_X = 0x35,
    AND_ABS = 0x2D, AND_ABS_X = 0x3D, AND_ABS_Y = 0x39,
    AND_IND_X = 0x21, AND_IND_Y = 0x31,

    ASL_ACC = 0x0A,
    ASL_ZP = 0x06, ASL_ZP_X = 0x16,
    ASL_ABS = 0x0E, ASL_ABS_X = 0x1E,

    BCC = 0x90, BCS = 0xB0,
    BEQ = 0xF0, BNE = 0xD0,
    BMI = 0x30, BPL = 0x10,
    BVC = 0x50, BVS = 0x70,

    // ...

    LSR_ACC = 0x4A
};

enum class InstructionStep {
    FETCH, CALCULATE_ADDRESS, EXECUTE
};

/* On a real 6502, the R/W line is pulled high for a read, and low for a write.
   Voltage levels don't matter for emulation, but hey, trivia :P */
enum class RWline {
    WRITE = 0, READ = 1
};

/* Flag overloads */
constexpr uint8_t operator&(uint8_t lhs, Flag rhs) {
    return lhs & static_cast<uint8_t>(rhs);
}
constexpr uint8_t operator|(uint8_t lhs, Flag rhs) {
    return lhs | static_cast<uint8_t>(rhs);
}
constexpr uint8_t operator|(Flag lhs, Flag rhs) {
    return static_cast<uint8_t>(lhs) | static_cast<uint8_t>(rhs);
}
constexpr uint8_t& operator|=(uint8_t& lhs, Flag rhs) {
    lhs |= static_cast<uint8_t>(rhs);
    return lhs;
}
