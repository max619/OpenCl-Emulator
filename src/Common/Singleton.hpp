#pragma once

namespace Common
{

template <class T> class Singleton
{
  public:
    static T &getInstance();
};

template <class T> inline T &Singleton<T>::getInstance()
{
    static std::once_flag flag;
    static std::unique_ptr<T> instance = nullptr;

    std::call_once(flag, [&instance = instance] { instance = std::unique_ptr<T>(new T()); });

    return *instance;
}

} // namespace Common
