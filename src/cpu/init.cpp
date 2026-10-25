#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <cpu/addressing_modes.h>
#include <cpu/cpu.h>
#include <cpu/enums.h>
#include <cpu/instructions.h>
#include <memory/memory.h>

using enum Instruction;

CPU::CPU(Memory* mem) : memory(mem) {
    InitializeAddressingModes();
    InitializeInstructions();
    InitializeCycleCounts();
}

void CPU::Initialize() {
    inst_cycle_count = 0;
    switch (cycle_step) {
        case 0: {}
        case 1: {}
        case 2: {}
        case 3: {}
        case 4: {}
        case 5: {}
        case 6: {}
    }
}

void CPU::InitializeAddressingModes() {
    using namespace addressing_modes;

    std::unordered_map<void(*)(CPU&, int), std::vector<Instruction>> instruction_map = {
        {Implied, {
            BRK, // BRK is technically a two-byte instruction, but it is reused for hardware interrupts. As such, the implementation is separately coded to increment the PC by one when BRK is called via software.
            CLC, SEC, CLD, SED, CLI, SEI, CLV,
            INX, INY, DEX, DEY,
            NOP,
            PHA, PLA, PHP, PLP,
            RTS, RTI,
            TAX, TAY, TXA, TYA, TXS, TSX,
            ASL_ACC, LSR_ACC, ROL_ACC, ROR_ACC // Listed as accumulator on nesdev, though functionally equivalent to implied
        }},
        {Immediate, {
            JSR, // Listed as absolute on nesdev, but has special behavior that makes it easier to implement via immediate addressing mode
            LDA_IMM, LDX_IMM, LDY_IMM,
            ADC_IMM, SBC_IMM,
            AND_IMM, ORA_IMM, XOR_IMM,
            CMP_IMM, CPX_IMM, CPY_IMM,
            BCC, BCS, BEQ, BNE, BPL, BMI, BVC, BVS // Listed as relative on nesdev, though functionally equivalent to immediate
        }},
        {ZeroPage, {
            LDA_ZP, LDX_ZP, LDY_ZP,
            STA_ZP, STX_ZP, STY_ZP,
            ADC_ZP, SBC_ZP,
            INC_ZP, DEC_ZP,
            ASL_ZP, LSR_ZP, ROL_ZP, ROR_ZP,
            AND_ZP, ORA_ZP, XOR_ZP, BIT_ZP,
            CMP_ZP, CPX_ZP, CPY_ZP,
        }},
        {ZeroPageX, {
            LDA_ZP_X, LDY_ZP_X,
            STA_ZP_X, STY_ZP_X,
            ADC_ZP_X, SBC_ZP_X,
            INC_ZP_X, DEC_ZP_X,
            ASL_ZP_X, LSR_ZP_X, ROL_ZP_X, ROR_ZP_X,
            AND_ZP_X, ORA_ZP_X, XOR_ZP_X,
            CMP_ZP_X
        }},
        {ZeroPageY, {
            LDX_ZP_Y, STX_ZP_Y
        }},
        {Absolute, {
            LDA_ABS, LDX_ABS, LDY_ABS,
            STA_ABS, STX_ABS, STY_ABS,
            ADC_ABS, SBC_ABS,
            INC_ABS, DEC_ABS,
            ASL_ABS, LSR_ABS, ROL_ABS, ROR_ABS,
            AND_ABS, ORA_ABS, XOR_ABS, BIT_ABS,
            CMP_ABS, CPX_ABS, CPY_ABS,
            JMP_ABS
        }},
        {AbsoluteX, {
            LDA_ABS_X, LDY_ABS_X,
            STA_ABS_X,
            ADC_ABS_X, SBC_ABS_X,
            INC_ABS_X, DEC_ABS_X,
            ASL_ABS_X, LSR_ABS_X, ROL_ABS_X, ROR_ABS_X,
            AND_ABS_X, ORA_ABS_Y, XOR_ABS_Y,
            CMP_ABS_X
        }},
        {AbsoluteY, {
            LDA_ABS_Y, LDX_ABS_Y,
            STA_ABS_Y,
            ADC_ABS_Y, SBC_ABS_Y,
            AND_ABS_Y, ORA_ABS_Y, XOR_ABS_Y,
            CMP_ABS_Y
        }},
        {Indirect, {
            JMP_IND
        }},
        {IndirectX, {
            LDA_IND_X,
            STA_IND_X,
            ADC_IND_X, SBC_IND_X,
            AND_IND_X, ORA_IND_X, XOR_IND_X,
            CMP_IND_X
        }},
        {IndirectY, {
            LDA_IND_Y,
            STA_IND_Y,
            ADC_IND_Y, SBC_IND_Y,
            AND_IND_Y, ORA_IND_Y, XOR_IND_Y,
            CMP_IND_Y
        }}
    };

    for (auto& [func_ptr, indices] : instruction_map) {
        for (auto inst : indices) {
            addressing_mode_array[static_cast<size_t>(inst)] = func_ptr;
        }
    }
}

