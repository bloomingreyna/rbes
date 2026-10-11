#include <cpu/cpu.h>

namespace instructions {
    namespace access {
        inline void LoadAccumulator(CPU& cpu, int step);
        inline void LoadX(CPU& cpu, int step);
        inline void LoadY(CPU& cpu, int step);

        inline void StoreAccumulator(CPU& cpu, int step);
        inline void StoreX(CPU& cpu, int step);
        inline void StoreY(CPU& cpu, int step);
    }
    namespace transfer {
        inline void TransferAccumulatorToX(CPU& cpu, int step);
        inline void TransferAccumulatorToY(CPU& cpu, int step);

        inline void TransferXtoAccumulator(CPU& cpu, int step);
        inline void TransferYtoAccumulator(CPU& cpu, int step);
    }
    namespace arithmetic {
        inline void AddWithCarry(CPU& cpu, int step);
        inline void SubtractWithCarry(CPU& cpu, int step);

        inline void IncrementMemory(CPU& cpu, int step);
        inline void IncrementX(CPU& cpu, int step);
        inline void IncrementY(CPU& cpu, int step);

        inline void DecrementMemory(CPU& cpu, int step);
        inline void DecrementX(CPU& cpu, int step);
        inline void DecrementY(CPU& cpu, int step);
    }
    namespace shift {
        inline void ArithmeticShiftLeft(CPU& cpu, int step);
        inline void LogicalShiftRight(CPU& cpu, int step);

        inline void RotateLeft(CPU& cpu, int step);
        inline void RotateRight(CPU& cpu, int step);
    }
    namespace bitwise {
        inline void AND(CPU& cpu, int step);
        inline void OR(CPU& cpu, int step);
        inline void XOR(CPU& cpu, int step);
        inline void BIT(CPU& cpu, int step);
    }
    namespace compare {
        inline void Compare(CPU& cpu, int step);
    }
    namespace branch {
        inline void BranchCarryClear(CPU& cpu, int step);
        inline void BranchCarrySet(CPU& cpu, int step);

        inline void BranchEqual(CPU& cpu, int step);
        inline void BranchNotEqual(CPU& cpu, int step);

        inline void BranchPositive(CPU& cpu, int step);
        inline void BranchNegative(CPU& cpu, int step);

        inline void BranchOverflowClear(CPU& cpu, int step);
        inline void BranchOverflowSet(CPU& cpu, int step);
    }
    namespace jump {
        inline void Jump(CPU& cpu, int step);
        inline void JumpToSubroutine(CPU& cpu, int step);
        
        inline void ReturnSubroutine(CPU& cpu, int step);
        inline void ReturnInterrupt(CPU& cpu, int step);

        inline void Break(CPU& cpu, int step);
    }
    namespace stack {
        inline void PushAccumulator(CPU& cpu, int step);
        inline void PullAccumulator(CPU& cpu, int step);

        inline void PushStatus(CPU& cpu, int step);
        inline void PullStatus(CPU& cpu, int step);

        inline void TransferXtoStack(CPU& cpu, int step);
        inline void TransferStackToX(CPU& cpu, int step);
    }
    namespace flags {
        inline void ClearCarry(CPU& cpu, int step);
        inline void ClearInterruptDisable(CPU& cpu, int step);
        inline void ClearDecimal(CPU& cpu, int step);
        inline void ClearOverflow(CPU& cpu, int step);

        inline void SetCarry(CPU& cpu, int step);
        inline void SetInterruptDisable(CPU& cpu, int step);
        inline void SetDecimal(CPU& cpu, int step);
    }
    namespace other {
        inline void NOP(CPU& cpu, int step);
    }
}