#pragma once

#include <shared_mutex>

namespace CL
{

struct PlatformRegistratorSettings
{
    bool recordCalls = true;
    bool createEmulatorPlatform = true;
    PlatformInfo emulatorPlatformInfo;
};

class PlatformRegistrator : public Common::Singleton<PlatformRegistrator>
{
  public:
    PlatformRegistrator(const PlatformRegistrator &) = delete;
    PlatformRegistrator &operator=(const PlatformRegistrator &) = delete;

    std::shared_ptr<PlatformIface> findPlatform(cl_platform_id id) const;
    std::vector<cl_platform_id> getPlatformIds() const;

  protected:
    PlatformRegistrator();

    friend class Common::Singleton<PlatformRegistrator>;

  private:
    void init(const PlatformRegistratorSettings &settings);

    std::shared_ptr<PlatformIface> createEmulatorPlatform(const PlatformInfo &info);

    std::unordered_map<cl_platform_id, std::shared_ptr<PlatformIface>> platforms;
    mutable std::shared_mutex mutex;

    std::atomic<bool> isInitialzed{false};
};

} // namespace CL
