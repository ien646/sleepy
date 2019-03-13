#include <catch2/catch.hpp>

#include "../../cpufw_test_init.hpp"

namespace sleepy
{
	TEST_CASE("CpuFirmware_Jumps")
    {
        SECTION("JR i8 (Jump relative v8-signed)")
        {
            CPUFW_SLEEPY_TESTINIT();

            auto& jr_i8 = inst_map[opcode(0x18)];

            regs.pc = 0x0000u;
            u8 arg = U8(0x00);
            jr_i8.call(&arg);
            REQUIRE(regs.pc == 0x0000u);

            regs.pc = 0x0000u;
            arg = U8(0x01);
            jr_i8.call(&arg);
            REQUIRE(regs.pc == 0x0001u);

            regs.pc = 0x0000u;
            arg = U8(0x79);
            jr_i8.call(&arg);
            REQUIRE(regs.pc == 0x0079u);

            regs.pc = 0x00FFu;
            arg = U8(0x88);
            jr_i8.call(&arg);
            REQUIRE(regs.pc == 0x00FFu + static_cast<int8_t>(arg));

            regs.pc = 0x00FFu;
            arg = U8(0x01);
            jr_i8.call(&arg);
            REQUIRE(regs.pc == 0x0100u);
        }

        SECTION("JR Z,i8 (Jump if zero-flag relative v8-signed)")
        {
            CPUFW_SLEEPY_TESTINIT();

            auto& jr_z_i8 = inst_map[opcode(0x28)];

            // -- On zero-flag set, behaves like 'JR i8' --
            regs.set_flag(registers::flag::ZERO);

            regs.pc = 0x0000u;
            u8 arg = U8(0x00);
            jr_z_i8.call(&arg);
            REQUIRE(regs.pc == 0x0000u);

            regs.pc = 0x0000u;
            arg = U8(0x01);
            jr_z_i8.call(&arg);
            REQUIRE(regs.pc == 0x0001u);

            regs.pc = 0x0000u;
            arg = U8(0x79);
            jr_z_i8.call(&arg);
            REQUIRE(regs.pc == 0x0079u);

            regs.pc = 0x00FFu;
            arg = U8(0x88);
            jr_z_i8.call(&arg);
            REQUIRE(regs.pc == 0x00FFu + static_cast<int8_t>(arg));

            regs.pc = 0x00FFu;
            arg = U8(0x01);
            jr_z_i8.call(&arg);
            REQUIRE(regs.pc == 0x0100u);

            // -- On zero-flag unset, do nothing --
            regs.reset_flag(registers::flag::ZERO);
            regs.pc = 0x0000u;
            arg = U8(0x00);
            jr_z_i8.call(&arg);
            REQUIRE(regs.pc == 0x0002u);

            regs.pc = 0x0000u;
            arg = U8(0x01);
            jr_z_i8.call(&arg);
            REQUIRE(regs.pc == 0x0002u); 

            regs.pc = 0x0000u;
            arg = U8(0x79);
            jr_z_i8.call(&arg);
            REQUIRE(regs.pc == 0x0002u);

            regs.pc = 0x00FFu;
            arg = U8(0x88);
            jr_z_i8.call(&arg);
            REQUIRE(regs.pc == 0x0101u);

            regs.pc = 0x00FFu;
            arg = U8(0x01);
            jr_z_i8.call(&arg);
            REQUIRE(regs.pc == 0x0101u);
        }

        SECTION("JR C,i8 (Jump if carry-flag relative v8-signed)")
        {
            CPUFW_SLEEPY_TESTINIT();

            auto& jr_z_i8 = inst_map[opcode(0x38)];

            // -- On carry-flag set, behaves like 'JR i8' --
            regs.set_flag(registers::flag::CARRY);

            regs.pc = 0x0000u;
            u8 arg = U8(0x00);
            jr_z_i8.call(&arg);
            REQUIRE(regs.pc == 0x0000u);

            regs.pc = 0x0000u;
            arg = U8(0x01);
            jr_z_i8.call(&arg);
            REQUIRE(regs.pc == 0x0001u);

            regs.pc = 0x0000u;
            arg = U8(0x79);
            jr_z_i8.call(&arg);
            REQUIRE(regs.pc == 0x0079u);

            regs.pc = 0x00FFu;
            arg = U8(0x88);
            jr_z_i8.call(&arg);
            REQUIRE(regs.pc == 0x00FFu + static_cast<int8_t>(arg));

            regs.pc = 0x00FFu;
            arg = U8(0x01);
            jr_z_i8.call(&arg);
            REQUIRE(regs.pc == 0x0100u);

            // -- On carry-flag unset, do nothing --
            regs.reset_flag(registers::flag::CARRY);
            regs.pc = 0x0000u;
            arg = U8(0x00);
            jr_z_i8.call(&arg);
            REQUIRE(regs.pc == 0x0002u);

            regs.pc = 0x0000u;
            arg = U8(0x01);
            jr_z_i8.call(&arg);
            REQUIRE(regs.pc == 0x0002u); 

            regs.pc = 0x0000u;
            arg = U8(0x79);
            jr_z_i8.call(&arg);
            REQUIRE(regs.pc == 0x0002u);

            regs.pc = 0x00FFu;
            arg = U8(0x88);
            jr_z_i8.call(&arg);
            REQUIRE(regs.pc == 0x0101u);

            regs.pc = 0x00FFu;
            arg = U8(0x01);
            jr_z_i8.call(&arg);
            REQUIRE(regs.pc == 0x0101u);
        }

        SECTION("JP a16")
        {
            CPUFW_SLEEPY_TESTINIT();

            auto& jp_a16 = inst_map[opcode(0xC3)];

            u16 args;
            u8* args_ptr = reinterpret_cast<u8*>(&args);

            regs.pc = 0x0000u;
            args = 0x0000u;
            jp_a16.call(args_ptr);
            REQUIRE(regs.pc == args);

            regs.pc = 0x0000u;
            args = 0x00FFu;
            jp_a16.call(args_ptr);
            REQUIRE(regs.pc == args);

            regs.pc = 0x00FFu;
            args = 0x0000u;
            jp_a16.call(args_ptr);
            REQUIRE(regs.pc == args);

            regs.pc = 0xFF00u;
            args = 0x00FFu;
            jp_a16.call(args_ptr);
            REQUIRE(regs.pc == args);
        }

        SECTION("JP NZ,a16")
        {
            CPUFW_SLEEPY_TESTINIT();

            auto& jp_nz_a16 = inst_map[opcode(0xC2)];

            regs.reset_flags(); // NZ = true
           
            u16 args;
            u8* args_ptr = reinterpret_cast<u8*>(&args);

            regs.pc = 0x0000u;
            args = 0x0000u;
            jp_nz_a16.call(args_ptr);
            REQUIRE(regs.pc == args);

            regs.pc = 0x0000u;
            args = 0x00FFu;
            jp_nz_a16.call(args_ptr);
            REQUIRE(regs.pc == args);

            regs.pc = 0x00FFu;
            args = 0x0000u;
            jp_nz_a16.call(args_ptr);
            REQUIRE(regs.pc == args);

            regs.pc = 0xFF00u;
            args = 0x00FFu;
            jp_nz_a16.call(args_ptr);
            REQUIRE(regs.pc == args);

            regs.set_flag(registers::flag::ZERO); // NZ = false

            regs.pc = 0x0000u;
            args = 0x0000u;
            jp_nz_a16.call(args_ptr);
            REQUIRE(regs.pc == 0x0003u);

            regs.pc = 0x0000u;
            args = 0x00FFu;
            jp_nz_a16.call(args_ptr);
            REQUIRE(regs.pc == 0x0003u);

            regs.pc = 0x00FFu;
            args = 0x0000u;
            jp_nz_a16.call(args_ptr);
            REQUIRE(regs.pc == 0x0102u);

            regs.pc = 0xFF00u;
            args = 0x00FFu;
            jp_nz_a16.call(args_ptr);
            REQUIRE(regs.pc == 0xFF03u);
        }

        SECTION("JP NC,a16")
        {
            CPUFW_SLEEPY_TESTINIT();

            auto& jp_nc_a16 = inst_map[opcode(0xD2)];

            regs.reset_flags(); // NC = true
           
            u16 args;
            u8* args_ptr = reinterpret_cast<u8*>(&args);

            regs.pc = 0x0000u;
            args = 0x0000u;
            jp_nc_a16.call(args_ptr);
            REQUIRE(regs.pc == args);

            regs.pc = 0x0000u;
            args = 0x00FFu;
            jp_nc_a16.call(args_ptr);
            REQUIRE(regs.pc == args);

            regs.pc = 0x00FFu;
            args = 0x0000u;
            jp_nc_a16.call(args_ptr);
            REQUIRE(regs.pc == args);

            regs.pc = 0xFF00u;
            args = 0x00FFu;
            jp_nc_a16.call(args_ptr);
            REQUIRE(regs.pc == args);

            regs.set_flag(registers::flag::CARRY); // NC = false

            regs.pc = 0x0000u;
            args = 0x0000u;
            jp_nc_a16.call(args_ptr);
            REQUIRE(regs.pc == 0x0003u);

            regs.pc = 0x0000u;
            args = 0x00FFu;
            jp_nc_a16.call(args_ptr);
            REQUIRE(regs.pc == 0x0003u);

            regs.pc = 0x00FFu;
            args = 0x0000u;
            jp_nc_a16.call(args_ptr);
            REQUIRE(regs.pc == 0x0102u);

            regs.pc = 0xFF00u;
            args = 0x00FFu;
            jp_nc_a16.call(args_ptr);
            REQUIRE(regs.pc == 0xFF03u);
        }

        SECTION("JP Z,a16")
        {
            CPUFW_SLEEPY_TESTINIT();

            auto& jp_z_a16 = inst_map[opcode(0xCA)];

            regs.reset_flags(); // Z = true
            regs.set_flag(registers::flag::ZERO);
           
            u16 args;
            u8* args_ptr = reinterpret_cast<u8*>(&args);

            regs.pc = 0x0000u;
            args = 0x0000u;
            jp_z_a16.call(args_ptr);
            REQUIRE(regs.pc == args);

            regs.pc = 0x0000u;
            args = 0x00FFu;
            jp_z_a16.call(args_ptr);
            REQUIRE(regs.pc == args);

            regs.pc = 0x00FFu;
            args = 0x0000u;
            jp_z_a16.call(args_ptr);
            REQUIRE(regs.pc == args);

            regs.pc = 0xFF00u;
            args = 0x00FFu;
            jp_z_a16.call(args_ptr);
            REQUIRE(regs.pc == args);

            regs.reset_flags(); // Z = false

            regs.pc = 0x0000u;
            args = 0x0000u;
            jp_z_a16.call(args_ptr);
            REQUIRE(regs.pc == 0x0003u);

            regs.pc = 0x0000u;
            args = 0x00FFu;
            jp_z_a16.call(args_ptr);
            REQUIRE(regs.pc == 0x0003u);

            regs.pc = 0x00FFu;
            args = 0x0000u;
            jp_z_a16.call(args_ptr);
            REQUIRE(regs.pc == 0x0102u);

            regs.pc = 0xFF00u;
            args = 0x00FFu;
            jp_z_a16.call(args_ptr);
            REQUIRE(regs.pc == 0xFF03u);
        }

        SECTION("JP C,a16")
        {
            CPUFW_SLEEPY_TESTINIT();

            auto& jp_c_a16 = inst_map[opcode(0xDA)];

            regs.reset_flags(); // C = true
            regs.set_flag(registers::flag::CARRY);
           
            u16 args;
            u8* args_ptr = reinterpret_cast<u8*>(&args);

            regs.pc = 0x0000u;
            args = 0x0000u;
            jp_c_a16.call(args_ptr);
            REQUIRE(regs.pc == args);

            regs.pc = 0x0000u;
            args = 0x00FFu;
            jp_c_a16.call(args_ptr);
            REQUIRE(regs.pc == args);

            regs.pc = 0x00FFu;
            args = 0x0000u;
            jp_c_a16.call(args_ptr);
            REQUIRE(regs.pc == args);

            regs.pc = 0xFF00u;
            args = 0x00FFu;
            jp_c_a16.call(args_ptr);
            REQUIRE(regs.pc == args);

            regs.reset_flags(); // Z = false

            regs.pc = 0x0000u;
            args = 0x0000u;
            jp_c_a16.call(args_ptr);
            REQUIRE(regs.pc == 0x0003u);

            regs.pc = 0x0000u;
            args = 0x00FFu;
            jp_c_a16.call(args_ptr);
            REQUIRE(regs.pc == 0x0003u);

            regs.pc = 0x00FFu;
            args = 0x0000u;
            jp_c_a16.call(args_ptr);
            REQUIRE(regs.pc == 0x0102u);

            regs.pc = 0xFF00u;
            args = 0x00FFu;
            jp_c_a16.call(args_ptr);
            REQUIRE(regs.pc == 0xFF03u);
        }

        SECTION("JP (HL)")
        {
            CPUFW_SLEEPY_TESTINIT();

            auto& jp_phl = inst_map[opcode(0xE9)];
            regs.pc = 0x0000u;

            u16 addr = 0x0000u;
            u16 val = 0x0000u;
            mem.write_word(addr, val);
            regs.hl(addr);
            jp_phl.call(nullptr);
            REQUIRE(regs.pc == val);

            addr = 0x00FFu;
            val = 0x0000u;
            mem.write_word(addr, val);
            regs.hl(addr);
            jp_phl.call(nullptr);
            REQUIRE(regs.pc == val);

            addr = 0x00FFu;
            val = 0x0001u;
            mem.write_word(addr, val);
            regs.hl(addr);
            jp_phl.call(nullptr);
            REQUIRE(regs.pc == val);

            addr = 0x00FFu;
            val = 0x00FFu;
            mem.write_word(addr, val);
            regs.hl(addr);
            jp_phl.call(nullptr);
            REQUIRE(regs.pc == val);

            addr = 0xFFFEu;
            val = 0xFFFFu;
            mem.write_word(addr, val);
            regs.hl(addr);
            jp_phl.call(nullptr);
            REQUIRE(regs.pc == val);
        }
    }
}