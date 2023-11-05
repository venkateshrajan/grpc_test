cmake_minimum_required(VERSION 3.22)

#
# Dependencies
#
find_package(glog REQUIRED)
set(DEPENDENCIES
  glog::glog
)

#
# Source files
#
set(SOURCES
  Main.cpp
)

#
# Target
#
include_directories(${grpc_test_SOURCE_DIR})
add_executable(client ${SOURCES})
target_link_libraries(client PRIVATE ${DEPENDENCIES})
target_precompile_headers(client PRIVATE pch.h)
