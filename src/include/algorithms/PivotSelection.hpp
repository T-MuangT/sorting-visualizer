#pragma once

#include <vector>

struct PivotPair {
    int firstPivot;
    int secondPivot;
};

int medianOfThreeIndices(const std::vector<int>& arr, int first, int second, int third);

using PivotSelector = int (*)(const std::vector<int>&, int, int);

int firstIndexPivot(const std::vector<int>&, int low, int);
int lastIndexPivot(const std::vector<int>&, int, int high);
int middleIndexPivot(const std::vector<int>&, int low, int high);
int randomIndexPivot(const std::vector<int>&, int low, int high);
int medianOfThreePivot(const std::vector<int>& arr, int low, int high);

using DualPivotSelector = PivotPair (*)(const std::vector<int>&, int low, int high);

PivotPair firstAndLastIndicesPivots(const std::vector<int>&, int low, int high);
PivotPair twoRandomIndicesPivots(const std::vector<int>&, int low, int high);
PivotPair twoQuartileMediansPivots(const std::vector<int>& arr, int low, int high);