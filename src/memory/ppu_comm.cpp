#include <memory/memory.h>

bool Memory::GetPPUSTATUSsignal() {
    bool state = ppustatus_signal;
    ppustatus_signal = false;
    return state;
}

bool Memory::GetPPUCTRLsignal() {
    bool state = ppuctrl_signal;
    ppuctrl_signal = false;
    return state;
}
