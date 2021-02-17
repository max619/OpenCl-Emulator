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

	class Platform
	{
	public:
		Platform(const PlatformInfo& info);

		const PlatformInfo& getInfo() const;

		static std::vector<Ptr<Platform>>& getPlatforms();
	private:
		PlatformInfo info;
	};
}
