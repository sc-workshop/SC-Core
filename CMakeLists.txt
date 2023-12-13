cmake_minimum_required(VERSION 3.26)
include(cmake/SupercellCore.cmake)

project("SupercelllCore")


add_executable("SupercellCoreTest"
  "test/main.cpp"
)

sc_core_base_setup("SupercellCoreTest")
target_link_libraries("SupercellCoreTest" PUBLIC SupercellCore)