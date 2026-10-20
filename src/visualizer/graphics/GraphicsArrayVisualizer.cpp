#include <algorithm>
#include <cmath>
#include <utility>

#include "../../include/visualizer/graphics/GraphicsArrayVisualizer.hpp"

namespace {
const wxColour kInk(35, 45, 60);
const wxColour kMuted(110, 122, 138);
const wxColour kBar(72, 139, 220);
const wxColour kCompare(245, 181, 62);
const wxColour kMove(226, 91, 91);
const wxColour kAux(126, 187, 155);

void drawBars(wxDC& dc, const std::vector<int>& values, const wxRect& area,
              int highlightA, int highlightB, const wxColour& normal,
              const wxColour& highlight) {
    if (values.empty()) {
        dc.SetTextForeground(kMuted);
        dc.DrawText("(empty)", area.x + 8, area.y + 4);
        return;
    }

    const int padding = 8;
    const int chartHeight = std::max(1, area.height - padding * 2 - 18);
    const int baseline = area.y + padding + chartHeight;
    int maxMagnitude = 1;
    for (const int value : values)
        maxMagnitude = std::max(maxMagnitude, std::abs(value));

    const double slotWidth = static_cast<double>(std::max(1, area.width - padding * 2)) / values.size();
    const int barWidth = std::max(2, static_cast<int>(slotWidth * 0.72));
    dc.SetPen(wxPen(wxColour(205, 213, 223), 1));
    dc.DrawLine(area.x + padding, baseline, area.x + area.width - padding, baseline);

    for (std::size_t i = 0; i < values.size(); ++i) {
        const int value = values[i];
        const int barHeight = std::max(1, static_cast<int>(static_cast<double>(std::abs(value)) / maxMagnitude * chartHeight));
        const int x = area.x + padding + static_cast<int>(i * slotWidth) + (static_cast<int>(slotWidth) - barWidth) / 2;
        const int y = value >= 0 ? baseline - barHeight : baseline;
        const bool active = static_cast<int>(i) == highlightA || static_cast<int>(i) == highlightB;
        dc.SetPen(wxPen(active ? highlight : normal, 1));
        dc.SetBrush(wxBrush(active ? highlight : normal));
        dc.DrawRectangle(x, y, barWidth, barHeight);
        if (slotWidth >= 34) {
            dc.SetTextForeground(kInk);
            dc.DrawText(wxString::Format("%d", value), x - 6, baseline + 3);
        }
    }
}

wxColour mainHighlight(SortEvent event) {
    return event == SortEvent::Swap || event == SortEvent::Shift || event == SortEvent::Insert ? kMove : kCompare;
}
}

GraphicsArrayVisualizer::GraphicsArrayVisualizer() = default;
GraphicsArrayVisualizer::~GraphicsArrayVisualizer() = default;
void GraphicsArrayVisualizer::initialize() {}
void GraphicsArrayVisualizer::shutdown() {}

void GraphicsArrayVisualizer::setRefreshCallback(std::function<void()> callback) {
    std::lock_guard<std::mutex> lock(stateMutex);
    refresh = std::move(callback);
}

void GraphicsArrayVisualizer::renderFrame(const std::vector<int>& arr, SortEvent event, int idx1, int idx2,
                                          const std::string& name, const SortStats& currentStats) {
    std::function<void()> refreshCallback;
    {
        std::lock_guard<std::mutex> lock(stateMutex);
        mainArray = arr;
        auxiliaryArrays.clear();
        auxiliaryLabel.clear();
        currentEvent = event;
        firstIndex = idx1;
        secondIndex = idx2;
        stepName = name;
        stats = currentStats;
        refreshCallback = refresh;
    }
    if (refreshCallback)
        refreshCallback();
}

void GraphicsArrayVisualizer::renderAuxFrame(const std::vector<int>& arr, AuxEvent event, int highlightedIdx,
                                             const std::string& label, const std::string& name,
                                             const SortStats& currentStats) {
    std::function<void()> refreshCallback;
    {
        std::lock_guard<std::mutex> lock(stateMutex);
        auxiliaryArrays[label] = arr;
        auxiliaryLabel = label;
        auxiliaryEvent = event;
        auxiliaryIndex = highlightedIdx;
        stepName = name;
        stats = currentStats;
        refreshCallback = refresh;
    }
    if (refreshCallback)
        refreshCallback();
}

void GraphicsArrayVisualizer::draw(wxDC& dc, const wxRect& bounds) const {
    std::lock_guard<std::mutex> lock(stateMutex);
    dc.SetClippingRegion(bounds);
    dc.SetBrush(wxBrush(wxColour(250, 252, 255)));
    dc.SetPen(*wxTRANSPARENT_PEN);
    dc.DrawRectangle(bounds);
    dc.SetTextForeground(kInk);
    dc.SetFont(wxFont(10, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    dc.DrawText("Array visualization", bounds.x + 12, bounds.y + 8);
    dc.SetFont(wxFont(8, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    dc.SetTextForeground(kMuted);
    dc.DrawText(wxString::Format("%s   |   Reads: %llu   Writes: %llu",
        wxString::FromUTF8(stepName.c_str()),
        static_cast<unsigned long long>(stats.getComparisons()),
        static_cast<unsigned long long>(stats.getSwaps())), bounds.x + 12, bounds.y + 29);

    const int headerHeight = 48;
    const int gap = 8;
    const int mainHeight = std::max(90, (bounds.height - headerHeight - gap * 3) * 2 / 3);
    const wxRect mainArea(bounds.x + 8, bounds.y + headerHeight, bounds.width - 16, mainHeight);
    dc.SetTextForeground(kInk);
    dc.SetFont(wxFont(8, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    dc.DrawText("Main array", mainArea.x, mainArea.y - 1);
    wxRect barsArea(mainArea.x, mainArea.y + 18, mainArea.width, std::max(20, mainArea.height - 18));
    drawBars(dc, mainArray, barsArea, firstIndex, secondIndex, kBar, mainHighlight(currentEvent));

    int auxY = mainArea.y + mainArea.height + gap;
    dc.SetTextForeground(kInk);
    dc.DrawText("Auxiliary arrays", bounds.x + 8, auxY);
    auxY += 18;
    const int auxCount = static_cast<int>(auxiliaryArrays.size());
    const int auxHeight = auxCount == 0 ? 32 : std::max(44, (bounds.y + bounds.height - auxY - 8) / auxCount);
    for (const auto& [label, values] : auxiliaryArrays) {
        dc.SetTextForeground(kMuted);
        dc.DrawText(wxString::FromUTF8(label.c_str()), bounds.x + 10, auxY + 2);
        const int labelWidth = 100;
        wxRect area(bounds.x + labelWidth, auxY, std::max(1, bounds.width - labelWidth - 10), std::max(25, auxHeight - 4));
        drawBars(dc, values, area, label == auxiliaryLabel ? auxiliaryIndex : -1, -1, kAux,
                 auxiliaryEvent == AuxEvent::CompareInAux ? kCompare : kMove);
        auxY += auxHeight;
        if (auxY >= bounds.y + bounds.height)
            break;
    }
    if (auxCount == 0) {
        dc.SetTextForeground(kMuted);
        dc.DrawText("(no auxiliary arrays yet)", bounds.x + 12, auxY + 3);
    }
    dc.DestroyClippingRegion();
}
