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
        typedef std::function<void(const u8*)> op_call_t;

        // Cpu instruction memory-ordered opcode
        opcode op = opcode(0xFF, 0x00);

        // Instruction textual representation
        std::string mnemonic = "uninitialized_mnemonic";

        // Execution time in cycles
        u8 cycles = 0xFF;

        // Offset applied to PC after execution
        u8 pc_offset = 0;

        // Argument count
        u8 arg_count = 0;

        // Instruction call
        op_call_t call = nullptr;

        vcpu_instruction() noexcept {};

        vcpu_instruction(
            opcode opc, 
            const std::string& mnem,
            u8 cc, 
            u8 pc_off,
            u8 argc,
            op_call_t ocall)
                : op(opc)
                , mnemonic(mnem)
                , cycles(cc)
                , pc_offset(pc_off)
                , arg_count(argc)
                , call(ocall)
        { }

        vcpu_instruction(const vcpu_instruction& copy_src) = delete;
        vcpu_instruction(vcpu_instruction&& move_src) = default;

        void operator=(const vcpu_instruction& copy_src) = delete;

        void operator=(vcpu_instruction&& move_src) noexcept
        {
            op = move_src.op;
            mnemonic = std::move(move_src.mnemonic);
            cycles = move_src.cycles;
            pc_offset = move_src.pc_offset;
            arg_count = move_src.arg_count;
            call = std::move(move_src.call);
        }
    };
}