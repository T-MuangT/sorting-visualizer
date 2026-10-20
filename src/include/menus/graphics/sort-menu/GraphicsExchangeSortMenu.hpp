#pragma once

#include <wx/frame.h>
#include <wx/string.h>

#include "../GraphicsAlgorithmSelection.hpp"

class GraphicsExchangeSortMenu : public wxFrame {
private:
    void createControls();

    void onBubbleSortBranch(wxCommandEvent& event);
    void onPartitionSortBranch(wxCommandEvent& event);

    GraphicsAlgorithmSelection onSelected;

public:
    explicit GraphicsExchangeSortMenu(const wxString& title, GraphicsAlgorithmSelection onSelected = {});
};
