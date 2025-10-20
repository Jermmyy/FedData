#pragma once
#include <string>
#include <vector>

struct SOFRValue {
	std::string date;
	double value;
};

class SOFRClient {
public:
    SOFRClient(const std::string& start, const std::string& end)
        : startDate(start), endDate(end) {
    }

    void fetch();                      // fetches data from NY Fed
    const std::vector<SOFRValue>& data() const { return rates; }

private:
    std::string startDate;
    std::string endDate;
    std::vector<SOFRValue> rates;
};