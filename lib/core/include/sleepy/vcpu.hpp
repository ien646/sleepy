#pragma once

#include <sleepy/common.hpp>
#include <sleepy/registers.hpp>
#include <sleepy/vcpu_impl.hpp>
#include <sleepy/special_registers.hpp>
#include <istream>
#include <functional>

namespace sleepy
{
    class vcpu
    {
    private:
        registers _regs;
        vcpu_impl _vfw;
        memory* _mem;

        bool _memory_set = false;
        const vcpu_instruction* _last_executed_inst = nullptr;

        typedef std::function<void(const vcpu*, const vcpu_instruction*)> debug_func_t;
        debug_func_t _pre_exec_debug_fun;
        debug_func_t _post_exec_debug_fun;
        bool _debug_enabled = false;

        uint64_t _ticks_elapsed = 0u;
    public:
        vcpu() = delete;
        vcpu(const vcpu& cp_src) = delete;
        vcpu(vcpu&& mv_src) = delete;

        vcpu(memory* mem);

        void exec_next_tick();
        void setup_memory(std::istream& data);

        void setup_debug(debug_func_t pre_exec, debug_func_t post_exec);
        void enable_debug(bool enabled);

        const vcpu_instruction& get_inst_data(opcode op) const;

        const memory* memory() const noexcept;
        const registers& registers() const noexcept;

        const vcpu_instruction* last_executed_instruction() const noexcept;

        void delay_cycles(size_t count) noexcept;
        uint64_t elapsed_cycles() const noexcept;

        void write_interrupt_master_enable(bool enabled);
        bool read_interrupt_master_enable();

        vcpu_impl* get_vcpu_impl();

        void write_if_flag(interrupt_flags flag);
        bool read_if_flag(interrupt_flags flag);

        void write_ie_flag(interrupt_flags flag);
        bool read_ie_flag(interrupt_flags flag);

    private:
        void exec_op(opcode op, u8* args);
        void init_state();
    };
}