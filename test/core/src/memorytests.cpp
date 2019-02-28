#include <catch2/catch.hpp>
#include <sleepy/memory.hpp>

using namespace sleepy;

namespace sleepy
{		
	TEST_CASE("MemoryTests")
	{
		SECTION("WriteWord_CorrectEndianess")
		{
			// Setup
			memory memory;
			byte_t* data = memory.data();

			// Run
			memory.write_word((addr_t)0x0000, (word_t)0xF0AE);
			
			// Assert
			REQUIRE(0xAE == data[0]);
			REQUIRE(0xF0 == data[1]);
		}

		SECTION("ReadWord_CorrectEndianess")
		{
			// Setup
			memory memory;
			byte_t* data = memory.data();
			((word_t*)memory.data())[0] = 0xF0AE;

			// Run
			word_t res = memory.read_word((addr_t)0x0000);

			// Assert
			REQUIRE(0xAE == data[0]);
			REQUIRE(0xF0 == data[1]);

			REQUIRE(0xF0AE == res);
		}

		SECTION("Write_Read_Byte_CorrectAddr")
		{
			// Setup
			memory memory;
			memory.write_byte(0xFA0F, 0xAD);
			memory.write_byte(0xAA0A, 0xB7);

			REQUIRE(0xAD == memory.read_byte(0xFA0F));
			REQUIRE(0xB7 == memory.read_byte(0xAA0A));
		}

		SECTION("Write_Read_Word_CorrectAddr")
		{
			// Setup
			memory memory;
			memory.write_word(0xFA0F, 0xADAD);
			memory.write_word(0xAA0A, 0xB7B7);

			REQUIRE(0xADAD == memory.read_word(0xFA0F));
			REQUIRE(0xB7B7 == memory.read_word(0xAA0A));
		}

		SECTION("MemoryRangeTest")
		{
			memory memory;
			memory.write_byte(0x0000, 0x00);
			memory.write_byte(0xFFFF, 0x00);
		}
	};
}