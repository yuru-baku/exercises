#pragma once
#include <string>
namespace statement {
enum Genre { TRAGEDY, COMEDY, NONE };

Genre toGenre(const std::string &genreName);
}// namespace statement
