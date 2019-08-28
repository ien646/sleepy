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

	void memory::init_state()
	{
		(*_memory)[0xFF05] = 0x00;
        (*_memory)[0xFF06] = 0x00;
        (*_memory)[0xFF07] = 0x00;
        (*_memory)[0xFF10] = 0x80;
        (*_memory)[0xFF11] = 0xBF;
        (*_memory)[0xFF12] = 0xF3;
        (*_memory)[0xFF14] = 0xBF;
        (*_memory)[0xFF16] = 0x3F;
        (*_memory)[0xFF17] = 0x00;
        (*_memory)[0xFF19] = 0xBF;
        (*_memory)[0xFF1A] = 0x7F;
        (*_memory)[0xFF1B] = 0xFF;
        (*_memory)[0xFF1C] = 0x9F;
        (*_memory)[0xFF1E] = 0xBF;
        (*_memory)[0xFF20] = 0xFF;
        (*_memory)[0xFF21] = 0x00;
        (*_memory)[0xFF22] = 0x00;
        (*_memory)[0xFF23] = 0xBF;
        (*_memory)[0xFF24] = 0x77;
        (*_memory)[0xFF25] = 0xF3;
        (*_memory)[0xFF26] = 0xF1;
        (*_memory)[0xFF40] = 0x91;
        (*_memory)[0xFF42] = 0x00;
        (*_memory)[0xFF43] = 0x00;
        (*_memory)[0xFF45] = 0x00;
        (*_memory)[0xFF47] = 0xFC;
        (*_memory)[0xFF48] = 0xFF;
        (*_memory)[0xFF49] = 0xFF;
        (*_memory)[0xFF4A] = 0x00;
        (*_memory)[0xFF4B] = 0x00;
        (*_memory)[0xFFFF] = 0x00;
	}
}