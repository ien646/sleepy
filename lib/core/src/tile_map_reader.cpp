#include <sleepy/tile_map_reader.hpp>

namespace sleepy
{
    const u16 ADDR_TILE_DATA_0 = 0x8000;
    const u16 ADDR_TILE_DATA_1 = 0x8800;
    const u16 TILE_STRIDE = 0x0010;

    tile_map_reader::tile_map_reader(const memory* mem)
    {
        _mem = mem;
    }

    tile_data_t tile_map_reader::read_tile_idx(int tile_idx, int map_idx)
    {
        u16 tile_addr = (map_idx ? ADDR_TILE_DATA_1 : ADDR_TILE_DATA_0) 
            + (tile_idx * TILE_STRIDE);
        
        tile_data_t result;
        for(int i = 0; i < TILE_STRIDE; i += 2)
        {
            u8 line_a = _mem->read_byte(tile_addr + i);
            u8 line_b = _mem->read_byte(tile_addr + i + 1);

            for(int j = 0; j < 8; ++j)
            {
                result[(i * 8) + j] = get_bit(line_a, j) + get_bit(line_b, j);
            }
        }
        return result;
    }

    std::vector<tile_data_t> tile_map_reader::read_all_tiles()
    {
        std::vector<tile_data_t> result;
        for(int map_idx = 0; map_idx < 2; ++map_idx)
        {
            for(int tile_idx = 0; tile_idx < 256; ++ tile_idx)
            {
                result.push_back(read_tile_idx(tile_idx, map_idx));
            }
        }
        return result;
    }
}