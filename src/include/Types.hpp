#pragma once
#include <vector>
#include <string>
#include <functional>

enum class SortEvent {
    Compare,
    Swap
};

using SortCallback = std::function<void(
    SortEvent event, 
    int idx1, 
    int idx2, 
    const std::string& stepName)>;