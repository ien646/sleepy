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

		void write_byte(addr_t address, byte_t value);
		void write_word(addr_t address, word_t value);
		byte_t read_byte(addr_t address);
		word_t read_word(addr_t address);

		/* Return raw pointer to memory address 0x0000 */
		byte_t* data();

		void zero_memory();
	private:
		static constexpr size_t TOTAL_MEM_SZ = 0x10000;
		std::unique_ptr<std::array<byte_t, TOTAL_MEM_SZ>> _memory;
	};
}