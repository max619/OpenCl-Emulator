add_library(Common STATIC "Common.hpp" "Common.cpp" "Singleton.hpp"  )

target_precompile_headers(Common PUBLIC "Common.hpp")
target_include_directories(Common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})