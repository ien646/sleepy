#include <catch2/catch.hpp>

#include "../../cpufw_test_init.hpp"

namespace sleepy
{
	TEST_CASE("CpuFirmware_SLA")
	{
        SECTION("CpuFirmware_SLA_Registers_Flags")
        {
            CPUFW_SLEEPY_TESTINIT();

            auto& sla_b = inst_map[opcode(0xCB, 0x20)];
            auto& sla_c = inst_map[opcode(0xCB, 0x21)];
            auto& sla_d = inst_map[opcode(0xCB, 0x22)];
            auto& sla_e = inst_map[opcode(0xCB, 0x23)];
            auto& sla_h = inst_map[opcode(0xCB, 0x24)];
            auto& sla_l = inst_map[opcode(0xCB, 0x25)];
            auto& sla_a = inst_map[opcode(0xCB, 0x27)];

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

                regs.reset_flags();
                reg = 0x80;
                inst.call(nullptr);
                REQUIRE(regs.read_flag(registers::flag::ZERO));

                regs.reset_flags();
                reg = 0x81;
                inst.call(nullptr);
                REQUIRE(!regs.read_flag(registers::flag::ZERO));
            };
            test_zero_flag(sla_b, regs.b);
            test_zero_flag(sla_c, regs.c);
            test_zero_flag(sla_d, regs.d);
            test_zero_flag(sla_e, regs.e);
            test_zero_flag(sla_h, regs.h);
            test_zero_flag(sla_l, regs.l);
            test_zero_flag(sla_a, regs.a);

            auto test_carry_flag = [&](const vcpu_instruction& inst, u8& reg)
            {
                regs.reset_flags();
                reg = 0x00;
                inst.call(nullptr);
                REQUIRE(!regs.read_flag(registers::flag::CARRY));

                regs.reset_flags();
                reg = 0x7F;
                inst.call(nullptr);
                REQUIRE(!regs.read_flag(registers::flag::CARRY));

                regs.reset_flags();
                reg = 0x80;
                inst.call(nullptr);
                REQUIRE(regs.read_flag(registers::flag::CARRY));

                regs.reset_flags();
                reg = 0x40;
                inst.call(nullptr);
                inst.call(nullptr);
                REQUIRE(regs.read_flag(registers::flag::CARRY));
            };

            test_carry_flag(sla_b, regs.b);
            test_carry_flag(sla_c, regs.c);
            test_carry_flag(sla_d, regs.d);
            test_carry_flag(sla_e, regs.e);
            test_carry_flag(sla_h, regs.h);
            test_carry_flag(sla_l, regs.l);
            test_carry_flag(sla_a, regs.a);
        }

        SECTION("CpuFirmware_SLA_Registers_Operation")
        {
            CPUFW_SLEEPY_TESTINIT();

            auto& sla_b = inst_map[opcode(0xCB, 0x20)];
            auto& sla_c = inst_map[opcode(0xCB, 0x21)];
            auto& sla_d = inst_map[opcode(0xCB, 0x22)];
            auto& sla_e = inst_map[opcode(0xCB, 0x23)];
            auto& sla_h = inst_map[opcode(0xCB, 0x24)];
            auto& sla_l = inst_map[opcode(0xCB, 0x25)];
            auto& sla_a = inst_map[opcode(0xCB, 0x27)];

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
                REQUIRE(reg == 0x02);

                regs.reset_flags();
                reg = 0x02;
                inst.call(nullptr);
                REQUIRE(reg == 0x04);

                regs.reset_flags();
                reg = 0x10;
                inst.call(nullptr);
                REQUIRE(reg == 0x20);

                regs.reset_flags();
                reg = 0x80;
                inst.call(nullptr);
                REQUIRE(reg == 0x00);

                regs.reset_flags();
                reg = 0xFF;
                inst.call(nullptr);
                REQUIRE(reg == 0xFE);
            };

            test_value(sla_b, regs.b);
            test_value(sla_c, regs.c);
            test_value(sla_d, regs.d);
            test_value(sla_e, regs.e);
            test_value(sla_h, regs.h);
            test_value(sla_l, regs.l);
            test_value(sla_a, regs.a);
        }
    }
}