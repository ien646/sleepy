#include <sleepy/system.hpp>

#include <chrono>
#include <sleepy/interrupt_addr.hpp>

namespace sleepy
{
    void system::load_cartridge(std::istream& data)
    {
        _memory.load_data(data);
    }

    void system::start()
    {
        using clock = std::chrono::high_resolution_clock;
        while (true)
        {            
            auto pre_tick_time = clock::now();
            uint64_t next_vblank_cycles = 
                _vcpu.elapsed_cycles() + CYCLES_PER_VBLANK;
            while(_vcpu.elapsed_cycles() <= next_vblank_cycles)
            {
                _vcpu.exec_next_tick();
            }
            auto post_tick_time = clock::now();

            auto spin_time = std::chrono::duration_cast<std::chrono::nanoseconds>(post_tick_time - pre_tick_time);
            
            // SPINWAIT FOR VBLANK
            while(spin_time.count() < NANOS_PER_VBLANK) 
            {
                post_tick_time = clock::now();
                spin_time = std::chrono::duration_cast<std::chrono::nanoseconds>(post_tick_time - pre_tick_time);
            }

            /*--------------------*/
            // VBLANK TRIGGER
            _vcpu.write_if_flag(interrupt_flags::VBLANK);
            if(_vcpu.read_interrupt_master_enable() && _vcpu.read_ie_flag(interrupt_flags::VBLANK))
            {
                _vcpu.write_interrupt_master_enable(false);
                const u16 addr = U16(interrupt_addr::VBLANK);
                const u8* args = reinterpret_cast<const u8*>(&addr);
                _vcpu.get_vcpu_impl()->inst_map[opcode(0xCD)].call(args);
            }           
            /*--------------------*/
        }
    }

    double system::elapsed_seconds() const noexcept
    {
        double cc = static_cast<double>(_vcpu.elapsed_cycles());
        return cc / static_cast<double>(CYCLES_PER_SECOND);
    }

    void system::setup_debug(debug_func_t pre_fun, debug_func_t post_fun)
    {
        _vcpu.setup_debug(pre_fun, post_fun);
    }
}