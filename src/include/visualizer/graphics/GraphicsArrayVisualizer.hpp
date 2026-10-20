#pragma once

#include <functional>
#include <mutex>
#include <string>
#include <map>
#include <vector>

#include <wx/dc.h>
#include <wx/gdicmn.h>

#include "../IArrayVisualizer.hpp"

class GraphicsArrayVisualizer : public IArrayVisualizer {
private:
    std::vector<int> mainArray;
    std::map<std::string, std::vector<int>> auxiliaryArrays;
    int firstIndex = -1;
    int secondIndex = -1;
    int auxiliaryIndex = -1;
    SortEvent currentEvent = SortEvent::Compare;
    AuxEvent auxiliaryEvent = AuxEvent::PlaceInBucket;
    std::string auxiliaryLabel;
    std::string stepName;
    SortStats stats;
    std::function<void()> refresh;
    mutable std::mutex stateMutex;

public:
    explicit GraphicsArrayVisualizer();

    ~GraphicsArrayVisualizer() override;

    void initialize();
    void shutdown();
    void setRefreshCallback(std::function<void()> callback);
    void draw(wxDC& dc, const wxRect& bounds) const;

    void renderFrame(const std::vector<int>& arr, SortEvent event, int idx1, int idx2, const std::string& stepName, const SortStats& stats) override;

    void renderAuxFrame(const std::vector<int>& arr, AuxEvent event, int highlightedIdx, const std::string& label, const std::string& stepName, const SortStats& stats) override;
};
