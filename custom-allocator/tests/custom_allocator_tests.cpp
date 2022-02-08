#include <gtest/gtest.h>

#include <list>

#include "custom_allocator.h"

TEST(custom_allocator, list) {
    constexpr int N = 3;
    std::list<int, CustomAllocator<int, N>> v;
    ASSERT_TRUE(v.empty());
    ASSERT_EQ(v.size(), 0);
    for (int i = 0; i < N; ++i) {
        v.push_back(i);
    }
    ASSERT_FALSE(v.empty());
    ASSERT_EQ(v.size(), N);
    try {
        v.push_back(N);
    } catch(std::exception& ex) {
        const std::string kBadAlloc = "std::bad_alloc";
        ASSERT_EQ(ex.what(), kBadAlloc);
    }
}
