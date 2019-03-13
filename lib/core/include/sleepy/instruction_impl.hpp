#pragma once

#include <sleepy/common.hpp>

namespace sleepy
{
	class memory;
	class registers;

	class instruction_impl
	{
	private:
		memory* _mem;
		registers* _regs;

	public:
		instruction_impl(memory* mem_ptr, registers* reg_ptr);

		void opcode_add_a_v8(u8 v8);
		void opcode_add_hl_v16(u16 v16);
		void opcode_sub_a_v8(u8 v8);
		void opcode_adc_a_v8(u8 v8);
		void opcode_sbc_a_v8(u8 v8);

		void opcode_and_a_v8(u8 v8);
		void opcode_or_a_v8(u8 v8);
		void opcode_xor_a_v8(u8 v8);
		void opcode_inc_r8(u8& reg);
		void opcode_dec_r8(u8 & reg);
		void opcode_cp_r8(u8 reg);

		void opcode_rrca();
		void opcode_rra();
		void opcode_rlca();
		void opcode_rla();
		void opcode_cpl();
		void opcode_ccf();
		void opcode_daa();

		void opcode_push_r16(u16 r16);

		void opcode_call_a16(const u8* args);
		void opcode_ret();

		void opcode_rlc(u8& vref);
		void opcode_rrc(u8& vref);
		void opcode_rl(u8& vref);
		void opcode_rr(u8& vref);
		void opcode_sla(u8& vref);
		void opcode_sra(u8& vref);
		void opcode_swap(u8& vref);
		void opcode_srl(u8& vref);
		void opcode_bit(u8 val, u8 index);
		void opcode_res(u8& val, u8 index);
		void opcode_set(u8& val, u8 index);
	};
}