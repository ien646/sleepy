#include <sleepy/instruction_impl.hpp>

namespace sleepy
{
	instruction_impl::instruction_impl(memory* mem_ptr, registers* reg_ptr)
		: _mem(mem_ptr)
		, _regs(reg_ptr)
	{	}

	void instruction_impl::opcode_add_a_v8(byte_t v8)
	{
		_regs->reset_flags();

		word_t result = _regs->a + v8;

		if ((byte_t)result == 0x00)
		{
			_regs->set_flag(FLAG_ZERO);
		}

		if (result > 0xFF)
		{
			_regs->set_flag(FLAG_CARRY);
			_regs->set_flag(FLAG_HCARRY);
		}
		else if (result > 0x0F)
		{
			_regs->set_flag(FLAG_HCARRY);
		}

		_regs->a = (byte_t)result;
	}

	void instruction_impl::opcode_add_hl_v16(word_t v16)
	{
		_regs->reset_flag(FLAG_SUB);

		dword result = _regs->hl() + v16;
		if (result > 0x0000FFFF)
		{
			_regs->set_flag(FLAG_CARRY);
			_regs->set_flag(FLAG_HCARRY);
		}
		else if (result > 0x000000FF)
		{
			_regs->set_flag(FLAG_HCARRY);
		}

		_regs->hl((word_t)result);
	}

	void instruction_impl::opcode_sub_a_v8(byte_t v8)
	{
		_regs->reset_flags();
		_regs->set_flag(FLAG_SUB);

		word_t result = _regs->a - v8;

		if ((byte_t)result == 0x00)
		{
			_regs->set_flag(FLAG_ZERO);
		}
		if (result > 0xFF)
		{
			_regs->set_flag(FLAG_CARRY);
			_regs->set_flag(FLAG_HCARRY);
		}
		else if (result > 0x0F)
		{
			_regs->set_flag(FLAG_HCARRY);
		}

		_regs->a = (byte_t)result;
	}

	void instruction_impl::opcode_adc_a_v8(byte_t v8)
	{
		word_t result = _regs->a + v8 + (_regs->read_flag(FLAG_CARRY) ? 1 : 0);

		_regs->reset_flags();

		if ((byte_t)result == 0x00)
		{
			_regs->set_flag(FLAG_ZERO);
		}

		if (result > 0xFF)
		{
			_regs->set_flag(FLAG_CARRY);
			_regs->set_flag(FLAG_HCARRY);
		}
		else if (result > 0x0F)
		{
			_regs->set_flag(FLAG_HCARRY);
		}

		_regs->a = (byte_t)result;
	}

	void instruction_impl::opcode_sbc_a_v8(byte_t v8)
	{
		word_t result = _regs->a - (v8 + (_regs->read_flag(FLAG_CARRY) ? 1 : 0));

		_regs->reset_flags();
		_regs->set_flag(FLAG_SUB);

		if ((byte_t)result == 0x00)
		{
			_regs->set_flag(FLAG_ZERO);
		}

		if (result > 0xFF)
		{
			_regs->set_flag(FLAG_CARRY);
			_regs->set_flag(FLAG_HCARRY);
		}
		else if (result > 0x0F)
		{
			_regs->set_flag(FLAG_HCARRY);
		}

		_regs->a = (byte_t)result;
	}

	void instruction_impl::opcode_and_a_v8(byte_t v8)
	{
		_regs->reset_flags();
		_regs->set_flag(FLAG_SUB);

		byte_t result = (_regs->a & v8);

		if (result == 0x00)
		{
			_regs->set_flag(FLAG_ZERO);
		}

		_regs->a = result;
	}

	void instruction_impl::opcode_or_a_v8(byte_t v8)
	{
		_regs->reset_flags();

		byte_t result = (_regs->a | v8);

		if (result == 0x00)
		{
			_regs->set_flag(FLAG_ZERO);
		}

		_regs->a = result;
	}

	void instruction_impl::opcode_xor_a_v8(byte_t v8)
	{
		_regs->reset_flags();

		byte_t result = (_regs->a ^ v8);

		if (result == 0x00)
		{
			_regs->set_flag(FLAG_ZERO);
		}

		_regs->a = result;
	}

