#pragma once

#include <array>
#include <cstddef>
#include <utility>

/// \brief R - reverse memory size limit
/// \note throws bad_alloc on attempting to allocate more elements than reserved memory capacity allows
template <typename T, size_t R>
struct CustomAllocator {
    using value_type = T;

    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;

    template <typename U>
    struct rebind {
        using other = CustomAllocator<U, R>;
    };

    CustomAllocator() = default;
    ~CustomAllocator() = default;

    template <typename U>
    explicit CustomAllocator(const CustomAllocator<U, R>&) {}

    pointer allocate(std::size_t n) {
        if (n + allocated_count_ > R) {
            throw std::bad_alloc();
        }

        auto p = &storage_[allocated_count_ * sizeof(T)];

        allocated_count_ += n;
        return reinterpret_cast<T*>(p);
    }

    void deallocate(pointer, std::size_t) {}

    template <typename U, typename... Args>
    void construct(U* p, Args&&... args) {
        new (p) U(std::forward<Args>(args)...);
    }

    template <typename U>
    void destroy(U* p) {
        p->~U();
    }

    size_t allocated_count_{0u};
    std::byte storage_[R * sizeof(T)];
};
