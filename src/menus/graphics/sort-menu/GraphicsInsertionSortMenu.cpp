#include <wx/wx.h>

#include <utility>

#include "../../../algorithms/insertion-sort/insertion-sort/InsertionSort.hpp"
#include "../../../algorithms/insertion-sort/insertion-sort/BinaryInsertionSort.hpp"
#include "../../../algorithms/insertion-sort/insertion-sort/ShellSort.hpp"
#include "../../../algorithms/insertion-sort/tree-sort/UnbalancedBstTreeSort.hpp"
#include "../../../include/menus/graphics/sort-menu/GraphicsInsertionSortMenu.hpp"

GraphicsInsertionSortMenu::GraphicsInsertionSortMenu(const wxString& title, GraphicsAlgorithmSelection selected)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(420, 320)), onSelected(std::move(selected)) {
    createControls();
    Centre();
}

void GraphicsInsertionSortMenu::createControls() {
    auto* panel = new wxPanel(this);
    auto* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(new wxStaticText(panel, wxID_ANY, "Choose an insertion sort branch"), 0, wxALIGN_CENTER | wxALL, 18);
    auto* insertion = new wxButton(panel, wxID_ANY, "Insertion Sort Branch", wxDefaultPosition, wxSize(240, 42));
    auto* tree = new wxButton(panel, wxID_ANY, "Tree Sort Branch", wxDefaultPosition, wxSize(240, 42));
    sizer->Add(insertion, 0, wxALIGN_CENTER | wxBOTTOM, 10);
    sizer->Add(tree, 0, wxALIGN_CENTER | wxBOTTOM, 10);
    panel->SetSizer(sizer);
    insertion->Bind(wxEVT_BUTTON, &GraphicsInsertionSortMenu::onInsertionSortBranch, this);
    tree->Bind(wxEVT_BUTTON, &GraphicsInsertionSortMenu::onTreeSortBranch, this);
}

void GraphicsInsertionSortMenu::onInsertionSortBranch(wxCommandEvent&) {
    const wxArrayString options{"Insertion Sort", "Binary Insertion Sort", "Shell Sort"};
    const std::vector<AlgorithmRunner> algorithms{
        AlgorithmRunner::fromClassic(insertionSort), AlgorithmRunner::fromClassic(binaryInsertionSort),
        AlgorithmRunner::fromClassic(shellSort)
    };
    if (chooseGraphicsAlgorithm(this, "Insertion Sort Branch", options, algorithms, onSelected)) Close(true);
}

void GraphicsInsertionSortMenu::onTreeSortBranch(wxCommandEvent&) {
    const wxArrayString options{"Unbalanced BST Tree Sort"};
    const std::vector<AlgorithmRunner> algorithms{AlgorithmRunner::fromSession(unbalancedBstTreeSort)};
    if (chooseGraphicsAlgorithm(this, "Tree Sort Branch", options, algorithms, onSelected)) Close(true);
}
