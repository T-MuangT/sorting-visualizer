#pragma once

#include <cstddef>
#include <string>
#include "Types.hpp"

// Lightweight snapshot for UI backends (Terminal, Raylib, SFML, GUI, etc.)
struct StatsSnapshot {
    size_t comparisons{0};
    size_t swaps{0};
};

class SortStats {
private:
    size_t comparisonCount{0};
    size_t swapCount{0};

public:
    SortStats() = default;

    // Mutators
    void reset() noexcept;
    void recordEvent(SortEvent event) noexcept;

    // Accessors
    [[nodiscard]] size_t getComparisons() const noexcept { return comparisonCount; }
    [[nodiscard]] size_t getSwaps() const noexcept { return swapCount; }

    // Export UI-agnostic snapshot
    [[nodiscard]] StatsSnapshot getSnapshot() const noexcept {
        return {comparisonCount, swapCount};
    }
};