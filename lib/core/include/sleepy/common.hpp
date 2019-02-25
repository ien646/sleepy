#pragma once

#include <cinttypes>
#include <memory>
#include <utility>

#define UNREFERENCED_PARAMETER(x) x

namespace sleepy
{
    template<typename T>
    using UPTR = std::unique_ptr<T>;

	/* -- Memory data types -- */
	typedef uint8_t byte_t;
	typedef uint16_t word_t;
	typedef uint16_t addr_t;
	typedef uint32_t dword;

	/* -- Register value types -- */
	typedef uint8_t reg8_t;
	typedef uint16_t reg16_t;

	const byte_t  HBYTE_MAX = 0x0F;
	const byte_t  BYTE_MAX	= 0xFF;
	const word_t  WORD_MAX	= 0xFFFF;
	const dword   DWORD_MAX	= 0xFFFFFFFF;

	const byte_t FLAG_ZERO	 = 0x80;
	const byte_t FLAG_SUB	 = 0x40;	
	const byte_t FLAG_HCARRY = 0x20;
	const byte_t FLAG_CARRY	 = 0x10;

	constexpr inline byte_t hibyte(word_t val) 	
	{ 
		return (byte_t)(val >> 8); 
	}

	constexpr inline byte_t lobyte(word_t val)
	{
		return (byte_t)val;
	}

	constexpr inline word_t compose_word(byte_t hibyte, byte_t lobyte)
	{
		return (hibyte << 8) | lobyte;
	}

	constexpr inline word_t read_word(const byte_t* addr)
	{
		return *((word_t*)(addr));
	}

	constexpr inline bool get_bit(byte_t value, byte_t index)
	{
		return (value | (1 << index)) == value;
	}

	constexpr inline bool get_bit(word_t value, byte_t index)
	{
		return (value | (1 << index)) == value;
	}
}