#include <catch2/catch.hpp>

#include "../../cpufw_test_init.hpp"

namespace sleepy
{
	TEST_CASE("CpuFirmware_RES")
	{
        for(u8 i = 0; i < 8; ++i)
        {
            SECTION("CpuFirmware_Register_RES_" + std::to_string(static_cast<int>(i)))
            {
                CPUFW_SLEEPY_TESTINIT();

                u8 opc_iidx = 0x80u + (i * 8);

                auto& res_x_b = inst_map[opcode(0xCB, opc_iidx + 0)];
                auto& res_x_c = inst_map[opcode(0xCB, opc_iidx + 1)];
                auto& res_x_d = inst_map[opcode(0xCB, opc_iidx + 2)];
                auto& res_x_e = inst_map[opcode(0xCB, opc_iidx + 3)];
                auto& res_x_h = inst_map[opcode(0xCB, opc_iidx + 4)];
                auto& res_x_l = inst_map[opcode(0xCB, opc_iidx + 5)];
                auto& res_x_a = inst_map[opcode(0xCB, opc_iidx + 7)];

                auto test = [&regs, i](const vcpu_instruction& inst, u8& reg)
                {
                    reg = 0x00;
                    inst.call(nullptr);
                    REQUIRE(reg == 0x00);

                    reg = U8(0x01u << i);
                    inst.call(nullptr);
                    REQUIRE(reg == 0x00);

                    reg = 0xFFu;
                    inst.call(nullptr);
                    u8 expected = (0xFF & ~(0x01u << i));
                    REQUIRE(reg == expected);
                };

                test(res_x_b, regs.b);
                test(res_x_c, regs.c);
                test(res_x_d, regs.d);
                test(res_x_e, regs.e);
                test(res_x_h, regs.h);
                test(res_x_l, regs.l);
                test(res_x_a, regs.a);
            }

            SECTION("CpuFirmware_PHL_RES_" + std::to_string(static_cast<int>(i)))
            {
                CPUFW_SLEEPY_TESTINIT();
                u8 opc_iidx = 0x80u + (i * 8);

                auto& res_x_phl = inst_map[opcode(0xCB, opc_iidx + 6)];

                u16 addr = 0xF122;
                u8 val = 0x00;
                regs.hl(addr);
                mem.write_byte(addr, val);
                res_x_phl.call(nullptr);
                u8 expected = val & ~(U8(1 << i));
                REQUIRE(mem.read_byte(addr) == expected);

                addr = 0xF122;
                val = 0x00 | U8(1 << i);
                regs.hl(addr);
                mem.write_byte(addr, val);
                res_x_phl.call(nullptr);
                expected = val & ~(U8(1 << i));
                REQUIRE(mem.read_byte(addr) == expected);

                addr = 0xF122;
                val = 0xFF;
                regs.hl(addr);
                mem.write_byte(addr, val);
                res_x_phl.call(nullptr);
                expected = val & ~(U8(1 << i));
                REQUIRE(mem.read_byte(addr) == expected);
            }
        }
    }
}