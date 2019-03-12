#pragma once

#include <sleepy/vcpu_impl.hpp>
#include <sleepy/vcpu_instruction.hpp>
#include <sleepy/memory.hpp>
#include <sleepy/registers.hpp>

#define _CPUFW_SLEEPYTEST_INIT_VARS()	[[maybe_unused]] registers regs; \
										[[maybe_unused]] memory mem; \
										[[maybe_unused]] vcpu_impl vfw(&mem, &regs); \
										[[maybe_unused]] auto& inst_map = vfw.inst_map; \
										mem.zero_memory(); \
										regs.zero_registers(true);\
										[[maybe_unused]] const registers::flag FLAG_SUB = registers::flag::SUB;\
										[[maybe_unused]] const registers::flag FLAG_ZERO = registers::flag::ZERO;\
										[[maybe_unused]] const registers::flag FLAG_HCARRY = registers::flag::HALF_CARRY;\
										[[maybe_unused]] const registers::flag FLAG_CARRY = registers::flag::CARRY

/* Initialize common cpu firmware unit test variables [sys,regs,mem,inst_map] */
#define CPUFW_SLEEPY_TESTINIT() _CPUFW_SLEEPYTEST_INIT_VARS()