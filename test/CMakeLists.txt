project(tests)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# Boost
find_package(Boost COMPONENTS random system chrono REQUIRED)

set(test_source main.cpp)
add_executable(test1 ${test_source})
target_link_libraries(test1 ${Boost_LIBRARIES})

add_test (NAME MyTest COMMAND test1)
