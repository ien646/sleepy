#include <sleepy/instruction_impl.hpp>

#include <sleepy/registers.hpp>
#include <sleepy/memory.hpp>

namespace sleepy
{
	instruction_impl::instruction_impl(memory* mem_ptr, registers* reg_ptr)
		: _mem(mem_ptr)
		, _regs(reg_ptr)
	{	}

	void instruction_impl::opcode_add_a_v8(u8 v8)
	{
		_regs->reset_flags();

		u16 result = U16(_regs->a) + U16(v8);

		// Z
		if (U8(result) == 0x00)
		{
			_regs->set_flag(registers::flag::ZERO);
		}
		// C
		if (result > 0xFF)
		{
			_regs->set_flag(registers::flag::CARRY);
		}
		// H
		if((lonibble(v8) + lonibble(_regs->a)) > 0x0F)
		{
			_regs->set_flag(registers::flag::HALF_CARRY);
		}
		_regs->a = U8(result);
	}

	void instruction_impl::opcode_add_hl_v16(u16 v16)
	{
		_regs->reset_flag(registers::flag::SUB);

		u32 result = U32(_regs->hl()) + U32(v16);

		// C
		if (result > 0x0000FFFF)
		{
			_regs->set_flag(registers::flag::CARRY);
		}
		// H
		if((lonibble(hibyte(v16)) + lonibble(hibyte(_regs->hl()))) > 0x0F)
		{
			_regs->set_flag(registers::flag::HALF_CARRY);
		}
		_regs->hl(U16(result));
	}

	void instruction_impl::opcode_sub_a_v8(u8 v8)
	{
		_regs->reset_flags();
		_regs->set_flag(registers::flag::SUB);

		u16 result = U16(_regs->a) - v8;

		if (U8(result) == 0x00)
		{
			_regs->set_flag(registers::flag::ZERO);
		}
		if (result > 0xFF)
		{
			_regs->set_flag(registers::flag::CARRY);
		}
		if (U8(lonibble(_regs->a) - lonibble(v8)) > 0x0F)
		{
			_regs->set_flag(registers::flag::HALF_CARRY);
		}

		_regs->a = U8(result);
	}

	void instruction_impl::opcode_adc_a_v8(u8 v8)
	{
		u8 carry = _regs->read_flag(registers::flag::CARRY) ? U8(1) : U8(0);
		u16 result = U16(_regs->a) + U16(v8) + carry;

		_regs->reset_flags();

		if (U8(result) == 0x00)
		{
			_regs->set_flag(registers::flag::ZERO);
		}

		if (result > 0xFF)
		{
			_regs->set_flag(registers::flag::CARRY);
		}
		if ((lonibble(v8) + lonibble(_regs->a) + carry) > 0x0F)
		{
			_regs->set_flag(registers::flag::HALF_CARRY);
		}

		_regs->a = U8(result);
	}

	void instruction_impl::opcode_sbc_a_v8(u8 v8)
	{
		u8 carry = _regs->read_flag(registers::flag::CARRY) ? 1 : 0;
		u16 result = U16(_regs->a) - (v8 + carry);

		_regs->reset_flags();
		_regs->set_flag(registers::flag::SUB);

		// Z
		if (U8(result) == 0x00)
		{
			_regs->set_flag(registers::flag::ZERO);
		}
		// C
		if (result > 0xFF)
		{
			_regs->set_flag(registers::flag::CARRY);
		}
		// H
		if (U8(lonibble(_regs->a) - lonibble(v8 + carry)) > 0x0F)
		{
			_regs->set_flag(registers::flag::HALF_CARRY);
		}

		_regs->a = U8(result);
	}

	void instruction_impl::opcode_and_a_v8(u8 v8)
	{
		_regs->reset_flags();
		_regs->set_flag(registers::flag::SUB);

		u8 result = (_regs->a & v8);

		if (result == 0x00)
		{
			_regs->set_flag(registers::flag::ZERO);
		}

		_regs->a = result;
	}

