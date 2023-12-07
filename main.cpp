
#include <json/json.h>
#include <assert.h>
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <math.h>

using namespace std;

namespace
{
    constexpr int calculateTragedyCost(const int audienceSize)
    {
        const auto baseCost = 40000;
        const auto minSize = 30;
        const auto audienceDependendCost = (audienceSize > minSize) ? 1000 * (audienceSize - minSize) : 0;
        return baseCost + audienceDependendCost;
    }

    enum string_code
    {
        tragedy,
        comedy,
        none
    };

    string_code hashit(std::string const &inString)
    {
        if (inString == "tragedy")
        {
            return tragedy;
        }
        if (inString == "comedy")
        {
            return comedy;
        }
        else
        {
            return none;
        }
    }

    string statement(Json::Value &invoices, Json::Value &plays)
    {
        unsigned int totalAmount{0};
        unsigned int volumeCredits{0};

        string result = "Statement for " + invoices[0]["customer"].asString() + " \n";
        Json::Value performances = invoices[0]["performances"];

        for (unsigned int index = 0; index < performances.size(); ++index)
        {
            unsigned int thisAmount{0};
            const auto play = plays[performances[index]["playID"].asString()];
            const int audience = performances[index]["audience"].asInt();

            switch (hashit(play["type"].asString()))
            {
            case tragedy:
                thisAmount = calculateTragedyCost(audience);
                break;
            case comedy:
                thisAmount = 30000;
                if (audience > 20)
                {
                    thisAmount += 10000 + 500 * (audience - 20);
                }
                thisAmount += 300 * audience;
                break;
            default:
                return "error";
            }

            volumeCredits += max(audience - 30, 0);

            if (play["type"].asString() == "comedy")
            {
                volumeCredits += floor(audience / 5);
            }

            result += " " + play["name"].asString() + ": $" + std::to_string(thisAmount / 100) + "(" + std::to_string(audience) + " seats)\n";
            totalAmount += thisAmount;
        }

        result += "Amount owed is $" + std::to_string(totalAmount / 100) + "\n";
        result += "You earned " + std::to_string(volumeCredits) + " credits\n";
        return result;
    }
}
int main()
{
    ifstream playsFile("plays.json");
    ifstream invoicesFile("invoices.json");

    Json::Value plays;
    Json::Value invoices;

    playsFile >> plays;
    invoicesFile >> invoices;

    const auto receipt = statement(invoices, plays);
    assert(receipt = std::string{"Statement for BigCon\n"} +
                     " Hamlet: $650(55 seats)\n" +
                     " As You Like It: $580(35 seats)" +
                     " Othello : $500(40 seats)\n" +
                     "Amount owed is $1730\n" +
                     "You earned 47 credits\n");
    return 0;
}