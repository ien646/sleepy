#include <catch2/catch.hpp>

#include "cpufw_test_init.hpp"

namespace sleepy
{
	TEST_CASE("CpuFirmware_DEC_R16")
	{
		SECTION("DEC_R16_CorrectOperation")
		{
			CPUFW_SLEEPY_TESTINIT();

			vcpu_instruction& dec_bc = inst_map[opcode(0x0B)];
			vcpu_instruction& dec_de = inst_map[opcode(0x1B)];
			vcpu_instruction& dec_hl = inst_map[opcode(0x2B)];
			vcpu_instruction& dec_sp = inst_map[opcode(0x3B)];

			regs.bc(0x0000);
			dec_bc.call(nullptr);
			REQUIRE(regs.bc() == 0xFFFF);
			regs.bc(0x0100);
			dec_bc.call(nullptr);
			REQUIRE(regs.bc() == 0x00FF);
			regs.bc(0x0001);
			dec_bc.call(nullptr);
			REQUIRE(regs.bc() == 0x0000);

			regs.de(0x0000);
			dec_de.call(nullptr);
			REQUIRE(regs.de() == 0xFFFF);
			regs.de(0x0100);
			dec_de.call(nullptr);
			REQUIRE(regs.de() == 0x00FF);
			regs.de(0x0001);
			dec_de.call(nullptr);
			REQUIRE(regs.de() == 0x0000);

			regs.hl(0x0000);
			dec_hl.call(nullptr);
			REQUIRE(regs.hl() == 0xFFFF);
			regs.hl(0x0100);
			dec_hl.call(nullptr);
			REQUIRE(regs.hl() == 0x00FF);
			regs.hl(0x0001);
			dec_hl.call(nullptr);
			REQUIRE(regs.hl() == 0x0000);

			regs.sp = (0x0000);
			dec_sp.call(nullptr);
			REQUIRE(regs.sp == 0xFFFF);
			regs.sp = (0x0100);
			dec_sp.call(nullptr);
			REQUIRE(regs.sp == 0x00FF);
			regs.sp = (0x0001);
			dec_sp.call(nullptr);
			REQUIRE(regs.sp == 0x0000);
		}
	};
}