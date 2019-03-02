#include <sleepy/memory.hpp>

namespace sleepy
{
	memory::memory()		
	{
		_memory = std::make_unique<std::array<byte_t, TOTAL_MEM_SZ>>();
	}

	byte_t memory::read_byte(addr_t address) const
	{
		return (*_memory)[address];
	}

	word_t memory::read_word(addr_t address) const
	{
		byte_t* ptr = &(*_memory)[address];
		return *reinterpret_cast<word_t*>(ptr);
	}

	byte_t* memory::data()
	{
		return _memory->data();
	}

	void memory::write_byte(addr_t address, byte_t value)
	{
		(*_memory)[address] = value;
	}

	void memory::write_word(addr_t address, word_t value)
	{
		word_t* ptr = reinterpret_cast<word_t*>(&(*_memory)[address]);
		*ptr = value;
	}

	void memory::zero_memory()
	{
		_memory->fill(0x00);
	}
}