#include <catch2/catch.hpp>

#include <sleepy/vcpu_firmware.hpp>
#include "test_macros.hpp"

using namespace sleepy;

namespace sleepy
{
	TEST_CASE("CpuFirmware_INC_R16")
	{
		SECTION("INC_R16_CorrectOperation")
		{
			CPUFW_SLEEPY_TESTINIT();

			vcpu_instruction& inc_bc = inst_map[opcode(0x03)];
			vcpu_instruction& inc_de = inst_map[opcode(0x13)];
			vcpu_instruction& inc_hl = inst_map[opcode(0x23)];
			vcpu_instruction& inc_sp = inst_map[opcode(0x33)];

			regs.bc(0x0000);
			inc_bc.call(nullptr);
			REQUIRE(regs.bc() == 0x0001);
			regs.bc(0x00FF);
			inc_bc.call(nullptr);
			REQUIRE(regs.bc() == 0x0100);
			regs.bc(0xFFFF);
			inc_bc.call(nullptr);
			REQUIRE(regs.bc() == 0x0000);

			regs.de(0x0000);
			inc_de.call(nullptr);
			REQUIRE(regs.de() == 0x0001);
			regs.de(0x00FF);
			inc_de.call(nullptr);
			REQUIRE(regs.de() == 0x0100);
			regs.de(0xFFFF);
			inc_de.call(nullptr);
			REQUIRE(regs.de() == 0x0000);

			regs.hl(0x0000);
			inc_hl.call(nullptr);
			REQUIRE(regs.hl() == 0x0001);
			regs.hl(0x00FF);
			inc_hl.call(nullptr);
			REQUIRE(regs.hl() == 0x0100);
			regs.hl(0xFFFF);
			inc_hl.call(nullptr);
			REQUIRE(regs.hl() == 0x0000);

			regs.sp = (0x0000);
			inc_sp.call(nullptr);
			REQUIRE(regs.sp == 0x0001);
			regs.sp = (0x00FF);
			inc_sp.call(nullptr);
			REQUIRE(regs.sp == 0x0100);
			regs.sp = (0xFFFF);
			inc_sp.call(nullptr);
			REQUIRE(regs.sp == 0x0000);
		}
	};
}