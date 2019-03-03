#include <sleepy/opcode.hpp>

namespace sleepy
{
    opcode::opcode(byte_t val)
    {
        prefix = 0x00u;
        value = val;
    }

    opcode::opcode(byte_t prefix, byte_t val)
    {
        prefix = prefix;
        value = val;
    }

    word_t opcode::get()
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