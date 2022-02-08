#include <iostream>
#include <map>

#include "custom_allocator.h"

template <typename Key, typename Value, typename Allocator>
void foo() {
    std::map<Key, Value, std::less<>, Allocator> mp{};

    constexpr int N{10};
    for (int i = 0, f = 1; i < N; i++, f *= i) {
        mp.insert({i, f});
    }

    for (auto [key, value] : mp) {
        std::cout << '{' << key << ", " << value << "} ";
    }
    std::cout << std::endl;
}

int main(int /*argc*/, char** /*argv*/) {
    // map with default allocator
    foo<int, int, std::allocator<std::pair<const int, int>>>();

    // map with custom allocator
    foo<int, int, CustomAllocator<std::pair<const int, int>, 10>>();

    return 0;
}
