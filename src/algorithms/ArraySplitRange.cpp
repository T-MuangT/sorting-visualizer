#include "../include/algorithms/ArraySplitRange.hpp"

bool isValid(const ArraySplitRange& range) {
    return range.low <= range.high;
}

bool isSingleton(const ArraySplitRange& range) {
    return range.low == range.high;
}

int size(const ArraySplitRange& range) {
    return range.high - range.low + 1;
}

int midpoint(const ArraySplitRange& range) {
    return range.low + (range.high - range.low) / 2;
}