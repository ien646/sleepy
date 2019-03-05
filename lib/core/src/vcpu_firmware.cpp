#include <sleepy/vcpu_firmware.hpp>

#include <sleepy/memory.hpp>
#include <sleepy/registers.hpp>

#define RET_NO_ARGS_REF UNREFERENCED_PARAMETER(args);return

namespace sleepy
{
	vcpu_firmware::vcpu_firmware(memory* mem_ptr, registers* regs_ptr)
		: _mem(mem_ptr)
		, _regs(regs_ptr)
	{
		_instImpl = std::make_unique<instruction_impl>(mem_ptr, regs_ptr);
		init_inst_map();
	}

	void vcpu_firmware::init_inst_map()
	{
		initmap_misc();

		initmap_ld_a_x8();
		initmap_ld_b_x8();
		initmap_ld_c_x8();
		initmap_ld_d_x8();
		initmap_ld_e_x8();
		initmap_ld_h_x8();
		initmap_ld_l_x8();
		initmap_ld_phl_x8();
		initmap_ld_r8_d8();
		initmap_ld_ptr_a();
		initmap_ld_a_ptr();
		initmap_ld_r16_d16();
		initmap_ld_misc();

		initmap_add_a_x8();
		initmap_add_hl_r16();
		initmap_sub_a_x8();
		initmap_adc_a_x8();
		initmap_sbc_a_x8();

		initmap_and_a_x8();
		initmap_or_a_x8();
		initmap_xor_a_x8();

		initmap_inc_r8();
		initmap_inc_r16();
		initmap_dec_r8();
		initmap_dec_r16();

		initmap_cp_r8();
		initmap_bitrotations();
		initmap_rst();

		initmap_jumps();
		
		initmap_push();
		initmap_pop();

		initmap_call();
		initmap_ret();
	}

