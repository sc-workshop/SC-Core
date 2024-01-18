cmake_minimum_required(VERSION 3.22)

project("SupercelllCore" CXX)

include(cmake/SupercellCore.cmake)

# Options
option(SC_CORE_TEST "Build Core Test" ON)

if(${SC_CORE_TEST})
  add_executable("SupercellCoreTest"
    "test/main.cpp"
  )

  sc_core_base_setup("SupercellCoreTest")
  target_link_libraries("SupercellCoreTest" PUBLIC SupercellCore)
  set_target_properties("SupercellCoreTest" PROPERTIES
    FOLDER Supercell/CLI
  )
endif()