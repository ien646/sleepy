#pragma once

#include <sleepy/common.hpp>

namespace sleepy
{
	struct opcode
	{
		byte_t prefix;
		byte_t value;

		opcode(byte_t val)
		{
			prefix = static_cast<byte_t>(0x00);
			value = val;
		}

		opcode(byte_t prefix, byte_t val)
		{
			prefix = prefix;
			value = val;
		}

		opcode(const opcode& copy)
		{
			this->prefix = copy.prefix;
			this->value = copy.value;
		}

		word_t get()
		{
			return (prefix << 8) | (value);
		}

		bool operator ==(const opcode& o) const
		{
			return compose_word(o.prefix, o.value) == compose_word(prefix, value);
		}

		bool operator <(const opcode& o) const
		{
			return compose_word(o.prefix, o.value) < compose_word(prefix, value);
		}

		bool operator >(const opcode& o) const
		{
			return compose_word(o.prefix, o.value) > compose_word(prefix, value);
		}
	};
}