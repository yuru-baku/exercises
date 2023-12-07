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

std::string Statement::perfsToString() const
{
  return std::accumulate(
    performances.begin(), performances.end(), std::string{ " " }, [](const auto &lines, const auto &perf) {
      return std::format("{}\n {}", lines, perf.toString());
    });
}

std::string Statement::toString() const
{
  const auto preamble = std::format("Statement for {}", customer);
  const auto performanceLines = perfsToString();
  const auto totalCostLine = std::format("Amount owed is {}", toDollar(totalCost()));
  const auto totalCreditLine = std::format("You earned {} credits", totalCredit());
  return std::format("{}\n{}\n{}\n{}\n", preamble, performanceLines, totalCostLine, totalCreditLine);
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
}// namespace statement