add_library(ApiRecording STATIC "ApiRecording.hpp" "ApiRecording.cpp"   "RecorderIface.hpp"  "ThreadedRecorder.hpp" "ThreadedRecorder.cpp" "ThreadedRecorderImpl.hpp" "ThreadedRecorderImpl.cpp")

target_precompile_headers(ApiRecording PUBLIC "ApiRecording.hpp")
target_include_directories(ApiRecording PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(ApiRecording PUBLIC Common)
target_link_libraries(ApiRecording PRIVATE atomic_queue)
