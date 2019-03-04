#include <catch2/catch.hpp>

#include "cpufw_test_init.hpp"

namespace sleepy
{
	TEST_CASE("CpuFirmware_OR_A_V8")
	{
		SECTION("OR_A_V8_CorrectOperation")
		{
			CPUFW_SLEEPY_TESTINIT();

			const vcpu_instruction& or_a_a = inst_map[opcode(0xB7)];
			const vcpu_instruction& or_a_b = inst_map[opcode(0xB0)];
			const vcpu_instruction& or_a_c = inst_map[opcode(0xB1)];
			const vcpu_instruction& or_a_d = inst_map[opcode(0xB2)];
			const vcpu_instruction& or_a_e = inst_map[opcode(0xB3)];
			const vcpu_instruction& or_a_h = inst_map[opcode(0xB4)];
			const vcpu_instruction& or_a_l = inst_map[opcode(0xB5)];
			const vcpu_instruction& or_a_phl = inst_map[opcode(0xB6)];
			const vcpu_instruction& or_a_d8 = inst_map[opcode(0xF6)];

			regs.a = 0xFF;
			or_a_a.call(nullptr);
			REQUIRE(0xFF == regs.a);

			regs.a = 0x00;
			or_a_a.call(nullptr);
			REQUIRE(0x00 == regs.a);

			regs.a = 0xAD;
			regs.b = 0xDA;
			or_a_b.call(nullptr);
			REQUIRE((0xAD | 0xDA) == regs.a);

			regs.a = 0xAD;
			regs.c = 0xDA;
			or_a_c.call(nullptr);
			REQUIRE((0xAD | 0xDA) == regs.a);

			regs.a = 0xAD;
			regs.d = 0xDA;
			or_a_d.call(nullptr);
			REQUIRE((0xAD | 0xDA) == regs.a);

			regs.a = 0xAD;
			regs.e = 0xDA;
			or_a_e.call(nullptr);
			REQUIRE((0xAD | 0xDA) == regs.a);

			regs.a = 0xAD;
			regs.h = 0xDA;
			or_a_h.call(nullptr);
			REQUIRE((0xAD | 0xDA) == regs.a);

			regs.a = 0xAD;
			regs.l = 0xDA;
			or_a_l.call(nullptr);
			REQUIRE((0xAD | 0xDA) == regs.a);

			regs.a = 0xAD;
			u16 phl = 0xFAFA;
			regs.hl(phl);
			mem.write_byte(phl, 0xDA);
			or_a_phl.call(nullptr);
			REQUIRE((0xAD | 0xDA) == regs.a);

			regs.a = 0xAD;
			u8 d8 = 0xDA;
			or_a_d8.call(&d8);
			REQUIRE((0xAD | 0xDA) == regs.a);
		}

		SECTION("OR_A_V8_FlagsAreCorrect")
		{
			CPUFW_SLEEPY_TESTINIT();

			const vcpu_instruction& or_a_a = inst_map[opcode(0xB7)];
			const vcpu_instruction& or_a_b = inst_map[opcode(0xB0)];
			//const vcpu_instruction& or_a_c = inst_map[opcode(0xB1)];
			//const vcpu_instruction& or_a_d = inst_map[opcode(0xB2)];
			//const vcpu_instruction& or_a_e = inst_map[opcode(0xB3)];
			//const vcpu_instruction& or_a_h = inst_map[opcode(0xB4)];
			//const vcpu_instruction& or_a_l = inst_map[opcode(0xB5)];
			//const vcpu_instruction& or_a_phl = inst_map[opcode(0xB6)];

			regs.a = 0xFF;
			or_a_a.call(nullptr);
			REQUIRE(!(regs.read_flag(FLAG_ZERO)));
			REQUIRE(!(regs.read_flag(FLAG_CARRY)));
			REQUIRE(!(regs.read_flag(FLAG_HCARRY)));
			REQUIRE(!(regs.read_flag(FLAG_SUB)));

			regs.a = 0x00;
			or_a_a.call(nullptr);
			REQUIRE(regs.read_flag(FLAG_ZERO));
			REQUIRE(!(regs.read_flag(FLAG_CARRY)));
			REQUIRE(!(regs.read_flag(FLAG_HCARRY)));
			REQUIRE(!(regs.read_flag(FLAG_SUB)));

			regs.a = 0x00;
			regs.b = 0x00;
			or_a_b.call(nullptr);
			REQUIRE(regs.read_flag(FLAG_ZERO));
			REQUIRE(!(regs.read_flag(FLAG_CARRY)));
			REQUIRE(!(regs.read_flag(FLAG_HCARRY)));
			REQUIRE(!(regs.read_flag(FLAG_SUB)));

			regs.a = 0xFF;
			regs.b = 0x00;
			or_a_b.call(nullptr);
			REQUIRE(!(regs.read_flag(FLAG_ZERO)));
			REQUIRE(!(regs.read_flag(FLAG_CARRY)));
			REQUIRE(!(regs.read_flag(FLAG_HCARRY)));
			REQUIRE(!(regs.read_flag(FLAG_SUB)));

			regs.a = 0xFF;
			regs.b = 0x0F;
			or_a_b.call(nullptr);
			REQUIRE(!(regs.read_flag(FLAG_ZERO)));
			REQUIRE(!(regs.read_flag(FLAG_CARRY)));
			REQUIRE(!(regs.read_flag(FLAG_HCARRY)));
			REQUIRE(!(regs.read_flag(FLAG_SUB)));

			regs.a = 0xFF;
			regs.b = 0x10;
			or_a_b.call(nullptr);
			REQUIRE(!(regs.read_flag(FLAG_ZERO)));
			REQUIRE(!(regs.read_flag(FLAG_CARRY)));
			REQUIRE(!(regs.read_flag(FLAG_HCARRY)));
			REQUIRE(!(regs.read_flag(FLAG_SUB)));
		}
	};
}