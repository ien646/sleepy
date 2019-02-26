#include <catch2/catch.hpp>

#include "cpufw_test_init.hpp"

namespace sleepy
{
	TEST_CASE("CpuFirmware_LD_pHL_R8")
	{
		SECTION("LD_pHL_R8")
		{			
			CPUFW_SLEEPY_TESTINIT();

			vcpu_instruction& ld_phl_a = inst_map[opcode(0x77)];
			vcpu_instruction& ld_phl_b = inst_map[opcode(0x70)];
			vcpu_instruction& ld_phl_c = inst_map[opcode(0x71)];
			vcpu_instruction& ld_phl_d = inst_map[opcode(0x72)];
			vcpu_instruction& ld_phl_e = inst_map[opcode(0x73)];
			vcpu_instruction& ld_phl_h = inst_map[opcode(0x74)];
			vcpu_instruction& ld_phl_l = inst_map[opcode(0x75)];

			addr_t phlAddr = 0xDA0F;

			// A
			regs.hl(phlAddr);
			regs.a = 0xA0;
			ld_phl_a.call(nullptr);
			REQUIRE(mem.read_byte(phlAddr) == 0xA0);

			// B
			regs.hl(phlAddr);
			regs.b = 0xB0;
			ld_phl_b.call(nullptr);
			REQUIRE(mem.read_byte(phlAddr) == 0xB0);

			// C
			regs.hl(phlAddr);
			regs.c = 0xC0;
			ld_phl_c.call(nullptr);
			REQUIRE(mem.read_byte(phlAddr) == 0xC0);

			// D
			regs.hl(phlAddr);
			regs.d = 0xD0;
			ld_phl_d.call(nullptr);
			REQUIRE(mem.read_byte(phlAddr) == 0xD0);

			// E
			regs.hl(phlAddr);
			regs.e = 0xE0;
			ld_phl_e.call(nullptr);
			REQUIRE(mem.read_byte(phlAddr) == 0xE0);

			// H
			regs.hl(phlAddr);
			ld_phl_h.call(nullptr);
			byte_t datah = mem.read_byte(phlAddr);
			REQUIRE(datah == regs.h);

			// L
			regs.hl(phlAddr);
			regs.l = 0xFF;
			ld_phl_l.call(nullptr);
			byte_t datal = mem.read_byte(phlAddr);
			REQUIRE(datal == regs.h);
		}
	};
}