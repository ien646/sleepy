#include <sleepy/system.hpp>

#include <iostream>

namespace sleepy
{
    void system::load_cartridge(std::istream& data)
    {
        _memory.load_data(data);
    }

    void system::start()
    {
        while (true)
        {
            uint64_t next_vblank_cycles = 
                _vcpu.elapsed_cycles() + CYCLES_PER_VBLANK;
            while(_vcpu.elapsed_cycles() <= next_vblank_cycles)
            {
                _vcpu.exec_next_tick();
            }
            std::cout << "[ESEC: ]" << elapsed_seconds() << "VBLANK" << std::endl;
            // VBLANK TRIGGER
        }
    }

    double system::elapsed_seconds() const noexcept
    {
        double cc = static_cast<double>(_vcpu.elapsed_cycles());
        return cc / static_cast<double>(CYCLES_PER_SECOND);
    }
}