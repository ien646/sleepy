#include <sleepy/vcpu.hpp>

#include <fstream>
#include <iostream>
#include <thread>

static void print_registers(const sleepy::registers* regs)
{
    std::cout << std::hex;
    std::cout 
        << "A: " << (int)regs->a << " | "
        << "B: " << (int)regs->b << " | "
        << "C: " << (int)regs->c << " | "
        << "D: " << (int)regs->d << " | "
        << "E: " << (int)regs->e << " | "
        << "F: " << (int)regs->f << " | "
        << "H: " << (int)regs->h << " | "
        << "L: " << (int)regs->l << " | "
        << std::endl;

    std::cout 
        << "AF:" << regs->af() << " | "
        << "BC:" << regs->bc() << " | "
        << "DE:" << regs->de() << " | "
        << "HL:" << regs->hl() << " | "
        << std::endl;

    std::cout 
        << "PC:" << regs->pc << " | "
        << "SP:" << regs->sp << " | "
        << std::endl;
}

int main(int argc, char** argv)
{
    sleepy::vcpu vcpu;

    if (argc < 2) { return -1; }

    std::string fpath(argv[1]);
    std::ifstream ifs(fpath, std::ios::binary);

    if(!ifs) { return -2; }

    vcpu.setup_memory(ifs);
    vcpu.start();

    return 0;
}