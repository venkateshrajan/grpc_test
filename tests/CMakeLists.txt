cmake_minimum_required(VERSION 3.22)

find_package(glog REQUIRED)
find_package(GTest REQUIRED)
add_executable(tests Main.cpp)
target_link_libraries(tests PRIVATE glog::glog GTest::gtest GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(tests)
