#include <sleepy/opcode.hpp>

namespace sleepy
{
    opcode::opcode(u8 val)
    {
        prefix = 0x00u;
        value = val;
    }

    opcode::opcode(u8 prefix, u8 val)
    {
        this->prefix = prefix;
        value = val;
    }

    u16 opcode::get()
    {
        return (prefix << 8) | (value);
    }

    bool opcode::operator==(const opcode& o) const
    {
        return compose_word(o.prefix, o.value) == compose_word(prefix, value);
    }

    bool opcode::operator<(const opcode& o) const
    {
        return compose_word(o.prefix, o.value) < compose_word(prefix, value);
    }

    bool opcode::operator>(const opcode& o) const
    {
        return compose_word(o.prefix, o.value) > compose_word(prefix, value);
    }
}