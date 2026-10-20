#include <wx/wx.h>

#include <utility>

#include "../../../../algorithms/exchange-sort/partition-sort/LomutoQuickSort.hpp"
#include "../../../../algorithms/exchange-sort/partition-sort/HoareQuickSort.hpp"
#include "../../../../algorithms/exchange-sort/partition-sort/DualPivotQuickSort.hpp"
#include "../../../../include/algorithms/PivotSelection.hpp"
#include "../../../../include/menus/graphics/sort-menu/exchange-sort/GraphicsPivotSelectionMenu.hpp"

namespace {
bool selectPivot(wxWindow* parent, const wxString& title, const GraphicsAlgorithmSelection& onSelected,
                 const wxArrayString& options, const std::vector<PivotSelector>& selectors,
                 bool lomuto) {
    wxSingleChoiceDialog dialog(parent, "Choose a pivot strategy:", title, options);
    if (dialog.ShowModal() != wxID_OK)
        return false;
    const auto selector = selectors[static_cast<std::size_t>(dialog.GetSelection())];
    AlgorithmRunner runner = AlgorithmRunner::fromClassic([selector, lomuto](std::vector<int>& values, SortCallback notify) {
        if (lomuto)
            lomutoQuickSort(values, notify, selector);
        else
            hoareQuickSort(values, notify, selector);
    });
    if (onSelected)
        onSelected(std::move(runner));
    return true;
}
}

GraphicsPivotSelectionMenu::GraphicsPivotSelectionMenu(const wxString& title, GraphicsAlgorithmSelection selected)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(420, 300)), onSelected(std::move(selected)) {
    createControls();
    Centre();
}

void GraphicsPivotSelectionMenu::createControls() {
    auto* panel = new wxPanel(this);
    auto* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(new wxStaticText(panel, wxID_ANY, "Choose a quicksort partition scheme"), 0, wxALIGN_CENTER | wxALL, 18);
    auto* lomuto = new wxButton(panel, wxID_ANY, "Lomuto Quicksort");
    auto* hoare = new wxButton(panel, wxID_ANY, "Hoare Quicksort");
    auto* dual = new wxButton(panel, wxID_ANY, "Dual-Pivot Quicksort");
    sizer->Add(lomuto, 0, wxALIGN_CENTER | wxBOTTOM, 8);
    sizer->Add(hoare, 0, wxALIGN_CENTER | wxBOTTOM, 8);
    sizer->Add(dual, 0, wxALIGN_CENTER | wxBOTTOM, 8);
    panel->SetSizer(sizer);
    lomuto->Bind(wxEVT_BUTTON, &GraphicsPivotSelectionMenu::onLomutoQuickSortPivotSelection, this);
    hoare->Bind(wxEVT_BUTTON, &GraphicsPivotSelectionMenu::onHoareQuickSortPivotSelection, this);
    dual->Bind(wxEVT_BUTTON, &GraphicsPivotSelectionMenu::onDualPivotQuickSortPivotSelection, this);
}

void GraphicsPivotSelectionMenu::onLomutoQuickSortPivotSelection(wxCommandEvent&) {
    const wxArrayString choices{"First element", "Last element", "Middle element", "Random element", "Median of three"};
    const std::vector<PivotSelector> selectors{firstIndexPivot, lastIndexPivot, middleIndexPivot, randomIndexPivot, medianOfThreePivot};
    if (selectPivot(this, "Lomuto Quicksort", onSelected, choices, selectors, true)) Close(true);
}

void GraphicsPivotSelectionMenu::onHoareQuickSortPivotSelection(wxCommandEvent&) {
    const wxArrayString choices{"First element", "Last element", "Middle element", "Random element", "Median of three"};
    const std::vector<PivotSelector> selectors{firstIndexPivot, lastIndexPivot, middleIndexPivot, randomIndexPivot, medianOfThreePivot};
    if (selectPivot(this, "Hoare Quicksort", onSelected, choices, selectors, false)) Close(true);
}

void GraphicsPivotSelectionMenu::onDualPivotQuickSortPivotSelection(wxCommandEvent&) {
    const wxArrayString choices{"First and last elements", "Two random elements", "Two quartile medians"};
    wxSingleChoiceDialog dialog(this, "Choose a pivot strategy:", "Dual-Pivot Quicksort", choices);
    if (dialog.ShowModal() != wxID_OK)
        return;
    const std::vector<DualPivotSelector> selectors{firstAndLastIndicesPivots, twoRandomIndicesPivots, twoQuartileMediansPivots};
    const auto selector = selectors[static_cast<std::size_t>(dialog.GetSelection())];
    auto runner = AlgorithmRunner::fromClassic([selector](std::vector<int>& values, SortCallback notify) {
        dualPivotQuickSort(values, notify, selector);
    });
    if (onSelected)
        onSelected(std::move(runner));
    Close(true);
}
