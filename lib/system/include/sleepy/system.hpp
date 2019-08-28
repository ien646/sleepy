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
    };
}