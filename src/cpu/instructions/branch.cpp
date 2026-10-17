#include <cpu/cpu.h>
#include <cpu/instructions.h>

// Branches the PC, then returns true if a page was crossed (low byte over/underflowed)
bool BranchCheckPageCross(CPU& cpu) {
    uint8_t pc_low = cpu.program_counter & 0xFF;
    uint16_t result = pc_low + cpu.data_bus;
    cpu.program_counter &= 0xFF00;
    cpu.program_counter |= result & 0xFF;

    bool carry_out = ((pc_low ^ cpu.data_bus ^ result) & 0x0100) != 0;
    bool positive = (cpu.data_bus & 0x80) == 0;

    bool overflow = carry_out && positive;
    bool underflow = !carry_out && !positive;

    if (overflow || underflow) {
        return true;
    }
    return false;
}

void AdjustHighByte(CPU& cpu) {
    if ((cpu.data_bus & 0x80) == 0) {
        cpu.program_counter += 1 << 8;
    } else {
        cpu.program_counter -= 1 << 8;
    }
}

void instructions::branch::BranchCarryClear(CPU& cpu, int step) {
    switch (step) {
        case 0: {
            cpu.program_counter++;
            if ((cpu.status & Flag::CARRY) != 0) {
                cpu.CompleteInstruction();
            }
            break;
        }
        case 1: {
            if (!BranchCheckPageCross(cpu)) {
                cpu.CompleteInstruction();
            }
            break;
        }
        case 2: {
            AdjustHighByte(cpu);
            cpu.CompleteInstruction();
            break;
        }
    }
}

void instructions::branch::BranchCarrySet(CPU& cpu, int step) {
    switch (step) {
        case 0: {
            cpu.program_counter++;
            if ((cpu.status & Flag::CARRY) == 0) {
                cpu.CompleteInstruction();
            }
            break;
        }
        case 1: {
            if (!BranchCheckPageCross(cpu)) {
                cpu.CompleteInstruction();
            }
            break;
        }
        case 2: {
            AdjustHighByte(cpu);
            cpu.CompleteInstruction();
            break;
        }
    }
}

void instructions::branch::BranchEqual(CPU& cpu, int step) {
    switch (step) {
        case 0: {
            cpu.program_counter++;
            if ((cpu.status & Flag::ZERO) == 0) {
                cpu.CompleteInstruction();
            }
            break;
        }
        case 1: {
            if (!BranchCheckPageCross(cpu)) {
                cpu.CompleteInstruction();
            }
            break;
        }
        case 2: {
            AdjustHighByte(cpu);
            cpu.CompleteInstruction();
            break;
        }
    }

}

void instructions::branch::BranchNotEqual(CPU& cpu, int step) {
    switch (step) {
        case 0: {
            cpu.program_counter++;
            if ((cpu.status & Flag::ZERO) != 0) {
                cpu.CompleteInstruction();
            }
            break;
        }
        case 1: {
            if (!BranchCheckPageCross(cpu)) {
                cpu.CompleteInstruction();
            }
            break;
        }
        case 2: {
            AdjustHighByte(cpu);
            cpu.CompleteInstruction();
            break;
        }
    }

}

void instructions::branch::BranchPositive(CPU& cpu, int step) {
    switch (step) {
        case 0: {
            cpu.program_counter++;
            if ((cpu.status & Flag::NEGATIVE) != 0) {
                cpu.CompleteInstruction();
            }
            break;
        }
        case 1: {
            if (!BranchCheckPageCross(cpu)) {
                cpu.CompleteInstruction();
            }
            break;
        }
        case 2: {
            AdjustHighByte(cpu);
            cpu.CompleteInstruction();
            break;
        }
    }

}

void instructions::branch::BranchNegative(CPU& cpu, int step) {
    switch (step) {
        case 0: {
            cpu.program_counter++;
            if ((cpu.status & Flag::NEGATIVE) == 0) {
                cpu.CompleteInstruction();
            }
            break;
        }
        case 1: {
            if (!BranchCheckPageCross(cpu)) {
                cpu.CompleteInstruction();
            }
            break;
        }
        case 2: {
            AdjustHighByte(cpu);
            cpu.CompleteInstruction();
            break;
        }
    }

}

void instructions::branch::BranchOverflowClear(CPU& cpu, int step) {
    switch (step) {
        case 0: {
            cpu.program_counter++;
            if ((cpu.status & Flag::OVERFLOW) != 0) {
                cpu.CompleteInstruction();
            }
            break;
        }
        case 1: {
            if (!BranchCheckPageCross(cpu)) {
                cpu.CompleteInstruction();
            }
            break;
        }
        case 2: {
            AdjustHighByte(cpu);
            cpu.CompleteInstruction();
            break;
        }
    }

}

void instructions::branch::BranchOverflowSet(CPU& cpu, int step) {
    switch (step) {
        case 0: {
            cpu.program_counter++;
            if ((cpu.status & Flag::OVERFLOW) == 0) {
                cpu.CompleteInstruction();
            }
            break;
        }
        case 1: {
            if (!BranchCheckPageCross(cpu)) {
                cpu.CompleteInstruction();
            }
            break;
        }
        case 2: {
            AdjustHighByte(cpu);
            cpu.CompleteInstruction();
            break;
        }
    }

}
