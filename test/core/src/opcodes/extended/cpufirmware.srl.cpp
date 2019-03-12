#include <catch2/catch.hpp>

#include "../../cpufw_test_init.hpp"

namespace sleepy
{
	TEST_CASE("CpuFirmware_SRL")
	{
        SECTION("CpuFirmware_SRL_Registers_Flags")
        {
            CPUFW_SLEEPY_TESTINIT();

            auto& srl_b = inst_map[opcode(0xCB, 0x38)];
            auto& srl_c = inst_map[opcode(0xCB, 0x39)];
            auto& srl_d = inst_map[opcode(0xCB, 0x3A)];
            auto& srl_e = inst_map[opcode(0xCB, 0x3B)];
            auto& srl_h = inst_map[opcode(0xCB, 0x3C)];
            auto& srl_l = inst_map[opcode(0xCB, 0x3D)];
            auto& srl_a = inst_map[opcode(0xCB, 0x3F)];

            auto test_zero_flag = [&](const vcpu_instruction& inst, u8& reg)
            {
                regs.reset_flags();
                reg = 0x00;
                inst.call(nullptr);
                REQUIRE(regs.read_flag(registers::flag::ZERO));

                regs.reset_flags();
                reg = 0x01;
                inst.call(nullptr);
                REQUIRE(regs.read_flag(registers::flag::ZERO));

                regs.reset_flags();
                reg = 0x80;
                inst.call(nullptr);
                REQUIRE(!regs.read_flag(registers::flag::ZERO));

                regs.reset_flags();
                reg = 0x81;
                inst.call(nullptr);
                REQUIRE(!regs.read_flag(registers::flag::ZERO));
            };
            test_zero_flag(srl_b, regs.b);
            test_zero_flag(srl_c, regs.c);
            test_zero_flag(srl_d, regs.d);
            test_zero_flag(srl_e, regs.e);
            test_zero_flag(srl_h, regs.h);
            test_zero_flag(srl_l, regs.l);
            test_zero_flag(srl_a, regs.a);

            auto test_carry_flag = [&](const vcpu_instruction& inst, u8& reg)
            {
                regs.reset_flags();
                reg = 0x00;
                inst.call(nullptr);
                REQUIRE(!regs.read_flag(registers::flag::CARRY));

                regs.reset_flags();
                reg = 0x7F;
                inst.call(nullptr);
                REQUIRE(regs.read_flag(registers::flag::CARRY));

                regs.reset_flags();
                reg = 0x80;
                inst.call(nullptr);
                REQUIRE(!regs.read_flag(registers::flag::CARRY));

                regs.reset_flags();
                reg = 0x02;
                inst.call(nullptr);
                REQUIRE(!regs.read_flag(registers::flag::CARRY));
                inst.call(nullptr);
                REQUIRE(regs.read_flag(registers::flag::CARRY));
            };

            test_carry_flag(srl_b, regs.b);
            test_carry_flag(srl_c, regs.c);
            test_carry_flag(srl_d, regs.d);
            test_carry_flag(srl_e, regs.e);
            test_carry_flag(srl_h, regs.h);
            test_carry_flag(srl_l, regs.l);
            test_carry_flag(srl_a, regs.a);
        }

        SECTION("CpuFirmware_SRL_Registers_Operation")
        {
            CPUFW_SLEEPY_TESTINIT();

            auto& srl_b = inst_map[opcode(0xCB, 0x38)];
            auto& srl_c = inst_map[opcode(0xCB, 0x39)];
            auto& srl_d = inst_map[opcode(0xCB, 0x3A)];
            auto& srl_e = inst_map[opcode(0xCB, 0x3B)];
            auto& srl_h = inst_map[opcode(0xCB, 0x3C)];
            auto& srl_l = inst_map[opcode(0xCB, 0x3D)];
            auto& srl_a = inst_map[opcode(0xCB, 0x3F)];

            auto test_value = [&](const vcpu_instruction& inst, u8& reg)
            {
                regs.reset_flags();
                reg = 0x00;
                inst.call(nullptr);
                REQUIRE(reg == 0x00);

                regs.reset_flags();
                regs.set_flag(registers::flag::CARRY);
                reg = 0x00;
                inst.call(nullptr);
                REQUIRE(reg == 0x00);

                regs.reset_flags();
                reg = 0x01;
                inst.call(nullptr);
                REQUIRE(reg == 0x00);

                regs.reset_flags();
                reg = 0x02;
                inst.call(nullptr);
                REQUIRE(reg == 0x01);

                regs.reset_flags();
                reg = 0x10;
                inst.call(nullptr);
                REQUIRE(reg == 0x08);

                regs.reset_flags();
                reg = 0x80;
                inst.call(nullptr);
                REQUIRE(reg == 0x40);

                regs.reset_flags();
                reg = 0xFF;
                inst.call(nullptr);
                REQUIRE(reg == 0x7F);
            };

            test_value(srl_b, regs.b);
            test_value(srl_c, regs.c);
            test_value(srl_d, regs.d);
            test_value(srl_e, regs.e);
            test_value(srl_h, regs.h);
            test_value(srl_l, regs.l);
            test_value(srl_a, regs.a);
        }

        SECTION("CpuFirmware_SRL_PHL")
        {
            CPUFW_SLEEPY_TESTINIT();

            auto& srl_phl = inst_map[opcode(0xCB, 0x3E)];

            u16 addr = 0xF122;
            u8 val = 0x00;
            regs.hl(addr);
            mem.write_byte(addr, val);
            srl_phl.call(nullptr);
            REQUIRE(mem.read_byte(addr) == val);
            REQUIRE(regs.read_flag(registers::flag::ZERO));
            REQUIRE(!regs.read_flag(registers::flag::CARRY));

            addr = 0xF122;
            val = 0x01;
            regs.hl(addr);
            mem.write_byte(addr, val);
            srl_phl.call(nullptr);
            REQUIRE(mem.read_byte(addr) == 0x00);
            REQUIRE(regs.read_flag(registers::flag::ZERO));
            REQUIRE(regs.read_flag(registers::flag::CARRY));

            addr = 0xF122;
            val = 0x02;
            regs.hl(addr);
            mem.write_byte(addr, val);
            srl_phl.call(nullptr);
            REQUIRE(mem.read_byte(addr) == 0x01);
            REQUIRE(!regs.read_flag(registers::flag::ZERO));
            REQUIRE(!regs.read_flag(registers::flag::CARRY));

            addr = 0xF122;
            val = 0x80;
            regs.hl(addr);
            mem.write_byte(addr, val);
            srl_phl.call(nullptr);
            REQUIRE(mem.read_byte(addr) == 0x40);
            REQUIRE(!regs.read_flag(registers::flag::ZERO));
            REQUIRE(!regs.read_flag(registers::flag::CARRY));

            addr = 0xF122;
            val = 0xFF;
            regs.hl(addr);
            mem.write_byte(addr, val);
            srl_phl.call(nullptr);
            REQUIRE(mem.read_byte(addr) == 0x7F);
            REQUIRE(!regs.read_flag(registers::flag::ZERO));
            REQUIRE(regs.read_flag(registers::flag::CARRY));
        }
    }
}