#pragma once

#include <myproject/statement_export.hpp>
#include <nlohmann/json.hpp>
#include <statement/genre.hpp>
#include <statement/invoice.hpp>
#include <statement/performance.hpp>
#include <string>

namespace statement {
struct Performance;
struct Statement
{
  Statement(const nlohmann::json &invoices, const nlohmann::json &plays);

  std::string toString() const;
  int totalCost() const;
  int totalCredit() const;

private:
  std::string perfsToString() const;
   std::string customer;
  std::vector<Performance> performances;
};
}// namespace statement