#pragma once

#include <sleepy/common.hpp>

namespace sleepy
{
	struct opcode
	{
		byte_t prefix;
		byte_t value;

		explicit opcode(byte_t val);
		opcode(byte_t prefix, byte_t val);

		word_t get();

		bool operator ==(const opcode&) const;
		bool operator <(const opcode&) const;
		bool operator >(const opcode&) const;

		constexpr bool is_extended() const noexcept 
		{ 
			return prefix == 0xCBu; 
		}
	};
}