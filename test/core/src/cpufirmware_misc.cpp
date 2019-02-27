#include <catch2/catch.hpp>

#include "cpufw_test_init.hpp"

namespace sleepy
{
	TEST_CASE("CpuFirmware_Misc")
	{
		SECTION("EI_EnablesInterrupts")
		{
			CPUFW_SLEEPY_TESTINIT();

			vcpu_instruction& ei = inst_map[opcode(0xFB)];

			vfw.disable_interrupts();
			ei.call(nullptr);
			REQUIRE(vfw.interrupts_enabled());

			vfw.enable_interrupts();
			ei.call(nullptr);
			REQUIRE(vfw.interrupts_enabled());
		}

		SECTION("DI_DisablesInterrupts")
		{
			CPUFW_SLEEPY_TESTINIT();

			vcpu_instruction& di = inst_map[opcode(0xF3)];

			vfw.disable_interrupts();
			di.call(nullptr);
			REQUIRE(!(vfw.interrupts_enabled()));

			vfw.enable_interrupts();
			di.call(nullptr);
			REQUIRE(!(vfw.interrupts_enabled()));
		}

		SECTION("CPL_CorrectOperationAndFlags")
		{
			CPUFW_SLEEPY_TESTINIT();

			vcpu_instruction& cpl = inst_map[opcode(0x2F)];

			regs.a = 0x00;
			cpl.call(nullptr);
			REQUIRE(regs.a == 0xFF);
			REQUIRE(regs.read_flag(FLAG_HCARRY));
			REQUIRE(regs.read_flag(FLAG_SUB));

			regs.a = 0x44;
			cpl.call(nullptr);
			REQUIRE(regs.a == (0xFF ^ 0x44));
			REQUIRE(regs.read_flag(FLAG_HCARRY));
			REQUIRE(regs.read_flag(FLAG_SUB));
		}

		SECTION("CCF_CorrectOperationAndFlags")
		{
			CPUFW_SLEEPY_TESTINIT();

			vcpu_instruction& ccf = inst_map[opcode(0x3F)];			

			regs.set_flag(FLAG_CARRY);
			ccf.call(nullptr);
			REQUIRE(!(regs.read_flag(FLAG_CARRY)));
			ccf.call(nullptr);
			REQUIRE(regs.read_flag(FLAG_CARRY));
		}

		SECTION("DAA_CorrectOperation")
		{
			CPUFW_SLEEPY_TESTINIT();

			vcpu_instruction& daa = inst_map[opcode(0x27)];

			regs.reset_flags();
			regs.a = 0x00;
			daa.call(nullptr);
			REQUIRE(regs.a == 0x00);
			REQUIRE(regs.read_flag(FLAG_ZERO));
			REQUIRE(!(regs.read_flag(FLAG_HCARRY)));
			REQUIRE(!(regs.read_flag(FLAG_CARRY)));
			REQUIRE(!(regs.read_flag(FLAG_SUB)));

			regs.reset_flags();
			regs.a = 0x99;
			daa.call(nullptr);
			REQUIRE(regs.a == 0x99);
			REQUIRE(!(regs.read_flag(FLAG_ZERO)));
			REQUIRE(!(regs.read_flag(FLAG_HCARRY)));
			REQUIRE(!(regs.read_flag(FLAG_CARRY)));
			REQUIRE(!(regs.read_flag(FLAG_SUB)));

			regs.reset_flags();
			regs.a = 0xAA;
			daa.call(nullptr);
			REQUIRE(regs.a == 0x10);
			REQUIRE(!(regs.read_flag(FLAG_ZERO)));
			REQUIRE(!(regs.read_flag(FLAG_HCARRY)));
			REQUIRE(regs.read_flag(FLAG_CARRY));
			REQUIRE(!(regs.read_flag(FLAG_SUB)));

			regs.reset_flags();
			regs.a = 0xCC;
			daa.call(nullptr);
			REQUIRE(regs.a == 0x32);
			REQUIRE(!(regs.read_flag(FLAG_ZERO)));
			REQUIRE(!(regs.read_flag(FLAG_HCARRY)));
			REQUIRE(regs.read_flag(FLAG_CARRY));
			REQUIRE(!(regs.read_flag(FLAG_SUB)));

			regs.reset_flags();
			regs.a = 0xEE;
			daa.call(nullptr);
			REQUIRE(regs.a == 0x54);
			REQUIRE(!(regs.read_flag(FLAG_ZERO)));
			REQUIRE(!(regs.read_flag(FLAG_HCARRY)));
			REQUIRE(regs.read_flag(FLAG_CARRY));
			REQUIRE(!(regs.read_flag(FLAG_SUB)));

			regs.reset_flags();
			regs.a = 0xFF;
			daa.call(nullptr);
			REQUIRE(regs.a == 0x65);
			REQUIRE(!(regs.read_flag(FLAG_ZERO)));
			REQUIRE(!(regs.read_flag(FLAG_HCARRY)));
			REQUIRE(regs.read_flag(FLAG_CARRY));
			REQUIRE(!(regs.read_flag(FLAG_SUB)));

			regs.reset_flags();
			regs.a = 0xA0;
			daa.call(nullptr);
			REQUIRE(regs.a == 0x00);
			REQUIRE(regs.read_flag(FLAG_ZERO));
			REQUIRE(!(regs.read_flag(FLAG_HCARRY)));
			REQUIRE(regs.read_flag(FLAG_CARRY));
			REQUIRE(!(regs.read_flag(FLAG_SUB)));

			regs.reset_flags();
			regs.a = 0x0A;
			daa.call(nullptr);
			REQUIRE(regs.a == 0x10);
			REQUIRE(!(regs.read_flag(FLAG_ZERO)));
			REQUIRE(!(regs.read_flag(FLAG_HCARRY)));
			REQUIRE(!(regs.read_flag(FLAG_CARRY)));
			REQUIRE(!(regs.read_flag(FLAG_SUB)));

			regs.reset_flags();
			regs.a = 0xB1;
			daa.call(nullptr);
			REQUIRE(regs.a == 0x11);
			REQUIRE(!(regs.read_flag(FLAG_ZERO)));
			REQUIRE(!(regs.read_flag(FLAG_HCARRY)));
			REQUIRE(regs.read_flag(FLAG_CARRY));
			REQUIRE(!(regs.read_flag(FLAG_SUB)));
		}

		SECTION("SCF_CorrectOperation")
		{
			CPUFW_SLEEPY_TESTINIT();

			vcpu_instruction& scf = inst_map[opcode(0x37)];

			regs.reset_flags();
			scf.call(nullptr);
			REQUIRE(regs.read_flag(FLAG_CARRY));

			regs.set_flag(FLAG_CARRY);
			scf.call(nullptr);
			REQUIRE(regs.read_flag(FLAG_CARRY));
		}

		SECTION("ADD_SP_d8")
		{
			CPUFW_SLEEPY_TESTINIT();

			vcpu_instruction& add_sp_d8 = inst_map[opcode(0xE8)];

			byte_t d8 = 0x00;

			regs.sp = 0xAAAA;
			d8 = 0xBB;
			add_sp_d8.call(&d8);
			REQUIRE(regs.sp == (0xAAAA + 0xBB));

			regs.sp = 0x0000;
			d8 = 0x0F;
			add_sp_d8.call(&d8);
			REQUIRE(!(regs.read_flag(FLAG_ZERO)));
			REQUIRE(!(regs.read_flag(FLAG_SUB)));
			REQUIRE(!(regs.read_flag(FLAG_HCARRY)));
			REQUIRE(!(regs.read_flag(FLAG_CARRY)));

			regs.sp = 0x0001;
			d8 = 0x0F;
			add_sp_d8.call(&d8);
			REQUIRE(!(regs.read_flag(FLAG_ZERO)));
			REQUIRE(!(regs.read_flag(FLAG_SUB)));
			REQUIRE(regs.read_flag(FLAG_HCARRY));
			REQUIRE(!(regs.read_flag(FLAG_CARRY)));

			regs.sp = 0x00F0;
			d8 = 0x0F;
			add_sp_d8.call(&d8);
			REQUIRE(!(regs.read_flag(FLAG_ZERO)));
			REQUIRE(!(regs.read_flag(FLAG_SUB)));
			REQUIRE(regs.read_flag(FLAG_HCARRY));
			REQUIRE(!(regs.read_flag(FLAG_CARRY)));

			regs.sp = 0x00F1;
			d8 = 0x0F;
			add_sp_d8.call(&d8);
			REQUIRE(!(regs.read_flag(FLAG_ZERO)));
			REQUIRE(!(regs.read_flag(FLAG_SUB)));
			REQUIRE(regs.read_flag(FLAG_HCARRY));
			REQUIRE(regs.read_flag(FLAG_CARRY));

			regs.sp = 0xFFF0;
			d8 = 0x0F;
			add_sp_d8.call(&d8);
			REQUIRE(!(regs.read_flag(FLAG_ZERO)));
			REQUIRE(!(regs.read_flag(FLAG_SUB)));
			REQUIRE(regs.read_flag(FLAG_HCARRY));
			REQUIRE(regs.read_flag(FLAG_CARRY));

			regs.sp = 0xFFF1;
			d8 = 0x0F;
			add_sp_d8.call(&d8);
			REQUIRE(!(regs.read_flag(FLAG_ZERO)));
			REQUIRE(!(regs.read_flag(FLAG_SUB)));
			REQUIRE(regs.read_flag(FLAG_HCARRY));
			REQUIRE(regs.read_flag(FLAG_CARRY));

			regs.sp = 0xFFFF;
			d8 = 0x0F;
			add_sp_d8.call(&d8);
			REQUIRE(!(regs.read_flag(FLAG_ZERO)));
			REQUIRE(!(regs.read_flag(FLAG_SUB)));
			REQUIRE(regs.read_flag(FLAG_HCARRY));
			REQUIRE(regs.read_flag(FLAG_CARRY));
		}
	};
}