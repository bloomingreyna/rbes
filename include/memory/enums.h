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
    APU_IO = 0x4000
};

enum class AddressEnd : uint16_t {
    INTERNAL_RAM = 0x1FFF,
    PPU_REGISTERS = 0x3FFF,
    APU_IO = 0x4017
};

enum class MirrorModulo {
    INTERNAL_RAM = 0x0800,
    PPU_REGISTERS = 0x0008
};

ComparisonOverload(AddressStart)
ComparisonOverload(AddressEnd)
