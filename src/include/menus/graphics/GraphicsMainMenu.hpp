#pragma once

#include <wx/frame.h>
#include <wx/string.h>

#include "GraphicsAlgorithmSelection.hpp"

class GraphicsMainMenu : public wxFrame {
public:
    explicit GraphicsMainMenu(const wxString& title, GraphicsAlgorithmSelection onSelected = {});

private:
    void createMenuBar();
    void createControls();
    void openFamilyMenu(wxCommandEvent& event);

    GraphicsAlgorithmSelection onSelected;
};
