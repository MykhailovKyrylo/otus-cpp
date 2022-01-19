#include "ip.h"

#include <sstream>
#include <utility>

IP::IP(std::vector<uint8_t>&& bytes) : bytes(std::move(bytes)) {}

std::ostream& operator<<(std::ostream& out, const IP& ip) {
    std::ostringstream os;

    const char* delimiter = ".";
    std::copy(ip.bytes.begin(), ip.bytes.end(), std::ostream_iterator<uint8_t>(os, delimiter));

    out << os.str();

    return out;
}