	void instruction_impl::opcode_or_a_v8(u8 v8)
	{
		_regs->reset_flags();

		u8 result = (_regs->a | v8);

		if (result == 0x00)
		{
			_regs->set_flag(registers::flag::ZERO);
		}

		_regs->a = result;
	}

	void instruction_impl::opcode_xor_a_v8(u8 v8)
	{
		_regs->reset_flags();

		u8 result = (_regs->a ^ v8);

		if (result == 0x00)
		{
			_regs->set_flag(registers::flag::ZERO);
		}

		_regs->a = result;
	}

	void instruction_impl::opcode_inc_r8(u8& reg)
	{
		_regs->reset_flag(registers::flag::ZERO);
		_regs->reset_flag(registers::flag::HALF_CARRY);
		_regs->reset_flag(registers::flag::SUB);

		if(lonibble(reg) == 0x0F)
		{
			_regs->set_flag(registers::flag::HALF_CARRY);
		}

		++reg;

		if (reg == 0x00)
		{
			_regs->set_flag(registers::flag::ZERO);
		}
	}

	void instruction_impl::opcode_dec_r8(u8& reg)
	{
		_regs->reset_flag(registers::flag::ZERO);
		_regs->reset_flag(registers::flag::HALF_CARRY);
		_regs->set_flag(registers::flag::SUB);

		if (lonibble(reg) == 0x00)
		{
			_regs->set_flag(registers::flag::HALF_CARRY);
		}

		--reg;

		if (reg == 0x00)
		{
			_regs->set_flag(registers::flag::ZERO);
		}
	}

	void instruction_impl::opcode_cp_r8(u8 reg)
	{
		_regs->reset_flags();
		_regs->set_flag(registers::flag::SUB);

		u16 result = U16(_regs->a) - U16(reg);

		if (U8(result) == 0x00)
		{
			_regs->set_flag(registers::flag::ZERO);
		}
		if (result > 0xFF)
		{
			_regs->set_flag(registers::flag::CARRY);
		}
		if (U8(lonibble(_regs->a) - lonibble(reg)) > 0x0F)
		{
			_regs->set_flag(registers::flag::HALF_CARRY);
		}
	}

	void instruction_impl::opcode_rrca()
	{
		bool bit_0 = get_bit(_regs->a, 0);

		_regs->reset_flags();

		u8 result = (_regs->a >> 1);
		if (bit_0)
		{
			_regs->set_flag(registers::flag::CARRY);
			result |= 0x80;
		}

		_regs->a = result;
	}

	void instruction_impl::opcode_rra()
	{
		bool bit_0 = get_bit(_regs->a, 0);

		_regs->reset_flags();

		u8 result = (_regs->a >> 1);
		if (bit_0)
		{
			_regs->set_flag(registers::flag::CARRY);
		}

		_regs->a = result;
	}

	void instruction_impl::opcode_rlca()
	{
		bool bit_7 = get_bit(_regs->a, 7);

		_regs->reset_flags();

		u8 result = (_regs->a << 1);
		if (bit_7)
		{
			_regs->set_flag(registers::flag::CARRY);
			result |= 0x01;
		}

		_regs->a = result;
	}

	void instruction_impl::opcode_rla()
	{
		bool bit_7 = get_bit(_regs->a, 7);

		_regs->reset_flags();

		u8 result = (_regs->a << 1);
		if (bit_7)
		{
			_regs->set_flag(registers::flag::CARRY);
		}

		_regs->a = result;
	}

	void instruction_impl::opcode_cpl()
	{
		_regs->set_flag(registers::flag::SUB);
		_regs->set_flag(registers::flag::HALF_CARRY);
		_regs->a ^= 0xFF;
	}

	void instruction_impl::opcode_ccf()
	{
		_regs->reset_flag(registers::flag::SUB);
		_regs->reset_flag(registers::flag::HALF_CARRY);
		_regs->invert_flag(registers::flag::CARRY);
	}

