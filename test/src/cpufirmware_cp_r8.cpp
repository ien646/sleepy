#include <catch2/catch.hpp>

#include <sleepy/vcpu_firmware.hpp>
#include "test_macros.hpp"

namespace sleepy
{
	TEST_CASE("CpuFirmware_CP_V8")
	{
		SECTION("CP_V8_FlagsAreCorrect")
		{
			CPUFW_SLEEPY_TESTINIT();

			vcpu_instruction& cp_a = inst_map[opcode(0xBF)];
			vcpu_instruction& cp_b = inst_map[opcode(0xB8)];
			vcpu_instruction& cp_c = inst_map[opcode(0xB9)];
			vcpu_instruction& cp_d = inst_map[opcode(0xBA)];
			vcpu_instruction& cp_e = inst_map[opcode(0xBB)];
			vcpu_instruction& cp_h = inst_map[opcode(0xBC)];
			vcpu_instruction& cp_l = inst_map[opcode(0xBD)];
			vcpu_instruction& cp_phl = inst_map[opcode(0xBE)];
			vcpu_instruction& cp_d8 = inst_map[opcode(0xFE)];

			regs.a = 0x00;
			cp_a.call(nullptr);
			REQUIRE(regs.read_flag(FLAG_SUB));
			REQUIRE(regs.read_flag(FLAG_ZERO));
			REQUIRE(!(regs.read_flag(FLAG_HCARRY)));
			REQUIRE(!(regs.read_flag(FLAG_CARRY)));

			regs.a = 0x00;
			regs.b = 0x01;
			cp_b.call(nullptr);
			REQUIRE(regs.read_flag(FLAG_SUB));
			REQUIRE(!(regs.read_flag(FLAG_ZERO)));
			REQUIRE(regs.read_flag(FLAG_HCARRY));
			REQUIRE(regs.read_flag(FLAG_CARRY));

			regs.a = 0x10;
			regs.b = 0x01;
			cp_b.call(nullptr);
			REQUIRE(regs.read_flag(FLAG_SUB));
			REQUIRE(!(regs.read_flag(FLAG_ZERO)));
			REQUIRE(!(regs.read_flag(FLAG_HCARRY)));
			REQUIRE(!(regs.read_flag(FLAG_CARRY)));

			regs.a = 0x11;
			regs.b = 0x01;
			cp_b.call(nullptr);
			REQUIRE(regs.read_flag(FLAG_SUB));
			REQUIRE(!(regs.read_flag(FLAG_ZERO)));
			REQUIRE(regs.read_flag(FLAG_HCARRY));
			REQUIRE(!(regs.read_flag(FLAG_CARRY))); 
		}
	};
}