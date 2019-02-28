#include <catch2/catch.hpp>

#include "cpufw_test_init.hpp"

namespace sleepy
{
	TEST_CASE("CpuFirmware_SUB_A_V8")
	{
		SECTION("SUB_A_V8_SubtractionIsCorrect")
		{
			CPUFW_SLEEPY_TESTINIT();

			const vcpu_instruction& sub_a_a = inst_map[opcode(0x97)];
			const vcpu_instruction& sub_a_b = inst_map[opcode(0x90)];
			const vcpu_instruction& sub_a_c = inst_map[opcode(0x91)];
			const vcpu_instruction& sub_a_d = inst_map[opcode(0x92)];
			const vcpu_instruction& sub_a_e = inst_map[opcode(0x93)];
			const vcpu_instruction& sub_a_h = inst_map[opcode(0x94)];
			const vcpu_instruction& sub_a_l = inst_map[opcode(0x95)];
			const vcpu_instruction& sub_a_phl = inst_map[opcode(0x96)];
			const vcpu_instruction& sub_a_d8 = inst_map[opcode(0xD6)];

			byte_t expectedValue = 0x00;

			regs.a = 0xFA;
			sub_a_a.call(nullptr);
			expectedValue = (byte_t)(0xFA - 0xFA);
			REQUIRE(expectedValue == regs.a);

			regs.a = 0xFA;
			regs.b = 0x0B;
			sub_a_b.call(nullptr);
			expectedValue = (byte_t)(0xFA - 0x0B);
			REQUIRE(expectedValue == regs.a);

			regs.a = 0xFA;
			regs.c = 0x0C;
			sub_a_c.call(nullptr);
			expectedValue = (byte_t)(0xFA - 0x0C);
			REQUIRE(expectedValue == regs.a);

			regs.a = 0xFA;
			regs.d = 0x0D;
			sub_a_d.call(nullptr);
			expectedValue = (byte_t)(0xFA - 0x0D);
			REQUIRE(expectedValue == regs.a);

			regs.a = 0xFA;
			regs.e = 0x0E;
			sub_a_e.call(nullptr);
			expectedValue = (byte_t)(0xFA - 0x0E);
			REQUIRE(expectedValue == regs.a);

			regs.a = 0xFA;
			regs.h = 0xA0;
			sub_a_h.call(nullptr);
			expectedValue = (byte_t)(0xFA - 0xA0);
			REQUIRE(expectedValue == regs.a);

			regs.a = 0xFA;
			regs.l = 0xAF;
			sub_a_l.call(nullptr);
			expectedValue = (byte_t)(0xFA - 0xAF);
			REQUIRE(expectedValue == regs.a);

			addr_t addrHL = 0xF0F0;
			mem.write_byte(addrHL, 0xAA);
			regs.hl(addrHL);
			regs.a = 0xFA;
			sub_a_phl.call(nullptr);
			expectedValue = (byte_t)(0xFA - 0xAA);
			REQUIRE(expectedValue == regs.a);

			regs.a = 0xFA;
			byte_t d8 = 0xAF;
			sub_a_d8.call(&d8);
			expectedValue = (byte_t)(0xFA - 0xAF);
			REQUIRE(expectedValue == regs.a);
		}		

		SECTION("SUB_A_V8_UnderflowCorrectlyHandled")
		{
			CPUFW_SLEEPY_TESTINIT();

			const vcpu_instruction& sub_a_a = inst_map[opcode(0x97)];
			const vcpu_instruction& sub_a_b = inst_map[opcode(0x90)];
			const vcpu_instruction& sub_a_c = inst_map[opcode(0x91)];
			const vcpu_instruction& sub_a_d = inst_map[opcode(0x92)];
			const vcpu_instruction& sub_a_e = inst_map[opcode(0x93)];
			const vcpu_instruction& sub_a_h = inst_map[opcode(0x94)];
			const vcpu_instruction& sub_a_l = inst_map[opcode(0x95)];
			const vcpu_instruction& sub_a_phl = inst_map[opcode(0x96)];
			const vcpu_instruction& sub_a_d8 = inst_map[opcode(0xD6)];

			byte_t expectedValue = 0x00;

			regs.a = 0xFA;
			sub_a_a.call(nullptr);
			expectedValue = (byte_t)(0xFA - 0xFA);
			REQUIRE(expectedValue == regs.a);

			regs.a = 0xFA;
			regs.b = 0xFF;
			sub_a_b.call(nullptr);
			expectedValue = (byte_t)(0xFA - 0xFF);
			REQUIRE(expectedValue == regs.a);

			regs.a = 0xFA;
			regs.c = 0xFF;
			sub_a_c.call(nullptr);
			expectedValue = (byte_t)(0xFA - 0xFF);
			REQUIRE(expectedValue == regs.a);

			regs.a = 0xFA;
			regs.d = 0xFF;
			sub_a_d.call(nullptr);
			expectedValue = (byte_t)(0xFA - 0xFF);
			REQUIRE(expectedValue == regs.a);

			regs.a = 0xFA;
			regs.e = 0xFF;
			sub_a_e.call(nullptr);
			expectedValue = (byte_t)(0xFA - 0xFF);
			REQUIRE(expectedValue == regs.a);

			regs.a = 0xFA;
			regs.h = 0xFF;
			sub_a_h.call(nullptr);
			expectedValue = (byte_t)(0xFA - 0xFF);
			REQUIRE(expectedValue == regs.a);

			regs.a = 0xFA;
			regs.l = 0xFF;
			sub_a_l.call(nullptr);
			expectedValue = (byte_t)(0xFA - 0xFF);
			REQUIRE(expectedValue == regs.a);

			addr_t addrHL = 0xF0F0;
			mem.write_byte(addrHL, 0xFF);
			regs.hl(addrHL);
			regs.a = 0xFA;
			sub_a_phl.call(nullptr);
			expectedValue = (byte_t)(0xFA - 0xFF);
			REQUIRE(expectedValue == regs.a);

			regs.a = 0xFA;
			byte_t d8 = 0xFF;
			sub_a_d8.call(&d8);
			expectedValue = (byte_t)(0xFA - 0xFF);
			REQUIRE(expectedValue == regs.a);
		}

		SECTION("SUB_A_V8_FlagsAreCorrect")
		{
			CPUFW_SLEEPY_TESTINIT();

			const vcpu_instruction& sub_a_a = inst_map[opcode(0x97)];
			const vcpu_instruction& sub_a_b = inst_map[opcode(0x90)];
			const vcpu_instruction& sub_a_c = inst_map[opcode(0x91)];
			const vcpu_instruction& sub_a_d = inst_map[opcode(0x92)];
			const vcpu_instruction& sub_a_e = inst_map[opcode(0x93)];
			const vcpu_instruction& sub_a_h = inst_map[opcode(0x94)];
			const vcpu_instruction& sub_a_l = inst_map[opcode(0x95)];
			const vcpu_instruction& sub_a_phl = inst_map[opcode(0x96)];

			regs.a = 0x00;
			sub_a_a.call(nullptr);
			REQUIRE(regs.read_flag(FLAG_SUB));
			REQUIRE(regs.read_flag(FLAG_ZERO));
			REQUIRE(!(regs.read_flag(FLAG_HCARRY)));
			REQUIRE(!(regs.read_flag(FLAG_CARRY)));

			regs.a = 0x00;
			regs.b = 0x01;
			sub_a_b.call(nullptr);
			REQUIRE(regs.read_flag(FLAG_SUB));
			REQUIRE(!(regs.read_flag(FLAG_ZERO)));
			REQUIRE(regs.read_flag(FLAG_HCARRY));
			REQUIRE(regs.read_flag(FLAG_CARRY));

			regs.a = 0x10;
			regs.b = 0x01;
			sub_a_b.call(nullptr);
			REQUIRE(regs.read_flag(FLAG_SUB));
			REQUIRE(!(regs.read_flag(FLAG_ZERO)));
			REQUIRE(!(regs.read_flag(FLAG_HCARRY)));
			REQUIRE(!(regs.read_flag(FLAG_CARRY)));

			regs.a = 0x11;
			regs.b = 0x01;
			sub_a_b.call(nullptr);
			REQUIRE(regs.read_flag(FLAG_SUB));
			REQUIRE(!(regs.read_flag(FLAG_ZERO)));
			REQUIRE(regs.read_flag(FLAG_HCARRY));
			REQUIRE(!(regs.read_flag(FLAG_CARRY)));
		}
	};
}