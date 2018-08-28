# Boost 1.68 requires CMake 3.12 or newer
cmake_minimum_required(VERSION 3.12)
project(bit_algo)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

file(GLOB SOURCE_FILES "test/*cpp")

# Boost
find_package(Boost COMPONENTS random system chrono REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

# Executable
add_executable(bit_algo ${SOURCE_FILES})

target_link_libraries(bit_algo ${Boost_LIBRARIES})
