#pragma once

#include <wx/frame.h>
#include <wx/string.h>

#include "../GraphicsAlgorithmSelection.hpp"

class GraphicsMergeSortMenu : public wxFrame {
private:
    void createControls();

    void onMergeSortBranch(wxCommandEvent& event);

    GraphicsAlgorithmSelection onSelected;

public:
    explicit GraphicsMergeSortMenu(const wxString& title, GraphicsAlgorithmSelection onSelected = {});
};
