#include <cpu/cpu.h>
#include <cpu/instructions.h>

void FixupCycle(CPU& cpu) {
    cpu.program_counter &= 0xFF00;
    cpu.program_counter |= cpu.alu.result;

    if ((cpu.alu.status & Flag::OVERFLOW) != 0) {
        cpu.program_counter += 0x01 << 8;
    } else if ((cpu.alu.status & Flag::NEGATIVE) != 0) {
        cpu.program_counter -= 0x01 << 8;
    } else {
        cpu.CompleteInstruction();
    }
}

void instructions::branch::BranchCarryClear(CPU& cpu, int step) {
    switch (step) {
        case 0: {
            if (static_cast<bool>(cpu.status & Flag::CARRY)) {
                cpu.CompleteInstruction();
            } else {
                cpu.alu.Add(cpu.program_counter & 0xFF, cpu.data_bus);
            }
            break;
        }
        case 1: {
            FixupCycle(cpu);
            break;
        }
        case 2: {
            cpu.CompleteInstruction();
            break;
        }
    }
}

void instructions::branch::BranchCarrySet(CPU& cpu, int step) {
    switch (step) {
        case 0: {
            if (!static_cast<bool>(cpu.status & Flag::CARRY)) {
                cpu.CompleteInstruction();
            } else {
                cpu.alu.Add(cpu.program_counter & 0xFF, cpu.data_bus);
            }
            break;
        }
        case 1: {
            FixupCycle(cpu);
            break;
        }
        case 2: {
            cpu.CompleteInstruction();
            break;
        }
    }
}

void instructions::branch::BranchEqual(CPU& cpu, int step) {
    switch (step) {
        case 0: {
            if (!static_cast<bool>(cpu.status & Flag::ZERO)) {
                cpu.CompleteInstruction();
            } else {
                cpu.alu.Add(cpu.program_counter & 0xFF, cpu.data_bus);
            }
            break;
        }
        case 1: {
            FixupCycle(cpu);
            break;
        }
        case 2: {
            cpu.CompleteInstruction();
            break;
        }
    }

}

void instructions::branch::BranchNotEqual(CPU& cpu, int step) {
    switch (step) {
        case 0: {
            if (static_cast<bool>(cpu.status & Flag::ZERO)) {
                cpu.CompleteInstruction();
            } else {
                cpu.alu.Add(cpu.program_counter & 0xFF, cpu.data_bus);
            }
            break;
        }
        case 1: {
            FixupCycle(cpu);
            break;
        }
        case 2: {
            cpu.CompleteInstruction();
            break;
        }
    }

}

void instructions::branch::BranchPositive(CPU& cpu, int step) {
    switch (step) {
        case 0: {
            if (static_cast<bool>(cpu.status & Flag::NEGATIVE)) {
                cpu.CompleteInstruction();
            } else {
                cpu.alu.Add(cpu.program_counter & 0xFF, cpu.data_bus);
            }
            break;
        }
        case 1: {
            FixupCycle(cpu);
            break;
        }
        case 2: {
            cpu.CompleteInstruction();
            break;
        }
    }

}

void instructions::branch::BranchNegative(CPU& cpu, int step) {
    switch (step) {
        case 0: {
            if (!static_cast<bool>(cpu.status & Flag::NEGATIVE)) {
                cpu.CompleteInstruction();
            } else {
                cpu.alu.Add(cpu.program_counter & 0xFF, cpu.data_bus);
            }
            break;
        }
        case 1: {
            FixupCycle(cpu);
            break;
        }
        case 2: {
            cpu.CompleteInstruction();
            break;
        }
    }

}

void instructions::branch::BranchOverflowClear(CPU& cpu, int step) {
    switch (step) {
        case 0: {
            if (static_cast<bool>(cpu.status & Flag::OVERFLOW)) {
                cpu.CompleteInstruction();
            } else {
                cpu.alu.Add(cpu.program_counter & 0xFF, cpu.data_bus);
            }
            break;
        }
        case 1: {
            FixupCycle(cpu);
            break;
        }
        case 2: {
            cpu.CompleteInstruction();
            break;
        }
    }

}

void instructions::branch::BranchOverflowSet(CPU& cpu, int step) {
    switch (step) {
        case 0: {
            if (!static_cast<bool>(cpu.status & Flag::OVERFLOW)) {
                cpu.CompleteInstruction();
            } else {
                cpu.alu.Add(cpu.program_counter & 0xFF, cpu.data_bus);
            }
            break;
        }
        case 1: {
            FixupCycle(cpu);
            break;
        }
        case 2: {
            cpu.CompleteInstruction();
            break;
        }
    }
}
