#pragma once

#include <sleepy/vcpu_instruction.hpp>
#include <array>

namespace sleepy
{
    class instruction_map
    {
    private:
        constexpr static size_t DEFAULT_ISET_SZ = (0x00FFu + 1);

        // Default instruction set
        std::array<vcpu_instruction, DEFAULT_ISET_SZ> _std_iset;

        // Extended (prefix CB) instruction set
        std::array<vcpu_instruction, DEFAULT_ISET_SZ> _ext_iset;

    public:
        instruction_map() = default;
        instruction_map(const instruction_map& copy_src) = delete;
        instruction_map(instruction_map&& move_src) = delete;

        void emplace(opcode, vcpu_instruction&&);
        const vcpu_instruction& operator[](opcode) const;
    };
}
