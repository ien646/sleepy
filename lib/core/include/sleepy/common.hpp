#pragma once

#include <cinttypes>
#include <memory>
#include <utility>

#define UNREFERENCED_PARAMETER(x) x

namespace sleepy
{
    template<typename T>
    using UPTR = std::unique_ptr<T>;

	/* -- Integer typedefs and casts -- */
	typedef uint8_t u8;
	typedef uint16_t u16;
	typedef uint32_t u32;
	typedef int8_t i8;
	typedef int16_t i16;
	typedef int32_t i32;
	
	template<typename T> constexpr u8 U8(T val) { return static_cast<u8>(val); }
	template<typename T> constexpr u16 U16(T val) { return static_cast<u16>(val); }
	template<typename T> constexpr u32 U32(T val) { return static_cast<u32>(val); }
	template<typename T> constexpr i8 I8(T val) { return static_cast<i8>(val); }
	template<typename T> constexpr i16 I16(T val) { return static_cast<i16>(val); }
	template<typename T> constexpr i32 I32(T val) { return static_cast<i32>(val); }

	const u8  HBYTE_MAX = 0x0F;
	const u8  BYTE_MAX	= 0xFF;
	const u16 WORD_MAX	= 0xFFFF;
	const u32 DWORD_MAX	= 0xFFFFFFFF;

	constexpr u8 hibyte(u16 val) 	
	{ 
		return U8(val >> 8); 
	}

	constexpr u8 lobyte(u16 val)
	{
		return U8(val);
	}

	constexpr u16 compose_word(u8 hibyte, u8 lobyte)
	{
		return (hibyte << 8) | lobyte;
	}

	constexpr u16 read_word(const u8* ptr)
	{
		return *reinterpret_cast<const u16*>(ptr);
	}

	constexpr bool get_bit(u8 value, u8 index)
	{
		return (value | (1 << index)) == value;
	}

	constexpr bool get_bit(u16 value, u8 index)
	{
		return (value | (1 << index)) == value;
	}
}