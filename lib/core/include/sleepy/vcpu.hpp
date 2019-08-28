#pragma once

#include <sleepy/common.hpp>
#include <sleepy/registers.hpp>
#include <sleepy/vcpu_impl.hpp>
#include <sleepy/special_registers.hpp>
#include <istream>
#include <functional>

namespace sleepy
{
    typedef std::function<void(const vcpu*, const vcpu_instruction*)> debug_callback_t;
    class vcpu
    {
    private:
        registers _regs;
        vcpu_impl _vfw;
        memory* _mem;

        bool _memory_set = false;
        const vcpu_instruction* _last_executed_inst = nullptr;
        
        debug_callback_t _pre_exec_debug_cbk;
        debug_callback_t _post_exec_debug_cbk;
        bool _debug_enabled = false;

        uint64_t _ticks_elapsed = 0u;
    public:
        vcpu() = delete;
        vcpu(const vcpu& cp_src) = delete;
        vcpu(vcpu&& mv_src) = delete;

        vcpu(memory* mem);

        void exec_next_tick();
        void setup_memory(std::istream& data);

        void setup_debug_pre(debug_callback_t);
        void setup_debug_post(debug_callback_t);

        void enable_debug(bool enabled);

        const vcpu_instruction& get_inst_data(opcode op) const;

        const memory* memory() const noexcept;
        const registers& registers() const noexcept;

        const vcpu_instruction* last_executed_instruction() const noexcept;

        void delay_cycles(size_t count) noexcept;
        uint64_t elapsed_cycles() const noexcept;

        void write_interrupt_master_enable(bool enabled);
        bool read_interrupt_master_enable();

        const vcpu_impl* get_vcpu_impl() const;

        void write_if_flag(interrupt_flags flag);
        bool read_if_flag(interrupt_flags flag);

        void write_ie_flag(interrupt_flags flag);
        bool read_ie_flag(interrupt_flags flag);

        void init_state();

    private:
        void exec_op(opcode op, const u8* args);
    };
}