#pragma once

#include <functional>
#include <mutex>
#include <string>
#include <vector>

#include <wx/dc.h>
#include <wx/gdicmn.h>

#include "../ITableVisualizer.hpp"

class GraphicsTableVisualizer : public ITableVisualizer {
private:
    std::vector<TableRow> rows;
    std::vector<TableCell> highlighted;
    AuxEvent currentEvent = AuxEvent::PlaceInBucket;
    std::string stepName;
    SortStats stats;
    std::function<void()> refresh;
    mutable std::mutex stateMutex;

public:
    explicit GraphicsTableVisualizer();

    ~GraphicsTableVisualizer() override;

    void initialize();
    void shutdown();
    void setRefreshCallback(std::function<void()> callback);
    void draw(wxDC& dc, const wxRect& bounds) const;

    void renderFrame(const std::vector<TableRow>& rows, AuxEvent event, const std::vector<TableCell>& highlighted, const std::string& stepName, const SortStats& stats) override;
};
