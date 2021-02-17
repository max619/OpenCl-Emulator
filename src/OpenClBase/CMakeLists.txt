add_library(OpenClBase STATIC "ClPlatform.cpp" "ClPlatform.hpp" "OpenClBase.hpp" "OpenClBase.cpp" "ClPtr.hpp" "Exceptions.hpp" "Exceptions.cpp"  "Utils.hpp" "Utils.cpp")

target_precompile_headers(OpenClBase PUBLIC "OpenClBase.hpp")

target_compile_definitions(OpenClBase PUBLIC CL_TARGET_OPENCL_VERSION=${CL_TARGET_VERSION})
target_link_libraries(OpenClBase PUBLIC OpenCLHeaders)
target_include_directories(OpenClBase PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})