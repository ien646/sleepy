#include <catch2/catch.hpp>

#include "cpufw_test_init.hpp"

namespace sleepy
{
	TEST_CASE("CpuFirmware_RST")
	{
		SECTION("RST_Correct_PC_Value")
		{
			CPUFW_SLEEPY_TESTINIT();

			vcpu_instruction& rst_00 = inst_map[opcode(0xC7)];
			vcpu_instruction& rst_08 = inst_map[opcode(0xCF)];
			vcpu_instruction& rst_10 = inst_map[opcode(0xD7)];
			vcpu_instruction& rst_18 = inst_map[opcode(0xDF)];
			vcpu_instruction& rst_20 = inst_map[opcode(0xE7)];
			vcpu_instruction& rst_28 = inst_map[opcode(0xEF)];
			vcpu_instruction& rst_30 = inst_map[opcode(0xF7)];
			vcpu_instruction& rst_38 = inst_map[opcode(0xFF)];

			regs.pc = 0xFFFF;
			rst_00.call(nullptr);
			REQUIRE(regs.pc == 0x0000);

			regs.pc = 0xFFFF;
			rst_08.call(nullptr);
			REQUIRE(regs.pc == 0x0008);

			regs.pc = 0xFFFF;
			rst_10.call(nullptr);
			REQUIRE(regs.pc == 0x0010);

			regs.pc = 0xFFFF;
			rst_18.call(nullptr);
			REQUIRE(regs.pc == 0x0018);

			regs.pc = 0xFFFF;
			rst_20.call(nullptr);
			REQUIRE(regs.pc == 0x0020);

			regs.pc = 0xFFFF;
			rst_28.call(nullptr);
			REQUIRE(regs.pc == 0x0028);

			regs.pc = 0xFFFF;
			rst_30.call(nullptr);
			REQUIRE(regs.pc == 0x0030);

			regs.pc = 0xFFFF;
			rst_38.call(nullptr);
			REQUIRE(regs.pc == 0x0038);
		}
	};
}