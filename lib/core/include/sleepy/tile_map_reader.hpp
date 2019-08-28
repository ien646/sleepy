#pragma once

#include <sleepy/memory.hpp>
#include <array>
#include <vector>

namespace sleepy
{
    typedef std::array<u8, 64> tile_data_t;

    class tile_map_reader
    {
    private:
        const memory* _mem;

    public:
        tile_map_reader(const memory* mem);

        tile_data_t read_tile_idx(int tile_idx, int map_idx);
        std::vector<tile_data_t> read_all_tiles();
    };
}