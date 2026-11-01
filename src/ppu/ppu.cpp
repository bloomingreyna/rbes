#include <memory/memory.h>
#include <ppu/ppu.h>

PPU::PPU(Memory* mem) : memory(mem) {}

void PPU::Tick() {
    if (!memory->ppustatus_signal) {
        if (current_scanline == static_cast<int>(Timing::VBLANK_START) && current_dot == 1) {
            vblank_flag = true;
        }
    } else {
        vblank_flag = false;
    }

    if (current_scanline == 0) {
        eo_flag = static_cast<EOflag>(!static_cast<bool>(eo_flag));
    }

    if (++current_dot == static_cast<int>(Timing::DOTS_PER_SCANLINE)) {
        current_dot = 0;
        if (++current_scanline == static_cast<int>(Timing::SCANLINE_COUNT)) {
            current_scanline = 0;
            vblank_flag = false;
        }
    }
}
