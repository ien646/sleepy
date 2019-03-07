#include <catch2/catch.hpp>

#include "cpufw_test_init.hpp"

namespace sleepy
{
	TEST_CASE("CpuFirmware_RL")
	{
        SECTION("CpuFirmware_RL_Registers_Flags")
        {
            CPUFW_SLEEPY_TESTINIT();

            auto& rl_b = inst_map[opcode(0xCB, 0x10)];
            auto& rl_c = inst_map[opcode(0xCB, 0x11)];
            auto& rl_d = inst_map[opcode(0xCB, 0x12)];
            auto& rl_e = inst_map[opcode(0xCB, 0x13)];
            auto& rl_h = inst_map[opcode(0xCB, 0x14)];
            auto& rl_l = inst_map[opcode(0xCB, 0x15)];
            auto& rl_a = inst_map[opcode(0xCB, 0x17)];

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
            test_zero_flag(rl_b, regs.b);
            test_zero_flag(rl_c, regs.c);
            test_zero_flag(rl_d, regs.d);
            test_zero_flag(rl_e, regs.e);
            test_zero_flag(rl_h, regs.h);
            test_zero_flag(rl_l, regs.l);
            test_zero_flag(rl_a, regs.a);

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

            test_carry_flag(rl_b, regs.b);
            test_carry_flag(rl_c, regs.c);
            test_carry_flag(rl_d, regs.d);
            test_carry_flag(rl_e, regs.e);
            test_carry_flag(rl_h, regs.h);
            test_carry_flag(rl_l, regs.l);
            test_carry_flag(rl_a, regs.a);
        }

        SECTION("CpuFirmware_RL_Registers_Operation")
        {
            CPUFW_SLEEPY_TESTINIT();

            auto& rl_b = inst_map[opcode(0xCB, 0x10)];
            auto& rl_c = inst_map[opcode(0xCB, 0x11)];
            auto& rl_d = inst_map[opcode(0xCB, 0x12)];
            auto& rl_e = inst_map[opcode(0xCB, 0x13)];
            auto& rl_h = inst_map[opcode(0xCB, 0x14)];
            auto& rl_l = inst_map[opcode(0xCB, 0x15)];
            auto& rl_a = inst_map[opcode(0xCB, 0x17)];

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
                REQUIRE(reg == 0x01);
                regs.reset_flags();

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
                REQUIRE(regs.read_flag(registers::flag::CARRY));

                regs.reset_flags();
                reg = 0xFF;
                inst.call(nullptr);
                REQUIRE(reg == 0xFE);

                regs.reset_flags();
                regs.set_flag(registers::flag::CARRY);
                reg = 0xFF;
                inst.call(nullptr);
                REQUIRE(reg == 0xFF);
            };

            test_value(rl_b, regs.b);
            test_value(rl_c, regs.c);
            test_value(rl_d, regs.d);
            test_value(rl_e, regs.e);
            test_value(rl_h, regs.h);
            test_value(rl_l, regs.l);
            test_value(rl_a, regs.a);
        }

        SECTION("CpuFirmware_RL_PHL")
        {
            CPUFW_SLEEPY_TESTINIT();

            auto& rl_phl = inst_map[opcode(0xCB, 0x16)];

            regs.reset_flags();
            u16 addr = 0xF122;
            u8 val = 0x00;
            regs.hl(addr);
            mem.write_byte(addr, val);
            rl_phl.call(nullptr);
            REQUIRE(mem.read_byte(addr) == val);
            REQUIRE(regs.read_flag(registers::flag::ZERO));
            REQUIRE(!regs.read_flag(registers::flag::CARRY));

            regs.reset_flags();
            regs.set_flag(registers::flag::CARRY);
            addr = 0xF122;
            val = 0x00;
            regs.hl(addr);
            mem.write_byte(addr, val);
            rl_phl.call(nullptr);
            REQUIRE(mem.read_byte(addr) == (val + 1));
            REQUIRE(!regs.read_flag(registers::flag::ZERO));
            REQUIRE(!regs.read_flag(registers::flag::CARRY));

            regs.reset_flags();
            addr = 0xF122;
            val = 0x01;
            regs.hl(addr);
            mem.write_byte(addr, val);
            rl_phl.call(nullptr);
            REQUIRE(mem.read_byte(addr) == 0x02);
            REQUIRE(!regs.read_flag(registers::flag::ZERO));
            REQUIRE(!regs.read_flag(registers::flag::CARRY));

            regs.reset_flags();
            addr = 0xF122;
            val = 0x02;
            regs.hl(addr);
            mem.write_byte(addr, val);
            rl_phl.call(nullptr);
            REQUIRE(mem.read_byte(addr) == 0x04);
            REQUIRE(!regs.read_flag(registers::flag::ZERO));
            REQUIRE(!regs.read_flag(registers::flag::CARRY));

            regs.reset_flags();
            addr = 0xF122;
            val = 0x80;
            regs.hl(addr);
            mem.write_byte(addr, val);
            rl_phl.call(nullptr);
            REQUIRE(mem.read_byte(addr) == 0x00);
            REQUIRE(!regs.read_flag(registers::flag::ZERO));
            REQUIRE(regs.read_flag(registers::flag::CARRY));

            regs.reset_flags();
            regs.set_flag(registers::flag::CARRY);
            addr = 0xF122;
            val = 0x80;
            regs.hl(addr);
            mem.write_byte(addr, val);
            rl_phl.call(nullptr);
            REQUIRE(mem.read_byte(addr) == 0x01);
            REQUIRE(!regs.read_flag(registers::flag::ZERO));
            REQUIRE(regs.read_flag(registers::flag::CARRY));

            regs.reset_flags();
            addr = 0xF122;
            val = 0xFF;
            regs.hl(addr);
            mem.write_byte(addr, val);
            rl_phl.call(nullptr);
            REQUIRE(mem.read_byte(addr) == 0xFE);
            REQUIRE(!regs.read_flag(registers::flag::ZERO));
            REQUIRE(regs.read_flag(registers::flag::CARRY));

            regs.reset_flags();
            regs.set_flag(registers::flag::CARRY);
            addr = 0xF122;
            val = 0xFF;
            regs.hl(addr);
            mem.write_byte(addr, val);
            rl_phl.call(nullptr);
            REQUIRE(mem.read_byte(addr) == 0xFF);
            REQUIRE(!regs.read_flag(registers::flag::ZERO));
            REQUIRE(regs.read_flag(registers::flag::CARRY));
        }
    };
}