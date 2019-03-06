#include <catch2/catch.hpp>

#include "cpufw_test_init.hpp"

namespace sleepy
{
	TEST_CASE("CpuFirmware_RRC")
	{
        SECTION("CpuFirmware_RRC_Registers_Flags")
        {
            CPUFW_SLEEPY_TESTINIT();

            auto& rrc_b = inst_map[opcode(0xCB, 0x08)];
            auto& rrc_c = inst_map[opcode(0xCB, 0x09)];
            auto& rrc_d = inst_map[opcode(0xCB, 0x0A)];
            auto& rrc_e = inst_map[opcode(0xCB, 0x0B)];
            auto& rrc_h = inst_map[opcode(0xCB, 0x0C)];
            auto& rrc_l = inst_map[opcode(0xCB, 0x0D)];
            auto& rrc_a = inst_map[opcode(0xCB, 0x0F)];

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
            test_zero_flag(rrc_b, regs.b);
            test_zero_flag(rrc_c, regs.c);
            test_zero_flag(rrc_d, regs.d);
            test_zero_flag(rrc_e, regs.e);
            test_zero_flag(rrc_h, regs.h);
            test_zero_flag(rrc_l, regs.l);
            test_zero_flag(rrc_a, regs.a);

            auto test_carry_flag = [&](const vcpu_instruction& inst, u8& reg)
            {
                regs.reset_flags();
                reg = 0x78;
                inst.call(nullptr);
                REQUIRE(!regs.read_flag(registers::flag::CARRY));

                regs.reset_flags();
                reg = 0x80;
                inst.call(nullptr);
                REQUIRE(!regs.read_flag(registers::flag::CARRY));

                regs.reset_flags();
                reg = 0x01;
                inst.call(nullptr);
                REQUIRE(regs.read_flag(registers::flag::CARRY));
            };

            test_carry_flag(rrc_b, regs.b);
            test_carry_flag(rrc_c, regs.c);
            test_carry_flag(rrc_d, regs.d);
            test_carry_flag(rrc_e, regs.e);
            test_carry_flag(rrc_h, regs.h);
            test_carry_flag(rrc_l, regs.l);
            test_carry_flag(rrc_a, regs.a);
        }

        SECTION("CpuFirmware_RRC_Registers_Operation")
        {
            CPUFW_SLEEPY_TESTINIT();

            auto& rrc_b = inst_map[opcode(0xCB, 0x08)];
            auto& rrc_c = inst_map[opcode(0xCB, 0x09)];
            auto& rrc_d = inst_map[opcode(0xCB, 0x0A)];
            auto& rrc_e = inst_map[opcode(0xCB, 0x0B)];
            auto& rrc_h = inst_map[opcode(0xCB, 0x0C)];
            auto& rrc_l = inst_map[opcode(0xCB, 0x0D)];
            auto& rrc_a = inst_map[opcode(0xCB, 0x0F)];

            auto test_value = [&](const vcpu_instruction& inst, u8& reg)
            {
                reg = 0x00;
                inst.call(nullptr);
                REQUIRE(reg == 0x00);

                reg = 0x01;
                inst.call(nullptr);
                REQUIRE(reg == 0x80);

                reg = 0x02;
                inst.call(nullptr);
                REQUIRE(reg == 0x01);

                reg = 0x10;
                inst.call(nullptr);
                REQUIRE(reg == 0x08);

                reg = 0x80;
                inst.call(nullptr);
                REQUIRE(reg == 0x40);

                reg = 0xFF;
                inst.call(nullptr);
                REQUIRE(reg == 0xFF);
            };

            test_value(rrc_b, regs.b);
            test_value(rrc_c, regs.c);
            test_value(rrc_d, regs.d);
            test_value(rrc_e, regs.e);
            test_value(rrc_h, regs.h);
            test_value(rrc_l, regs.l);
            test_value(rrc_a, regs.a);
        }

        SECTION("CpuFirmware_RRC_PHL")
        {
            CPUFW_SLEEPY_TESTINIT();

            auto& rrc_phl = inst_map[opcode(0xCB, 0x0E)];

            u16 addr = 0xF122;
            u8 val = 0x00;
            regs.hl(addr);
            mem.write_byte(addr, val);
            rrc_phl.call(nullptr);
            REQUIRE(mem.read_byte(addr) == val);
            REQUIRE(regs.read_flag(registers::flag::ZERO));
            REQUIRE(!regs.read_flag(registers::flag::CARRY));

            addr = 0xF122;
            val = 0x01;
            regs.hl(addr);
            mem.write_byte(addr, val);
            rrc_phl.call(nullptr);
            REQUIRE(mem.read_byte(addr) == 0x80);
            REQUIRE(!regs.read_flag(registers::flag::ZERO));
            REQUIRE(regs.read_flag(registers::flag::CARRY));

            addr = 0xF122;
            val = 0x02;
            regs.hl(addr);
            mem.write_byte(addr, val);
            rrc_phl.call(nullptr);
            REQUIRE(mem.read_byte(addr) == 0x01);
            REQUIRE(!regs.read_flag(registers::flag::ZERO));
            REQUIRE(!regs.read_flag(registers::flag::CARRY));

            addr = 0xF122;
            val = 0x80;
            regs.hl(addr);
            mem.write_byte(addr, val);
            rrc_phl.call(nullptr);
            REQUIRE(mem.read_byte(addr) == 0x40);
            REQUIRE(!regs.read_flag(registers::flag::ZERO));
            REQUIRE(!regs.read_flag(registers::flag::CARRY));

            addr = 0xF122;
            val = 0xFF;
            regs.hl(addr);
            mem.write_byte(addr, val);
            rrc_phl.call(nullptr);
            REQUIRE(mem.read_byte(addr) == 0xFF);
            REQUIRE(!regs.read_flag(registers::flag::ZERO));
            REQUIRE(regs.read_flag(registers::flag::CARRY));
        }
    };
}