#include "sofr_panel.hpp"
#include "implot.h"
#include "imgui.h"
#include <vector>
#include <algorithm>

void renderSOFRPanel(const SOFRClient& sofr) {
    const auto& data = sofr.data();
    if (data.empty()) return;

    std::vector<double> x(data.size()), y(data.size());
    for (size_t i = 0; i < data.size(); ++i) {
        x[i] = (double)i;
        y[i] = data[i].value;
    }

    // Set fixed window size
    ImGui::SetNextWindowSize(ImVec2(600, 400), ImGuiCond_FirstUseEver);
    ImGui::Begin("SOFR Chart");

    // Set axis limits to lock zoom/pan
    double x_min = 0, x_max = (double)data.size() - 1;
    double y_min = *std::min_element(y.begin(), y.end());
    double y_max = *std::max_element(y.begin(), y.end());
    ImPlot::SetNextAxisLimits(ImAxis_X1, x_min, x_max, ImGuiCond_Always);
    ImPlot::SetNextAxisLimits(ImAxis_Y1, y_min, y_max, ImGuiCond_Always);

    if (ImPlot::BeginPlot("SOFR over Time")) {
        ImPlot::SetupAxes("Day", "Rate (%)");
        ImPlot::SetupAxisTicks(ImAxis_X1, x.data(), (int)x.size()); // integer ticks only
        ImPlot::PlotLine("SOFR", x.data(), y.data(), (int)data.size());
        ImPlot::EndPlot();
    }

    ImGui::End();
}