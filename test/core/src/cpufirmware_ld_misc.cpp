#include <catch2/catch.hpp>

#include "cpufw_test_init.hpp"

namespace sleepy
{
	TEST_CASE("CpuFirmware_LD_Misc")
	{
		SECTION("LD_pFF00C_A")
		{
			CPUFW_SLEEPY_TESTINIT();

			const vcpu_instruction& ld_pff00c_a = inst_map[opcode(0xE2)];

			regs.a = 0xAA;
			regs.c = 0x00;
			ld_pff00c_a.call(nullptr);
			REQUIRE(mem.read_byte(0xFF00 + 0x00) == 0xAA);

			regs.a = 0xAB;
			regs.c = 0x01;
			ld_pff00c_a.call(nullptr);
			REQUIRE(mem.read_byte(0xFF00 + 0x01) == 0xAB);

			regs.a = 0xCA;
			regs.c = 0x10;
			ld_pff00c_a.call(nullptr);
			REQUIRE(mem.read_byte(0xFF00 + 0x10) == 0xCA);

			regs.a = 0x1F;
			regs.c = 0xFF;
			ld_pff00c_a.call(nullptr);
			REQUIRE(mem.read_byte(0xFFFF) == 0x1F);
		}

		SECTION("LD_A_pFF00C")
		{
			CPUFW_SLEEPY_TESTINIT();

			const vcpu_instruction& ld_a_pff00c = inst_map[opcode(0xF2)];

			regs.c = 0x00;
			mem.write_byte(0xFF00 + regs.c, 0xAA);
			ld_a_pff00c.call(nullptr);
			REQUIRE(regs.a == 0xAA);

			regs.c = 0x05;
			mem.write_byte(0xFF00 + regs.c, 0xBB);
			ld_a_pff00c.call(nullptr);
			REQUIRE(regs.a == 0xBB);

			regs.c = 0x10;
			mem.write_byte(0xFF00 + regs.c, 0xCC);
			ld_a_pff00c.call(nullptr);
			REQUIRE(regs.a == 0xCC);

			regs.c = 0xFF;
			mem.write_byte(0xFF00 + regs.c, 0xDD);
			ld_a_pff00c.call(nullptr);
			REQUIRE(regs.a == 0xDD);
		}

		SECTION("LD_d16_SP")
		{
			CPUFW_SLEEPY_TESTINIT();

			const vcpu_instruction& ld_d16_sp = inst_map[opcode(0x08)];

			word_t val = 0xFAA7;
			word_t args = 0xADD3;

			regs.sp = val;
			ld_d16_sp.call((byte_t*)&args);
			REQUIRE(mem.read_word(args) == val);
		}

		SECTION("LD_HL_SPd8")
		{
			CPUFW_SLEEPY_TESTINIT();

			const vcpu_instruction& ld_hl_spd8 = inst_map[opcode(0xF8)];
			byte_t d8 = 0x00;

			regs.sp = 0xAAAA;
			d8 = 0xBB;
			ld_hl_spd8.call(&d8);
			REQUIRE(regs.hl() == (word_t)(0xAAAA + 0xBB));

			regs.reset_flags();
			regs.sp = 0x0000;
			d8 = HBYTE_MAX;
			ld_hl_spd8.call(&d8);
			REQUIRE(!(regs.read_flag(FLAG_ZERO)));
			REQUIRE(!(regs.read_flag(FLAG_SUB)));
			REQUIRE(!(regs.read_flag(FLAG_HCARRY)));
			REQUIRE(!(regs.read_flag(FLAG_CARRY)));

			regs.reset_flags();
			regs.sp = 0x0001;
			d8 = HBYTE_MAX;
			ld_hl_spd8.call(&d8);
			REQUIRE(!(regs.read_flag(FLAG_ZERO)));
			REQUIRE(!(regs.read_flag(FLAG_SUB)));
			REQUIRE(regs.read_flag(FLAG_HCARRY));
			REQUIRE(!(regs.read_flag(FLAG_CARRY)));

			regs.reset_flags();
			regs.sp = 0x00F0;
			d8 = HBYTE_MAX;
			ld_hl_spd8.call(&d8);
			REQUIRE(!(regs.read_flag(FLAG_ZERO)));
			REQUIRE(!(regs.read_flag(FLAG_SUB)));
			REQUIRE(regs.read_flag(FLAG_HCARRY));
			REQUIRE(!(regs.read_flag(FLAG_CARRY)));

			regs.reset_flags();
			regs.sp = 0x00F1;
			d8 = HBYTE_MAX;
			ld_hl_spd8.call(&d8);
			REQUIRE(!(regs.read_flag(FLAG_ZERO)));
			REQUIRE(!(regs.read_flag(FLAG_SUB)));
			REQUIRE(regs.read_flag(FLAG_HCARRY));
			REQUIRE(regs.read_flag(FLAG_CARRY));

			regs.reset_flags();
			regs.sp = 0xFFF1;
			d8 = HBYTE_MAX;
			ld_hl_spd8.call(&d8);
			REQUIRE(regs.hl() == 0x0000);
			REQUIRE(!(regs.read_flag(FLAG_ZERO)));
			REQUIRE(!(regs.read_flag(FLAG_SUB)));
			REQUIRE(regs.read_flag(FLAG_HCARRY));
			REQUIRE(regs.read_flag(FLAG_CARRY));
		}

		SECTION("LD_a16_A")
		{
			CPUFW_SLEEPY_TESTINIT();
			const vcpu_instruction& ld_a16_a = inst_map[opcode(0xEA)];
			addr_t a16 = 0x0000;

			regs.a = 0x00;
			a16 = 0xBEBA;
			ld_a16_a.call((byte_t*)&a16);
			REQUIRE(mem.read_byte(a16) == 0x00);

			regs.a = 0xCC;
			a16 = 0xACAC;
			ld_a16_a.call((byte_t*)&a16);
			REQUIRE(mem.read_byte(a16) == 0xCC);
		}

		SECTION("LD_A_a16")
		{
			CPUFW_SLEEPY_TESTINIT();
			const vcpu_instruction& ld_a_a16 = inst_map[opcode(0xFA)];

			addr_t a16 = 0x0000;
			byte_t val = 0x00;

			a16 = 0x0000;
			val = 0x00;
			mem.write_byte(a16, val);
			ld_a_a16.call((byte_t*)&a16);
			REQUIRE(regs.a == val);

			a16 = 0x1111;
			val = 0x21;
			mem.write_byte(a16, val);
			ld_a_a16.call((byte_t*)&a16);
			REQUIRE(regs.a == val);

			a16 = 0xFFFF;
			val = 0xAF;
			mem.write_byte(a16, val);
			ld_a_a16.call((byte_t*)&a16);
			REQUIRE(regs.a == val);
		}

		SECTION("LD_SP_HL")
		{
			CPUFW_SLEEPY_TESTINIT();
			const vcpu_instruction& ld_sp_hl = inst_map[opcode(0xF9)];

			regs.sp = 0xA0AB;
			regs.hl(0xFEFE);
			ld_sp_hl.call(nullptr);
			REQUIRE(regs.sp == 0xFEFE);

			regs.sp = 0xBA0F;
			regs.hl(0x0F13);
			ld_sp_hl.call(nullptr);
			REQUIRE(regs.sp == 0x0F13);
		}

		SECTION("LD_pFF00a8_A")
		{
			CPUFW_SLEEPY_TESTINIT();
			const vcpu_instruction& ld_pff00a8_a = inst_map[opcode(0xE0)];

			byte_t a8 = 0x00;
			addr_t addr = 0x0000;

			a8 = 0x33;
			addr = 0xFF00 + a8;
			regs.a = 0xAB;
			ld_pff00a8_a.call(&a8);
			REQUIRE(mem.read_byte(addr) == 0xAB);

			a8 = 0xFF;
			addr = 0xFF00 + a8;
			regs.a = 0x12;
			ld_pff00a8_a.call(&a8);
			REQUIRE(mem.read_byte(addr) == 0x12);
		}

		SECTION("LD_A_pFF00a8")
		{
			CPUFW_SLEEPY_TESTINIT();
			const vcpu_instruction& ld_pff00a8_a = inst_map[opcode(0xF0)];

			byte_t a8 = 0x00;
			addr_t addr = 0x0000;

			a8 = 0x33;
			addr = 0xFF00 + a8;
			mem.write_byte(addr, 0x55);
			regs.a = 0x00;
			ld_pff00a8_a.call(&a8);
			REQUIRE(regs.a == 0x55);

			a8 = 0x33;
			addr = 0xFF00 + a8;
			mem.write_byte(addr, 0x55);
			regs.a = 0x00;
			ld_pff00a8_a.call(&a8);
			REQUIRE(regs.a == 0x55);
		}
	};
}