	void instruction_impl::opcode_daa()
	{
		u8 lo_nibble = 0x0F & _regs->a;
		u8 hi_nibble = (0xF0 & _regs->a) >> 4;
		if ((lo_nibble > 9) || (_regs->read_flag(registers::flag::HALF_CARRY)))
		{
			_regs->a += 0x06;
		}
		if ((hi_nibble > 9) || (_regs->read_flag(registers::flag::CARRY)))
		{
			_regs->a += 0x60;
			_regs->set_flag(registers::flag::CARRY);
		}
		if (_regs->a == 0x00)
		{
			_regs->set_flag(registers::flag::ZERO);
		}
		_regs->reset_flag(registers::flag::HALF_CARRY);
	}

	void instruction_impl::opcode_push_r16(u16 r16)
	{
		_regs->sp -= 2;
		_mem->write_word(_regs->sp, r16);
	}

	void instruction_impl::opcode_call_a16(const u8* args)
	{
		// jump address
		u16 a16 = read_word(args); 
		// return address
		u16 save_addr = read_word(args + 2); 

		// push operation
		_regs->sp -= 2;
		_mem->write_word(_regs->sp, save_addr);

		// jump
		_regs->pc = a16;
	}

	void instruction_impl::opcode_ret()
	{
		_regs->pc = _mem->read_word(_regs->sp);
		_regs->sp += 2;
	}

	void instruction_impl::opcode_rlc(u8& vref)
	{
		_regs->reset_flags();
		if(vref == 0x00) 
		{
			_regs->set_flag(registers::flag::ZERO);
			return;
		}

		u16 aux = U16(vref) << 1;
		if(aux > 0xFF)
		{
			aux += 1; // rotated bit
			_regs->set_flag(registers::flag::CARRY);
		}

		vref = U8(aux);
	}

	void instruction_impl::opcode_rrc(u8& vref)
	{
		_regs->reset_flags();
		if(vref == 0x00) 
		{
			_regs->set_flag(registers::flag::ZERO);
			return;
		}

		bool rbit = vref % 2 == 1;
		u16 aux = U16(vref) >> 1;
		if(rbit) 
		{
			aux |= 0x80u;
			_regs->set_flag(registers::flag::CARRY);
		}
		
		vref = U8(aux);
	}

	void instruction_impl::opcode_rl(u8& vref)
	{
		u8 carry = _regs->read_flag(registers::flag::CARRY) ? 1 : 0;
		_regs->reset_flags();
		if(vref == 0x00 && !carry) 
		{
			_regs->set_flag(registers::flag::ZERO);
			return;
		}

		u16 aux = U16(vref) << 1;

		if(aux > 0xFF)
		{
			_regs->set_flag(registers::flag::CARRY);
		}
		aux += carry;
		if(U8(aux) == 0x00u) { _regs->set_flag(registers::flag::ZERO); }
		
		vref = U8(aux);
	}

	void instruction_impl::opcode_rr(u8& vref)
	{
		bool carry = _regs->read_flag(registers::flag::CARRY);
		_regs->reset_flags();
		if(vref == 0x00 && !carry) 
		{
			_regs->set_flag(registers::flag::ZERO);
			return;
		}

		bool bit0 = get_bit(vref, 0);
		u16 aux = U16(vref) >> 1;

		if(bit0) { _regs->set_flag(registers::flag::CARRY); }
		if(carry) { aux |= 0x80u; }
		if(U8(aux) == 0x00u) { _regs->set_flag(registers::flag::ZERO); }

        vref = U8(aux);
	}

	void instruction_impl::opcode_sla(u8& vref)
	{
		bool carry = vref >= 0x80u;
		_regs->reset_flags();

		u16 aux = U16(vref) << 1;
		aux &= 0xFEu;
		if(carry) { _regs->set_flag(registers::flag::CARRY); } 
		if(U8(aux) == 0x00u) { _regs->set_flag(registers::flag::ZERO); }

		vref = U8(aux);
	}
}