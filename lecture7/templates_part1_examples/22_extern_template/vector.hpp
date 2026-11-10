#pragma once
#include <algorithm>
#include <cstddef>
#include <memory>
#include <utility>

template <typename T>
class Vector {
public:
    using value_type = T;                       // имена, которые ждёт STL
    using size_type  = std::size_t;
    using iterator   = T*;
    using const_iterator = const T*;

    Vector() = default;
    Vector(const Vector& o) : data_(new T[o.cap_]), size_(o.size_), cap_(o.cap_) {
        std::copy(o.begin(), o.end(), data_.get());
    }
    Vector(Vector&&) noexcept = default;
    Vector& operator=(Vector o) noexcept {      // copy-and-swap
        swap(o);
        return *this;
    }

    void push_back(const T& v) { grow_if_full(); data_[size_++] = v; }
    void push_back(T&& v)      { grow_if_full(); data_[size_++] = std::move(v); }

    T&       operator[](size_type i)       { return data_[i]; }
    const T& operator[](size_type i) const { return data_[i]; }
    size_type size() const     { return size_; }
    size_type capacity() const { return cap_; }

    iterator begin()             { return data_.get(); }
    iterator end()               { return data_.get() + size_; }
    const_iterator begin() const { return data_.get(); }
    const_iterator end()   const { return data_.get() + size_; }

    void swap(Vector& o) noexcept {
        std::swap(data_, o.data_); std::swap(size_, o.size_); std::swap(cap_, o.cap_);
    }

private:
    void grow_if_full() {
        if (size_ < cap_) return;
        size_type newCap = cap_ ? cap_ * 2 : 1;
        std::unique_ptr<T[]> fresh(new T[newCap]);
        std::move(begin(), end(), fresh.get());
        data_ = std::move(fresh);
        cap_ = newCap;
    }

    std::unique_ptr<T[]> data_;
    size_type size_ = 0;
    size_type cap_ = 0;
};
