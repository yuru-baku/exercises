#include <algorithm>
#include <cmath>
#include <format>
#include <nlohmann/json.hpp>
#include <statement/genre.hpp>
#include <statement/performance.hpp>
#include <statement/util.hpp>
#include <string>

namespace statement {

std::string Performance::toString() const
{
  return std::format("{}: {} ({} seats)", name, toDollar(getCost()), audience);
}

void Performance::setPlay(const Play &play)
{
  this->name = play.name;
  this->genre = play.genre;
}


int Performance::calculateComedyCost() const
{
  const auto baseCost = 30000;
  const auto minSize = 20;
  const auto offset = 10000;
  const auto largeGroupCostPerPerson = 500;
  const auto largeGroupCost = (audience > minSize) ? offset + largeGroupCostPerPerson * (audience - minSize) : 0;
  const auto costPerPerson = 300;
  const auto groupCost = costPerPerson * audience;
  return baseCost + groupCost + largeGroupCost;
}

int Performance::getCost() const
{
  switch (genre) {
  case TRAGEDY:
    return calculateTragedyCost();
  case COMEDY:
    return calculateComedyCost();
  default:
    return 0;
  }
}

int Performance::calculateTragedyCost() const
{
  const auto baseCost = 40000;
  const auto minSize = 30;
  const auto costPerPerson = 1000;
  const auto audienceDependendCost = (audience > minSize) ? costPerPerson * (audience - minSize) : 0;
  return baseCost + audienceDependendCost;
}


int Performance::getCredits() const
{
  const auto rewardOffset = 30;
  auto volumeCredits = static_cast<int>(std::max(audience - rewardOffset, 0));
  if (genre == Genre::COMEDY) {
    const auto comedyCreditFactor = 5;
    volumeCredits += static_cast<int>(std::floor(audience / comedyCreditFactor));
  }
  return volumeCredits;
}

void from_json(const nlohmann::json &json, Performance &performance)
{
  json.at("playID").get_to(performance.playID);
  json.at("audience").get_to(performance.audience);
}
}// namespace statement
