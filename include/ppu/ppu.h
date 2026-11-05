#pragma once

#include <cstdint>
#include <vector>

#include <ppu/enums.h>

constexpr size_t VRAM_SIZE = 0x800;
constexpr size_t OAM_SIZE = 0x100;

struct Memory;

struct PPU {
    PPU(Memory* mem);

    void Tick();

    Memory* memory;

    std::vector<uint8_t> vram = std::vector<uint8_t>(VRAM_SIZE);
    std::vector<uint8_t> oam = std::vector<uint8_t>(OAM_SIZE);

    EOflag eo_flag = EOflag::EVEN;

    bool new_frame = false;
    int current_scanline = 0;
    int current_dot = 0;

    uint8_t latch;

    bool vblank_flag = false;
    bool nmi_output = false;
};
