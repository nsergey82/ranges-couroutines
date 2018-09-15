cmake_minimum_required(VERSION 3.8)
project(ranges)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_VERBOSE_MAKEFILE ON)

#set(Boost_DEBUG 1)
find_package(Boost REQUIRED COMPONENTS system context coroutine thread)

add_subdirectory(range-v3)
include_directories(range-v3/include)

add_subdirectory(RxCpp)
include_directories(RxCpp/Rx/v2/src/rxcpp)

add_subdirectory(googletest)
include_directories(googletest/include ${gtest_SOURCE_DIR})

set(BENCHMARK_ENABLE_GTEST_TESTS OFF CACHE BOOL "Disable Google Test in benchmark" FORCE)
add_subdirectory(benchmark)
include_directories(${benchmark_SOURCE_DIR}/include ${benchmark_BINARY_DIR})

add_executable(bench bench.cpp count_record_breaking/count_helpers.h count_record_breaking/count_helpers.h count_record_breaking/count_record_breaking_vanilla.h)
target_link_libraries(bench
        PUBLIC
          Boost::boost
          benchmark
        PRIVATE
          Boost::system
          Boost::context
          Boost::coroutine
          Boost::thread)

# add_executable(utest ${SOURCE_FILES} utest.cpp)
# target_link_libraries(utest ${Boost_LIBRARIES} gtest gtest_main )

add_executable(foo foo.cpp)
target_link_libraries(foo
        PUBLIC
            Boost::boost
        PRIVATE
            Boost::system
            Boost::context
            Boost::coroutine
            Boost::thread)