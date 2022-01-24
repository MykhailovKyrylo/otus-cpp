#include <iostream>
#include <fstream>

#include "ip_parser.h"

int Solution(std::istream& in = std::cin, std::ostream& out = std::cout) {
    std::vector<IP> ips;

    if (auto result = GetIPsFromStream(in); result.has_value()) {
        ips = std::move(result.value());
    } else {
        out << "Input is invalid" << std::endl;
        return -1;
    }

    std::sort(ips.begin(), ips.end(), [] (const IP& lhs, const IP& rhs) {
        return lhs.bytes > rhs.bytes;
    });

    auto print = [&out] (const std::vector<IP>& ips) {
        for (const auto& ip : ips) {
            out << ip << '\n';
        }
    };

    print(ips);

    {  // filter by first byte == 1
        std::vector<IP> filtered_ips;

        auto filter = [] (const IP& ip) {
            return ip.bytes[0] == 1;
        };

        std::copy_if(ips.begin(), ips.end(), std::back_inserter(filtered_ips), filter);

        print(filtered_ips);
    }

    {  // filter by first byte == 46, second byte == 70
        std::vector<IP> filtered_ips;

        auto filter = [] (const IP& ip) {
            return ip.bytes[0] == 46 && ip.bytes[1] == 70;
        };

        std::copy_if(ips.begin(), ips.end(), std::back_inserter(filtered_ips), filter);

        print(filtered_ips);
    }

    {  // filter by any byte == 46
        std::vector<IP> filtered_ips;

        auto filter = [] (const IP& ip) {
            return std::any_of(ip.bytes.begin(), ip.bytes.end(), [] (uint8_t byte) { return byte == 46; });
        };

        std::copy_if(ips.begin(), ips.end(), std::back_inserter(filtered_ips), filter);

        print(filtered_ips);
    }

    return 0;
}

int main(int /*argc*/, char** /*argv*/) {
    return Solution();
}
