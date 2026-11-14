#pragma once

#include <cstddef>
#include <memory>
#include <numeric>
#include <string>
#include <utility>
#include <vector>

template <typename T>
struct ValueOf {
    static std::string get(const T& item) { return item.myValue(); }
};

template <typename T>
struct ValueOf<T*> {
    static std::string get(const T* item) { return item->myValue(); }
};

template <typename T>
struct ValueOf<std::unique_ptr<T>> {
    static std::string get(const std::unique_ptr<T>& item) { return item->myValue(); }
};

template <typename T>
class Collection {
public:
    using value_type     = T;
    using iterator       = typename std::vector<T>::iterator;
    using const_iterator = typename std::vector<T>::const_iterator;

    void add(T item) { items_.push_back(std::move(item)); }

    iterator begin()             { return items_.begin(); }
    iterator end()               { return items_.end(); }
    const_iterator begin() const { return items_.begin(); }
    const_iterator end()   const { return items_.end(); }
    std::size_t size() const     { return items_.size(); }

private:
    std::vector<T> items_;
};

template <typename T>
std::string joinValues(const Collection<T>& c, const std::string& sep = " ") {
    return std::accumulate(c.begin(), c.end(), std::string{},
        [&sep](std::string acc, const T& item) {
            if (!acc.empty()) acc += sep;
            return acc + ValueOf<T>::get(item);
        });
}
