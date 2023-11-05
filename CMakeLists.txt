cmake_minimum_required(VERSION 3.22)
project(grpc_test)

#
# Project Settings
#
include("$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)

#
# Subprojects
#
add_subdirectory(protos)
add_subdirectory(server)
add_subdirectory(client)
add_subdirectory(tests)
