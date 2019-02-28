#include <sleepy/vcpu.hpp>

#include <iostream>

namespace sleepy
{
    vcpu::vcpu()
        : _vfw(vcpu_firmware(&_mem, &_regs))
    { }

    void vcpu::exec_op(opcode op, byte_t* args)
    {
        auto& inst = _vfw.inst_map[op];
        inst.call(args);
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
        while(true)
        {
            byte_t op = _mem.read_byte(_regs.pc);
            if(op == 0xCBu)
            {
                byte_t op2 = _mem.read_byte(_regs.pc + 1);
                byte_t* args = &_mem.data()[_regs.pc + 1];
                opcode opc(op, op2);
                exec_op(opc, args);
                _regs.pc += 2;
            }
            else
            {
                opcode opc(op);
                byte_t* args = &_mem.data()[_regs.pc];
                exec_op(opc, args);
                ++_regs.pc;
            }
        }
    }

    void vcpu::setup_memory(std::istream& data)
    {
        std::istream_iterator<sleepy::byte_t> beg(data);
        std::istream_iterator<sleepy::byte_t> end;

        std::vector<byte_t> cdata(beg, end);

        std::copy(cdata.begin(), cdata.begin() + 0xFFFF, _mem.data());
        _memory_set = true;
    }
}