#pragma once 

#include <sleepy/common.hpp>
#include <sleepy/vcpu.hpp>
#include <sleepy/memory.hpp>

namespace sleepy
{
    class system
    {
    private:
        memory _memory;
        vcpu _vcpu;

        static const uint64_t CYCLES_PER_SECOND = 4194300;
        static const uint64_t CYCLES_PER_VBLANK = 69905;
        static const uint64_t NANOS_PER_VBLANK = 16666667;        
        
    public:
        system() 
            : _vcpu(&_memory) 
        { }

        void load_cartridge(std::istream&);
        void start();
        double elapsed_seconds() const noexcept;
    };
}