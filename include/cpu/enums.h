enum class Instruction {};

/* On a real 6502, the R/W line is pulled high for a read, and low for a write.
   Voltage levels don't matter for emulation, but hey, trivia :P */
enum class RWline {
    WRITE = 0, READ = 1
};