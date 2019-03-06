#include <sleepy/vcpu.hpp>

#include <iostream>
#include <iterator>

namespace sleepy
{
    vcpu::vcpu()
        : _vfw(vcpu_impl(&_mem, &_regs))
    { }

    void vcpu::exec_op(opcode op, u8* args)
    {
        auto& inst = _vfw.inst_map[op];

        if(inst.cycles == 0xFF) 
        {
            throw std::logic_error("Unimplemented opcode (dec): " + inst.op.value);
        }

        _pre_exec_debug_fun(*this, &inst);
        inst.call(args);
        _post_exec_debug_fun(*this, &inst);
        
        _last_executed_inst = &inst;
        _regs.pc += inst.pc_offset;
    }

    const memory& vcpu::memory() const noexcept
    {
        return _mem;
    }

    const registers& vcpu::registers() const noexcept
    {
        return _regs;
    }

    const vcpu_instruction& vcpu::get_inst_data(opcode op)
    {
        return _vfw.inst_map[op];
    }

    void vcpu::start()
    {
        if(!_memory_set)
        { 
            throw std::logic_error("Unable to start vcpu without setting memory data!");
        }
        _regs.zero_registers(true);
        _regs.pc = 0x0100;
        _regs.sp = 0xFFFE;
        while(true)
        {
            u8 op = _mem.read_byte(_regs.pc);
            if(op == 0x00) { _regs.pc++; continue;}
            if(op == 0xCBu)
            {
                ++(_regs.pc);
                u8 opv = _mem.read_byte(_regs.pc);
                opcode opc(op, opv);
                u8* args = &_mem.data()[_regs.pc + 1];
                exec_op(opc, args);
            }
            else
            {
                opcode opc(op);
                u8* args = &_mem.data()[_regs.pc + 1];
                exec_op(opc, args);
            }
        }
    }

    void vcpu::setup_memory(std::istream& data)
    {
        std::istreambuf_iterator<char> beg(data);
        std::istreambuf_iterator<char> end;

        std::vector<u8> cdata(beg, end);

        std::copy(cdata.begin(), cdata.end(), _mem.data() + 0x0100);
        _memory_set = true;
    }

    void vcpu::setup_debug(debug_func_t pre_exec, debug_func_t post_exec)
    {
        _pre_exec_debug_fun = pre_exec;
        _post_exec_debug_fun = post_exec;
        _debug_enabled = true;
    }

    void vcpu::enable_debug(bool enabled)
    {
        _debug_enabled = enabled;
    }

    const vcpu_instruction* vcpu::last_executed_instruction() const noexcept
    {
        return _last_executed_inst;
    }
}