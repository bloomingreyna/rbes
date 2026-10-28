#include <iostream>

#include <cpu/cpu.h>
#include <memory/memory.h>

// #define EMU_DEBUG

int main(int argc, char* argv[]) {
    Memory mem;
    CPU cpu(&mem);

    cpu.InitializeAddressingModes();
    cpu.InitializeInstructions();

    std::string file_name = argv[1];

    mem.LoadFile(file_name);

    cpu.program_counter = (mem.CPURead(0xFFFD) << 8) | mem.CPURead(0xFFFC);
    cpu.inst_step = InstructionStep::FETCH;

    uint16_t text_output_index = 0x6004;
    while (true) { // TODO: Fix loop stopping for no reason
        cpu.Tick();

#ifdef EMU_DEBUG
        std::cout << static_cast<int>(cpu.inst_step) << ", ";
        std::cout << reinterpret_cast<void*>(cpu.program_counter) << ", ";
        std::cout << reinterpret_cast<void*>(cpu.program_counter - 0x8000 + 0x10) << ", "; // ROM address
        std::cout << reinterpret_cast<void*>(cpu.instruction) << '\n';

        if (cpu.instruction == Instruction::BIT_ABS) {
            std::cout << "Accumulator: " << reinterpret_cast<void*>(cpu.accumulator) << ", ";
            std::cout << "Memory: " << reinterpret_cast<void*>(cpu.data_bus) << ", ";
            std::cout << "Status: " << reinterpret_cast<void*>(cpu.data_bus) << '\n';
        }
#endif

        if (mem.CPURead(text_output_index) != 0x00) {
            std::cout << static_cast<int>(mem.CPURead(text_output_index++));
        }
    }
    std::cout << "Here";
    return 0;
}
