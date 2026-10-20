#pragma once

#include <wx/frame.h>
#include <wx/string.h>

#include "../GraphicsAlgorithmSelection.hpp"

class GraphicsDistributionSortMenu : public wxFrame {
private:
    void createControls();

    void onPigeonholeSortBranch(wxCommandEvent& event);
    void onCountingSortBranch(wxCommandEvent& event);

    GraphicsAlgorithmSelection onSelected;

public:
    explicit GraphicsDistributionSortMenu(const wxString& title, GraphicsAlgorithmSelection onSelected = {});
};
