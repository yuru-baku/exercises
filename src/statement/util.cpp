#include <format>
#include <statement/util.hpp>
#include <string>

namespace statement {
std::string toDollar(const int cent)
{
  const auto centsPerDollar = 100.0;// Double for FP division.
  return std::format("${:0.2f}", (cent / centsPerDollar));
}
}// namespace statement
