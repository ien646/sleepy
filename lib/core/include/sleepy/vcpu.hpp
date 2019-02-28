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
        const vcpu_instruction* _last_executed_inst = nullptr;

    public:
        vcpu();

        void start();
        void setup_memory(std::istream& data);

        const vcpu_instruction& get_inst_data(opcode op);

        const memory& memory() const noexcept;
        const registers& registers() const noexcept;

        const vcpu_instruction* last_executed_instruction() const noexcept;

    private:
        void exec_op(opcode op, byte_t* args);
    };
}