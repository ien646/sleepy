#include <catch2/catch.hpp>

#include "cpufw_test_init.hpp"

namespace sleepy
{
	TEST_CASE("CpuFirmware_SBC_A_V8")
	{
		SECTION("SBC_A_V8_SubtractionIsCorrect_NoFlags")
		{
			CPUFW_SLEEPY_TESTINIT();

			const vcpu_instruction& sbc_a_a = inst_map[opcode(0x9F)];
			const vcpu_instruction& sbc_a_b = inst_map[opcode(0x98)];
			const vcpu_instruction& sbc_a_c = inst_map[opcode(0x99)];
			const vcpu_instruction& sbc_a_d = inst_map[opcode(0x9A)];
			const vcpu_instruction& sbc_a_e = inst_map[opcode(0x9B)];
			const vcpu_instruction& sbc_a_h = inst_map[opcode(0x9C)];
			const vcpu_instruction& sbc_a_l = inst_map[opcode(0x9D)];
			const vcpu_instruction& sbc_a_phl = inst_map[opcode(0x9E)];
			const vcpu_instruction& sbc_a_d8 = inst_map[opcode(0xDE)];

			regs.reset_flags();
			regs.a = 0xA0;
			sbc_a_a.call(nullptr);
			REQUIRE((0xA0 - 0xA0) == regs.a);

			regs.reset_flags();
			regs.a = 0xA0;
			regs.b = 0x0B;
			sbc_a_b.call(nullptr);
			REQUIRE((0xA0 - 0x0B) == regs.a);

			regs.reset_flags();
			regs.a = 0xA0;
			regs.c = 0x0C;
			sbc_a_c.call(nullptr);
			REQUIRE((0xA0 - 0x0C) == regs.a);

			regs.reset_flags();
			regs.a = 0xA0;
			regs.d = 0x0D;
			sbc_a_d.call(nullptr);
			REQUIRE((0xA0 - 0x0D) == regs.a);

			regs.reset_flags();
			regs.a = 0xA0;
			regs.e = 0x0E;
			sbc_a_e.call(nullptr);
			REQUIRE((0xA0 - 0x0E) == regs.a);

			regs.reset_flags();
			regs.a = 0xA0;
			regs.h = 0x0F;
			sbc_a_h.call(nullptr);
			REQUIRE((0xA0 - 0x0F) == regs.a);

			regs.reset_flags();
			regs.a = 0xA0;
			regs.l = 0x1F;
			sbc_a_l.call(nullptr);
			REQUIRE((0xA0 - 0x1F) == regs.a);

			regs.reset_flags();
			addr_t addrHL = 0xF0F0;
			mem.write_byte(addrHL, 0x22);
			regs.hl(addrHL);
			regs.a = 0xA0;
			sbc_a_phl.call(nullptr);
			REQUIRE((0xA0 - 0x22) == regs.a);

			regs.reset_flags();
			regs.a = 0xA0;
			byte_t d8 = 0x1F;
			sbc_a_d8.call(&d8);
			REQUIRE((0xA0 - 0x1F) == regs.a);
		}

		SECTION("SBC_A_V8_SubtractionIsCorrect_WithFlags")
		{
			CPUFW_SLEEPY_TESTINIT();

			const vcpu_instruction& sbc_a_a = inst_map[opcode(0x9F)];
			const vcpu_instruction& sbc_a_b = inst_map[opcode(0x98)];
			const vcpu_instruction& sbc_a_c = inst_map[opcode(0x99)];
			const vcpu_instruction& sbc_a_d = inst_map[opcode(0x9A)];
			const vcpu_instruction& sbc_a_e = inst_map[opcode(0x9B)];
			const vcpu_instruction& sbc_a_h = inst_map[opcode(0x9C)];
			const vcpu_instruction& sbc_a_l = inst_map[opcode(0x9D)];
			const vcpu_instruction& sbc_a_phl = inst_map[opcode(0x9E)];

			regs.reset_flags();
			regs.set_flag(FLAG_CARRY);
			regs.a = 0x0A;
			sbc_a_a.call(nullptr);
			REQUIRE((byte_t)(0x0A - 0x0A - 1) == regs.a);

			regs.reset_flags();
			regs.set_flag(FLAG_CARRY);
			regs.a = 0x0A;
			regs.b = 0x0B;
			sbc_a_b.call(nullptr);
			REQUIRE((byte_t)(0x0A - 0x0B - 1) == regs.a);

			regs.reset_flags();
			regs.set_flag(FLAG_CARRY);
			regs.a = 0x0A;
			regs.c = 0x0C;
			sbc_a_c.call(nullptr);
			REQUIRE((byte_t)(0x0A - 0x0C - 1) == regs.a);

			regs.reset_flags();
			regs.set_flag(FLAG_CARRY);
			regs.a = 0x0A;
			regs.d = 0x0D;
			sbc_a_d.call(nullptr);
			REQUIRE((byte_t)(0x0A - 0x0D - 1) == regs.a);

			regs.reset_flags();
			regs.set_flag(FLAG_CARRY);
			regs.a = 0x0A;
			regs.e = 0x0E;
			sbc_a_e.call(nullptr);
			REQUIRE((byte_t)(0x0A - 0x0E - 1) == regs.a);

			regs.reset_flags();
			regs.set_flag(FLAG_CARRY);
			regs.a = 0x0A;
			regs.h = 0xA0;
			sbc_a_h.call(nullptr);
			REQUIRE((byte_t)(0x0A - 0xA0 - 1) == regs.a);

			regs.reset_flags();
			regs.set_flag(FLAG_CARRY);
			regs.a = 0x0A;
			regs.l = 0xAF;
			sbc_a_l.call(nullptr);
			REQUIRE((byte_t)(0x0A - 0xAF - 1) == regs.a);

			regs.reset_flags();
			regs.set_flag(FLAG_CARRY);
			addr_t addrHL = 0xF0F0;
			mem.write_byte(addrHL, 0xAA);
			regs.hl(addrHL);
			regs.a = 0x0A;
			sbc_a_phl.call(nullptr);
			REQUIRE((byte_t)(0x0A - 0xAA - 1) == regs.a);
		}

		SECTION("SBC_A_V8_FlagsAreCorrect")
		{
			CPUFW_SLEEPY_TESTINIT();

			const vcpu_instruction& sbc_a_a = inst_map[opcode(0x9F)];
			const vcpu_instruction& sbc_a_b = inst_map[opcode(0x98)];
			const vcpu_instruction& sbc_a_c = inst_map[opcode(0x99)];
			const vcpu_instruction& sbc_a_d = inst_map[opcode(0x9A)];
			const vcpu_instruction& sbc_a_e = inst_map[opcode(0x9B)];
			const vcpu_instruction& sbc_a_h = inst_map[opcode(0x9C)];
			const vcpu_instruction& sbc_a_l = inst_map[opcode(0x9D)];
			const vcpu_instruction& sbc_a_phl = inst_map[opcode(0x9E)];

			regs.reset_flags();

			regs.reset_flag(FLAG_CARRY);
			regs.a = 0x00;
			sbc_a_a.call(nullptr);
			REQUIRE(regs.read_flag(FLAG_ZERO));
			REQUIRE(!(regs.read_flag(FLAG_HCARRY)));
			REQUIRE(!(regs.read_flag(FLAG_CARRY)));
			REQUIRE(regs.read_flag(FLAG_SUB));

			regs.set_flag(FLAG_CARRY);
			regs.a = 0x00;
			sbc_a_a.call(nullptr);
			REQUIRE(!(regs.read_flag(FLAG_ZERO)));
			REQUIRE(regs.read_flag(FLAG_HCARRY));
			REQUIRE(regs.read_flag(FLAG_CARRY));
			REQUIRE(regs.read_flag(FLAG_SUB));

			regs.reset_flag(FLAG_CARRY);
			regs.a = 0x10;
			regs.b = 0x01;
			sbc_a_b.call(nullptr);
			REQUIRE(!(regs.read_flag(FLAG_ZERO)));
			REQUIRE(!(regs.read_flag(FLAG_HCARRY)));
			REQUIRE(!(regs.read_flag(FLAG_CARRY)));
			REQUIRE(regs.read_flag(FLAG_SUB));

			regs.set_flag(FLAG_CARRY);
			regs.a = 0xFF;
			regs.b = 0x10;
			sbc_a_b.call(nullptr);
			REQUIRE(!(regs.read_flag(FLAG_ZERO)));
			REQUIRE(regs.read_flag(FLAG_HCARRY));
			REQUIRE(!(regs.read_flag(FLAG_CARRY)));
			REQUIRE(regs.read_flag(FLAG_SUB));

			regs.reset_flag(FLAG_CARRY);
			regs.a = 0xFF;
			regs.b = 0x00;
			sbc_a_b.call(nullptr);
			REQUIRE(!(regs.read_flag(FLAG_ZERO)));
			REQUIRE(regs.read_flag(FLAG_HCARRY));
			REQUIRE(!(regs.read_flag(FLAG_CARRY)));
			REQUIRE(regs.read_flag(FLAG_SUB));

			regs.set_flag(FLAG_CARRY);
			regs.a = 0x00;
			regs.b = 0x00;
			sbc_a_b.call(nullptr);
			REQUIRE(!(regs.read_flag(FLAG_ZERO)));
			REQUIRE(regs.read_flag(FLAG_HCARRY));
			REQUIRE(regs.read_flag(FLAG_CARRY));
			REQUIRE(regs.read_flag(FLAG_SUB));
		}
	};
}