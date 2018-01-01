cmake_minimum_required(VERSION 3.8)
project(ranges)

set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_VERBOSE_MAKEFILE ON)

find_package(Boost COMPONENTS context coroutine system thread REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

add_subdirectory(benchmark)
include_directories(${benchmark_SOURCE_DIR}/include ${benchmark_BINARY_DIR})

add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_subdirectory(range-v3)
include_directories(range-v3/include)

add_subdirectory(RxCpp)
include_directories(RxCpp/Rx/v2/src/rxcpp)

set(SOURCE_FILES fzbz_crtn.h crtn_helpers.h count_bad_good.h fzbz_rng.h fzbz_rx.h fzbz_helpers.h fzbz_vanilla.h)

add_executable(bench ${SOURCE_FILES} bench.cpp)
target_link_libraries(bench ${Boost_LIBRARIES} benchmark)

add_executable(utest ${SOURCE_FILES} utest.cpp)
target_link_libraries(utest ${Boost_LIBRARIES} gtest gtest_main )
