#include <catch2/catch.hpp>

#include "../../cpufw_test_init.hpp"

namespace sleepy
{
	TEST_CASE("CpuFirmware_ADD_HL_V16")
	{
		SECTION("ADD_HL_V16_AdditionIsCorrect")
		{
			CPUFW_SLEEPY_TESTINIT();

			const vcpu_instruction& add_hl_bc = inst_map[opcode(0x09)];
			const vcpu_instruction& add_hl_de = inst_map[opcode(0x19)];
			const vcpu_instruction& add_hl_hl = inst_map[opcode(0x29)];
			const vcpu_instruction& add_hl_sp = inst_map[opcode(0x39)];

			regs.hl(0x1100);
			regs.bc(0x00BC);
			add_hl_bc.call(nullptr);
			REQUIRE(regs.hl() == U16(0x1100 + 0x00BC));

			regs.hl(0x2200);
			regs.de(0x00DE);
			add_hl_de.call(nullptr);
			REQUIRE(regs.hl() == U16(0x2200 + 0x00DE));

			regs.hl(0x2200);
			add_hl_hl.call(nullptr);
			REQUIRE(regs.hl() == U16(0x2200 + 0x2200));

			regs.hl(0x4444);
			regs.sp = (0x0055);
			add_hl_sp.call(nullptr);
			REQUIRE(regs.hl() == U16(0x4444 + 0x0055));
		}

		SECTION("ADD_HL_V16_OverflowingIsCorrect")
		{
			CPUFW_SLEEPY_TESTINIT();

			const vcpu_instruction& add_hl_bc = inst_map[opcode(0x09)];
			const vcpu_instruction& add_hl_de = inst_map[opcode(0x19)];
			const vcpu_instruction& add_hl_hl = inst_map[opcode(0x29)];
			const vcpu_instruction& add_hl_sp = inst_map[opcode(0x39)];

			regs.hl(0xFF00);
			regs.bc(0x1111);
			add_hl_bc.call(nullptr);
            u32 expected = 0xFF00 + 0x1111;
			REQUIRE(regs.hl() == U16(expected));

			regs.hl(0xFF44);
			regs.de(0x1DDD);
			add_hl_de.call(nullptr);
            expected = 0xFF44 + 0x1DDD;
            REQUIRE(regs.hl() == U16(expected));

			regs.hl(0xDDDD);
			add_hl_hl.call(nullptr);
            expected = 0xDDDD + 0xDDDD;
            REQUIRE(regs.hl() == U16(expected));

			regs.hl(0xEEEE);
			regs.sp = (0x2222);
			add_hl_sp.call(nullptr);
            expected = 0xEEEE + 0x2222;
			REQUIRE(regs.hl() == U16(expected));
		}

		SECTION("ADD_HL_V16_FlagsAreCorrect")
		{
			CPUFW_SLEEPY_TESTINIT();

			const vcpu_instruction& add_hl_bc = inst_map[opcode(0x09)];
			//const vcpu_instruction& add_hl_de = inst_map[opcode(0x19)];
			//const vcpu_instruction& add_hl_hl = inst_map[opcode(0x29)];
			//const vcpu_instruction& add_hl_sp = inst_map[opcode(0x39)];

			regs.reset_flags();
			regs.hl(0x0000);
			regs.bc(0x0000);
			add_hl_bc.call(nullptr);
			REQUIRE(!(regs.read_flag(FLAG_CARRY)));
			REQUIRE(!(regs.read_flag(FLAG_HCARRY)));
			REQUIRE(!(regs.read_flag(FLAG_SUB)));
			REQUIRE(!(regs.read_flag(FLAG_ZERO)));

			regs.reset_flags();
			regs.hl(0x00FF);
			regs.bc(0x0001);
			add_hl_bc.call(nullptr);
			REQUIRE(!(regs.read_flag(FLAG_CARRY)));
			REQUIRE(!regs.read_flag(FLAG_HCARRY));
			REQUIRE(!(regs.read_flag(FLAG_SUB)));
			REQUIRE(!(regs.read_flag(FLAG_ZERO)));

			regs.reset_flags();
			regs.hl(0xFFFF);
			regs.bc(0x0001);
			add_hl_bc.call(nullptr);
			REQUIRE(regs.read_flag(FLAG_CARRY));
			REQUIRE(!regs.read_flag(FLAG_HCARRY));
			REQUIRE(!(regs.read_flag(FLAG_SUB)));
			REQUIRE(!(regs.read_flag(FLAG_ZERO)));

			regs.reset_flags();
			regs.hl(0xFFFF);
			regs.bc(0x0100);
			add_hl_bc.call(nullptr);
			REQUIRE(regs.read_flag(FLAG_CARRY));
			REQUIRE(regs.read_flag(FLAG_HCARRY));
			REQUIRE(!(regs.read_flag(FLAG_SUB)));
			REQUIRE(!(regs.read_flag(FLAG_ZERO)));
		}
	}
}