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
}