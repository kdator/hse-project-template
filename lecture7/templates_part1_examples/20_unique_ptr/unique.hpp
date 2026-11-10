#pragma once
#include <utility>

template <typename T>
struct DefaultDelete {
    void operator()(T* p) const { delete p; }
};

template <typename T>
struct DefaultDelete<T[]> {                          // частичная: массив
    void operator()(T* p) const { delete[] p; }
};

template <typename T, typename D = DefaultDelete<T>>
class UniquePtr {
public:
    explicit UniquePtr(T* p = nullptr, D d = D()) : ptr_(p), del_(d) {}
    ~UniquePtr() { if (ptr_) del_(ptr_); }

    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;
    UniquePtr(UniquePtr&& o) noexcept : ptr_(o.release()), del_(std::move(o.del_)) {}
    UniquePtr& operator=(UniquePtr&& o) noexcept { reset(o.release()); del_ = std::move(o.del_); return *this; }

    T& operator*() const  { return *ptr_; }
    T* operator->() const { return ptr_; }
    T* get() const        { return ptr_; }
    explicit operator bool() const { return ptr_ != nullptr; }

    T* release() { return std::exchange(ptr_, nullptr); }
    void reset(T* p = nullptr) { T* old = std::exchange(ptr_, p); if (old) del_(old); }

private:
    T* ptr_;
    D del_;
};

template <typename T, typename D>                    // частичная: массивы
class UniquePtr<T[], D> {
public:
    explicit UniquePtr(T* p = nullptr, D d = D()) : ptr_(p), del_(d) {}
    ~UniquePtr() { if (ptr_) del_(ptr_); }
    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;
    UniquePtr(UniquePtr&& o) noexcept : ptr_(std::exchange(o.ptr_, nullptr)), del_(std::move(o.del_)) {}

    T& operator[](std::size_t i) const { return ptr_[i]; }   // вместо * и ->
    T* get() const { return ptr_; }

private:
    T* ptr_;
    D del_;
};
