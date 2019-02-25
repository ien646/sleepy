file(GLOB SLEEPY_TEST_CORE_SOURCES src/*.cpp)

add_executable(sleepy2.test.core ${SLEEPY_TEST_CORE_SOURCES})
target_link_libraries(sleepy2.test.core sleepy2.core Catch2::Catch2)