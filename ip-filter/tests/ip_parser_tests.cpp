#include <gtest/gtest.h>

#include "ip_parser.h"

TEST(GetIPFromString, basic_test) {
    auto result = GetIPFromString("1.2.3.4");

    ASSERT_TRUE(result.has_value());

    const std::vector<uint8_t> expected_bytes{1, 2, 3, 4};
    ASSERT_EQ(result.value().bytes, expected_bytes);
}

TEST(GetIPFromString, not_enough_bytes) {
    auto result = GetIPFromString("1.2.3");

    ASSERT_FALSE(result.has_value());
}

TEST(GetIPFromString, numbers_out_of_bounds) {
    auto result = GetIPFromString("256.256.256.256");

    ASSERT_FALSE(result.has_value());
}

TEST(GetIPFromString, negative_numbers) {
    auto result = GetIPFromString("1.2.3.-1");

    ASSERT_FALSE(result.has_value());
}

TEST(GetIPFromString, totally_invalid) {
    auto result = GetIPFromString("1.2.3..");

    ASSERT_FALSE(result.has_value());
}

TEST(GetIPsFromStream, basic_test) {
    std::istringstream is("1.2.3.4 \t5.6.7.8 \t9.10.11.12\n");
    auto result = GetIPsFromStream(is);

    ASSERT_TRUE(result.has_value());

    const std::vector<IP>& ips = result.value();
    ASSERT_EQ(ips.size(), 1);

    const std::vector<uint8_t> expected_bytes{1, 2, 3, 4};
    ASSERT_EQ(ips[0].bytes, expected_bytes);
}

TEST(GetIPsFromStream, multiline_test) {
    std::istringstream is("1.2.3.4 \t5.6.7.8 \t9.10.11.12\n"
                          "13.14.15.16 \t17.18.19.20 \t21.22.23.24\n");
    auto result = GetIPsFromStream(is);

    ASSERT_TRUE(result.has_value());

    const std::vector<IP>& ips = result.value();
    ASSERT_EQ(result.value().size(), 2);

    const std::vector<std::vector<uint8_t>> expected_bytes {
        {1, 2, 3, 4},
        {13, 14, 15, 16}
    };

    std::vector<std::vector<uint8_t>> actual_bytes;
    std::transform(ips.begin(),
                   ips.end(),
                   std::back_inserter(actual_bytes),
                   [] (const IP& ip) { return ip.bytes; });

    std::equal(actual_bytes.begin(), actual_bytes.end(), expected_bytes.begin());
}

TEST(GetIPsFromStream, multiline_test_with_first_valid_api) {
    std::istringstream is("1.2.3.4 \t5 \t6\n"
                          "7.8.9.10 \t11 \t12\n");
    auto result = GetIPsFromStream(is);

    ASSERT_TRUE(result.has_value());

    const std::vector<IP>& ips = result.value();
    ASSERT_EQ(result.value().size(), 2);

    const std::vector<std::vector<uint8_t>> expected_bytes {
        {1, 2, 3, 4},
        {7, 8, 9, 10}
    };

    std::vector<std::vector<uint8_t>> actual_bytes;
    std::transform(ips.begin(),
                   ips.end(),
                   std::back_inserter(actual_bytes),
                   [] (const IP& ip) { return ip.bytes; });

    std::equal(actual_bytes.begin(), actual_bytes.end(), expected_bytes.begin());
}
