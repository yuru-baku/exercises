#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <statement/statement.hpp>

int main()
{
  std::ifstream playsFile("plays.json");
  const nlohmann::json plays = nlohmann::json::parse(playsFile);

  std::ifstream invoicesFile("invoices.json");
  const nlohmann::json invoices = nlohmann::json::parse(invoicesFile);

  std::cout << statement::Statement(invoices, plays).toString();
  return 0;
}