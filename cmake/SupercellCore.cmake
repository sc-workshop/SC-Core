include(cmake/constants.cmake)

# Base Prepare
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# Core Files
set(Core_Sources
  "source/generic/image/image.cpp"
  "source/generic/image/raw_image.cpp"

  "source/memory/Allocator/STL/MemoryPool.cpp"

  "source/stb/stb.cpp"
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
)

add_library("SupercellCore" STATIC ${Core_Sources} ${Core_Headers})
source_group(TREE ${CMAKE_SOURCE_DIR} FILES ${Core_Sources} ${Core_Headers})

function(sc_core_base_setup project_name)

  target_compile_options(${project_name} PRIVATE
    $<${SC_MSVC}:/W4 /WX>

    $<${SC_GNU}:-Wall -Wextra -Wpedantic -Werror>
  )

  add_compile_definitions(
    $<${SC_MSVC}:SC_MSVC>
    $<${SC_DEBUG}:SC_DEBUG>
  )

  target_compile_features(${project_name}
    PRIVATE
    cxx_std_17
  )

  target_include_directories(${project_name}
    PUBLIC
    "include/"
  )

endfunction()

sc_core_base_setup("SupercellCore")

# # TODO: Test this all on Linux