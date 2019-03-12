#include <catch2/catch.hpp>

#include "../../cpufw_test_init.hpp"

namespace sleepy
{
	TEST_CASE("CpuFirmware_BITROT")
	{
		SECTION("RRCA")
		{
			CPUFW_SLEEPY_TESTINIT();

			const vcpu_instruction& rrca = inst_map[opcode(0x0F)];

			regs.a = 0x00;
			rrca.call(nullptr);
			REQUIRE(regs.a == 0x00);			
			REQUIRE(!(regs.read_flag(FLAG_ZERO)));
			REQUIRE(!(regs.read_flag(FLAG_CARRY)));
			REQUIRE(!(regs.read_flag(FLAG_HCARRY)));
			REQUIRE(!(regs.read_flag(FLAG_SUB)));

			regs.a = 0x01;
			rrca.call(nullptr);
			REQUIRE(regs.a == 0x80);
			REQUIRE(!(regs.read_flag(FLAG_ZERO)));
			REQUIRE(regs.read_flag(FLAG_CARRY));
			REQUIRE(!(regs.read_flag(FLAG_HCARRY)));
			REQUIRE(!(regs.read_flag(FLAG_SUB)));

			regs.a = 0x80;
			rrca.call(nullptr);
			REQUIRE(regs.a == 0x40);
			REQUIRE(!(regs.read_flag(FLAG_ZERO)));
			REQUIRE(!(regs.read_flag(FLAG_CARRY)));
			REQUIRE(!(regs.read_flag(FLAG_HCARRY)));
			REQUIRE(!(regs.read_flag(FLAG_SUB)));
		}

		SECTION("RRA")
		{
			CPUFW_SLEEPY_TESTINIT();

			const vcpu_instruction& rra = inst_map[opcode(0x1F)];

			regs.a = 0x00;
			rra.call(nullptr);
			REQUIRE(regs.a == 0x00);
			REQUIRE(!(regs.read_flag(FLAG_ZERO)));
			REQUIRE(!(regs.read_flag(FLAG_CARRY)));
			REQUIRE(!(regs.read_flag(FLAG_HCARRY)));
			REQUIRE(!(regs.read_flag(FLAG_SUB)));

			regs.a = 0x01;
			rra.call(nullptr);
			REQUIRE(regs.a == 0x00);
			REQUIRE(!(regs.read_flag(FLAG_ZERO)));
			REQUIRE(regs.read_flag(FLAG_CARRY));
			REQUIRE(!(regs.read_flag(FLAG_HCARRY)));
			REQUIRE(!(regs.read_flag(FLAG_SUB)));

			regs.a = 0x80;
			rra.call(nullptr);
			REQUIRE(regs.a == 0x40);
			REQUIRE(!(regs.read_flag(FLAG_ZERO)));
			REQUIRE(!(regs.read_flag(FLAG_CARRY)));
			REQUIRE(!(regs.read_flag(FLAG_HCARRY)));
			REQUIRE(!(regs.read_flag(FLAG_SUB)));
		}

		SECTION("RLCA")
		{
			CPUFW_SLEEPY_TESTINIT();

			const vcpu_instruction& rlca = inst_map[opcode(0x07)];

			regs.a = 0x80;
			rlca.call(nullptr);
			REQUIRE(regs.a == 0x01);
			REQUIRE(!(regs.read_flag(FLAG_ZERO)));
			REQUIRE(regs.read_flag(FLAG_CARRY));
			REQUIRE(!(regs.read_flag(FLAG_HCARRY)));
			REQUIRE(!(regs.read_flag(FLAG_SUB)));

			regs.a = 0x00;
			rlca.call(nullptr);
			REQUIRE(regs.a == 0x00);
			REQUIRE(!(regs.read_flag(FLAG_ZERO)));
			REQUIRE(!(regs.read_flag(FLAG_CARRY)));
			REQUIRE(!(regs.read_flag(FLAG_HCARRY)));
			REQUIRE(!(regs.read_flag(FLAG_SUB)));

			regs.a = 0x01;
			rlca.call(nullptr);
			REQUIRE(regs.a == 0x02);
			REQUIRE(!(regs.read_flag(FLAG_ZERO)));
			REQUIRE(!(regs.read_flag(FLAG_CARRY)));
			REQUIRE(!(regs.read_flag(FLAG_HCARRY)));
			REQUIRE(!(regs.read_flag(FLAG_SUB)));
		}

		SECTION("RLA")
		{
			CPUFW_SLEEPY_TESTINIT();

			const vcpu_instruction& rla = inst_map[opcode(0x17)];

			regs.a = 0x80;
			rla.call(nullptr);
			REQUIRE(regs.a == 0x00);
			REQUIRE(!(regs.read_flag(FLAG_ZERO)));
			REQUIRE(regs.read_flag(FLAG_CARRY));
			REQUIRE(!(regs.read_flag(FLAG_HCARRY)));
			REQUIRE(!(regs.read_flag(FLAG_SUB)));

			regs.a = 0x00;
			rla.call(nullptr);
			REQUIRE(regs.a == 0x00);
			REQUIRE(!(regs.read_flag(FLAG_ZERO)));
			REQUIRE(!(regs.read_flag(FLAG_CARRY)));
			REQUIRE(!(regs.read_flag(FLAG_HCARRY)));
			REQUIRE(!(regs.read_flag(FLAG_SUB)));

			regs.a = 0x01;
			rla.call(nullptr);
			REQUIRE(regs.a == 0x02);
			REQUIRE(!(regs.read_flag(FLAG_ZERO)));
			REQUIRE(!(regs.read_flag(FLAG_CARRY)));
			REQUIRE(!(regs.read_flag(FLAG_HCARRY)));
			REQUIRE(!(regs.read_flag(FLAG_SUB)));
		}
	}
}