void CPU::InitializeInstructions() {
    using namespace instructions;

    std::unordered_map<void(*)(CPU&, int), std::vector<Instruction>> instruction_map = {
        {access::LoadAccumulator, {LDA_IMM, LDA_ZP, LDA_ZP_X, LDA_ABS, LDA_ABS_X, LDA_ABS_Y, LDA_IND_X, LDA_IND_Y}},
        {access::LoadX, {LDX_IMM, LDX_ZP, LDX_ZP_Y, LDX_ABS, LDX_ABS_Y}},
        {access::LoadY, {LDY_IMM, LDY_ZP, LDY_ZP_X, LDY_ABS, LDY_ABS_X}},
        {access::StoreAccumulator, {STA_ZP, STA_ZP_X, STA_ABS, STA_ABS_X, STA_ABS_Y, STA_IND_X, STA_IND_Y}},
        {access::StoreX, {STX_ZP, STX_ZP_Y, STX_ABS}},
        {access::StoreY, {STY_ZP, STY_ZP_X, STY_ABS}},

        {transfer::TransferAccumulatorToX, {TAX}},
        {transfer::TransferAccumulatorToY, {TAY}},
        {transfer::TransferXtoAccumulator, {TXA}},
        {transfer::TransferYtoAccumulator, {TYA}},

        {arithmetic::AddWithCarry, {ADC_IMM, ADC_ZP, ADC_ZP_X, ADC_ABS, ADC_ABS_X, ADC_ABS_Y, ADC_IND_X, ADC_IND_Y}},
        {arithmetic::SubtractWithCarry, {SBC_IMM, SBC_ZP, SBC_ZP_X, SBC_ABS, SBC_ABS_X, SBC_ABS_Y, SBC_IND_X, SBC_IND_Y}},
        {arithmetic::IncrementMemory, {INC_ZP, INC_ZP_X, INC_ABS, INC_ABS_X}},
        {arithmetic::IncrementX, {INX}},
        {arithmetic::IncrementY, {INY}},
        {arithmetic::DecrementMemory, {DEC_ZP, DEC_ZP_X, DEC_ABS, DEC_ABS_X}},
        {arithmetic::DecrementX, {DEX}},
        {arithmetic::DecrementY, {DEY}},

        {shift::ArithmeticShiftLeft, {ASL_ACC, ASL_ZP, ASL_ZP_X, ASL_ABS, ASL_ABS_X}},
        {shift::LogicalShiftRight, {LSR_ACC, LSR_ZP, LSR_ZP_X, LSR_ABS, LSR_ABS_X}},
        {shift::RotateLeft, {ROL_ACC, ROL_ZP, ROL_ZP_X, ROL_ABS, ROL_ABS_X}},
        {shift::RotateRight, {ROR_ACC, ROR_ZP, ROR_ZP_X, ROR_ABS, ROR_ABS_X}},

        {bitwise::AND, {AND_IMM, AND_ZP, AND_ZP_X, AND_ABS, AND_ABS_X, AND_ABS_Y, AND_IND_X, AND_IND_Y}},
        {bitwise::OR, {ORA_IMM, ORA_ZP, ORA_ZP_X, ORA_ABS, ORA_ABS_X, ORA_ABS_Y, ORA_IND_X, ORA_IND_Y}},
        {bitwise::XOR, {XOR_IMM, XOR_ZP, XOR_ZP_X, XOR_ABS, XOR_ABS_X, XOR_ABS_Y, XOR_IND_X, XOR_IND_Y}},
        {bitwise::BIT, {BIT_ZP, BIT_ABS}},

        {compare::CompareAccumulator, {CMP_IMM, CMP_ZP, CMP_ZP_X, CMP_ABS, CMP_ABS_X, CMP_ABS_Y, CMP_IND_X, CMP_IND_Y}},
        {compare::CompareX, {CPX_IMM, CPX_ZP, CPX_ABS}},
        {compare::CompareY, {CPY_IMM, CPY_ZP, CPY_ABS}},

        {branch::BranchCarryClear, {BCC}},
        {branch::BranchCarrySet, {BCS}},
        {branch::BranchEqual, {BEQ}},
        {branch::BranchNotEqual, {BNE}},
        {branch::BranchPositive, {BPL}},
        {branch::BranchNegative, {BNE}},
        {branch::BranchOverflowClear, {BVC}},
        {branch::BranchOverflowSet, {BVS}},

        {jump::Jump, {JMP_ABS, JMP_IND}},
        {jump::JumpToSubroutine, {JSR}},
        {jump::ReturnFromSubroutine, {RTS}},
        {jump::ReturnFromInterrupt, {RTI}},
        {jump::Break, {BRK}},

        {stack::PushAccumulator, {PHA}},
        {stack::PullAccumulator, {PLA}},
        {stack::PushStatus, {PHP}},
        {stack::PullStatus, {PLP}},
        {stack::TransferXtoStack, {TXS}},
        {stack::TransferStackToX, {TSX}},

        {flags::ClearCarry, {CLC}},
        {flags::SetCarry, {SEC}},
        {flags::ClearDecimal, {CLD}},
        {flags::SetDecimal, {SED}},
        {flags::ClearInterruptDisable, {CLI}},
        {flags::SetInterruptDisable, {SEI}},
        {flags::ClearOverflow, {CLV}},

        {other::NOP, {NOP}}
    };

    for (auto& [func_ptr, indices] : instruction_map) {
        for (auto inst : indices) {
            instruction_array[static_cast<size_t>(inst)] = func_ptr;
        }
    }
}

