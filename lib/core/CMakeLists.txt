file(GLOB SLEEPY_CORE_SOURCES 
    src/instruction_impl.cpp
    src/instruction_map.cpp
    src/memory.cpp
    src/opcode.cpp
    src/registers.cpp
    src/tile_map_reader.cpp
    src/vcpu_impl.cpp
    src/vcpu.cpp
)

add_library(sleepy.core ${SLEEPY_CORE_SOURCES})
target_include_directories(sleepy.core PUBLIC include)