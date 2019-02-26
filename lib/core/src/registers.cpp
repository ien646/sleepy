#include <sleepy/registers.hpp>

namespace sleepy
{
	void registers::af(word_t value)
	{
		a = hibyte(value);
		f = lobyte(value);
	}

	void registers::bc(word_t value)
	{
		b = hibyte(value);
		c = lobyte(value);
	}

	void registers::de(word_t value)
	{
		d = hibyte(value);
		e = lobyte(value);
	}

	void registers::hl(word_t value)
	{
		h = hibyte(value);
		l = lobyte(value);
	}

	word_t registers::af() const noexcept
	{
		return compose_word(a, f);
	}

	word_t registers::bc() const noexcept
	{
		return compose_word(b, c);
	}

	word_t registers::de() const noexcept
	{
		return compose_word(d, e);
	}

	word_t registers::hl() const noexcept
	{
		return compose_word(h, l);
	}

	void registers::set_flag(flag flagMask)
	{
		f |= (byte_t)flagMask;
	}

	void registers::set_flag(byte_t flagMask)
	{
		f |= flagMask;
	}

	void registers::reset_flag(flag flagMask)
	{
		f &= ((byte_t)flagMask ^ 0xFF);
	}

	void registers::reset_flag(byte_t flagMask)
	{
		f &= (flagMask ^ 0xFF);
	}

	void registers::invert_flag(flag flagMask)
	{
		f ^= (byte_t)flagMask;
	}

	void registers::invert_flag(byte_t flagMask)
	{
		f ^= flagMask;
	}

	bool registers::read_flag(flag flagMask)
	{
		return ((byte_t)flagMask | f) == f;
	}

	bool registers::read_flag(byte_t flagMask)
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