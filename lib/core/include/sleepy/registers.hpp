#pragma once

#include <sleepy/common.hpp>

namespace sleepy
{
	class registers
	{
	public:
		registers() noexcept {}
		registers(const registers& copy_src) = default;
		registers(registers&& move_src) = default;

		enum class flag : byte_t
		{
			ZERO	= 1 << 7,
			SUB		= 1 << 6,
			HALF_CARRY	= 1 << 5,
			CARRY	= 1 << 4,
			NULL_3	= 1 << 3,
			NULL_2	= 1 << 2,
			NULL_1	= 1 << 1,
			NULL_0	= 1 << 0,
		};

		reg8_t a = 0x00;
		reg8_t f = 0x00;
		reg8_t b = 0x00;
		reg8_t c = 0x00;
		reg8_t d = 0x00;
		reg8_t e = 0x00;
		reg8_t h = 0x00;
		reg8_t l = 0x00;

		reg16_t pc = 0x0000;
		reg16_t sp = 0x0000;

		void af(word_t value);
		void bc(word_t value);
		void de(word_t value);
		void hl(word_t value);

		word_t af();
		word_t bc();
		word_t de();
		word_t hl();

		void set_flag(flag flagMask);
		void set_flag(byte_t flagMask);
		void reset_flag(flag flagMask);
		void reset_flag(byte_t flagMask);
		void invert_flag(flag flagMask);
		void invert_flag(byte_t flagMask);
		bool read_flag(flag flagMask);
		bool read_flag(byte_t flagMask);
		
		void reset_flags();

		void zero_registers(bool zero_pc_sp = false);
	};
}