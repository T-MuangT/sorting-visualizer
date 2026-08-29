#pragma once

#include <functional>
#include <vector>
#include <string>
#include "../Types.hpp"

// Define signature alias if not already declared globally
using SortCallback = std::function<void(SortEvent, int, int, const std::string&)>;
using AlgorithmRunner = std::function<void(std::vector<int>&, SortCallback)>;

AlgorithmRunner selectBubbleAlgorithm();
AlgorithmRunner selectQuickSortAlgorithm();
AlgorithmRunner selectExchangeAlgorithm();