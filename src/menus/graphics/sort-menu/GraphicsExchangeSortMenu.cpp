#include <wx/wx.h>

#include <utility>
#include <vector>

#include "../../../algorithms/exchange-sort/bubble-sort/BubbleSort.hpp"
#include "../../../algorithms/exchange-sort/bubble-sort/OptimizedBubbleSort.hpp"
#include "../../../algorithms/exchange-sort/bubble-sort/CocktailShakerSort.hpp"
#include "../../../algorithms/exchange-sort/bubble-sort/OptimizedCocktailShakerSort.hpp"
#include "../../../algorithms/exchange-sort/bubble-sort/OddEvenSort.hpp"
#include "../../../algorithms/exchange-sort/bubble-sort/OptimizedOddEvenSort.hpp"
#include "../../../algorithms/exchange-sort/bubble-sort/CombSort.hpp"
#include "../../../algorithms/exchange-sort/bubble-sort/OptimizedCombSort.hpp"
#include "../../../algorithms/exchange-sort/partition-sort/CircleSort.hpp"
#include "../../../algorithms/exchange-sort/partition-sort/OptimizedCircleSort.hpp"
#include "../../../algorithms/exchange-sort/partition-sort/LomutoQuickSort.hpp"
#include "../../../algorithms/exchange-sort/partition-sort/HoareQuickSort.hpp"
#include "../../../algorithms/exchange-sort/partition-sort/DualPivotQuickSort.hpp"
#include "../../../algorithms/exchange-sort/partition-sort/StableQuickSort.hpp"
#include "../../../include/menus/graphics/sort-menu/exchange-sort/GraphicsPivotSelectionMenu.hpp"
#include "../../../include/menus/graphics/sort-menu/GraphicsExchangeSortMenu.hpp"

GraphicsExchangeSortMenu::GraphicsExchangeSortMenu(const wxString& title, GraphicsAlgorithmSelection selected)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(420, 320)), onSelected(std::move(selected)) {
    createControls();
    Centre();
}

void GraphicsExchangeSortMenu::createControls() {
    auto* panel = new wxPanel(this);
    auto* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(new wxStaticText(panel, wxID_ANY, "Choose an exchange sort branch"), 0, wxALIGN_CENTER | wxALL, 18);
    auto* bubble = new wxButton(panel, wxID_ANY, "Bubble Sort Branch", wxDefaultPosition, wxSize(240, 42));
    auto* partition = new wxButton(panel, wxID_ANY, "Partition Sort Branch", wxDefaultPosition, wxSize(240, 42));
    sizer->Add(bubble, 0, wxALIGN_CENTER | wxBOTTOM, 10);
    sizer->Add(partition, 0, wxALIGN_CENTER | wxBOTTOM, 10);
    panel->SetSizer(sizer);
    bubble->Bind(wxEVT_BUTTON, &GraphicsExchangeSortMenu::onBubbleSortBranch, this);
    partition->Bind(wxEVT_BUTTON, &GraphicsExchangeSortMenu::onPartitionSortBranch, this);
}

void GraphicsExchangeSortMenu::onBubbleSortBranch(wxCommandEvent&) {
    const wxArrayString options{"Bubble Sort", "Optimized Bubble Sort", "Cocktail Shaker Sort", "Optimized Cocktail Shaker Sort", "Odd-Even Sort", "Parallel Odd-Even Sort", "Comb Sort", "Parallel Comb Sort"};
    const std::vector<AlgorithmRunner> algorithms{
        AlgorithmRunner::fromClassic(bubbleSort), AlgorithmRunner::fromClassic(optimizedBubbleSort),
        AlgorithmRunner::fromClassic(cocktailShakerSort), AlgorithmRunner::fromClassic(optimizedCocktailShakerSort),
        AlgorithmRunner::fromClassic(oddEvenSort), AlgorithmRunner::fromClassic(optimizedOddEvenSort),
        AlgorithmRunner::fromClassic(combSort), AlgorithmRunner::fromClassic(optimizedCombSort)
    };
    if (chooseGraphicsAlgorithm(this, "Bubble Sort Branch", options, algorithms, onSelected))
        Close(true);
}

void GraphicsExchangeSortMenu::onPartitionSortBranch(wxCommandEvent&) {
    const wxArrayString options{"Circle Sort", "Parallel Circle Sort", "Lomuto Quicksort", "Hoare Quicksort", "Dual-Pivot Quicksort", "Stable Quicksort"};
    wxSingleChoiceDialog dialog(this, "Choose an algorithm:", "Partition Sort Branch", options);
    if (dialog.ShowModal() != wxID_OK)
        return;
    const int selection = dialog.GetSelection();
    if (selection >= 2 && selection <= 4) {
        auto* pivotMenu = new GraphicsPivotSelectionMenu(dialog.GetStringSelection(), [this](AlgorithmRunner algorithm) {
            if (onSelected)
                onSelected(std::move(algorithm));
            Close(true);
        });
        pivotMenu->Show();
        return;
    }
    AlgorithmRunner algorithm;
    switch (selection) {
        case 0: algorithm = AlgorithmRunner::fromClassic(circleSort); break;
        case 1: algorithm = AlgorithmRunner::fromClassic(optimizedCircleSort); break;
        case 5: algorithm = AlgorithmRunner::fromSession(stableQuickSort); break;
        default: return;
    }
    if (onSelected)
        onSelected(std::move(algorithm));
    Close(true);
}
