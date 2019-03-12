#include <catch2/catch.hpp>

#include "../../cpufw_test_init.hpp"

namespace sleepy
{
	TEST_CASE("CpuFirmware_ADD_A_V8")
	{
		SECTION("ADD_A_V8_AdditionIsCorrect")
		{
			CPUFW_SLEEPY_TESTINIT();

			const vcpu_instruction& add_a_a = inst_map[opcode(0x87)];
			const vcpu_instruction& add_a_b = inst_map[opcode(0x80)];
			const vcpu_instruction& add_a_c = inst_map[opcode(0x81)];
			const vcpu_instruction& add_a_d = inst_map[opcode(0x82)];
			const vcpu_instruction& add_a_e = inst_map[opcode(0x83)];
			const vcpu_instruction& add_a_h = inst_map[opcode(0x84)];
			const vcpu_instruction& add_a_l = inst_map[opcode(0x85)];
			const vcpu_instruction& add_a_phl = inst_map[opcode(0x86)];
			const vcpu_instruction& add_a_d8 = inst_map[opcode(0xC6)];

			regs.a = 0x0A;
			add_a_a.call(nullptr);
			REQUIRE((0x0A + 0x0A) == regs.a);

			regs.a = 0x0A;
			regs.b = 0x0B;
			add_a_b.call(nullptr);
			REQUIRE((0x0A + 0x0B) == regs.a);

			regs.a = 0x0A;
			regs.c = 0x0C;
			add_a_c.call(nullptr);
			REQUIRE((0x0A + 0x0C) == regs.a);

			regs.a = 0x0A;
			regs.d = 0x0D;
			add_a_d.call(nullptr);
			REQUIRE((0x0A + 0x0D) == regs.a);

			regs.a = 0x0A;
			regs.e = 0x0E;
			add_a_e.call(nullptr);
			REQUIRE((0x0A + 0x0E) == regs.a);

			regs.a = 0x0A;
			regs.h = 0xA0;
			add_a_h.call(nullptr);
			REQUIRE((0x0A + 0xA0) == regs.a);

			regs.a = 0x0A;
			regs.l = 0xAF;
			add_a_l.call(nullptr);
			REQUIRE((0x0A + 0xAF) == regs.a);

			u16 addrHL = 0xF0F0;
			mem.write_byte(addrHL, 0xAA);
			regs.hl(addrHL);
			regs.a = 0x0A;
			add_a_phl.call(nullptr);
			REQUIRE((0x0A + 0xAA) == regs.a);

			u8 v8 = 0xAF;
			regs.a = 0x10;
			add_a_d8.call(&v8);
			REQUIRE((0xAF + 0x10) == regs.a);
		}

		SECTION("ADD_A_V8_OverflowCorrectlyHandled")
		{
			CPUFW_SLEEPY_TESTINIT();

			const vcpu_instruction& add_a_a = inst_map[opcode(0x87)];
			const vcpu_instruction& add_a_b = inst_map[opcode(0x80)];
			const vcpu_instruction& add_a_c = inst_map[opcode(0x81)];
			const vcpu_instruction& add_a_d = inst_map[opcode(0x82)];
			const vcpu_instruction& add_a_e = inst_map[opcode(0x83)];
			const vcpu_instruction& add_a_h = inst_map[opcode(0x84)];
			const vcpu_instruction& add_a_l = inst_map[opcode(0x85)];
			const vcpu_instruction& add_a_phl = inst_map[opcode(0x86)];
			const vcpu_instruction& add_a_d8 = inst_map[opcode(0xC6)];

            u16 expectedValue = 0x00;

			regs.a = 0xF0;
			add_a_a.call(nullptr);
			expectedValue = 0xF0 + 0xF0;
			REQUIRE(U8(expectedValue) == regs.a);

			regs.a = 0xF0;
			regs.b = 0x0B;
			add_a_b.call(nullptr);
			expectedValue = 0xF0 + 0x0B;
			REQUIRE(U8(expectedValue) == regs.a);

			regs.a = 0xF0;
			regs.c = 0x0C;
			add_a_c.call(nullptr);
			expectedValue = 0xF0 + 0x0C;
			REQUIRE(U8(expectedValue) == regs.a);

			regs.a = 0xF0;
			regs.d = 0x0D;
			add_a_d.call(nullptr);
			expectedValue = 0xF0 + 0x0D;
			REQUIRE(U8(expectedValue) == regs.a);

			regs.a = 0xF0;
			regs.e = 0x0E;
			add_a_e.call(nullptr);
			expectedValue = 0xF0 + 0x0E;
			REQUIRE(U8(expectedValue) == regs.a);

			regs.a = 0xF0;
			regs.h = 0x0F;
			add_a_h.call(nullptr);
			expectedValue = 0xF0 + 0x0F;
			REQUIRE(U8(expectedValue) == regs.a);

			regs.a = 0xF0;
			regs.l = 0xFF;
			add_a_l.call(nullptr);
			expectedValue = 0xF0 + 0xFF;
			REQUIRE(U8(expectedValue) == regs.a);

			u16 addrHL = 0xF0F0;
			mem.write_byte(addrHL, 0xFA);
			regs.hl(addrHL);
			regs.a = 0xF0;
			add_a_phl.call(nullptr);
			expectedValue = 0xF0 + 0xFA;
			REQUIRE(U8(expectedValue) == regs.a);

			u8 v8 = 0xFF;
			regs.a = 0x10;
			add_a_d8.call(&v8);
            expectedValue = 0xFF + 0x10;
			REQUIRE(U8(expectedValue) == regs.a);
		}

		SECTION("ADD_A_V8_FlagsAreCorrect")
		{
			CPUFW_SLEEPY_TESTINIT();

			const vcpu_instruction& add_a_a = inst_map[opcode(0x87)];
			const vcpu_instruction& add_a_b = inst_map[opcode(0x80)];
			//const vcpu_instruction& add_a_c = inst_map[opcode(0x81)];
			//const vcpu_instruction& add_a_d = inst_map[opcode(0x82)];
			//const vcpu_instruction& add_a_e = inst_map[opcode(0x83)];
			//const vcpu_instruction& add_a_h = inst_map[opcode(0x84)];
			//const vcpu_instruction& add_a_l = inst_map[opcode(0x85)];
			//const vcpu_instruction& add_a_phl = inst_map[opcode(0x86)];

			// Zero add zero sets only flag_zero
			regs.reset_flags();
			regs.a = 0x00;
			add_a_a.call(nullptr);
			REQUIRE(regs.read_flag(FLAG_ZERO));
			REQUIRE(!(regs.read_flag(FLAG_SUB)));
			REQUIRE(!(regs.read_flag(FLAG_HCARRY)));
			REQUIRE(!(regs.read_flag(FLAG_CARRY)));

			// 1 + 1 sets no flags
			regs.reset_flags();
			regs.a = 0x01;
			add_a_a.call(nullptr);
			REQUIRE(!(regs.read_flag(FLAG_ZERO)));
			REQUIRE(!(regs.read_flag(FLAG_SUB)));
			REQUIRE(!(regs.read_flag(FLAG_HCARRY)));
			REQUIRE(!(regs.read_flag(FLAG_CARRY)));

			// 10 + 10 > 15, sets halfcarry
			regs.reset_flags();
			regs.a = 0x0A;
			add_a_a.call(nullptr);
			REQUIRE(!(regs.read_flag(FLAG_ZERO)));
			REQUIRE(!(regs.read_flag(FLAG_SUB)));
			REQUIRE(regs.read_flag(FLAG_HCARRY));
			REQUIRE(!(regs.read_flag(FLAG_CARRY)));

			// 160 + 160 > 255, sets halfcarry and carry
			regs.reset_flags();
			regs.a = 0xA0;
			add_a_a.call(nullptr);
			REQUIRE(!(regs.read_flag(FLAG_ZERO)));
			REQUIRE(!(regs.read_flag(FLAG_SUB)));
			REQUIRE(!regs.read_flag(FLAG_HCARRY));
			REQUIRE(regs.read_flag(FLAG_CARRY));

			// 255 + 1 == 0, sets halfcarry, carry, and zero
			regs.reset_flags();
			regs.a = 0xFF;
			regs.b = 0x01;
			add_a_b.call(nullptr);
			REQUIRE(regs.read_flag(FLAG_ZERO));
			REQUIRE(!(regs.read_flag(FLAG_SUB)));
			REQUIRE(regs.read_flag(FLAG_HCARRY));
			REQUIRE(regs.read_flag(FLAG_CARRY));
		}
	};
}