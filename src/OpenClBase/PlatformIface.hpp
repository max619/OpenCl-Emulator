#pragma once

namespace CL
{

struct PlatformInfo
{
    std::string profile;
    std::string version;
    std::string name;
    std::string vendor;
    std::string extensions;
};

class PlatformIface
{
  public:
    virtual ~PlatformIface() = default;

    virtual cl_int getPlatformInfo(cl_platform_info param_name, size_t param_value_size, void *param_value,
                                   size_t *param_value_size_ret) const noexcept = 0;
};
} // namespace CL
