#include <catch2/catch.hpp>

#include "../../cpufw_test_init.hpp"

namespace sleepy
{
	TEST_CASE("CpuFirmware_Push_r16")
	{
        SECTION("CpuFirmware_Push_AF")
		{
			CPUFW_SLEEPY_TESTINIT();

            auto& push_af = inst_map[opcode(0xF5)];

            regs.af(0xF123u);
            regs.sp = 0xFF22u;
            push_af.call(nullptr);
            REQUIRE(regs.sp == 0xFF20);
            REQUIRE(mem.read_word(regs.sp) == 0xF123);
        }

		SECTION("CpuFirmware_Push_BC")
		{
			CPUFW_SLEEPY_TESTINIT();

            auto& push_bc = inst_map[opcode(0xC5)];

            regs.bc(0xF123u);
            regs.sp = 0xFF22u;
            push_bc.call(nullptr);
            REQUIRE(regs.sp == 0xFF20);
            REQUIRE(mem.read_word(regs.sp) == 0xF123);
        }

        SECTION("CpuFirmware_Push_DE")
		{
			CPUFW_SLEEPY_TESTINIT();

            auto& push_de = inst_map[opcode(0xD5)];

            regs.de(0xF123u);
            regs.sp = 0xFF22u;
            push_de.call(nullptr);
            REQUIRE(regs.sp == 0xFF20);
            REQUIRE(mem.read_word(regs.sp) == 0xF123);
        }

        SECTION("CpuFirmware_Push_HL")
		{
			CPUFW_SLEEPY_TESTINIT();

            auto& push_hl = inst_map[opcode(0xE5)];

            regs.hl(0xF123u);
            regs.sp = 0xFF22u;
            push_hl.call(nullptr);
            REQUIRE(regs.sp == 0xFF20);
            REQUIRE(mem.read_word(regs.sp) == 0xF123);
        }
    }
}