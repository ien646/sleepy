#include <sleepy/memory.hpp>

namespace sleepy
{
	byte_t memory::read_byte(addr_t address)
	{
		return (*_memory)[address];
	}

	word_t memory::read_word(addr_t address)
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
}