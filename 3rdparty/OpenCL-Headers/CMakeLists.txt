add_library(OpenCLHeaders INTERFACE)

target_include_directories(OpenCLHeaders
  INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)