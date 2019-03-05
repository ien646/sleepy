#include <catch2/catch.hpp>

#include "cpufw_test_init.hpp"

namespace sleepy
{
	TEST_CASE("CpuFirmware_RET")
	{
		SECTION("RET")
        {
            CPUFW_SLEEPY_TESTINIT();

            auto& ret = inst_map[opcode(0xC9)];

            u16 val = 0x987Fu;
            regs.sp = 0xAA06u;
            regs.pc = 0x0000u;
            mem.write_word(regs.sp, val);
            ret.call(nullptr);
            REQUIRE(regs.sp == 0xAA08u);
            REQUIRE(regs.pc == val);
        }

        //SECTION("RET Z")  { }
        //SECTION("RET C")  { }
        //SECTION("RET NZ") { }
        //SECTION("RET NC") { }
    };
}