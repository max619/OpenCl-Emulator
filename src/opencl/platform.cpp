#include "OpenClBase.hpp"

using namespace CL;

/* Platform API */
CL_EXPORT CL_API_ENTRY cl_int CL_API_CALL clGetPlatformIDs(cl_uint num_entries, cl_platform_id *platforms,
                                                           cl_uint *num_platforms) CL_API_SUFFIX__VERSION_1_0
{
    if (platforms && !num_entries || !platforms && !num_platforms)
    {
        return CL_INVALID_VALUE;
    }

    std::vector<cl_platform_id> platformsPtrs = PlatformRegistrator::getInstance().getPlatformIds();

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
            platforms[i] = platformsPtrs[i];
        }
    }

    return CL_SUCCESS;
}

CL_EXPORT CL_API_ENTRY cl_int CL_API_CALL clGetPlatformInfo(cl_platform_id platformId, cl_platform_info param_name,
                                                            size_t param_value_size, void *param_value,
                                                            size_t *param_value_size_ret) CL_API_SUFFIX__VERSION_1_0
{
    std::shared_ptr<PlatformIface> platform = PlatformRegistrator::getInstance().findPlatform(platformId);

    if (!platform)
    {
        return CL_INVALID_PLATFORM;
    }

    return platform->getPlatformInfo(param_name, param_value_size, param_value, param_value_size_ret);
}
