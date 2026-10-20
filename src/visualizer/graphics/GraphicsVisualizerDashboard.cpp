#include <wx/app.h>
#include <wx/dcbuffer.h>
#include <wx/menu.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/utils.h>

#include <algorithm>
#include <chrono>
#include <thread>

#include "../../include/visualizer/graphics/GraphicsVisualizerDashboard.hpp"

namespace {
constexpr int kMainArrayView = wxID_HIGHEST + 101;
constexpr int kTableView = wxID_HIGHEST + 102;
constexpr int kGraphView = wxID_HIGHEST + 103;
const wxColour kCanvas(242, 246, 251);
const wxColour kPanel(250, 252, 255);

void prepareCanvas(wxPanel* panel) {
    panel->SetBackgroundStyle(wxBG_STYLE_PAINT);
    panel->SetBackgroundColour(kPanel);
}
}

GraphicsVisualizerDashboard::GraphicsVisualizerDashboard(wxWindow* parent, const wxString& title)
    : wxFrame(parent, wxID_ANY, title, wxDefaultPosition, wxSize(1280, 850), wxDEFAULT_FRAME_STYLE | wxCLIP_CHILDREN) {
    createMenuBar();
    createControls();
    createLayout();
    const auto refresh = [this] {
        requestRefresh();
        if (frameDelayMs > 0)
            std::this_thread::sleep_for(std::chrono::milliseconds(frameDelayMs));
    };
    arrayVisualizer.setRefreshCallback(refresh);
    tableVisualizer.setRefreshCallback(refresh);
    graphVisualizer.setRefreshCallback(refresh);
    arrayVisualizer.initialize();
    tableVisualizer.initialize();
    graphVisualizer.initialize();
    Bind(wxEVT_CLOSE_WINDOW, [this](wxCloseEvent& event) {
        if (sortingRunning) {
            event.Veto();
            return;
        }
        if (auto* parentFrame = wxDynamicCast(GetParent(), wxFrame)) {
            parentFrame->Show();
            if (wxTheApp)
                wxTheApp->SetTopWindow(parentFrame);
        }
        event.Skip();
    });
    Centre();
}

void GraphicsVisualizerDashboard::requestRefresh() {
    if (refreshPending.exchange(true))
        return;

    CallAfter([this] {
        refreshPending.store(false);
        if (mainArrayPanel) mainArrayPanel->Refresh(false);
        if (tablePanel) tablePanel->Refresh(false);
        if (graphPanel) graphPanel->Refresh(false);
    });
}

GraphicsVisualizerDashboard::~GraphicsVisualizerDashboard() {
    arrayVisualizer.shutdown();
    tableVisualizer.shutdown();
    graphVisualizer.shutdown();
}

void GraphicsVisualizerDashboard::createMenuBar() {
    auto* menuBar = new wxMenuBar;
    auto* fileMenu = new wxMenu;
    fileMenu->Append(wxID_EXIT, "E&xit\tAlt-X");
    menuBar->Append(fileMenu, "&File");

    auto* viewMenu = new wxMenu;
    viewMenu->AppendCheckItem(kMainArrayView, "Main and auxiliary arrays")->Check(true);
    viewMenu->AppendCheckItem(kTableView, "Auxiliary table")->Check(true);
    viewMenu->AppendCheckItem(kGraphView, "Tree graph")->Check(true);
    menuBar->Append(viewMenu, "&View");
    SetMenuBar(menuBar);

    Bind(wxEVT_MENU, [this](wxCommandEvent&) { Close(); }, wxID_EXIT);
    Bind(wxEVT_MENU, [this](wxCommandEvent& event) {
        if (mainArrayPanel) mainArrayPanel->Show(event.IsChecked());
        Layout();
    }, kMainArrayView);
    Bind(wxEVT_MENU, [this](wxCommandEvent& event) {
        if (tablePanel) tablePanel->Show(event.IsChecked());
        Layout();
    }, kTableView);
    Bind(wxEVT_MENU, [this](wxCommandEvent& event) {
        if (graphPanel) graphPanel->Show(event.IsChecked());
        Layout();
    }, kGraphView);
}

void GraphicsVisualizerDashboard::createControls() {
    auto* root = new wxPanel(this);
    root->SetBackgroundColour(kCanvas);

    auto* heading = new wxStaticText(root, wxID_ANY, "Sorting Visualizer");
    heading->SetFont(wxFont(15, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    auto* subtitle = new wxStaticText(root, wxID_ANY,
        "Compare the active arrays, auxiliary storage, and the complete tree structure in one view.");

    mainArrayPanel = new wxPanel(root, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE);
    tablePanel = new wxPanel(root, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE);
    graphPanel = new wxPanel(root, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE);
    prepareCanvas(mainArrayPanel);
    prepareCanvas(tablePanel);
    prepareCanvas(graphPanel);

    mainArrayPanel->Bind(wxEVT_PAINT, [this](wxPaintEvent&) {
        wxAutoBufferedPaintDC dc(mainArrayPanel);
        dc.SetBackground(wxBrush(kPanel));
        dc.Clear();
        arrayVisualizer.draw(dc, mainArrayPanel->GetClientRect());
    });
    tablePanel->Bind(wxEVT_PAINT, [this](wxPaintEvent&) {
        wxAutoBufferedPaintDC dc(tablePanel);
        dc.SetBackground(wxBrush(kPanel));
        dc.Clear();
        tableVisualizer.draw(dc, tablePanel->GetClientRect());
    });
    graphPanel->Bind(wxEVT_PAINT, [this](wxPaintEvent&) {
        wxAutoBufferedPaintDC dc(graphPanel);
        dc.SetBackground(wxBrush(kPanel));
        dc.Clear();
        graphVisualizer.draw(dc, graphPanel->GetClientRect());
    });

    auto* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(heading, 0, wxLEFT | wxRIGHT | wxTOP, 12);
    sizer->Add(subtitle, 0, wxLEFT | wxRIGHT | wxBOTTOM, 12);
    sizer->Add(mainArrayPanel, 3, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 8);
    auto* lower = new wxBoxSizer(wxHORIZONTAL);
    lower->Add(tablePanel, 1, wxEXPAND | wxRIGHT, 4);
    lower->Add(graphPanel, 1, wxEXPAND | wxLEFT, 4);
    sizer->Add(lower, 2, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 8);
    root->SetSizer(sizer);
    SetSizer(new wxBoxSizer(wxVERTICAL));
    GetSizer()->Add(root, 1, wxEXPAND);
}

void GraphicsVisualizerDashboard::createLayout() {
    Layout();
    mainArrayPanel->Refresh(false);
    tablePanel->Refresh(false);
    graphPanel->Refresh(false);
}

GraphicsArrayVisualizer& GraphicsVisualizerDashboard::getArrayVisualizer() noexcept {
    return arrayVisualizer;
}

GraphicsTableVisualizer& GraphicsVisualizerDashboard::getTableVisualizer() noexcept {
    return tableVisualizer;
}

GraphicsGraphVisualizer& GraphicsVisualizerDashboard::getGraphVisualizer() noexcept {
    return graphVisualizer;
}

void GraphicsVisualizerDashboard::setFrameDelay(int delayMs) noexcept {
    frameDelayMs = std::max(0, delayMs);
}

void GraphicsVisualizerDashboard::setSortingRunning(bool running) noexcept {
    sortingRunning = running;
}
