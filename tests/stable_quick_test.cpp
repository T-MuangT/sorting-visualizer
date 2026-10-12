#include <algorithm>
#include <iostream>
#include <vector>

#include "include/NoopVisualizers.hpp"
#include "../src/include/visualizer/VisualizationSession.hpp"
#include "../src/algorithms/exchange-sort/partition-sort/StableQuickSort.hpp"

int main() {
	const std::vector<std::vector<int>> cases = {
		{},
		{42},
		{5, 4, 3, 2, 1},
		{1, 2, 3, 4, 5},
		{3, 1, 3, 2, 1},
		{-5, 0, -2, 9, -1},
		{10, -1, 7, -9, 3, 2, 0},
		{1, 2, 3, 5, 4, 6, 7, 8},
		{12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1}
	};

	for (const auto& input : cases) {
		auto data = input;

		// Dummy noop visualizers and session for the algorithm
		NoopArrayVisualizer av;
		NoopTableVisualizer tv;
		NoopGraphVisualizer gv;
		VisualizationSession session(av, tv, gv);

		stableQuickSort(data, session);

		if (!std::is_sorted(data.begin(), data.end())) {
			std::cerr << "FAIL: stableQuickSort produced unsorted output" << std::endl;
			return 1;
		}

		std::vector<int> expected = input;
		std::sort(expected.begin(), expected.end());
		if (data != expected) {
			std::cerr << "FAIL: stableQuickSort produced incorrect values" << std::endl;
			return 1;
		}
	}

	std::cout << "Stable Quicksort tests passed." << std::endl;
	return 0;
}
