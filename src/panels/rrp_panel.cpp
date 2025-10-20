#include "rrp_panel.hpp"
#include "implot.h"
#include "imgui.h"
#include <vector>
#include <algorithm>

void renderRRPPanel(const RRPClient& rrp) {
	const auto& data = rrp.data();
	if (data.empty()) return;

	static bool showChart = true;

	// Perp x and y index in billions
	std::vector<double> x(data.size()), y(data.size());
	for (size_t i = 0; i < data.size(); ++i) {
		x[i] = (double)i;
		y[i] = data[data.size() - 1 - i].totalAmtAccepted;
	}

	// Fixed window size
	ImGui::SetNextWindowSize(ImVec2(600, 400), ImGuiCond_FirstUseEver);
	ImGui::Begin("RRP");

	// Toggle button
	if (ImGui::Button(showChart ? "Show  Raw Data" : "Show Chart"))
		showChart = !showChart;

    if (showChart) {
        // Chart view
        double x_min = 0, x_max = (double)data.size() - 1;
        double y_min = 0;
        double y_max = *std::max_element(y.begin(), y.end()) * 1.05; // small margin

        ImPlot::SetNextAxisLimits(ImAxis_X1, x_min, x_max, ImGuiCond_Always);
        ImPlot::SetNextAxisLimits(ImAxis_Y1, y_min, y_max, ImGuiCond_Always);

        if (ImPlot::BeginPlot("RRP Volume", ImVec2(-1, -1))) {
            ImPlot::SetupAxes("Day", "Amount ($B)");
            ImPlot::SetupAxisTicks(ImAxis_X1, x.data(), (int)x.size()); // integer day ticks
            ImPlot::PlotBars("RRP Amount", x.data(), y.data(), (int)data.size(), 0.5);
            ImPlot::EndPlot();
        }
    }
    else {
        // Raw data table
        ImGui::BeginTable("RRP Table", 2, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg);
        ImGui::TableSetupColumn("Date");
        ImGui::TableSetupColumn("Amount ($B)");
        ImGui::TableHeadersRow();

        for (auto it = data.rbegin(); it != data.rend(); ++it) {
            ImGui::TableNextRow();
            ImGui::TableNextColumn(); ImGui::TextUnformatted(it->date.c_str());
            ImGui::TableNextColumn(); ImGui::Text("%.2f", it->totalAmtAccepted);
        }
        ImGui::EndTable();
    }

    ImGui::End();
}