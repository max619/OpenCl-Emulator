#include "ClPlatform.hpp"

namespace CL {

Platform::Platform(const PlatformInfo& info)
  : info(info)
{}

const PlatformInfo&
Platform::getInfo() const
{
  return info;
}

std::vector<Ptr<Platform>>&
Platform::getPlatforms()
{
  static std::vector<Ptr<Platform>> platforms = { makePtr<Platform>(
    PlatformInfo{
      "FULL_PROFILE", "OpenCL 1.2 Emulator", "Emulator", "Vendor", "" }) };

  return platforms;
}
}
