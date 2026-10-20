#include <limits>
#include <wx/wx.h>
#include <wx/valnum.h>

#include "../../include/menus/graphics/GraphicsPresortMenu.hpp"

GraphicsPresortMenu::GraphicsPresortMenu(wxWindow* parent)
    : wxDialog(parent, wxID_ANY, "Array Setup", wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER) {
    createControls();
    CentreOnParent();
}

PresortConfig GraphicsPresortMenu::getConfig() const {
    PresortConfig config;
    const int pattern = patternChoice->GetSelection();
    config.pattern = pattern == 1 ? Pattern::ReverseSorted : pattern == 2 ? Pattern::NearlySorted : Pattern::UniformRandom;
    long size = 32;
    if (arraySizeInput->GetValue().ToLong(&size) && size > 0)
        config.arraySize = static_cast<std::size_t>(size);
    long delay = 100;
    if (delayInput->GetValue().ToLong(&delay) && delay >= 0 && delay <= std::numeric_limits<int>::max())
        config.delayMs = static_cast<int>(delay);
    return config;
}

void GraphicsPresortMenu::createControls() {
    auto* root = new wxBoxSizer(wxVERTICAL);
    auto* form = new wxFlexGridSizer(2, 10, 10);
    form->AddGrowableCol(1, 1);

    form->Add(new wxStaticText(this, wxID_ANY, "Data pattern:"), 0, wxALIGN_CENTER_VERTICAL);
    const wxString patterns[] = {"Uniform random", "Reverse sorted", "Nearly sorted"};
    patternChoice = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 3, patterns);
    patternChoice->SetSelection(0);
    form->Add(patternChoice, 1, wxEXPAND);

    form->Add(new wxStaticText(this, wxID_ANY, "Array size:"), 0, wxALIGN_CENTER_VERTICAL);
    arraySizeInput = new wxTextCtrl(this, wxID_ANY, "32", wxDefaultPosition, wxDefaultSize, 0, wxIntegerValidator<unsigned long>());
    form->Add(arraySizeInput, 1, wxEXPAND);

    form->Add(new wxStaticText(this, wxID_ANY, "Frame delay (ms):"), 0, wxALIGN_CENTER_VERTICAL);
    delayInput = new wxTextCtrl(this, wxID_ANY, "100", wxDefaultPosition, wxDefaultSize, 0, wxIntegerValidator<unsigned long>());
    form->Add(delayInput, 1, wxEXPAND);
    root->Add(form, 1, wxALL | wxEXPAND, 16);

    auto* buttons = new wxStdDialogButtonSizer;
    auto* start = new wxButton(this, wxID_OK, "Start");
    auto* cancel = new wxButton(this, wxID_CANCEL, "Cancel");
    buttons->AddButton(start);
    buttons->AddButton(cancel);
    buttons->Realize();
    root->Add(buttons, 0, wxALL | wxALIGN_RIGHT, 12);
    SetSizerAndFit(root);
    SetMinSize(wxSize(340, -1));
    Bind(wxEVT_BUTTON, &GraphicsPresortMenu::onStart, this, wxID_OK);
}

void GraphicsPresortMenu::onStart(wxCommandEvent&) {
    long value = 0;
    if (!arraySizeInput->GetValue().ToLong(&value) || value <= 0) {
        wxMessageBox("Enter an array size greater than zero.", "Invalid array size", wxOK | wxICON_WARNING, this);
        arraySizeInput->SetFocus();
        return;
    }
    if (!delayInput->GetValue().ToLong(&value) || value < 0 || value > std::numeric_limits<int>::max()) {
        wxMessageBox("Enter a non-negative frame delay.", "Invalid frame delay", wxOK | wxICON_WARNING, this);
        delayInput->SetFocus();
        return;
    }
    EndModal(wxID_OK);
}
