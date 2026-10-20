#include <wx/wx.h>

#include <utility>

#include "../../../algorithms/selection-sort/selection-sort/SelectionSort.hpp"
#include "../../../algorithms/selection-sort/selection-sort/DoubleSelectionSort.hpp"
#include "../../../algorithms/selection-sort/selection-sort/CycleSort.hpp"
#include "../../../algorithms/selection-sort/heap-sort/MaxHeapSort.hpp"
#include "../../../algorithms/selection-sort/heap-sort/MinHeapSort.hpp"
#include "../../../algorithms/selection-sort/heap-sort/SmoothSort.hpp"
#include "../../../include/menus/graphics/sort-menu/GraphicsSelectionSortMenu.hpp"

GraphicsSelectionSortMenu::GraphicsSelectionSortMenu(const wxString& title, GraphicsAlgorithmSelection selected)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(420, 320)), onSelected(std::move(selected)) {
    createControls();
    Centre();
}

void GraphicsSelectionSortMenu::createControls() {
    auto* panel = new wxPanel(this);
    auto* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(new wxStaticText(panel, wxID_ANY, "Choose a selection sort branch"), 0, wxALIGN_CENTER | wxALL, 18);
    auto* selection = new wxButton(panel, wxID_ANY, "Selection Sort Branch", wxDefaultPosition, wxSize(240, 42));
    auto* heap = new wxButton(panel, wxID_ANY, "Heap Sort Branch", wxDefaultPosition, wxSize(240, 42));
    sizer->Add(selection, 0, wxALIGN_CENTER | wxBOTTOM, 10);
    sizer->Add(heap, 0, wxALIGN_CENTER | wxBOTTOM, 10);
    panel->SetSizer(sizer);
    selection->Bind(wxEVT_BUTTON, &GraphicsSelectionSortMenu::onSelectionSortBranch, this);
    heap->Bind(wxEVT_BUTTON, &GraphicsSelectionSortMenu::onHeapSortBranch, this);
}

void GraphicsSelectionSortMenu::onSelectionSortBranch(wxCommandEvent&) {
    const wxArrayString options{"Selection Sort", "Double Selection Sort", "Cycle Sort"};
    const std::vector<AlgorithmRunner> algorithms{
        AlgorithmRunner::fromClassic(selectionSort), AlgorithmRunner::fromClassic(doubleSelectionSort),
        AlgorithmRunner::fromClassic(cycleSort)
    };
    if (chooseGraphicsAlgorithm(this, "Selection Sort Branch", options, algorithms, onSelected)) Close(true);
}

void GraphicsSelectionSortMenu::onHeapSortBranch(wxCommandEvent&) {
    const wxArrayString options{"Max Heapsort", "Min Heapsort", "Smoothsort"};
    const std::vector<AlgorithmRunner> algorithms{
        AlgorithmRunner::fromClassic(maxHeapSort), AlgorithmRunner::fromClassic(minHeapSort),
        AlgorithmRunner::fromClassic(smoothSort)
    };
    if (chooseGraphicsAlgorithm(this, "Heap Sort Branch", options, algorithms, onSelected)) Close(true);
}
