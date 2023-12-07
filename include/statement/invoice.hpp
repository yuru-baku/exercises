#pragma once
#include <nlohmann/json.hpp>
#include <statement/performance.hpp>
#include <string>
#include <vector>

namespace statement {
struct Performance;
struct invoice
{
  std::string client;
  std::vector<Performance> performance;
};
}// namespace statement