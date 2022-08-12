#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <utility>
#include <iterator>
#include <sstream>
#include <tuple>

namespace {
    template<class Tuple, size_t Idx>
    std::ostream& print_ip_impl([[maybe_unused]] Tuple tuple, std::ostream& out = std::cout) {
        out << '\n';
        return out;
    }

    template<class Tuple, size_t Idx, class Head, class... Tail>
    std::ostream& print_ip_impl(Tuple tuple, std::ostream& out = std::cout) {
        if constexpr (Idx != 0) {
            out << '.';
        }

        out << std::get<Idx>(tuple);
        print_ip_impl<decltype(tuple), Idx + 1, Tail...>(tuple);
        return out;
    }
}   // namespace - deprecated for outside users

template<typename T, std::enable_if_t<std::is_integral_v<T>, bool> = true>
std::ostream& print_ip(const T& number, std::ostream& out = std::cout) {
    const auto byte_p = reinterpret_cast<const std::byte*>(&number);

    constexpr size_t kSizeOfValue{sizeof(number)};
    for (auto i = static_cast<int>(kSizeOfValue - 1); i >= 0; i--) {
        out << static_cast<int>(byte_p[i]);
        out << ((i == 0) ? '\n' : '.');
    }

    return out;
}

template<typename T, std::enable_if_t<std::is_same_v<T, std::string>, bool> = true>
std::ostream& print_ip(const T& string, std::ostream& out = std::cout) {
    out << string << '\n';
    return out;
}

template<typename T, std::enable_if_t<!std::is_same_v<typename T::value_type, char>, bool> = true>
std::ostream& print_ip(const T& container, std::ostream& out = std::cout) {
    std::ostringstream os;

    const char* delimiter = ".";
    std::copy(container.begin(), container.end(), std::ostream_iterator<typename T::value_type>(os, delimiter));

    const std::string& os_str = os.str();
    const std::string_view output(os_str.data(), os_str.size() - 1);

    out << output << '\n';

    return out;
}

/// \note: printing tuples is prohibited if inner types are not the same
template<class Head,
         class... Args,
         typename = std::enable_if_t<std::conjunction_v<std::is_same<Head, Args>...>>>
std::ostream& print_ip(std::tuple<Head, Args...> tuple, std::ostream& out = std::cout) {
    print_ip_impl<decltype(tuple), 0, Head, Args...>(tuple);
    return out;
}
