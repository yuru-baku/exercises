#pragma once
#include <statement/genre.hpp>
#include <statement/play.hpp>

namespace statement {
struct Play;

struct Performance
{
  std::string playID;
  int audience;
  Genre genre = Genre::NONE;
  std::string name;
  int getCredits() const;
  int getCost() const;
  void setPlay(const Play &play);
  std::string toString() const;

private:
  int calculateComedyCost() const;
  int calculateTragedyCost() const;
};

void from_json(const nlohmann::json &json, Performance &performance);

}// namespace statement
