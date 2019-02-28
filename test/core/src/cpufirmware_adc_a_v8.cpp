#include <catch2/catch.hpp>

#include "cpufw_test_init.hpp"

namespace sleepy
{
	TEST_CASE("CpuFirmware_ADC_A_V8")
	{
		SECTION("ADC_A_V8_AdditionIsCorrect_NoFlags")
		{
			CPUFW_SLEEPY_TESTINIT();

			const vcpu_instruction& adc_a_a = inst_map[opcode(0x8F)];
			const vcpu_instruction& adc_a_b = inst_map[opcode(0x88)];
			const vcpu_instruction& adc_a_c = inst_map[opcode(0x89)];
			const vcpu_instruction& adc_a_d = inst_map[opcode(0x8A)];
			const vcpu_instruction& adc_a_e = inst_map[opcode(0x8B)];
			const vcpu_instruction& adc_a_h = inst_map[opcode(0x8C)];
			const vcpu_instruction& adc_a_l = inst_map[opcode(0x8D)];
			const vcpu_instruction& adc_a_phl = inst_map[opcode(0x8E)];
			const vcpu_instruction& adc_a_d8 = inst_map[opcode(0xCE)];

			regs.reset_flags();
			regs.a = 0x0A;
			adc_a_a.call(nullptr);
			REQUIRE((0x0A + 0x0A) == regs.a);

			regs.reset_flags();
			regs.a = 0x0A;
			regs.b = 0x0B;
			adc_a_b.call(nullptr);
			REQUIRE((0x0A + 0x0B) == regs.a);

			regs.reset_flags();
			regs.a = 0x0A;
			regs.c = 0x0C;
			adc_a_c.call(nullptr);
			REQUIRE((0x0A + 0x0C) == regs.a);

			regs.reset_flags();
			regs.a = 0x0A;
			regs.d = 0x0D;
			adc_a_d.call(nullptr);
			REQUIRE((0x0A + 0x0D) == regs.a);

			regs.reset_flags();
			regs.a = 0x0A;
			regs.e = 0x0E;
			adc_a_e.call(nullptr);
			REQUIRE((0x0A + 0x0E) == regs.a);

			regs.reset_flags();
			regs.a = 0x0A;
			regs.h = 0xA0;
			adc_a_h.call(nullptr);
			REQUIRE((0x0A + 0xA0) == regs.a);

			regs.reset_flags();
			regs.a = 0x0A;
			regs.l = 0xAF;
			adc_a_l.call(nullptr);
			REQUIRE((0x0A + 0xAF) == regs.a);

			regs.reset_flags();
			addr_t addrHL = 0xF0F0;
			mem.write_byte(addrHL, 0xAA);
			regs.hl(addrHL);
			regs.a = 0x0A;
			adc_a_phl.call(nullptr);
			REQUIRE((0x0A + 0xAA) == regs.a);

			regs.reset_flags();
			regs.a = 0x0A;
			byte_t d8 = 0x0B;
			adc_a_d8.call(&d8);
			REQUIRE(regs.a == (d8 + 0x0A));
		}

		SECTION("ADC_A_V8_AdditionIsCorrect_WithFlags")
		{
			CPUFW_SLEEPY_TESTINIT();

			const vcpu_instruction& adc_a_a = inst_map[opcode(0x8F)];
			const vcpu_instruction& adc_a_b = inst_map[opcode(0x88)];
			const vcpu_instruction& adc_a_c = inst_map[opcode(0x89)];
			const vcpu_instruction& adc_a_d = inst_map[opcode(0x8A)];
			const vcpu_instruction& adc_a_e = inst_map[opcode(0x8B)];
			const vcpu_instruction& adc_a_h = inst_map[opcode(0x8C)];
			const vcpu_instruction& adc_a_l = inst_map[opcode(0x8D)];
			const vcpu_instruction& adc_a_phl = inst_map[opcode(0x8E)];

			regs.reset_flags();
			regs.set_flag(FLAG_CARRY);
			regs.a = 0x0A;
			adc_a_a.call(nullptr);
			REQUIRE((0x0A + 0x0A + 1) == regs.a);

			regs.reset_flags();
			regs.set_flag(FLAG_CARRY);
			regs.a = 0x0A;
			regs.b = 0x0B;
			adc_a_b.call(nullptr);
			REQUIRE((0x0A + 0x0B + 1) == regs.a);

			regs.reset_flags();
			regs.set_flag(FLAG_CARRY);
			regs.a = 0x0A;
			regs.c = 0x0C;
			adc_a_c.call(nullptr);
			REQUIRE((0x0A + 0x0C + 1) == regs.a);

			regs.reset_flags();
			regs.set_flag(FLAG_CARRY);
			regs.a = 0x0A;
			regs.d = 0x0D;
			adc_a_d.call(nullptr);
			REQUIRE((0x0A + 0x0D + 1) == regs.a);

			regs.reset_flags();
			regs.set_flag(FLAG_CARRY);
			regs.a = 0x0A;
			regs.e = 0x0E;
			adc_a_e.call(nullptr);
			REQUIRE((0x0A + 0x0E + 1) == regs.a);

			regs.reset_flags();
			regs.set_flag(FLAG_CARRY);
			regs.a = 0x0A;
			regs.h = 0xA0;
			adc_a_h.call(nullptr);
			REQUIRE((0x0A + 0xA0 + 1) == regs.a);

			regs.reset_flags();
			regs.set_flag(FLAG_CARRY);
			regs.a = 0x0A;
			regs.l = 0xAF;
			adc_a_l.call(nullptr);
			REQUIRE((0x0A + 0xAF + 1) == regs.a);

			regs.reset_flags();
			regs.set_flag(FLAG_CARRY);
			addr_t addrHL = 0xF0F0;
			mem.write_byte(addrHL, 0xAA);
			regs.hl(addrHL);
			regs.a = 0x0A;
			adc_a_phl.call(nullptr);
			REQUIRE((0x0A + 0xAA + 1) == regs.a);
		}

		SECTION("ADC_A_V8_FlagsAreCorrect")
		{
			CPUFW_SLEEPY_TESTINIT();

			const vcpu_instruction& adc_a_a = inst_map[opcode(0x8F)];
			const vcpu_instruction& adc_a_b = inst_map[opcode(0x88)];
			const vcpu_instruction& adc_a_c = inst_map[opcode(0x89)];
			const vcpu_instruction& adc_a_d = inst_map[opcode(0x8A)];
			const vcpu_instruction& adc_a_e = inst_map[opcode(0x8B)];
			const vcpu_instruction& adc_a_h = inst_map[opcode(0x8C)];
			const vcpu_instruction& adc_a_l = inst_map[opcode(0x8D)];
			const vcpu_instruction& adc_a_phl = inst_map[opcode(0x8E)];

			regs.reset_flags();

			regs.reset_flag(FLAG_CARRY);
			regs.a = 0x00;
			adc_a_a.call(nullptr);
			REQUIRE(regs.read_flag(FLAG_ZERO));
			REQUIRE(!(regs.read_flag(FLAG_HCARRY)));
			REQUIRE(!(regs.read_flag(FLAG_CARRY)));
			REQUIRE(!(regs.read_flag(FLAG_SUB)));

			regs.set_flag(FLAG_CARRY);
			regs.a = 0x00;
			adc_a_a.call(nullptr);
			REQUIRE(!(regs.read_flag(FLAG_ZERO)));
			REQUIRE(!(regs.read_flag(FLAG_HCARRY)));
			REQUIRE(!(regs.read_flag(FLAG_CARRY)));
			REQUIRE(!(regs.read_flag(FLAG_SUB)));

			regs.reset_flag(FLAG_CARRY);
			regs.a = 0x0F;
			regs.b = 0x01;
			adc_a_b.call(nullptr);
			REQUIRE(!(regs.read_flag(FLAG_ZERO)));
			REQUIRE(regs.read_flag(FLAG_HCARRY));
			REQUIRE(!(regs.read_flag(FLAG_CARRY)));
			REQUIRE(!(regs.read_flag(FLAG_SUB)));

			regs.set_flag(FLAG_CARRY);
			regs.a = 0x0F;
			regs.b = 0x00;
			adc_a_b.call(nullptr);
			REQUIRE(!(regs.read_flag(FLAG_ZERO)));
			REQUIRE(regs.read_flag(FLAG_HCARRY));
			REQUIRE(!(regs.read_flag(FLAG_CARRY)));
			REQUIRE(!(regs.read_flag(FLAG_SUB)));

			regs.reset_flag(FLAG_CARRY);
			regs.a = 0xFF;
			regs.b = 0x00;
			adc_a_b.call(nullptr);
			REQUIRE(!(regs.read_flag(FLAG_ZERO)));
			REQUIRE(regs.read_flag(FLAG_HCARRY));
			REQUIRE(!(regs.read_flag(FLAG_CARRY)));
			REQUIRE(!(regs.read_flag(FLAG_SUB)));

			regs.set_flag(FLAG_CARRY);
			regs.a = 0xFF;
			regs.b = 0x00;
			adc_a_b.call(nullptr);
			REQUIRE(regs.read_flag(FLAG_ZERO));
			REQUIRE(regs.read_flag(FLAG_HCARRY));
			REQUIRE(regs.read_flag(FLAG_CARRY));
			REQUIRE(!(regs.read_flag(FLAG_SUB)));
		}
	};
}