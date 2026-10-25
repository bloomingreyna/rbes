#pragma once

class CPU;

namespace addressing_modes {
    void Implied(CPU& cpu, int step);
    void Immediate(CPU& cpu, int step);

    void ZeroPage(CPU& cpu, int step);
    void ZeroPageX(CPU& cpu, int step);
    void ZeroPageY(CPU& cpu, int step);

    void Absolute(CPU& cpu, int step);
    void AbsoluteX(CPU& cpu, int step);
    void AbsoluteY(CPU& cpu, int step);

    void Indirect(CPU& cpu, int step);
    void IndirectX(CPU& cpu, int step);
    void IndirectY(CPU& cpu, int step);
}
