cmake_minimum_required(VERSION 3.22)

include_directories(${grpc_test_SOURCE_DIR})
find_package(glog REQUIRED)
add_executable(client Main.cpp)
target_link_libraries(client PRIVATE glog::glog)
