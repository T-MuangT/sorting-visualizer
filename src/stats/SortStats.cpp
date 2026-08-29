#include "../include/SortStats.hpp"

void SortStats::reset() noexcept {
    comparisonCount = 0;
    swapCount = 0;
}

void SortStats::recordEvent(SortEvent event) noexcept {
    switch (event) {
        case SortEvent::Compare:
            comparisonCount++;
            break;
        case SortEvent::Swap:
            swapCount++;
            break;
    }
}