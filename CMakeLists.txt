cmake_minimum_required(VERSION 3.22)

project(grpc_test)

include("$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(server)
add_subdirectory(client)
add_subdirectory(tests)

target_precompile_headers(server PRIVATE pch.h)
target_precompile_headers(client PRIVATE pch.h)
target_precompile_headers(tests PRIVATE pch.h)
