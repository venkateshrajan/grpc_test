cmake_minimum_required(VERSION 3.22)

#
# Dependencies
#
find_package(absl CONFIG REQUIRED)
find_package(glog REQUIRED)
find_package(gRPC REQUIRED)
set(DEPENDENCIES
  absl::base
  absl::flags
  absl::strings
  glog::glog
  myproto
  gRPC::grpc++_reflection
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
add_executable(server ${SOURCES})
target_link_libraries(server PRIVATE ${DEPENDENCIES})
target_precompile_headers(server PRIVATE ${grpc_test_SOURCE_DIR}/pch.h)
