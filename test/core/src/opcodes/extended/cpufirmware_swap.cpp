#include <catch2/catch.hpp>

#include "../../cpufw_test_init.hpp"

namespace sleepy
{
	TEST_CASE("CpuFirmware_SWAP")
	{
        SECTION("CpuFirmware_SWAP")
        {
            CPUFW_SLEEPY_TESTINIT();

            auto& swap_b = inst_map[opcode(0xCB, 0x30)];
            auto& swap_c = inst_map[opcode(0xCB, 0x31)];
            auto& swap_d = inst_map[opcode(0xCB, 0x32)];
            auto& swap_e = inst_map[opcode(0xCB, 0x33)];
            auto& swap_h = inst_map[opcode(0xCB, 0x34)];
            auto& swap_l = inst_map[opcode(0xCB, 0x35)];
            auto& swap_a = inst_map[opcode(0xCB, 0x37)];

            regs.reset_flags();

            auto test = [&](const vcpu_instruction& inst, u8& reg)
            {
                reg = 0x00;
                inst.call(nullptr);
                REQUIRE(reg == 0x00);
                REQUIRE(regs.read_flag(registers::flag::ZERO));

                reg = 0x11;
                inst.call(nullptr);
                REQUIRE(reg == 0x11);
                REQUIRE(!regs.read_flag(registers::flag::ZERO));

                reg = 0x10;
                inst.call(nullptr);
                REQUIRE(reg == 0x01);
                REQUIRE(!regs.read_flag(registers::flag::ZERO));

                reg = 0x7A;
                inst.call(nullptr);
                REQUIRE(reg == 0xA7);
                REQUIRE(!regs.read_flag(registers::flag::ZERO));

                reg = 0xFF;
                inst.call(nullptr);
                REQUIRE(reg == 0xFF);
                REQUIRE(!regs.read_flag(registers::flag::ZERO));
            };

            test(swap_b, regs.b);
            test(swap_c, regs.c);
            test(swap_d, regs.d);
            test(swap_e, regs.e);
            test(swap_h, regs.h);
            test(swap_l, regs.l);
            test(swap_a, regs.a);
        }

        SECTION("CpuFirmware_SWAP_PHL")
        {
            CPUFW_SLEEPY_TESTINIT();

            auto& swap_phl = inst_map[opcode(0xCB, 0x36)];

            u16 addr = 0xF122;
            u8 val = 0x00;
            regs.hl(addr);
            mem.write_byte(addr, val);
            swap_phl.call(nullptr);
            REQUIRE(mem.read_byte(addr) == 0x00);
            REQUIRE(regs.read_flag(registers::flag::ZERO));

            addr = 0xF122;
            val = 0x01;
            regs.hl(addr);
            mem.write_byte(addr, val);
            swap_phl.call(nullptr);
            REQUIRE(mem.read_byte(addr) == 0x10);
            REQUIRE(!regs.read_flag(registers::flag::ZERO));

            addr = 0xF122;
            val = 0xFE;
            regs.hl(addr);
            mem.write_byte(addr, val);
            swap_phl.call(nullptr);
            REQUIRE(mem.read_byte(addr) == 0xEF);
            REQUIRE(!regs.read_flag(registers::flag::ZERO));
        }
    }
}