#include <catch2/catch.hpp>

#include "../../cpufw_test_init.hpp"

namespace sleepy
{
	TEST_CASE("CpuFirmware_LD_RPTR_A")
	{
		SECTION("LD_RPTR_A_CorrectOperation")
		{
			CPUFW_SLEEPY_TESTINIT();

			const vcpu_instruction& ld_pbc_a = inst_map[opcode(0x02)];
			const vcpu_instruction& ld_pde_a = inst_map[opcode(0x12)];
			const vcpu_instruction& ld_phli_a = inst_map[opcode(0x22)];
			const vcpu_instruction& ld_phld_a = inst_map[opcode(0x32)];

			u8 val = 0x00;

			regs.a = 0xBC;
			regs.bc(0x01BC);
			ld_pbc_a.call(nullptr);
			val = mem.read_byte(0x01BC);
			REQUIRE(0xBC == val);

			regs.a = 0xDE;
			regs.de(0x02DE);
			ld_pde_a.call(nullptr);
			val = mem.read_byte(0x02DE);
			REQUIRE(0xDE == val);

			regs.a = 0x0F;
			regs.hl(0x0F0F);
			ld_phli_a.call(nullptr);
			val = mem.read_byte(0x0F0F);
			REQUIRE(0x0F == val);
			REQUIRE(0x0F10 == regs.hl());

			regs.a = 0xF0;
			regs.hl(0xF0F0);
			ld_phld_a.call(nullptr);
			val = mem.read_byte(0xF0F0);
			REQUIRE(0xF0 == val);
			REQUIRE((0xF0F0 - 1) == regs.hl());
		}
	};
}