#include <wx/app.h>
#include <wx/init.h>

#include <algorithm>
#include <iostream>

#include "src/include/AlgorithmRunner.hpp"
#include "src/include/ArrayGenerator.hpp"
#include "src/algorithms/exchange-sort/bubble-sort/BubbleSort.hpp"
#include "src/algorithms/merge-sort/MergeSort.hpp"
#include "src/algorithms/distribution-sort/counting-sort/CountingSort.hpp"
#include "src/algorithms/insertion-sort/tree-sort/UnbalancedBstTreeSort.hpp"
#include "src/include/visualizer/VisualizationSession.hpp"
#include "src/include/visualizer/graphics/GraphicsVisualizerDashboard.hpp"

class GraphicsTestApp final : public wxApp {
public:
    bool OnInit() override {
        return true;
    }
};

wxIMPLEMENT_APP_NO_MAIN(GraphicsTestApp);

int main(int argc, char** argv) {
    if (!wxEntryStart(argc, argv)) {
        return 77;
    }

    if (!wxTheApp || !wxTheApp->CallOnInit()) {
        wxEntryCleanup();
        return 77;
    }

    int result = 0;

    {
        GraphicsVisualizerDashboard dashboard(
            nullptr, "Dashboard integration test");

        dashboard.setFrameDelay(0);
        dashboard.setSortingRunning(false);

        VisualizationSession session(
            dashboard.getArrayVisualizer(),
            dashboard.getTableVisualizer(),
            dashboard.getGraphVisualizer());

        const auto input = ArrayGenerator::generate(
            64, -50, 50, Pattern::UniformRandom, 99ULL);

        auto bubbleData = input;
        auto bubbleRunner = AlgorithmRunner::fromClassic(bubbleSort);
        bubbleRunner(bubbleData, session);

        auto mergeData = input;
        mergeSort(mergeData, session);

        auto countData = input;
        countingSort(countData, session);

        auto treeData = input;
        unbalancedBstTreeSort(treeData, session);

        wxTheApp->ProcessPendingEvents();

        const bool passed =
            std::is_sorted(bubbleData.begin(), bubbleData.end()) &&
            std::is_sorted(mergeData.begin(), mergeData.end()) &&
            std::is_sorted(countData.begin(), countData.end()) &&
            std::is_sorted(treeData.begin(), treeData.end());

        if (!passed) {
            std::cerr
                << "Dashboard integration test failed to sort all inputs.\n";
            result = 1;
        }
        else {
            std::cout
                << "Graphics dashboard integration test passed.\n";
        }
    } // Dashboard is destroyed before wxWidgets cleanup.

    wxTheApp->OnExit();
    wxEntryCleanup();

    return result;
}