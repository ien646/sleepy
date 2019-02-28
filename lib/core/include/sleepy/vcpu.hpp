#pragma once

#include <sleepy/common.hpp>
#include <sleepy/memory.hpp>
#include <sleepy/registers.hpp>
#include <sleepy/vcpu_firmware.hpp>
#include <istream>

namespace sleepy
{
    class vcpu
    {
    private:
        memory _mem;
        registers _regs;
        vcpu_firmware _vfw;
        bool _memory_set = false;

    public:
        vcpu();

        void start();
        void setup_memory(std::istream& data);

        const vcpu_instruction& get_inst_data(opcode op);
        
        void exec_op(opcode op, byte_t* args);

        const memory& memory() const noexcept;
        const registers& registers() const noexcept;
    };
}