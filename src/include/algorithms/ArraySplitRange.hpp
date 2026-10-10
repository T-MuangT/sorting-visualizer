#pragma once

struct ArraySplitRange {
    int low;
    int high;
};

bool isValid(const ArraySplitRange& range);
bool isSingleton(const ArraySplitRange& range);
int size(const ArraySplitRange& range);
int midpoint(const ArraySplitRange& range);