#pragma once

#include <cstdint>

#define ComparisonOverload(enum_) \
constexpr bool operator>=(uint16_t lhs, enum_ rhs) { \
    return lhs >= static_cast<uint16_t>(rhs); \
} \
constexpr bool operator<=(uint16_t lhs, enum_ rhs) { \
    return lhs <= static_cast<uint16_t>(rhs); \
}

enum class AddressStart : uint16_t {
    INTERNAL_RAM = 0x0000,
    PPU_REGISTERS = 0x2000,
    APU_IO = 0x4000,
    APU_IO_DIS_FUNC = 0x4018,
    CARTRIDGE = 0x4020
};

enum class PPUregister : uint16_t {
    PPUCTRL = 0x2000,
    PPUMASK = 0x2001,
    PPUSTATUS = 0x2002,
    OAMADDR = 0x2003,
    OAMDATA = 0x2004,
    PPUSCROLL = 0x2005,
    PPUADDR = 0x2006,
    PPUDATA = 0x2007
};

enum class AddressEnd : uint16_t {
    INTERNAL_RAM = 0x1FFF,
    PPU_REGISTERS = 0x3FFF,
    APU_IO = 0x4017,
    APU_IO_DIS_FUNC = 0x401F,
    CARTRIDGE = 0xFFFF
};

enum class MirrorModulo {
    INTERNAL_RAM = 0x0800,
    PPU_REGISTERS = 0x0008
};

enum class InterruptVector {
    IRQ = 0xFFFE,
    NMI = 0xFFFA
};

enum class InterruptVectorByte {
    LOW, HIGH
};

ComparisonOverload(AddressStart)
ComparisonOverload(AddressEnd)
