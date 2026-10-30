#include <memory/memory.h>
#include <ppu/ppu.h>

void PPU::Tick() {
    if (current_dot == 0 && current_scanline == static_cast<int>(Timing::VBLANK_START)) {
        vblank_flag = true;
    }

    if (memory->GetPPUSTATUSsignal()) {
        vblank_flag = false;
    }

    if (new_frame) {
        eo_flag = static_cast<EOflag>(!static_cast<bool>(eo_flag));
        new_frame = false;
    }

    if (++current_dot == static_cast<int>(Timing::DOTS_PER_SCANLINE)) {
        current_dot = 0;
        if (++current_scanline == static_cast<int>(Timing::SCANLINE_COUNT)) {
            current_scanline = 0;
            new_frame = true;
            vblank_flag = false;
        }
    }
}
