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

    bool nmi_generated = false;

    uint16_t null_term_address = 0x6004;
}

void CPUloopLogic();
void PPUloopLogic();

void FrameUpdate();
void AudioUpdate();

void DebugLog();

int main(int argc, char* argv[]) {
    mem.LoadFile(argv[1]);
    std::cout << reinterpret_cast<void*>(mem.cpu_bus[0xE447]) << '\n';

    cpu.program_counter = (mem.cpu_bus[0xFFFD] << 8) | (mem.cpu_bus[0xFFFC] & 0xFF);
    cpu.cycle_type = CycleType::FETCH;

    while (true) {
        while (clock_accumulator++ < CLOCKS_PER_FRAME) {
            CPUloopLogic();
            PPUloopLogic();
        }
        clock_accumulator -= CLOCKS_PER_FRAME;

        FrameUpdate();
        AudioUpdate();

        DebugLog();
    }
}

/* ---- */


void CPUloopLogic() {
    cpu.nmi_input = nmi_generated;

    cpu_clock++;
    cpu_clock %= CPU_CLOCK_RATIO;

    if (cpu_clock == 0) {
        cpu.Tick();
        std::cout << "PC: " << reinterpret_cast<void*>(cpu.program_counter) << ", ";
        std::cout << "ROM PC: " << reinterpret_cast<void*>(cpu.program_counter - 0x8000 + 0x10) << ", ";
        std::cout << "Opcode: " << reinterpret_cast<void*>(cpu.instruction) << '\n';
    }

    if (cpu.program_counter == 0xC66E) {
        std::terminate();
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

    uint8_t ppustatus = mem.PPURegisterRead(PPUregister::PPUSTATUS);
    mem.PPURegisterWrite(PPUregister::PPUSTATUS, (ppustatus & ~0x80) | (ppu.vblank_flag << 7));

    nmi_generated = ppu.vblank_flag && ppu.nmi_output;
}

void FrameUpdate() {

}

void AudioUpdate() {

}

void DebugLog() {
    while (mem.cpu_bus[null_term_address] != 0x00) {
        std::cout << mem.cpu_bus[null_term_address++];
    }
}
