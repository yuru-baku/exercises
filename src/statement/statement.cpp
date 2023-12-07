#include <format>
#include <nlohmann/json.hpp>
#include <numeric>
#include <statement/statement.hpp>
#include <statement/util.hpp>
#include <string>
#include <vector>

namespace statement {

Statement::Statement(const nlohmann::json &invoice, const nlohmann::json &plays)
{
  customer = invoice["customer"];
  performances = invoice["performances"].get<std::vector<Performance>>();

  // iterate over all performances to correctly set their genre
  for (auto &performance : performances) { performance.setPlay(plays[performance.playID]); }
}

std::string Statement::toString() const
{
  const auto preamble = std::format("Statement for {}\n", customer);
  const auto items = std::accumulate(
    performances.begin(), performances.end(), std::string{ " " }, [](const auto &lines, const auto &perf) {
      return std::format("{}\n {}", lines, perf.toString());
    });
  const auto totalCostLine = std::format("Amount owed is {}\n", toDollar(totalCost()));
  const auto totalCreditLine = std::format("You earned {} credits\n", totalCredit());
  return std::format("{}{}{}{}", preamble, items, totalCostLine, totalCreditLine);
}

int Statement::totalCost() const
{
  return std::accumulate(
    performances.begin(), performances.end(), 0, [](const int sum, const auto &perf) { return perf.getCost() + sum; });
}

int Statement::totalCredit() const
{
  return std::accumulate(performances.begin(), performances.end(), 0, [](const int sum, const auto &perf) {
    return perf.getCredits() + sum;
  });
}
/*
std::string statement(const nlohmann::json &invoices, const nlohmann::json &plays)
{


  int totalAmount{ 0 };
  int volumeCredits{ 0 };
  const Statement stats(invoices, plays);
  auto result = std::format("Statement for {}\n", std::string{ invoices[0]["customer"] });

  for (const auto &performance : stats.performances) {
    result += lineItem();
    totalAmount += performance.getCost();
    volumeCredits += performance.getCredits();
  }

  result += std::format("Amount owed is {}\n", toDollar(totalAmount));
  result += std::format("You earned {} credits\n", volumeCredits);
  return result;

return "";
}
 */
}// namespace statement