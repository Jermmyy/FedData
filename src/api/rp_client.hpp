#pragma once
#include <string>
#include <vector>

struct RPData {
	std::string date;
	double totalAmtAccepted; // In billions
};

class RPClient {
public:
	RPClient() = default;

	// Fetch latest
	bool fetchLatest(int numOperations);

	// Return stored data
	const std::vector<RPData>& data() const { return m_data; }

private:
	std::vector<RPData> m_data;
};