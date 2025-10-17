#include <iostream>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

int main() {
    std::cout << "Testing dependencies...\n";

    // Test
    auto response = cpr::Get(cpr::Url{ "https://api.github.com" });
    std::cout << "HTTP status: " << response.status_code << "\n";

    // Simple Parse
    nlohmann::json j = { {"hello", "world"} };
    std::cout << j.dump(2) << "\n";

    return 0;
}