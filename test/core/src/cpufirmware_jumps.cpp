#include <catch2/catch.hpp>

#include "cpufw_test_init.hpp"

namespace sleepy
{
	TEST_CASE("CpuFirmware_Jumps")
    {
        SECTION("JR i8 (Jump relative v8-signed)")
        {
            CPUFW_SLEEPY_TESTINIT();

            auto& jr_i8 = inst_map[opcode(0x18)];

            regs.pc = 0x0000u;
            byte_t arg = static_cast<byte_t>(0x00);
            jr_i8.call(&arg);
            REQUIRE(regs.pc == 0x0000u);

            regs.pc = 0x0000u;
            arg = static_cast<byte_t>(0x01);
            jr_i8.call(&arg);
            REQUIRE(regs.pc == 0x0001u);

            regs.pc = 0x0000u;
            arg = static_cast<byte_t>(0x79);
            jr_i8.call(&arg);
            REQUIRE(regs.pc == 0x0079u);

            regs.pc = 0x00FFu;
            arg = static_cast<byte_t>(0x88);
            jr_i8.call(&arg);
            REQUIRE(regs.pc == 0x00FFu + static_cast<int8_t>(arg));

            regs.pc = 0x00FFu;
            arg = static_cast<byte_t>(0x01);
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
            byte_t arg = static_cast<byte_t>(0x00);
            jr_z_i8.call(&arg);
            REQUIRE(regs.pc == 0x0000u);

            regs.pc = 0x0000u;
            arg = static_cast<byte_t>(0x01);
            jr_z_i8.call(&arg);
            REQUIRE(regs.pc == 0x0001u);

            regs.pc = 0x0000u;
            arg = static_cast<byte_t>(0x79);
            jr_z_i8.call(&arg);
            REQUIRE(regs.pc == 0x0079u);

            regs.pc = 0x00FFu;
            arg = static_cast<byte_t>(0x88);
            jr_z_i8.call(&arg);
            REQUIRE(regs.pc == 0x00FFu + static_cast<int8_t>(arg));

            regs.pc = 0x00FFu;
            arg = static_cast<byte_t>(0x01);
            jr_z_i8.call(&arg);
            REQUIRE(regs.pc == 0x0100u);

            // -- On zero-flag unset, do nothing --
            regs.reset_flag(registers::flag::ZERO);
            regs.pc = 0x0000u;
            arg = static_cast<byte_t>(0x00);
            jr_z_i8.call(&arg);
            REQUIRE(regs.pc == 0x0000u);

            regs.pc = 0x0000u;
            arg = static_cast<byte_t>(0x01);
            jr_z_i8.call(&arg);
            REQUIRE(regs.pc == 0x0000u); 

            regs.pc = 0x0000u;
            arg = static_cast<byte_t>(0x79);
            jr_z_i8.call(&arg);
            REQUIRE(regs.pc == 0x0000u);

            regs.pc = 0x00FFu;
            arg = static_cast<byte_t>(0x88);
            jr_z_i8.call(&arg);
            REQUIRE(regs.pc == 0x00FFu);

            regs.pc = 0x00FFu;
            arg = static_cast<byte_t>(0x01);
            jr_z_i8.call(&arg);
            REQUIRE(regs.pc == 0x00FFu);
        }

        SECTION("JR C,i8 (Jump if carry-flag relative v8-signed)")
        {
            CPUFW_SLEEPY_TESTINIT();

            auto& jr_z_i8 = inst_map[opcode(0x38)];

            // -- On carry-flag set, behaves like 'JR i8' --
            regs.set_flag(registers::flag::CARRY);

            regs.pc = 0x0000u;
            byte_t arg = static_cast<byte_t>(0x00);
            jr_z_i8.call(&arg);
            REQUIRE(regs.pc == 0x0000u);

            regs.pc = 0x0000u;
            arg = static_cast<byte_t>(0x01);
            jr_z_i8.call(&arg);
            REQUIRE(regs.pc == 0x0001u);

            regs.pc = 0x0000u;
            arg = static_cast<byte_t>(0x79);
            jr_z_i8.call(&arg);
            REQUIRE(regs.pc == 0x0079u);

            regs.pc = 0x00FFu;
            arg = static_cast<byte_t>(0x88);
            jr_z_i8.call(&arg);
            REQUIRE(regs.pc == 0x00FFu + static_cast<int8_t>(arg));

            regs.pc = 0x00FFu;
            arg = static_cast<byte_t>(0x01);
            jr_z_i8.call(&arg);
            REQUIRE(regs.pc == 0x0100u);

            // -- On carry-flag unset, do nothing --
            regs.reset_flag(registers::flag::CARRY);
            regs.pc = 0x0000u;
            arg = static_cast<byte_t>(0x00);
            jr_z_i8.call(&arg);
            REQUIRE(regs.pc == 0x0000u);

            regs.pc = 0x0000u;
            arg = static_cast<byte_t>(0x01);
            jr_z_i8.call(&arg);
            REQUIRE(regs.pc == 0x0000u); 

            regs.pc = 0x0000u;
            arg = static_cast<byte_t>(0x79);
            jr_z_i8.call(&arg);
            REQUIRE(regs.pc == 0x0000u);

            regs.pc = 0x00FFu;
            arg = static_cast<byte_t>(0x88);
            jr_z_i8.call(&arg);
            REQUIRE(regs.pc == 0x00FFu);

            regs.pc = 0x00FFu;
            arg = static_cast<byte_t>(0x01);
            jr_z_i8.call(&arg);
            REQUIRE(regs.pc == 0x00FFu);
        }

        SECTION("JP a16")
        {
            CPUFW_SLEEPY_TESTINIT();

            auto& jp_a16 = inst_map[opcode(0xC3)];

            word_t args;
            byte_t* args_ptr = reinterpret_cast<byte_t*>(&args);

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
           
            word_t args;
            byte_t* args_ptr = reinterpret_cast<byte_t*>(&args);

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
            REQUIRE(regs.pc == 0x0000u);

            regs.pc = 0x0000u;
            args = 0x00FFu;
            jp_nz_a16.call(args_ptr);
            REQUIRE(regs.pc == 0x0000u);

            regs.pc = 0x00FFu;
            args = 0x0000u;
            jp_nz_a16.call(args_ptr);
            REQUIRE(regs.pc == 0x00FFu);

            regs.pc = 0xFF00u;
            args = 0x00FFu;
            jp_nz_a16.call(args_ptr);
            REQUIRE(regs.pc == 0xFF00u);
        }

        SECTION("JP NC,a16")
        {
            CPUFW_SLEEPY_TESTINIT();

            auto& jp_nc_a16 = inst_map[opcode(0xD2)];

            regs.reset_flags(); // NC = true
           
            word_t args;
            byte_t* args_ptr = reinterpret_cast<byte_t*>(&args);

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
            REQUIRE(regs.pc == 0x0000u);

            regs.pc = 0x0000u;
            args = 0x00FFu;
            jp_nc_a16.call(args_ptr);
            REQUIRE(regs.pc == 0x0000u);

            regs.pc = 0x00FFu;
            args = 0x0000u;
            jp_nc_a16.call(args_ptr);
            REQUIRE(regs.pc == 0x00FFu);

            regs.pc = 0xFF00u;
            args = 0x00FFu;
            jp_nc_a16.call(args_ptr);
            REQUIRE(regs.pc == 0xFF00u);
        }
    }
}