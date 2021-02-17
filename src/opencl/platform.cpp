#include "OpenClBase.hpp"

using namespace CL;

/* Platform API */
CL_EXPORT CL_API_ENTRY cl_int CL_API_CALL
clGetPlatformIDs(cl_uint num_entries, cl_platform_id* platforms,
    cl_uint* num_platforms) CL_API_SUFFIX__VERSION_1_0 {

    if (platforms && !num_entries || !platforms && !num_platforms)
    {
        return CL_INVALID_VALUE;
    }

    std::vector<Ptr<Platform>>& platformsPtrs = CL::Platform::getPlatforms();

    if (num_platforms)
    {
        *num_platforms = static_cast<cl_uint>(platformsPtrs.size());
    }

    if (platforms)
    {
        memset(platforms, 0, sizeof(cl_platform_id) * num_entries);
        
        cl_uint platformsToPass = std::min(static_cast<cl_uint>(platformsPtrs.size()), num_entries);

        for (cl_uint i = 0; i < platformsToPass; ++i)
        {
            platforms[i] = reinterpret_cast<cl_platform_id>(&platformsPtrs[i]);
        }
    }

    return CL_SUCCESS;
}

CL_EXPORT CL_API_ENTRY cl_int CL_API_CALL
clGetPlatformInfo(cl_platform_id platform, cl_platform_info param_name,
    size_t param_value_size, void* param_value,
    size_t* param_value_size_ret) CL_API_SUFFIX__VERSION_1_0 {
    
    if (!platform)
    {
        return CL_INVALID_PLATFORM;
    }

    const Ptr<Platform>& platformPtr = *reinterpret_cast<Ptr<Platform>*>(platform);

    if (!platformPtr.isAlive())
    {
        return CL_INVALID_PLATFORM;
    }

    const PlatformInfo& info = platformPtr->getInfo();

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
