cmake_minimum_required(VERSION 3.22)


# workspace
project(supercell-sdk)

# options
option(SC_CORE_BUILD_SHARED "Build supercell::core library as shared library" OFF)


# lets force C++17
set(CMAKE_CXX_STANDARD 17)

# includes
include(FetchContent)
include(cmake/supercell-sdk-macros.cmake)


# projects
add_subdirectory(supercell-core)
