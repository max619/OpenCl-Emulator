#pragma once

namespace ApiRecording
{

class ThreadedRecorderImpl;

class ThreadedRecorder : public RecorderIface
{
  public:
    ThreadedRecorder();
    virtual ~ThreadedRecorder() override = default;

    // Inherited via RecorderIface
    virtual void appendCallTrace(const CallTrace &trace) override;
    virtual void appendCallTrace(CallTrace &&trace) override;

  protected:
    virtual void writeCallTrace(const CallTrace &trace) = 0;

    friend class ThreadedRecorderImpl;

  private:
    std::unique_ptr<ThreadedRecorderImpl> impl;
};

} // namespace ApiRecording
