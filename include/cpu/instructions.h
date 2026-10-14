#pragma once

#include <array>

#include <cpu/enums.h>

class CPU;

namespace instructions {
    namespace access {
        void LoadAccumulator(CPU& cpu, int step);
        void LoadX(CPU& cpu, int step);
        void LoadY(CPU& cpu, int step);

        void StoreAccumulator(CPU& cpu, int step);
        void StoreX(CPU& cpu, int step);
        void StoreY(CPU& cpu, int step);
    }
    namespace transfer {
        void TransferAccumulatorToX(CPU& cpu, int step);
        void TransferAccumulatorToY(CPU& cpu, int step);

        void TransferXtoAccumulator(CPU& cpu, int step);
        void TransferYtoAccumulator(CPU& cpu, int step);
    }
    namespace arithmetic {
        void AddWithCarry(CPU& cpu, int step);
        void SubtractWithCarry(CPU& cpu, int step);

        void IncrementMemory(CPU& cpu, int step);
        void IncrementX(CPU& cpu, int step);
        void IncrementY(CPU& cpu, int step);

        void DecrementMemory(CPU& cpu, int step);
        void DecrementX(CPU& cpu, int step);
        void DecrementY(CPU& cpu, int step);
    }
    namespace shift {
        void ArithmeticShiftLeft(CPU& cpu, int step);
        void LogicalShiftRight(CPU& cpu, int step);

        void RotateLeft(CPU& cpu, int step);
        void RotateRight(CPU& cpu, int step);
    }
    namespace bitwise {
        void AND(CPU& cpu, int step);
        void OR(CPU& cpu, int step);
        void XOR(CPU& cpu, int step);
        void BIT(CPU& cpu, int step);
    }
    namespace compare {
        void CompareAccumulator(CPU& cpu, int step);
        void CompareX(CPU& cpu, int step);
        void CompareY(CPU& cpu, int step);
    }
    namespace branch {
        void BranchCarryClear(CPU& cpu, int step);
        void BranchCarrySet(CPU& cpu, int step);

        void BranchEqual(CPU& cpu, int step);
        void BranchNotEqual(CPU& cpu, int step);

        void BranchPositive(CPU& cpu, int step);
        void BranchNegative(CPU& cpu, int step);

        void BranchOverflowClear(CPU& cpu, int step);
        void BranchOverflowSet(CPU& cpu, int step);
    }
    namespace jump {
        void Jump(CPU& cpu, int step);
        void JumpToSubroutine(CPU& cpu, int step);

        void ReturnFromSubroutine(CPU& cpu, int step);
        void ReturnFromInterrupt(CPU& cpu, int step);

        void Break(CPU& cpu, int step);
    }
    namespace stack {
        void PushAccumulator(CPU& cpu, int step);
        void PullAccumulator(CPU& cpu, int step);

        void PushStatus(CPU& cpu, int step);
        void PullStatus(CPU& cpu, int step);

        void TransferXtoStack(CPU& cpu, int step);
        void TransferStackToX(CPU& cpu, int step);
    }
    namespace flags {
        void ClearCarry(CPU& cpu, int step);
        void ClearInterruptDisable(CPU& cpu, int step);
        void ClearDecimal(CPU& cpu, int step);
        void ClearOverflow(CPU& cpu, int step);

        void SetCarry(CPU& cpu, int step);
        void SetInterruptDisable(CPU& cpu, int step);
        void SetDecimal(CPU& cpu, int step);
    }
    namespace other {
        void NOP(CPU& cpu, int step);
    }
}
