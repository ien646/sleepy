#include <catch2/catch.hpp>

#include "cpufw_test_init.hpp"

namespace sleepy
{
	TEST_CASE("CpuFirmware_XOR_A_V8")
	{
		SECTION("XOR_A_V8_CorrectOperation")
		{
			CPUFW_SLEEPY_TESTINIT();

			const vcpu_instruction& xor_a_a = inst_map[opcode(0xAF)];
			const vcpu_instruction& xor_a_b = inst_map[opcode(0xA8)];
			const vcpu_instruction& xor_a_c = inst_map[opcode(0xA9)];
			const vcpu_instruction& xor_a_d = inst_map[opcode(0xAA)];
			const vcpu_instruction& xor_a_e = inst_map[opcode(0xAB)];
			const vcpu_instruction& xor_a_h = inst_map[opcode(0xAC)];
			const vcpu_instruction& xor_a_l = inst_map[opcode(0xAD)];
			const vcpu_instruction& xor_a_phl = inst_map[opcode(0xAE)];
			const vcpu_instruction& xor_a_d8 = inst_map[opcode(0xEE)];

			regs.a = 0xFF;
			xor_a_a.call(nullptr);
			REQUIRE((0xFF ^ 0xFF) == regs.a);

			regs.a = 0x00;
			xor_a_a.call(nullptr);
			REQUIRE((0x00 ^ 0x00) == regs.a);

			regs.a = 0xDA;
			regs.b = 0xAD;
			xor_a_b.call(nullptr);
			REQUIRE((0xDA ^ 0xAD) == regs.a);

			regs.a = 0xDA;
			regs.c = 0xAD;
			xor_a_c.call(nullptr);
			REQUIRE((0xDA ^ 0xAD) == regs.a);

			regs.a = 0xDA;
			regs.d = 0xAD;
			xor_a_d.call(nullptr);
			REQUIRE((0xDA ^ 0xAD) == regs.a);

			regs.a = 0xDA;
			regs.e = 0xAD;
			xor_a_e.call(nullptr);
			REQUIRE((0xDA ^ 0xAD) == regs.a);

			regs.a = 0xDA;
			regs.h = 0xAD;
			xor_a_h.call(nullptr);
			REQUIRE((0xDA ^ 0xAD) == regs.a);

			regs.a = 0xDA;
			regs.l = 0xAD;
			xor_a_l.call(nullptr);
			REQUIRE((0xDA ^ 0xAD) == regs.a);

			regs.a = 0xDA;
			u8 d8 = 0xAD;
			xor_a_d8.call(&d8);
			REQUIRE((0xDA ^ 0xAD) == regs.a);

			u16 phl = 0xFAFA;
			regs.hl(phl);
			mem.write_byte(regs.hl(), 0xAD);
			regs.a = 0xDA;
			xor_a_phl.call(&d8);
			REQUIRE((0xDA ^ 0xAD) == regs.a);
		}

		SECTION("XOR_A_V8_FlagsAreCorrect")
		{
			CPUFW_SLEEPY_TESTINIT();

			const vcpu_instruction& xor_a_a = inst_map[opcode(0xAF)];
			const vcpu_instruction& xor_a_b = inst_map[opcode(0xA8)];
			
			//const vcpu_instruction& xor_a_c = inst_map[opcode(0xA9)];
			//const vcpu_instruction& xor_a_d = inst_map[opcode(0xAA)];
			//const vcpu_instruction& xor_a_e = inst_map[opcode(0xAB)];
			//const vcpu_instruction& xor_a_h = inst_map[opcode(0xAC)];
			//const vcpu_instruction& xor_a_l = inst_map[opcode(0xAD)];
			//const vcpu_instruction& xor_a_phl = inst_map[opcode(0xAE)];

			regs.a = 0x00;
			xor_a_a.call(nullptr);
			REQUIRE(!(regs.read_flag(FLAG_CARRY)));
			REQUIRE(!(regs.read_flag(FLAG_HCARRY)));
			REQUIRE(regs.read_flag(FLAG_ZERO));
			REQUIRE(!(regs.read_flag(FLAG_SUB)));

			regs.a = 0xFF;
			xor_a_a.call(nullptr);
			REQUIRE(!(regs.read_flag(FLAG_CARRY)));
			REQUIRE(!(regs.read_flag(FLAG_HCARRY)));
			REQUIRE(regs.read_flag(FLAG_ZERO));
			REQUIRE(!(regs.read_flag(FLAG_SUB)));

			regs.a = 0xDA;
			regs.b = 0xAA;
			xor_a_b.call(nullptr);
			REQUIRE(!(regs.read_flag(FLAG_CARRY)));
			REQUIRE(!(regs.read_flag(FLAG_HCARRY)));
			REQUIRE(!(regs.read_flag(FLAG_ZERO)));
			REQUIRE(!(regs.read_flag(FLAG_SUB)));

			regs.a = 0xAA;
			regs.b = 0xAA;
			xor_a_b.call(nullptr);
			REQUIRE(!(regs.read_flag(FLAG_CARRY)));
			REQUIRE(!(regs.read_flag(FLAG_HCARRY)));
			REQUIRE(regs.read_flag(FLAG_ZERO));
			REQUIRE(!(regs.read_flag(FLAG_SUB)));
		}
	};
}