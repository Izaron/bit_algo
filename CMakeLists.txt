cmake_minimum_required(VERSION 3.9.2)
set(CMAKE_CXX_STANDARD ${YEAR})
project(bit_algo)

### TESTING
enable_testing()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

file(GLOB SOURCE_FILES "test/*cpp")

# Boost
find_package(Boost COMPONENTS random system chrono REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

add_subdirectory(test build/test)
