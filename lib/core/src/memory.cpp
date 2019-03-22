#include <sleepy/memory.hpp>

#include <vector>
#include <algorithm>

namespace sleepy
{
	memory::memory()		
	{
		_memory = std::make_unique<std::array<u8, TOTAL_MEM_SZ>>();
	}

	u8 memory::read_byte(u16 address) const
	{
		return (*_memory)[address];
	}

	u16 memory::read_word(u16 address) const
	{
		u8* ptr = &(*_memory)[address];
		return *reinterpret_cast<u16*>(ptr);
	}

	u8* memory::data()
	{
		return _memory->data();
	}

	void memory::write_byte(u16 address, u8 value)
	{
		(*_memory)[address] = value;
	}

	void memory::write_word(u16 address, u16 value)
	{
		u16* ptr = reinterpret_cast<u16*>(&(*_memory)[address]);
		*ptr = value;
	}

	void memory::zero_memory()
	{
		_memory->fill(0x00);
	}

    void memory::load_data(std::istream& data, u16 offset)
    {        
        std::istreambuf_iterator<char> begin(data);
        std::istreambuf_iterator<char> end;
        std::vector<u8> cdata(begin, end);
        std::copy(cdata.begin(), cdata.end(), _memory->data() + offset);
    }
}