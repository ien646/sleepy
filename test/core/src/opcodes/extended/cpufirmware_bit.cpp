#include <catch2/catch.hpp>

#include "../../cpufw_test_init.hpp"

namespace sleepy
{
	TEST_CASE("CpuFirmware_BIT")
	{
        for(u8 i = 0; i < 8; ++i)
        {
            SECTION("CpuFirmware_Register_BIT_" + std::to_string(static_cast<int>(i)))
            {
                CPUFW_SLEEPY_TESTINIT();

                u8 opc_iidx = 0x40u + (i * 8);

                auto& bit_x_b = inst_map[opcode(0xCB, opc_iidx + 0)];
                auto& bit_x_c = inst_map[opcode(0xCB, opc_iidx + 1)];
                auto& bit_x_d = inst_map[opcode(0xCB, opc_iidx + 2)];
                auto& bit_x_e = inst_map[opcode(0xCB, opc_iidx + 3)];
                auto& bit_x_h = inst_map[opcode(0xCB, opc_iidx + 4)];
                auto& bit_x_l = inst_map[opcode(0xCB, opc_iidx + 5)];
                auto& bit_x_a = inst_map[opcode(0xCB, opc_iidx + 7)];

                auto test = [&](const vcpu_instruction& inst, u8& reg)
                {
                    reg = 0x00;
                    inst.call(nullptr);
                    REQUIRE(regs.read_flag(registers::flag::ZERO));

                    reg = 0x00 | (0x01 << i);
                    inst.call(nullptr);
                    REQUIRE(!regs.read_flag(registers::flag::ZERO));

                    reg = ~(0x00 | (0x01 << i));
                    inst.call(nullptr);
                    REQUIRE(regs.read_flag(registers::flag::ZERO));
                };

                test(bit_x_b, regs.b);
                test(bit_x_c, regs.c);
                test(bit_x_d, regs.d);
                test(bit_x_e, regs.e);
                test(bit_x_h, regs.h);
                test(bit_x_l, regs.l);
                test(bit_x_a, regs.a);
            }

            SECTION("CpuFirmware_PHL_BIT_" + std::to_string(static_cast<int>(i)))
            {
                CPUFW_SLEEPY_TESTINIT();
                u8 opc_iidx = 0x40u + (i * 8);

                auto& bit_x_phl = inst_map[opcode(0xCB, opc_iidx + 6)];
                
                regs.reset_flags();
                u16 addr = 0xF122;
                u8 val = 0x00;
                regs.hl(addr);
                mem.write_byte(addr, val);
                bit_x_phl.call(nullptr);
                REQUIRE(regs.read_flag(registers::flag::ZERO));

                regs.reset_flags();
                addr = 0xF122;
                val = 0x00 | (0x01 << i);
                regs.hl(addr);
                mem.write_byte(addr, val);
                bit_x_phl.call(nullptr);
                REQUIRE(!regs.read_flag(registers::flag::ZERO));

                regs.reset_flags();
                addr = 0xF122;
                val = ~(0x00 | (0x01 << i));
                regs.hl(addr);
                mem.write_byte(addr, val);
                bit_x_phl.call(nullptr);
                REQUIRE(regs.read_flag(registers::flag::ZERO));
            }
        }
    }
}