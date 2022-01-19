#pragma once

#include <string>
#include <optional>
#include <vector>

#include "ip.h"

std::optional<IP> GetIPFromString(const std::string& ip_str);

std::optional<std::vector<IP>> GetIPsFromStream(std::istream& in);
