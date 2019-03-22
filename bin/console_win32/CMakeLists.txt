set(CMAKE_RUNTIME_OUTPUT_DIRECTORY 			${PROJECT_BINARY_DIR}/output/bin/sleepy.console_win32/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG 	${PROJECT_BINARY_DIR}/output/bin/sleepy.console_win32/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE 	${PROJECT_BINARY_DIR}/output/bin/sleepy.console_win32/)

file(GLOB SLEEPY_CONSOLE_SOURCES src/*.cpp)
add_executable(sleepy.console_win32 ${SLEEPY_CONSOLE_SOURCES})
target_link_libraries(sleepy.console_win32 sleepy.core)