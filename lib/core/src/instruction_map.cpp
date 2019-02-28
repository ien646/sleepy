#include <sleepy/instruction_map.hpp>

namespace sleepy
{
    void instruction_map::emplace(opcode opc, vcpu_instruction&& inst)
    {
        if(opc.is_extended())
        {
            _ext_iset[opc.value] = std::move(inst);
        }
        else
        {
            _std_iset[opc.value] = std::move(inst);
        }
    }

    const vcpu_instruction& instruction_map::operator[](opcode opc)
    {
        if(opc.is_extended())
        {
            return _ext_iset[opc.value];
        }
        else
        {
            return _std_iset[opc.value];
        }
    }
}