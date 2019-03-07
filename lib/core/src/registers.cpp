#include <sleepy/registers.hpp>

namespace sleepy
{
	void registers::af(u16 value)
	{
		a = hibyte(value);
		f = lobyte(value);
	}

	void registers::bc(u16 value)
	{
		b = hibyte(value);
		c = lobyte(value);
	}

	void registers::de(u16 value)
	{
		d = hibyte(value);
		e = lobyte(value);
	}

	void registers::hl(u16 value)
	{
		h = hibyte(value);
		l = lobyte(value);
	}

	u16 registers::af() const noexcept
	{
		return compose_word(a, f);
	}

	u16 registers::bc() const noexcept
	{
		return compose_word(b, c);
	}

	u16 registers::de() const noexcept
	{
		return compose_word(d, e);
	}

	u16 registers::hl() const noexcept
	{
		return compose_word(h, l);
	}

	void registers::set_flag(flag flagMask)
	{
		f |= U8(flagMask);
	}

	void registers::set_flag(u8 flagMask)
	{
		f |= flagMask;
	}

	void registers::reset_flag(flag flagMask)
	{
		f &= (U8(flagMask) ^ 0xFF);
	}

	void registers::reset_flag(u8 flagMask)
	{
		f &= (flagMask ^ 0xFF);
	}

	void registers::invert_flag(flag flagMask)
	{
		f ^= U8(flagMask);
	}

	void registers::invert_flag(u8 flagMask)
	{
		f ^= flagMask;
	}

	bool registers::read_flag(flag flagMask) const
	{
		return (U8(flagMask) | f) == f;
	}

	bool registers::read_flag(u8 flagMask) const
	{
		return (flagMask | f) == f;
	}

	void registers::reset_flags()
	{
		f = 0x00;
	}

	void registers::zero_registers(bool zero_PC_SP)
	{
		a = 0x00;
		f = 0x00;
		b = 0x00;
		c = 0x00;
		d = 0x00;
		e = 0x00;
		h = 0x00;
		l = 0x00;

		if (zero_PC_SP)
		{
			pc = 0x0000;
			sp = 0x0000;
		}
	}
}