	void instruction_impl::opcode_inc_r8(reg8_t& reg)
	{
		_regs->reset_flag(FLAG_ZERO);
		_regs->reset_flag(FLAG_HCARRY);
		_regs->reset_flag(FLAG_SUB);

		++reg;

		if (reg == 0x00)
		{
			_regs->set_flag(FLAG_ZERO);
		}

		if (reg > 0x0F)
		{
			_regs->set_flag(FLAG_HCARRY);
		}
	}

	void instruction_impl::opcode_dec_r8(reg8_t& reg)
	{
		_regs->reset_flag(FLAG_ZERO);
		_regs->reset_flag(FLAG_HCARRY);
		_regs->set_flag(FLAG_SUB);

		--reg;

		if (reg == 0x00)
		{
			_regs->set_flag(FLAG_ZERO);
		}

		if (reg > 0x0F)
		{
			_regs->set_flag(FLAG_HCARRY);
		}
	}

	void instruction_impl::opcode_cp_r8(byte_t reg)
	{
		_regs->reset_flags();
		_regs->set_flag(FLAG_SUB);

		word_t result = _regs->a - reg;

		if ((byte_t)result == 0x00)
		{
			_regs->set_flag(FLAG_ZERO);
		}
		if (result > 0xFF)
		{
			_regs->set_flag(FLAG_CARRY);
			_regs->set_flag(FLAG_HCARRY);
		}
		else if (result > 0x0F)
		{
			_regs->set_flag(FLAG_HCARRY);
		}
		/* -- omit result -- */
	}

	void instruction_impl::opcode_rrca()
	{
		bool bit_0 = get_bit(_regs->a, 0);

		_regs->reset_flags();

		byte_t result = (_regs->a >> 1);
		if (bit_0)
		{
			_regs->set_flag(FLAG_CARRY);
			result |= 0x80;
		}

		_regs->a = result;
	}

	void instruction_impl::opcode_rra()
	{
		bool bit_0 = get_bit(_regs->a, 0);

		_regs->reset_flags();

		byte_t result = (_regs->a >> 1);
		if (bit_0)
		{
			_regs->set_flag(FLAG_CARRY);
		}

		_regs->a = result;
	}

	void instruction_impl::opcode_rlca()
	{
		bool bit_7 = get_bit(_regs->a, 7);

		_regs->reset_flags();

		byte_t result = (_regs->a << 1);
		if (bit_7)
		{
			_regs->set_flag(FLAG_CARRY);
			result |= 0x01;
		}

		_regs->a = result;
	}

	void instruction_impl::opcode_rla()
	{
		bool bit_7 = get_bit(_regs->a, 7);

		_regs->reset_flags();

		byte_t result = (_regs->a << 1);
		if (bit_7)
		{
			_regs->set_flag(FLAG_CARRY);
		}

		_regs->a = result;
	}

	void instruction_impl::opcode_cpl()
	{
		_regs->set_flag(FLAG_SUB);
		_regs->set_flag(FLAG_HCARRY);
		_regs->a ^= 0xFF;
	}

	void instruction_impl::opcode_ccf()
	{
		_regs->reset_flag(FLAG_SUB);
		_regs->reset_flag(FLAG_HCARRY);
		_regs->invert_flag(FLAG_CARRY);
	}

	void instruction_impl::opcode_daa()
	{
		byte_t lowNibble = 0x0F & _regs->a;
		byte_t hiNibble = (0xF0 & _regs->a) >> 4;
		if ((lowNibble > 9) || (_regs->read_flag(FLAG_HCARRY)))
		{
			_regs->a += 0x06;
		}
		if ((hiNibble > 9) || (_regs->read_flag(FLAG_CARRY)))
		{
			_regs->a += 0x60;
			_regs->set_flag(FLAG_CARRY);
		}
		if (_regs->a == 0x00)
		{
			_regs->set_flag(FLAG_ZERO);
		}
		_regs->reset_flag(FLAG_HCARRY);
	}
}