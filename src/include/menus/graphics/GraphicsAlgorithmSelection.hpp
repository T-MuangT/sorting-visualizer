#pragma once

#include <cstddef>
#include <functional>
#include <vector>

#include <wx/choicdlg.h>
#include <wx/window.h>

#include "../../AlgorithmRunner.hpp"

using GraphicsAlgorithmSelection = std::function<void(AlgorithmRunner)>;

inline bool chooseGraphicsAlgorithm(wxWindow* parent, const wxString& title, const wxArrayString& choices, const std::vector<AlgorithmRunner>& algorithms, const GraphicsAlgorithmSelection& onSelected) {
    wxSingleChoiceDialog dialog(parent, "Choose an algorithm:", title, choices);
    if (dialog.ShowModal() != wxID_OK)
        return false;

    const int selected = dialog.GetSelection();
    if (selected < 0 || selected >= static_cast<int>(algorithms.size()) || !algorithms[static_cast<std::size_t>(selected)])
        return false;

    if (onSelected)
        onSelected(algorithms[static_cast<std::size_t>(selected)]);
    return true;
}
