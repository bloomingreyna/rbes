#include <unordered_map>
#include <vector>

#include <cpu/cpu.h>
#include <cpu/enums.h>
#include <cpu/instructions.h>

void CPU::InitializeInstructions() {
    using namespace instructions;
    using enum Instruction;

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
        {branch::BranchOverflowSet, {BVS}}
    };

    for (auto& [func_ptr, indices] : instruction_map) {
        for (auto inst : indices) {
            instruction_array[static_cast<size_t>(inst)] = func_ptr;
        }
    }
}
