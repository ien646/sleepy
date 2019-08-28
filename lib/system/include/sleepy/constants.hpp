#pragma once

#include <sleepy/common.hpp>

namespace sleepy
{
    const u64 CYCLES_PER_SECOND = 4194304;

    const u64 SCREEN_RES_X = 160;
    const u64 SCREEN_RES_Y = 144;

    const u64 VBLANKS_PER_SEC = 60;
    const u64 LCD_LINES_PER_SEC = VBLANKS_PER_SEC * SCREEN_RES_Y;

    const u64 CYCLES_PER_LCD_LINE = CYCLES_PER_SECOND / LCD_LINES_PER_SEC;
    const u64 CYCLES_PER_VBLANK = CYCLES_PER_SECOND / VBLANKS_PER_SEC;
}