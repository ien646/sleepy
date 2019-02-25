file(GLOB SLEEPY_CORE_SOURCES src/*.cpp)

add_library(sleepy2.core STATIC ${SLEEPY_CORE_SOURCES})
target_include_directories(sleepy2.core PUBLIC include)