#include <catch2/catch.hpp>

#include "../../cpufw_test_init.hpp"

namespace sleepy
{
	TEST_CASE("CpuFirmware_INC_R8")
	{
		SECTION("INC_R8_CorrectOperation")
		{
			CPUFW_SLEEPY_TESTINIT();

			const vcpu_instruction& inc_a = inst_map[opcode(0x3C)];
			//const vcpu_instruction& inc_b = inst_map[opcode(0x04)];
			//const vcpu_instruction& inc_c = inst_map[opcode(0x0C)];
			//const vcpu_instruction& inc_d = inst_map[opcode(0x14)];
			//const vcpu_instruction& inc_e = inst_map[opcode(0x1C)];
			//const vcpu_instruction& inc_h = inst_map[opcode(0x24)];
			//const vcpu_instruction& inc_l = inst_map[opcode(0x2C)];
			//const vcpu_instruction& inc_phl = inst_map[opcode(0x34)];

			regs.a = 0x00;
			inc_a.call(nullptr);
			REQUIRE(0x01 == regs.a);

			regs.a = 0x11;
			inc_a.call(nullptr);
			REQUIRE(0x12 == regs.a);
		}

		SECTION("INC_R8_CorrectFlags")
		{
			CPUFW_SLEEPY_TESTINIT();

			const vcpu_instruction& inc_a = inst_map[opcode(0x3C)];
			//const vcpu_instruction& inc_b = inst_map[opcode(0x04)];
			//const vcpu_instruction& inc_c = inst_map[opcode(0x0C)];
			//const vcpu_instruction& inc_d = inst_map[opcode(0x14)];
			//const vcpu_instruction& inc_e = inst_map[opcode(0x1C)];
			//const vcpu_instruction& inc_h = inst_map[opcode(0x24)];
			//const vcpu_instruction& inc_l = inst_map[opcode(0x2C)];
			//const vcpu_instruction& inc_phl = inst_map[opcode(0x24)];

			regs.a = 0x00;
			inc_a.call(nullptr);
			REQUIRE(!(regs.read_flag(FLAG_CARRY)));
			REQUIRE(!(regs.read_flag(FLAG_HCARRY)));
			REQUIRE(!(regs.read_flag(FLAG_SUB)));
			REQUIRE(!(regs.read_flag(FLAG_ZERO)));

			regs.a = 0x01;
			inc_a.call(nullptr);
			REQUIRE(!(regs.read_flag(FLAG_CARRY)));
			REQUIRE(!(regs.read_flag(FLAG_HCARRY)));
			REQUIRE(!(regs.read_flag(FLAG_SUB)));
			REQUIRE(!(regs.read_flag(FLAG_ZERO)));

			regs.a = 0x0F;
			inc_a.call(nullptr);
			REQUIRE(!(regs.read_flag(FLAG_CARRY)));
			REQUIRE(regs.read_flag(FLAG_HCARRY));
			REQUIRE(!(regs.read_flag(FLAG_SUB)));
			REQUIRE(!(regs.read_flag(FLAG_ZERO)));

			regs.a = 0xFE;
			inc_a.call(nullptr);
			REQUIRE(!(regs.read_flag(FLAG_CARRY)));
			REQUIRE(!(regs.read_flag(FLAG_HCARRY)));
			REQUIRE(!(regs.read_flag(FLAG_SUB)));
			REQUIRE(!(regs.read_flag(FLAG_ZERO)));

			regs.a = 0xFF;
			inc_a.call(nullptr);
			REQUIRE(!(regs.read_flag(FLAG_CARRY)));
			REQUIRE((regs.read_flag(FLAG_HCARRY)));
			REQUIRE(!(regs.read_flag(FLAG_SUB)));
			REQUIRE(regs.read_flag(FLAG_ZERO));
		}
	};
}