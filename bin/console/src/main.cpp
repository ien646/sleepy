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
    if (argc < 2)
    {
        return -1;
    }

    std::ifstream fs(std::string(argv[1]), std::ios::binary);
    if(!fs) { return -2; }
    char ch = 0;
    bool prefix_flag = false;
    char prefix;
    while(fs.get(ch))
    {
        if(ch == 0x00) {continue;}
        if(ch == 0xCB)
        {
            prefix = true;
        }
        else
        {
            if(prefix)
            {
                
            }
            else
            {
                sleepy::opcode opc(static_cast<sleepy::byte_t>(ch));
                auto& inst_data = vcpu.get_inst_data(opc);
                if(inst_data.cycles == 0xFF) { continue; }
                system("cls");
                print_registers(&vcpu.registers());
                std::cout 
                        << "Incoming instruction: "
                        << "[ " << inst_data.mnemonic << " ]"
                        << std::endl;

                using namespace std::chrono_literals;
                std::this_thread::sleep_for(0.015s);

                std::vector<sleepy::byte_t> argvec;
                for(size_t i = 0; i < inst_data.arg_count; i++) 
                { 
                    argvec.push_back(static_cast<sleepy::byte_t>(fs.get()));
                }
                vcpu.exec_op(opc, argvec.data());
            }
            prefix = false;
        }
    }
}