#include <sleepy/vcpu.hpp>
#include <sleepy/memory.hpp>

namespace sleepy
{
    class system
    {
    private:
        std::unique_ptr<vcpu> _cpu;
        std::unique_ptr<memory> _memory;

    public:
        system();

        void set_preexec_debug_callback(debug_callback_t);
        void set_postexec_debug_callback(debug_callback_t);

        void start();

    private:
        void init_state();
    };
}