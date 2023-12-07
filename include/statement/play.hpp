#pragma once
#include <statement/genre.hpp>
#include <statement/statement.hpp>

namespace statement {
struct Play
{
  std::string name;
  Genre genre;
};

void from_json(const nlohmann::json &json, Play &play);
}// namespace statement
