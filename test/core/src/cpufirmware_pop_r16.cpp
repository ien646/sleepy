#include <catch2/catch.hpp>

#include "cpufw_test_init.hpp"

namespace sleepy
{
	TEST_CASE("CpuFirmware_Pop_r16")
	{
        SECTION("CpuFirmware_Pop_AF")
        {
            CPUFW_SLEEPY_TESTINIT();

            auto& pop_af = inst_map[opcode(0xF1)];
            addr_t addr = 0xF122;
            regs.sp = 0xF122;
            regs.af(0x0000u);
            mem.write_word(addr, 0x11FF);
            pop_af.call(nullptr);
            REQUIRE(regs.sp == (addr + 2));
            REQUIRE(regs.af() == 0x11FF);
        }

        SECTION("CpuFirmware_Pop_BC")
        {
            CPUFW_SLEEPY_TESTINIT();
            
            auto& pop_bc = inst_map[opcode(0xC1)];
            addr_t addr = 0xF122;
            regs.sp = 0xF122;
            regs.bc(0x0000u);
            mem.write_word(addr, 0x11FF);
            pop_bc.call(nullptr);
            REQUIRE(regs.sp == (addr + 2));
            REQUIRE(regs.bc() == 0x11FF);
        }

        SECTION("CpuFirmware_Pop_DE")
        {
            CPUFW_SLEEPY_TESTINIT();
            
            auto& pop_de = inst_map[opcode(0xD1)];
            addr_t addr = 0xF122;
            regs.sp = 0xF122;
            regs.de(0x0000u);
            mem.write_word(addr, 0x11FF);
            pop_de.call(nullptr);
            REQUIRE(regs.sp == (addr + 2));
            REQUIRE(regs.de() == 0x11FF);
        }

        SECTION("CpuFirmware_Pop_HL")
        {
            CPUFW_SLEEPY_TESTINIT();
            
            auto& pop_hl = inst_map[opcode(0xE1)];
            addr_t addr = 0xF122;
            regs.sp = 0xF122;
            regs.hl(0x0000u);
            mem.write_word(addr, 0x11FF);
            pop_hl.call(nullptr);
            REQUIRE(regs.sp == (addr + 2));
            REQUIRE(regs.hl() == 0x11FF);
        }
    };
}