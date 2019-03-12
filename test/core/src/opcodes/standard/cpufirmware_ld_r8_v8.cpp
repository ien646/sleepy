#include <catch2/catch.hpp>

#include "../../cpufw_test_init.hpp"

namespace sleepy
{
	TEST_CASE("CpuFirmware_LD_R8_V8")
	{
		SECTION("CPUF_LD_R8_V8")
		{
			CPUFW_SLEEPY_TESTINIT();

			const vcpu_instruction& ld_a_a = inst_map[opcode(0x7F)];
			const vcpu_instruction& ld_b_a = inst_map[opcode(0x47)];
			const vcpu_instruction& ld_c_a = inst_map[opcode(0x4F)];
			const vcpu_instruction& ld_d_a = inst_map[opcode(0x57)];
			const vcpu_instruction& ld_e_a = inst_map[opcode(0x5F)];
			const vcpu_instruction& ld_h_a = inst_map[opcode(0x67)];
			const vcpu_instruction& ld_l_a = inst_map[opcode(0x6F)];

			regs.a = 0xCA;

			// Run
			ld_a_a.call(nullptr);
			ld_b_a.call(nullptr);
			ld_c_a.call(nullptr);
			ld_d_a.call(nullptr);
			ld_e_a.call(nullptr);
			ld_h_a.call(nullptr);
			ld_l_a.call(nullptr);			

			// Assert
			REQUIRE(regs.a == U8(0xCA));
			REQUIRE(regs.b == U8(0xCA));
			REQUIRE(regs.c == U8(0xCA));
			REQUIRE(regs.d == U8(0xCA));
			REQUIRE(regs.e == U8(0xCA));
			REQUIRE(regs.h == U8(0xCA));
			REQUIRE(regs.l == U8(0xCA));
		}

		SECTION("CPUF_LD_R8_B")
		{
			CPUFW_SLEEPY_TESTINIT();		

			const vcpu_instruction& ld_a_b = inst_map[opcode(0x78)];
			const vcpu_instruction& ld_b_b = inst_map[opcode(0x40)];
			const vcpu_instruction& ld_c_b = inst_map[opcode(0x48)];
			const vcpu_instruction& ld_d_b = inst_map[opcode(0x50)];
			const vcpu_instruction& ld_e_b = inst_map[opcode(0x58)];
			const vcpu_instruction& ld_h_b = inst_map[opcode(0x60)];
			const vcpu_instruction& ld_l_b = inst_map[opcode(0x68)];

			regs.b = 0xCA;

			// Run
			ld_a_b.call(nullptr);
			ld_b_b.call(nullptr);
			ld_c_b.call(nullptr);
			ld_d_b.call(nullptr);
			ld_e_b.call(nullptr);
			ld_h_b.call(nullptr);
			ld_l_b.call(nullptr);

			// Assert
			REQUIRE(regs.a == U8(0xCA));
			REQUIRE(regs.b == U8(0xCA));
			REQUIRE(regs.c == U8(0xCA));
			REQUIRE(regs.d == U8(0xCA));
			REQUIRE(regs.e == U8(0xCA));
			REQUIRE(regs.h == U8(0xCA));
			REQUIRE(regs.l == U8(0xCA));
		}

		SECTION("CPUF_LD_R8_C")
		{
			CPUFW_SLEEPY_TESTINIT();			

			const vcpu_instruction& ld_a_c = inst_map[opcode(0x79)];
			const vcpu_instruction& ld_b_c = inst_map[opcode(0x41)];
			const vcpu_instruction& ld_c_c = inst_map[opcode(0x49)];
			const vcpu_instruction& ld_d_c = inst_map[opcode(0x51)];
			const vcpu_instruction& ld_e_c = inst_map[opcode(0x59)];
			const vcpu_instruction& ld_h_c = inst_map[opcode(0x61)];
			const vcpu_instruction& ld_l_c = inst_map[opcode(0x69)];

			regs.c = 0xCA;

			// Run
			ld_a_c.call(nullptr);
			ld_b_c.call(nullptr);
			ld_c_c.call(nullptr);
			ld_d_c.call(nullptr);
			ld_e_c.call(nullptr);
			ld_h_c.call(nullptr);
			ld_l_c.call(nullptr);

			// Assert
			REQUIRE(regs.a == U8(0xCA));
			REQUIRE(regs.b == U8(0xCA));
			REQUIRE(regs.c == U8(0xCA));
			REQUIRE(regs.d == U8(0xCA));
			REQUIRE(regs.e == U8(0xCA));
			REQUIRE(regs.h == U8(0xCA));
			REQUIRE(regs.l == U8(0xCA));
		}

		SECTION("CPUF_LD_R8_D")
		{
			CPUFW_SLEEPY_TESTINIT();			

			const vcpu_instruction& ld_a_d = inst_map[opcode(0x7A)];
			const vcpu_instruction& ld_b_d = inst_map[opcode(0x42)];
			const vcpu_instruction& ld_c_d = inst_map[opcode(0x4A)];
			const vcpu_instruction& ld_d_d = inst_map[opcode(0x52)];
			const vcpu_instruction& ld_e_d = inst_map[opcode(0x5A)];
			const vcpu_instruction& ld_h_d = inst_map[opcode(0x62)];
			const vcpu_instruction& ld_l_d = inst_map[opcode(0x6A)];

			regs.d = 0xCA;

			// Run
			ld_a_d.call(nullptr);
			ld_b_d.call(nullptr);
			ld_c_d.call(nullptr);
			ld_d_d.call(nullptr);
			ld_e_d.call(nullptr);
			ld_h_d.call(nullptr);
			ld_l_d.call(nullptr);			

			// Assert
			REQUIRE(regs.a == U8(0xCA));
			REQUIRE(regs.b == U8(0xCA));
			REQUIRE(regs.c == U8(0xCA));
			REQUIRE(regs.d == U8(0xCA));
			REQUIRE(regs.e == U8(0xCA));
			REQUIRE(regs.h == U8(0xCA));
			REQUIRE(regs.l == U8(0xCA));
		}

		SECTION("CPUF_LD_R8_E")
		{
			CPUFW_SLEEPY_TESTINIT();			

			const vcpu_instruction& ld_a_e = inst_map[opcode(0x7B)];
			const vcpu_instruction& ld_b_e = inst_map[opcode(0x43)];
			const vcpu_instruction& ld_c_e = inst_map[opcode(0x4B)];
			const vcpu_instruction& ld_d_e = inst_map[opcode(0x53)];
			const vcpu_instruction& ld_e_e = inst_map[opcode(0x5B)];
			const vcpu_instruction& ld_h_e = inst_map[opcode(0x63)];
			const vcpu_instruction& ld_l_e = inst_map[opcode(0x6B)];

			regs.e = 0xCA;

			// Run
			ld_a_e.call(nullptr);
			ld_b_e.call(nullptr);
			ld_c_e.call(nullptr);
			ld_d_e.call(nullptr);
			ld_e_e.call(nullptr);
			ld_h_e.call(nullptr);
			ld_l_e.call(nullptr);

			// Assert
			REQUIRE(regs.a == U8(0xCA));
			REQUIRE(regs.b == U8(0xCA));
			REQUIRE(regs.c == U8(0xCA));
			REQUIRE(regs.d == U8(0xCA));
			REQUIRE(regs.e == U8(0xCA));
			REQUIRE(regs.h == U8(0xCA));
			REQUIRE(regs.l == U8(0xCA));
		}

		SECTION("CPUF_LD_R8_H")
		{
			CPUFW_SLEEPY_TESTINIT();
			
			const vcpu_instruction& ld_a_h = inst_map[opcode(0x7C)];
			const vcpu_instruction& ld_b_h = inst_map[opcode(0x44)];
			const vcpu_instruction& ld_c_h = inst_map[opcode(0x4C)];
			const vcpu_instruction& ld_d_h = inst_map[opcode(0x54)];
			const vcpu_instruction& ld_e_h = inst_map[opcode(0x5C)];
			const vcpu_instruction& ld_h_h = inst_map[opcode(0x64)];
			const vcpu_instruction& ld_l_h = inst_map[opcode(0x6C)];

			regs.h = 0xCA;

			// Run
			ld_a_h.call(nullptr);
			ld_b_h.call(nullptr);
			ld_c_h.call(nullptr);
			ld_d_h.call(nullptr);
			ld_e_h.call(nullptr);
			ld_h_h.call(nullptr);
			ld_l_h.call(nullptr);

			// Assert
			REQUIRE(regs.a == U8(0xCA));
			REQUIRE(regs.b == U8(0xCA));
			REQUIRE(regs.c == U8(0xCA));
			REQUIRE(regs.d == U8(0xCA));
			REQUIRE(regs.e == U8(0xCA));
			REQUIRE(regs.h == U8(0xCA));
			REQUIRE(regs.l == U8(0xCA));
		}

		SECTION("CPUF_LD_R8_L")
		{
			CPUFW_SLEEPY_TESTINIT();			

			const vcpu_instruction& ld_a_l = inst_map[opcode(0x7D)];
			const vcpu_instruction& ld_b_l = inst_map[opcode(0x45)];
			const vcpu_instruction& ld_c_l = inst_map[opcode(0x4D)];
			const vcpu_instruction& ld_d_l = inst_map[opcode(0x55)];
			const vcpu_instruction& ld_e_l = inst_map[opcode(0x5D)];
			const vcpu_instruction& ld_h_l = inst_map[opcode(0x65)];
			const vcpu_instruction& ld_l_l = inst_map[opcode(0x6D)];

			regs.l = 0xCA;

			// Run
			ld_a_l.call(nullptr);
			ld_b_l.call(nullptr);
			ld_c_l.call(nullptr);
			ld_d_l.call(nullptr);
			ld_e_l.call(nullptr);
			ld_h_l.call(nullptr);
			ld_l_l.call(nullptr);

			// Assert
			REQUIRE(regs.a == U8(0xCA));
			REQUIRE(regs.b == U8(0xCA));
			REQUIRE(regs.c == U8(0xCA));
			REQUIRE(regs.d == U8(0xCA));
			REQUIRE(regs.e == U8(0xCA));
			REQUIRE(regs.h == U8(0xCA));
			REQUIRE(regs.l == U8(0xCA));
		}

		SECTION("CPUF_LD_R8_pHL")
		{
			CPUFW_SLEEPY_TESTINIT();

			u16 addr_a = 0x0220;
			u16 addr_b = 0x1331;
			u16 addr_c = 0x2442;
			u16 addr_d = 0x3553;
			u16 addr_e = 0x4664;
			u16 addr_h = 0x5775;
			u16 addr_l = 0x6886;

			mem.data()[addr_a] = 0x0A;
			mem.data()[addr_b] = 0x0B;
			mem.data()[addr_c] = 0x0C;
			mem.data()[addr_d] = 0x0D;
			mem.data()[addr_e] = 0x0E;
			mem.data()[addr_h] = 0x11;
			mem.data()[addr_l] = 0x22;

			const vcpu_instruction& ld_a_phl = inst_map[opcode(0x7E)];
			const vcpu_instruction& ld_b_phl = inst_map[opcode(0x46)];
			const vcpu_instruction& ld_c_phl = inst_map[opcode(0x4E)];
			const vcpu_instruction& ld_d_phl = inst_map[opcode(0x56)];
			const vcpu_instruction& ld_e_phl = inst_map[opcode(0x5E)];
			const vcpu_instruction& ld_h_phl = inst_map[opcode(0x66)];
			const vcpu_instruction& ld_l_phl = inst_map[opcode(0x6E)];

			// Run
			ld_a_phl.call(nullptr);
			ld_b_phl.call(nullptr);
			ld_c_phl.call(nullptr);
			ld_d_phl.call(nullptr);
			ld_e_phl.call(nullptr);
			ld_h_phl.call(nullptr);
			ld_l_phl.call(nullptr);

			// Assert

			REQUIRE(mem.read_byte(addr_a) == 0x0A);
			REQUIRE(mem.read_byte(addr_b) == 0x0B);
			REQUIRE(mem.read_byte(addr_c) == 0x0C);
			REQUIRE(mem.read_byte(addr_d) == 0x0D);
			REQUIRE(mem.read_byte(addr_e) == 0x0E);
			REQUIRE(mem.read_byte(addr_h) == 0x11);
			REQUIRE(mem.read_byte(addr_l) == 0x22);
		}
	};
}