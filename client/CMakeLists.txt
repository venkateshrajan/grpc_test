cmake_minimum_required(VERSION 3.22)

#
# Dependencies
#
find_package(absl CONFIG REQUIRED)
find_package(glog CONFIG REQUIRED)
set(DEPENDENCIES
  absl::flags
  absl::flags_parse
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
include_directories(${CMAKE_CURRENT_BINARY_DIR})

#
# Target
#
add_executable(client ${SOURCES})
target_link_libraries(client PRIVATE ${DEPENDENCIES})
target_precompile_headers(client PRIVATE ${grpc_test_SOURCE_DIR}/pch.h)
