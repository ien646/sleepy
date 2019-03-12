#include <catch2/catch.hpp>

#include "../../cpufw_test_init.hpp"

namespace sleepy
{
	TEST_CASE("CpuFirmware_LD_R8_D8")
	{
		SECTION("LD_R8_D8_CorrectOperation")
		{
			CPUFW_SLEEPY_TESTINIT();

			const vcpu_instruction& ld_a_d8 = inst_map[opcode(0x3E)];
			const vcpu_instruction& ld_b_d8 = inst_map[opcode(0x06)];
			const vcpu_instruction& ld_c_d8 = inst_map[opcode(0x0E)];
			const vcpu_instruction& ld_d_d8 = inst_map[opcode(0x16)];
			const vcpu_instruction& ld_e_d8 = inst_map[opcode(0x1E)];
			const vcpu_instruction& ld_h_d8 = inst_map[opcode(0x26)];
			const vcpu_instruction& ld_l_d8 = inst_map[opcode(0x2E)];
			const vcpu_instruction& ld_phl_d8 = inst_map[opcode(0x36)];

			u8 d8 = 0xAF;

			ld_a_d8.call(&d8); 
			ld_b_d8.call(&d8); 
			ld_c_d8.call(&d8); 
			ld_d_d8.call(&d8); 
			ld_e_d8.call(&d8); 
			ld_h_d8.call(&d8); 
			ld_l_d8.call(&d8); 

			REQUIRE(regs.a == 0xAF);
			REQUIRE(regs.b == 0xAF);
			REQUIRE(regs.c == 0xAF);
			REQUIRE(regs.d == 0xAF);
			REQUIRE(regs.e == 0xAF);
			REQUIRE(regs.h == 0xAF);
			REQUIRE(regs.l == 0xAF);

			u16 phl = 0xFAFA;
			regs.hl(phl);
			ld_phl_d8.call(&d8);
			u8 mval = mem.read_byte(regs.hl());
			REQUIRE(mval == 0xAF);
		}
	};
}