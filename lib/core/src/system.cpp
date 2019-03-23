#include <sleepy/system.hpp>

#include <iostream>
#include <chrono>

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
            std::cout << "[ESEC: " << elapsed_seconds() << "] VBLANK" << std::endl;

            auto spin_time = std::chrono::duration_cast<std::chrono::nanoseconds>(post_tick_time - pre_tick_time);
            
            // SPINWAIT FOR VBLANK
            while(spin_time.count() < NANOS_PER_VBLANK) 
            {
                post_tick_time = clock::now();
                spin_time = std::chrono::duration_cast<std::chrono::nanoseconds>(post_tick_time - pre_tick_time);
            }

            /*--------------------*/
            // VBLANK TRIGGER
            /*--------------------*/
        }
    }

    double system::elapsed_seconds() const noexcept
    {
        double cc = static_cast<double>(_vcpu.elapsed_cycles());
        return cc / static_cast<double>(CYCLES_PER_SECOND);
    }
}