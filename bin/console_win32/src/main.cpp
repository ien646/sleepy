#include <sleepy/system.hpp>
#include <string>
#include <fstream>
#include <thread>

#include <winconw/console.hpp>
#include <winconw/basic_widgets.hpp>

class registers_widget : public wcw::widget
{
private:
    const sleepy::registers* _regs;

public:
    registers_widget(wcw::console* con_ptr, wcw::rect bounds, wcw::widget* parent = nullptr)
        : widget(con_ptr, bounds, parent)
    { }

    void bind_registers(const sleepy::registers* regs_ptr)
    {
        _regs = regs_ptr;
    }

    void update() override
    {
        fill_background();
        write_at("A: " + sleepy::to_hex(_regs->a), 0, 0);
        write_at("F: " + sleepy::to_hex(_regs->f), 0, 1);
        write_at("B: " + sleepy::to_hex(_regs->b), 0, 2);
        write_at("C: " + sleepy::to_hex(_regs->c), 0, 3);
        write_at("D: " + sleepy::to_hex(_regs->d), 0, 4);
        write_at("E: " + sleepy::to_hex(_regs->e), 0, 5);
        write_at("H: " + sleepy::to_hex(_regs->h), 0, 6);
        write_at("L: " + sleepy::to_hex(_regs->l), 0, 7);

        write_at("  AF: " + sleepy::to_hex(_regs->af()), 8, 0);
        write_at("  BC: " + sleepy::to_hex(_regs->bc()), 8, 1);
        write_at("  DE: " + sleepy::to_hex(_regs->de()), 8, 2);
        write_at("  HL: " + sleepy::to_hex(_regs->hl()), 8, 3);
        write_at("  PC: " + sleepy::to_hex(_regs->pc),   8, 4);
        write_at("  SP: " + sleepy::to_hex(_regs->sp),   8, 5);
    }
};

class dissasm_widget : public wcw::lineview_widget
{
private:
    const sleepy::vcpu* _vcpu;
    const sleepy::memory* _memory;

public:
    dissasm_widget(wcw::console* con_ptr, wcw::rect bounds, wcw::widget* parent = nullptr)
        : lineview_widget(con_ptr, bounds, parent)
    { }

    void bind(const sleepy::vcpu* vcpu, const sleepy::memory* mem)
    {
        _vcpu = vcpu;
        _memory = mem;

        using namespace sleepy;
        auto v = _vcpu->get_vcpu_impl();

        for(u16 i = 0; i < 0xFFFF; ++i)
        {
            std::stringstream sstr;

            sstr << to_hex(static_cast<u16>(i));

            u8 val = _memory->cdata()[i];
            opcode opc(0x00, 0x00);
            if(val == 0xCB)
            {
                u8 s_opc = _memory->cdata()[i];
                opc = opcode(0xCB, s_opc);
                ++i;
            }
            else
            {
                opc = opcode(0x00, val);
            }

            const auto& inst = _vcpu->get_vcpu_impl()->inst_map[opc];
            sstr << "    " << inst.mnemonic;
            
            if(inst.arg_count > 0)
            {
                std::vector<u8> args;
                for(size_t a = 0; a < inst.arg_count; ++a)
                {
                    u8 arg = _memory->cdata()[i + 1 + a];
                    sstr << "[" << a << "]:" << to_hex(arg);
                }
                i += inst.arg_count;
            }
            add_line(sstr.str());
        }
    }

    void update() override
    {
        _vertical_offset = std::max(sleepy::U16(0), _vcpu->registers().pc);
        lineview_widget::update();
    }
};

wcw::console console;
wcw::time_widget* wtime;
registers_widget* wregs;
dissasm_widget* wdisasm;

static void debug_pre(const sleepy::vcpu*, const sleepy::vcpu_instruction*)
{
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(1s);
    console.update();
    console.draw();
}

int main(int argc, char** argv)
{ 
    std::string path(argv[1]);
    sleepy::system sys;
    std::ifstream ifs(path, std::ios::in | std::ios::binary);

    sys.setup_debug(&debug_pre, &debug_pre);

    console.initialize(wcw::rect(0, 0, 80, 40));

    wtime = console.add_widget<wcw::time_widget>(wcw::rect(0, 39, 40, 1));

    wregs = console.add_widget<registers_widget>(wcw::rect(0, 0, 20, 8));
    wregs->set_current_color(wcw::color::BLACK, wcw::color::YELLOW);
    wregs->bind_registers(&sys.vcpu()->registers());   

    sys.load_cartridge(ifs);

    wdisasm = console.add_widget<dissasm_widget>(wcw::rect(22, 0, 58, 38));
    wdisasm->bind(sys.vcpu(), sys.vcpu()->memory());
    wdisasm->set_current_color(wcw::color::WHITE, wcw::color::DARK_BLUE);

    sys.start();    

    return 0;
}