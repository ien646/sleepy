#include <sleepy/system.hpp>

namespace sleepy
{
    system::system()
    {
        _memory = std::make_unique<memory>();
        _cpu = std::make_unique<vcpu>(_memory.get());
    }

    void system::init_state()
    {
        _memory->init_state();
        _cpu->init_state();
    }

    void system::set_preexec_debug_callback(debug_callback_t cback)
    {
        _cpu->setup_debug_pre(cback);
    }
    
    void system::set_postexec_debug_callback(debug_callback_t cback)
    {
        _cpu->setup_debug_post(cback);
    }

    void system::start()
    {
        while(true)
        {
            /* ... */
        }
    }
}