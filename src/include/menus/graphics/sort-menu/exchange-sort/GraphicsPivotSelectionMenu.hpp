#pragma once

#include <wx/frame.h>
#include <wx/string.h>

#include "../../GraphicsAlgorithmSelection.hpp"

class GraphicsPivotSelectionMenu : public wxFrame {
private:
    void createControls();

    void onLomutoQuickSortPivotSelection(wxCommandEvent& event);
    void onHoareQuickSortPivotSelection(wxCommandEvent& event);
    void onDualPivotQuickSortPivotSelection(wxCommandEvent& event);

    GraphicsAlgorithmSelection onSelected;

public:
    explicit GraphicsPivotSelectionMenu(const wxString& title, GraphicsAlgorithmSelection onSelected = {});
};
