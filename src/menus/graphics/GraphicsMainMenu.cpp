#include <wx/wx.h>

#include <utility>

#include "../../include/menus/graphics/GraphicsMainMenu.hpp"
#include "../../include/menus/graphics/sort-menu/GraphicsExchangeSortMenu.hpp"
#include "../../include/menus/graphics/sort-menu/GraphicsSelectionSortMenu.hpp"
#include "../../include/menus/graphics/sort-menu/GraphicsInsertionSortMenu.hpp"
#include "../../include/menus/graphics/sort-menu/GraphicsMergeSortMenu.hpp"
#include "../../include/menus/graphics/sort-menu/GraphicsDistributionSortMenu.hpp"

namespace {
enum FamilyId {
    ExchangeId = wxID_HIGHEST + 1,
    SelectionId,
    InsertionId,
    MergeId,
    DistributionId
};
}

GraphicsMainMenu::GraphicsMainMenu(const wxString& title, GraphicsAlgorithmSelection onSelected)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(500, 450)), onSelected(std::move(onSelected)) {
    createMenuBar();
    createControls();
    Centre();
}

void GraphicsMainMenu::createMenuBar() {
    auto* menuBar = new wxMenuBar;
    auto* fileMenu = new wxMenu;
    fileMenu->Append(wxID_EXIT, "E&xit\tAlt-X");
    menuBar->Append(fileMenu, "&File");
    SetMenuBar(menuBar);
    Bind(wxEVT_MENU, [this](wxCommandEvent&) { Close(true); }, wxID_EXIT);
}

void GraphicsMainMenu::createControls() {
    auto* panel = new wxPanel(this);
    auto* sizer = new wxBoxSizer(wxVERTICAL);
    auto* title = new wxStaticText(panel, wxID_ANY, "Select a Sorting Family");
    sizer->Add(title, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 20);

    const wxString labels[] = {"Exchange Sorts", "Selection Sorts", "Insertion Sorts", "Merge Sorts", "Distribution Sorts"};
    const int ids[] = {ExchangeId, SelectionId, InsertionId, MergeId, DistributionId};
    for (std::size_t i = 0; i < 5; ++i) {
        auto* button = new wxButton(panel, ids[i], labels[i], wxDefaultPosition, wxSize(260, 40));
        sizer->Add(button, 0, wxALIGN_CENTER | wxBOTTOM, 10);
        button->Bind(wxEVT_BUTTON, &GraphicsMainMenu::openFamilyMenu, this);
    }
    panel->SetSizer(sizer);
}

void GraphicsMainMenu::openFamilyMenu(wxCommandEvent& event) {
    wxFrame* menu = nullptr;
    switch (event.GetId()) {
        case ExchangeId: menu = new GraphicsExchangeSortMenu("Exchange Sorts", onSelected); break;
        case SelectionId: menu = new GraphicsSelectionSortMenu("Selection Sorts", onSelected); break;
        case InsertionId: menu = new GraphicsInsertionSortMenu("Insertion Sorts", onSelected); break;
        case MergeId: menu = new GraphicsMergeSortMenu("Merge Sorts", onSelected); break;
        case DistributionId: menu = new GraphicsDistributionSortMenu("Distribution Sorts", onSelected); break;
        default: return;
    }
    menu->Show();
}
