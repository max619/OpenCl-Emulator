#pragma once

namespace CL
{

struct PtrRef
{
    PtrRef(void *thePtr) : ptr(thePtr), weakRefs(1)
    {
    }

    std::atomic<void *> ptr = nullptr;
    std::atomic<uint32_t> weakRefs = 0;
};

template <typename T> class Ptr
{
  public:
    Ptr(T *ptr, std::function<void(T *)> &&deleter);
    Ptr(const Ptr<T> &another);
    Ptr(Ptr<T> &&another);

    ~Ptr();

    Ptr<T> &operator=(const Ptr<T> &another);
    Ptr<T> &operator=(Ptr<T> &&another);

    bool isAlive() const;
    void release();
    uint32_t getRefsCount() const;

    T *operator->() const;

  private:
    std::function<void(T *)> deleter;
    PtrRef *ref = nullptr;
};

template <typename T> using PtrPtr = Ptr<T> *;

template <typename T> void defaultDelete(T *ptr)
{
    delete ptr;
}

template <typename T, typename... Args> Ptr<T> makePtr(Args &&...args);

template <typename T>
inline Ptr<T>::Ptr(T *ptr, std::function<void(T *)> &&deleter) : ref(new PtrRef(ptr)), deleter(deleter)
{
}

template <typename T> inline Ptr<T>::Ptr(const Ptr<T> &another)
{
    operator=(another);
}

template <typename T> inline Ptr<T>::Ptr(Ptr<T> &&another)
{
    operator=(std::move(another));
}

template <typename T> inline Ptr<T>::~Ptr()
{
    if (ref)
    {
        if (ref->weakRefs.fetch_sub(1) == 1)
        {
            release();
            delete ref;
        }
        ref = nullptr;
    }
}

template <typename T> inline Ptr<T> &Ptr<T>::operator=(const Ptr<T> &another)
{
    if (this == &another)
    {
        return *this;
    }

    deleter = another.deleter;
    ref = another.ref;

    ref->weakRefs.fetch_add(1);

    return *this;
}

template <typename T> inline Ptr<T> &Ptr<T>::operator=(Ptr<T> &&another)
{
    if (this == &another)
    {
        return *this;
    }

    release();

    deleter = std::move(another.deleter);

    std::swap(ref, another.ref);
}

template <typename T> inline bool Ptr<T>::isAlive() const
{
    return ref->ptr.load();
}

template <typename T> inline void Ptr<T>::release()
{
    T *ptr = (T *)ref->ptr.exchange(nullptr);

    if (ptr)
    {
        deleter(ptr);
    }
}

template <typename T> inline uint32_t Ptr<T>::getRefsCount() const
{
    return ref->weakRefs.load();
}

template <typename T> inline T *Ptr<T>::operator->() const
{
    T *ptr = (T *)ref->ptr.load();

    if (!ptr)
    {
        throw std::bad_weak_ptr();
    }

    return ptr;
}

template <typename T, typename... Args> inline Ptr<T> makePtr(Args &&...args)
{
    T *ptr = new T(std::forward<Args>(args)...);
    return Ptr<T>(ptr, defaultDelete<T>);
}

} // namespace CL
