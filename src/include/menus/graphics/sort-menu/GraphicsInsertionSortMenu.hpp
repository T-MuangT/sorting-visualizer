#pragma once

#include <wx/frame.h>
#include <wx/string.h>

#include "../GraphicsAlgorithmSelection.hpp"

class GraphicsInsertionSortMenu : public wxFrame {
private:
    void createControls();

    void onInsertionSortBranch(wxCommandEvent& event);
    void onTreeSortBranch(wxCommandEvent& event);

    GraphicsAlgorithmSelection onSelected;

public:
    explicit GraphicsInsertionSortMenu(const wxString& title, GraphicsAlgorithmSelection onSelected = {});
};
