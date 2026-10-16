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

    BIT_ZP = 0x24,
    BIT_ABS = 0x2C,

    BRK = 0x00,

    CLC = 0x18, SEC = 0x38,
    CLD = 0xD8, SED = 0xF8,
    CLI = 0x58, SEI = 0x78,
    CLV = 0xB8,

    CMP_IMM = 0xC9,
    CMP_ZP = 0xC5, CMP_ZP_X = 0xD5,
    CMP_ABS = 0xCD, CMP_ABS_X = 0xDD, CMP_ABS_Y = 0xD9,
    CMP_IND_X = 0xC1, CMP_IND_Y = 0xD1,

    CPX_IMM = 0xE0, CPY_IMM = 0xC0,
    CPX_ZP = 0xE4, CPY_ZP = 0xC4,
    CPX_ABS = 0xEC, CPY_ABS = 0xCC,

    DEC_ZP = 0xC6, DEC_ZP_X = 0xD6,
    DEC_ABS = 0xCE, DEC_ABS_X = 0xDE,

    DEX = 0xCA, DEY = 0x88,

    INC_ZP = 0xE6, INC_ZP_X = 0xF6,
    INC_ABS = 0xEE, INC_ABS_X = 0xFE,

    INX = 0xE8, INY = 0xC8,

    JMP_ABS = 0x4C,
    JMP_IND = 0x6C,

    JSR_ABS = 0x20,

    LDA_IMM = 0xA9,
    LDA_ZP = 0xA5, LDA_ZP_X = 0xB5,
    LDA_ABS = 0xAD, LDA_ABS_X = 0xBD, LDA_ABS_Y = 0xB9,
    LDA_IND_X = 0xA1, LDA_IND_Y = 0xB1,

    LDX = 0xA2,
    LDX_ZP = 0xA6, LDX_ZP_Y = 0xB6,
    LDX_ABS = 0xAE, LDX_ABS_Y = 0xBE,

    LDY_IMM = 0xA2,
    LDY_ZP = 0xA6, LDY_ZP_X = 0xB6,
    LDY_ABS = 0xAE, LDY_ABS_X = 0xBE,

    LSR_ACC = 0x4A,
    LSR_ZP = 0x46, LSR_ZP_X = 0x56,
    LSR_ABS = 0x4E, LSR_ABS_X = 0x5E,

    NOP = 0xEA,

    ORA_IMM = 0x09,
    ORA_ZP = 0x05, ORA_ZP_X = 0x15,
    ORA_ABS = 0x0D, ORA_ABS_X = 0x1D, ORA_ABS_Y = 0x19,
    ORA_IND_X = 0x01, ORA_IND_Y = 0x11,

    PHA = 0x48, PHP = 0x08,
    PLA = 0x68, PLP = 0x28,

    ROL_ACC = 0x2A,
    ROL_ZP = 0x26, ROL_ZP_X = 0x36,
    ROL_ABS = 0x2E, ROL_ABS_X = 0x3E,

    ROR_ACC = 0x6A,
    ROR_ZP = 0x66, ROR_ZP_X = 0x76,
    ROR_ABS = 0x6E, ROR_ABS_X = 0x7E,

    RTI = 0x40, RTS = 0x60,

    SBC_IMM = 0xE9,
    SBC_ZP = 0xE5, SBC_ZP_X = 0xF5,
    SBC_ABS = 0xED, SBC_ABS_X = 0xFD, SBC_ABS_Y = 0xF9,
    SBC_IND_X = 0xE1, SBC_IND_Y = 0xF1,

    STA_ZP = 0x85, STA_ZP_X = 0x95,
    STA_ABS = 0x8D, STA_ABS_X = 0x9D, STA_ABS_Y = 0x99,
    STA_IND_X = 0x81, STA_IND_Y = 0x91,

    STX_ZP = 0x86, STX_ZP_Y = 0x96,
    STX_ABS = 0x8E,

    STY_ZP = 0x84, STY_ZP_X = 0x94,
    STY_ABS = 0x8C,

    TAX = 0xAA, TAY = 0xA8,
    TXA = 0x8A, TYA = 0x98,
    TSX = 0xBA, TXS = 0x9A
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
