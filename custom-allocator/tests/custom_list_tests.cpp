#include <gtest/gtest.h>

#include <vector>

#include "custom_list.h"
#include "custom_allocator.h"

TEST(custom_list, basic_test) {
    CustomList<int> c_list;

    constexpr int N = 10;

    for (int i = 0; i < N; i++) {
        c_list.push(i);
    }

    std::vector<int> c_list_elems;
    std::copy(c_list.begin(), c_list.end(), std::back_inserter(c_list_elems));

    const std::vector<int> expected_c_list_elems{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    ASSERT_EQ(c_list_elems, expected_c_list_elems);

    ASSERT_EQ(c_list.front(), 0);
    ASSERT_EQ(c_list.back(), N - 1);
}

TEST(custom_list, custom_allocator) {
    constexpr int N = 10;

    CustomList<int, CustomAllocator<int, N>> c_list;

    for (int i = 0; i < N; i++) {
        c_list.push(i);
    }

    std::vector<int> c_list_elems;
    std::copy(c_list.begin(), c_list.end(), std::back_inserter(c_list_elems));

    const std::vector<int> expected_c_list_elems{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    ASSERT_EQ(c_list_elems, expected_c_list_elems);

    ASSERT_EQ(c_list.front(), 0);
    ASSERT_EQ(c_list.back(), N - 1);
}

TEST(custom_list, constructor_destructor) {
    static int create_count{0};
    static int destroy_count{0};

    class Dummy {
     public:
        Dummy() {
            create();
        }

        ~Dummy() {
            destroy();
        }

        void create() {
            create_count++;
        }

        void destroy() {
            destroy_count++;
        }

        static void resetCount() {
            create_count = 0;
            destroy_count = 0;
        }
    };

    constexpr int N{10};

    // standard allocator
    {
        CustomList<Dummy> list;

        for (int i = 0; i < N; i++) {
            list.emplace(Dummy{});
        }
    }

    ASSERT_EQ(create_count, N);
    ASSERT_EQ(destroy_count, N + N);

    Dummy::resetCount();

    // custom allocator
    {
        CustomList<Dummy, CustomAllocator<Dummy, N>> list;

        for (int i = 0; i < N; i++) {
            Dummy d;

            list.emplace(std::move(d));
        }
    }

    ASSERT_EQ(create_count, N);
    ASSERT_EQ(destroy_count, N + N);
}
