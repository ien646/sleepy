#include <catch2/catch.hpp>

#include "cpufw_test_init.hpp"

namespace sleepy
{
	TEST_CASE("CpuFirmware_CP_V8")
	{
		SECTION("CP_V8_FlagsAreCorrect")
		{
			CPUFW_SLEEPY_TESTINIT();

			const vcpu_instruction& cp_a = inst_map[opcode(0xBF)];
			const vcpu_instruction& cp_b = inst_map[opcode(0xB8)];
			//const vcpu_instruction& cp_c = inst_map[opcode(0xB9)];
			//const vcpu_instruction& cp_d = inst_map[opcode(0xBA)];
			//const vcpu_instruction& cp_e = inst_map[opcode(0xBB)];
			//const vcpu_instruction& cp_h = inst_map[opcode(0xBC)];
			//const vcpu_instruction& cp_l = inst_map[opcode(0xBD)];
			//const vcpu_instruction& cp_phl = inst_map[opcode(0xBE)];
			//const vcpu_instruction& cp_d8 = inst_map[opcode(0xFE)];

			regs.reset_flags();
			regs.a = 0x00;
			cp_a.call(nullptr);
			REQUIRE(regs.read_flag(FLAG_SUB));
			REQUIRE(regs.read_flag(FLAG_ZERO));
			REQUIRE(!(regs.read_flag(FLAG_HCARRY)));
			REQUIRE(!(regs.read_flag(FLAG_CARRY)));

			regs.reset_flags();
			regs.a = 0x00;
			regs.b = 0x01;
			cp_b.call(nullptr);
			REQUIRE(regs.read_flag(FLAG_SUB));
			REQUIRE(!(regs.read_flag(FLAG_ZERO)));
			REQUIRE(regs.read_flag(FLAG_HCARRY));
			REQUIRE(regs.read_flag(FLAG_CARRY));

			regs.reset_flags();
			regs.a = 0x10;
			regs.b = 0x01;
			cp_b.call(nullptr);
			REQUIRE(regs.read_flag(FLAG_SUB));
			REQUIRE(!(regs.read_flag(FLAG_ZERO)));
			REQUIRE((regs.read_flag(FLAG_HCARRY)));
			REQUIRE(!(regs.read_flag(FLAG_CARRY)));

			regs.reset_flags();
			regs.a = 0x11;
			regs.b = 0x01;
			cp_b.call(nullptr);
			REQUIRE(regs.read_flag(FLAG_SUB));
			REQUIRE(!(regs.read_flag(FLAG_ZERO)));
			REQUIRE(!regs.read_flag(FLAG_HCARRY));
			REQUIRE(!(regs.read_flag(FLAG_CARRY))); 
		}
	};
}