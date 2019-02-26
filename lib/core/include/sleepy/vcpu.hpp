#pragma once

#include <sleepy/common.hpp>
#include <sleepy/memory.hpp>
#include <sleepy/registers.hpp>
#include <sleepy/vcpu_firmware.hpp>

namespace sleepy
{
    class vcpu
    {
    private:
        memory _mem;
        registers _regs;
        vcpu_firmware _vfw;

    public:
        vcpu();

        void exec_op(opcode op, byte_t* args);
        const memory& memory() const noexcept;
        const registers& registers() const noexcept;
    };
}