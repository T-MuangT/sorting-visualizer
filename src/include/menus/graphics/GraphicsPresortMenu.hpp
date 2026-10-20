#pragma once

#include <wx/dialog.h>
#include <wx/choice.h>
#include <wx/textctrl.h>

#include "../../PresortConfig.hpp"

class GraphicsPresortMenu : public wxDialog {
public:
    explicit GraphicsPresortMenu(wxWindow* parent);
    PresortConfig getConfig() const;

private:
    void createControls();
    void onStart(wxCommandEvent& event);

    wxChoice* patternChoice = nullptr;
    wxTextCtrl* arraySizeInput = nullptr;
    wxTextCtrl* delayInput = nullptr;
};
