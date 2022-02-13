#include <gtest/gtest.h>

#include <list>
#include <map>

#include "custom_allocator.h"
#include "custom_list.h"

TEST(custom_allocator, list) {
    constexpr int N = 5;
    std::list<int, CustomAllocator<int, N>> v;

    for (int i = 0; i < N; ++i) {
        v.push_back(i);
    }

    ASSERT_EQ(v.size(), N);

    try {
        v.push_back(N);
    } catch(std::exception& ex) {
        const std::string kBadAlloc = "std::bad_alloc";
        ASSERT_EQ(ex.what(), kBadAlloc);
    }
}

TEST(custom_allocator, map) {
    constexpr int N = 10;
    std::map<int,
             int,
             std::less<>,
             CustomAllocator<std::pair<const int, int>, N>> mp;

    for (int i = 0; i < N; ++i) {
        mp.insert({i, i + 1});
    }

    ASSERT_EQ(mp.size(), N);

    try {
        mp.insert({N, N + 1});
    } catch(std::exception& ex) {
        const std::string kBadAlloc = "std::bad_alloc";
        ASSERT_EQ(ex.what(), kBadAlloc);
    }
}

TEST(custom_allocator, custom_value) {
    constexpr int N = 10;

    struct Item {
        std::string s{"string"};
        int i{5};
        std::vector<int> v{1, 2, 4};
    };

    std::map<int,
             Item,
             std::less<>,
             CustomAllocator<std::pair<const int, Item>, N>> mp;

    for (int i = 0; i < N; ++i) {
        mp.insert({i, Item()});
    }

    ASSERT_EQ(mp.size(), N);

    try {
        mp.insert({N, Item()});
    } catch(std::exception& ex) {
        const std::string kBadAlloc = "std::bad_alloc";
        ASSERT_EQ(ex.what(), kBadAlloc);
    }
}
