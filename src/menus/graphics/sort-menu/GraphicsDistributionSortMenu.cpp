#include <wx/wx.h>

#include <utility>

#include "../../../algorithms/distribution-sort/pigeonhole-sort/PigeonholeSort.hpp"
#include "../../../algorithms/distribution-sort/counting-sort/CountingSort.hpp"
#include "../../../include/menus/graphics/sort-menu/GraphicsDistributionSortMenu.hpp"

GraphicsDistributionSortMenu::GraphicsDistributionSortMenu(const wxString& title, GraphicsAlgorithmSelection selected)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(420, 320)), onSelected(std::move(selected)) {
    createControls();
    Centre();
}

void GraphicsDistributionSortMenu::createControls() {
    auto* panel = new wxPanel(this);
    auto* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(new wxStaticText(panel, wxID_ANY, "Choose a distribution sort branch"), 0, wxALIGN_CENTER | wxALL, 18);
    auto* pigeonhole = new wxButton(panel, wxID_ANY, "Pigeonhole Sort Branch", wxDefaultPosition, wxSize(240, 42));
    auto* counting = new wxButton(panel, wxID_ANY, "Counting Sort Branch", wxDefaultPosition, wxSize(240, 42));
    sizer->Add(pigeonhole, 0, wxALIGN_CENTER | wxBOTTOM, 10);
    sizer->Add(counting, 0, wxALIGN_CENTER | wxBOTTOM, 10);
    panel->SetSizer(sizer);
    pigeonhole->Bind(wxEVT_BUTTON, &GraphicsDistributionSortMenu::onPigeonholeSortBranch, this);
    counting->Bind(wxEVT_BUTTON, &GraphicsDistributionSortMenu::onCountingSortBranch, this);
}

void GraphicsDistributionSortMenu::onPigeonholeSortBranch(wxCommandEvent&) {
    const wxArrayString options{"Pigeonhole Sort"};
    const std::vector<AlgorithmRunner> algorithms{AlgorithmRunner::fromSession(pigeonholeSort)};
    if (chooseGraphicsAlgorithm(this, "Pigeonhole Sort Branch", options, algorithms, onSelected)) Close(true);
}

void GraphicsDistributionSortMenu::onCountingSortBranch(wxCommandEvent&) {
    const wxArrayString options{"Counting Sort"};
    const std::vector<AlgorithmRunner> algorithms{AlgorithmRunner::fromSession(countingSort)};
    if (chooseGraphicsAlgorithm(this, "Counting Sort Branch", options, algorithms, onSelected)) Close(true);
}
