#pragma once

#include <vector>
#include <cstdint>
#include <algorithm>
#include <string>

struct IP {
    explicit IP(std::vector<uint8_t>&& bytes);

    static constexpr size_t kIPSize{4u};

    std::vector<uint8_t> bytes;
};

std::ostream& operator<<(std::ostream& out, const IP& ip);
