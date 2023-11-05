cmake_minimum_required(VERSION 3.22)

#
# Dependencies list
#
find_package(glog REQUIRED)
find_package(GTest REQUIRED)
set(DEPENDENCIES
  glog::glog
  GTest::gtest
  GTest::gtest_main
)

#
# Sources
#
set(SOURCES
  Main.cpp
)

#
# Target
#
include_directories(${grpc_test_SOURCE_DIR})
add_executable(tests ${SORUCES})
target_link_libraries(tests PRIVATE ${DEPENDENCIES})
target_precompile_headers(tests PRIVATE pch.h)

#
# GTest stuffs
#
include(GoogleTest)
gtest_discover_tests(tests)
