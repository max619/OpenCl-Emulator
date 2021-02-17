add_executable(ApiTests "PlatformTests.cpp" "main.cpp")

add_custom_target(OpenCLEmuDllCopy
	COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_BINARY_DIR}/src/opencl/${OPENCL_EMULATOR_LIBRARY_NAME}.dll" "${CMAKE_BINARY_DIR}/src/ApiTests"
)


target_link_libraries(ApiTests Catch2::Catch2 ${OPENCL_EMULATOR_LIBRARY_NAME})
add_dependencies(ApiTests OpenCLEmuDllCopy)