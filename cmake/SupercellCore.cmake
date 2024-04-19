include(FetchContent)

# Base Prepare
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Core Files
set(Core_Sources
  "source/generic/image/image.cpp"
  "source/generic/image/raw_image.cpp"

  "source/memory/Allocator/STL/MemoryPool.cpp"

  "source/stb/stb.cpp"

  "source/logger/time.cpp"
)

set(Core_Headers
  "include/exception/GeneralRuntimeException.h"
  "include/exception/MemoryAllocationException.h"
  "include/exception/image/BasicExceptions.h"
  "include/exception/image/StbExceptions.h"
  "include/exception/io/BinariesExceptions.h"
  "include/exception/io/FileExceptions.h"
  "include/exception/io/IOGeneralException.h"

  "include/generic/image/raw_image.h"
  "include/generic/image/image.h"
  "include/generic/image/compressed_image.h"
  "include/generic/md5.h"
  "include/generic/ref.h"

  "include/io/buffer_stream.h"
  "include/io/endian.h"
  "include/io/file_stream.h"
  "include/io/memory_stream.h"
  "include/io/stream.h"

  "include/math/alpha_color.h"
  "include/math/color.h"
  "include/math/matrix2x3.h"
  "include/math/point.h"
  "include/math/rect.h"

  "include/memory/Allocator/STL/MemoryPool.h"
  "include/memory/alloc.h"

  "include/stb/stb.h"
  "include/stb/stb_image.h"
  "include/stb/stb_image_resize.h"
  "include/stb/stb_image_write.h"

  "include/logger/time.h"
)

add_library("SupercellCore" STATIC ${Core_Sources} ${Core_Headers})
source_group(TREE ${CMAKE_SOURCE_DIR} FILES ${Core_Sources} ${Core_Headers})
set_target_properties("SupercellCore" PROPERTIES
  FOLDER Supercell
)

target_include_directories("SupercellCore"
  PUBLIC
  "include/"
)

macro(sc_set_global var_name var_value)
    set(${var_name} ${var_value} CACHE INTERNAL "")
    add_compile_definitions(
        ${var_name}=${var_value}
    )
endmacro()

macro(sc_core_base_setup project_name)
# Defines
  sc_set_global(SC_GNU_DEF_fe "$<STREQUAL:${CMAKE_CXX_COMPILER_FRONTEND_VARIANT},GNU>")
  sc_set_global(SC_GNU_APPLE_fe "$<STREQUAL:${CMAKE_CXX_COMPILER_FRONTEND_VARIANT},AppleClang>")
  sc_set_global(SC_GNU_fe "$<OR:${SC_GNU_DEF_fe},${SC_GNU_APPLE_fe}>")
  sc_set_global(SC_MSVC_fe "$<STREQUAL:${CMAKE_CXX_COMPILER_FRONTEND_VARIANT},MSVC>")

  sc_set_global(SC_CLANG "$<OR:${SC_GNU_fe},$<CXX_COMPILER_ID:Clang>>")
  sc_set_global(SC_GNU "$<OR:${SC_GNU_fe},$<CXX_COMPILER_ID:GNU>>")
  sc_set_global(SC_MSVC "$<OR:${SC_MSVC_fe},$<CXX_COMPILER_ID:MSVC>>")

  sc_set_global(SC_DEBUG "$<CONFIG:Debug>")
  sc_set_global(SC_RELEASE "$<CONFIG:Release,RelWithDebInfo,MinSizeRel>")

  sc_set_global(SC_X86_64 "$<STREQUAL:${CMAKE_SYSTEM_PROCESSOR},x86_64>")
  sc_set_global(SC_AARCH64 "$<STREQUAL:${CMAKE_SYSTEM_PROCESSOR},aarch64>")

  sc_set_global(SC_X64 "$<OR:${SC_X86_64},${SC_AARCH64}>")

# Compile Flags
  target_compile_options(${project_name} PRIVATE
    $<$<AND:${SC_MSVC},${SC_RELEASE}>: /Wall /Ox /GF /Gy /GS- /Ob2 /Oi /Ot>

    $<${SC_MSVC}: /wd4820 /wd4365 /wd4061 /wd4514 /wd5219 /wd4242 /wd4711 /wd4710 /wd4625 /wd4626 /wd5039 /wd5045 /wd5026 /wd5027 /wd4623 /wd4201> # Top 10 stupidest warnings

    $<$<OR:${SC_GNU},${SC_CLANG}>:-Wall -Wextra -Wpedantic -Wno-unused-variable -Wno-unknown-pragmas -Werror -Wno-gnu-anonymous-struct -Wno-nested-anon-types>
  )
  
  target_compile_features(${project_name}
    PRIVATE
    cxx_std_17
  )
endmacro()

sc_core_base_setup("SupercellCore")

set(CPPTRACE_STATIC_DEFINE TRUE)

FetchContent_Declare(
  cpptrace
  GIT_REPOSITORY "https://github.com/jeremy-rifkin/cpptrace.git"
  GIT_TAG 531a8c13d948ec883088bae4fb6c15dc4ffe0a74 # v0.5.2 with some fixes
)
FetchContent_MakeAvailable(cpptrace)

target_link_libraries("SupercellCore"
  cpptrace::cpptrace
)

set_target_properties("cpptrace-lib" PROPERTIES
  FOLDER Debug
)