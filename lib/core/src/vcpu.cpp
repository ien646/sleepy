#include <sleepy/vcpu.hpp>

namespace sleepy
{
    vcpu::vcpu()
        : _vfw(vcpu_firmware(&_mem, &_regs))
    { }

    void vcpu::exec_op(opcode op, byte_t* args)
    {
        _vfw.inst_map[op].call(args);
    }

    const vcpu::memory& memory() const noexcept
    {
        return _mem;
    }

    const vcpu::registers& registers() const noexcept
    {
        return _regs
    }
}