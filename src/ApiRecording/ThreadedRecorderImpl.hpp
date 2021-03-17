#pragma once

#include "ApiRecording.hpp"

#pragma warning(push)
#pragma warning(disable : 4324)
#pragma warning(disable : 4127)

#include "atomic_queue.h"

#pragma warning(pop)

namespace ApiRecording
{
constexpr unsigned numMaxQueueSize = 1024;
using Queue = atomic_queue::AtomicQueue<CallTrace *, numMaxQueueSize>;

#pragma warning(push)
#pragma warning(disable : 4316)
class ThreadedRecorderImpl
{
  public:
    ThreadedRecorderImpl(ThreadedRecorder *base);
    ~ThreadedRecorderImpl();

    // Inherited via RecorderIface
    void appendCallTrace(const CallTrace &trace);
    void appendCallTrace(CallTrace &&trace);

    void stop();

  private:
    void writeCallTraceInternal(CallTrace *trace);
    void appendCallTraceInternal(CallTrace *trace);
    static void runThread(ThreadedRecorderImpl *selfPtr);

    ThreadedRecorder *basePtr = nullptr;

    Queue queue;
    std::thread thread;

    std::atomic_bool isStopped{false};
    std::condition_variable condVariable;

    static constexpr std::chrono::microseconds numSleepFor = std::chrono::microseconds(1);
    static constexpr std::chrono::seconds numSpinFor = std::chrono::seconds(2);
    static constexpr std::chrono::seconds numWaitTimeout = std::chrono::seconds(5);
};
#pragma warning(pop)

} // namespace ApiRecording
