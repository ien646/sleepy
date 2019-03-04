#include <catch2/catch.hpp>

#include "cpufw_test_init.hpp"

namespace sleepy
{
	TEST_CASE("CpuFirmware_AND_A_V8")
	{
		SECTION("AND_A_V8_CorrectOperation")
		{
			CPUFW_SLEEPY_TESTINIT();

			const vcpu_instruction& and_a_a = inst_map[opcode(0xA7)];
			const vcpu_instruction& and_a_b = inst_map[opcode(0xA0)];
			const vcpu_instruction& and_a_c = inst_map[opcode(0xA1)];
			const vcpu_instruction& and_a_d = inst_map[opcode(0xA2)];
			const vcpu_instruction& and_a_e = inst_map[opcode(0xA3)];
			const vcpu_instruction& and_a_h = inst_map[opcode(0xA4)];
			const vcpu_instruction& and_a_l = inst_map[opcode(0xA5)];
			const vcpu_instruction& and_a_phl = inst_map[opcode(0xA6)];
			const vcpu_instruction& and_a_d8 = inst_map[opcode(0xE6)];

			regs.a = 0xFF;
			and_a_a.call(nullptr);
			REQUIRE(0xFF == regs.a);

			regs.a = 0x00;
			and_a_a.call(nullptr);
			REQUIRE(0x00 == regs.a);

			regs.a = 0xFF;
			regs.b = 0xDD;
			and_a_b.call(nullptr);
			REQUIRE((0xFF & 0xDD) == regs.a);

			regs.a = 0xFF;
			regs.c = 0xDD;
			and_a_c.call(nullptr);
			REQUIRE((0xFF & 0xDD) == regs.a);

			regs.a = 0xFF;
			regs.d = 0xDD;
			and_a_d.call(nullptr);
			REQUIRE((0xFF & 0xDD) == regs.a);

			regs.a = 0xFF;
			regs.e = 0xDD;
			and_a_e.call(nullptr);
			REQUIRE((0xFF & 0xDD) == regs.a);

			regs.a = 0xFF;
			regs.h = 0xDD;
			and_a_h.call(nullptr);
			REQUIRE((0xFF & 0xDD) == regs.a);

			regs.a = 0xFF;
			regs.l = 0xDD;
			and_a_l.call(nullptr);
			REQUIRE((0xFF & 0xDD) == regs.a);

			regs.a = 0xFF;
			u16 phl = 0xFAFA;
			mem.write_byte(phl, 0xDD);
			regs.hl(phl);
			and_a_phl.call(nullptr);
			REQUIRE((0xFF & 0xDD) == regs.a);

			regs.a = 0xFF;
			u8 d8 = 0xDD;
			and_a_d8.call(&d8);
			REQUIRE((0xFF & 0xDD) == regs.a);
		}

		SECTION("AND_A_V8_FlagsAreCorrect")
		{
			CPUFW_SLEEPY_TESTINIT();

			const vcpu_instruction& and_a_a = inst_map[opcode(0xA7)];
			const vcpu_instruction& and_a_b = inst_map[opcode(0xA0)];
			//const vcpu_instruction& and_a_c = inst_map[opcode(0xA1)];
			//const vcpu_instruction& and_a_d = inst_map[opcode(0xA2)];
			//const vcpu_instruction& and_a_e = inst_map[opcode(0xA3)];
			//const vcpu_instruction& and_a_h = inst_map[opcode(0xA4)];
			//const vcpu_instruction& and_a_l = inst_map[opcode(0xA5)];
			//const vcpu_instruction& and_a_phl = inst_map[opcode(0xA6)];

			regs.a = 0xFF;
			and_a_a.call(nullptr);
			REQUIRE(!(regs.read_flag(FLAG_ZERO)));
			REQUIRE(!(regs.read_flag(FLAG_CARRY)));
			REQUIRE(!(regs.read_flag(FLAG_HCARRY)));
			REQUIRE(regs.read_flag(FLAG_SUB));

			regs.a = 0x00;
			and_a_a.call(nullptr);
			REQUIRE(regs.read_flag(FLAG_ZERO));
			REQUIRE(!(regs.read_flag(FLAG_CARRY)));
			REQUIRE(!(regs.read_flag(FLAG_HCARRY)));
			REQUIRE(regs.read_flag(FLAG_SUB));

			regs.a = 0x00;
			regs.b = 0x00;
			and_a_b.call(nullptr);
			REQUIRE(regs.read_flag(FLAG_ZERO));
			REQUIRE(!(regs.read_flag(FLAG_CARRY)));
			REQUIRE(!(regs.read_flag(FLAG_HCARRY)));
			REQUIRE(regs.read_flag(FLAG_SUB));

			regs.a = 0xFF;
			regs.b = 0x00;
			and_a_b.call(nullptr);
			REQUIRE(regs.read_flag(FLAG_ZERO));
			REQUIRE(!(regs.read_flag(FLAG_CARRY)));
			REQUIRE(!(regs.read_flag(FLAG_HCARRY)));
			REQUIRE(regs.read_flag(FLAG_SUB));

			regs.a = 0xFF;
			regs.b = 0x0F;
			and_a_b.call(nullptr);
			REQUIRE(!(regs.read_flag(FLAG_ZERO)));
			REQUIRE(!(regs.read_flag(FLAG_CARRY)));
			REQUIRE(!(regs.read_flag(FLAG_HCARRY)));
			REQUIRE(regs.read_flag(FLAG_SUB));

			regs.a = 0xFF;
			regs.b = 0x10;
			and_a_b.call(nullptr);
			REQUIRE(!(regs.read_flag(FLAG_ZERO)));
			REQUIRE(!(regs.read_flag(FLAG_CARRY)));
			REQUIRE(!(regs.read_flag(FLAG_HCARRY)));
			REQUIRE(regs.read_flag(FLAG_SUB));
		}
	};
}