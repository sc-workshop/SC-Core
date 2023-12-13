
macro(set_global var_name var_value )
    set(${var_name} ${var_value}  CACHE INTERNAL "")
endmacro()

set_global(SC_GNU_fe "$<STREQUAL:${CMAKE_CXX_COMPILER_FRONTEND_VARIANT},GNU>")
set_global(SC_GNU_APPLE_fe "$<STREQUAL:${CMAKE_CXX_COMPILER_FRONTEND_VARIANT},AppleClang>")
set_global(SC_MSVC_fe "$<STREQUAL:${CMAKE_CXX_COMPILER_FRONTEND_VARIANT},MSVC>")

set_global(SC_GNU "$<OR:${SC_GNU_fe},${SC_GNU_APPLE_fe}>")
set_global(SC_MSVC "$<AND:${SC_MSVC_fe},$<CXX_COMPILER_ID:MSVC>>")
set_global(SC_DEBUG "$<CONFIG:Debug>")
set_global(SC_RELEASE "$<OR:$<CONFIG:Release>,$<CONFIG:RelWithDebInfo>,$<CONFIG:MinSizeRel>")

set_global(SC_X86_64 "$<CMAKE_SYSTEM_PROCESSOR:x86_64>")
set_global(SC_AARCH64 "$<CMAKE_SYSTEM_PROCESSOR:aarch64>")

set_global(SC_X64 "$<OR:${SC_X86_64},${SC_AARCH64}>")