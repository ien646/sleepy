#include <catch2/catch.hpp>

#include <sleepy/vcpu_firmware.hpp>
#include "test_macros.hpp"

namespace sleepy
{
	TEST_CASE("CpuFirmware_LD_A_RPTR")
	{
		SECTION("LD_A_RPTR_CorrectOperation")
		{
			CPUFW_SLEEPY_TESTINIT();

			vcpu_instruction& ld_a_pbc = inst_map[0x0A];
			vcpu_instruction& ld_a_pde = inst_map[0x1A];
			vcpu_instruction& ld_a_phli = inst_map[0x2A];
			vcpu_instruction& ld_a_phld = inst_map[0x3A];

			addr_t addr = 0x0000;

			regs.a = 0x00;
			addr = 0x01BC;
			regs.bc(0x01BC);
			mem.write_byte(addr, 0xBC);
			ld_a_pbc.call(nullptr);
			REQUIRE(regs.a == 0xBC);

			regs.a = 0x00;
			addr = 0x02DE;
			regs.de(0x02DE);
			mem.write_byte(addr, 0xDE);
			ld_a_pde.call(nullptr);
			REQUIRE(regs.a == 0xDE);

			regs.a = 0x00;
			addr = 0x030F;
			regs.hl(0x030F);
			mem.write_byte(addr, 0x0F);
			ld_a_phli.call(nullptr);
			REQUIRE(regs.a == 0x0F);
			REQUIRE(0x0310 == regs.hl());

			regs.a = 0x00;
			addr = 0x03FF;
			regs.hl(0x03FF);
			mem.write_byte(addr, 0xFF);
			ld_a_phld.call(nullptr);
			REQUIRE(regs.a == 0xFF);
			REQUIRE(0x03FE == regs.hl());
		}
	};
}