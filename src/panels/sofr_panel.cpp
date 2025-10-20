#include "sofr_panel.hpp"
#include "implot.h"
#include "imgui.h"
#include <vector>
#include <algorithm>

void renderSOFRPanel(const SOFRClient& sofr) {
    const auto& data = sofr.data();
    if (data.empty()) return;

    static bool showChart = true;

    std::vector<double> x(data.size()), y(data.size());
    for (size_t i = 0; i < data.size(); ++i) {
        x[i] = (double)i;
        y[i] = data[data.size() - 1 - i].value;
    }

    // Set fixed window size
    ImGui::SetNextWindowSize(ImVec2(600, 400), ImGuiCond_FirstUseEver);
    ImGui::Begin("SOFR");

    // Toggle Button
    if (ImGui::Button(showChart ? "Show raw data" : "Show Chart"))
        showChart = !showChart;

    if (showChart) {
        // Chart view
        double x_min = 0, x_max = (double)data.size() - 1;
        double y_min = *std::min_element(y.begin(), y.end());
        double y_max = *std::max_element(y.begin(), y.end());

        ImPlot::SetNextAxisLimits(ImAxis_X1, x_min, x_max, ImGuiCond_Always);
        ImPlot::SetNextAxisLimits(ImAxis_Y1, y_min, y_max, ImGuiCond_Always);

        if (ImPlot::BeginPlot("SOFR over Time", ImVec2(-1, -1))) {
            ImPlot::SetupAxes("Day", "Rate (%)");
            ImPlot::SetupAxisTicks(ImAxis_X1, x.data(), (int)x.size()); // integer ticks
            ImPlot::PlotLine("SOFR", x.data(), y.data(), (int)data.size());
            ImPlot::EndPlot();
        }
    }
    else {
        // Raw data view
        ImGui::BeginTable("SOFR Table", 2, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg);
        ImGui::TableSetupColumn("Date");
        ImGui::TableSetupColumn("Rate (%)");
        ImGui::TableHeadersRow();

        for (const auto& r : data) {
            ImGui::TableNextRow();
            ImGui::TableNextColumn(); ImGui::TextUnformatted(r.date.c_str());
            ImGui::TableNextColumn(); ImGui::Text("%.2f", r.value);
        }
        ImGui::EndTable();
    }

    ImGui::End();
}