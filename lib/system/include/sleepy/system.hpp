#include <sleepy/common.hpp>

#include <sleepy/memory.hpp>
#include <sleepy/vcpu.hpp>

namespace sleepy
{
    class system
    {
    private:
        std::unique_ptr<vcpu> _cpu;
        std::unique_ptr<memory> _memory;

        u64 _elapsed_cycles;

    public:
        system();

        void set_preexec_debug_callback(debug_callback_t);
        void set_postexec_debug_callback(debug_callback_t);

        void interrupt_procedure();

        void start();

    private:
        void init_state();
    };
}