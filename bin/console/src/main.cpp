#include <sleepy/vcpu.hpp>

#include <fstream>
#include <iostream>
#include <iomanip>
#include <thread>
#include <sstream>

int batch_cc = 0;
std::stringstream batch;

static void print_registers(const sleepy::registers* regs)
{
    batch << std::hex;
    batch 
        << "A: " << static_cast<int>(regs->a) << " | "
        << "B: " << static_cast<int>(regs->b) << " | "
        << "C: " << static_cast<int>(regs->c) << " | "
        << "D: " << static_cast<int>(regs->d) << " | "
        << "E: " << static_cast<int>(regs->e) << " | "
        << "F: " << static_cast<int>(regs->f) << " | "
        << "H: " << static_cast<int>(regs->h) << " | "
        << "L: " << static_cast<int>(regs->l) << " | "
        << std::endl;

    batch 
        << "AF:" << regs->af() << " | "
        << "BC:" << regs->bc() << " | "
        << "DE:" << regs->de() << " | "
        << "HL:" << regs->hl() << " | "
        << std::endl;

    batch
        << "PC:" << regs->pc << " | "
        << "SP:" << regs->sp << " | "
        << std::endl;
}

static void debug_pre(
    sleepy::vcpu& vcpu,
    const sleepy::vcpu_instruction* inst)
{    
    if(batch_cc++ % 10 == 0) { std::cout << batch.str(); batch.str(""); }
    batch << "Next instruction: " << inst->mnemonic << std::endl;
    batch << "Arguments: ";
    if(inst->arg_count == 0) 
    { 
        batch << "None" << std::endl; 
    }
    else
    {
        for(sleepy::u8 i = 0; i < inst->arg_count; i++)
        {
            sleepy::u8 arg = vcpu.memory().read_byte(vcpu.registers().pc + 1 + i);
            batch << "[" << static_cast<int>(i) << "]=" << static_cast<int>(arg);
        }
        batch << std::endl;
    }
    
    print_registers(&vcpu.registers());
    using namespace std::chrono_literals;
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