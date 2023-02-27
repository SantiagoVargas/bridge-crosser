cmake_minimum_required (VERSION 3.5)
project (BridgeCrosser)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)

add_subdirectory(yaml-cpp)

# Bridge crosser library
set(
    LIB_SOURCES 
    src/lib/simulator.cpp 
    src/lib/simulator.h 
    src/lib/structs.h 
    src/lib/yaml-parser.cpp 
    src/lib/yaml-parser.h
)

add_library(
    bridge_crosser_lib
    STATIC ${LIB_SOURCES}
)

target_link_libraries(
    bridge_crosser_lib
    PRIVATE yaml-cpp
)

target_include_directories(
    bridge_crosser_lib
    PUBLIC src/lib/
)

# Bridge crosser executable
add_executable(
    bridge_crosser
    src/main.cpp
)

target_link_libraries(
    bridge_crosser
    PRIVATE bridge_crosser_lib
)

# Testing using GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
    main_tests
    src/tests/simulator_tests.cpp
)

target_link_libraries(
    main_tests
    PRIVATE GTest::gtest_main
    PRIVATE bridge_crosser_lib
)

include(GoogleTest)
gtest_discover_tests(main_tests)