class CPU;

namespace addressing_modes {
    inline void NoAddress(CPU& cpu, int step);

    inline void Immediate(CPU& cpu, int step);

    inline void ZeroPage(CPU& cpu, int step);
    inline void ZeroPageX(CPU& cpu, int step);
    inline void ZeroPageY(CPU& cpu, int step);

    inline void Absolute(CPU& cpu, int step);
    inline void AbsoluteX(CPU& cpu, int step);
    inline void AbsoluteY(CPU& cpu, int step);
    
    inline void Indirect(CPU& cpu, int step);
    inline void IndirectX(CPU& cpu, int step);
    inline void IndirectY(CPU& cpu, int step);
}