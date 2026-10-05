#include <utility>

#include "../include/algorithms/PairwiseCompareSwap.hpp"

bool pairwiseCompareSwap(
    std::vector<int>& arr,
    int lhs,
    int rhs) {

    if (arr[lhs] <= arr[rhs]) {
        return false;
    }

    std::swap(arr[lhs], arr[rhs]);
    return true;
}