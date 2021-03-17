#pragma once

namespace ApiRecording
{

class CallTraceParamIface;

struct CallTrace
{
    std::string functionName;
    std::vector<std::shared_ptr<CallTraceParamIface>> params;
    std::shared_ptr<CallTraceParamIface> returnValue;
};

class RecorderIface
{
  public:
    virtual ~RecorderIface() = default;

    virtual void appendCallTrace(const CallTrace &trace) = 0;
    virtual void appendCallTrace(CallTrace &&trace) = 0;
};

} // namespace ApiRecording
