file(GLOB SLEEPY_SYSTEM_SOURCES 
    src/system.cpp
)

add_library(sleepy.system ${SLEEPY_SYSTEM_SOURCES})
target_link_libraries(sleepy.system sleepy.core)
target_include_directories(sleepy.system PUBLIC include)