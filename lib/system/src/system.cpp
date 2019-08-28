#include <sleepy/system.hpp>

namespace sleepy
{
    system::system()
    {
        _memory = std::make_unique<memory>();
        _cpu = std::make_unique<vcpu>(_memory.get());
    }
}