#include "ip_parser.h"

#include <sstream>
#include <limits>
#include <algorithm>
#include <utility>

#include "ip.h"

namespace {

class StringDelimitedByPoints : public std::string {};

    std::istream& operator>>(std::istream& is, StringDelimitedByPoints& output) {
        std::getline(is, output, '.');
        return is;
    }
}  // namespace

std::optional<IP> GetIPFromString(const std::string& ip_str) {
    std::istringstream iss(ip_str);
    std::vector<std::string> results((std::istream_iterator<StringDelimitedByPoints>(iss)),
                                      std::istream_iterator<StringDelimitedByPoints>());

    if (results.size() != IP::kIPSize) {
        return std::nullopt;
    }

    for (const auto& result : results) {
        if (result.empty()) {
            return std::nullopt;
        }

        if (std::any_of(result.begin(), result.end(), [] (char c) { return std::isdigit(c) == 0; })) {
            return std::nullopt;
        }

        const int number = std::stoi(result);
        if (number < std::numeric_limits<uint8_t>::min() || number > std::numeric_limits<uint8_t>::max()) {
            return std::nullopt;
        }
    }

    std::vector<uint8_t> IP_values(IP::kIPSize);
    std::transform(results.begin(), results.end(), IP_values.begin(), [] (const std::string& result) {
        return std::stoi(result);
    });

    return IP(std::move(IP_values));
}

std::optional<std::vector<IP>> GetIPsFromStream(std::istream& in) {
    std::vector<IP> ips;

    std::string line;
    while (std::getline(in, line)) {
        std::istringstream iss(line);

        std::vector<std::string> results(std::istream_iterator<std::string>{iss},
                                         std::istream_iterator<std::string>());

        if (results.size() != 3) {
            return std::nullopt;
        }

        auto ip = GetIPFromString(results[0]);
        if (!ip.has_value()) {
            return std::nullopt;
        }

        ips.push_back(ip.value());
    }

    return ips;
}
