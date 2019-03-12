#include <catch2/catch.hpp>

#include "../../cpufw_test_init.hpp"

namespace sleepy
{
	TEST_CASE("CpuFirmware_SRA")
	{
        SECTION("CpuFirmware_SRA_Registers_Flags")
        {
            CPUFW_SLEEPY_TESTINIT();

            auto& sra_b = inst_map[opcode(0xCB, 0x28)];
            auto& sra_c = inst_map[opcode(0xCB, 0x29)];
            auto& sra_d = inst_map[opcode(0xCB, 0x2A)];
            auto& sra_e = inst_map[opcode(0xCB, 0x2B)];
            auto& sra_h = inst_map[opcode(0xCB, 0x2C)];
            auto& sra_l = inst_map[opcode(0xCB, 0x2D)];
            auto& sra_a = inst_map[opcode(0xCB, 0x2F)];

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
            test_zero_flag(sra_b, regs.b);
            test_zero_flag(sra_c, regs.c);
            test_zero_flag(sra_d, regs.d);
            test_zero_flag(sra_e, regs.e);
            test_zero_flag(sra_h, regs.h);
            test_zero_flag(sra_l, regs.l);
            test_zero_flag(sra_a, regs.a);

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
                inst.call(nullptr);
                REQUIRE(regs.read_flag(registers::flag::CARRY));
            };

            test_carry_flag(sra_b, regs.b);
            test_carry_flag(sra_c, regs.c);
            test_carry_flag(sra_d, regs.d);
            test_carry_flag(sra_e, regs.e);
            test_carry_flag(sra_h, regs.h);
            test_carry_flag(sra_l, regs.l);
            test_carry_flag(sra_a, regs.a);
        }

        SECTION("CpuFirmware_SRA_Registers_Operation")
        {
            CPUFW_SLEEPY_TESTINIT();

            auto& sra_b = inst_map[opcode(0xCB, 0x28)];
            auto& sra_c = inst_map[opcode(0xCB, 0x29)];
            auto& sra_d = inst_map[opcode(0xCB, 0x2A)];
            auto& sra_e = inst_map[opcode(0xCB, 0x2B)];
            auto& sra_h = inst_map[opcode(0xCB, 0x2C)];
            auto& sra_l = inst_map[opcode(0xCB, 0x2D)];
            auto& sra_a = inst_map[opcode(0xCB, 0x2F)];

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
                REQUIRE(reg == 0xC0);

                regs.reset_flags();
                reg = 0xFF;
                inst.call(nullptr);
                REQUIRE(reg == 0xFF);
            };

            test_value(sra_b, regs.b);
            test_value(sra_c, regs.c);
            test_value(sra_d, regs.d);
            test_value(sra_e, regs.e);
            test_value(sra_h, regs.h);
            test_value(sra_l, regs.l);
            test_value(sra_a, regs.a);
        }

        SECTION("CpuFirmware_SLA_PHL")
        {
            CPUFW_SLEEPY_TESTINIT();

            auto& sla_phl = inst_map[opcode(0xCB, 0x2E)];

            u16 addr = 0xF122;
            u8 val = 0x00;
            regs.hl(addr);
            mem.write_byte(addr, val);
            sla_phl.call(nullptr);
            REQUIRE(mem.read_byte(addr) == val);
            REQUIRE(regs.read_flag(registers::flag::ZERO));
            REQUIRE(!regs.read_flag(registers::flag::CARRY));

            addr = 0xF122;
            val = 0x01;
            regs.hl(addr);
            mem.write_byte(addr, val);
            sla_phl.call(nullptr);
            REQUIRE(mem.read_byte(addr) == 0x00);
            REQUIRE(regs.read_flag(registers::flag::ZERO));
            REQUIRE(regs.read_flag(registers::flag::CARRY));

            addr = 0xF122;
            val = 0x02;
            regs.hl(addr);
            mem.write_byte(addr, val);
            sla_phl.call(nullptr);
            REQUIRE(mem.read_byte(addr) == 0x01);
            REQUIRE(!regs.read_flag(registers::flag::ZERO));
            REQUIRE(!regs.read_flag(registers::flag::CARRY));

            addr = 0xF122;
            val = 0x80;
            regs.hl(addr);
            mem.write_byte(addr, val);
            sla_phl.call(nullptr);
            REQUIRE(mem.read_byte(addr) == 0xC0);
            REQUIRE(!regs.read_flag(registers::flag::ZERO));
            REQUIRE(!regs.read_flag(registers::flag::CARRY));

            addr = 0xF122;
            val = 0xFF;
            regs.hl(addr);
            mem.write_byte(addr, val);
            sla_phl.call(nullptr);
            REQUIRE(mem.read_byte(addr) == 0xFF);
            REQUIRE(!regs.read_flag(registers::flag::ZERO));
            REQUIRE(regs.read_flag(registers::flag::CARRY));
        }
    }
}