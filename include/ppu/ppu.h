#pragma once

#include <cstdint>
#include <vector>

#include <ppu/enums.h>

class Memory;

constexpr size_t OAM_SIZE = 256;

class PPU {
public:
    void Tick();
private:
    Memory* memory;

    EOflag eo_flag = EOflag::EVEN;

    bool new_frame = false;
    int current_scanline = 0;
    int current_dot = 0;

    std::vector<uint8_t> oam = std::vector<uint8_t>(OAM_SIZE);

    uint8_t latch;
    bool vblank_flag = false;
    bool nmi_output = false;
};
