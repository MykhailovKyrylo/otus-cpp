#include "ip.h"

#include <sstream>
#include <utility>
#include <iterator>

IP::IP(std::vector<uint8_t>&& bytes) : bytes(std::move(bytes)) {}

std::ostream& operator<<(std::ostream& out, const IP& ip) {
    std::ostringstream os;

    const char* delimiter = ".";
    std::copy(ip.bytes.begin(), ip.bytes.end(), std::ostream_iterator<int>(os, delimiter));

    const std::string& ip_str = os.str();
    out << ip_str.substr(0, ip_str.size() - 1);

    return out;
}
