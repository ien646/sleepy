#pragma once

#include <sleepy/common.hpp>

namespace sleepy
{
	struct opcode
	{
		u8 prefix;
		u8 value;

		explicit opcode(u8 val);
		opcode(u8 prefix, u8 val);

		u16 get();

		bool operator ==(const opcode&) const;
		bool operator <(const opcode&) const;
		bool operator >(const opcode&) const;

		constexpr bool is_extended() const noexcept 
		{ 
			return prefix == 0xCBu; 
		}
	};
}