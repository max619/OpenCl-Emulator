#pragma once

namespace CL
{

class EmulatorPlatform : public PlatformIface
{
  public:
    EmulatorPlatform(const PlatformInfo &info);

    const PlatformInfo &getInfo() const;
    virtual cl_int getPlatformInfo(cl_platform_info param_name, size_t param_value_size, void *param_value,
                                   size_t *param_value_size_ret) const noexcept override;

  private:
    PlatformInfo info;
};

} // namespace CL
