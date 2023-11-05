cmake_minimum_required(VERSION 3.22)

#
# Dependencies
#
find_package(glog REQUIRED)
set(DEPENDENCIES
  glog::glog
  myproto
)

#
# Source files
#
set(SOURCES
  Main.cpp
)

#
# Includes
#
include_directories(${grpc_test_SOURCE_DIR})
include_directories(${grpc_test_SOURCE_DIR}/build/protos/myproto)

#
# Target
#
add_executable(client ${SOURCES})
target_link_libraries(client PRIVATE ${DEPENDENCIES})
target_precompile_headers(client PRIVATE ${grpc_test_SOURCE_DIR}/pch.h)
