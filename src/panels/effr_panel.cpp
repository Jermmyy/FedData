#include "effr_panel.hpp"
#include "implot.h"
#include "imgui.h"
#include <vector>
#include <algorithm>

void renderEFFRPanel(const EFFRClient& effr) {
    const auto& data = effr.data();
    if (data.empty()) return;

    static bool showChart = true;

    std::vector<double> x(data.size()), y(data.size());
    for (size_t i = 0; i < data.size(); ++i) {
        x[i] = (double)i;
        y[i] = data[data.size() - 1 - i].value;
    }

    // Set fixed window size
    ImGui::SetNextWindowSize(ImVec2(600, 400), ImGuiCond_FirstUseEver);
    ImGui::Begin("EFFR");

    // Toggle Button
    if (ImGui::Button(showChart ? "Show raw data" : "Show Chart"))
        showChart = !showChart;

    if (showChart) {
        // Chart view
        double x_min = 0, x_max = (double)data.size() - 1;
        double y_min = *std::min_element(y.begin(), y.end());
        double y_max = *std::max_element(y.begin(), y.end());

        double y_margin = (y_max - y_min) * 0.05; // 5% margin
        ImPlot::SetNextAxisLimits(ImAxis_X1, x_min, x_max, ImGuiCond_Always);
        ImPlot::SetNextAxisLimits(ImAxis_Y1, y_min - y_margin, y_max + y_margin, ImGuiCond_Always);

        if (ImPlot::BeginPlot("EFFR over Time", ImVec2(-1, -1))) {
            ImPlot::SetupAxes("Day", "Rate (%)");
            ImPlot::SetupAxisTicks(ImAxis_X1, x.data(), (int)x.size()); // integer ticks
            ImPlot::PlotLine("EFFR", x.data(), y.data(), (int)data.size());
            ImPlot::EndPlot();
        }
    }
    else {
        // Raw data view
        ImGui::BeginTable("EFFR Table", 2, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg);
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