#include <catch2/catch.hpp>

#include "../../cpufw_test_init.hpp"

namespace sleepy
{
	TEST_CASE("CpuFirmware_LD_R16_D16")
	{
		SECTION("LD_R16_D16_CorrectOperation")
		{
			CPUFW_SLEEPY_TESTINIT();

			const vcpu_instruction& ld_bc_d16 = inst_map[opcode(0x01)];
			const vcpu_instruction& ld_de_d16 = inst_map[opcode(0x11)];
			const vcpu_instruction& ld_hl_d16 = inst_map[opcode(0x21)];
			const vcpu_instruction& ld_sp_d16 = inst_map[opcode(0x31)];

			u16 args;

			regs.bc(0x0000);
			args = 0xBCCB;
			ld_bc_d16.call((u8*)(&args));
			REQUIRE(regs.bc() == 0xBCCB);

			regs.de(0x0000);
			args = 0xDEED;
			ld_de_d16.call((u8*)(&args));
			REQUIRE(regs.de() == 0xDEED);

			regs.hl(0x0000);
			args = 0x9889;
			ld_hl_d16.call((u8*)(&args));
			REQUIRE(regs.hl() == 0x9889);

			regs.sp = 0x0000;
			args = 0x5775;
			ld_sp_d16.call((u8*)(&args));
			REQUIRE(regs.sp == 0x5775);
		}
	};
}