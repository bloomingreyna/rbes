#pragma once

enum class EOflag {
    EVEN, ODD
};

enum class Timing {
    SCANLINE_COUNT = 262,
    DOTS_PER_SCANLINE = 341,
    VBLANK_START = 240 // Zero-indexed, nesdev notes it as 241
};
