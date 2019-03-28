#pragma once

namespace sleepy
{
    enum class interrupt_addr
    {
        VBLANK = 0x0040u,
        LCDC = 0x0048u,
        TIMER_OF = 0x0050,
        SIOTC = 0x0058
    };
}