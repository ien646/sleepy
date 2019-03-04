#pragma once

#include <sleepy/common.hpp>
#include <sleepy/memory.hpp>
#include <sleepy/registers.hpp>
#include <sleepy/vcpu_firmware.hpp>
#include <istream>
#include <functional>

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

        typedef std::function<void(vcpu&, const vcpu_instruction*)> debug_func_t;
        debug_func_t _pre_exec_debug_fun;
        debug_func_t _post_exec_debug_fun;
        bool _debug_enabled = false;
    public:
        vcpu();

        void start();
        void setup_memory(std::istream& data);

        void setup_debug(debug_func_t pre_exec, debug_func_t post_exec);
        void enable_debug(bool enabled);

        const vcpu_instruction& get_inst_data(opcode op);

        const memory& memory() const noexcept;
        const registers& registers() const noexcept;

        const vcpu_instruction* last_executed_instruction() const noexcept;

    private:
        void exec_op(opcode op, u8* args);
    };
}