#include <random>

#include "../include/algorithms/PivotSelection.hpp"

int medianOfThreeIndices(const std::vector<int>& arr, int first, int second, int third) {
    int a = arr[first];
    int b = arr[second];
    int c = arr[third];

    if ((a <= b && b <= c) || (c <= b && b <= a)) return second;
    if ((b <= a && a <= c) || (c <= a && a <= b)) return first;
    return third;
}

int firstIndexPivot(const std::vector<int>&, int low, int) {
    return low;
}

int lastIndexPivot(const std::vector<int>&, int, int high) {
    return high;
}

int middleIndexPivot(const std::vector<int>&, int low, int high) {
    return low + (high - low) / 2;
}

int randomIndexPivot(const std::vector<int>&, int low, int high) {
    static std::random_device rd;
    static std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(low, high);
    return distribution(generator);
}

int medianOfThreePivot(const std::vector<int>& arr, int low, int high) {
    int mid = low + (high - low) / 2;
    return medianOfThreeIndices(arr, low, mid, high);
}

PivotPair firstAndLastIndicesPivots(const std::vector<int>&, int low, int high) {
    int firstPivot = low;
    int secondPivot = high;
    return {firstPivot, secondPivot};
}
// twoRandomIndices may return arbitrary indices and will be normalized in the algorithm.
PivotPair twoRandomIndicesPivots(const std::vector<int>&, int low, int high) {
    static std::random_device rd;
    static std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(low, high);

    int firstPivot = distribution(generator);
    int secondPivot;

    do {
        secondPivot = distribution(generator);
    } while (secondPivot == firstPivot);

    return {firstPivot, secondPivot};
}

PivotPair twoQuartileMediansPivots(const std::vector<int>& arr, int low, int high) {
    int mid = low + (high - low) / 2;
    int firstQuartile = low + (high - low) / 4;
    int thirdQuartile = low + 3 * (high - low) / 4;

    int firstPivot = medianOfThreeIndices(arr, low, firstQuartile, mid);
    int secondPivot = medianOfThreeIndices(arr, mid, thirdQuartile, high);

    return {firstPivot, secondPivot};
}