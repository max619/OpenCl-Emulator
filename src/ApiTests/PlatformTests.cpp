#include "CL/cl.h"
#include "catch2/catch.hpp"

TEST_CASE("Test clGetPlatformIDs invalid args", "[cl_platform]")
{
    REQUIRE(clGetPlatformIDs(0, nullptr, nullptr) == CL_INVALID_VALUE);
}

TEST_CASE("Test clGetPlatformIDs", "[cl_platform]")
{
    cl_uint numPlatforms = 0;

    REQUIRE(clGetPlatformIDs(0, nullptr, &numPlatforms) == CL_SUCCESS);
    REQUIRE(numPlatforms > 0);

    std::vector<cl_platform_id> platforms;
    platforms.resize(numPlatforms);

    REQUIRE(clGetPlatformIDs(numPlatforms, platforms.data(), nullptr) == CL_SUCCESS);

    for (const auto &platform : platforms)
    {
        REQUIRE(platform);
    }
}

void testPlatform(std::function<void(cl_platform_id)> &&functor)
{
    cl_uint numPlatforms = 0;

    REQUIRE(clGetPlatformIDs(0, nullptr, &numPlatforms) == CL_SUCCESS);
    REQUIRE(numPlatforms > 0);

    std::vector<cl_platform_id> platforms;
    platforms.resize(numPlatforms);

    REQUIRE(clGetPlatformIDs(numPlatforms, platforms.data(), nullptr) == CL_SUCCESS);

    for (const auto &platform : platforms)
    {
        REQUIRE(platform);

        functor(platform);
    }
}

TEST_CASE("Test clGetPlatformInfo invalid params", "[cl_platform]")
{
    testPlatform([](cl_platform_id platform) {
        REQUIRE(clGetPlatformInfo(nullptr, CL_PLATFORM_VENDOR, 0, nullptr, nullptr) == CL_INVALID_PLATFORM);
        REQUIRE(clGetPlatformInfo(platform, CL_PLATFORM_VENDOR, 0, nullptr, nullptr) == CL_INVALID_VALUE);

        std::vector<char> data;
        data.resize(1024);
        REQUIRE(clGetPlatformInfo(platform, CL_DEVICE_ADDRESS_BITS, data.size(), data.data(), nullptr) ==
                CL_INVALID_VALUE);
    });
}

TEST_CASE("Test clGetPlatformInfo", "[cl_platform]")
{
    testPlatform([](cl_platform_id platform) {
        std::vector<char> data;
        data.resize(1024);
        size_t size = 0;

        REQUIRE(clGetPlatformInfo(platform, CL_PLATFORM_PROFILE, data.size(), data.data(), &size) == CL_SUCCESS);
        std::string str(data.data(), size);

        REQUIRE(str == "FULL_PROFILE");

        REQUIRE(clGetPlatformInfo(platform, CL_PLATFORM_VERSION, data.size(), data.data(), &size) == CL_SUCCESS);

        str = std::string(data.data(), size);
        REQUIRE(str == "OpenCL 1.2 Emulator");

        REQUIRE(clGetPlatformInfo(platform, CL_PLATFORM_NAME, data.size(), data.data(), &size) == CL_SUCCESS);

        str = std::string(data.data(), size);
        REQUIRE(str == "Emulator");

        REQUIRE(clGetPlatformInfo(platform, CL_PLATFORM_VENDOR, data.size(), data.data(), &size) == CL_SUCCESS);

        str = std::string(data.data(), size);
        REQUIRE(str == "Vendor");

        REQUIRE(clGetPlatformInfo(platform, CL_PLATFORM_EXTENSIONS, data.size(), data.data(), &size) == CL_SUCCESS);

        str = std::string(data.data(), size);
        REQUIRE(str == "");
    });
}
