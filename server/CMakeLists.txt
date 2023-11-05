cmake_minimum_required(VERSION 3.22)

#
# Dependencies
#
find_package(absl CONFIG REQUIRED)
find_package(glog CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)
set(DEPENDENCIES
  absl::flags
  absl::flags_parse
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
include_directories(${CMAKE_CURRENT_BINARY_DIR})

#
# Target
#
add_executable(server ${SOURCES})
target_link_libraries(server PRIVATE ${DEPENDENCIES})
target_precompile_headers(server PRIVATE ${grpc_test_SOURCE_DIR}/pch.h)
