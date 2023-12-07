#include <statement/genre.hpp>
#include <string>

namespace statement
{
Genre toGenre(const std::string &genreName)
{
  if (genreName == "tragedy") { return Genre::TRAGEDY; }
  if (genreName == "comedy") { return Genre::COMEDY; }
  return Genre::NONE;
}

} // namespace statement
