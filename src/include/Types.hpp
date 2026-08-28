#pragma once
#include <vector>
#include <functional>
#include <string>

enum class SortEvent {
    Compare,
    Swap,
    PassComplete
};

// Unified callback type emitted by all algorithms
using SortCallback = std::function<void(SortEvent event, int idx1, int idx2, const std::string& stepName)>;