#include <wx/wx.h>

#include <utility>

#include "../../../algorithms/merge-sort/MergeSort.hpp"
#include "../../../include/menus/graphics/sort-menu/GraphicsMergeSortMenu.hpp"

GraphicsMergeSortMenu::GraphicsMergeSortMenu(const wxString& title, GraphicsAlgorithmSelection selected)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(420, 300)), onSelected(std::move(selected)) {
    createControls();
    Centre();
}

void GraphicsMergeSortMenu::createControls() {
    auto* panel = new wxPanel(this);
    auto* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(new wxStaticText(panel, wxID_ANY, "Choose a merge sort implementation"), 0, wxALIGN_CENTER | wxALL, 18);
    auto* merge = new wxButton(panel, wxID_ANY, "Merge Sort Branch", wxDefaultPosition, wxSize(240, 42));
    sizer->Add(merge, 0, wxALIGN_CENTER | wxBOTTOM, 10);
    panel->SetSizer(sizer);
    merge->Bind(wxEVT_BUTTON, &GraphicsMergeSortMenu::onMergeSortBranch, this);
}

void GraphicsMergeSortMenu::onMergeSortBranch(wxCommandEvent&) {
    const wxArrayString options{"Merge Sort"};
    const std::vector<AlgorithmRunner> algorithms{AlgorithmRunner::fromSession(mergeSort)};
    if (chooseGraphicsAlgorithm(this, "Merge Sort Branch", options, algorithms, onSelected)) Close(true);
}
