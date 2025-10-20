#include "rrp_client.hpp"
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <iostream>

bool RRPClient::fetchLatest(int numOperations) {
    m_data.clear();

    // Construct URL dynamically
    std::string url = "https://markets.newyorkfed.org/api/rp/reverserepo/all/results/last/"
        + std::to_string(numOperations) + ".json";

    auto r = cpr::Get(cpr::Url{ url }, cpr::Header{ {"accept", "application/json"} });
    if (r.status_code != 200) {
        std::cerr << "Error fetching RRP: " << r.status_code << std::endl;
        return false;
    }

    try {
        auto j = nlohmann::json::parse(r.text);
        if (!j.contains("repo") || !j["repo"].contains("operations")) return false;

        for (auto& op : j["repo"]["operations"]) {
            if (!op.contains("operationDate") || !op.contains("totalAmtAccepted")) continue;

            RRPData dp;
            dp.date = op["operationDate"].get<std::string>();
            dp.totalAmtAccepted = op["totalAmtAccepted"].get<double>() / 1e9; // billions
            m_data.push_back(dp);
        }
    }
    catch (std::exception& e) {
        std::cerr << "JSON parse error: " << e.what() << std::endl;
        return false;
    }

    return !m_data.empty();
}