	void vcpu_firmware::initmap_misc()
	{
		add_instruction(opcode(0x00), "NOP", 4, 1, 0, [&](const u8* args)
		{
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x10), "STOP", 4, 2, 0, [&](const u8* args)
		{
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x76), "HALT", 4, 1, 0, [&](const u8* args)
		{
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0xF3), "DI", 4, 1, 0, [&](const u8* args)
		{
			_interrupts_enabled = false;
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0xFB), "EI", 4, 1, 0, [&](const u8* args)
		{
			_interrupts_enabled = true;
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x2F), "CPL", 4, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_cpl();
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x3F), "CCF", 4, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_ccf();
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x27), "DAA", 4, 1, 0, [&](const u8* args)
		{			
			_instImpl->opcode_daa();
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x37), "SCF", 4, 1, 0, [&](const u8* args)
		{
			_regs->set_flag(registers::flag::CARRY);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0xE8), "ADD SP,d8", 16, 2, 1, [&](const u8* args)
		{
			u8 d8 = *&args[0];
			u32 val = _regs->sp + d8;
			_regs->sp = (u16)val;

			_regs->reset_flags();

			if (val > BYTE_MAX)
			{
				_regs->set_flag(registers::flag::CARRY);
				_regs->set_flag(registers::flag::HALF_CARRY);
			}
			else if (val > HBYTE_MAX)
			{
				_regs->set_flag(registers::flag::HALF_CARRY);
			}
		});		
	}

	void vcpu_firmware::initmap_ld_a_x8()
	{
		add_instruction(opcode(0x7F), "LD A,A", 4, 1, 0, [&](const u8* args)
		{
			_regs->a = _regs->a;
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x78), "LD A,B", 4, 1, 0, [&](const u8* args)
		{
			_regs->a = _regs->b;
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x79), "LD A,C", 4, 1, 0, [&](const u8* args)
		{
			_regs->a = _regs->c;
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x7A), "LD A,D", 4, 1, 0, [&](const u8* args)
		{
			_regs->a = _regs->d;
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x7B), "LD A,E", 4, 1, 0, [&](const u8* args)
		{
			_regs->a = _regs->e;
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x7C), "LD A,H", 4, 1, 0, [&](const u8* args)
		{
			_regs->a = _regs->h;
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x7D), "LD A,L", 4, 1, 0, [&](const u8* args)
		{
			_regs->a = _regs->l;
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x7E), "LD A,(HL)", 8, 1, 0, [&](const u8* args)
		{
			u16 addr = (u16)_regs->hl();
			_regs->a = _mem->read_byte(addr);
			RET_NO_ARGS_REF;
		});
	}

	void vcpu_firmware::initmap_ld_b_x8()
	{
		add_instruction(opcode(0x47), "LD B,A", 4, 1, 0, [&](const u8* args)
		{
			_regs->b = _regs->a;
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x40), "LD B,B", 4, 1, 0, [&](const u8* args)
		{
			_regs->b = _regs->b;
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x41), "LD B,C", 4, 1, 0, [&](const u8* args)
		{
			_regs->b = _regs->c;
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x42), "LD B,D", 4, 1, 0, [&](const u8* args)
		{
			_regs->b = _regs->d;
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x43), "LD B,E", 4, 1, 0, [&](const u8* args)
		{
			_regs->b = _regs->e;
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x44), "LD B,H", 4, 1, 0, [&](const u8* args)
		{
			_regs->b = _regs->h;
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x45), "LD B,L", 4, 1, 0, [&](const u8* args)
		{
			_regs->b = _regs->l;
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x46), "LD B,(HL)", 8, 1, 0, [&](const u8* args)
		{
			u16 addr = (u16)_regs->hl();
			_regs->b = _mem->read_byte(addr);
			RET_NO_ARGS_REF;
		});
	}

	void vcpu_firmware::initmap_ld_c_x8()
	{
		add_instruction(opcode(0x4F), "LD C,A", 4, 1, 0, [&](const u8* args)
		{
			_regs->c = _regs->a;
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x48), "LD C,B", 4, 1, 0, [&](const u8* args)
		{
			_regs->c = _regs->b;
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x49), "LD C,C", 4, 1, 0, [&](const u8* args)
		{
			_regs->c = _regs->c;
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x4A), "LD C,D", 4, 1, 0, [&](const u8* args)
		{
			_regs->c = _regs->d;
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x4B), "LD C,E", 4, 1, 0, [&](const u8* args)
		{
			_regs->c = _regs->e;
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x4C), "LD C,H", 4, 1, 0, [&](const u8* args)
		{
			_regs->c = _regs->h;
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x4D), "LD C,L", 4, 1, 0, [&](const u8* args)
		{
			_regs->c = _regs->l;
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x4E), "LD C,(HL)", 8, 1, 0, [&](const u8* args)
		{
			u16 addr = (u16)_regs->hl();
			_regs->c = _mem->read_byte(addr);
			RET_NO_ARGS_REF;
		});
	}

	void vcpu_firmware::initmap_ld_d_x8()
	{
		add_instruction(opcode(0x57), "LD D,A", 4, 1, 0, [&](const u8* args)
		{
			_regs->d = _regs->a;
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x50), "LD D,B", 4, 1, 0, [&](const u8* args)
		{
			_regs->d = _regs->b;
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x51), "LD D,C", 4, 1, 0, [&](const u8* args)
		{
			_regs->d = _regs->c;
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x52), "LD D,D", 4, 1, 0, [&](const u8* args)
		{
			_regs->d = _regs->d;
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x53), "LD D,E", 4, 1, 0, [&](const u8* args)
		{
			_regs->d = _regs->e;
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x54), "LD D,H", 4, 1, 0, [&](const u8* args)
		{
			_regs->d = _regs->h;
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x55), "LD D,L", 4, 1, 0, [&](const u8* args)
		{
			_regs->d = _regs->l;
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x56), "LD D,(HL)", 8, 1, 0, [&](const u8* args)
		{
			u16 addr = (u16)_regs->hl();
			_regs->d = _mem->read_byte(addr);
			RET_NO_ARGS_REF;
		});
	}

	void vcpu_firmware::initmap_ld_e_x8()
	{
		add_instruction(opcode(0x5F), "LD E,A", 4, 1, 0, [&](const u8* args)
		{
			_regs->e = _regs->a;
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x58), "LD E,B", 4, 1, 0, [&](const u8* args)
		{
			_regs->e = _regs->b;
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x59), "LD E,C", 4, 1, 0, [&](const u8* args)
		{
			_regs->e = _regs->c;
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x5A), "LD E,D", 4, 1, 0, [&](const u8* args)
		{
			_regs->e = _regs->d;
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x5B), "LD E,E", 4, 1, 0, [&](const u8* args)
		{
			_regs->e = _regs->e;
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x5C), "LD E,H", 4, 1, 0, [&](const u8* args)
		{
			_regs->e = _regs->h;
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x5D), "LD E,L", 4, 1, 0, [&](const u8* args)
		{
			_regs->e = _regs->l;
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x5E), "LD E,(HL)", 8, 1, 0, [&](const u8* args)
		{
			u16 addr = (u16)_regs->hl();
			_regs->e = _mem->read_byte(addr);
			RET_NO_ARGS_REF;
		});		
	}

	void vcpu_firmware::initmap_ld_h_x8()
	{
		add_instruction(opcode(0x67), "LD H,A", 4, 1, 0, [&](const u8* args)
		{
			_regs->h = _regs->a;
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x60), "LD H,B", 4, 1, 0, [&](const u8* args)
		{
			_regs->h = _regs->b;
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x61), "LD H,C", 4, 1, 0, [&](const u8* args)
		{
			_regs->h = _regs->c;
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x62), "LD H,D", 4, 1, 0, [&](const u8* args)
		{
			_regs->h = _regs->d;
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x63), "LD H,E", 4, 1, 0, [&](const u8* args)
		{
			_regs->h = _regs->e;
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x64), "LD H,H", 4, 1, 0, [&](const u8* args)
		{
			_regs->h = _regs->h;
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x65), "LD H,L", 4, 1, 0, [&](const u8* args)
		{
			_regs->h = _regs->l;
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x66), "LD H,(HL)", 8, 1, 0, [&](const u8* args)
		{
			u16 addr = (u16)_regs->hl();
			_regs->h = _mem->read_byte(addr);
			RET_NO_ARGS_REF;
		});
	}

	void vcpu_firmware::initmap_ld_l_x8()
	{
		add_instruction(opcode(0x6F), "LD L,A", 4, 1, 0, [&](const u8* args)
		{
			_regs->l = _regs->a;
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x68), "LD L,B", 4, 1, 0, [&](const u8* args)
		{
			_regs->l = _regs->b;
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x69), "LD L,C", 4, 1, 0, [&](const u8* args)
		{
			_regs->l = _regs->c;
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x6A), "LD L,D", 4, 1, 0, [&](const u8* args)
		{
			_regs->l = _regs->d;
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x6B), "LD L,E", 4, 1, 0, [&](const u8* args)
		{
			_regs->l = _regs->e;
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x6C), "LD L,H", 4, 1, 0, [&](const u8* args)
		{
			_regs->l = _regs->h;
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x6D), "LD L,L", 4, 1, 0, [&](const u8* args)
		{
			_regs->l = _regs->l;
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x6E), "LD L,(HL)", 8, 1, 0, [&](const u8* args)
		{
			u16 addr = (u16)_regs->hl();
			_regs->l = _mem->read_byte(addr);
			RET_NO_ARGS_REF;
		});
	}

	void vcpu_firmware::initmap_ld_phl_x8()
	{
		add_instruction(opcode(0x77), "LD (HL),A", 8, 1, 0, [&](const u8* args)
		{
			_mem->write_byte(_regs->hl(), _regs->a);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x70), "LD (HL),B", 8, 1, 0, [&](const u8* args)
		{
			_mem->write_byte(_regs->hl(), _regs->b);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x71), "LD (HL),C", 8, 1, 0, [&](const u8* args)
		{
			_mem->write_byte(_regs->hl(), _regs->c);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x72), "LD (HL),D", 8, 1, 0, [&](const u8* args)
		{
			_mem->write_byte(_regs->hl(), _regs->d);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x73), "LD (HL),E", 8, 1, 0, [&](const u8* args)
		{
			_mem->write_byte(_regs->hl(), _regs->e);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x74), "LD (HL),H", 8, 1, 0, [&](const u8* args)
		{
			_mem->write_byte(_regs->hl(), _regs->h);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x75), "LD (HL),L", 8, 1, 0, [&](const u8* args)
		{
			_mem->write_byte(_regs->hl(), _regs->l);
			RET_NO_ARGS_REF;
		});
	}

	void vcpu_firmware::initmap_ld_r8_d8()
	{
		add_instruction(opcode(0x3E), "LD A,d8", 8, 2, 1, [&](const u8* args)
		{
			u8 d8 = args[0];
			_regs->a = d8;
		});

		add_instruction(opcode(0x06), "LD B,d8", 8, 2, 1, [&](const u8* args)
		{
			u8 d8 = args[0];
			_regs->b = d8;
		});

		add_instruction(opcode(0x0E), "LD C,d8", 8, 2, 1, [&](const u8* args)
		{
			u8 d8 = args[0];
			_regs->c = d8;
		});

		add_instruction(opcode(0x16), "LD D,d8", 8, 2, 1, [&](const u8* args)
		{
			u8 d8 = args[0];
			_regs->d = d8;
		});

		add_instruction(opcode(0x1E), "LD E,d8", 8, 2, 1, [&](const u8* args)
		{
			u8 d8 = args[0];
			_regs->e = d8;
		});

		add_instruction(opcode(0x26), "LD H,d8", 8, 2, 1, [&](const u8* args)
		{
			u8 d8 = args[0];
			_regs->h = d8;
		});

		add_instruction(opcode(0x2E), "LD L,d8", 8, 2, 1, [&](const u8* args)
		{
			u8 d8 = args[0];
			_regs->l = d8;
		});

		add_instruction(opcode(0x36), "LD (HL),d8", 12, 2, 1, [&](const u8* args)
		{
			u16 addr = _regs->hl();
			u8 d8 = args[0];
			_mem->write_byte(addr, d8);
		});
	}

	void vcpu_firmware::initmap_ld_ptr_a()
	{
		add_instruction(opcode(0x02), "LD (BC),A", 8, 1, 0, [&](const u8* args)
		{
			u16 addr = (u16)(_regs->bc());
			_mem->write_byte(addr, _regs->a);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x12), "LD (DE),A", 8, 1, 0, [&](const u8* args)
		{
			u16 addr = (u16)(_regs->de());
			_mem->write_byte(addr, _regs->a);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x22), "LD (HL+),A", 8, 1, 0, [&](const u8* args)
		{
			u16 addr = (u16)(_regs->hl());
			_mem->write_byte(addr, _regs->a);
			_regs->hl(_regs->hl() + 1);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x32), "LD (HL-),A", 8, 1, 0, [&](const u8* args)
		{
			u16 addr = (u16)(_regs->hl());
			_mem->write_byte(addr, _regs->a);
			_regs->hl(_regs->hl() - 1);
			RET_NO_ARGS_REF;
		});
	}

	void vcpu_firmware::initmap_ld_a_ptr()
	{
		add_instruction(opcode(0x0A), "LD A,(BC)", 8, 1, 0, [&](const u8* args)
		{
			_regs->a = _mem->read_byte(_regs->bc());
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x1A), "LD A,(DE)", 8, 1, 0, [&](const u8* args)
		{
			_regs->a = _mem->read_byte(_regs->de());
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x2A), "LD A,(HL+)", 8, 1, 0, [&](const u8* args)
		{
			u16 vhl = _regs->hl();
			_regs->a = _mem->read_byte(vhl);
			_regs->hl(vhl + 1);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x3A), "LD A,(HL-)", 8, 1, 0, [&](const u8* args)
		{
			u16 vhl = _regs->hl();
			_regs->a = _mem->read_byte(vhl);
			_regs->hl(vhl - 1);
			RET_NO_ARGS_REF;
		});
	}

	void vcpu_firmware::initmap_ld_r16_d16()
	{
		add_instruction(opcode(0x01), "LD BC,d16", 12, 3, 2, [&](const u8* args)
		{
			u16 val = read_word(&args[0]);
			_regs->bc(val);
		});

		add_instruction(opcode(0x11), "LD DE,d16", 12, 3, 2, [&](const u8* args)
		{
			u16 val = read_word(&args[0]);
			_regs->de(val);
		});

		add_instruction(opcode(0x21), "LD DE,d16", 12, 3, 2, [&](const u8* args)
		{
			u16 val = read_word(&args[0]);
			_regs->hl(val);
		});

		add_instruction(opcode(0x31), "LD DE,d16", 12, 3, 2, [&](const u8* args)
		{
			u16 val = read_word(&args[0]);
			_regs->sp = val;
		});
	}

	void vcpu_firmware::initmap_ld_misc()
	{
		add_instruction(opcode(0xE2), "LD (C),A", 8, 1, 0, [&](const u8* args)
		{
			_mem->write_byte((u16)(0xFF00 + _regs->c), _regs->a);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0xF2), "LD A,(C)", 8, 1, 0, [&](const u8* args)
		{
			_regs->a = _mem->read_byte(0xFF00 + _regs->c);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x08), "LD (d16),SP", 20, 3, 2, [&](const u8* args)
		{
			u16 addr = read_word(&args[0]);
			u16 val = _regs->sp;
			_mem->write_word(addr, val);
		});

		add_instruction(opcode(0xF8), "LD HL, SP + d8", 12, 2, 1, [&](const u8* args)
		{
			u8 d8 = *(&args[0]);
			u32 val = d8 + _regs->sp;
			_regs->hl((u16)val);

			_regs->reset_flags();

			if (val > BYTE_MAX)
			{
				_regs->set_flag(registers::flag::CARRY);
				_regs->set_flag(registers::flag::HALF_CARRY);
			}
			else if (val > HBYTE_MAX)
			{
				_regs->set_flag(registers::flag::HALF_CARRY);
			}
		});

		add_instruction(opcode(0xEA), "LD (a16), A", 16, 3, 2, [&](const u8* args)
		{
			u16 a16 = read_word(args);
			u8 val = _regs->a;
			_mem->write_byte(a16, val);
		});

		add_instruction(opcode(0xFA), "LD A, (a16)", 16, 3, 2, [&](const u8* args)
		{
			u16 a16 = read_word(args);
			u8 val = _mem->read_byte(a16);
			_regs->a = val;
		});

		add_instruction(opcode(0xF9), "LD SP,HL", 8, 1, 0, [&](const u8* args)
		{
			u16 hl = _regs->hl();
			_regs->sp = hl;
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0xE0), "LDH ($FF00+a8), A", 12, 2, 1, [&](const u8* args)
		{
			u8 a8 = *&args[0];
			u16 addr = 0xFF00 + a8;
			_mem->write_byte(addr, _regs->a);
		});

		add_instruction(opcode(0xF0), "LDH A, ($FF00+a8)", 12, 2, 1, [&](const u8* args)
		{
			u8 a8 = *&args[0];
			u16 addr = 0xFF00 + a8;
			u8 val = _mem->read_byte(addr);
			_regs->a = val;
		});
	}

	void vcpu_firmware::initmap_add_a_x8()
	{
		add_instruction(opcode(0x87), "ADD A,A", 4, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_add_a_v8(_regs->a);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x80), "ADD A,B", 4, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_add_a_v8(_regs->b);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x81), "ADD A,C", 4, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_add_a_v8(_regs->c);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x82), "ADD A,D", 4, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_add_a_v8(_regs->d);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x83), "ADD A,E", 4, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_add_a_v8(_regs->e);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x84), "ADD A,H", 4, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_add_a_v8(_regs->h);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x85), "ADD A,L", 4, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_add_a_v8(_regs->l);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x86), "ADD A,(HL)", 8, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_add_a_v8(_mem->read_byte(_regs->hl()));
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0xC6), "ADD A,d8", 8, 2, 1, [&](const u8* args)
		{
			u8 d8 = args[0];
			_instImpl->opcode_add_a_v8(d8);
			RET_NO_ARGS_REF;
		});
	}

	void vcpu_firmware::initmap_add_hl_r16()
	{
		add_instruction(opcode(0x09), "ADD HL,BC", 8, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_add_hl_v16(_regs->bc());
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x19), "ADD HL,DE", 8, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_add_hl_v16(_regs->de());
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x29), "ADD HL,HL", 8, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_add_hl_v16(_regs->hl());
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x39), "ADD HL,SP", 8, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_add_hl_v16(_regs->sp);
			RET_NO_ARGS_REF;
		});
	}

	void vcpu_firmware::initmap_sub_a_x8()
	{
		add_instruction(opcode(0x97), "SUB A,A", 4, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_sub_a_v8(_regs->a);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x90), "SUB A,B", 4, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_sub_a_v8(_regs->b);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x91), "SUB A,C", 4, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_sub_a_v8(_regs->c);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x92), "SUB A,D", 4, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_sub_a_v8(_regs->d);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x93), "SUB A,E", 4, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_sub_a_v8(_regs->e);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x94), "SUB A,H", 4, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_sub_a_v8(_regs->h);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x95), "SUB A,L", 4, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_sub_a_v8(_regs->l);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x96), "SUB A,(HL)", 8, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_sub_a_v8(_mem->read_byte(_regs->hl()));
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0xD6), "SUB A,d8", 8, 2, 1, [&](const u8* args)
		{
			u8 d8 = args[0];
			_instImpl->opcode_sub_a_v8(d8);
			RET_NO_ARGS_REF;
		});
	}

	void vcpu_firmware::initmap_adc_a_x8()
	{
		add_instruction(opcode(0x8F), "ADC A,A", 4, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_adc_a_v8(_regs->a);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x88), "ADC A,B", 4, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_adc_a_v8(_regs->b);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x89), "ADC A,C", 4, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_adc_a_v8(_regs->c);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x8A), "ADC A,D", 4, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_adc_a_v8(_regs->d);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x8B), "ADC A,E", 4, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_adc_a_v8(_regs->e);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x8C), "ADC A,H", 4, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_adc_a_v8(_regs->h);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x8D), "ADC A,L", 4, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_adc_a_v8(_regs->l);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x8E), "ADC A,(HL)", 8, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_adc_a_v8(_mem->read_byte(_regs->hl()));
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0xCE), "ADC A,d8", 8, 2, 1, [&](const u8* args)
		{
			u8 d8 = args[0];
			_instImpl->opcode_adc_a_v8(d8);
		});
	}

	void vcpu_firmware::initmap_sbc_a_x8()
	{
		add_instruction(opcode(0x9F), "SBC A,A", 4, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_sbc_a_v8(_regs->a);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x98), "SBC A,B", 4, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_sbc_a_v8(_regs->b);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x99), "SBC A,C", 4, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_sbc_a_v8(_regs->c);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x9A), "SBC A,D", 4, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_sbc_a_v8(_regs->d);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x9B), "SBC A,E", 4, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_sbc_a_v8(_regs->e);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x9C), "SBC A,H", 4, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_sbc_a_v8(_regs->h);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x9D), "SBC A,L", 4, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_sbc_a_v8(_regs->l);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x9E), "SBC A,(HL)", 8, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_sbc_a_v8(_mem->read_byte(_regs->hl()));
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0xDE), "SBC A,d8", 8, 2, 1, [&](const u8* args)
		{
			u8 d8 = args[0];
			_instImpl->opcode_sbc_a_v8(d8);
		});
	}

	void vcpu_firmware::initmap_and_a_x8()
	{
		add_instruction(opcode(0xA7), "AND A,A", 4, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_and_a_v8(_regs->a);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0xA0), "AND A,B", 4, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_and_a_v8(_regs->b);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0xA1), "AND A,C", 4, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_and_a_v8(_regs->c);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0xA2), "AND A,D", 4, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_and_a_v8(_regs->d);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0xA3), "AND A,E", 4, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_and_a_v8(_regs->e);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0xA4), "AND A,H", 4, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_and_a_v8(_regs->h);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0xA5), "AND A,L", 4, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_and_a_v8(_regs->l);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0xA6), "AND A,(HL)", 8, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_and_a_v8(_mem->read_byte(_regs->hl()));
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0xE6), "AND A,d8", 8, 2, 1, [&](const u8* args)
		{
			u8 d8 = args[0];
			_instImpl->opcode_and_a_v8(d8);
		});
	}

	void vcpu_firmware::initmap_or_a_x8()
	{
		add_instruction(opcode(0xB7), "OR A,A", 4, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_or_a_v8(_regs->a);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0xB0), "OR A,B", 4, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_or_a_v8(_regs->b);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0xB1), "OR A,C", 4, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_or_a_v8(_regs->c);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0xB2), "OR A,D", 4, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_or_a_v8(_regs->d);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0xB3), "OR A,E", 4, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_or_a_v8(_regs->e);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0xB4), "OR A,H", 4, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_or_a_v8(_regs->h);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0xB5), "OR A,L", 4, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_or_a_v8(_regs->l);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0xB6), "OR A,(HL)", 8, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_or_a_v8(_mem->read_byte(_regs->hl()));
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0xF6), "OR A,d8", 8, 2, 1, [&](const u8* args)
		{
			u8 d8 = args[0];
			_instImpl->opcode_or_a_v8(d8);
		});
	}

	void vcpu_firmware::initmap_xor_a_x8()
	{
		add_instruction(opcode(0xAF), "XOR A,A", 4, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_xor_a_v8(_regs->a);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0xA8), "XOR A,B", 4, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_xor_a_v8(_regs->b);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0xA9), "XOR A,C", 4, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_xor_a_v8(_regs->c);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0xAA), "XOR A,D", 4, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_xor_a_v8(_regs->d);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0xAB), "XOR A,E", 4, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_xor_a_v8(_regs->e);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0xAC), "XOR A,H", 4, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_xor_a_v8(_regs->h);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0xAD), "XOR A,L", 4, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_xor_a_v8(_regs->l);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0xAE), "XOR A,(HL)", 8, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_xor_a_v8(_mem->read_byte(_regs->hl()));
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0xEE), "XOR A,d8", 8, 2, 1, [&](const u8* args)
		{
			u8 d8 = args[0];
			_instImpl->opcode_xor_a_v8(d8);
		});
	}

	void vcpu_firmware::initmap_inc_r8()
	{
		add_instruction(opcode(0x3C), "INC A", 4, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_inc_r8(_regs->a);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x04), "INC B", 4, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_inc_r8(_regs->b);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x0C), "INC C", 4, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_inc_r8(_regs->c);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x14), "INC D", 4, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_inc_r8(_regs->d);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x1C), "INC E", 4, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_inc_r8(_regs->e);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x24), "INC H", 4, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_inc_r8(_regs->h);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x2C), "INC L", 4, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_inc_r8(_regs->e);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x34), "INC (HL)", 12, 1, 0, [&](const u8* args)
		{
			u16 addr = _regs->hl();
			u8 val = _mem->read_byte(addr);
			_instImpl->opcode_inc_r8(val);
			_mem->write_byte(addr, val);
			RET_NO_ARGS_REF;
		});
	}

	void vcpu_firmware::initmap_inc_r16()
	{
		add_instruction(opcode(0x03), "INC BC", 8, 1, 0, [&](const u8* args)
		{
			u16 val = (u16)(_regs->bc() + 1);
			_regs->bc(val);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x13), "INC DE", 8, 1, 0, [&](const u8* args)
		{
			u16 val = (u16)(_regs->de() + 1);
			_regs->de(val);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x23), "INC HL", 8, 1, 0, [&](const u8* args)
		{
			u16 val = (u16)(_regs->hl() + 1);
			_regs->hl(val);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x33), "INC SP", 8, 1, 0, [&](const u8* args)
		{
			_regs->sp += 1;
			RET_NO_ARGS_REF;
		});
	}

	void vcpu_firmware::initmap_dec_r8()
	{
		add_instruction(opcode(0x3D), "DEC A", 4, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_dec_r8(_regs->a);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x05), "DEC B", 4, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_dec_r8(_regs->b);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x0D), "DEC C", 4, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_dec_r8(_regs->c);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x15), "DEC D", 4, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_dec_r8(_regs->d);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x1D), "DEC E", 4, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_dec_r8(_regs->e);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x25), "DEC H", 4, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_dec_r8(_regs->h);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x2D), "DEC L", 4, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_dec_r8(_regs->e);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x35), "DEC (HL)", 12, 1, 0, [&](const u8* args)
		{
			u16 addr = _regs->hl();
			u8 val = _mem->read_byte(addr);
			_instImpl->opcode_dec_r8(val);
			_mem->write_byte(addr, val);
			RET_NO_ARGS_REF;
		});
	}

	void vcpu_firmware::initmap_dec_r16()
	{
		add_instruction(opcode(0x0B), "DEC BC", 8, 1, 0, [&](const u8* args)
		{
			u16 val = (u16)(_regs->bc() - 1);
			_regs->bc(val);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x1B), "DEC DE", 8, 1, 0, [&](const u8* args)
		{
			u16 val = (u16)(_regs->de() - 1);
			_regs->de(val);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x2B), "DEC HL", 8, 1, 0, [&](const u8* args)
		{
			u16 val = (u16)(_regs->hl() - 1);
			_regs->hl(val);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x3B), "DEC SP", 8, 1, 0, [&](const u8* args)
		{
			_regs->sp -= 1;
			RET_NO_ARGS_REF;
		});
	}

	void vcpu_firmware::initmap_cp_r8()
	{
		add_instruction(opcode(0xBF), "CP A", 4, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_cp_r8(_regs->a);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0xB8), "CP B", 4, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_cp_r8(_regs->b);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0xB9), "CP C", 4, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_cp_r8(_regs->c);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0xBA), "CP D", 4, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_cp_r8(_regs->d);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0xBB), "CP E", 4, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_cp_r8(_regs->e);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0xBC), "CP H", 4, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_cp_r8(_regs->h);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0xBD), "CP L", 4, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_cp_r8(_regs->l);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0xBE), "CP (HL)", 8, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_cp_r8(_regs->l);
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0xFE), "CP d8", 8, 2, 1, [&](const u8* args)
		{
			u8 d8 = args[0];
			_instImpl->opcode_cp_r8(d8);
		});
	}

	void vcpu_firmware::initmap_bitrotations()
	{
		add_instruction(opcode(0x0F), "RRCA", 4, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_rrca();
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x1F), "RRA", 4, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_rra();
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x07), "RLCA", 4, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_rlca();
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0x17), "RLA", 4, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_rla();
			RET_NO_ARGS_REF;
		});
	}

	void vcpu_firmware::initmap_rst()
	{
		add_instruction(opcode(0xC7), "RST 00H", 16, 1, 0, [&](const u8* args)
		{
			_regs->pc = 0x0000;
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0xCF), "RST 08H", 16, 1, 0, [&](const u8* args)
		{
			_regs->pc = 0x0008;
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0xD7), "RST 10H", 16, 1, 0, [&](const u8* args)
		{
			_regs->pc = 0x0010;
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0xDF), "RST 18H", 16, 1, 0, [&](const u8* args)
		{
			_regs->pc = 0x0018;
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0xE7), "RST 20H", 16, 1, 0, [&](const u8* args)
		{
			_regs->pc = 0x0020;
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0xEF), "RST 28H", 16, 1, 0, [&](const u8* args)
		{
			_regs->pc = 0x0028;
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0xF7), "RST 30H", 16, 1, 0, [&](const u8* args)
		{
			_regs->pc = 0x0030;
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0xFF), "RST 38H", 16, 1, 0, [&](const u8* args)
		{
			_regs->pc = 0x0038;
			RET_NO_ARGS_REF;
		});
	}

	void vcpu_firmware::initmap_jumps()
	{
		add_instruction(opcode(0x18), "JR i8", 12, 0, 1, [&](const u8* args)
		{
			int8_t i8 = static_cast<int8_t>(args[0]);
			_regs->pc += i8;
		});

		add_instruction(opcode(0x28), "JR Z,i8", 8, 0, 1, [&](const u8* args)
		{
			if(_regs->read_flag(registers::flag::ZERO))
			{
				delay_cycles(4); //16
				int8_t i8 = static_cast<int8_t>(args[0]);
				_regs->pc += i8;
			}
		});

		add_instruction(opcode(0x38), "JR C,i8", 8, 0, 1, [&](const u8* args)
		{
			if(_regs->read_flag(registers::flag::CARRY))
			{
				delay_cycles(4); //16
				int8_t i8 = static_cast<int8_t>(args[0]);
				_regs->pc += i8;
			}
		});

		add_instruction(opcode(0xC3), "JP a16", 16, 0, 2, [&](const u8* args)
		{
			u16 a16 = read_word(args);
			_regs->pc = a16;
		});

		add_instruction(opcode(0xC2), "JP NZ,a16", 12, 0, 2, [&](const u8* args)
		{
			if(!_regs->read_flag(registers::flag::ZERO))
			{
				delay_cycles(4); 
				u16 a16 = read_word(args);
				_regs->pc = a16;
			}
		});

		add_instruction(opcode(0xD2), "JP NC,a16", 12, 0, 2, [&](const u8* args)
		{
			if(!_regs->read_flag(registers::flag::CARRY))
			{
				delay_cycles(4); 
				u16 a16 = read_word(args);
				_regs->pc = a16;
			}
		});

		add_instruction(opcode(0xCA), "JP Z,a16", 12, 0, 2, [&](const u8* args)
		{
			if(_regs->read_flag(registers::flag::ZERO))
			{
				delay_cycles(4); 
				u16 a16 = read_word(args);
				_regs->pc = a16;
			}
		});
		 
		add_instruction(opcode(0xDA), "JP C,a16", 12, 0, 2, [&](const u8* args)
		{
			if(_regs->read_flag(registers::flag::CARRY))
			{
				delay_cycles(4);
				u16 a16 = read_word(args);
				_regs->pc = a16;
			}
		});

		add_instruction(opcode(0xE9), "JP (HL)", 4, 0, 0, [&](const u8* args)
		{
			u16 phl = _mem->read_word(_regs->hl());
			_regs->pc = phl;
            RET_NO_ARGS_REF;
		});
	}

	void vcpu_firmware::initmap_push()
	{
		add_instruction(opcode(0xF5), "PUSH AF", 16, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_push_r16(_regs->af());
            RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0xC5), "PUSH BC", 16, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_push_r16(_regs->bc());
            RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0xD5), "PUSH DE", 16, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_push_r16(_regs->de());
            RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0xE5), "PUSH HL", 16, 1, 0, [&](const u8* args)
		{
			_instImpl->opcode_push_r16(_regs->hl());
            RET_NO_ARGS_REF;
		});
	}

	void vcpu_firmware::initmap_pop()
	{
		add_instruction(opcode(0xF1), "POP AF", 12, 1, 0, [&](const u8* args)
		{
			u16 val = _mem->read_word(_regs->sp);
			_regs->af(val);
			_regs->sp += 2;
            RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0xC1), "POP BC", 12, 1, 0, [&](const u8* args)
		{
			u16 val = _mem->read_word(_regs->sp);
			_regs->bc(val);
			_regs->sp += 2;
            RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0xD1), "POP DE", 12, 1, 0, [&](const u8* args)
		{
			u16 val = _mem->read_word(_regs->sp);
			_regs->de(val);
			_regs->sp += 2;
            RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0xE1), "POP HL", 12, 1, 0, [&](const u8* args)
		{
			u16 val = _mem->read_word(_regs->sp);
			_regs->hl(val);
			_regs->sp += 2;
            RET_NO_ARGS_REF;
		});
	}

	void vcpu_firmware::initmap_call()
	{
		add_instruction(opcode(0xCD), "CALL a16", 24, 0, 2, [&](const u8* args)
		{
			_instImpl->opcode_call_a16(args);
		});

		add_instruction(opcode(0xCC), "CALL Z,a16", 12, 0, 2, [&](const u8* args)
		{
			if(_regs->read_flag(registers::flag::ZERO))
			{
				delay_cycles(12);
				_instImpl->opcode_call_a16(args);
			}
		});

		add_instruction(opcode(0xDC), "CALL C,a16", 12, 0, 2, [&](const u8* args)
		{
			if(_regs->read_flag(registers::flag::CARRY))
			{
				delay_cycles(12);
				_instImpl->opcode_call_a16(args);
			}
		});

		add_instruction(opcode(0xD4), "CALL NC,a16", 12, 0, 2, [&](const u8* args)
		{
			if(!_regs->read_flag(registers::flag::CARRY))
			{
				delay_cycles(12);
				_instImpl->opcode_call_a16(args);
			}
		});

		add_instruction(opcode(0xC4), "CALL NZ,a16", 12, 0, 2, [&](const u8* args)
		{
			if(!_regs->read_flag(registers::flag::ZERO))
			{
				delay_cycles(12);
				_instImpl->opcode_call_a16(args);
			}
		});
	}

	void vcpu_firmware::initmap_ret()
	{
		add_instruction(opcode(0xC9), "RET", 16, 0, 0, [&](const u8* args)
		{
			_instImpl->opcode_ret();
			RET_NO_ARGS_REF;
		});

		add_instruction(opcode(0xC8), "RET Z", 8, 0, 0, [&](const u8* args)
		{
			if(_regs->read_flag(registers::flag::ZERO))
			{
				delay_cycles(12);
				_instImpl->opcode_ret();
				RET_NO_ARGS_REF;
			}
		});

		add_instruction(opcode(0xD8), "RET C", 8, 0, 0, [&](const u8* args)
		{
			if(_regs->read_flag(registers::flag::CARRY))
			{
				delay_cycles(12);
				_instImpl->opcode_ret();
				RET_NO_ARGS_REF;
			}
		});

		add_instruction(opcode(0xC0), "RET NZ", 8, 0, 0, [&](const u8* args)
		{
			if(!_regs->read_flag(registers::flag::ZERO))
			{
				delay_cycles(12);
				_instImpl->opcode_ret();
				RET_NO_ARGS_REF;
			}
		});

		add_instruction(opcode(0xD0), "RET NC", 8, 0, 0, [&](const u8* args)
		{
			if(!_regs->read_flag(registers::flag::CARRY))
			{
				delay_cycles(12);
				_instImpl->opcode_ret();
				RET_NO_ARGS_REF;
			}
		});
	}

	void vcpu_firmware::add_instruction(
		opcode opc, 
		const std::string& mnem, 
		u8 cycc, 
		u8 pc_offset, 
		u8 arg_count,
		const vcpu_instruction::op_call_t& call)
	{
		vcpu_instruction inst(opc, mnem, cycc, pc_offset, arg_count, call);
		inst_map.emplace(opc, std::move(inst));
	}
}