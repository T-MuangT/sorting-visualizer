#include <algorithm>
#include <string>
#include <utility>

#include "../../include/visualizer/graphics/GraphicsTableVisualizer.hpp"

namespace {
const wxColour kInk(35, 45, 60);
const wxColour kMuted(110, 122, 138);
const wxColour kLine(214, 222, 232);
const wxColour kCell(239, 244, 250);
const wxColour kCompare(245, 181, 62);
const wxColour kPlace(126, 187, 155);
const wxColour kFlush(226, 91, 91);

bool containsCell(const std::vector<TableCell>& cells, int row, int pos) {
    return std::any_of(cells.begin(), cells.end(), [row, pos](const TableCell& cell) {
        return cell.row == row && cell.pos == pos;
    });
}

const wxColour& eventColour(AuxEvent event) {
    switch (event) {
        case AuxEvent::CompareInAux:
        case AuxEvent::AccumulateCount:
            return kCompare;
        case AuxEvent::FlushBucket:
        case AuxEvent::PlaceCountOutput:
            return kFlush;
        default:
            return kPlace;
    }
}
}

GraphicsTableVisualizer::GraphicsTableVisualizer() = default;
GraphicsTableVisualizer::~GraphicsTableVisualizer() = default;
void GraphicsTableVisualizer::initialize() {}
void GraphicsTableVisualizer::shutdown() {}

void GraphicsTableVisualizer::setRefreshCallback(std::function<void()> callback) {
    std::lock_guard<std::mutex> lock(stateMutex);
    refresh = std::move(callback);
}

void GraphicsTableVisualizer::renderFrame(const std::vector<TableRow>& tableRows, AuxEvent event,
                                          const std::vector<TableCell>& activeCells, const std::string& name,
                                          const SortStats& currentStats) {
    std::function<void()> refreshCallback;
    {
        std::lock_guard<std::mutex> lock(stateMutex);
        rows = tableRows;
        highlighted = activeCells;
        currentEvent = event;
        stepName = name;
        stats = currentStats;
        refreshCallback = refresh;
    }
    if (refreshCallback)
        refreshCallback();
}

void GraphicsTableVisualizer::draw(wxDC& dc, const wxRect& bounds) const {
    std::lock_guard<std::mutex> lock(stateMutex);
    dc.SetClippingRegion(bounds);
    dc.SetBrush(wxBrush(wxColour(250, 252, 255)));
    dc.SetPen(*wxTRANSPARENT_PEN);
    dc.DrawRectangle(bounds);
    dc.SetTextForeground(kInk);
    dc.SetFont(wxFont(10, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    dc.DrawText("Auxiliary table", bounds.x + 12, bounds.y + 8);
    dc.SetFont(wxFont(8, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    dc.SetTextForeground(kMuted);
    dc.DrawText(wxString::Format("%s   |   Reads: %llu   Writes: %llu", wxString::FromUTF8(stepName.c_str()),
        static_cast<unsigned long long>(stats.getComparisons()),
        static_cast<unsigned long long>(stats.getSwaps())), bounds.x + 12, bounds.y + 29);

    if (rows.empty()) {
        dc.DrawText("(no auxiliary rows yet)", bounds.x + 14, bounds.y + 60);
        dc.DestroyClippingRegion();
        return;
    }

    const int top = bounds.y + 56;
    const int rowHeight = 34;
    const int labelWidth = std::min(115, std::max(70, bounds.width / 4));
    int maxColumns = 0;
    for (const auto& row : rows)
        maxColumns = std::max(maxColumns, static_cast<int>(row.values.size()));
    const int available = std::max(1, bounds.width - labelWidth - 24);
    const int cellWidth = std::max(38, std::min(90, available / std::max(1, maxColumns)));
    const wxColour activeColour = eventColour(currentEvent);

    for (std::size_t r = 0; r < rows.size(); ++r) {
        const int y = top + static_cast<int>(r) * rowHeight;
        if (y + rowHeight > bounds.y + bounds.height)
            break;
        dc.SetFont(wxFont(8, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
        dc.SetTextForeground(kInk);
        dc.DrawText(wxString::FromUTF8(rows[r].label.c_str()), bounds.x + 12, y + 9);
        if (rows[r].values.empty()) {
            dc.SetFont(wxFont(8, wxFONTFAMILY_SWISS, wxFONTSTYLE_ITALIC, wxFONTWEIGHT_NORMAL));
            dc.SetTextForeground(kMuted);
            dc.DrawText("(empty)", bounds.x + labelWidth, y + 9);
            continue;
        }

        for (std::size_t c = 0; c < rows[r].values.size(); ++c) {
            const int x = bounds.x + labelWidth + static_cast<int>(c) * cellWidth;
            if (x + cellWidth - 3 > bounds.x + bounds.width)
                break;
            const bool active = containsCell(highlighted, static_cast<int>(r), static_cast<int>(c));
            dc.SetPen(wxPen(active ? activeColour : kLine, 1));
            dc.SetBrush(wxBrush(active ? activeColour : kCell));
            dc.DrawRoundedRectangle(x, y + 2, cellWidth - 4, rowHeight - 5, 4);
            dc.SetTextForeground(active ? *wxWHITE : kInk);
            dc.SetFont(wxFont(9, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL,
                              active ? wxFONTWEIGHT_BOLD : wxFONTWEIGHT_NORMAL));
            const wxString value = wxString::Format("%d", rows[r].values[c]);
            wxCoord textWidth = 0, textHeight = 0;
            dc.GetTextExtent(value, &textWidth, &textHeight);
            dc.DrawText(value, x + (cellWidth - 4 - textWidth) / 2, y + (rowHeight - textHeight) / 2);
        }
    }
    dc.DestroyClippingRegion();
}
