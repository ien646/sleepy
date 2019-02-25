#pragma once

#include <sleepy/common.hpp>
#include <sleepy/opcode.hpp>

#include <string>
#include <functional>

namespace sleepy
{
    class vcpu_instruction
    {
    public:
        typedef std::function<void(const byte_t*)> op_call_t;

        // Cpu instruction memory-ordered opcode
        opcode op = opcode(0xFF, 0x00);

        // Instruction textual representation
        std::string mnemonic = "uninitialized_mnemonic";

        // Execution time in cycles
        byte_t cycles = 0xFF;

        // Arguments length in bytes
        byte_t arg_count = 0;

        // Instruction call
        op_call_t call = nullptr;

        vcpu_instruction() noexcept {};

        vcpu_instruction(opcode opc, const std::string& mnem, byte_t cc, byte_t argc, op_call_t ocall)
            : op(opc)
            , mnemonic(mnem)
            , cycles(cc)
            , arg_count(argc)
            , call(ocall)
        { }

        vcpu_instruction(const vcpu_instruction& copy_src) = delete;

        vcpu_instruction(vcpu_instruction&& move_src) = default;
    };
}