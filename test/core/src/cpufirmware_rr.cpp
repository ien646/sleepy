#include <catch2/catch.hpp>

#include "cpufw_test_init.hpp"

namespace sleepy
{
	TEST_CASE("CpuFirmware_RR")
	{
        SECTION("CpuFirmware_RR_Registers_Flags")
        {
            CPUFW_SLEEPY_TESTINIT();

            auto& rr_b = inst_map[opcode(0xCB, 0x18)];
            auto& rr_c = inst_map[opcode(0xCB, 0x19)];
            auto& rr_d = inst_map[opcode(0xCB, 0x1A)];
            auto& rr_e = inst_map[opcode(0xCB, 0x1B)];
            auto& rr_h = inst_map[opcode(0xCB, 0x1C)];
            auto& rr_l = inst_map[opcode(0xCB, 0x1D)];
            auto& rr_a = inst_map[opcode(0xCB, 0x1F)];

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
                regs.set_flag(registers::flag::CARRY);
                reg = 0x00;
                inst.call(nullptr);
                REQUIRE(!regs.read_flag(registers::flag::ZERO));

            };
            test_zero_flag(rr_b, regs.b);
            test_zero_flag(rr_c, regs.c);
            test_zero_flag(rr_d, regs.d);
            test_zero_flag(rr_e, regs.e);
            test_zero_flag(rr_h, regs.h);
            test_zero_flag(rr_l, regs.l);
            test_zero_flag(rr_a, regs.a);

            auto test_carry_flag = [&](const vcpu_instruction& inst, u8& reg)
            {
                regs.reset_flags();
                reg = 0x00;
                inst.call(nullptr);
                REQUIRE(!regs.read_flag(registers::flag::CARRY));

                regs.reset_flags();
                reg = 0x01;
                inst.call(nullptr);
                REQUIRE(regs.read_flag(registers::flag::CARRY));

                regs.reset_flags();
                reg = 0x02;
                inst.call(nullptr);
                REQUIRE(!regs.read_flag(registers::flag::CARRY));

                regs.reset_flags();
                reg = 0x03;
                inst.call(nullptr);
                REQUIRE(regs.read_flag(registers::flag::CARRY));
            };

            test_carry_flag(rr_b, regs.b);
            test_carry_flag(rr_c, regs.c);
            test_carry_flag(rr_d, regs.d);
            test_carry_flag(rr_e, regs.e);
            test_carry_flag(rr_h, regs.h);
            test_carry_flag(rr_l, regs.l);
            test_carry_flag(rr_a, regs.a);
        }

        SECTION("CpuFirmware_RR_Registers_Operation")
        {
            CPUFW_SLEEPY_TESTINIT();

            auto& rr_b = inst_map[opcode(0xCB, 0x18)];
            auto& rr_c = inst_map[opcode(0xCB, 0x19)];
            auto& rr_d = inst_map[opcode(0xCB, 0x1A)];
            auto& rr_e = inst_map[opcode(0xCB, 0x1B)];
            auto& rr_h = inst_map[opcode(0xCB, 0x1C)];
            auto& rr_l = inst_map[opcode(0xCB, 0x1D)];
            auto& rr_a = inst_map[opcode(0xCB, 0x1F)];

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
                REQUIRE(reg == 0x80);
                regs.reset_flags();

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

                regs.reset_flags();
                regs.set_flag(registers::flag::CARRY);
                reg = 0xFF;
                inst.call(nullptr);
                REQUIRE(reg == 0xFF);
            };

            test_value(rr_b, regs.b);
            test_value(rr_c, regs.c);
            test_value(rr_d, regs.d);
            test_value(rr_e, regs.e);
            test_value(rr_h, regs.h);
            test_value(rr_l, regs.l);
            test_value(rr_a, regs.a);
        }

        SECTION("CpuFirmware_RR_PHL")
        {
            CPUFW_SLEEPY_TESTINIT();

            auto& rr_phl = inst_map[opcode(0xCB, 0x1E)];

            regs.reset_flags();
            u16 addr = 0xF122;
            u8 val = 0x00;
            regs.hl(addr);
            mem.write_byte(addr, val);
            rr_phl.call(nullptr);
            REQUIRE(mem.read_byte(addr) == val);
            REQUIRE(regs.read_flag(registers::flag::ZERO));
            REQUIRE(!regs.read_flag(registers::flag::CARRY));

            regs.reset_flags();
            regs.set_flag(registers::flag::CARRY);
            addr = 0xF122;
            val = 0x00;
            regs.hl(addr);
            mem.write_byte(addr, val);
            rr_phl.call(nullptr);
            REQUIRE(mem.read_byte(addr) == 0x80);
            REQUIRE(!regs.read_flag(registers::flag::ZERO));
            REQUIRE(!regs.read_flag(registers::flag::CARRY));

            regs.reset_flags();
            addr = 0xF122;
            val = 0x01;
            regs.hl(addr);
            mem.write_byte(addr, val);
            rr_phl.call(nullptr);
            REQUIRE(mem.read_byte(addr) == 0x00);
            REQUIRE(regs.read_flag(registers::flag::ZERO));
            REQUIRE(regs.read_flag(registers::flag::CARRY));

            regs.reset_flags();
            addr = 0xF122;
            val = 0x02;
            regs.hl(addr);
            mem.write_byte(addr, val);
            rr_phl.call(nullptr);
            REQUIRE(mem.read_byte(addr) == 0x01);
            REQUIRE(!regs.read_flag(registers::flag::ZERO));
            REQUIRE(!regs.read_flag(registers::flag::CARRY));

            regs.reset_flags();
            addr = 0xF122;
            val = 0x80;
            regs.hl(addr);
            mem.write_byte(addr, val);
            rr_phl.call(nullptr);
            REQUIRE(mem.read_byte(addr) == 0x40);
            REQUIRE(!regs.read_flag(registers::flag::ZERO));
            REQUIRE(!regs.read_flag(registers::flag::CARRY));

            regs.reset_flags();
            regs.set_flag(registers::flag::CARRY);
            addr = 0xF122;
            val = 0x80;
            regs.hl(addr);
            mem.write_byte(addr, val);
            rr_phl.call(nullptr);
            REQUIRE(mem.read_byte(addr) == 0xC0);
            REQUIRE(!regs.read_flag(registers::flag::ZERO));
            REQUIRE(!regs.read_flag(registers::flag::CARRY));

            regs.reset_flags();
            addr = 0xF122;
            val = 0xFF;
            regs.hl(addr);
            mem.write_byte(addr, val);
            rr_phl.call(nullptr);
            REQUIRE(mem.read_byte(addr) == 0x7F);
            REQUIRE(!regs.read_flag(registers::flag::ZERO));
            REQUIRE(regs.read_flag(registers::flag::CARRY));

            regs.reset_flags();
            regs.set_flag(registers::flag::CARRY);
            addr = 0xF122;
            val = 0xFF;
            regs.hl(addr);
            mem.write_byte(addr, val);
            rr_phl.call(nullptr);
            REQUIRE(mem.read_byte(addr) == 0xFF);
            REQUIRE(!regs.read_flag(registers::flag::ZERO));
            REQUIRE(regs.read_flag(registers::flag::CARRY));
        }
    };
}