file(GLOB SLEEPY_CORE_SOURCES src/*.cpp)

add_library(sleepy.core STATIC ${SLEEPY_CORE_SOURCES})
target_include_directories(sleepy.core PUBLIC include)