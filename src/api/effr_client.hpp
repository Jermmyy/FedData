#pragma once
#include <string>
#include <vector>

struct EFFRValue {
    std::string date;
    double value;
};

class EFFRClient {
public:
    EFFRClient(const std::string& start, const std::string& end)
        : startDate(start), endDate(end) {
    }

    void fetch();                      // fetches data from NY Fed
    const std::vector<EFFRValue>& data() const { return rates; }

private:
    std::string startDate;
    std::string endDate;
    std::vector<EFFRValue> rates;
};