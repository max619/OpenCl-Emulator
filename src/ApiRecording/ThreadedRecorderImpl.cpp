#include "ThreadedRecorderImpl.hpp"

namespace ApiRecording
{

ThreadedRecorderImpl::ThreadedRecorderImpl(ThreadedRecorder *base) : basePtr(base)
{
    thread = std::thread(runThread, this);
}

ThreadedRecorderImpl::~ThreadedRecorderImpl()
{
    stop();
}

void ThreadedRecorderImpl::appendCallTrace(const CallTrace &trace)
{
    appendCallTraceInternal(new CallTrace(trace));
}

void ThreadedRecorderImpl::appendCallTrace(CallTrace &&trace)
{
    appendCallTraceInternal(new CallTrace(std::move(trace)));
}

void ThreadedRecorderImpl::stop()
{
    isStopped = true;
    thread.join();
}

void ThreadedRecorderImpl::writeCallTraceInternal(CallTrace *trace)
{
    basePtr->writeCallTrace(*trace);
    delete trace;
}

void ThreadedRecorderImpl::appendCallTraceInternal(CallTrace *trace)
{
    queue.push(trace);
    condVariable.notify_one();
}

void ThreadedRecorderImpl::runThread(ThreadedRecorderImpl *selfPtr)
{
    std::mutex mutex;
    std::unique_lock<std::mutex> lock;

    CallTrace *trace = nullptr;

    while (!selfPtr->isStopped)
    {
        auto startWait = std::chrono::steady_clock::now();

        bool isPoppedSuccesfull = false;

        for (;
             !selfPtr->isStopped && !isPoppedSuccesfull && (startWait - std::chrono::steady_clock::now()) < numSpinFor;
             isPoppedSuccesfull = selfPtr->queue.try_pop(trace))
        {
            std::this_thread::sleep_for(numSleepFor);
        }

        for (; !selfPtr->isStopped && !isPoppedSuccesfull; isPoppedSuccesfull = selfPtr->queue.try_pop(trace))
        {
            selfPtr->condVariable.wait_for(lock, numWaitTimeout);
        }

        if (isPoppedSuccesfull)
        {
            selfPtr->writeCallTraceInternal(trace);
        }
    }

    // write all messages in queue

    while (selfPtr->queue.try_pop(trace))
    {
        selfPtr->writeCallTraceInternal(trace);
    }
}

} // namespace ApiRecording
