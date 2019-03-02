#include <sleepy/vcpu.hpp>

#include <fstream>
#include <iostream>
#include <iomanip>
#include <thread>

class pv8
{
public:
    sleepy::byte_t val;
    pv8(sleepy::byte_t v) : val(v) { }
};

class pv16
{
public:
    sleepy::word_t val;
    pv16(sleepy::word_t v) : val(v) { }
};

std::ostream& operator<< (std::ostream& os, const pv8& t) 
{
    if (os.iword(std::ios_base::xalloc()))
        return os << std::hex << std::setw(2) << std::setfill('0') << t.val;
    else
        return os << t.val;
}

std::ostream& operator<< (std::ostream& os, const pv16& t) 
{
    if (os.iword(std::ios_base::xalloc()))
        return os << std::hex << std::setw(4) << std::setfill('0') << t.val;
    else
        return os << t.val;
}

static void print_registers(const sleepy::registers* regs)
{
    std::cout << std::hex;
    std::cout 
        << "A: " << pv8(regs->a) << " | "
        << "B: " << pv8(regs->b) << " | "
        << "C: " << pv8(regs->c) << " | "
        << "D: " << pv8(regs->d) << " | "
        << "E: " << pv8(regs->e) << " | "
        << "F: " << pv8(regs->f) << " | "
        << "H: " << pv8(regs->h) << " | "
        << "L: " << pv8(regs->l) << " | "
        << std::endl;

    std::cout 
        << "AF:" << pv16(regs->af()) << " | "
        << "BC:" << pv16(regs->bc()) << " | "
        << "DE:" << pv16(regs->de()) << " | "
        << "HL:" << pv16(regs->hl()) << " | "
        << std::endl;

    std::cout 
        << "PC:" << pv16(regs->pc) << " | "
        << "SP:" << pv16(regs->sp) << " | "
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