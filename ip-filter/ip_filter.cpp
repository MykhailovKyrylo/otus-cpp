#include <iostream>

#include "ip_parser.h"

int main(int /*argc*/, char** /*argv*/) {
    std::vector<IP> ips;

    if (auto result = GetIPsFromStream(std::cin); result.has_value()) {
        ips = std::move(result.value());
    } else {
        std::cerr << "Input is invalid" << std::endl;
        return -1;
    }

    std::sort(ips.begin(), ips.end(), [] (const IP& lhs, const IP& rhs) {
        return lhs.bytes > rhs.bytes;
    });

    auto print = [] (const std::vector<IP>& ips) {
        for (const auto& ip : ips) {
            std::cout << ip << '\n';
        }
    };

    print(ips);

    {  // filter by first byte == 1
        std::vector<IP> filtered_ips;

        auto filter = [] (const IP& ip) {
            return ip.bytes[0] == 1;
        };

        std::copy_if(filtered_ips.begin(), filtered_ips.end(), std::back_inserter(filtered_ips), filter);

        print(filtered_ips);
    }

    {  // filter by first byte == 46, second byte == 70
        std::vector<IP> filtered_ips;

        auto filter = [] (const IP& ip) {
            return ip.bytes[0] == 46 && ip.bytes[1] == 70;
        };

        std::copy_if(filtered_ips.begin(), filtered_ips.end(), std::back_inserter(filtered_ips), filter);

        print(filtered_ips);
    }

    {  // filter by any byte == 46
        std::vector<IP> filtered_ips;

        auto filter = [] (const IP& ip) {
            return std::any_of(ip.bytes.begin(), ip.bytes.end(), [] (uint8_t byte) { return byte == 46; });
        };

        std::copy_if(filtered_ips.begin(), filtered_ips.end(), std::back_inserter(filtered_ips), filter);

        print(filtered_ips);
    }

    return 0;
}
