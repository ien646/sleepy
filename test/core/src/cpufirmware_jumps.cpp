#include <catch2/catch.hpp>

#include "cpufw_test_init.hpp"

namespace sleepy
{
	TEST_CASE("CpuFirmware_Jumps")
    {
        SECTION("JR i8 (Jump relative v8-signed)")
        {
            CPUFW_SLEEPY_TESTINIT();

            auto& jr_i8 = inst_map[opcode(0x18)];

            regs.pc = 0x0000u;
            byte_t arg = static_cast<byte_t>(0x00);
            jr_i8.call(&arg);
            REQUIRE(regs.pc == 0x0000u);

            regs.pc = 0x0000u;
            arg = static_cast<byte_t>(0x01);
            jr_i8.call(&arg);
            REQUIRE(regs.pc == 0x0001u);

            regs.pc = 0x0000u;
            arg = static_cast<byte_t>(0x79);
            jr_i8.call(&arg);
            REQUIRE(regs.pc == 0x0079u);

            regs.pc = 0x00FFu;
            arg = static_cast<byte_t>(0x88);
            jr_i8.call(&arg);
            REQUIRE(regs.pc == 0x00FFu + static_cast<int8_t>(arg));

            regs.pc = 0x00FFu;
            arg = static_cast<byte_t>(0x01);
            jr_i8.call(&arg);
            REQUIRE(regs.pc == 0x0100u);
        }
    }
}