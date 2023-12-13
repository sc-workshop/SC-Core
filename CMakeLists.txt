cmake_minimum_required(VERSION 3.26)

include(cmake/SupercellCore.cmake)

# Options
option(SC_CORE_TEST "Build Core Test" ON)

project("SupercelllCore")

if(${SC_CORE_TEST})
  add_executable("SupercellCoreTest"
    "test/main.cpp"
  )

  sc_core_base_setup("SupercellCoreTest")
  target_link_libraries("SupercellCoreTest" PUBLIC SupercellCore)
endif()