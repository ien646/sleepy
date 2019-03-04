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

		enum class flag : u8
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

		u8 a = 0x00;
		u8 f = 0x00;
		u8 b = 0x00;
		u8 c = 0x00;
		u8 d = 0x00;
		u8 e = 0x00;
		u8 h = 0x00;
		u8 l = 0x00;

		u16 pc = 0x0000;
		u16 sp = 0x0000;

		void af(u16 value);
		void bc(u16 value);
		void de(u16 value);
		void hl(u16 value);

		u16 af() const noexcept;
		u16 bc() const noexcept;
		u16 de() const noexcept;
		u16 hl() const noexcept;

		void set_flag(flag flagMask);
		void set_flag(u8 flagMask);
		void reset_flag(flag flagMask);
		void reset_flag(u8 flagMask);
		void invert_flag(flag flagMask);
		void invert_flag(u8 flagMask);
		bool read_flag(flag flagMask);
		bool read_flag(u8 flagMask);
		
		void reset_flags();

		void zero_registers(bool zero_pc_sp = false);
	};
}