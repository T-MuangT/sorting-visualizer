#pragma once

#include <wx/frame.h>
#include <wx/string.h>

#include "../GraphicsAlgorithmSelection.hpp"

class GraphicsSelectionSortMenu : public wxFrame {
private:
    void createControls();

    void onSelectionSortBranch(wxCommandEvent& event);
    void onHeapSortBranch(wxCommandEvent& event);

    GraphicsAlgorithmSelection onSelected;

public:
    explicit GraphicsSelectionSortMenu(const wxString& title, GraphicsAlgorithmSelection onSelected = {});
};
