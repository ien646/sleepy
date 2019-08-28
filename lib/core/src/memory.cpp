#include <sleepy/memory.hpp>

#include <vector>
#include <algorithm>
#include <streambuf>
#include <unordered_map>
#include <functional>

namespace sleepy
{
	const std::unordered_map<u16, std::function<void(memory*)>> _special_writes =
	{
		{ 0xFF44, [](memory* mem) { mem->write_byte(0xFF44, 0x00); }}
	};

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
	
	const u8* memory::cdata() const
	{
		return _memory->data();
	}

	void memory::write_byte(u16 address, u8 value)
	{
		if(_special_writes.count(address))
		{
			_special_writes.at(address)(this);
		}
		else
		{
			((*_memory))[address] = value;
		}
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
        std::copy(cdata.begin(), cdata.end(), _memory->begin() + offset);
    }
}