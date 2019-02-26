#pragma once

#include <sleepy/common.hpp>

namespace sleepy
{
	struct opcode
	{
		byte_t prefix;
		byte_t value;

		opcode(byte_t val);
		opcode(byte_t prefix, byte_t val);
		opcode(const opcode& copy);

		word_t get();

		bool operator ==(const opcode&) const;
		bool operator <(const opcode&) const;
		bool operator >(const opcode&) const;
	};
}