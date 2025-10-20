#pragma once
#include <string>
#include <vector>

struct RRPData {
	std::string date;
	double totalAmtAccepted; // In billions
};

class RRPClient {
public:
	RRPClient() = default;

	// Fetch latest
	bool fetchLatest(int numOperations);

	// Return stored data
	const std::vector<RRPData>& data() const { return m_data; }

private:
	std::vector<RRPData> m_data;
};