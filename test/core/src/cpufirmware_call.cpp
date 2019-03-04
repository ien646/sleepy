#include <catch2/catch.hpp>

#include "cpufw_test_init.hpp"

namespace sleepy
{
	TEST_CASE("CpuFirmware_CALL")
	{
		SECTION("CALL_a16")
        {
            CPUFW_SLEEPY_TESTINIT();

            auto& call_a16 = inst_map[opcode(0xCD)];

            word_t a16[2] = {0x1FF2u, 0x22E2u};
            byte_t* args = reinterpret_cast<byte_t*>(a16);
            regs.pc = 0x0000u;
            regs.sp = 0xFFFEu;
            call_a16.call(args);
            REQUIRE(regs.sp == 0xFFFCu);
            REQUIRE(mem.read_word(regs.sp) == 0x22E2u);
            REQUIRE(regs.pc == 0x1FF2u);
        }
    };
}