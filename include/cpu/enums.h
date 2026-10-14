#pragma once

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
