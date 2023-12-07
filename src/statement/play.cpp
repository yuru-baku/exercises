#include <nlohmann/json.hpp>
#include <statement/genre.hpp>
#include <statement/play.hpp>

namespace statement {
void from_json(const nlohmann::json &json, Play &play)
{
  json.at("name").get_to(play.name);
  play.genre = toGenre(json.at("type"));
}
}// namespace statement
