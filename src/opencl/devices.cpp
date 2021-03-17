#include "OpenClBase.hpp"

using namespace CL;
#pragma warning(push)
#pragma warning(disable : 4100)

/* Device APIs */
CL_EXPORT CL_API_ENTRY cl_int CL_API_CALL clGetDeviceIDs(cl_platform_id platform, cl_device_type device_type,
                                                         cl_uint num_entries, cl_device_id *devices,
                                                         cl_uint *num_devices) CL_API_SUFFIX__VERSION_1_0
{
    std::shared_ptr<PlatformIface> platformPtr = PlatformRegistrator::getInstance().findPlatform(platform);

    if (!platformPtr)
    {
        return CL_INVALID_PLATFORM;
    }

    return CL_SUCCESS;
}

CL_EXPORT CL_API_ENTRY cl_int CL_API_CALL clGetDeviceInfo(cl_device_id device, cl_device_info param_name,
                                                          size_t param_value_size, void *param_value,
                                                          size_t *param_value_size_ret) CL_API_SUFFIX__VERSION_1_0
{
    return CL_INVALID_VALUE;
}

#ifdef CL_VERSION_1_2

CL_EXPORT CL_API_ENTRY cl_int CL_API_CALL clCreateSubDevices(cl_device_id in_device,
                                                             const cl_device_partition_property *properties,
                                                             cl_uint num_devices, cl_device_id *out_devices,
                                                             cl_uint *num_devices_ret) CL_API_SUFFIX__VERSION_1_2
{
    return CL_INVALID_VALUE;
}

CL_EXPORT CL_API_ENTRY cl_int CL_API_CALL clRetainDevice(cl_device_id device) CL_API_SUFFIX__VERSION_1_2
{
    return CL_INVALID_VALUE;
}

CL_EXPORT CL_API_ENTRY cl_int CL_API_CALL clReleaseDevice(cl_device_id device) CL_API_SUFFIX__VERSION_1_2
{
    return CL_INVALID_VALUE;
}

#endif

#ifdef CL_VERSION_2_1

CL_EXPORT CL_API_ENTRY cl_int CL_API_CALL clSetDefaultDeviceCommandQueue(
    cl_context context, cl_device_id device, cl_command_queue command_queue) CL_API_SUFFIX__VERSION_2_1
{
    return CL_INVALID_VALUE;
}

CL_EXPORT CL_API_ENTRY cl_int CL_API_CALL clGetDeviceAndHostTimer(cl_device_id device, cl_ulong *device_timestamp,
                                                                  cl_ulong *host_timestamp) CL_API_SUFFIX__VERSION_2_1
{
    return CL_INVALID_VALUE;
}

CL_EXPORT CL_API_ENTRY cl_int CL_API_CALL clGetHostTimer(cl_device_id device,
                                                         cl_ulong *host_timestamp) CL_API_SUFFIX__VERSION_2_1
{
    return CL_INVALID_VALUE;
}

#endif

#pragma warning(pop)
