﻿

add_library(${OPENCL_EMULATOR_LIBRARY_NAME} SHARED "CL.cpp" "platform.cpp" "devices.cpp")

target_compile_definitions(${OPENCL_EMULATOR_LIBRARY_NAME} PRIVATE EXPORT)

target_compile_definitions(${OPENCL_EMULATOR_LIBRARY_NAME} PUBLIC CL_TARGET_OPENCL_VERSION=${CL_TARGET_VERSION})
target_link_libraries(${OPENCL_EMULATOR_LIBRARY_NAME} PRIVATE OpenClBase PUBLIC OpenCLHeaders)