#include <iostream>

#include <cpu/cpu.h>
#include <memory/memory.h>
#include <ppu/ppu.h>

namespace {
    Memory mem;
    CPU cpu(&mem);
    PPU ppu(&mem);

    constexpr float CLOCK_SPEED_HZ = 236.25 / 11 * 1000;
    constexpr float CLOCKS_PER_FRAME = CLOCK_SPEED_HZ / 60.0988;

    constexpr int CPU_CLOCK_RATIO = 12;
    constexpr int PPU_CLOCK_RATIO = 4;

    constexpr int PPU_TO_CPU_RATIO = 3;
    constexpr int CPU_PPU_SIGNAL_RESET_CLOCK = CPU_CLOCK_RATIO - PPU_TO_CPU_RATIO;

    float clock_accumulator = 0.0f;
    int cpu_clock = 0;
    int ppu_clock = 0;
}

void CPUloopLogic();
void PPUloopLogic();

void FrameUpdate();
void AudioUpdate();

int main(int argc, char* argv[]) {
    mem.LoadFile(argv[1]);

    while (true) {
        while (clock_accumulator++ < CLOCKS_PER_FRAME) {
            CPUloopLogic();
            PPUloopLogic();
        }
        clock_accumulator -= CLOCKS_PER_FRAME;

        FrameUpdate();
        AudioUpdate();
    }
}

/* ---- */

void CPUloopLogic() {
    cpu_clock++;
    cpu_clock %= CPU_CLOCK_RATIO;

    if (cpu_clock == 0) {
        cpu.Tick();
    }

    if (cpu_clock == CPU_PPU_SIGNAL_RESET_CLOCK) {
        mem.ppustatus_signal = false;
    }
}

void PPUloopLogic() {
    ppu_clock++;
    ppu_clock %= PPU_CLOCK_RATIO;

    if (ppu_clock == 0) {
        ppu.Tick();
    }

    if (mem.ppustatus_signal) {
        ppu.vblank_flag = false;
    }
}

void FrameUpdate() {

}

void AudioUpdate() {

}
