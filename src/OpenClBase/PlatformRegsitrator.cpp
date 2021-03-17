#include "OpenClBase.hpp"

namespace CL
{

PlatformRegistrator::PlatformRegistrator()
{
    init({true, true, PlatformInfo{"FULL_PROFILE", "OpenCL 1.2 Emulator", "Emulator", "Vendor", ""}});
}

std::shared_ptr<PlatformIface> PlatformRegistrator::findPlatform(cl_platform_id id) const
{
    std::shared_lock<std::shared_mutex> lock(mutex);

    auto it = platforms.find(id);
    if (it != platforms.end())
    {
        return it->second;
    }

    return std::shared_ptr<PlatformIface>();
}

std::vector<cl_platform_id> PlatformRegistrator::getPlatformIds() const
{
    std::shared_lock<std::shared_mutex> lock(mutex);

    std::vector<cl_platform_id> result;
    result.reserve(platforms.size());

    for (const auto &[id, value] : platforms)
    {
        result.push_back(id);
    }

    return result;
}

void PlatformRegistrator::init(const PlatformRegistratorSettings &settings)
{
    if (isInitialzed)
        return;

    std::unique_lock<std::shared_mutex> lock(mutex);

    if (isInitialzed)
        return;

    try
    {
        if (settings.createEmulatorPlatform)
        {
            auto emulatorPlatform = createEmulatorPlatform(settings.emulatorPlatformInfo);
            platforms.emplace(reinterpret_cast<cl_platform_id>(emulatorPlatform.get()), emulatorPlatform);
        }

        isInitialzed = true;
    }
    catch (...)
    {
        platforms.clear();
        throw;
    }
}

std::shared_ptr<PlatformIface> PlatformRegistrator::createEmulatorPlatform(const PlatformInfo &info)
{
    return std::make_shared<EmulatorPlatform>(info);
}

} // namespace CL
