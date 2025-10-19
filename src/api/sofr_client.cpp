#include "sofr_client.hpp"
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

void SOFRClient::fetch() {
    rates.clear();
    std::string url = "https://markets.newyorkfed.org/api/rates/all/search.json?startDate="
        + startDate + "&endDate=" + endDate + "&type=rate";

    cpr::Response r = cpr::Get(cpr::Url{ url }, cpr::Header{ {"accept", "application/json"} });
    if (r.status_code != 200) return;

    auto j = nlohmann::json::parse(r.text);
    if (!j.contains("refRates")) return;

    for (auto& item : j["refRates"])
        if (item["type"] == "SOFR")
            rates.push_back({ item["effectiveDate"].get<std::string>(), item["percentRate"].get<double>() });
}