#include "OpenClBase.hpp"

namespace CL
{

EmulatorPlatform::EmulatorPlatform(const PlatformInfo &info) : info(info)
{
}

const PlatformInfo &EmulatorPlatform::getInfo() const
{
    return info;
}

cl_int EmulatorPlatform::getPlatformInfo(cl_platform_info param_name, size_t param_value_size, void *param_value,
                                         size_t *param_value_size_ret) const noexcept
{
    switch (param_name)
    {
    case CL_PLATFORM_PROFILE:
        return Utils::storeString(info.profile, param_value_size, param_value, param_value_size_ret);
    case CL_PLATFORM_VERSION:
        return Utils::storeString(info.version, param_value_size, param_value, param_value_size_ret);
    case CL_PLATFORM_NAME:
        return Utils::storeString(info.name, param_value_size, param_value, param_value_size_ret);
    case CL_PLATFORM_VENDOR:
        return Utils::storeString(info.vendor, param_value_size, param_value, param_value_size_ret);
    case CL_PLATFORM_EXTENSIONS:
        return Utils::storeString(info.extensions, param_value_size, param_value, param_value_size_ret);
    default:
        return CL_INVALID_VALUE;
    }
}

} // namespace CL
