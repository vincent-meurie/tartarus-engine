cmake_minimum_required(VERSION 3.15)
project(TartarusEngine VERSION 0.1.0 LANGUAGES CXX)

# C++20 Standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Compiler warnings
if(MSVC)
    add_compile_options(/W4 /WX-)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Fetch Google Test
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)
# For Windows: Prveent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Fetch GLM (mathematics library)
FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 1.0.1
)
set(GLM_BUILD_TESTS OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(glm)

# Enable testing
enable_testing()
include(GoogleTest)

# Source files (will add as we develop)
set(TARTARUS_SOURCES
    # Will add src files here as we create them
    src/core/Room.cpp
    src/core/Biome.cpp
    src/core/Reward.cpp
)

# Create library (empty for now, will add sources incrementally)
add_library(tartarus_lib ${TARTARUS_SOURCES})
target_include_directories(tartarus_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)
target_link_libraries(tartarus_lib PUBLIC glm::glm)

# Test executable (will add test files as we create them)
set(TARTARUS_TEST_SOURCES
    # Will add test files as we create them
    tests/unit/test_room.cpp
)

add_executable(tartarus_tests ${TARTARUS_TEST_SOURCES})
target_link_libraries(tartarus_tests
    tartarus_lib
    gtest_main
    gmock_main
)

# Discover tests
gtest_discover_tests(tartarus_tests)