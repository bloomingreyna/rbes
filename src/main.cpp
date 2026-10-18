#include <iostream>

#include <cpu/cpu.h>
#include <memory/memory.h>

int main() {
    Memory mem;
    CPU cpu(&mem);

    cpu.InitializeAddressingModes();
    cpu.InitializeInstructions();

    std::string file_name;
    std::getline(std::cin, file_name);

    mem.LoadFile(file_name);

    while (true) {
        
    }
    return 0;
}
