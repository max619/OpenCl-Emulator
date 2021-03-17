#include "ApiRecording.hpp"
#include "ThreadedRecorderImpl.hpp"

namespace ApiRecording
{

ThreadedRecorder::ThreadedRecorder()
{
    impl = std::make_unique<ThreadedRecorderImpl>(this);
}

void ThreadedRecorder::appendCallTrace(const CallTrace &trace)
{
    impl->appendCallTrace(trace);
}

void ThreadedRecorder::appendCallTrace(CallTrace &&trace)
{
    impl->appendCallTrace(std::move(trace));
}

} // namespace ApiRecording
