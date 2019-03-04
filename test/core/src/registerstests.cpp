#include <catch2/catch.hpp>
#include <sleepy/registers.hpp>
#include <sleepy/memory.hpp>

using namespace sleepy;

namespace sleepy
{
	TEST_CASE("RegistersTests")
	{
		SECTION("Set_8Bit_RegisterPair_As16bit_Endianess")
		{
			// Setup
			registers r;

			// Run
			r.af(0xFF00);
			r.bc(0xEE11);
			r.de(0xDD22);
			r.hl(0xCC33);
			
			// Assert
			REQUIRE(0x00 == r.f);
			REQUIRE(0xFF == r.a);

			REQUIRE(0x11 == r.c);
			REQUIRE(0xEE == r.b);

			REQUIRE(0x22 == r.e);
			REQUIRE(0xDD == r.d);

			REQUIRE(0x33 == r.l);
			REQUIRE(0xCC == r.h);
		}

		SECTION("Read_8Bit_RegisterPair_As16bit_Endianess")
		{
			// Setup
			registers r;
			r.a = 0xFF;
			r.f = 0x00;
			r.b = 0xEE;
			r.c = 0x11;
			r.d = 0xDD;
			r.e = 0x22;
			r.h = 0xCC;
			r.l = 0x33;

			// Run
			u16 AF = r.af();
			u16 BC = r.bc();
			u16 DE = r.de();
			u16 HL = r.hl();

			// Assert
			REQUIRE((u16)0xFF00 == AF);
			REQUIRE((u16)0xEE11 == BC);
			REQUIRE((u16)0xDD22 == DE);
			REQUIRE((u16)0xCC33 == HL);
		};

		SECTION("Set_Flags_CorrectBit")
		{
			registers r;

			r.f = 0x00;
			r.set_flag(registers::flag::NULL_0);
			REQUIRE(0b00000001 == r.f);

			r.f = 0x00;
			r.set_flag(registers::flag::NULL_1);
			REQUIRE(0b00000010 == r.f);

			r.f = 0x00;
			r.set_flag(registers::flag::NULL_2);
			REQUIRE(0b00000100 == r.f);

			r.f = 0x00;
			r.set_flag(registers::flag::NULL_3);
			REQUIRE(0b00001000 == r.f);

			r.f = 0x00;
			r.set_flag(registers::flag::CARRY);
			REQUIRE(0b00010000 == r.f);

			r.f = 0x00;
			r.set_flag(registers::flag::HALF_CARRY);
			REQUIRE(0b00100000 == r.f);

			r.f = 0x00;
			r.set_flag(registers::flag::SUB);
			REQUIRE(0b01000000 == r.f);

			r.f = 0x00;
			r.set_flag(registers::flag::ZERO);
			REQUIRE(0b10000000 == r.f);
		}

		SECTION("Reset_Flags_CorrectBit")
		{
			registers r;

			r.f = 0xFF;
			r.reset_flag(registers::flag::NULL_0);
			REQUIRE(0b11111110 == r.f);

			r.f = 0xFF;
			r.reset_flag(registers::flag::NULL_1);
			REQUIRE(0b11111101 == r.f);

			r.f = 0xFF;
			r.reset_flag(registers::flag::NULL_2);
			REQUIRE(0b11111011 == r.f);

			r.f = 0xFF;
			r.reset_flag(registers::flag::NULL_3);
			REQUIRE(0b11110111 == r.f);

			r.f = 0xFF;
			r.reset_flag(registers::flag::CARRY);
			REQUIRE(0b11101111 == r.f);

			r.f = 0xFF;
			r.reset_flag(registers::flag::HALF_CARRY);
			REQUIRE(0b11011111 == r.f);

			r.f = 0xFF;
			r.reset_flag(registers::flag::SUB);
			REQUIRE(0b10111111 == r.f);

			r.f = 0xFF;
			r.reset_flag(registers::flag::ZERO);
			REQUIRE(0b01111111 == r.f);
		}

		SECTION("Write_Read_Mantain_Order")
		{
			registers r;

			r.af(0xAF);
			r.bc(0xBC);
			r.de(0xDE);
			r.hl(0x99);

			REQUIRE(0xAF == r.af());
			REQUIRE(0xBC == r.bc());
			REQUIRE(0xDE == r.de());
			REQUIRE(0x99 == r.hl());

		}
	};
}