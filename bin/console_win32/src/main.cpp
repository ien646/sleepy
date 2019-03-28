#include <sleepy/system.hpp>
#include <string>
#include <fstream>

int main(int argc, char** argv)
{
    std::string path(argv[1]);
    sleepy::system sys;
    std::ifstream ifs(path, std::ios::in | std::ios::binary);
    sys.load_cartridge(ifs);
    sys.start();
    return 0;
}