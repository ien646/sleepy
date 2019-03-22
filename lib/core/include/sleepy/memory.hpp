#pragma once

#include <memory>
#include <array>

#include <sleepy/common.hpp>

namespace sleepy
{
	class memory
	{
	public:
		memory();
		memory(const memory& copy_src) = delete;
		memory(memory&& move_src) = delete;

		void write_byte(u16 address, u8 value);
		void write_word(u16 address, u16 value);
		u8 read_byte(u16 address) const;
		u16 read_word(u16 address) const;

		/* Return raw pointer to memory address 0x0000 */
		u8* data();

		void zero_memory();

        void load_data(std::istream&, u16 index = 0u);
	private:
		static constexpr size_t TOTAL_MEM_SZ = 0x10000;
		std::unique_ptr<std::array<u8, TOTAL_MEM_SZ>> _memory;
	};
}