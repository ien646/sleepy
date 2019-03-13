#include <sleepy/vcpu.hpp>

#include <fstream>
#include <iostream>
#include <iomanip>
#include <thread>

static void print_registers(const sleepy::registers* regs)
{
    std::cout << std::hex;
    std::cout 
        << "A: " << regs->a << " | "
        << "B: " << regs->b << " | "
        << "C: " << regs->c << " | "
        << "D: " << regs->d << " | "
        << "E: " << regs->e << " | "
        << "F: " << regs->f << " | "
        << "H: " << regs->h << " | "
        << "L: " << regs->l << " | "
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

static void debug_pre(
    sleepy::vcpu& vcpu,
    const sleepy::vcpu_instruction* inst)
{
    std::cout << "Next instruction: " << inst->mnemonic << std::endl;
    std::cout << "Arguments: ";
    if(inst->arg_count == 0) 
    { 
        std::cout << "None" << std::endl; 
    }
    else
    {
        for(sleepy::u8 i = 0; i < inst->arg_count; i++)
        {
            sleepy::u8 arg = vcpu.memory().read_byte(vcpu.registers().pc + 1 + i);
            std::cout << "[" << static_cast<int>(i) << "]=" << static_cast<int>(arg);
        }
        std::cout << std::endl;
    }
    
    print_registers(&vcpu.registers());
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(2s);
}

static void debug_post(
    [[maybe_unused]] sleepy::vcpu& vcpu,
    [[maybe_unused]] const sleepy::vcpu_instruction* inst)
{
    return;
}

int main(int argc, char** argv)
{
    sleepy::vcpu vcpu;

    if (argc < 2) { return -1; }

    std::string fpath(argv[1]);
    std::ifstream ifs(fpath, std::ios::in | std::ios::binary);

    if(!ifs) { return -2; }

    vcpu.setup_memory(ifs);
    vcpu.setup_debug(&debug_pre, &debug_post);
    vcpu.start();

    return 0;
}