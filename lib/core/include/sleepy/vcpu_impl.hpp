#pragma once

#include <sleepy/common.hpp>
#include <sleepy/vcpu_instruction.hpp>
#include <sleepy/instruction_impl.hpp>
#include <sleepy/instruction_map.hpp>

#include <string>
#include <map>

namespace sleepy
{
	class memory;
	class registers;

	class vcpu_impl
	{
	public:
		vcpu_impl() = delete;
		vcpu_impl(memory* mem_ptr, registers* regs_ptr);

		instruction_map inst_map;

		void enable_interrupts() { _interrupts_enabled = true; }
		void disable_interrupts() { _interrupts_enabled = false; }
		bool interrupts_enabled() const noexcept { return _interrupts_enabled; }
        void delay_cycles([[maybe_unused]] size_t count) { return; }

	private:
		registers* _regs;
		memory* _mem;
		std::unique_ptr<instruction_impl> _inst_impl;
		bool _interrupts_enabled = false;		

		void init_inst_map();

		/* -- Non prefixed opcodes -- */
		void initmap_misc();
		void initmap_ld_a_x8();
		void initmap_ld_b_x8();
		void initmap_ld_c_x8();
		void initmap_ld_d_x8();
		void initmap_ld_e_x8();
		void initmap_ld_h_x8();
		void initmap_ld_l_x8();
		void initmap_ld_phl_x8();
		void initmap_ld_r8_d8();
		void initmap_ld_ptr_a();
		void initmap_ld_a_ptr();
		void initmap_ld_r16_d16();
		void initmap_ld_misc();
		void initmap_add_a_x8();
		void initmap_add_hl_r16();
		void initmap_sub_a_x8();
		void initmap_adc_a_x8();
		void initmap_sbc_a_x8();
		void initmap_and_a_x8();
		void initmap_or_a_x8();
		void initmap_xor_a_x8();
		void initmap_inc_r8();
		void initmap_inc_r16();
		void initmap_dec_r8();
		void initmap_dec_r16();
		void initmap_cp_r8();
		void initmap_bitrotations();
		void initmap_rst();
		void initmap_jumps();
		void initmap_push();
		void initmap_pop();
		void initmap_call();
		void initmap_ret();

		/* -- 0xCB prefixed opcodes -- */
		void initmap_rlc();
		void initmap_rrc();
		void initmap_rl();
		void initmap_rr();
		void initmap_sla();
		void initmap_sra();
		void initmap_swap();

		void add_instruction(
			opcode opc, 
			const std::string& mnem, 
			u8 cycc, 
			u8 pc_offset, 
			u8 arg_count,
			const vcpu_instruction::op_call_t& call);
	};
}