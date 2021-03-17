add_subdirectory(OpenCL-Headers)
add_subdirectory(Catch2)

add_library(atomic_queue INTERFACE)

target_include_directories(atomic_queue
  INTERFACE
  "${CMAKE_CURRENT_SOURCE_DIR}/atomic_queue/include/atomic_queue"
)