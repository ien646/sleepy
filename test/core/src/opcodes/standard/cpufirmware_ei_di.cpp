#include <catch2/catch.hpp>

#include "../../cpufw_test_init.hpp"

namespace sleepy
{
	TEST_CASE("CpuFirmware_EI_DI")
	{
		SECTION("CpuFirmware_EI_EnablesInterrupts")
		{
			CPUFW_SLEEPY_TESTINIT();

			auto& ei = inst_map[opcode(0xFB)];

			vfw.disable_interrupts();
			ei.call(nullptr);
			REQUIRE(vfw.interrupts_enabled());

			vfw.enable_interrupts();
			ei.call(nullptr);
			REQUIRE(vfw.interrupts_enabled());
		}

		SECTION("CpuFirmware_DI_EnablesInterrupts")
		{
			CPUFW_SLEEPY_TESTINIT();

			auto& di = inst_map[opcode(0xF3)];

			vfw.enable_interrupts();
			di.call(nullptr);
			REQUIRE(!(vfw.interrupts_enabled()));

			vfw.disable_interrupts();
			di.call(nullptr);
			REQUIRE(!(vfw.interrupts_enabled()));
		}
	}
}