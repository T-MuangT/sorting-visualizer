#include <exception>
#include <thread>
#include <utility>
#include <vector>

#include <wx/app.h>
#include <wx/msgdlg.h>

#include "../include/ArrayGenerator.hpp"
#include "../include/AlgorithmRunner.hpp"
#include "../include/PresortConfig.hpp"
#include "../include/menus/graphics/GraphicsMainMenu.hpp"
#include "../include/menus/graphics/GraphicsPresortMenu.hpp"
#include "../include/visualizer/VisualizationSession.hpp"
#include "../include/visualizer/graphics/GraphicsVisualizerDashboard.hpp"

class SortingVisualizerApp final : public wxApp {
private:
    GraphicsMainMenu* mainMenu = nullptr;
    std::thread sortWorker;

    void startVisualization(AlgorithmRunner algorithm) {
        GraphicsPresortMenu setup(mainMenu);
        if (setup.ShowModal() != wxID_OK)
            return;

        const PresortConfig config = setup.getConfig();
        mainMenu->Hide();

        auto* dashboard = new GraphicsVisualizerDashboard(mainMenu, "Sorting Visualizer");
        dashboard->setFrameDelay(config.delayMs);
        dashboard->setSortingRunning(true);
        dashboard->Show();
        SetTopWindow(dashboard);

        if (sortWorker.joinable())
            sortWorker.join();

        sortWorker = std::thread([this, dashboard, algorithm = std::move(algorithm), config]() mutable {
            std::string errorMessage;
            try {
                auto values = ArrayGenerator::generate(config.arraySize, 1, 64, config.pattern);
                VisualizationSession session(
                    dashboard->getArrayVisualizer(),
                    dashboard->getTableVisualizer(),
                    dashboard->getGraphVisualizer());

                session.onArrayEvent(values, SortEvent::Compare, -1, -1, "Starting visualization");
                algorithm(values, session);
                session.onArrayEvent(values, SortEvent::Compare, -1, -1, "Sorting complete");
            } catch (const std::exception& error) {
                errorMessage = error.what();
            } catch (...) {
                errorMessage = "An unexpected error occurred while running the sort.";
            }
            CallAfter([dashboard, errorMessage = std::move(errorMessage)] {
                dashboard->setSortingRunning(false);
                if (!errorMessage.empty())
                    wxMessageBox(wxString::FromUTF8(errorMessage), "Visualization error", wxOK | wxICON_ERROR, dashboard);
            });
        });
    }

public:
    bool OnInit() override {
        if (!wxApp::OnInit())
            return false;

        mainMenu = new GraphicsMainMenu("Sorting Visualizer", [this](AlgorithmRunner algorithm) {
            startVisualization(std::move(algorithm));
        });
        SetTopWindow(mainMenu);
        mainMenu->Show();
        return true;
    }

    int OnExit() override {
        if (sortWorker.joinable())
            sortWorker.join();
        return wxApp::OnExit();
    }
};

wxIMPLEMENT_APP(SortingVisualizerApp);
