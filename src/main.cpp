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
  for (const auto &invoice : invoices) { std::cout << statement::Statement(invoice, plays).toString(); }

  return 0;
}