// This function is essentially only used to help poll interrupts at the correct timing; branch instructions are deliberately omitted from regular initialization and are separately tracked according to their documented special behavior.
void CPU::InitializeCycleCounts() {
    std::unordered_map<int, std::vector<Instruction>> instruction_map = {
        {-1, { // For easy branch instruction detection
            BCC, BCS,
            BEQ, BNE,
            BPL, BMI,
            BVC, BVS
        }},
        {2, {
            LDA_IMM, LDX_IMM, LDY_IMM,
            TAX, TAY, TXA, TYA,
            ADC_IMM, SBC_IMM,
            INX, INY, DEX, DEY,
            ASL_ACC, LSR_ACC, ROL_ACC, ROR_ACC,
            AND_IMM, ORA_IMM, XOR_IMM,
            CMP_IMM, CPX_IMM, CPY_IMM,
            CLC, CLD, CLI, CLV,
            TXS, TSX,
            SEC, SED, SEI,
            NOP
        }},
        {3, {
            LDA_ZP, LDX_ZP, LDY_ZP,
            STA_ZP, STX_ZP, STY_ZP,
            ADC_ZP, SBC_ZP,
            AND_ZP, ORA_ZP, XOR_ZP, BIT_ZP,
            CMP_ZP, CPX_ZP, CPY_ZP,
            JMP_ABS,
            PHA, PHP
        }},
        {4, {
            LDA_ZP_X, LDA_ABS, LDA_ABS_X, LDA_ABS_Y,
            LDX_ZP_Y, LDX_ABS, LDX_ABS_Y,
            LDY_ZP_X, LDY_ABS, LDY_ABS_X,
            STA_ZP_X, STA_ABS,
            STX_ZP_Y, STX_ABS,
            STY_ZP_X, STY_ABS,
            ADC_ZP_X, ADC_ABS, ADC_ABS_X, ADC_ABS_Y,
            SBC_ZP_X, SBC_ABS, SBC_ABS_X, SBC_ABS_Y,
            AND_ZP_X, AND_ABS, AND_ABS_X, AND_ABS_Y,
            ORA_ZP_X, ORA_ABS, ORA_ABS_X, ORA_ABS_Y,
            XOR_ZP_X, XOR_ABS, XOR_ABS_X, XOR_ABS_Y,
            BIT_ABS,
            CMP_ZP_X, CMP_ABS, CMP_ABS_X, CMP_ABS_Y,
            CPX_ABS, CPY_ABS,
            PLA, PLP
        }},
        {5, {
            LDA_IND_Y,
            STA_ABS_X, STA_ABS_Y,
            ADC_IND_Y, SBC_IND_Y,
            INC_ZP, DEC_ZP,
            ASL_ZP, LSR_ZP, ROL_ZP, ROR_ZP,
            AND_IND_Y, ORA_IND_Y, XOR_IND_Y,
            CMP_IND_Y,
            JMP_IND
        }},
        {6, {
            LDA_IND_X,
            STA_IND_X, STA_IND_Y,
            ADC_IND_X, SBC_IND_X,
            INC_ZP_X, INC_ABS,
            DEC_ZP_X, DEC_ABS,
            ASL_ZP_X, ASL_ABS,
            LSR_ZP_X, LSR_ABS,
            ROL_ZP_X, ROL_ABS,
            ROR_ZP_X, ROR_ABS,
            AND_IND_X, ORA_IND_X, XOR_IND_X,
            CMP_IND_X,
            JSR, RTS, RTI
        }},
        {7, {
            INC_ABS_X, DEC_ABS_X,
            ASL_ABS_X, LSR_ABS_X, ROL_ABS_X, ROR_ABS_X,
            BRK
        }}
    };

    for (auto& [count, indices] : instruction_map) {
        for (auto inst : indices) {
            cycle_count_array[static_cast<size_t>(inst)] = count;
        }
    }
}
