#include <iostream>
#include <map>

#include "custom_allocator.h"
#include "custom_list.h"

constexpr int N{10};

template <typename Key, typename Value, typename Allocator>
void fill_map() {
    std::map<Key, Value, std::less<>, Allocator> mp{};

    for (int i = 0, f = 1; i < N; i++, f *= i) {
        mp.insert({i, f});
    }

    for (auto [key, value] : mp) {
        std::cout << '{' << key << ", " << value << "} ";
    }
    std::cout << std::endl;
}

template <typename Allocator>
void fill_custom_list() {
    CustomList<int, Allocator> list;
    for (int i = 0; i < N; i++) {
        list.push(i);
    }

    for (auto value : list) {
        std::cout << value << ' ';
    }

    std::cout << std::endl;
}

int main(int /*argc*/, char** /*argv*/) {
    // map with default allocator
    fill_map<int, int, std::allocator<std::pair<const int, int>>>();

    // map with custom allocator
    fill_map<int, int, CustomAllocator<std::pair<const int, int>, N>>();

    // custom container
    fill_custom_list<std::allocator<int>>();

    // custom container
    fill_custom_list<CustomAllocator<int, N>>();

    return 0;
}
