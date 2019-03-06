#include <catch2/catch.hpp>

#include "cpufw_test_init.hpp"

namespace sleepy
{
	TEST_CASE("CpuFirmware_RLC")
	{
        SECTION("CpuFirmware_RLC_Registers_Flags")
        {
            CPUFW_SLEEPY_TESTINIT();

            auto& rlc_b = inst_map[opcode(0xCB, 0x00)];
            auto& rlc_c = inst_map[opcode(0xCB, 0x01)];
            auto& rlc_d = inst_map[opcode(0xCB, 0x02)];
            auto& rlc_e = inst_map[opcode(0xCB, 0x03)];
            auto& rlc_h = inst_map[opcode(0xCB, 0x04)];
            auto& rlc_l = inst_map[opcode(0xCB, 0x05)];
            auto& rlc_a = inst_map[opcode(0xCB, 0x07)];

            auto test_zero_flag = [&](const vcpu_instruction& inst, u8& reg)
            {
                regs.reset_flags();
                reg = 0x00;
                inst.call(nullptr);
                REQUIRE(regs.read_flag(registers::flag::ZERO));

                regs.reset_flags();
                reg = 0x01;
                inst.call(nullptr);
                REQUIRE(!regs.read_flag(registers::flag::ZERO));
            };
            test_zero_flag(rlc_b, regs.b);
            test_zero_flag(rlc_c, regs.c);
            test_zero_flag(rlc_d, regs.d);
            test_zero_flag(rlc_e, regs.e);
            test_zero_flag(rlc_h, regs.h);
            test_zero_flag(rlc_l, regs.l);
            test_zero_flag(rlc_a, regs.a);

            auto test_carry_flag = [&](const vcpu_instruction& inst, u8& reg)
            {
                regs.reset_flags();
                reg = 0x79;
                inst.call(nullptr);
                REQUIRE(!regs.read_flag(registers::flag::CARRY));

                regs.reset_flags();
                reg = 0x80;
                inst.call(nullptr);
                REQUIRE(regs.read_flag(registers::flag::CARRY));
            };

            test_carry_flag(rlc_b, regs.b);
            test_carry_flag(rlc_c, regs.c);
            test_carry_flag(rlc_d, regs.d);
            test_carry_flag(rlc_e, regs.e);
            test_carry_flag(rlc_h, regs.h);
            test_carry_flag(rlc_l, regs.l);
            test_carry_flag(rlc_a, regs.a);
        }

        SECTION("CpuFirmware_RLC_Registers_Operation")
        {
            CPUFW_SLEEPY_TESTINIT();

            auto& rlc_b = inst_map[opcode(0xCB, 0x00)];
            auto& rlc_c = inst_map[opcode(0xCB, 0x01)];
            auto& rlc_d = inst_map[opcode(0xCB, 0x02)];
            auto& rlc_e = inst_map[opcode(0xCB, 0x03)];
            auto& rlc_h = inst_map[opcode(0xCB, 0x04)];
            auto& rlc_l = inst_map[opcode(0xCB, 0x05)];
            auto& rlc_a = inst_map[opcode(0xCB, 0x07)];

            auto test_value = [&](const vcpu_instruction& inst, u8& reg)
            {
                reg = 0x00;
                inst.call(nullptr);
                REQUIRE(reg == 0x00);

                reg = 0x01;
                inst.call(nullptr);
                REQUIRE(reg == 0x02);

                reg = 0x02;
                inst.call(nullptr);
                REQUIRE(reg == 0x04);

                reg = 0x10;
                inst.call(nullptr);
                REQUIRE(reg == 0x20);

                reg = 0x80;
                inst.call(nullptr);
                REQUIRE(reg == 0x01);

                reg = 0xFF;
                inst.call(nullptr);
                REQUIRE(reg == 0xFF);
            };

            test_value(rlc_b, regs.b);
            test_value(rlc_c, regs.c);
            test_value(rlc_d, regs.d);
            test_value(rlc_e, regs.e);
            test_value(rlc_h, regs.h);
            test_value(rlc_l, regs.l);
            test_value(rlc_a, regs.a);
        }

        SECTION("CpuFirmware_RLC_PHL")
        {
            CPUFW_SLEEPY_TESTINIT();

            auto& rlc_phl = inst_map[opcode(0xCB, 0x06)];

            u16 addr = 0xF122;
            u8 val = 0x00;
            regs.hl(addr);
            mem.write_byte(addr, val);
            rlc_phl.call(nullptr);
            REQUIRE(mem.read_byte(addr) == val);
            REQUIRE(regs.read_flag(registers::flag::ZERO));
            REQUIRE(!regs.read_flag(registers::flag::CARRY));

            addr = 0xF122;
            val = 0x01;
            regs.hl(addr);
            mem.write_byte(addr, val);
            rlc_phl.call(nullptr);
            REQUIRE(mem.read_byte(addr) == 0x02);
            REQUIRE(!regs.read_flag(registers::flag::ZERO));
            REQUIRE(!regs.read_flag(registers::flag::CARRY));

            addr = 0xF122;
            val = 0x02;
            regs.hl(addr);
            mem.write_byte(addr, val);
            rlc_phl.call(nullptr);
            REQUIRE(mem.read_byte(addr) == 0x04);
            REQUIRE(!regs.read_flag(registers::flag::ZERO));
            REQUIRE(!regs.read_flag(registers::flag::CARRY));

            addr = 0xF122;
            val = 0x80;
            regs.hl(addr);
            mem.write_byte(addr, val);
            rlc_phl.call(nullptr);
            REQUIRE(mem.read_byte(addr) == 0x01);
            REQUIRE(!regs.read_flag(registers::flag::ZERO));
            REQUIRE(regs.read_flag(registers::flag::CARRY));

            addr = 0xF122;
            val = 0xFF;
            regs.hl(addr);
            mem.write_byte(addr, val);
            rlc_phl.call(nullptr);
            REQUIRE(mem.read_byte(addr) == 0xFF);
            REQUIRE(!regs.read_flag(registers::flag::ZERO));
            REQUIRE(regs.read_flag(registers::flag::CARRY));
        }
    };
}