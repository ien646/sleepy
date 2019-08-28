file(GLOB SLEEPY_TEST_CORE_SOURCES 
src/*.cpp 
src/opcodes/standard/*.cpp
src/opcodes/extended/*.cpp)

set(CMAKE_CXX_STACK_SIZE 20000000)

add_executable(sleepy.test.core ${SLEEPY_TEST_CORE_SOURCES})
target_link_libraries(sleepy.test.core sleepy.core Catch2::Catch2)