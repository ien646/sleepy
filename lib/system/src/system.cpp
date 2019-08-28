#include <sleepy/system.hpp>
#include <sleepy/constants.hpp>

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
            // -- loop until vblank 
                // Execute instructions until LCD line change
                // Each instruction updates TMA register if TAC register is enabled (check docs)
                // Update special registers
                // Check for interrupts (input, LCDC, etc.)
            // --

            // Set IF(interrupt-flag)
            // -- if(Check IME and IE flags)
                // Reset IF register (allow nesting)
                // Reset IME
                // Push PC to stack
                // Jump to interrupt address
                // Run Vblank interrupt procedure (check flag)                
            // --
        }
    }

    void system::interrupt_procedure()
    {
        
    }
}